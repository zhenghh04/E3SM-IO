/*********************************************************************
 *
 * Copyright (C) 2022, Northwestern University
 * See COPYRIGHT notice in top-level directory.
 *
 * This program is part of the E3SM I/O benchmark.
 *
 *********************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
//
#include <assert.h>
#include <errno.h>
#include <libgen.h> /* basename() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* getopt() */

#include <vector>
//
#include <mpi.h>
//
#include <e3sm_io.h>
#include <e3sm_io_err.h>

#include <e3sm_io_driver.hpp>

#define MAX_NFILES 6
#define LINE_SIZE  4692802

static void set_start_count(int             nprocs,
                            int             rank,
                            MPI_Offset      nelems,
                            MPI_Offset     *start,
                            MPI_Offset     *count)
{
    *count = nelems / nprocs;
    *start = *count * rank;
    if (rank < nelems % nprocs) {
        *start += rank;
        (*count)++;
    }
    else {
        *start += nelems % nprocs;
    }
}

/*----< replay_decomp() >-------------------------------------------------*/
/* Read I/O decomposition file, cfg->decomp_path. The contents of the file
 * are shown below, an example from map_f_case_16p.nc
 *
 *   % ncdump -h map_f_case_16p.nc
 *   netcdf map_f_case_16p.nc {
 *   // file format: CDF-1
 *   dimensions:
 *       num_decomp = 3 ;
 *       decomp_nprocs = 16 ;
 *       D1.total_nreqs = 47 ;
 *       D2.total_nreqs = 407 ;
 *       D3.total_nreqs = 29788 ;
 *   variables:
 *       int D1.nreqs(decomp_nprocs) ;
 *           D1.nreqs:description = "Number of noncontiguous requests per process" ;
 *       int D1.offsets(D1.total_nreqs) ;
 *           D1.offsets:description = "Flattened starting indices of noncontiguous requests" ;
 *       int D1.lengths(D1.total_nreqs) ;
 *           D1.lengths:description = "Lengths of noncontiguous requests" ;
 *           D1.lengths:max = 36 ;
 *           D1.lengths:min = 9 ;
 *       int D2.nreqs(decomp_nprocs) ;
 *           D2.nreqs:description = "Number of noncontiguous requests per process" ;
 *       int D2.offsets(D2.total_nreqs) ;
 *           D2.offsets:description = "Flattened starting indices of noncontiguous requests" ;
 *       int D2.lengths(D2.total_nreqs) ;
 *           D2.lengths:description = "Lengths of noncontiguous requests" ;
 *           D2.lengths:max = 4 ;
 *           D2.lengths:min = 1 ;
 *       int D3.nreqs(decomp_nprocs) ;
 *           D3.nreqs:description = "Number of noncontiguous requests per process" ;
 *       int D3.offsets(D3.total_nreqs) ;
 *           D3.offsets:description = "Flattened starting indices of noncontiguous requests" ;
 *       int D3.lengths(D3.total_nreqs) ;
 *           D3.lengths:description = "Lengths of noncontiguous requests" ;
 *           D3.lengths:max = 4 ;
 *           D3.lengths:min = 1 ;
 *
 *   // global attributes:
 *       :command_line = "./dat2nc -o map_f_case_16p.nc -1
 * datasets/piodecomp16tasks16io01dims_ioid_514.dat -2
 * datasets/piodecomp16tasks16io01dims_ioid_516.dat -3
 * datasets/piodecomp16tasks16io02dims_ioid_548.dat " ; :D1.ndims = 1 ; :D1.dims = 866 ;
 *       :D1.max_nreqs = 4 ;
 *       :D1.min_nreqs = 2 ;
 *       :D2.ndims = 1 ;
 *       :D2.dims = 866 ;
 *       :D2.max_nreqs = 39 ;
 *       :D2.min_nreqs = 13 ;
 *       :D3.ndims = 2 ;
 *       :D3.dims = 72 , 866 ;
 *       :D3.max_nreqs = 2808 ;
 *       :D3.min_nreqs = 936 ;
 *   }
 *
 * Arguments:
 *   cfg->decomp_path: (IN) input file name, a NetCDF file containing the data
 *                     decomposition generated by PIO library from an E3SM run.
 *   decom->num_decomp (OUT) number of decompositions
 *   decom->ndims:     (OUT) number of decomposition dimensions
 *   decom->dims:      (OUT) global array dimension lengths of decompositions
 *   decom->contig_nreqs: (OUT) number of noncontiguous requests assigned to
 *                     this process. May be zero.
 *   decom->disps:     (OUT) starting offsets of individual requests (sorted)
 *                     Memory space will be allocated in this subroutine
 *                     and must be freed by the caller. Any pair of
 *                     disps[][i] and blocklens[][i] is within the size of
 *                     the least significant dimension.
 *   decom->blocklens: (OUT) lengths of individual requests
 *                     Memory space will be allocated in this subroutine
 *                     and must be freed by the caller.
 */

int replay_decomp (e3sm_io_config *cfg, e3sm_io_decom *decom) {
    int err = 0;
    int i;
    int fidi, fido;        // Fid for in and out file
    int dimndi, dimndo;    // dimid for num decomp
    int dimnpi, dimnpo;    // dimid for num processes
    int dimnri, dimnro;    // dimid for num reqs
    int dimnrri, dimnrro;  // dimid for num raw reqs
    int ndims;
    int varnri, varnro;
    int varnrri, varnrro;
    int varoffi, varoffo;
    int varroffi, varroffo;
    int varleni, varleno;
    int varfilli, varfillo;
    std::vector<int> dims;
    int max_nreqs, min_nreqs;
    int max_len, min_len;
    int *buf      = NULL;
    bool have_raw = false;
    e3sm_io_config cfg_in;  // Dummy cfg for read decom
    e3sm_io_driver *din  = NULL;
    e3sm_io_driver *dout = NULL;
    MPI_Offset num_decomp;       // # decom maps
    MPI_Offset decomp_nprocs;    // # procs sharing the decom
    MPI_Offset total_nreqs;      // Di total_nreqs
    MPI_Offset total_raw_nreqs;  // Di total_raw_nreqs
    MPI_Offset att_len;          // size of str_att
    MPI_Offset start, count;
    std::vector<char> str_att;
    std::string name;

    // Set up dummy config for the driver
    cfg_in.io_comm        = MPI_COMM_WORLD;
    cfg_in.info           = MPI_INFO_NULL;
    cfg_in.num_iotasks    = cfg_in.np;
    cfg_in.num_subfiles   = 0;
    cfg_in.out_path[0]    = '\0';
    cfg_in.in_path[0]     = '\0';
    cfg_in.decomp_path[0] = '\0';
    cfg_in.hx             = -1;
    cfg_in.wr             = 0;
    cfg_in.rd             = 0;
    cfg_in.nvars          = 0;
    cfg_in.strategy       = undef_io;
    cfg_in.api            = undef_api;
    cfg_in.chunksize      = 0;
    cfg_in.filter         = none;
    cfg_in.verbose        = 0;
    cfg_in.keep_outfile   = 0;
    cfg_in.profiling      = 0;
    cfg_in.two_buf        = 0;
    cfg_in.non_contig_buf = 0;
    cfg_in.io_stride      = 1;
    cfg_in.sub_comm       = MPI_COMM_NULL;
    cfg_in.rank           = cfg->rank;

    // Set up driver
    din = e3sm_io_get_driver (cfg->in_path, &cfg_in);
    CHECK_PTR (din)
    dout = e3sm_io_get_driver (NULL, cfg);
    CHECK_PTR (dout)

    /* open input file that contains I/O decomposition information */
    err = din->open (cfg->in_path, cfg->io_comm, cfg->info, &fidi);
    CHECK_ERR
    err = dout->create (cfg->out_path, cfg->io_comm, cfg->info, &fido);
    CHECK_ERR

    // command_line
    err = din->inq_att (fidi, NC_GLOBAL, "command_line", &att_len);
    CHECK_ERR
    str_att.resize (att_len + 1);
    err = din->get_att (fidi, NC_GLOBAL, "command_line", str_att.data ());
    CHECK_ERR
    err = dout->put_att (fido, NC_GLOBAL, "command_line", NC_CHAR, att_len, str_att.data ());
    CHECK_ERR

    // num_decomp
    err = din->inq_dim (fidi, "num_decomp", &dimndi);
    CHECK_ERR
    err = din->inq_dimlen (fidi, dimndi, &num_decomp);
    CHECK_ERR
    err = dout->def_dim (fido, "num_decomp", num_decomp, &dimndo);
    CHECK_ERR

    // decomp_nprocs
    err = din->inq_dim (fidi, "decomp_nprocs", &dimnpi);
    CHECK_ERR
    err = din->inq_dimlen (fidi, dimnpi, &decomp_nprocs);
    CHECK_ERR
    err = dout->def_dim (fido, "decomp_nprocs", decomp_nprocs, &dimnpo);
    CHECK_ERR

    for (i = 1; i <= num_decomp; i++) {
        // Di.total_nreqs
        name = "D" + std::to_string (i) + ".total_nreqs";
        err  = din->inq_dim (fidi, name, &dimnri);
        CHECK_ERR
        err = din->inq_dimlen (fidi, dimnri, &total_nreqs);
        CHECK_ERR
        err = dout->def_dim (fido, name, total_nreqs, &dimnro);
        CHECK_ERR

        // Di.total_raw_nreqs
        name = "D" + std::to_string (i) + ".total_raw_nreqs";
        err  = din->inq_dim (fidi, name, &dimnrri);
        if (err >= 0) {
            have_raw = true;
            err      = din->inq_dimlen (fidi, dimnrri, &total_raw_nreqs);
            CHECK_ERR
            err = dout->def_dim (fido, name, total_raw_nreqs, &dimnrro);
            CHECK_ERR
        } else {
            total_raw_nreqs = 0;
        }

        // Di.ndims
        name = "D" + std::to_string (i) + ".ndims";
        err  = din->get_att (fidi, NC_GLOBAL, name, &ndims);
        CHECK_ERR
        err = dout->put_att (fido, NC_GLOBAL, name, NC_INT, 1, &ndims);
        CHECK_ERR

        dims.resize (ndims);
        // Di.dims
        name = "D" + std::to_string (i) + ".dims";
        err  = din->get_att (fidi, NC_GLOBAL, name, dims.data ());
        CHECK_ERR
        err = dout->put_att (fido, NC_GLOBAL, name, NC_INT, ndims, dims.data ());
        CHECK_ERR

        // Di.max_nreqs
        name = "D" + std::to_string (i) + ".max_nreqs";
        err  = din->get_att (fidi, NC_GLOBAL, name, &max_nreqs);
        CHECK_ERR
        err = dout->put_att (fido, NC_GLOBAL, name, NC_INT, 1, &max_nreqs);
        CHECK_ERR

        // Di.min_nreqs
        name = "D" + std::to_string (i) + ".min_nreqs";
        err  = din->get_att (fidi, NC_GLOBAL, name, &min_nreqs);
        CHECK_ERR
        err = dout->put_att (fido, NC_GLOBAL, name, NC_INT, 1, &min_nreqs);
        CHECK_ERR

        // Di.fully_covered
        name = "D" + std::to_string (i) + ".fully_covered";
        err = din->inq_att (fidi, NC_GLOBAL, name, &att_len);
        CHECK_ERR
        str_att.resize (att_len + 1);
        err  = din->get_att(fidi, NC_GLOBAL, name, str_att.data());
        CHECK_ERR
        err = dout->put_att(fido, NC_GLOBAL, name, NC_CHAR, att_len, str_att.data ());
        CHECK_ERR

        // Di.nreqs
        name = "D" + std::to_string (i) + ".nreqs";
        err  = din->inq_varid (fidi, name.c_str(), &varnri);
        CHECK_ERR
        err = dout->def_var (fido, name, NC_INT, 1, &dimnpo, &varnro);
        CHECK_ERR

        // Di.nreqs:description
        err = din->inq_att (fidi, varnri, "description", &att_len);
        CHECK_ERR
        str_att.resize (att_len + 1);
        err = din->get_att (fidi, varnri, "description", str_att.data ());
        CHECK_ERR
        err = dout->put_att (fido, varnro, "description", NC_CHAR, att_len, str_att.data ());
        CHECK_ERR

        if (have_raw) {
            // Di.raw_nreqs
            name = "D" + std::to_string (i) + ".raw_nreqs";
            err  = din->inq_varid (fidi, name.c_str(), &varnrri);
            CHECK_ERR
            err = dout->def_var (fido, name, NC_INT, 1, &dimnpo, &varnrro);
            CHECK_ERR

            // Di.raw_nreqs:description
            err = din->inq_att (fidi, varnrri, "description", &att_len);
            CHECK_ERR
            str_att.resize (att_len + 1);
            err = din->get_att (fidi, varnrri, "description", str_att.data ());
            CHECK_ERR
            err = dout->put_att (fido, varnrro, "description", NC_CHAR, att_len, str_att.data ());
            CHECK_ERR
        }

        // Di.offsets
        name = "D" + std::to_string (i) + ".offsets";
        err  = din->inq_varid (fidi, name.c_str(), &varoffi);
        CHECK_ERR
        err = dout->def_var (fido, name, NC_INT, 1, &dimnro, &varoffo);
        CHECK_ERR

        // Di.offsets:description
        err = din->inq_att (fidi, varoffi, "description", &att_len);
        CHECK_ERR
        str_att.resize (att_len + 1);
        err = din->get_att (fidi, varoffi, "description", str_att.data ());
        CHECK_ERR
        err = dout->put_att (fido, varoffo, "description", NC_CHAR, att_len, str_att.data ());
        CHECK_ERR

        if (have_raw) {
            // Di.raw_offsets
            name = "D" + std::to_string (i) + ".raw_offsets";
            err  = din->inq_varid (fidi, name.c_str(), &varroffi);
            CHECK_ERR
            err = dout->def_var (fido, name, NC_INT, 1, &dimnrro, &varroffo);
            CHECK_ERR

            // Di.raw_offsets:description
            err = din->inq_att (fidi, varroffi, "description", &att_len);
            CHECK_ERR
            str_att.resize (att_len + 1);
            err = din->get_att (fidi, varroffi, "description", str_att.data ());
            CHECK_ERR
            err = dout->put_att (fido, varroffo, "description", NC_CHAR, att_len, str_att.data ());
            CHECK_ERR
        }

        // Di.lengths
        name = "D" + std::to_string (i) + ".lengths";
        err  = din->inq_varid (fidi, name.c_str(), &varleni);
        CHECK_ERR
        err = dout->def_var (fido, name, NC_INT, 1, &dimnro, &varleno);
        CHECK_ERR

        // Di.lengths:description
        err = din->inq_att (fidi, varleni, "description", &att_len);
        CHECK_ERR
        str_att.resize (att_len + 1);
        err = din->get_att (fidi, varleni, "description", str_att.data ());
        CHECK_ERR
        err = dout->put_att (fido, varleno, "description", NC_CHAR, att_len, str_att.data ());
        CHECK_ERR

        // Di.lengths:max
        err = din->get_att (fidi, varleni, "max", &max_len);
        CHECK_ERR
        err = dout->put_att (fido, varleno, "max", NC_INT, 1, &max_len);
        CHECK_ERR

        // Di.lengths:min
        err = din->get_att (fidi, varleni, "min", &min_len);
        CHECK_ERR
        err = dout->put_att (fido, varleno, "min", NC_INT, 1, &min_len);
        CHECK_ERR

        /* Di.fill_starts */
        name = "D" + std::to_string (i) + ".fill_starts";
        err  = din->inq_varid(fidi, name.c_str(), &varfilli);
        CHECK_ERR
        err = dout->def_var(fido, name, NC_INT, 1, &dimnpo, &varfillo);
        CHECK_ERR

        /* Di.fill_starts:description */
        err = din->inq_att(fidi, varfilli, "description", &att_len);
        CHECK_ERR
        str_att.resize(att_len + 1);
        err = din->get_att(fidi, varfilli, "description", str_att.data());
        CHECK_ERR
        err = dout->put_att(fido, varfillo, "description", NC_CHAR, att_len, str_att.data());
        CHECK_ERR

        /* exit define mode */
        err = dout->enddef (fido);
        CHECK_ERR

        MPI_Offset nelems = std::max(total_nreqs, std::max (total_raw_nreqs, decomp_nprocs));
        nelems = nelems / cfg->np + 1;

        buf = (int *)malloc (nelems * sizeof (int));
        CHECK_PTR (buf)

        /* Di.nreqs */
        nelems = decomp_nprocs;
        set_start_count(cfg->np, cfg->rank, nelems, &start, &count);

        err = din->get_vara (fidi, varnri, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR
        err = dout->put_vara (fido, varnro, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR

        /* Di.fill_starts */
        err = din->get_vara (fidi, varfilli, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR
        err = dout->put_vara (fido, varfillo, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR

        /* Di.raw_nreqs */
        if (have_raw) {
            err = din->get_vara (fidi, varnrri, MPI_INT, &start, &count, buf, coll);
            CHECK_ERR
            err = dout->put_vara (fido, varnrro, MPI_INT, &start, &count, buf, coll);
            CHECK_ERR
        }

        /* Di.offsets */
        nelems = total_nreqs;
        set_start_count(cfg->np, cfg->rank, nelems, &start, &count);

        err = din->get_vara (fidi, varoffi, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR
        err = dout->put_vara (fido, varoffo, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR

        /* Di.lengths */
        err = din->get_vara (fidi, varleni, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR
        err = dout->put_vara (fido, varleno, MPI_INT, &start, &count, buf, coll);
        CHECK_ERR

        /* Di.raw_offsets */
        if (have_raw) {
            nelems = total_raw_nreqs;
            set_start_count(cfg->np, cfg->rank, nelems, &start, &count);

            err = din->get_vara (fidi, varroffi, MPI_INT, &start, &count, buf, coll);
            CHECK_ERR
            err = dout->put_vara (fido, varroffo, MPI_INT, &start, &count, buf, coll);
            CHECK_ERR
        }

        free (buf);
        buf = NULL;

        err = dout->redef (fido);
        CHECK_ERR
    }

    err = din->close (fidi);
    CHECK_ERR
    err = dout->close (fido);
    CHECK_ERR

err_out:;
    if (din) { delete din; }
    if (dout) { delete dout; }
    if (buf) { free (buf); }
    return err;
}

static void usage (char *argv0) {
    const char *help =
        "Usage: %s [-h|-v] -a fmt -i input_file -o out_file\n"
        "   [-h]            Print help\n"
        "   [-v]            verbose mode\n"
        "   -a fmt          output file format, fmt is one of the followings\n"
        "      cdf5:        NetCDF classic 64-bit data format\n"
        "      netcdf4:     NetCDF-4 (HDF5-based) format\n"
        "      hdf5:        HDF5 format\n"
        "      bp:          ADIOS2 BP format\n"
        "   -i input_file   input file name\n"
        "   -o out_file     output file name\n";
    fprintf (stderr, help, argv0);
}

/*----< main() >------------------------------------------------------------*/
int main (int argc, char **argv) {
    char cmd_line[4096];
    int i, rank, nprocs, num_decomp = 0, err = 0;
    e3sm_io_config cfg;
    e3sm_io_decom decom;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

    cmd_line[0] = '\0';
    for (i = 0; i < argc; i++) {
        strcat (cmd_line, argv[i]);
        strcat (cmd_line, " ");
    }

    // Set up default config
    cfg.io_comm        = comm;
    cfg.info           = MPI_INFO_NULL;
    cfg.np             = nprocs;
    cfg.num_iotasks    = cfg.np;
    cfg.num_subfiles   = 0;
    cfg.out_path[0]    = '\0';
    cfg.in_path[0]     = '\0';
    cfg.decomp_path[0] = '\0';
    cfg.hx             = -1;
    cfg.wr             = 0;
    cfg.rd             = 0;
    cfg.nvars          = 0;
    cfg.strategy       = undef_io;
    cfg.api            = undef_api;
    cfg.chunksize      = 0;
    cfg.filter         = none;
    cfg.verbose        = 0;
    cfg.keep_outfile   = 0;
    cfg.profiling      = 0;
    cfg.two_buf        = 0;
    cfg.non_contig_buf = 0;
    cfg.io_stride      = 1;
    cfg.sub_comm       = MPI_COMM_NULL;
    cfg.rank           = rank;

    /* get command-line arguments */
    while ((i = getopt (argc, argv, "hvo:i:a:")) != EOF) {
        switch (i) {
            case 'a':;
                if (std::string (optarg) == "cdf5") {
                    cfg.api = pnetcdf;
                } else if (std::string (optarg) == "hdf5") {
                    cfg.api = hdf5;
                } else if (std::string (optarg) == "bp") {
                    cfg.api = adios;
                } else if (std::string (optarg) == "netcdf4") {
                    cfg.api = netcdf4;
                } else {
                    cfg.api = undef_api;
                }
                break;
            case 'v':
                cfg.verbose = 1;
                break;
            case 'o':
                strncpy (cfg.out_path, optarg, sizeof (cfg.out_path));
                break;
            case 'i':
                strncpy (cfg.in_path, optarg, sizeof (cfg.in_path));
                break;
            case 'h':
            default:
                if (rank == 0) usage (argv[0]);
                err = -1;
                goto err_out;
        }
    }

    if (cfg.in_path[0] == '\0') { /* input file name is mandatory */
        if (rank == 0) {
            printf ("input file is missing\n");
            usage (argv[0]);
        }
        err = -1;
        goto err_out;
    }
    if (cfg.out_path[0] == '\0') { /* output file name is mandatory */
        if (rank == 0) {
            printf ("output file is missing\n");
            usage (argv[0]);
        }
        err = -1;
        goto err_out;
    }

    if (cfg.verbose && rank == 0) {
        printf ("input  file: %s\n", cfg.in_path);
        printf ("output file: %s\n", cfg.out_path);
        printf ("Number of decomposition files: %d\n", num_decomp);
    }

    /* replay request information from decomposition file */
    err = replay_decomp (&cfg, &decom);
    CHECK_ERR

err_out:

    MPI_Finalize ();
    return err;
}
/*********************************************************************
 *
 * Copyright (C) 2021, Northwestern University
 * See COPYRIGHT notice in top-level directory.
 *
 * This program uses the E3SM I/O patterns recorded by the PIO library to
 * evaluate the performance of two PnetCDF APIs: ncmpi_vard_all(), and
 * ncmpi_iput_varn(). The E3SM I/O patterns consist of a large number of small,
 * noncontiguous requests on each MPI process, which presents a challenge for
 * achieving a good performance.
 *
 * See README.md for compile and run instructions.
 *
 *********************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
/**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcpy(), strncpy() */
/**/
#include <unistd.h> /* getopt() */
/**/
#include <mpi.h>
/**/
#include <e3sm_io.h>
#include <e3sm_io_err.h>

static inline int set_info (e3sm_io_config *cfg, e3sm_io_decom *decom) {
    int err, nerrs = 0;
    MPI_Offset estimated_nc_ibuf_size;

    /* set MPI-IO hints */
    MPI_Info_set (cfg->info, "romio_cb_write", "enable");  /* collective write */
    MPI_Info_set (cfg->info, "romio_no_indep_rw", "true"); /* no independent MPI-IO */

    /* set PnetCDF I/O hints */
    MPI_Info_set (cfg->info, "nc_var_align_size", "1");     /* no gap between variables */
    MPI_Info_set (cfg->info, "nc_in_place_swap", "enable"); /* in-place byte swap */

    /* use total write amount to estimate nc_ibuf_size */
    estimated_nc_ibuf_size =
        decom->dims[2][0] * decom->dims[2][1] * sizeof (double) / cfg->num_iotasks;
    estimated_nc_ibuf_size *= cfg->nvars;
    if (estimated_nc_ibuf_size > 16777216) {
        char nc_ibuf_size_str[32];
        sprintf (nc_ibuf_size_str, "%lld", estimated_nc_ibuf_size);
        MPI_Info_set (cfg->info, "nc_ibuf_size", nc_ibuf_size_str);
    }

err_out:;
    return nerrs;
}

/*----< print_info() >------------------------------------------------------*/
void print_info (MPI_Info *info_used) {
    int i, nkeys;

    MPI_Info_get_nkeys (*info_used, &nkeys);
    printf ("MPI File Info: nkeys = %d\n", nkeys);
    for (i = 0; i < nkeys; i++) {
        char key[MPI_MAX_INFO_KEY], value[MPI_MAX_INFO_VAL];
        int valuelen, flag;

        MPI_Info_get_nthkey (*info_used, i, key);
        MPI_Info_get_valuelen (*info_used, key, &valuelen, &flag);
        MPI_Info_get (*info_used, key, valuelen + 1, value, &flag);
        printf ("MPI File Info: [%2d] key = %25s, value = %s\n", i, key, value);
    }
}

/*----< usage() >------------------------------------------------------------*/
static void usage (char *argv0) {
    char *help =
        "Usage: %s [OPTION]...\n"
        "       [-h] Print help\n"
        "       [-v] Verbose mode\n"
        "       [-k] Keep the output files when the program exits\n"
        "       [-d] Run test that uses low-level APIs\n"
        "       [-n] Run test using noncontiguous write buffer\n"
        "       [-t] Write 2D variables followed by 3D variables\n"
        "       [-R] Test reading performance\n"
        "       [-W] Test writing performance\n"
        "       [-H num] File number to run in F case (-1 (both) (default), 0, 1)\n"
        "       [-r num] Number of records (default 1)\n"
        "       [-s num] Stride between IO tasks (default 1)\n"
        "       [-a api] Underlying API to test (pnc (default), hdf5, adios2)\n"
        "       [-l layout] Storage layout of the variables (contig (default), chunk)\n"
        "       [-o target_dir] Path to directory containing the test files (default ./)\n"
        "       [-i target_dir] Path to directory containing the input files\n"
        "       [-c output_dir] Name of input netCDF file describing data decompositions "
        "\n";
    fprintf (stderr, help, argv0);
}

/*----< main() >-------------------------------------------------------------*/
int main (int argc, char **argv) {
    int err, nerrs = 0;
    int i;
    char targetdir[E3SM_IO_MAX_PATH] = "./";
    char datadir[E3SM_IO_MAX_PATH]   = "";
    char cfgpath[E3SM_IO_MAX_PATH]   = "";
    e3sm_io_config cfg;
    e3sm_io_decom decom;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &(cfg.rank));
    MPI_Comm_size (MPI_COMM_WORLD, &(cfg.np));
    cfg.io_comm        = MPI_COMM_WORLD;
    cfg.info           = MPI_INFO_NULL;
    cfg.num_iotasks    = cfg.np;
    cfg.targetdir      = targetdir;
    cfg.datadir        = datadir;
    cfg.cfgpath        = cfgpath;
    cfg.hx             = 0;
    cfg.nrec           = 1;
    cfg.wr             = 0;
    cfg.rd             = 0;
    cfg.nvars          = 0;
    cfg.api            = pnc;
    cfg.layout         = contig;
    cfg.low_lvl        = 0;
    cfg.verbose        = 0;
    cfg.keep_outfile   = 0;
    cfg.two_buf        = 0;
    cfg.non_contig_buf = 0;
    cfg.io_stride      = 1;

    /* command-line arguments */
    while ((i = getopt (argc, argv, "vkr:s:l:o:i:c:dntRWH:ha:")) != EOF) switch (i) {
            case 'v':
                cfg.verbose = 1;
                break;
            case 'k':
                cfg.keep_outfile = 1;
                break;
            case 'r':
                cfg.nrec = atoi (optarg);
                break;
            case 's':
                cfg.io_stride = atoi (optarg);
                break;
            case 'a':
                if (strcmp (optarg, "pnc") == 0) {
                    cfg.api = pnc;
                } else if (strcmp (optarg, "hdf5") == 0) {
                    cfg.api = hdf5;
                } else if (strcmp (optarg, "adios2") == 0) {
                    cfg.api = adios2;
                } else {
                    RET_ERR ("Unknown API")
                }
                break;
            case 'l':
                if (strcmp (optarg, "contig") == 0) {
                    cfg.layout = contig;
                } else if (strcmp (optarg, "chunk") == 0) {
                    cfg.layout = chunk;
                } else {
                    RET_ERR ("Unknown layout")
                }
                break;
            case 'o':
                strncpy (cfg.targetdir, optarg, E3SM_IO_MAX_PATH);

                break;
            case 'i':
                strncpy (cfg.datadir, optarg, E3SM_IO_MAX_PATH);

                break;
            case 'c':
                strncpy (cfg.cfgpath, optarg, E3SM_IO_MAX_PATH);

                break;
            case 'd':
                cfg.low_lvl = 1;
                break;
            case 'n':
                cfg.non_contig_buf = 1;
                break;
            case 't':
                cfg.two_buf = 1;
                break;
            case 'R':
                cfg.rd = 1;
                break;
            case 'W':
                cfg.wr = 1;
                break;
            case 'H':
                cfg.hx = atoi (optarg);
                break;
            case 'h':
            default:
                if (cfg.rank == 0) usage (argv[0]);
                goto err_out;
        }

    if (cfg.cfgpath[0] == '\0') { /* input file is mandatory */
        if (!cfg.rank) usage (argv[0]);
        ERR_OUT ("Decomposition file not provided")
    }
    /* input file contains number of write requests and their file access
     * offsets (per array element) */
    PRINT_MSG (1, "input file name =%s\n", cfg.cfgpath);

    /* neither command-line option -R or -W is used, run write */
    if (!(cfg.wr || cfg.rd)) cfg.wr = 1;

    /* set the output folder name */
    PRINT_MSG (1, "Target folder name =%s\n", cfg.targetdir);
    if (cfg.datadir[0] != '\0') { PRINT_MSG (1, "Input folder name =%s\n", cfg.datadir); }

    err = MPI_Info_create (&(cfg.info));
    CHECK_MPIERR
    nerrs += set_info (&cfg, &decom);
    CHECK_NERR

    /* read request information from decompositions 1, 2 and 3 */
    err = read_decomp (cfg.verbose, cfg.io_comm, cfg.cfgpath, &(decom.num_decomp), decom.dims,
                       decom.contig_nreqs, decom.disps, decom.blocklens);
    CHECK_ERR

    nerrs += e3sm_io_core (&cfg, &decom);

err_out:;
    if (cfg.info != MPI_INFO_NULL) MPI_Info_free (&(cfg.info));
    if (cfg.io_comm != MPI_COMM_WORLD && cfg.io_comm != MPI_COMM_NULL) {
        MPI_Comm_free (&(cfg.io_comm));
    }

    /* Non-IO tasks wait for IO tasks to complete */
    MPI_Barrier (MPI_COMM_WORLD);
    MPI_Finalize ();

    return (nerrs > 0);
}
/*********************************************************************
 *
 * Copyright (C) 2018, Northwestern University
 * See COPYRIGHT notice in top-level directory.
 *
 * This program is part of the E3SM I/O benchmark.
 *
 *********************************************************************/

#include <assert.h>

#include "e3sm_io_hdf5.h"

#define INQ_VID(A, B, D, E, F, C) hdf5_inq_varid (A, B, C)
#define NOP(A, B, D, E, C)        NC_NOERR
#define NOP2(A, B, D, E, F, C)    NC_NOERR

/*----< def_F_case_h0() >----------------------------------------------------*/
int def_F_case_h0_hdf5 (hid_t ncid,               /* file ID */
                        const MPI_Offset dims[2], /* dimension sizes */
                        int nvars,                /* number of variables */
                        int *varids)            /* variable IDs */
{
    /* Total 408 variables */
    int lat, lon, area, lev, hyam, hybm, P0, ilev, hyai, hybi, time, date, datesec, time_bnds,
        date_written, time_written, ndbase, nsbase, nbdate, nbsec, mdt, ndcur, nscur, co2vmr,
        ch4vmr, n2ovmr, f11vmr, f12vmr, sol_tsi, nsteph, AEROD_v, ANRAIN, ANSNOW, AODABS, AODABSBC,
        AODBC, AODDUST, AODDUST1, AODDUST3, AODDUST4, AODMODE1, AODMODE2, AODMODE3, AODMODE4,
        AODNIR, AODPOM, AODSO4, AODSOA, AODSS, AODUV, AODVIS, AQRAIN, AQSNOW, AQ_DMS, AQ_H2O2,
        AQ_H2SO4, AQ_O3, AQ_SO2, AQ_SOAG, AREI, AREL, AWNC, AWNI, CCN3, CDNUMC, CLDHGH, CLDICE,
        CLDLIQ, CLDLOW, CLDMED, CLDTOT, CLOUD, CLOUDFRAC_CLUBB, CONCLD, DCQ, DF_DMS, DF_H2O2,
        DF_H2SO4, DF_O3, DF_SO2, DF_SOAG, DMS_SRF, DP_KCLDBASE, DP_MFUP_MAX, DP_WCLDBASE, DSTSFMBL,
        DTCOND, DTENDTH, DTENDTQ, EXTINCT, FICE, FLDS, FLNS, FLNSC, FLNT, FLNTC, FLUT, FLUTC, FREQI,
        FREQL, FREQR, FREQS, FSDS, FSDSC, FSNS, FSNSC, FSNT, FSNTC, FSNTOA, FSNTOAC, FSUTOA,
        FSUTOAC, F_eff, H2O2_SRF, H2SO4_SRF, H2SO4_sfgaex1, ICEFRAC, ICIMR, ICWMR, IWC, LANDFRAC,
        LHFLX, LINOZ_DO3, LINOZ_DO3_PSC, LINOZ_O3CLIM, LINOZ_O3COL, LINOZ_SSO3, LINOZ_SZA, LND_MBL,
        LWCF, Mass_bc, Mass_dst, Mass_mom, Mass_ncl, Mass_pom, Mass_so4, Mass_soa, NUMICE, NUMLIQ,
        NUMRAI, NUMSNO, O3, O3_SRF, OCNFRAC, OMEGA, OMEGA500, OMEGAT, PBLH, PHIS, PRECC, PRECL,
        PRECSC, PRECSL, PS, PSL, Q, QFLX, QREFHT, QRL, QRS, RAINQM, RAM1, RELHUM, SFDMS, SFH2O2,
        SFH2SO4, SFO3, SFSO2, SFSOAG, SFbc_a1, SFbc_a3, SFbc_a4, SFdst_a1, SFdst_a3, SFmom_a1,
        SFmom_a2, SFmom_a3, SFmom_a4, SFncl_a1, SFncl_a2, SFncl_a3, SFnum_a1, SFnum_a2, SFnum_a3,
        SFnum_a4, SFpom_a1, SFpom_a3, SFpom_a4, SFso4_a1, SFso4_a2, SFso4_a3, SFsoa_a1, SFsoa_a2,
        SFsoa_a3, SHFLX, SH_KCLDBASE, SH_MFUP_MAX, SH_WCLDBASE, SNOWHICE, SNOWHLND, SNOWQM, SO2,
        SO2_CLXF, SO2_SRF, SOAG_CLXF, SOAG_SRF, SOAG_sfgaex1, SOLIN, SSAVIS, SSTSFMBL, SSTSFMBL_OM,
        SWCF, T, TAUGWX, TAUGWY, TAUX, TAUY, TGCLDCWP, TGCLDIWP, TGCLDLWP, TH7001000, TMQ, TREFHT,
        TROP_P, TROP_T, TS, TSMN, TSMX, TUH, TUQ, TVH, TVQ, U, U10, UU, V, VQ, VT, VU, VV, WD_H2O2,
        WD_H2SO4, WD_SO2, WSUB, Z3, aero_water, airFV, bc_a1DDF, bc_a1SFWET, bc_a1_SRF,
        bc_a1_sfgaex1, bc_a3DDF, bc_a3SFWET, bc_a3_SRF, bc_a4DDF, bc_a4SFWET, bc_a4_CLXF, bc_a4_SRF,
        bc_a4_sfgaex1, bc_c1DDF, bc_c1SFWET, bc_c3DDF, bc_c3SFWET, bc_c4DDF, bc_c4SFWET, chla,
        dst_a1DDF, dst_a1SF, dst_a1SFWET, dst_a1_SRF, dst_a3DDF, dst_a3SF, dst_a3SFWET, dst_a3_SRF,
        dst_c1DDF, dst_c1SFWET, dst_c3DDF, dst_c3SFWET, hstobie_linoz, mlip, mom_a1DDF, mom_a1SF,
        mom_a1SFWET, mom_a1_SRF, mom_a1_sfgaex1, mom_a2DDF, mom_a2SF, mom_a2SFWET, mom_a2_SRF,
        mom_a3DDF, mom_a3SFWET, mom_a3_SRF, mom_a4DDF, mom_a4SF, mom_a4SFWET, mom_a4_SRF,
        mom_a4_sfgaex1, mom_c1DDF, mom_c1SFWET, mom_c2DDF, mom_c2SFWET, mom_c3DDF, mom_c3SFWET,
        mom_c4DDF, mom_c4SFWET, mpoly, mprot, ncl_a1DDF, ncl_a1SF, ncl_a1SFWET, ncl_a1_SRF,
        ncl_a2DDF, ncl_a2SF, ncl_a2SFWET, ncl_a2_SRF, ncl_a3DDF, ncl_a3SF, ncl_a3SFWET, ncl_a3_SRF,
        ncl_c1DDF, ncl_c1SFWET, ncl_c2DDF, ncl_c2SFWET, ncl_c3DDF, ncl_c3SFWET, num_a1DDF, num_a1SF,
        num_a1SFWET, num_a1_CLXF, num_a1_SRF, num_a1_sfgaex1, num_a2DDF, num_a2SFWET, num_a2_CLXF,
        num_a2_SRF, num_a3DDF, num_a3SF, num_a3SFWET, num_a3_SRF, num_a4DDF, num_a4SFWET,
        num_a4_CLXF, num_a4_SRF, num_a4_sfgaex1, num_c1DDF, num_c1SFWET, num_c2DDF, num_c2SFWET,
        num_c3DDF, num_c3SFWET, num_c4DDF, num_c4SFWET, pom_a1DDF, pom_a1SFWET, pom_a1_SRF,
        pom_a1_sfgaex1, pom_a3DDF, pom_a3SFWET, pom_a3_SRF, pom_a4DDF, pom_a4SFWET, pom_a4_CLXF,
        pom_a4_SRF, pom_a4_sfgaex1, pom_c1DDF, pom_c1SFWET, pom_c3DDF, pom_c3SFWET, pom_c4DDF,
        pom_c4SFWET, so4_a1DDF, so4_a1SFWET, so4_a1_CLXF, so4_a1_SRF, so4_a1_sfgaex1, so4_a2DDF,
        so4_a2SFWET, so4_a2_CLXF, so4_a2_SRF, so4_a2_sfgaex1, so4_a3DDF, so4_a3SFWET, so4_a3_SRF,
        so4_a3_sfgaex1, so4_c1DDF, so4_c1SFWET, so4_c2DDF, so4_c2SFWET, so4_c3DDF, so4_c3SFWET,
        soa_a1DDF, soa_a1SFWET, soa_a1_SRF, soa_a1_sfgaex1, soa_a2DDF, soa_a2SFWET, soa_a2_SRF,
        soa_a2_sfgaex1, soa_a3DDF, soa_a3SFWET, soa_a3_SRF, soa_a3_sfgaex1, soa_c1DDF, soa_c1SFWET,
        soa_c2DDF, soa_c2SFWET, soa_c3DDF, soa_c3SFWET;

    int i, err, nerrs = 0, dimids[3], iattr, mdims = 1;
    int dim_ncol, dim_time, dim_nbnd, dim_chars, dim_lev, dim_ilev;
    float fillv = 1.e+36f, missv = 1.e+36f;

    /* global attributes: */
    iattr = 4;
    err   = HDF5_PUT_ATT_INT (ncid, NC_GLOBAL, "ne", NC_INT, 1, &iattr);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, NC_GLOBAL, "np", NC_INT, 1, &iattr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "Conventions", 6, "CF-1.0");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "source", 3, "CAM");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "case", 20, "FC5AV1C-H01B_ne4_ne4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "title", 5, "UNSET");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "logname", 6, "wkliao");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "host", 10, "compute001");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "Version", 6, "$Name$");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "revision_Id", 4, "$Id$");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, NC_GLOBAL, "initial_file", 86,
        "/home/climate1/acme/inputdata/atm/cam/inic/homme/cami_mam3_Linoz_ne4np4_L72_c160909.nc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, NC_GLOBAL, "topography_file", 79,
        "/home/climate1/acme/inputdata/atm/cam/topo/USGS-gtopo30_ne4np4_16x.c20160612.nc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "time_period_freq", 5, "day_5");
    ERR;

    /* define dimensions */
    err = hdf5_def_dim (ncid, "ncol", dims[1], &dim_ncol);
    ERR;
    err = hdf5_def_dim (ncid, "time", NC_UNLIMITED, &dim_time);
    ERR;
    err = hdf5_def_dim (ncid, "nbnd", 2, &dim_nbnd);
    ERR;
    err = hdf5_def_dim (ncid, "chars", 8, &dim_chars);
    ERR;
    err = hdf5_def_dim (ncid, "lev", dims[0], &dim_lev);
    ERR;
    err = hdf5_def_dim (ncid, "ilev", dims[0] + 1, &dim_ilev);
    ERR;

    i = 0;

    /* define variables */
    dimids[0] = dim_ncol;
    err       = hdf5_def_var (ncid, "lat", NC_DOUBLE, 1, dimids, &lat);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lat, "long_name", 8, "latitude");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lat, "units", 13, "degrees_north");
    ERR;
    varids[i++] = lat;

    dimids[0] = dim_ncol;
    err       = hdf5_def_var (ncid, "lon", NC_DOUBLE, 1, dimids, &lon);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lon, "long_name", 9, "longitude");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lon, "units", 12, "degrees_east");
    ERR;
    varids[i++] = lon;

    dimids[0] = dim_ncol;
    err       = hdf5_def_var (ncid, "area", NC_DOUBLE, 1, dimids, &area);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, area, "long_name", 14, "gll grid areas");
    ERR;
    varids[i++] = area;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "lev", NC_DOUBLE, 1, dimids, &lev);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "long_name", 38, "hybrid level at midpoints (1000*(A+B))");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "units", 3, "hPa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "positive", 4, "down");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "standard_name", 43,
                             "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "formula_terms", 29, "a: hyam b: hybm p0: P0 ps: PS");
    ERR;
    varids[i++] = lev;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "hyam", NC_DOUBLE, 1, dimids, &hyam);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hyam, "long_name", 39, "hybrid A coefficient at layer midpoints");
    ERR;
    varids[i++] = hyam;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "hybm", NC_DOUBLE, 1, dimids, &hybm);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hybm, "long_name", 39, "hybrid B coefficient at layer midpoints");
    ERR;
    varids[i++] = hybm;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "P0", NC_DOUBLE, 0, NULL, &P0);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, P0, "long_name", 18, "reference pressure");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, P0, "units", 2, "Pa");
    ERR;
    varids[i++] = P0;

    dimids[0] = dim_ilev;
    err       = hdf5_def_var (ncid, "ilev", NC_DOUBLE, 1, dimids, &ilev);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, ilev, "long_name", 39, "hybrid level at interfaces (1000*(A+B))");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "units", 3, "hPa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "positive", 4, "down");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "standard_name", 43,
                             "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "formula_terms", 29, "a: hyai b: hybi p0: P0 ps: PS");
    ERR;
    varids[i++] = ilev;

    dimids[0] = dim_ilev;
    err       = hdf5_def_var (ncid, "hyai", NC_DOUBLE, 1, dimids, &hyai);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hyai, "long_name", 40, "hybrid A coefficient at layer interfaces");
    ERR;
    varids[i++] = hyai;

    dimids[0] = dim_ilev;
    err       = hdf5_def_var (ncid, "hybi", NC_DOUBLE, 1, dimids, &hybi);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hybi, "long_name", 40, "hybrid B coefficient at layer interfaces");
    ERR;
    varids[i++] = hybi;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "time", NC_DOUBLE, 1, dimids, &time);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "long_name", 4, "time");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "units", 30, "days since 0001-01-01 00:00:00");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "calendar", 6, "noleap");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "bounds", 9, "time_bnds");
    ERR;
    varids[i++] = time;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "date", NC_INT, 1, dimids, &date);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, date, "long_name", 23, "current date (YYYYMMDD)");
    ERR;
    varids[i++] = date;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "datesec", NC_INT, 1, dimids, &datesec);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, datesec, "long_name", 31, "current seconds of current date");
    ERR;
    varids[i++] = datesec;

    dimids[0] = dim_time;
    dimids[1] = dim_nbnd;
    err       = hdf5_def_var (ncid, "time_bnds", NC_DOUBLE, 2, dimids, &time_bnds);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time_bnds, "long_name", 23, "time interval endpoints");
    ERR;
    varids[i++] = time_bnds;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = hdf5_def_var (ncid, "date_written", NC_CHAR, 2, dimids, &date_written);
    ERR;
    varids[i++] = date_written;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = hdf5_def_var (ncid, "time_written", NC_CHAR, 2, dimids, &time_written);
    ERR;
    varids[i++] = time_written;

    err = hdf5_def_var (ncid, "ndbase", NC_INT, 0, NULL, &ndbase);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ndbase, "long_name", 8, "base day");
    ERR;
    varids[i++] = ndbase;
    err         = hdf5_def_var (ncid, "nsbase", NC_INT, 0, NULL, &nsbase);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nsbase, "long_name", 19, "seconds of base day");
    ERR;
    varids[i++] = nsbase;

    err = hdf5_def_var (ncid, "nbdate", NC_INT, 0, NULL, &nbdate);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nbdate, "long_name", 20, "base date (YYYYMMDD)");
    ERR;
    varids[i++] = nbdate;

    err = hdf5_def_var (ncid, "nbsec", NC_INT, 0, NULL, &nbsec);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nbsec, "long_name", 20, "seconds of base date");
    ERR;
    varids[i++] = nbsec;

    err = hdf5_def_var (ncid, "mdt", NC_INT, 0, NULL, &mdt);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mdt, "long_name", 8, "timestep");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mdt, "units", 1, "s");
    ERR;
    varids[i++] = mdt;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "ndcur", NC_INT, 1, dimids, &ndcur);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ndcur, "long_name", 27, "current day (from base day)");
    ERR;
    varids[i++] = ndcur;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "nscur", NC_INT, 1, dimids, &nscur);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nscur, "long_name", 30, "current seconds of current day");
    ERR;
    varids[i++] = nscur;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "co2vmr", NC_DOUBLE, 1, dimids, &co2vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, co2vmr, "long_name", 23, "co2 volume mixing ratio");
    ERR;
    varids[i++] = co2vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "ch4vmr", NC_DOUBLE, 1, dimids, &ch4vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ch4vmr, "long_name", 23, "ch4 volume mixing ratio");
    ERR;
    varids[i++] = ch4vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "n2ovmr", NC_DOUBLE, 1, dimids, &n2ovmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, n2ovmr, "long_name", 23, "n2o volume mixing ratio");
    ERR;
    varids[i++] = n2ovmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "f11vmr", NC_DOUBLE, 1, dimids, &f11vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, f11vmr, "long_name", 23, "f11 volume mixing ratio");
    ERR;
    varids[i++] = f11vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "f12vmr", NC_DOUBLE, 1, dimids, &f12vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, f12vmr, "long_name", 23, "f12 volume mixing ratio");
    ERR;
    varids[i++] = f12vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "sol_tsi", NC_DOUBLE, 1, dimids, &sol_tsi);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, sol_tsi, "long_name", 22, "total solar irradiance");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, sol_tsi, "units", 4, "W/m2");
    ERR;
    varids[i++] = sol_tsi;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "nsteph", NC_INT, 1, dimids, &nsteph);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nsteph, "long_name", 16, "current timestep");
    ERR;
    varids[i++] = nsteph;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AEROD_v", NC_FLOAT, 2, dimids, &AEROD_v);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AEROD_v, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AEROD_v, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AEROD_v, "units", 1, "1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AEROD_v, "long_name", 43,
                             "Total Aerosol Optical Depth in visible band");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AEROD_v, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AEROD_v;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "ANRAIN", NC_FLOAT, 3, dimids, &ANRAIN);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, ANRAIN, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ANRAIN, "units", 3, "m-3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ANRAIN, "long_name", 24, "Average rain number conc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ANRAIN, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ANRAIN;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "ANSNOW", NC_FLOAT, 3, dimids, &ANSNOW);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, ANSNOW, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ANSNOW, "units", 3, "m-3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ANSNOW, "long_name", 24, "Average snow number conc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ANSNOW, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ANSNOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODABS", NC_FLOAT, 2, dimids, &AODABS);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODABS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODABS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODABS, "long_name", 39,
                             "Aerosol absorption optical depth 550 nm");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODABS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODABS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODABSBC", NC_FLOAT, 2, dimids, &AODABSBC);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODABSBC, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODABSBC, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODABSBC, "long_name", 47,
                             "Aerosol absorption optical depth 550 nm from BC");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODABSBC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODABSBC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODBC", NC_FLOAT, 2, dimids, &AODBC);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODBC, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODBC, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODBC, "long_name", 36, "Aerosol optical depth 550 nm from BC");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODBC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODBC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODDUST", NC_FLOAT, 2, dimids, &AODDUST);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST, "long_name", 38,
                             "Aerosol optical depth 550 nm from dust");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODDUST1", NC_FLOAT, 2, dimids, &AODDUST1);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST1, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST1, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST1, "long_name", 46,
                             "Aerosol optical depth 550 nm model 1 from dust");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODDUST3", NC_FLOAT, 2, dimids, &AODDUST3);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST3, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST3, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST3, "long_name", 46,
                             "Aerosol optical depth 550 nm model 3 from dust");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODDUST4", NC_FLOAT, 2, dimids, &AODDUST4);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST4, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODDUST4, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST4, "long_name", 46,
                             "Aerosol optical depth 550 nm model 4 from dust");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODDUST4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODMODE1", NC_FLOAT, 2, dimids, &AODMODE1);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE1, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE1, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AODMODE1, "long_name", 35, "Aerosol optical depth 550 nm mode 1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODMODE1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODMODE2", NC_FLOAT, 2, dimids, &AODMODE2);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE2, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE2, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AODMODE2, "long_name", 35, "Aerosol optical depth 550 nm mode 2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODMODE2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODMODE3", NC_FLOAT, 2, dimids, &AODMODE3);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE3, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE3, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AODMODE3, "long_name", 35, "Aerosol optical depth 550 nm mode 3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODMODE3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODMODE4", NC_FLOAT, 2, dimids, &AODMODE4);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE4, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODMODE4, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AODMODE4, "long_name", 35, "Aerosol optical depth 550 nm mode 4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODMODE4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODNIR", NC_FLOAT, 2, dimids, &AODNIR);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODNIR, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODNIR, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODNIR, "long_name", 28, "Aerosol optical depth 850 nm");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODNIR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODNIR;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODPOM", NC_FLOAT, 2, dimids, &AODPOM);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODPOM, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODPOM, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AODPOM, "long_name", 37, "Aerosol optical depth 550 nm from POM");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODPOM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODPOM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODSO4", NC_FLOAT, 2, dimids, &AODSO4);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODSO4, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODSO4, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AODSO4, "long_name", 37, "Aerosol optical depth 550 nm from SO4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODSO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODSO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODSOA", NC_FLOAT, 2, dimids, &AODSOA);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODSOA, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODSOA, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AODSOA, "long_name", 37, "Aerosol optical depth 550 nm from SOA");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODSOA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODSOA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODSS", NC_FLOAT, 2, dimids, &AODSS);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODSS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODSS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODSS, "long_name", 41,
                             "Aerosol optical depth 550 nm from seasalt");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODSS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODSS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODUV", NC_FLOAT, 2, dimids, &AODUV);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODUV, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODUV, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODUV, "long_name", 28, "Aerosol optical depth 350 nm");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODUV, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODUV;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AODVIS", NC_FLOAT, 2, dimids, &AODVIS);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODVIS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, AODVIS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODVIS, "long_name", 28, "Aerosol optical depth 550 nm");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AODVIS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODVIS;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQRAIN", NC_FLOAT, 3, dimids, &AQRAIN);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, AQRAIN, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQRAIN, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQRAIN, "long_name", 25, "Average rain mixing ratio");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQRAIN, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQRAIN;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQSNOW", NC_FLOAT, 3, dimids, &AQSNOW);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, AQSNOW, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQSNOW, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQSNOW, "long_name", 25, "Average snow mixing ratio");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQSNOW, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQSNOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQ_DMS", NC_FLOAT, 2, dimids, &AQ_DMS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_DMS, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_DMS, "long_name", 39,
                             "DMS aqueous chemistry (for gas species)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_DMS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_DMS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQ_H2O2", NC_FLOAT, 2, dimids, &AQ_H2O2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_H2O2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_H2O2, "long_name", 40,
                             "H2O2 aqueous chemistry (for gas species)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_H2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_H2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQ_H2SO4", NC_FLOAT, 2, dimids, &AQ_H2SO4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_H2SO4, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_H2SO4, "long_name", 41,
                             "H2SO4 aqueous chemistry (for gas species)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_H2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_H2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQ_O3", NC_FLOAT, 2, dimids, &AQ_O3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_O3, "units", 7, "kg/m2/s");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, AQ_O3, "long_name", 38, "O3 aqueous chemistry (for gas species)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_O3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_O3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQ_SO2", NC_FLOAT, 2, dimids, &AQ_SO2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_SO2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_SO2, "long_name", 39,
                             "SO2 aqueous chemistry (for gas species)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "AQ_SOAG", NC_FLOAT, 2, dimids, &AQ_SOAG);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_SOAG, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_SOAG, "long_name", 40,
                             "SOAG aqueous chemistry (for gas species)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AQ_SOAG, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_SOAG;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "AREI", NC_FLOAT, 3, dimids, &AREI);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, AREI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AREI, "units", 6, "Micron");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AREI, "long_name", 28, "Average ice effective radius");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AREI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AREI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "AREL", NC_FLOAT, 3, dimids, &AREL);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, AREL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AREL, "units", 6, "Micron");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AREL, "long_name", 32, "Average droplet effective radius");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AREL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AREL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "AWNC", NC_FLOAT, 3, dimids, &AWNC);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, AWNC, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AWNC, "units", 3, "m-3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AWNC, "long_name", 31, "Average cloud water number conc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AWNC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AWNC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "AWNI", NC_FLOAT, 3, dimids, &AWNI);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, AWNI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AWNI, "units", 3, "m-3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AWNI, "long_name", 29, "Average cloud ice number conc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, AWNI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AWNI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "CCN3", NC_FLOAT, 3, dimids, &CCN3);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, CCN3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CCN3, "units", 5, "#/cm3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CCN3, "long_name", 27, "CCN concentration at S=0.1%");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CCN3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CCN3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CDNUMC", NC_FLOAT, 2, dimids, &CDNUMC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CDNUMC, "units", 4, "1/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CDNUMC, "long_name", 43,
                             "Vertically-integrated droplet concentration");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CDNUMC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CDNUMC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDHGH", NC_FLOAT, 2, dimids, &CLDHGH);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDHGH, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDHGH, "long_name", 32, "Vertically-integrated high cloud");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDHGH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDHGH;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDICE", NC_FLOAT, 3, dimids, &CLDICE);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, CLDICE, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDICE, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDICE, "long_name", 34, "Grid box averaged cloud ice amount");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDICE;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDLIQ", NC_FLOAT, 3, dimids, &CLDLIQ);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, CLDLIQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDLIQ, "units", 5, "kg/kg");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, CLDLIQ, "long_name", 37, "Grid box averaged cloud liquid amount");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDLIQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDLIQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDLOW", NC_FLOAT, 2, dimids, &CLDLOW);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDLOW, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDLOW, "long_name", 31, "Vertically-integrated low cloud");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDLOW, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDLOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDMED", NC_FLOAT, 2, dimids, &CLDMED);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDMED, "units", 8, "fraction");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, CLDMED, "long_name", 37, "Vertically-integrated mid-level cloud");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDMED, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDMED;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDTOT", NC_FLOAT, 2, dimids, &CLDTOT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDTOT, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDTOT, "long_name", 33, "Vertically-integrated total cloud");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDTOT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDTOT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLOUD", NC_FLOAT, 3, dimids, &CLOUD);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, CLOUD, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLOUD, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLOUD, "long_name", 14, "Cloud fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLOUD, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLOUD;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLOUDFRAC_CLUBB", NC_FLOAT, 3, dimids, &CLOUDFRAC_CLUBB);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, CLOUDFRAC_CLUBB, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLOUDFRAC_CLUBB, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLOUDFRAC_CLUBB, "long_name", 14, "Cloud Fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLOUDFRAC_CLUBB, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLOUDFRAC_CLUBB;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "CONCLD", NC_FLOAT, 3, dimids, &CONCLD);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, CONCLD, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CONCLD, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CONCLD, "long_name", 22, "Convective cloud cover");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CONCLD, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CONCLD;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "DCQ", NC_FLOAT, 3, dimids, &DCQ);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, DCQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DCQ, "units", 7, "kg/kg/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DCQ, "long_name", 33, "Q tendency due to moist processes");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DCQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DCQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DF_DMS", NC_FLOAT, 2, dimids, &DF_DMS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_DMS, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_DMS, "long_name", 19, "dry deposition flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_DMS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_DMS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DF_H2O2", NC_FLOAT, 2, dimids, &DF_H2O2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_H2O2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_H2O2, "long_name", 19, "dry deposition flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_H2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_H2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DF_H2SO4", NC_FLOAT, 2, dimids, &DF_H2SO4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_H2SO4, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_H2SO4, "long_name", 19, "dry deposition flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_H2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_H2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DF_O3", NC_FLOAT, 2, dimids, &DF_O3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_O3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_O3, "long_name", 19, "dry deposition flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_O3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_O3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DF_SO2", NC_FLOAT, 2, dimids, &DF_SO2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_SO2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_SO2, "long_name", 19, "dry deposition flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DF_SOAG", NC_FLOAT, 2, dimids, &DF_SOAG);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_SOAG, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_SOAG, "long_name", 19, "dry deposition flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DF_SOAG, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_SOAG;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DMS_SRF", NC_FLOAT, 2, dimids, &DMS_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DMS_SRF, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DMS_SRF, "long_name", 19, "DMS in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DMS_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DMS_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DP_KCLDBASE", NC_FLOAT, 2, dimids, &DP_KCLDBASE);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_KCLDBASE, "units", 1, "1");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, DP_KCLDBASE, "long_name", 32, "Deep conv. cloudbase level index");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_KCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DP_KCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DP_MFUP_MAX", NC_FLOAT, 2, dimids, &DP_MFUP_MAX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_MFUP_MAX, "units", 5, "kg/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_MFUP_MAX, "long_name", 39,
                             "Deep conv. column-max updraft mass flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_MFUP_MAX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DP_MFUP_MAX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DP_WCLDBASE", NC_FLOAT, 2, dimids, &DP_WCLDBASE);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_WCLDBASE, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_WCLDBASE, "long_name", 38,
                             "Deep conv. cloudbase vertical velocity");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DP_WCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DP_WCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DSTSFMBL", NC_FLOAT, 2, dimids, &DSTSFMBL);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DSTSFMBL, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DSTSFMBL, "long_name", 28, "Mobilization flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DSTSFMBL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DSTSFMBL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "DTCOND", NC_FLOAT, 3, dimids, &DTCOND);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, DTCOND, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTCOND, "units", 3, "K/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTCOND, "long_name", 28, "T tendency - moist processes");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTCOND, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DTCOND;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DTENDTH", NC_FLOAT, 2, dimids, &DTENDTH);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTENDTH, "units", 4, "W/m2");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, DTENDTH, "long_name", 69,
                           "Dynamic Tendency of Total (vertically integrated) moist static energy");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTENDTH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DTENDTH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "DTENDTQ", NC_FLOAT, 2, dimids, &DTENDTQ);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTENDTQ, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTENDTQ, "long_name", 67,
                             "Dynamic Tendency of Total (vertically integrated) specific humidity");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, DTENDTQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DTENDTQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "EXTINCT", NC_FLOAT, 3, dimids, &EXTINCT);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, EXTINCT, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, EXTINCT, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, EXTINCT, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, EXTINCT, "units", 2, "/m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, EXTINCT, "long_name", 18, "Aerosol extinction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, EXTINCT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = EXTINCT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "FICE", NC_FLOAT, 3, dimids, &FICE);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, FICE, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FICE, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FICE, "long_name", 35, "Fractional ice content within cloud");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FICE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLDS", NC_FLOAT, 2, dimids, &FLDS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLDS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLDS, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLDS, "long_name", 36, "Downwelling longwave flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLDS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLDS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLNS", NC_FLOAT, 2, dimids, &FLNS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNS, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNS, "long_name", 28, "Net longwave flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLNSC", NC_FLOAT, 2, dimids, &FLNSC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNSC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNSC, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNSC, "long_name", 37, "Clearsky net longwave flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLNT", NC_FLOAT, 2, dimids, &FLNT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNT, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNT, "long_name", 33, "Net longwave flux at top of model");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLNTC", NC_FLOAT, 2, dimids, &FLNTC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNTC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNTC, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNTC, "long_name", 42,
                             "Clearsky net longwave flux at top of model");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNTC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNTC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLUT", NC_FLOAT, 2, dimids, &FLUT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLUT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLUT, "units", 4, "W/m2");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, FLUT, "long_name", 39, "Upwelling longwave flux at top of model");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLUT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLUT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLUTC", NC_FLOAT, 2, dimids, &FLUTC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLUTC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLUTC, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLUTC, "long_name", 48,
                             "Clearsky upwelling longwave flux at top of model");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLUTC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLUTC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "FREQI", NC_FLOAT, 3, dimids, &FREQI);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, FREQI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQI, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQI, "long_name", 28, "Fractional occurrence of ice");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "FREQL", NC_FLOAT, 3, dimids, &FREQL);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, FREQL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQL, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQL, "long_name", 31, "Fractional occurrence of liquid");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "FREQR", NC_FLOAT, 3, dimids, &FREQR);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, FREQR, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQR, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQR, "long_name", 29, "Fractional occurrence of rain");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQR;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "FREQS", NC_FLOAT, 3, dimids, &FREQS);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, FREQS, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQS, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQS, "long_name", 29, "Fractional occurrence of snow");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FREQS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSDS", NC_FLOAT, 2, dimids, &FSDS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDS, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDS, "long_name", 33, "Downwelling solar flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSDS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSDSC", NC_FLOAT, 2, dimids, &FSDSC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDSC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDSC, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDSC, "long_name", 42,
                             "Clearsky downwelling solar flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSDSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSDSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSNS", NC_FLOAT, 2, dimids, &FSNS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNS, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNS, "long_name", 25, "Net solar flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSNSC", NC_FLOAT, 2, dimids, &FSNSC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNSC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNSC, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNSC, "long_name", 34, "Clearsky net solar flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSNT", NC_FLOAT, 2, dimids, &FSNT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNT, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNT, "long_name", 30, "Net solar flux at top of model");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSNTC", NC_FLOAT, 2, dimids, &FSNTC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTC, "units", 4, "W/m2");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, FSNTC, "long_name", 39, "Clearsky net solar flux at top of model");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNTC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSNTOA", NC_FLOAT, 2, dimids, &FSNTOA);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOA, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOA, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOA, "long_name", 35, "Net solar flux at top of atmosphere");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNTOA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSNTOAC", NC_FLOAT, 2, dimids, &FSNTOAC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOAC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOAC, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOAC, "long_name", 44,
                             "Clearsky net solar flux at top of atmosphere");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSNTOAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNTOAC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSUTOA", NC_FLOAT, 2, dimids, &FSUTOA);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOA, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOA, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOA, "long_name", 41,
                             "Upwelling solar flux at top of atmosphere");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSUTOA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FSUTOAC", NC_FLOAT, 2, dimids, &FSUTOAC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOAC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOAC, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOAC, "long_name", 50,
                             "Clearsky upwelling solar flux at top of atmosphere");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FSUTOAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSUTOAC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "F_eff", NC_FLOAT, 2, dimids, &F_eff);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, F_eff, "units", 1, "1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, F_eff, "long_name", 52,
                             "Effective enrichment factor of marine organic matter");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, F_eff, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = F_eff;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "H2O2_SRF", NC_FLOAT, 2, dimids, &H2O2_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2O2_SRF, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2O2_SRF, "long_name", 20, "H2O2 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2O2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = H2O2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "H2SO4_SRF", NC_FLOAT, 2, dimids, &H2SO4_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2SO4_SRF, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2SO4_SRF, "long_name", 21, "H2SO4 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2SO4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = H2SO4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "H2SO4_sfgaex1", NC_FLOAT, 2, dimids, &H2SO4_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2SO4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2SO4_sfgaex1, "long_name", 50,
                             "H2SO4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, H2SO4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = H2SO4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ICEFRAC", NC_FLOAT, 2, dimids, &ICEFRAC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICEFRAC, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICEFRAC, "long_name", 39,
                             "Fraction of sfc area covered by sea-ice");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICEFRAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ICEFRAC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "ICIMR", NC_FLOAT, 3, dimids, &ICIMR);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, ICIMR, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICIMR, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICIMR, "long_name", 36, "Prognostic in-cloud ice mixing ratio");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICIMR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ICIMR;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "ICWMR", NC_FLOAT, 3, dimids, &ICWMR);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, ICWMR, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICWMR, "units", 5, "kg/kg");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, ICWMR, "long_name", 38, "Prognostic in-cloud water mixing ratio");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ICWMR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ICWMR;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "IWC", NC_FLOAT, 3, dimids, &IWC);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, IWC, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, IWC, "units", 5, "kg/m3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, IWC, "long_name", 34, "Grid box average ice water content");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, IWC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = IWC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "LANDFRAC", NC_FLOAT, 2, dimids, &LANDFRAC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LANDFRAC, "units", 8, "fraction");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, LANDFRAC, "long_name", 36, "Fraction of sfc area covered by land");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LANDFRAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LANDFRAC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "LHFLX", NC_FLOAT, 2, dimids, &LHFLX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LHFLX, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LHFLX, "long_name", 24, "Surface latent heat flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LHFLX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LHFLX;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "LINOZ_DO3", NC_FLOAT, 3, dimids, &LINOZ_DO3);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, LINOZ_DO3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_DO3, "units", 2, "/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_DO3, "long_name", 48,
                             "ozone vmr tendency by linearized ozone chemistry");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_DO3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_DO3;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "LINOZ_DO3_PSC", NC_FLOAT, 3, dimids, &LINOZ_DO3_PSC);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, LINOZ_DO3_PSC, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_DO3_PSC, "units", 2, "/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_DO3_PSC, "long_name", 50,
                             "ozone vmr loss by PSCs using Carille et al. (1990)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_DO3_PSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_DO3_PSC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "LINOZ_O3CLIM", NC_FLOAT, 3, dimids, &LINOZ_O3CLIM);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, LINOZ_O3CLIM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_O3CLIM, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_O3CLIM, "long_name", 29, "climatology of ozone in LINOZ");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_O3CLIM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_O3CLIM;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "LINOZ_O3COL", NC_FLOAT, 3, dimids, &LINOZ_O3COL);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, LINOZ_O3COL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_O3COL, "units", 2, "DU");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_O3COL, "long_name", 18, "ozone column above");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_O3COL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_O3COL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "LINOZ_SSO3", NC_FLOAT, 3, dimids, &LINOZ_SSO3);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, LINOZ_SSO3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_SSO3, "units", 2, "kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_SSO3, "long_name", 27, "steady state ozone in LINOZ");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_SSO3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_SSO3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "LINOZ_SZA", NC_FLOAT, 2, dimids, &LINOZ_SZA);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_SZA, "units", 7, "degrees");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_SZA, "long_name", 27, "solar zenith angle in LINOZ");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LINOZ_SZA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_SZA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "LND_MBL", NC_FLOAT, 2, dimids, &LND_MBL);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LND_MBL, "units", 4, "frac");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LND_MBL, "long_name", 23, "Soil erodibility factor");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LND_MBL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LND_MBL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "LWCF", NC_FLOAT, 2, dimids, &LWCF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LWCF, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LWCF, "long_name", 22, "Longwave cloud forcing");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LWCF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Mass_bc", NC_FLOAT, 3, dimids, &Mass_bc);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Mass_bc, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_bc, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_bc, "long_name", 64,
                             "sum of bc mass concentration bc_a1+bc_c1+bc_a3+bc_c3+bc_a4+bc_c4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_bc, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_bc;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Mass_dst", NC_FLOAT, 3, dimids, &Mass_dst);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Mass_dst, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_dst, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_dst, "long_name", 57,
                             "sum of dst mass concentration dst_a1+dst_c1+dst_a3+dst_c3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_dst, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_dst;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Mass_mom", NC_FLOAT, 3, dimids, &Mass_mom);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Mass_mom, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_mom, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, Mass_mom, "long_name", 85,
        "sum of mom mass concentration mom_a1+mom_c1+mom_a2+mom_c2+mom_a3+mom_c3+mom_a4+mom_c4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_mom, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_mom;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Mass_ncl", NC_FLOAT, 3, dimids, &Mass_ncl);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Mass_ncl, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_ncl, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, Mass_ncl, "long_name", 71,
        "sum of ncl mass concentration ncl_a1+ncl_c1+ncl_a2+ncl_c2+ncl_a3+ncl_c3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_ncl, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_ncl;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Mass_pom", NC_FLOAT, 3, dimids, &Mass_pom);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Mass_pom, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_pom, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, Mass_pom, "long_name", 71,
        "sum of pom mass concentration pom_a1+pom_c1+pom_a3+pom_c3+pom_a4+pom_c4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_pom, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_pom;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Mass_so4", NC_FLOAT, 3, dimids, &Mass_so4);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Mass_so4, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_so4, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, Mass_so4, "long_name", 71,
        "sum of so4 mass concentration so4_a1+so4_c1+so4_a2+so4_c2+so4_a3+so4_c3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_so4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_so4;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Mass_soa", NC_FLOAT, 3, dimids, &Mass_soa);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Mass_soa, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_soa, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, Mass_soa, "long_name", 71,
        "sum of soa mass concentration soa_a1+soa_c1+soa_a2+soa_c2+soa_a3+soa_c3");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Mass_soa, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_soa;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "NUMICE", NC_FLOAT, 3, dimids, &NUMICE);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, NUMICE, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMICE, "units", 4, "1/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMICE, "long_name", 34, "Grid box averaged cloud ice number");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMICE;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "NUMLIQ", NC_FLOAT, 3, dimids, &NUMLIQ);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, NUMLIQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMLIQ, "units", 4, "1/kg");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, NUMLIQ, "long_name", 37, "Grid box averaged cloud liquid number");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMLIQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMLIQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "NUMRAI", NC_FLOAT, 3, dimids, &NUMRAI);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, NUMRAI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMRAI, "units", 4, "1/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMRAI, "long_name", 29, "Grid box averaged rain number");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMRAI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMRAI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "NUMSNO", NC_FLOAT, 3, dimids, &NUMSNO);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, NUMSNO, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMSNO, "units", 4, "1/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMSNO, "long_name", 29, "Grid box averaged snow number");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NUMSNO, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMSNO;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "O3", NC_FLOAT, 3, dimids, &O3);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, O3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, O3, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, O3, "long_name", 16, "O3 concentration");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, O3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = O3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "O3_SRF", NC_FLOAT, 2, dimids, &O3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, O3_SRF, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, O3_SRF, "long_name", 18, "O3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, O3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = O3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "OCNFRAC", NC_FLOAT, 2, dimids, &OCNFRAC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OCNFRAC, "units", 8, "fraction");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, OCNFRAC, "long_name", 37, "Fraction of sfc area covered by ocean");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OCNFRAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OCNFRAC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "OMEGA", NC_FLOAT, 3, dimids, &OMEGA);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, OMEGA, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA, "units", 4, "Pa/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA, "long_name", 28, "Vertical velocity (pressure)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OMEGA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "OMEGA500", NC_FLOAT, 2, dimids, &OMEGA500);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA500, "units", 4, "Pa/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA500, "long_name", 46,
                             "Vertical velocity at 500 mbar pressure surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA500, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OMEGA500;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "OMEGAT", NC_FLOAT, 3, dimids, &OMEGAT);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, OMEGAT, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGAT, "units", 6, "K Pa/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGAT, "long_name", 18, "Vertical heat flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGAT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OMEGAT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PBLH", NC_FLOAT, 2, dimids, &PBLH);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PBLH, "units", 1, "m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PBLH, "long_name", 10, "PBL height");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PBLH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PBLH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PHIS", NC_FLOAT, 2, dimids, &PHIS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PHIS, "units", 5, "m2/s2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PHIS, "long_name", 20, "Surface geopotential");
    ERR;
    varids[i++] = PHIS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PRECC", NC_FLOAT, 2, dimids, &PRECC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECC, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECC, "long_name", 41,
                             "Convective precipitation rate (liq + ice)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PRECL", NC_FLOAT, 2, dimids, &PRECL);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECL, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECL, "long_name", 51,
                             "Large-scale (stable) precipitation rate (liq + ice)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PRECSC", NC_FLOAT, 2, dimids, &PRECSC);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECSC, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECSC, "long_name", 39,
                             "Convective snow rate (water equivalent)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PRECSL", NC_FLOAT, 2, dimids, &PRECSL);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECSL, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECSL, "long_name", 49,
                             "Large-scale (stable) snow rate (water equivalent)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECSL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECSL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PS", NC_FLOAT, 2, dimids, &PS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PS, "units", 2, "Pa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PS, "long_name", 16, "Surface pressure");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PSL", NC_FLOAT, 2, dimids, &PSL);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PSL, "units", 2, "Pa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PSL, "long_name", 18, "Sea level pressure");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PSL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PSL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Q", NC_FLOAT, 3, dimids, &Q);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Q, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Q, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Q, "long_name", 17, "Specific humidity");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Q, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Q;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "QFLX", NC_FLOAT, 2, dimids, &QFLX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QFLX, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QFLX, "long_name", 18, "Surface water flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QFLX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QFLX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "QREFHT", NC_FLOAT, 2, dimids, &QREFHT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QREFHT, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QREFHT, "long_name", 25, "Reference height humidity");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QREFHT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QREFHT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "QRL", NC_FLOAT, 3, dimids, &QRL);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, QRL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRL, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRL, "units", 3, "K/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRL, "long_name", 21, "Longwave heating rate");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QRL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "QRS", NC_FLOAT, 3, dimids, &QRS);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, QRS, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRS, "units", 3, "K/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRS, "long_name", 18, "Solar heating rate");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, QRS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QRS;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "RAINQM", NC_FLOAT, 3, dimids, &RAINQM);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, RAINQM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RAINQM, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RAINQM, "long_name", 29, "Grid box averaged rain amount");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RAINQM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = RAINQM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "RAM1", NC_FLOAT, 2, dimids, &RAM1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RAM1, "units", 4, "frac");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RAM1, "long_name", 4, "RAM1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RAM1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = RAM1;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "RELHUM", NC_FLOAT, 3, dimids, &RELHUM);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, RELHUM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RELHUM, "units", 7, "percent");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RELHUM, "long_name", 17, "Relative humidity");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, RELHUM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = RELHUM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFDMS", NC_FLOAT, 2, dimids, &SFDMS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFDMS, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFDMS, "long_name", 16, "DMS surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFDMS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFDMS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFH2O2", NC_FLOAT, 2, dimids, &SFH2O2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFH2O2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFH2O2, "long_name", 17, "H2O2 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFH2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFH2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFH2SO4", NC_FLOAT, 2, dimids, &SFH2SO4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFH2SO4, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFH2SO4, "long_name", 18, "H2SO4 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFH2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFH2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFO3", NC_FLOAT, 2, dimids, &SFO3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFO3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFO3, "long_name", 15, "O3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFO3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFO3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFSO2", NC_FLOAT, 2, dimids, &SFSO2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFSO2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFSO2, "long_name", 16, "SO2 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFSO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFSO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFSOAG", NC_FLOAT, 2, dimids, &SFSOAG);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFSOAG, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFSOAG, "long_name", 17, "SOAG surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFSOAG, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFSOAG;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFbc_a1", NC_FLOAT, 2, dimids, &SFbc_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a1, "long_name", 18, "bc_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFbc_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFbc_a3", NC_FLOAT, 2, dimids, &SFbc_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a3, "long_name", 18, "bc_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFbc_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFbc_a4", NC_FLOAT, 2, dimids, &SFbc_a4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a4, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a4, "long_name", 18, "bc_a4 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFbc_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFbc_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFdst_a1", NC_FLOAT, 2, dimids, &SFdst_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFdst_a1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFdst_a1, "long_name", 19, "dst_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFdst_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFdst_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFdst_a3", NC_FLOAT, 2, dimids, &SFdst_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFdst_a3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFdst_a3, "long_name", 19, "dst_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFdst_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFdst_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFmom_a1", NC_FLOAT, 2, dimids, &SFmom_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a1, "long_name", 19, "mom_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFmom_a2", NC_FLOAT, 2, dimids, &SFmom_a2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a2, "long_name", 19, "mom_a2 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFmom_a3", NC_FLOAT, 2, dimids, &SFmom_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a3, "long_name", 19, "mom_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFmom_a4", NC_FLOAT, 2, dimids, &SFmom_a4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a4, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a4, "long_name", 19, "mom_a4 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFmom_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFncl_a1", NC_FLOAT, 2, dimids, &SFncl_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a1, "long_name", 19, "ncl_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFncl_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFncl_a2", NC_FLOAT, 2, dimids, &SFncl_a2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a2, "long_name", 19, "ncl_a2 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFncl_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFncl_a3", NC_FLOAT, 2, dimids, &SFncl_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a3, "long_name", 19, "ncl_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFncl_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFncl_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFnum_a1", NC_FLOAT, 2, dimids, &SFnum_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a1, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a1, "long_name", 19, "num_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFnum_a2", NC_FLOAT, 2, dimids, &SFnum_a2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a2, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a2, "long_name", 19, "num_a2 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFnum_a3", NC_FLOAT, 2, dimids, &SFnum_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a3, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a3, "long_name", 19, "num_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFnum_a4", NC_FLOAT, 2, dimids, &SFnum_a4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a4, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a4, "long_name", 19, "num_a4 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFnum_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFpom_a1", NC_FLOAT, 2, dimids, &SFpom_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a1, "long_name", 19, "pom_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFpom_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFpom_a3", NC_FLOAT, 2, dimids, &SFpom_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a3, "long_name", 19, "pom_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFpom_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFpom_a4", NC_FLOAT, 2, dimids, &SFpom_a4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a4, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a4, "long_name", 19, "pom_a4 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFpom_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFpom_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFso4_a1", NC_FLOAT, 2, dimids, &SFso4_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a1, "long_name", 19, "so4_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFso4_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFso4_a2", NC_FLOAT, 2, dimids, &SFso4_a2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a2, "long_name", 19, "so4_a2 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFso4_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFso4_a3", NC_FLOAT, 2, dimids, &SFso4_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a3, "long_name", 19, "so4_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFso4_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFso4_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFsoa_a1", NC_FLOAT, 2, dimids, &SFsoa_a1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a1, "long_name", 19, "soa_a1 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFsoa_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFsoa_a2", NC_FLOAT, 2, dimids, &SFsoa_a2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a2, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a2, "long_name", 19, "soa_a2 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFsoa_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SFsoa_a3", NC_FLOAT, 2, dimids, &SFsoa_a3);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a3, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a3, "long_name", 19, "soa_a3 surface flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SFsoa_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFsoa_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SHFLX", NC_FLOAT, 2, dimids, &SHFLX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SHFLX, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SHFLX, "long_name", 26, "Surface sensible heat flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SHFLX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SHFLX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SH_KCLDBASE", NC_FLOAT, 2, dimids, &SH_KCLDBASE);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_KCLDBASE, "units", 1, "1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_KCLDBASE, "long_name", 35,
                             "Shallow conv. cloudbase level index");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_KCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SH_KCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SH_MFUP_MAX", NC_FLOAT, 2, dimids, &SH_MFUP_MAX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_MFUP_MAX, "units", 5, "kg/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_MFUP_MAX, "long_name", 42,
                             "Shallow conv. column-max updraft mass flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_MFUP_MAX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SH_MFUP_MAX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SH_WCLDBASE", NC_FLOAT, 2, dimids, &SH_WCLDBASE);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_WCLDBASE, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_WCLDBASE, "long_name", 41,
                             "Shallow conv. cloudbase vertical velocity");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SH_WCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SH_WCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SNOWHICE", NC_FLOAT, 2, dimids, &SNOWHICE);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWHICE, "units", 1, "m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWHICE, "long_name", 19, "Snow depth over ice");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWHICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SNOWHICE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SNOWHLND", NC_FLOAT, 2, dimids, &SNOWHLND);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWHLND, "units", 1, "m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWHLND, "long_name", 27, "Water equivalent snow depth");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWHLND, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SNOWHLND;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "SNOWQM", NC_FLOAT, 3, dimids, &SNOWQM);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, SNOWQM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWQM, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWQM, "long_name", 29, "Grid box averaged snow amount");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SNOWQM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SNOWQM;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "SO2", NC_FLOAT, 3, dimids, &SO2);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, SO2, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2, "long_name", 17, "SO2 concentration");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SO2_CLXF", NC_FLOAT, 2, dimids, &SO2_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2_CLXF, "long_name", 47,
                             "vertically intergrated external forcing for SO2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SO2_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SO2_SRF", NC_FLOAT, 2, dimids, &SO2_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2_SRF, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2_SRF, "long_name", 19, "SO2 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SO2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SO2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SOAG_CLXF", NC_FLOAT, 2, dimids, &SOAG_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_CLXF, "long_name", 48,
                             "vertically intergrated external forcing for SOAG");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOAG_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SOAG_SRF", NC_FLOAT, 2, dimids, &SOAG_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_SRF, "units", 7, "mol/mol");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_SRF, "long_name", 20, "SOAG in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOAG_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SOAG_sfgaex1", NC_FLOAT, 2, dimids, &SOAG_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_sfgaex1, "long_name", 49,
                             "SOAG gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOAG_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOAG_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SOLIN", NC_FLOAT, 2, dimids, &SOLIN);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOLIN, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOLIN, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOLIN, "long_name", 16, "Solar insolation");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SOLIN, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOLIN;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SSAVIS", NC_FLOAT, 2, dimids, &SSAVIS);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, SSAVIS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, SSAVIS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSAVIS, "long_name", 29, "Aerosol singel-scatter albedo");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSAVIS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SSAVIS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SSTSFMBL", NC_FLOAT, 2, dimids, &SSTSFMBL);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSTSFMBL, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSTSFMBL, "long_name", 28, "Mobilization flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSTSFMBL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SSTSFMBL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SSTSFMBL_OM", NC_FLOAT, 2, dimids, &SSTSFMBL_OM);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSTSFMBL_OM, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSTSFMBL_OM, "long_name", 53,
                             "Mobilization flux of marine organic matter at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SSTSFMBL_OM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SSTSFMBL_OM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SWCF", NC_FLOAT, 2, dimids, &SWCF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SWCF, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SWCF, "long_name", 23, "Shortwave cloud forcing");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SWCF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "T", NC_FLOAT, 3, dimids, &T);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, T, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, T, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, T, "long_name", 11, "Temperature");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, T, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = T;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TAUGWX", NC_FLOAT, 2, dimids, &TAUGWX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUGWX, "units", 4, "N/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUGWX, "long_name", 33, "Zonal gravity wave surface stress");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUGWX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUGWX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TAUGWY", NC_FLOAT, 2, dimids, &TAUGWY);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUGWY, "units", 4, "N/m2");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, TAUGWY, "long_name", 38, "Meridional gravity wave surface stress");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUGWY, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUGWY;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TAUX", NC_FLOAT, 2, dimids, &TAUX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUX, "units", 4, "N/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUX, "long_name", 20, "Zonal surface stress");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TAUY", NC_FLOAT, 2, dimids, &TAUY);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUY, "units", 4, "N/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUY, "long_name", 25, "Meridional surface stress");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TAUY, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUY;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TGCLDCWP", NC_FLOAT, 2, dimids, &TGCLDCWP);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDCWP, "units", 5, "kg/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDCWP, "long_name", 48,
                             "Total grid-box cloud water path (liquid and ice)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDCWP, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TGCLDCWP;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TGCLDIWP", NC_FLOAT, 2, dimids, &TGCLDIWP);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDIWP, "units", 5, "kg/m2");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, TGCLDIWP, "long_name", 35, "Total grid-box cloud ice water path");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDIWP, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TGCLDIWP;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TGCLDLWP", NC_FLOAT, 2, dimids, &TGCLDLWP);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDLWP, "units", 5, "kg/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDLWP, "long_name", 38,
                             "Total grid-box cloud liquid water path");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TGCLDLWP, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TGCLDLWP;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TH7001000", NC_FLOAT, 2, dimids, &TH7001000);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TH7001000, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TH7001000, "long_name", 33, "Theta difference 700 mb - 1000 mb");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TH7001000, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TH7001000;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TMQ", NC_FLOAT, 2, dimids, &TMQ);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TMQ, "units", 5, "kg/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TMQ, "long_name", 48,
                             "Total (vertically integrated) precipitable water");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TMQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TMQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TREFHT", NC_FLOAT, 2, dimids, &TREFHT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TREFHT, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TREFHT, "long_name", 28, "Reference height temperature");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TREFHT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TREFHT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TROP_P", NC_FLOAT, 2, dimids, &TROP_P);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, TROP_P, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, TROP_P, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TROP_P, "units", 2, "Pa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TROP_P, "long_name", 19, "Tropopause Pressure");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TROP_P, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TROP_P;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TROP_T", NC_FLOAT, 2, dimids, &TROP_T);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, TROP_T, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = HDF5_PUT_ATT_FLOAT (ncid, TROP_T, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TROP_T, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TROP_T, "long_name", 22, "Tropopause Temperature");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TROP_T, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TROP_T;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TS", NC_FLOAT, 2, dimids, &TS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TS, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TS, "long_name", 31, "Surface temperature (radiative)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TSMN", NC_FLOAT, 2, dimids, &TSMN);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TSMN, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TSMN, "long_name", 46,
                             "Minimum surface temperature over output period");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TSMN, "cell_methods", 13, "time: minimum");
    ERR;
    varids[i++] = TSMN;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TSMX", NC_FLOAT, 2, dimids, &TSMX);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TSMX, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TSMX, "long_name", 46,
                             "Maximum surface temperature over output period");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TSMX, "cell_methods", 13, "time: maximum");
    ERR;
    varids[i++] = TSMX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TUH", NC_FLOAT, 2, dimids, &TUH);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TUH, "units", 3, "W/m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TUH, "long_name", 44,
                             "Total (vertically integrated) zonal MSE flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TUH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TUH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TUQ", NC_FLOAT, 2, dimids, &TUQ);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TUQ, "units", 6, "kg/m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TUQ, "long_name", 46,
                             "Total (vertically integrated) zonal water flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TUQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TUQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TVH", NC_FLOAT, 2, dimids, &TVH);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TVH, "units", 3, "W/m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TVH, "long_name", 49,
                             "Total (vertically integrated) meridional MSE flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TVH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TVH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TVQ", NC_FLOAT, 2, dimids, &TVQ);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TVQ, "units", 6, "kg/m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TVQ, "long_name", 51,
                             "Total (vertically integrated) meridional water flux");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TVQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TVQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "U", NC_FLOAT, 3, dimids, &U);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, U, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U, "long_name", 10, "Zonal wind");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = U;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "U10", NC_FLOAT, 2, dimids, &U10);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U10, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U10, "long_name", 14, "10m wind speed");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U10, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = U10;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "UU", NC_FLOAT, 3, dimids, &UU);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, UU, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, UU, "units", 5, "m2/s2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, UU, "long_name", 22, "Zonal velocity squared");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, UU, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = UU;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "V", NC_FLOAT, 3, dimids, &V);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, V, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, V, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, V, "long_name", 15, "Meridional wind");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, V, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = V;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "VQ", NC_FLOAT, 3, dimids, &VQ);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, VQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VQ, "units", 8, "m/skg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VQ, "long_name", 26, "Meridional water transport");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "VT", NC_FLOAT, 3, dimids, &VT);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, VT, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VT, "units", 5, "K m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VT, "long_name", 25, "Meridional heat transport");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "VU", NC_FLOAT, 3, dimids, &VU);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, VU, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VU, "units", 5, "m2/s2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VU, "long_name", 33, "Meridional flux of zonal momentum");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VU, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VU;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "VV", NC_FLOAT, 3, dimids, &VV);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, VV, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VV, "units", 5, "m2/s2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VV, "long_name", 27, "Meridional velocity squared");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VV, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VV;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "WD_H2O2", NC_FLOAT, 2, dimids, &WD_H2O2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_H2O2, "units", 4, "kg/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_H2O2, "long_name", 31, "H2O2             wet deposition");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_H2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WD_H2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "WD_H2SO4", NC_FLOAT, 2, dimids, &WD_H2SO4);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_H2SO4, "units", 4, "kg/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_H2SO4, "long_name", 31, "H2SO4            wet deposition");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_H2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WD_H2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "WD_SO2", NC_FLOAT, 2, dimids, &WD_SO2);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_SO2, "units", 4, "kg/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_SO2, "long_name", 31, "SO2              wet deposition");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WD_SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WD_SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "WSUB", NC_FLOAT, 3, dimids, &WSUB);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, WSUB, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WSUB, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WSUB, "long_name", 37, "Diagnostic sub-grid vertical velocity");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, WSUB, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WSUB;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "Z3", NC_FLOAT, 3, dimids, &Z3);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, Z3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Z3, "units", 1, "m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Z3, "long_name", 37, "Geopotential Height (above sea level)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Z3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Z3;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "aero_water", NC_FLOAT, 3, dimids, &aero_water);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, aero_water, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, aero_water, "units", 1, "m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, aero_water, "long_name", 70,
        "sum of aerosol water of interstitial modes wat_a1+wat_a2+wat_a3+wat_a4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, aero_water, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = aero_water;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "airFV", NC_FLOAT, 2, dimids, &airFV);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, airFV, "units", 4, "frac");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, airFV, "long_name", 2, "FV");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, airFV, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = airFV;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a1DDF", NC_FLOAT, 2, dimids, &bc_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1DDF, "long_name", 49,
                             "bc_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a1SFWET", NC_FLOAT, 2, dimids, &bc_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a1_SRF", NC_FLOAT, 2, dimids, &bc_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1_SRF, "long_name", 21, "bc_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a1_sfgaex1", NC_FLOAT, 2, dimids, &bc_a1_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1_sfgaex1, "long_name", 50,
                             "bc_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a3DDF", NC_FLOAT, 2, dimids, &bc_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3DDF, "long_name", 49,
                             "bc_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a3SFWET", NC_FLOAT, 2, dimids, &bc_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a3_SRF", NC_FLOAT, 2, dimids, &bc_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3_SRF, "long_name", 21, "bc_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a4DDF", NC_FLOAT, 2, dimids, &bc_a4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4DDF, "long_name", 49,
                             "bc_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a4SFWET", NC_FLOAT, 2, dimids, &bc_a4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a4_CLXF", NC_FLOAT, 2, dimids, &bc_a4_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_CLXF, "long_name", 49,
                             "vertically intergrated external forcing for bc_a4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a4_SRF", NC_FLOAT, 2, dimids, &bc_a4_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_SRF, "long_name", 21, "bc_a4 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_a4_sfgaex1", NC_FLOAT, 2, dimids, &bc_a4_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_sfgaex1, "long_name", 50,
                             "bc_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_c1DDF", NC_FLOAT, 2, dimids, &bc_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c1DDF, "long_name", 49,
                             "bc_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_c1SFWET", NC_FLOAT, 2, dimids, &bc_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c1SFWET, "long_name", 36,
                             "bc_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_c3DDF", NC_FLOAT, 2, dimids, &bc_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c3DDF, "long_name", 49,
                             "bc_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_c3SFWET", NC_FLOAT, 2, dimids, &bc_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c3SFWET, "long_name", 36,
                             "bc_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_c4DDF", NC_FLOAT, 2, dimids, &bc_c4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c4DDF, "long_name", 49,
                             "bc_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "bc_c4SFWET", NC_FLOAT, 2, dimids, &bc_c4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c4SFWET, "long_name", 36,
                             "bc_c4 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, bc_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "chla", NC_FLOAT, 2, dimids, &chla);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, chla, "units", 6, "mg L-1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, chla, "long_name", 22, "ocean input data: chla");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, chla, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = chla;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a1DDF", NC_FLOAT, 2, dimids, &dst_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1DDF, "long_name", 50,
                             "dst_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a1SF", NC_FLOAT, 2, dimids, &dst_a1SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1SF, "long_name", 28, "dst_a1 dust surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a1SFWET", NC_FLOAT, 2, dimids, &dst_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a1_SRF", NC_FLOAT, 2, dimids, &dst_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1_SRF, "long_name", 22, "dst_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a3DDF", NC_FLOAT, 2, dimids, &dst_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3DDF, "long_name", 50,
                             "dst_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a3SF", NC_FLOAT, 2, dimids, &dst_a3SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3SF, "long_name", 28, "dst_a3 dust surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a3SFWET", NC_FLOAT, 2, dimids, &dst_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_a3_SRF", NC_FLOAT, 2, dimids, &dst_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3_SRF, "long_name", 22, "dst_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_c1DDF", NC_FLOAT, 2, dimids, &dst_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c1DDF, "long_name", 50,
                             "dst_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_c1SFWET", NC_FLOAT, 2, dimids, &dst_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c1SFWET, "long_name", 37,
                             "dst_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_c3DDF", NC_FLOAT, 2, dimids, &dst_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c3DDF, "long_name", 50,
                             "dst_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "dst_c3SFWET", NC_FLOAT, 2, dimids, &dst_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c3SFWET, "long_name", 37,
                             "dst_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, dst_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "hstobie_linoz", NC_FLOAT, 3, dimids, &hstobie_linoz);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, hstobie_linoz, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, hstobie_linoz, "units", 22, "fraction of model time");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, hstobie_linoz, "long_name", 27, "Lowest possible Linoz level");
    ERR;
    varids[i++] = hstobie_linoz;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mlip", NC_FLOAT, 2, dimids, &mlip);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mlip, "units", 4, "uM C");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mlip, "long_name", 22, "ocean input data: mlip");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mlip, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mlip;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a1DDF", NC_FLOAT, 2, dimids, &mom_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1DDF, "long_name", 50,
                             "mom_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a1SF", NC_FLOAT, 2, dimids, &mom_a1SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1SF, "long_name", 31, "mom_a1 seasalt surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a1SFWET", NC_FLOAT, 2, dimids, &mom_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a1_SRF", NC_FLOAT, 2, dimids, &mom_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1_SRF, "long_name", 22, "mom_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a1_sfgaex1", NC_FLOAT, 2, dimids, &mom_a1_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1_sfgaex1, "long_name", 51,
                             "mom_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a2DDF", NC_FLOAT, 2, dimids, &mom_a2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2DDF, "long_name", 50,
                             "mom_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a2SF", NC_FLOAT, 2, dimids, &mom_a2SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2SF, "long_name", 31, "mom_a2 seasalt surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a2SFWET", NC_FLOAT, 2, dimids, &mom_a2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a2_SRF", NC_FLOAT, 2, dimids, &mom_a2_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2_SRF, "long_name", 22, "mom_a2 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a3DDF", NC_FLOAT, 2, dimids, &mom_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3DDF, "long_name", 50,
                             "mom_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a3SFWET", NC_FLOAT, 2, dimids, &mom_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a3_SRF", NC_FLOAT, 2, dimids, &mom_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3_SRF, "long_name", 22, "mom_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a4DDF", NC_FLOAT, 2, dimids, &mom_a4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4DDF, "long_name", 50,
                             "mom_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a4SF", NC_FLOAT, 2, dimids, &mom_a4SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4SF, "long_name", 31, "mom_a4 seasalt surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a4SFWET", NC_FLOAT, 2, dimids, &mom_a4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a4_SRF", NC_FLOAT, 2, dimids, &mom_a4_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4_SRF, "long_name", 22, "mom_a4 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_a4_sfgaex1", NC_FLOAT, 2, dimids, &mom_a4_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4_sfgaex1, "long_name", 51,
                             "mom_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c1DDF", NC_FLOAT, 2, dimids, &mom_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c1DDF, "long_name", 50,
                             "mom_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c1SFWET", NC_FLOAT, 2, dimids, &mom_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c1SFWET, "long_name", 37,
                             "mom_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c2DDF", NC_FLOAT, 2, dimids, &mom_c2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c2DDF, "long_name", 50,
                             "mom_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c2SFWET", NC_FLOAT, 2, dimids, &mom_c2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c2SFWET, "long_name", 37,
                             "mom_c2 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c3DDF", NC_FLOAT, 2, dimids, &mom_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c3DDF, "long_name", 50,
                             "mom_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c3SFWET", NC_FLOAT, 2, dimids, &mom_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c3SFWET, "long_name", 37,
                             "mom_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c4DDF", NC_FLOAT, 2, dimids, &mom_c4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c4DDF, "long_name", 50,
                             "mom_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mom_c4SFWET", NC_FLOAT, 2, dimids, &mom_c4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c4SFWET, "long_name", 37,
                             "mom_c4 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mom_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mpoly", NC_FLOAT, 2, dimids, &mpoly);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mpoly, "units", 4, "uM C");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mpoly, "long_name", 23, "ocean input data: mpoly");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mpoly, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mpoly;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "mprot", NC_FLOAT, 2, dimids, &mprot);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mprot, "units", 4, "uM C");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mprot, "long_name", 23, "ocean input data: mprot");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mprot, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mprot;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a1DDF", NC_FLOAT, 2, dimids, &ncl_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1DDF, "long_name", 50,
                             "ncl_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a1SF", NC_FLOAT, 2, dimids, &ncl_a1SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1SF, "long_name", 31, "ncl_a1 seasalt surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a1SFWET", NC_FLOAT, 2, dimids, &ncl_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a1_SRF", NC_FLOAT, 2, dimids, &ncl_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1_SRF, "long_name", 22, "ncl_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a2DDF", NC_FLOAT, 2, dimids, &ncl_a2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2DDF, "long_name", 50,
                             "ncl_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a2SF", NC_FLOAT, 2, dimids, &ncl_a2SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2SF, "long_name", 31, "ncl_a2 seasalt surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a2SFWET", NC_FLOAT, 2, dimids, &ncl_a2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a2_SRF", NC_FLOAT, 2, dimids, &ncl_a2_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2_SRF, "long_name", 22, "ncl_a2 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a3DDF", NC_FLOAT, 2, dimids, &ncl_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3DDF, "long_name", 50,
                             "ncl_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a3SF", NC_FLOAT, 2, dimids, &ncl_a3SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3SF, "long_name", 31, "ncl_a3 seasalt surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a3SFWET", NC_FLOAT, 2, dimids, &ncl_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_a3_SRF", NC_FLOAT, 2, dimids, &ncl_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3_SRF, "long_name", 22, "ncl_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_c1DDF", NC_FLOAT, 2, dimids, &ncl_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c1DDF, "long_name", 50,
                             "ncl_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_c1SFWET", NC_FLOAT, 2, dimids, &ncl_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c1SFWET, "long_name", 37,
                             "ncl_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_c2DDF", NC_FLOAT, 2, dimids, &ncl_c2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c2DDF, "long_name", 50,
                             "ncl_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_c2SFWET", NC_FLOAT, 2, dimids, &ncl_c2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c2SFWET, "long_name", 37,
                             "ncl_c2 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_c3DDF", NC_FLOAT, 2, dimids, &ncl_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c3DDF, "long_name", 50,
                             "ncl_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "ncl_c3SFWET", NC_FLOAT, 2, dimids, &ncl_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c3SFWET, "long_name", 37,
                             "ncl_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ncl_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a1DDF", NC_FLOAT, 2, dimids, &num_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1DDF, "long_name", 50,
                             "num_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a1SF", NC_FLOAT, 2, dimids, &num_a1SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1SF, "long_name", 28, "num_a1 dust surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a1SFWET", NC_FLOAT, 2, dimids, &num_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a1_CLXF", NC_FLOAT, 2, dimids, &num_a1_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_CLXF, "long_name", 50,
                             "vertically intergrated external forcing for num_a1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a1_SRF", NC_FLOAT, 2, dimids, &num_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_SRF, "units", 5, " 1/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_SRF, "long_name", 22, "num_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a1_sfgaex1", NC_FLOAT, 2, dimids, &num_a1_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_sfgaex1, "long_name", 51,
                             "num_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a2DDF", NC_FLOAT, 2, dimids, &num_a2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2DDF, "long_name", 50,
                             "num_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a2SFWET", NC_FLOAT, 2, dimids, &num_a2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a2_CLXF", NC_FLOAT, 2, dimids, &num_a2_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2_CLXF, "long_name", 50,
                             "vertically intergrated external forcing for num_a2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a2_SRF", NC_FLOAT, 2, dimids, &num_a2_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2_SRF, "units", 5, " 1/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2_SRF, "long_name", 22, "num_a2 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a3DDF", NC_FLOAT, 2, dimids, &num_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3DDF, "long_name", 50,
                             "num_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a3SF", NC_FLOAT, 2, dimids, &num_a3SF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3SF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3SF, "long_name", 28, "num_a3 dust surface emission");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a3SFWET", NC_FLOAT, 2, dimids, &num_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a3_SRF", NC_FLOAT, 2, dimids, &num_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3_SRF, "units", 5, " 1/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3_SRF, "long_name", 22, "num_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a4DDF", NC_FLOAT, 2, dimids, &num_a4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4DDF, "long_name", 50,
                             "num_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a4SFWET", NC_FLOAT, 2, dimids, &num_a4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a4_CLXF", NC_FLOAT, 2, dimids, &num_a4_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_CLXF, "long_name", 50,
                             "vertically intergrated external forcing for num_a4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a4_SRF", NC_FLOAT, 2, dimids, &num_a4_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_SRF, "units", 5, " 1/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_SRF, "long_name", 22, "num_a4 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_a4_sfgaex1", NC_FLOAT, 2, dimids, &num_a4_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_sfgaex1, "long_name", 51,
                             "num_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c1DDF", NC_FLOAT, 2, dimids, &num_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c1DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c1DDF, "long_name", 50,
                             "num_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c1SFWET", NC_FLOAT, 2, dimids, &num_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c1SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c1SFWET, "long_name", 37,
                             "num_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c2DDF", NC_FLOAT, 2, dimids, &num_c2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c2DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c2DDF, "long_name", 50,
                             "num_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c2SFWET", NC_FLOAT, 2, dimids, &num_c2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c2SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c2SFWET, "long_name", 37,
                             "num_c2 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c3DDF", NC_FLOAT, 2, dimids, &num_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c3DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c3DDF, "long_name", 50,
                             "num_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c3SFWET", NC_FLOAT, 2, dimids, &num_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c3SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c3SFWET, "long_name", 37,
                             "num_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c4DDF", NC_FLOAT, 2, dimids, &num_c4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c4DDF, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c4DDF, "long_name", 50,
                             "num_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "num_c4SFWET", NC_FLOAT, 2, dimids, &num_c4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c4SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c4SFWET, "long_name", 37,
                             "num_c4 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, num_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a1DDF", NC_FLOAT, 2, dimids, &pom_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1DDF, "long_name", 50,
                             "pom_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a1SFWET", NC_FLOAT, 2, dimids, &pom_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a1_SRF", NC_FLOAT, 2, dimids, &pom_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1_SRF, "long_name", 22, "pom_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a1_sfgaex1", NC_FLOAT, 2, dimids, &pom_a1_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1_sfgaex1, "long_name", 51,
                             "pom_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a3DDF", NC_FLOAT, 2, dimids, &pom_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3DDF, "long_name", 50,
                             "pom_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a3SFWET", NC_FLOAT, 2, dimids, &pom_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a3_SRF", NC_FLOAT, 2, dimids, &pom_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3_SRF, "long_name", 22, "pom_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a4DDF", NC_FLOAT, 2, dimids, &pom_a4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4DDF, "long_name", 50,
                             "pom_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a4SFWET", NC_FLOAT, 2, dimids, &pom_a4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a4_CLXF", NC_FLOAT, 2, dimids, &pom_a4_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_CLXF, "long_name", 50,
                             "vertically intergrated external forcing for pom_a4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a4_SRF", NC_FLOAT, 2, dimids, &pom_a4_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_SRF, "long_name", 22, "pom_a4 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_a4_sfgaex1", NC_FLOAT, 2, dimids, &pom_a4_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_sfgaex1, "long_name", 51,
                             "pom_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_c1DDF", NC_FLOAT, 2, dimids, &pom_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c1DDF, "long_name", 50,
                             "pom_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_c1SFWET", NC_FLOAT, 2, dimids, &pom_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c1SFWET, "long_name", 37,
                             "pom_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_c3DDF", NC_FLOAT, 2, dimids, &pom_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c3DDF, "long_name", 50,
                             "pom_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_c3SFWET", NC_FLOAT, 2, dimids, &pom_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c3SFWET, "long_name", 37,
                             "pom_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_c4DDF", NC_FLOAT, 2, dimids, &pom_c4DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c4DDF, "long_name", 50,
                             "pom_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "pom_c4SFWET", NC_FLOAT, 2, dimids, &pom_c4SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c4SFWET, "long_name", 37,
                             "pom_c4 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, pom_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a1DDF", NC_FLOAT, 2, dimids, &so4_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1DDF, "long_name", 50,
                             "so4_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a1SFWET", NC_FLOAT, 2, dimids, &so4_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a1_CLXF", NC_FLOAT, 2, dimids, &so4_a1_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_CLXF, "long_name", 50,
                             "vertically intergrated external forcing for so4_a1");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a1_SRF", NC_FLOAT, 2, dimids, &so4_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_SRF, "long_name", 22, "so4_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a1_sfgaex1", NC_FLOAT, 2, dimids, &so4_a1_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_sfgaex1, "long_name", 51,
                             "so4_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a2DDF", NC_FLOAT, 2, dimids, &so4_a2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2DDF, "long_name", 50,
                             "so4_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a2SFWET", NC_FLOAT, 2, dimids, &so4_a2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a2_CLXF", NC_FLOAT, 2, dimids, &so4_a2_CLXF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_CLXF, "long_name", 50,
                             "vertically intergrated external forcing for so4_a2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a2_SRF", NC_FLOAT, 2, dimids, &so4_a2_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_SRF, "long_name", 22, "so4_a2 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a2_sfgaex1", NC_FLOAT, 2, dimids, &so4_a2_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_sfgaex1, "long_name", 51,
                             "so4_a2 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a2_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a3DDF", NC_FLOAT, 2, dimids, &so4_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3DDF, "long_name", 50,
                             "so4_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a3SFWET", NC_FLOAT, 2, dimids, &so4_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a3_SRF", NC_FLOAT, 2, dimids, &so4_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3_SRF, "long_name", 22, "so4_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_a3_sfgaex1", NC_FLOAT, 2, dimids, &so4_a3_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3_sfgaex1, "long_name", 51,
                             "so4_a3 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_a3_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_c1DDF", NC_FLOAT, 2, dimids, &so4_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c1DDF, "long_name", 50,
                             "so4_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_c1SFWET", NC_FLOAT, 2, dimids, &so4_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c1SFWET, "long_name", 37,
                             "so4_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_c2DDF", NC_FLOAT, 2, dimids, &so4_c2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c2DDF, "long_name", 50,
                             "so4_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_c2SFWET", NC_FLOAT, 2, dimids, &so4_c2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c2SFWET, "long_name", 37,
                             "so4_c2 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_c3DDF", NC_FLOAT, 2, dimids, &so4_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c3DDF, "long_name", 50,
                             "so4_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "so4_c3SFWET", NC_FLOAT, 2, dimids, &so4_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c3SFWET, "long_name", 37,
                             "so4_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, so4_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a1DDF", NC_FLOAT, 2, dimids, &soa_a1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1DDF, "long_name", 50,
                             "soa_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a1SFWET", NC_FLOAT, 2, dimids, &soa_a1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a1_SRF", NC_FLOAT, 2, dimids, &soa_a1_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1_SRF, "long_name", 22, "soa_a1 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a1_sfgaex1", NC_FLOAT, 2, dimids, &soa_a1_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1_sfgaex1, "long_name", 51,
                             "soa_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a2DDF", NC_FLOAT, 2, dimids, &soa_a2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2DDF, "long_name", 50,
                             "soa_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a2SFWET", NC_FLOAT, 2, dimids, &soa_a2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a2_SRF", NC_FLOAT, 2, dimids, &soa_a2_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2_SRF, "long_name", 22, "soa_a2 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a2_sfgaex1", NC_FLOAT, 2, dimids, &soa_a2_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2_sfgaex1, "long_name", 51,
                             "soa_a2 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a2_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a3DDF", NC_FLOAT, 2, dimids, &soa_a3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3DDF, "long_name", 50,
                             "soa_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a3SFWET", NC_FLOAT, 2, dimids, &soa_a3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a3_SRF", NC_FLOAT, 2, dimids, &soa_a3_SRF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3_SRF, "long_name", 22, "soa_a3 in bottom layer");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_a3_sfgaex1", NC_FLOAT, 2, dimids, &soa_a3_sfgaex1);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3_sfgaex1, "long_name", 51,
                             "soa_a3 gas-aerosol-exchange primary column tendency");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_a3_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_c1DDF", NC_FLOAT, 2, dimids, &soa_c1DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c1DDF, "long_name", 50,
                             "soa_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_c1SFWET", NC_FLOAT, 2, dimids, &soa_c1SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c1SFWET, "long_name", 37,
                             "soa_c1 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_c2DDF", NC_FLOAT, 2, dimids, &soa_c2DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c2DDF, "long_name", 50,
                             "soa_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_c2SFWET", NC_FLOAT, 2, dimids, &soa_c2SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c2SFWET, "long_name", 37,
                             "soa_c2 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_c3DDF", NC_FLOAT, 2, dimids, &soa_c3DDF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c3DDF, "long_name", 50,
                             "soa_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "soa_c3SFWET", NC_FLOAT, 2, dimids, &soa_c3SFWET);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c3SFWET, "long_name", 37,
                             "soa_c3 wet deposition flux at surface");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, soa_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c3SFWET;

    assert (i == nvars);

fn_exit:
    return nerrs;
}

/*----< inq_F_case_h0() >----------------------------------------------------*/
int inq_F_case_h0_hdf5 (hid_t ncid,         /* file ID */
                        MPI_Offset dims[2], /* dimension sizes */
                        int nvars,          /* number of variables */
                        int *varids)      /* variable IDs */
{
    /* Total 408 variables */
    int lat, lon, area, lev, hyam, hybm, P0, ilev, hyai, hybi, time, date, datesec, time_bnds,
        date_written, time_written, ndbase, nsbase, nbdate, nbsec, mdt, ndcur, nscur, co2vmr,
        ch4vmr, n2ovmr, f11vmr, f12vmr, sol_tsi, nsteph, AEROD_v, ANRAIN, ANSNOW, AODABS, AODABSBC,
        AODBC, AODDUST, AODDUST1, AODDUST3, AODDUST4, AODMODE1, AODMODE2, AODMODE3, AODMODE4,
        AODNIR, AODPOM, AODSO4, AODSOA, AODSS, AODUV, AODVIS, AQRAIN, AQSNOW, AQ_DMS, AQ_H2O2,
        AQ_H2SO4, AQ_O3, AQ_SO2, AQ_SOAG, AREI, AREL, AWNC, AWNI, CCN3, CDNUMC, CLDHGH, CLDICE,
        CLDLIQ, CLDLOW, CLDMED, CLDTOT, CLOUD, CLOUDFRAC_CLUBB, CONCLD, DCQ, DF_DMS, DF_H2O2,
        DF_H2SO4, DF_O3, DF_SO2, DF_SOAG, DMS_SRF, DP_KCLDBASE, DP_MFUP_MAX, DP_WCLDBASE, DSTSFMBL,
        DTCOND, DTENDTH, DTENDTQ, EXTINCT, FICE, FLDS, FLNS, FLNSC, FLNT, FLNTC, FLUT, FLUTC, FREQI,
        FREQL, FREQR, FREQS, FSDS, FSDSC, FSNS, FSNSC, FSNT, FSNTC, FSNTOA, FSNTOAC, FSUTOA,
        FSUTOAC, F_eff, H2O2_SRF, H2SO4_SRF, H2SO4_sfgaex1, ICEFRAC, ICIMR, ICWMR, IWC, LANDFRAC,
        LHFLX, LINOZ_DO3, LINOZ_DO3_PSC, LINOZ_O3CLIM, LINOZ_O3COL, LINOZ_SSO3, LINOZ_SZA, LND_MBL,
        LWCF, Mass_bc, Mass_dst, Mass_mom, Mass_ncl, Mass_pom, Mass_so4, Mass_soa, NUMICE, NUMLIQ,
        NUMRAI, NUMSNO, O3, O3_SRF, OCNFRAC, OMEGA, OMEGA500, OMEGAT, PBLH, PHIS, PRECC, PRECL,
        PRECSC, PRECSL, PS, PSL, Q, QFLX, QREFHT, QRL, QRS, RAINQM, RAM1, RELHUM, SFDMS, SFH2O2,
        SFH2SO4, SFO3, SFSO2, SFSOAG, SFbc_a1, SFbc_a3, SFbc_a4, SFdst_a1, SFdst_a3, SFmom_a1,
        SFmom_a2, SFmom_a3, SFmom_a4, SFncl_a1, SFncl_a2, SFncl_a3, SFnum_a1, SFnum_a2, SFnum_a3,
        SFnum_a4, SFpom_a1, SFpom_a3, SFpom_a4, SFso4_a1, SFso4_a2, SFso4_a3, SFsoa_a1, SFsoa_a2,
        SFsoa_a3, SHFLX, SH_KCLDBASE, SH_MFUP_MAX, SH_WCLDBASE, SNOWHICE, SNOWHLND, SNOWQM, SO2,
        SO2_CLXF, SO2_SRF, SOAG_CLXF, SOAG_SRF, SOAG_sfgaex1, SOLIN, SSAVIS, SSTSFMBL, SSTSFMBL_OM,
        SWCF, T, TAUGWX, TAUGWY, TAUX, TAUY, TGCLDCWP, TGCLDIWP, TGCLDLWP, TH7001000, TMQ, TREFHT,
        TROP_P, TROP_T, TS, TSMN, TSMX, TUH, TUQ, TVH, TVQ, U, U10, UU, V, VQ, VT, VU, VV, WD_H2O2,
        WD_H2SO4, WD_SO2, WSUB, Z3, aero_water, airFV, bc_a1DDF, bc_a1SFWET, bc_a1_SRF,
        bc_a1_sfgaex1, bc_a3DDF, bc_a3SFWET, bc_a3_SRF, bc_a4DDF, bc_a4SFWET, bc_a4_CLXF, bc_a4_SRF,
        bc_a4_sfgaex1, bc_c1DDF, bc_c1SFWET, bc_c3DDF, bc_c3SFWET, bc_c4DDF, bc_c4SFWET, chla,
        dst_a1DDF, dst_a1SF, dst_a1SFWET, dst_a1_SRF, dst_a3DDF, dst_a3SF, dst_a3SFWET, dst_a3_SRF,
        dst_c1DDF, dst_c1SFWET, dst_c3DDF, dst_c3SFWET, hstobie_linoz, mlip, mom_a1DDF, mom_a1SF,
        mom_a1SFWET, mom_a1_SRF, mom_a1_sfgaex1, mom_a2DDF, mom_a2SF, mom_a2SFWET, mom_a2_SRF,
        mom_a3DDF, mom_a3SFWET, mom_a3_SRF, mom_a4DDF, mom_a4SF, mom_a4SFWET, mom_a4_SRF,
        mom_a4_sfgaex1, mom_c1DDF, mom_c1SFWET, mom_c2DDF, mom_c2SFWET, mom_c3DDF, mom_c3SFWET,
        mom_c4DDF, mom_c4SFWET, mpoly, mprot, ncl_a1DDF, ncl_a1SF, ncl_a1SFWET, ncl_a1_SRF,
        ncl_a2DDF, ncl_a2SF, ncl_a2SFWET, ncl_a2_SRF, ncl_a3DDF, ncl_a3SF, ncl_a3SFWET, ncl_a3_SRF,
        ncl_c1DDF, ncl_c1SFWET, ncl_c2DDF, ncl_c2SFWET, ncl_c3DDF, ncl_c3SFWET, num_a1DDF, num_a1SF,
        num_a1SFWET, num_a1_CLXF, num_a1_SRF, num_a1_sfgaex1, num_a2DDF, num_a2SFWET, num_a2_CLXF,
        num_a2_SRF, num_a3DDF, num_a3SF, num_a3SFWET, num_a3_SRF, num_a4DDF, num_a4SFWET,
        num_a4_CLXF, num_a4_SRF, num_a4_sfgaex1, num_c1DDF, num_c1SFWET, num_c2DDF, num_c2SFWET,
        num_c3DDF, num_c3SFWET, num_c4DDF, num_c4SFWET, pom_a1DDF, pom_a1SFWET, pom_a1_SRF,
        pom_a1_sfgaex1, pom_a3DDF, pom_a3SFWET, pom_a3_SRF, pom_a4DDF, pom_a4SFWET, pom_a4_CLXF,
        pom_a4_SRF, pom_a4_sfgaex1, pom_c1DDF, pom_c1SFWET, pom_c3DDF, pom_c3SFWET, pom_c4DDF,
        pom_c4SFWET, so4_a1DDF, so4_a1SFWET, so4_a1_CLXF, so4_a1_SRF, so4_a1_sfgaex1, so4_a2DDF,
        so4_a2SFWET, so4_a2_CLXF, so4_a2_SRF, so4_a2_sfgaex1, so4_a3DDF, so4_a3SFWET, so4_a3_SRF,
        so4_a3_sfgaex1, so4_c1DDF, so4_c1SFWET, so4_c2DDF, so4_c2SFWET, so4_c3DDF, so4_c3SFWET,
        soa_a1DDF, soa_a1SFWET, soa_a1_SRF, soa_a1_sfgaex1, soa_a2DDF, soa_a2SFWET, soa_a2_SRF,
        soa_a2_sfgaex1, soa_a3DDF, soa_a3SFWET, soa_a3_SRF, soa_a3_sfgaex1, soa_c1DDF, soa_c1SFWET,
        soa_c2DDF, soa_c2SFWET, soa_c3DDF, soa_c3SFWET;

    int i, err, nerrs = 0, dimids[3], iattr, mdims = 1;
    int dim_ncol, dim_time, dim_nbnd, dim_chars, dim_lev, dim_ilev;
    float fillv = 1.e+36f, missv = 1.e+36f;

    /* global attributes: */
    iattr = 4;
    err   = NOP2 (ncid, NC_GLOBAL, "ne", NC_INT, 1, &iattr);
    ERR;
    err = NOP2 (ncid, NC_GLOBAL, "np", NC_INT, 1, &iattr);
    ERR;
    err = NOP (ncid, NC_GLOBAL, "Conventions", 6, "CF-1.0");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "source", 3, "CAM");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "case", 20, "FC5AV1C-H01B_ne4_ne4");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "title", 5, "UNSET");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "logname", 6, "wkliao");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "host", 10, "compute001");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "Version", 6, "$Name$");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "revision_Id", 4, "$Id$");
    ERR;
    err = NOP (
        ncid, NC_GLOBAL, "initial_file", 86,
        "/home/climate1/acme/inputdata/atm/cam/inic/homme/cami_mam3_Linoz_ne4np4_L72_c160909.nc");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "topography_file", 79,
               "/home/climate1/acme/inputdata/atm/cam/topo/USGS-gtopo30_ne4np4_16x.c20160612.nc");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "time_period_freq", 5, "day_5");
    ERR;

    /* inquery dimensions */
    err = hdf5_inq_dimid (ncid, "ncol", &dim_ncol);
    ERR;
    // err = hdf5_inq_dimid(ncid, "time", &dim_time); ERR;
    // err = hdf5_inq_dimid(ncid, "nbnd", &dim_nbnd); ERR;
    // err = hdf5_inq_dimid(ncid, "chars", &dim_chars); ERR;
    err = hdf5_inq_dimid (ncid, "lev", &dim_lev);
    ERR;
    // err = hdf5_inq_dimid(ncid, "ilev", &dim_ilev); ERR;

    err = hdf5_inq_dimlen (ncid, dim_ncol, dims + 1);
    ERR;
    err = hdf5_inq_dimlen (ncid, dim_lev, dims);
    ERR;
    /*
    err = hdf5_def_dim(ncid, "ncol", dims[1],      &dim_ncol); ERR;
    err = hdf5_def_dim(ncid, "time", NC_UNLIMITED, &dim_time); ERR;
    err = hdf5_def_dim(ncid, "nbnd",  2,           &dim_nbnd); ERR;
    err = hdf5_def_dim(ncid, "chars", 8,           &dim_chars); ERR;
    err = hdf5_def_dim(ncid, "lev",   dims[0],     &dim_lev); ERR;
    err = hdf5_def_dim(ncid, "ilev",  dims[0]+1,   &dim_ilev); ERR;
    */

    i = 0;

    /* define variables */
    dimids[0] = dim_ncol;
    err       = INQ_VID (ncid, "lat", NC_DOUBLE, 1, dimids, &lat);
    ERR;
    err = NOP (ncid, lat, "long_name", 8, "latitude");
    ERR;
    err = NOP (ncid, lat, "units", 13, "degrees_north");
    ERR;
    varids[i++] = lat;

    dimids[0] = dim_ncol;
    err       = INQ_VID (ncid, "lon", NC_DOUBLE, 1, dimids, &lon);
    ERR;
    err = NOP (ncid, lon, "long_name", 9, "longitude");
    ERR;
    err = NOP (ncid, lon, "units", 12, "degrees_east");
    ERR;
    varids[i++] = lon;

    dimids[0] = dim_ncol;
    err       = INQ_VID (ncid, "area", NC_DOUBLE, 1, dimids, &area);
    ERR;
    err = NOP (ncid, area, "long_name", 14, "gll grid areas");
    ERR;
    varids[i++] = area;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "lev", NC_DOUBLE, 1, dimids, &lev);
    ERR;
    err = NOP (ncid, lev, "long_name", 38, "hybrid level at midpoints (1000*(A+B))");
    ERR;
    err = NOP (ncid, lev, "units", 3, "hPa");
    ERR;
    err = NOP (ncid, lev, "positive", 4, "down");
    ERR;
    err = NOP (ncid, lev, "standard_name", 43, "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = NOP (ncid, lev, "formula_terms", 29, "a: hyam b: hybm p0: P0 ps: PS");
    ERR;
    varids[i++] = lev;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "hyam", NC_DOUBLE, 1, dimids, &hyam);
    ERR;
    err = NOP (ncid, hyam, "long_name", 39, "hybrid A coefficient at layer midpoints");
    ERR;
    varids[i++] = hyam;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "hybm", NC_DOUBLE, 1, dimids, &hybm);
    ERR;
    err = NOP (ncid, hybm, "long_name", 39, "hybrid B coefficient at layer midpoints");
    ERR;
    varids[i++] = hybm;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "P0", NC_DOUBLE, 0, NULL, &P0);
    ERR;
    err = NOP (ncid, P0, "long_name", 18, "reference pressure");
    ERR;
    err = NOP (ncid, P0, "units", 2, "Pa");
    ERR;
    varids[i++] = P0;

    dimids[0] = dim_ilev;
    err       = INQ_VID (ncid, "ilev", NC_DOUBLE, 1, dimids, &ilev);
    ERR;
    err = NOP (ncid, ilev, "long_name", 39, "hybrid level at interfaces (1000*(A+B))");
    ERR;
    err = NOP (ncid, ilev, "units", 3, "hPa");
    ERR;
    err = NOP (ncid, ilev, "positive", 4, "down");
    ERR;
    err = NOP (ncid, ilev, "standard_name", 43, "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = NOP (ncid, ilev, "formula_terms", 29, "a: hyai b: hybi p0: P0 ps: PS");
    ERR;
    varids[i++] = ilev;

    dimids[0] = dim_ilev;
    err       = INQ_VID (ncid, "hyai", NC_DOUBLE, 1, dimids, &hyai);
    ERR;
    err = NOP (ncid, hyai, "long_name", 40, "hybrid A coefficient at layer interfaces");
    ERR;
    varids[i++] = hyai;

    dimids[0] = dim_ilev;
    err       = INQ_VID (ncid, "hybi", NC_DOUBLE, 1, dimids, &hybi);
    ERR;
    err = NOP (ncid, hybi, "long_name", 40, "hybrid B coefficient at layer interfaces");
    ERR;
    varids[i++] = hybi;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "time", NC_DOUBLE, 1, dimids, &time);
    ERR;
    err = NOP (ncid, time, "long_name", 4, "time");
    ERR;
    err = NOP (ncid, time, "units", 30, "days since 0001-01-01 00:00:00");
    ERR;
    err = NOP (ncid, time, "calendar", 6, "noleap");
    ERR;
    err = NOP (ncid, time, "bounds", 9, "time_bnds");
    ERR;
    varids[i++] = time;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "date", NC_INT, 1, dimids, &date);
    ERR;
    err = NOP (ncid, date, "long_name", 23, "current date (YYYYMMDD)");
    ERR;
    varids[i++] = date;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "datesec", NC_INT, 1, dimids, &datesec);
    ERR;
    err = NOP (ncid, datesec, "long_name", 31, "current seconds of current date");
    ERR;
    varids[i++] = datesec;

    dimids[0] = dim_time;
    dimids[1] = dim_nbnd;
    err       = INQ_VID (ncid, "time_bnds", NC_DOUBLE, 2, dimids, &time_bnds);
    ERR;
    err = NOP (ncid, time_bnds, "long_name", 23, "time interval endpoints");
    ERR;
    varids[i++] = time_bnds;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = INQ_VID (ncid, "date_written", NC_CHAR, 2, dimids, &date_written);
    ERR;
    varids[i++] = date_written;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = INQ_VID (ncid, "time_written", NC_CHAR, 2, dimids, &time_written);
    ERR;
    varids[i++] = time_written;

    err = INQ_VID (ncid, "ndbase", NC_INT, 0, NULL, &ndbase);
    ERR;
    err = NOP (ncid, ndbase, "long_name", 8, "base day");
    ERR;
    varids[i++] = ndbase;
    err         = INQ_VID (ncid, "nsbase", NC_INT, 0, NULL, &nsbase);
    ERR;
    err = NOP (ncid, nsbase, "long_name", 19, "seconds of base day");
    ERR;
    varids[i++] = nsbase;

    err = INQ_VID (ncid, "nbdate", NC_INT, 0, NULL, &nbdate);
    ERR;
    err = NOP (ncid, nbdate, "long_name", 20, "base date (YYYYMMDD)");
    ERR;
    varids[i++] = nbdate;

    err = INQ_VID (ncid, "nbsec", NC_INT, 0, NULL, &nbsec);
    ERR;
    err = NOP (ncid, nbsec, "long_name", 20, "seconds of base date");
    ERR;
    varids[i++] = nbsec;

    err = INQ_VID (ncid, "mdt", NC_INT, 0, NULL, &mdt);
    ERR;
    err = NOP (ncid, mdt, "long_name", 8, "timestep");
    ERR;
    err = NOP (ncid, mdt, "units", 1, "s");
    ERR;
    varids[i++] = mdt;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "ndcur", NC_INT, 1, dimids, &ndcur);
    ERR;
    err = NOP (ncid, ndcur, "long_name", 27, "current day (from base day)");
    ERR;
    varids[i++] = ndcur;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "nscur", NC_INT, 1, dimids, &nscur);
    ERR;
    err = NOP (ncid, nscur, "long_name", 30, "current seconds of current day");
    ERR;
    varids[i++] = nscur;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "co2vmr", NC_DOUBLE, 1, dimids, &co2vmr);
    ERR;
    err = NOP (ncid, co2vmr, "long_name", 23, "co2 volume mixing ratio");
    ERR;
    varids[i++] = co2vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "ch4vmr", NC_DOUBLE, 1, dimids, &ch4vmr);
    ERR;
    err = NOP (ncid, ch4vmr, "long_name", 23, "ch4 volume mixing ratio");
    ERR;
    varids[i++] = ch4vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "n2ovmr", NC_DOUBLE, 1, dimids, &n2ovmr);
    ERR;
    err = NOP (ncid, n2ovmr, "long_name", 23, "n2o volume mixing ratio");
    ERR;
    varids[i++] = n2ovmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "f11vmr", NC_DOUBLE, 1, dimids, &f11vmr);
    ERR;
    err = NOP (ncid, f11vmr, "long_name", 23, "f11 volume mixing ratio");
    ERR;
    varids[i++] = f11vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "f12vmr", NC_DOUBLE, 1, dimids, &f12vmr);
    ERR;
    err = NOP (ncid, f12vmr, "long_name", 23, "f12 volume mixing ratio");
    ERR;
    varids[i++] = f12vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "sol_tsi", NC_DOUBLE, 1, dimids, &sol_tsi);
    ERR;
    err = NOP (ncid, sol_tsi, "long_name", 22, "total solar irradiance");
    ERR;
    err = NOP (ncid, sol_tsi, "units", 4, "W/m2");
    ERR;
    varids[i++] = sol_tsi;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "nsteph", NC_INT, 1, dimids, &nsteph);
    ERR;
    err = NOP (ncid, nsteph, "long_name", 16, "current timestep");
    ERR;
    varids[i++] = nsteph;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AEROD_v", NC_FLOAT, 2, dimids, &AEROD_v);
    ERR;
    err = NOP2 (ncid, AEROD_v, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AEROD_v, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AEROD_v, "units", 1, "1");
    ERR;
    err = NOP (ncid, AEROD_v, "long_name", 43, "Total Aerosol Optical Depth in visible band");
    ERR;
    err = NOP (ncid, AEROD_v, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AEROD_v;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "ANRAIN", NC_FLOAT, 3, dimids, &ANRAIN);
    ERR;
    err = NOP2 (ncid, ANRAIN, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, ANRAIN, "units", 3, "m-3");
    ERR;
    err = NOP (ncid, ANRAIN, "long_name", 24, "Average rain number conc");
    ERR;
    err = NOP (ncid, ANRAIN, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ANRAIN;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "ANSNOW", NC_FLOAT, 3, dimids, &ANSNOW);
    ERR;
    err = NOP2 (ncid, ANSNOW, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, ANSNOW, "units", 3, "m-3");
    ERR;
    err = NOP (ncid, ANSNOW, "long_name", 24, "Average snow number conc");
    ERR;
    err = NOP (ncid, ANSNOW, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ANSNOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODABS", NC_FLOAT, 2, dimids, &AODABS);
    ERR;
    err = NOP2 (ncid, AODABS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODABS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODABS, "long_name", 39, "Aerosol absorption optical depth 550 nm");
    ERR;
    err = NOP (ncid, AODABS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODABS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODABSBC", NC_FLOAT, 2, dimids, &AODABSBC);
    ERR;
    err = NOP2 (ncid, AODABSBC, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODABSBC, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODABSBC, "long_name", 48, "Aerosol absorption optical depth 550 nm from BC");
    ERR;
    err = NOP (ncid, AODABSBC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODABSBC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODBC", NC_FLOAT, 2, dimids, &AODBC);
    ERR;
    err = NOP2 (ncid, AODBC, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODBC, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODBC, "long_name", 37, "Aerosol optical depth 550 nm from BC");
    ERR;
    err = NOP (ncid, AODBC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODBC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODDUST", NC_FLOAT, 2, dimids, &AODDUST);
    ERR;
    err = NOP2 (ncid, AODDUST, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODDUST, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODDUST, "long_name", 38, "Aerosol optical depth 550 nm from dust");
    ERR;
    err = NOP (ncid, AODDUST, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODDUST1", NC_FLOAT, 2, dimids, &AODDUST1);
    ERR;
    err = NOP2 (ncid, AODDUST1, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODDUST1, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODDUST1, "long_name", 46, "Aerosol optical depth 550 nm model 1 from dust");
    ERR;
    err = NOP (ncid, AODDUST1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODDUST3", NC_FLOAT, 2, dimids, &AODDUST3);
    ERR;
    err = NOP2 (ncid, AODDUST3, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODDUST3, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODDUST3, "long_name", 46, "Aerosol optical depth 550 nm model 3 from dust");
    ERR;
    err = NOP (ncid, AODDUST3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODDUST4", NC_FLOAT, 2, dimids, &AODDUST4);
    ERR;
    err = NOP2 (ncid, AODDUST4, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODDUST4, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODDUST4, "long_name", 46, "Aerosol optical depth 550 nm model 4 from dust");
    ERR;
    err = NOP (ncid, AODDUST4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODDUST4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODMODE1", NC_FLOAT, 2, dimids, &AODMODE1);
    ERR;
    err = NOP2 (ncid, AODMODE1, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODMODE1, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODMODE1, "long_name", 35, "Aerosol optical depth 550 nm mode 1");
    ERR;
    err = NOP (ncid, AODMODE1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODMODE2", NC_FLOAT, 2, dimids, &AODMODE2);
    ERR;
    err = NOP2 (ncid, AODMODE2, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODMODE2, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODMODE2, "long_name", 35, "Aerosol optical depth 550 nm mode 2");
    ERR;
    err = NOP (ncid, AODMODE2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODMODE3", NC_FLOAT, 2, dimids, &AODMODE3);
    ERR;
    err = NOP2 (ncid, AODMODE3, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODMODE3, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODMODE3, "long_name", 35, "Aerosol optical depth 550 nm mode 3");
    ERR;
    err = NOP (ncid, AODMODE3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODMODE4", NC_FLOAT, 2, dimids, &AODMODE4);
    ERR;
    err = NOP2 (ncid, AODMODE4, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODMODE4, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODMODE4, "long_name", 35, "Aerosol optical depth 550 nm mode 4");
    ERR;
    err = NOP (ncid, AODMODE4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODMODE4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODNIR", NC_FLOAT, 2, dimids, &AODNIR);
    ERR;
    err = NOP2 (ncid, AODNIR, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODNIR, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODNIR, "long_name", 28, "Aerosol optical depth 850 nm");
    ERR;
    err = NOP (ncid, AODNIR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODNIR;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODPOM", NC_FLOAT, 2, dimids, &AODPOM);
    ERR;
    err = NOP2 (ncid, AODPOM, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODPOM, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODPOM, "long_name", 37, "Aerosol optical depth 550 nm from POM");
    ERR;
    err = NOP (ncid, AODPOM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODPOM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODSO4", NC_FLOAT, 2, dimids, &AODSO4);
    ERR;
    err = NOP2 (ncid, AODSO4, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODSO4, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODSO4, "long_name", 37, "Aerosol optical depth 550 nm from SO4");
    ERR;
    err = NOP (ncid, AODSO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODSO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODSOA", NC_FLOAT, 2, dimids, &AODSOA);
    ERR;
    err = NOP2 (ncid, AODSOA, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODSOA, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODSOA, "long_name", 37, "Aerosol optical depth 550 nm from SOA");
    ERR;
    err = NOP (ncid, AODSOA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODSOA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODSS", NC_FLOAT, 2, dimids, &AODSS);
    ERR;
    err = NOP2 (ncid, AODSS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODSS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODSS, "long_name", 41, "Aerosol optical depth 550 nm from seasalt");
    ERR;
    err = NOP (ncid, AODSS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODSS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODUV", NC_FLOAT, 2, dimids, &AODUV);
    ERR;
    err = NOP2 (ncid, AODUV, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODUV, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODUV, "long_name", 28, "Aerosol optical depth 350 nm");
    ERR;
    err = NOP (ncid, AODUV, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODUV;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AODVIS", NC_FLOAT, 2, dimids, &AODVIS);
    ERR;
    err = NOP2 (ncid, AODVIS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, AODVIS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, AODVIS, "long_name", 28, "Aerosol optical depth 550 nm");
    ERR;
    err = NOP (ncid, AODVIS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AODVIS;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "AQRAIN", NC_FLOAT, 3, dimids, &AQRAIN);
    ERR;
    err = NOP2 (ncid, AQRAIN, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, AQRAIN, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, AQRAIN, "long_name", 25, "Average rain mixing ratio");
    ERR;
    err = NOP (ncid, AQRAIN, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQRAIN;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "AQSNOW", NC_FLOAT, 3, dimids, &AQSNOW);
    ERR;
    err = NOP2 (ncid, AQSNOW, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, AQSNOW, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, AQSNOW, "long_name", 25, "Average snow mixing ratio");
    ERR;
    err = NOP (ncid, AQSNOW, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQSNOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AQ_DMS", NC_FLOAT, 2, dimids, &AQ_DMS);
    ERR;
    err = NOP (ncid, AQ_DMS, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, AQ_DMS, "long_name", 39, "DMS aqueous chemistry (for gas species)");
    ERR;
    err = NOP (ncid, AQ_DMS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_DMS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AQ_H2O2", NC_FLOAT, 2, dimids, &AQ_H2O2);
    ERR;
    err = NOP (ncid, AQ_H2O2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, AQ_H2O2, "long_name", 40, "H2O2 aqueous chemistry (for gas species)");
    ERR;
    err = NOP (ncid, AQ_H2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_H2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AQ_H2SO4", NC_FLOAT, 2, dimids, &AQ_H2SO4);
    ERR;
    err = NOP (ncid, AQ_H2SO4, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, AQ_H2SO4, "long_name", 41, "H2SO4 aqueous chemistry (for gas species)");
    ERR;
    err = NOP (ncid, AQ_H2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_H2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AQ_O3", NC_FLOAT, 2, dimids, &AQ_O3);
    ERR;
    err = NOP (ncid, AQ_O3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, AQ_O3, "long_name", 38, "O3 aqueous chemistry (for gas species)");
    ERR;
    err = NOP (ncid, AQ_O3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_O3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AQ_SO2", NC_FLOAT, 2, dimids, &AQ_SO2);
    ERR;
    err = NOP (ncid, AQ_SO2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, AQ_SO2, "long_name", 39, "SO2 aqueous chemistry (for gas species)");
    ERR;
    err = NOP (ncid, AQ_SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "AQ_SOAG", NC_FLOAT, 2, dimids, &AQ_SOAG);
    ERR;
    err = NOP (ncid, AQ_SOAG, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, AQ_SOAG, "long_name", 40, "SOAG aqueous chemistry (for gas species)");
    ERR;
    err = NOP (ncid, AQ_SOAG, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AQ_SOAG;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "AREI", NC_FLOAT, 3, dimids, &AREI);
    ERR;
    err = NOP2 (ncid, AREI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, AREI, "units", 6, "Micron");
    ERR;
    err = NOP (ncid, AREI, "long_name", 28, "Average ice effective radius");
    ERR;
    err = NOP (ncid, AREI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AREI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "AREL", NC_FLOAT, 3, dimids, &AREL);
    ERR;
    err = NOP2 (ncid, AREL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, AREL, "units", 6, "Micron");
    ERR;
    err = NOP (ncid, AREL, "long_name", 32, "Average droplet effective radius");
    ERR;
    err = NOP (ncid, AREL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AREL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "AWNC", NC_FLOAT, 3, dimids, &AWNC);
    ERR;
    err = NOP2 (ncid, AWNC, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, AWNC, "units", 3, "m-3");
    ERR;
    err = NOP (ncid, AWNC, "long_name", 31, "Average cloud water number conc");
    ERR;
    err = NOP (ncid, AWNC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AWNC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "AWNI", NC_FLOAT, 3, dimids, &AWNI);
    ERR;
    err = NOP2 (ncid, AWNI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, AWNI, "units", 3, "m-3");
    ERR;
    err = NOP (ncid, AWNI, "long_name", 29, "Average cloud ice number conc");
    ERR;
    err = NOP (ncid, AWNI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = AWNI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "CCN3", NC_FLOAT, 3, dimids, &CCN3);
    ERR;
    err = NOP2 (ncid, CCN3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, CCN3, "units", 5, "#/cm3");
    ERR;
    err = NOP (ncid, CCN3, "long_name", 27, "CCN concentration at S=0.1%");
    ERR;
    err = NOP (ncid, CCN3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CCN3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CDNUMC", NC_FLOAT, 2, dimids, &CDNUMC);
    ERR;
    err = NOP (ncid, CDNUMC, "units", 4, "1/m2");
    ERR;
    err = NOP (ncid, CDNUMC, "long_name", 43, "Vertically-integrated droplet concentration");
    ERR;
    err = NOP (ncid, CDNUMC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CDNUMC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CLDHGH", NC_FLOAT, 2, dimids, &CLDHGH);
    ERR;
    err = NOP (ncid, CLDHGH, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLDHGH, "long_name", 32, "Vertically-integrated high cloud");
    ERR;
    err = NOP (ncid, CLDHGH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDHGH;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "CLDICE", NC_FLOAT, 3, dimids, &CLDICE);
    ERR;
    err = NOP2 (ncid, CLDICE, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, CLDICE, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, CLDICE, "long_name", 34, "Grid box averaged cloud ice amount");
    ERR;
    err = NOP (ncid, CLDICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDICE;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "CLDLIQ", NC_FLOAT, 3, dimids, &CLDLIQ);
    ERR;
    err = NOP2 (ncid, CLDLIQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, CLDLIQ, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, CLDLIQ, "long_name", 37, "Grid box averaged cloud liquid amount");
    ERR;
    err = NOP (ncid, CLDLIQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDLIQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CLDLOW", NC_FLOAT, 2, dimids, &CLDLOW);
    ERR;
    err = NOP (ncid, CLDLOW, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLDLOW, "long_name", 31, "Vertically-integrated low cloud");
    ERR;
    err = NOP (ncid, CLDLOW, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDLOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CLDMED", NC_FLOAT, 2, dimids, &CLDMED);
    ERR;
    err = NOP (ncid, CLDMED, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLDMED, "long_name", 37, "Vertically-integrated mid-level cloud");
    ERR;
    err = NOP (ncid, CLDMED, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDMED;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CLDTOT", NC_FLOAT, 2, dimids, &CLDTOT);
    ERR;
    err = NOP (ncid, CLDTOT, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLDTOT, "long_name", 33, "Vertically-integrated total cloud");
    ERR;
    err = NOP (ncid, CLDTOT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLDTOT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "CLOUD", NC_FLOAT, 3, dimids, &CLOUD);
    ERR;
    err = NOP2 (ncid, CLOUD, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, CLOUD, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLOUD, "long_name", 14, "Cloud fraction");
    ERR;
    err = NOP (ncid, CLOUD, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLOUD;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "CLOUDFRAC_CLUBB", NC_FLOAT, 3, dimids, &CLOUDFRAC_CLUBB);
    ERR;
    err = NOP2 (ncid, CLOUDFRAC_CLUBB, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, CLOUDFRAC_CLUBB, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLOUDFRAC_CLUBB, "long_name", 14, "Cloud Fraction");
    ERR;
    err = NOP (ncid, CLOUDFRAC_CLUBB, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CLOUDFRAC_CLUBB;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "CONCLD", NC_FLOAT, 3, dimids, &CONCLD);
    ERR;
    err = NOP2 (ncid, CONCLD, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, CONCLD, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CONCLD, "long_name", 22, "Convective cloud cover");
    ERR;
    err = NOP (ncid, CONCLD, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = CONCLD;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "DCQ", NC_FLOAT, 3, dimids, &DCQ);
    ERR;
    err = NOP2 (ncid, DCQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, DCQ, "units", 7, "kg/kg/s");
    ERR;
    err = NOP (ncid, DCQ, "long_name", 33, "Q tendency due to moist processes");
    ERR;
    err = NOP (ncid, DCQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DCQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DF_DMS", NC_FLOAT, 2, dimids, &DF_DMS);
    ERR;
    err = NOP (ncid, DF_DMS, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DF_DMS, "long_name", 19, "dry deposition flux");
    ERR;
    err = NOP (ncid, DF_DMS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_DMS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DF_H2O2", NC_FLOAT, 2, dimids, &DF_H2O2);
    ERR;
    err = NOP (ncid, DF_H2O2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DF_H2O2, "long_name", 19, "dry deposition flux");
    ERR;
    err = NOP (ncid, DF_H2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_H2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DF_H2SO4", NC_FLOAT, 2, dimids, &DF_H2SO4);
    ERR;
    err = NOP (ncid, DF_H2SO4, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DF_H2SO4, "long_name", 19, "dry deposition flux");
    ERR;
    err = NOP (ncid, DF_H2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_H2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DF_O3", NC_FLOAT, 2, dimids, &DF_O3);
    ERR;
    err = NOP (ncid, DF_O3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DF_O3, "long_name", 19, "dry deposition flux");
    ERR;
    err = NOP (ncid, DF_O3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_O3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DF_SO2", NC_FLOAT, 2, dimids, &DF_SO2);
    ERR;
    err = NOP (ncid, DF_SO2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DF_SO2, "long_name", 19, "dry deposition flux");
    ERR;
    err = NOP (ncid, DF_SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DF_SOAG", NC_FLOAT, 2, dimids, &DF_SOAG);
    ERR;
    err = NOP (ncid, DF_SOAG, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DF_SOAG, "long_name", 19, "dry deposition flux");
    ERR;
    err = NOP (ncid, DF_SOAG, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DF_SOAG;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DMS_SRF", NC_FLOAT, 2, dimids, &DMS_SRF);
    ERR;
    err = NOP (ncid, DMS_SRF, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, DMS_SRF, "long_name", 19, "DMS in bottom layer");
    ERR;
    err = NOP (ncid, DMS_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DMS_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DP_KCLDBASE", NC_FLOAT, 2, dimids, &DP_KCLDBASE);
    ERR;
    err = NOP (ncid, DP_KCLDBASE, "units", 1, "1");
    ERR;
    err = NOP (ncid, DP_KCLDBASE, "long_name", 32, "Deep conv. cloudbase level index");
    ERR;
    err = NOP (ncid, DP_KCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DP_KCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DP_MFUP_MAX", NC_FLOAT, 2, dimids, &DP_MFUP_MAX);
    ERR;
    err = NOP (ncid, DP_MFUP_MAX, "units", 5, "kg/m2");
    ERR;
    err = NOP (ncid, DP_MFUP_MAX, "long_name", 39, "Deep conv. column-max updraft mass flux");
    ERR;
    err = NOP (ncid, DP_MFUP_MAX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DP_MFUP_MAX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DP_WCLDBASE", NC_FLOAT, 2, dimids, &DP_WCLDBASE);
    ERR;
    err = NOP (ncid, DP_WCLDBASE, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, DP_WCLDBASE, "long_name", 38, "Deep conv. cloudbase vertical velocity");
    ERR;
    err = NOP (ncid, DP_WCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DP_WCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DSTSFMBL", NC_FLOAT, 2, dimids, &DSTSFMBL);
    ERR;
    err = NOP (ncid, DSTSFMBL, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DSTSFMBL, "long_name", 28, "Mobilization flux at surface");
    ERR;
    err = NOP (ncid, DSTSFMBL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DSTSFMBL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "DTCOND", NC_FLOAT, 3, dimids, &DTCOND);
    ERR;
    err = NOP2 (ncid, DTCOND, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, DTCOND, "units", 3, "K/s");
    ERR;
    err = NOP (ncid, DTCOND, "long_name", 28, "T tendency - moist processes");
    ERR;
    err = NOP (ncid, DTCOND, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DTCOND;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DTENDTH", NC_FLOAT, 2, dimids, &DTENDTH);
    ERR;
    err = NOP (ncid, DTENDTH, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, DTENDTH, "long_name", 69,
               "Dynamic Tendency of Total (vertically integrated) moist static energy");
    ERR;
    err = NOP (ncid, DTENDTH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DTENDTH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "DTENDTQ", NC_FLOAT, 2, dimids, &DTENDTQ);
    ERR;
    err = NOP (ncid, DTENDTQ, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, DTENDTQ, "long_name", 67,
               "Dynamic Tendency of Total (vertically integrated) specific humidity");
    ERR;
    err = NOP (ncid, DTENDTQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = DTENDTQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "EXTINCT", NC_FLOAT, 3, dimids, &EXTINCT);
    ERR;
    err = NOP2 (ncid, EXTINCT, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP2 (ncid, EXTINCT, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, EXTINCT, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, EXTINCT, "units", 2, "/m");
    ERR;
    err = NOP (ncid, EXTINCT, "long_name", 18, "Aerosol extinction");
    ERR;
    err = NOP (ncid, EXTINCT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = EXTINCT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "FICE", NC_FLOAT, 3, dimids, &FICE);
    ERR;
    err = NOP2 (ncid, FICE, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, FICE, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, FICE, "long_name", 35, "Fractional ice content within cloud");
    ERR;
    err = NOP (ncid, FICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FICE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLDS", NC_FLOAT, 2, dimids, &FLDS);
    ERR;
    err = NOP (ncid, FLDS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLDS, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLDS, "long_name", 36, "Downwelling longwave flux at surface");
    ERR;
    err = NOP (ncid, FLDS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLDS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLNS", NC_FLOAT, 2, dimids, &FLNS);
    ERR;
    err = NOP (ncid, FLNS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLNS, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLNS, "long_name", 28, "Net longwave flux at surface");
    ERR;
    err = NOP (ncid, FLNS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLNSC", NC_FLOAT, 2, dimids, &FLNSC);
    ERR;
    err = NOP (ncid, FLNSC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLNSC, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLNSC, "long_name", 37, "Clearsky net longwave flux at surface");
    ERR;
    err = NOP (ncid, FLNSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLNT", NC_FLOAT, 2, dimids, &FLNT);
    ERR;
    err = NOP (ncid, FLNT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLNT, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLNT, "long_name", 33, "Net longwave flux at top of model");
    ERR;
    err = NOP (ncid, FLNT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLNTC", NC_FLOAT, 2, dimids, &FLNTC);
    ERR;
    err = NOP (ncid, FLNTC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLNTC, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLNTC, "long_name", 42, "Clearsky net longwave flux at top of model");
    ERR;
    err = NOP (ncid, FLNTC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLNTC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLUT", NC_FLOAT, 2, dimids, &FLUT);
    ERR;
    err = NOP (ncid, FLUT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLUT, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLUT, "long_name", 39, "Upwelling longwave flux at top of model");
    ERR;
    err = NOP (ncid, FLUT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLUT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLUTC", NC_FLOAT, 2, dimids, &FLUTC);
    ERR;
    err = NOP (ncid, FLUTC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLUTC, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLUTC, "long_name", 48, "Clearsky upwelling longwave flux at top of model");
    ERR;
    err = NOP (ncid, FLUTC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FLUTC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "FREQI", NC_FLOAT, 3, dimids, &FREQI);
    ERR;
    err = NOP2 (ncid, FREQI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, FREQI, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, FREQI, "long_name", 28, "Fractional occurrence of ice");
    ERR;
    err = NOP (ncid, FREQI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "FREQL", NC_FLOAT, 3, dimids, &FREQL);
    ERR;
    err = NOP2 (ncid, FREQL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, FREQL, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, FREQL, "long_name", 31, "Fractional occurrence of liquid");
    ERR;
    err = NOP (ncid, FREQL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "FREQR", NC_FLOAT, 3, dimids, &FREQR);
    ERR;
    err = NOP2 (ncid, FREQR, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, FREQR, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, FREQR, "long_name", 29, "Fractional occurrence of rain");
    ERR;
    err = NOP (ncid, FREQR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQR;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "FREQS", NC_FLOAT, 3, dimids, &FREQS);
    ERR;
    err = NOP2 (ncid, FREQS, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, FREQS, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, FREQS, "long_name", 29, "Fractional occurrence of snow");
    ERR;
    err = NOP (ncid, FREQS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FREQS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSDS", NC_FLOAT, 2, dimids, &FSDS);
    ERR;
    err = NOP (ncid, FSDS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSDS, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSDS, "long_name", 33, "Downwelling solar flux at surface");
    ERR;
    err = NOP (ncid, FSDS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSDS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSDSC", NC_FLOAT, 2, dimids, &FSDSC);
    ERR;
    err = NOP (ncid, FSDSC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSDSC, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSDSC, "long_name", 42, "Clearsky downwelling solar flux at surface");
    ERR;
    err = NOP (ncid, FSDSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSDSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSNS", NC_FLOAT, 2, dimids, &FSNS);
    ERR;
    err = NOP (ncid, FSNS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSNS, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSNS, "long_name", 25, "Net solar flux at surface");
    ERR;
    err = NOP (ncid, FSNS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSNSC", NC_FLOAT, 2, dimids, &FSNSC);
    ERR;
    err = NOP (ncid, FSNSC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSNSC, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSNSC, "long_name", 34, "Clearsky net solar flux at surface");
    ERR;
    err = NOP (ncid, FSNSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSNT", NC_FLOAT, 2, dimids, &FSNT);
    ERR;
    err = NOP (ncid, FSNT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSNT, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSNT, "long_name", 30, "Net solar flux at top of model");
    ERR;
    err = NOP (ncid, FSNT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSNTC", NC_FLOAT, 2, dimids, &FSNTC);
    ERR;
    err = NOP (ncid, FSNTC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSNTC, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSNTC, "long_name", 39, "Clearsky net solar flux at top of model");
    ERR;
    err = NOP (ncid, FSNTC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNTC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSNTOA", NC_FLOAT, 2, dimids, &FSNTOA);
    ERR;
    err = NOP (ncid, FSNTOA, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSNTOA, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSNTOA, "long_name", 35, "Net solar flux at top of atmosphere");
    ERR;
    err = NOP (ncid, FSNTOA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNTOA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSNTOAC", NC_FLOAT, 2, dimids, &FSNTOAC);
    ERR;
    err = NOP (ncid, FSNTOAC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSNTOAC, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSNTOAC, "long_name", 44, "Clearsky net solar flux at top of atmosphere");
    ERR;
    err = NOP (ncid, FSNTOAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSNTOAC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSUTOA", NC_FLOAT, 2, dimids, &FSUTOA);
    ERR;
    err = NOP (ncid, FSUTOA, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSUTOA, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FSUTOA, "long_name", 41, "Upwelling solar flux at top of atmosphere");
    ERR;
    err = NOP (ncid, FSUTOA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSUTOA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FSUTOAC", NC_FLOAT, 2, dimids, &FSUTOAC);
    ERR;
    err = NOP (ncid, FSUTOAC, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FSUTOAC, "units", 4, "W/m2");
    ERR;
    err =
        NOP (ncid, FSUTOAC, "long_name", 50, "Clearsky upwelling solar flux at top of atmosphere");
    ERR;
    err = NOP (ncid, FSUTOAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = FSUTOAC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "F_eff", NC_FLOAT, 2, dimids, &F_eff);
    ERR;
    err = NOP (ncid, F_eff, "units", 1, "1");
    ERR;
    err =
        NOP (ncid, F_eff, "long_name", 52, "Effective enrichment factor of marine organic matter");
    ERR;
    err = NOP (ncid, F_eff, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = F_eff;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "H2O2_SRF", NC_FLOAT, 2, dimids, &H2O2_SRF);
    ERR;
    err = NOP (ncid, H2O2_SRF, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, H2O2_SRF, "long_name", 20, "H2O2 in bottom layer");
    ERR;
    err = NOP (ncid, H2O2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = H2O2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "H2SO4_SRF", NC_FLOAT, 2, dimids, &H2SO4_SRF);
    ERR;
    err = NOP (ncid, H2SO4_SRF, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, H2SO4_SRF, "long_name", 21, "H2SO4 in bottom layer");
    ERR;
    err = NOP (ncid, H2SO4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = H2SO4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "H2SO4_sfgaex1", NC_FLOAT, 2, dimids, &H2SO4_sfgaex1);
    ERR;
    err = NOP (ncid, H2SO4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, H2SO4_sfgaex1, "long_name", 50,
               "H2SO4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, H2SO4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = H2SO4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ICEFRAC", NC_FLOAT, 2, dimids, &ICEFRAC);
    ERR;
    err = NOP (ncid, ICEFRAC, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, ICEFRAC, "long_name", 39, "Fraction of sfc area covered by sea-ice");
    ERR;
    err = NOP (ncid, ICEFRAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ICEFRAC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "ICIMR", NC_FLOAT, 3, dimids, &ICIMR);
    ERR;
    err = NOP2 (ncid, ICIMR, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, ICIMR, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, ICIMR, "long_name", 36, "Prognostic in-cloud ice mixing ratio");
    ERR;
    err = NOP (ncid, ICIMR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ICIMR;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "ICWMR", NC_FLOAT, 3, dimids, &ICWMR);
    ERR;
    err = NOP2 (ncid, ICWMR, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, ICWMR, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, ICWMR, "long_name", 38, "Prognostic in-cloud water mixing ratio");
    ERR;
    err = NOP (ncid, ICWMR, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ICWMR;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "IWC", NC_FLOAT, 3, dimids, &IWC);
    ERR;
    err = NOP2 (ncid, IWC, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, IWC, "units", 5, "kg/m3");
    ERR;
    err = NOP (ncid, IWC, "long_name", 34, "Grid box average ice water content");
    ERR;
    err = NOP (ncid, IWC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = IWC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "LANDFRAC", NC_FLOAT, 2, dimids, &LANDFRAC);
    ERR;
    err = NOP (ncid, LANDFRAC, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, LANDFRAC, "long_name", 36, "Fraction of sfc area covered by land");
    ERR;
    err = NOP (ncid, LANDFRAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LANDFRAC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "LHFLX", NC_FLOAT, 2, dimids, &LHFLX);
    ERR;
    err = NOP (ncid, LHFLX, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, LHFLX, "long_name", 24, "Surface latent heat flux");
    ERR;
    err = NOP (ncid, LHFLX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LHFLX;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "LINOZ_DO3", NC_FLOAT, 3, dimids, &LINOZ_DO3);
    ERR;
    err = NOP2 (ncid, LINOZ_DO3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, LINOZ_DO3, "units", 2, "/s");
    ERR;
    err =
        NOP (ncid, LINOZ_DO3, "long_name", 48, "ozone vmr tendency by linearized ozone chemistry");
    ERR;
    err = NOP (ncid, LINOZ_DO3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_DO3;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "LINOZ_DO3_PSC", NC_FLOAT, 3, dimids, &LINOZ_DO3_PSC);
    ERR;
    err = NOP2 (ncid, LINOZ_DO3_PSC, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, LINOZ_DO3_PSC, "units", 2, "/s");
    ERR;
    err = NOP (ncid, LINOZ_DO3_PSC, "long_name", 50,
               "ozone vmr loss by PSCs using Carille et al. (1990)");
    ERR;
    err = NOP (ncid, LINOZ_DO3_PSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_DO3_PSC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "LINOZ_O3CLIM", NC_FLOAT, 3, dimids, &LINOZ_O3CLIM);
    ERR;
    err = NOP2 (ncid, LINOZ_O3CLIM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, LINOZ_O3CLIM, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, LINOZ_O3CLIM, "long_name", 29, "climatology of ozone in LINOZ");
    ERR;
    err = NOP (ncid, LINOZ_O3CLIM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_O3CLIM;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "LINOZ_O3COL", NC_FLOAT, 3, dimids, &LINOZ_O3COL);
    ERR;
    err = NOP2 (ncid, LINOZ_O3COL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, LINOZ_O3COL, "units", 2, "DU");
    ERR;
    err = NOP (ncid, LINOZ_O3COL, "long_name", 18, "ozone column above");
    ERR;
    err = NOP (ncid, LINOZ_O3COL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_O3COL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "LINOZ_SSO3", NC_FLOAT, 3, dimids, &LINOZ_SSO3);
    ERR;
    err = NOP2 (ncid, LINOZ_SSO3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, LINOZ_SSO3, "units", 2, "kg");
    ERR;
    err = NOP (ncid, LINOZ_SSO3, "long_name", 27, "steady state ozone in LINOZ");
    ERR;
    err = NOP (ncid, LINOZ_SSO3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_SSO3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "LINOZ_SZA", NC_FLOAT, 2, dimids, &LINOZ_SZA);
    ERR;
    err = NOP (ncid, LINOZ_SZA, "units", 7, "degrees");
    ERR;
    err = NOP (ncid, LINOZ_SZA, "long_name", 27, "solar zenith angle in LINOZ");
    ERR;
    err = NOP (ncid, LINOZ_SZA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LINOZ_SZA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "LND_MBL", NC_FLOAT, 2, dimids, &LND_MBL);
    ERR;
    err = NOP (ncid, LND_MBL, "units", 4, "frac");
    ERR;
    err = NOP (ncid, LND_MBL, "long_name", 23, "Soil erodibility factor");
    ERR;
    err = NOP (ncid, LND_MBL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LND_MBL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "LWCF", NC_FLOAT, 2, dimids, &LWCF);
    ERR;
    err = NOP (ncid, LWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, LWCF, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, LWCF, "long_name", 22, "Longwave cloud forcing");
    ERR;
    err = NOP (ncid, LWCF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = LWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Mass_bc", NC_FLOAT, 3, dimids, &Mass_bc);
    ERR;
    err = NOP2 (ncid, Mass_bc, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Mass_bc, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, Mass_bc, "long_name", 64,
               "sum of bc mass concentration bc_a1+bc_c1+bc_a3+bc_c3+bc_a4+bc_c4");
    ERR;
    err = NOP (ncid, Mass_bc, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_bc;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Mass_dst", NC_FLOAT, 3, dimids, &Mass_dst);
    ERR;
    err = NOP2 (ncid, Mass_dst, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Mass_dst, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, Mass_dst, "long_name", 57,
               "sum of dst mass concentration dst_a1+dst_c1+dst_a3+dst_c3");
    ERR;
    err = NOP (ncid, Mass_dst, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_dst;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Mass_mom", NC_FLOAT, 3, dimids, &Mass_mom);
    ERR;
    err = NOP2 (ncid, Mass_mom, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Mass_mom, "units", 5, "kg/kg");
    ERR;
    err = NOP (
        ncid, Mass_mom, "long_name", 85,
        "sum of mom mass concentration mom_a1+mom_c1+mom_a2+mom_c2+mom_a3+mom_c3+mom_a4+mom_c4");
    ERR;
    err = NOP (ncid, Mass_mom, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_mom;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Mass_ncl", NC_FLOAT, 3, dimids, &Mass_ncl);
    ERR;
    err = NOP2 (ncid, Mass_ncl, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Mass_ncl, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, Mass_ncl, "long_name", 71,
               "sum of ncl mass concentration ncl_a1+ncl_c1+ncl_a2+ncl_c2+ncl_a3+ncl_c3");
    ERR;
    err = NOP (ncid, Mass_ncl, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_ncl;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Mass_pom", NC_FLOAT, 3, dimids, &Mass_pom);
    ERR;
    err = NOP2 (ncid, Mass_pom, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Mass_pom, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, Mass_pom, "long_name", 71,
               "sum of pom mass concentration pom_a1+pom_c1+pom_a3+pom_c3+pom_a4+pom_c4");
    ERR;
    err = NOP (ncid, Mass_pom, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_pom;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Mass_so4", NC_FLOAT, 3, dimids, &Mass_so4);
    ERR;
    err = NOP2 (ncid, Mass_so4, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Mass_so4, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, Mass_so4, "long_name", 71,
               "sum of so4 mass concentration so4_a1+so4_c1+so4_a2+so4_c2+so4_a3+so4_c3");
    ERR;
    err = NOP (ncid, Mass_so4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_so4;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Mass_soa", NC_FLOAT, 3, dimids, &Mass_soa);
    ERR;
    err = NOP2 (ncid, Mass_soa, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Mass_soa, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, Mass_soa, "long_name", 71,
               "sum of soa mass concentration soa_a1+soa_c1+soa_a2+soa_c2+soa_a3+soa_c3");
    ERR;
    err = NOP (ncid, Mass_soa, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Mass_soa;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "NUMICE", NC_FLOAT, 3, dimids, &NUMICE);
    ERR;
    err = NOP2 (ncid, NUMICE, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, NUMICE, "units", 4, "1/kg");
    ERR;
    err = NOP (ncid, NUMICE, "long_name", 34, "Grid box averaged cloud ice number");
    ERR;
    err = NOP (ncid, NUMICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMICE;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "NUMLIQ", NC_FLOAT, 3, dimids, &NUMLIQ);
    ERR;
    err = NOP2 (ncid, NUMLIQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, NUMLIQ, "units", 4, "1/kg");
    ERR;
    err = NOP (ncid, NUMLIQ, "long_name", 37, "Grid box averaged cloud liquid number");
    ERR;
    err = NOP (ncid, NUMLIQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMLIQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "NUMRAI", NC_FLOAT, 3, dimids, &NUMRAI);
    ERR;
    err = NOP2 (ncid, NUMRAI, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, NUMRAI, "units", 4, "1/kg");
    ERR;
    err = NOP (ncid, NUMRAI, "long_name", 29, "Grid box averaged rain number");
    ERR;
    err = NOP (ncid, NUMRAI, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMRAI;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "NUMSNO", NC_FLOAT, 3, dimids, &NUMSNO);
    ERR;
    err = NOP2 (ncid, NUMSNO, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, NUMSNO, "units", 4, "1/kg");
    ERR;
    err = NOP (ncid, NUMSNO, "long_name", 29, "Grid box averaged snow number");
    ERR;
    err = NOP (ncid, NUMSNO, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = NUMSNO;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "O3", NC_FLOAT, 3, dimids, &O3);
    ERR;
    err = NOP2 (ncid, O3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, O3, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, O3, "long_name", 16, "O3 concentration");
    ERR;
    err = NOP (ncid, O3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = O3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "O3_SRF", NC_FLOAT, 2, dimids, &O3_SRF);
    ERR;
    err = NOP (ncid, O3_SRF, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, O3_SRF, "long_name", 18, "O3 in bottom layer");
    ERR;
    err = NOP (ncid, O3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = O3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "OCNFRAC", NC_FLOAT, 2, dimids, &OCNFRAC);
    ERR;
    err = NOP (ncid, OCNFRAC, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, OCNFRAC, "long_name", 37, "Fraction of sfc area covered by ocean");
    ERR;
    err = NOP (ncid, OCNFRAC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OCNFRAC;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "OMEGA", NC_FLOAT, 3, dimids, &OMEGA);
    ERR;
    err = NOP2 (ncid, OMEGA, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, OMEGA, "units", 4, "Pa/s");
    ERR;
    err = NOP (ncid, OMEGA, "long_name", 28, "Vertical velocity (pressure)");
    ERR;
    err = NOP (ncid, OMEGA, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OMEGA;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "OMEGA500", NC_FLOAT, 2, dimids, &OMEGA500);
    ERR;
    err = NOP (ncid, OMEGA500, "units", 4, "Pa/s");
    ERR;
    err = NOP (ncid, OMEGA500, "long_name", 46, "Vertical velocity at 500 mbar pressure surface");
    ERR;
    err = NOP (ncid, OMEGA500, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OMEGA500;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "OMEGAT", NC_FLOAT, 3, dimids, &OMEGAT);
    ERR;
    err = NOP2 (ncid, OMEGAT, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, OMEGAT, "units", 6, "K Pa/s");
    ERR;
    err = NOP (ncid, OMEGAT, "long_name", 18, "Vertical heat flux");
    ERR;
    err = NOP (ncid, OMEGAT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = OMEGAT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PBLH", NC_FLOAT, 2, dimids, &PBLH);
    ERR;
    err = NOP (ncid, PBLH, "units", 1, "m");
    ERR;
    err = NOP (ncid, PBLH, "long_name", 10, "PBL height");
    ERR;
    err = NOP (ncid, PBLH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PBLH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PHIS", NC_FLOAT, 2, dimids, &PHIS);
    ERR;
    err = NOP (ncid, PHIS, "units", 5, "m2/s2");
    ERR;
    err = NOP (ncid, PHIS, "long_name", 20, "Surface geopotential");
    ERR;
    varids[i++] = PHIS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PRECC", NC_FLOAT, 2, dimids, &PRECC);
    ERR;
    err = NOP (ncid, PRECC, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, PRECC, "long_name", 41, "Convective precipitation rate (liq + ice)");
    ERR;
    err = NOP (ncid, PRECC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PRECL", NC_FLOAT, 2, dimids, &PRECL);
    ERR;
    err = NOP (ncid, PRECL, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, PRECL, "long_name", 51, "Large-scale (stable) precipitation rate (liq + ice)");
    ERR;
    err = NOP (ncid, PRECL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PRECSC", NC_FLOAT, 2, dimids, &PRECSC);
    ERR;
    err = NOP (ncid, PRECSC, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, PRECSC, "long_name", 39, "Convective snow rate (water equivalent)");
    ERR;
    err = NOP (ncid, PRECSC, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECSC;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PRECSL", NC_FLOAT, 2, dimids, &PRECSL);
    ERR;
    err = NOP (ncid, PRECSL, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, PRECSL, "long_name", 49, "Large-scale (stable) snow rate (water equivalent)");
    ERR;
    err = NOP (ncid, PRECSL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PRECSL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PS", NC_FLOAT, 2, dimids, &PS);
    ERR;
    err = NOP (ncid, PS, "units", 2, "Pa");
    ERR;
    err = NOP (ncid, PS, "long_name", 16, "Surface pressure");
    ERR;
    err = NOP (ncid, PS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PSL", NC_FLOAT, 2, dimids, &PSL);
    ERR;
    err = NOP (ncid, PSL, "units", 2, "Pa");
    ERR;
    err = NOP (ncid, PSL, "long_name", 18, "Sea level pressure");
    ERR;
    err = NOP (ncid, PSL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = PSL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Q", NC_FLOAT, 3, dimids, &Q);
    ERR;
    err = NOP2 (ncid, Q, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Q, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, Q, "long_name", 17, "Specific humidity");
    ERR;
    err = NOP (ncid, Q, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Q;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "QFLX", NC_FLOAT, 2, dimids, &QFLX);
    ERR;
    err = NOP (ncid, QFLX, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, QFLX, "long_name", 18, "Surface water flux");
    ERR;
    err = NOP (ncid, QFLX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QFLX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "QREFHT", NC_FLOAT, 2, dimids, &QREFHT);
    ERR;
    err = NOP (ncid, QREFHT, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, QREFHT, "long_name", 25, "Reference height humidity");
    ERR;
    err = NOP (ncid, QREFHT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QREFHT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "QRL", NC_FLOAT, 3, dimids, &QRL);
    ERR;
    err = NOP2 (ncid, QRL, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, QRL, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, QRL, "units", 3, "K/s");
    ERR;
    err = NOP (ncid, QRL, "long_name", 21, "Longwave heating rate");
    ERR;
    err = NOP (ncid, QRL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QRL;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "QRS", NC_FLOAT, 3, dimids, &QRS);
    ERR;
    err = NOP2 (ncid, QRS, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, QRS, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, QRS, "units", 3, "K/s");
    ERR;
    err = NOP (ncid, QRS, "long_name", 18, "Solar heating rate");
    ERR;
    err = NOP (ncid, QRS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = QRS;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "RAINQM", NC_FLOAT, 3, dimids, &RAINQM);
    ERR;
    err = NOP2 (ncid, RAINQM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, RAINQM, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, RAINQM, "long_name", 29, "Grid box averaged rain amount");
    ERR;
    err = NOP (ncid, RAINQM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = RAINQM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "RAM1", NC_FLOAT, 2, dimids, &RAM1);
    ERR;
    err = NOP (ncid, RAM1, "units", 4, "frac");
    ERR;
    err = NOP (ncid, RAM1, "long_name", 4, "RAM1");
    ERR;
    err = NOP (ncid, RAM1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = RAM1;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "RELHUM", NC_FLOAT, 3, dimids, &RELHUM);
    ERR;
    err = NOP2 (ncid, RELHUM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, RELHUM, "units", 7, "percent");
    ERR;
    err = NOP (ncid, RELHUM, "long_name", 17, "Relative humidity");
    ERR;
    err = NOP (ncid, RELHUM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = RELHUM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFDMS", NC_FLOAT, 2, dimids, &SFDMS);
    ERR;
    err = NOP (ncid, SFDMS, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFDMS, "long_name", 16, "DMS surface flux");
    ERR;
    err = NOP (ncid, SFDMS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFDMS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFH2O2", NC_FLOAT, 2, dimids, &SFH2O2);
    ERR;
    err = NOP (ncid, SFH2O2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFH2O2, "long_name", 17, "H2O2 surface flux");
    ERR;
    err = NOP (ncid, SFH2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFH2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFH2SO4", NC_FLOAT, 2, dimids, &SFH2SO4);
    ERR;
    err = NOP (ncid, SFH2SO4, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFH2SO4, "long_name", 18, "H2SO4 surface flux");
    ERR;
    err = NOP (ncid, SFH2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFH2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFO3", NC_FLOAT, 2, dimids, &SFO3);
    ERR;
    err = NOP (ncid, SFO3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFO3, "long_name", 15, "O3 surface flux");
    ERR;
    err = NOP (ncid, SFO3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFO3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFSO2", NC_FLOAT, 2, dimids, &SFSO2);
    ERR;
    err = NOP (ncid, SFSO2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFSO2, "long_name", 16, "SO2 surface flux");
    ERR;
    err = NOP (ncid, SFSO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFSO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFSOAG", NC_FLOAT, 2, dimids, &SFSOAG);
    ERR;
    err = NOP (ncid, SFSOAG, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFSOAG, "long_name", 17, "SOAG surface flux");
    ERR;
    err = NOP (ncid, SFSOAG, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFSOAG;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFbc_a1", NC_FLOAT, 2, dimids, &SFbc_a1);
    ERR;
    err = NOP (ncid, SFbc_a1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFbc_a1, "long_name", 18, "bc_a1 surface flux");
    ERR;
    err = NOP (ncid, SFbc_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFbc_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFbc_a3", NC_FLOAT, 2, dimids, &SFbc_a3);
    ERR;
    err = NOP (ncid, SFbc_a3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFbc_a3, "long_name", 18, "bc_a3 surface flux");
    ERR;
    err = NOP (ncid, SFbc_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFbc_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFbc_a4", NC_FLOAT, 2, dimids, &SFbc_a4);
    ERR;
    err = NOP (ncid, SFbc_a4, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFbc_a4, "long_name", 18, "bc_a4 surface flux");
    ERR;
    err = NOP (ncid, SFbc_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFbc_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFdst_a1", NC_FLOAT, 2, dimids, &SFdst_a1);
    ERR;
    err = NOP (ncid, SFdst_a1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFdst_a1, "long_name", 19, "dst_a1 surface flux");
    ERR;
    err = NOP (ncid, SFdst_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFdst_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFdst_a3", NC_FLOAT, 2, dimids, &SFdst_a3);
    ERR;
    err = NOP (ncid, SFdst_a3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFdst_a3, "long_name", 19, "dst_a3 surface flux");
    ERR;
    err = NOP (ncid, SFdst_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFdst_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFmom_a1", NC_FLOAT, 2, dimids, &SFmom_a1);
    ERR;
    err = NOP (ncid, SFmom_a1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFmom_a1, "long_name", 19, "mom_a1 surface flux");
    ERR;
    err = NOP (ncid, SFmom_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFmom_a2", NC_FLOAT, 2, dimids, &SFmom_a2);
    ERR;
    err = NOP (ncid, SFmom_a2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFmom_a2, "long_name", 19, "mom_a2 surface flux");
    ERR;
    err = NOP (ncid, SFmom_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFmom_a3", NC_FLOAT, 2, dimids, &SFmom_a3);
    ERR;
    err = NOP (ncid, SFmom_a3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFmom_a3, "long_name", 19, "mom_a3 surface flux");
    ERR;
    err = NOP (ncid, SFmom_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFmom_a4", NC_FLOAT, 2, dimids, &SFmom_a4);
    ERR;
    err = NOP (ncid, SFmom_a4, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFmom_a4, "long_name", 19, "mom_a4 surface flux");
    ERR;
    err = NOP (ncid, SFmom_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFmom_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFncl_a1", NC_FLOAT, 2, dimids, &SFncl_a1);
    ERR;
    err = NOP (ncid, SFncl_a1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFncl_a1, "long_name", 19, "ncl_a1 surface flux");
    ERR;
    err = NOP (ncid, SFncl_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFncl_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFncl_a2", NC_FLOAT, 2, dimids, &SFncl_a2);
    ERR;
    err = NOP (ncid, SFncl_a2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFncl_a2, "long_name", 19, "ncl_a2 surface flux");
    ERR;
    err = NOP (ncid, SFncl_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFncl_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFncl_a3", NC_FLOAT, 2, dimids, &SFncl_a3);
    ERR;
    err = NOP (ncid, SFncl_a3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFncl_a3, "long_name", 19, "ncl_a3 surface flux");
    ERR;
    err = NOP (ncid, SFncl_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFncl_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFnum_a1", NC_FLOAT, 2, dimids, &SFnum_a1);
    ERR;
    err = NOP (ncid, SFnum_a1, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, SFnum_a1, "long_name", 19, "num_a1 surface flux");
    ERR;
    err = NOP (ncid, SFnum_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFnum_a2", NC_FLOAT, 2, dimids, &SFnum_a2);
    ERR;
    err = NOP (ncid, SFnum_a2, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, SFnum_a2, "long_name", 19, "num_a2 surface flux");
    ERR;
    err = NOP (ncid, SFnum_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFnum_a3", NC_FLOAT, 2, dimids, &SFnum_a3);
    ERR;
    err = NOP (ncid, SFnum_a3, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, SFnum_a3, "long_name", 19, "num_a3 surface flux");
    ERR;
    err = NOP (ncid, SFnum_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFnum_a4", NC_FLOAT, 2, dimids, &SFnum_a4);
    ERR;
    err = NOP (ncid, SFnum_a4, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, SFnum_a4, "long_name", 19, "num_a4 surface flux");
    ERR;
    err = NOP (ncid, SFnum_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFnum_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFpom_a1", NC_FLOAT, 2, dimids, &SFpom_a1);
    ERR;
    err = NOP (ncid, SFpom_a1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFpom_a1, "long_name", 19, "pom_a1 surface flux");
    ERR;
    err = NOP (ncid, SFpom_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFpom_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFpom_a3", NC_FLOAT, 2, dimids, &SFpom_a3);
    ERR;
    err = NOP (ncid, SFpom_a3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFpom_a3, "long_name", 19, "pom_a3 surface flux");
    ERR;
    err = NOP (ncid, SFpom_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFpom_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFpom_a4", NC_FLOAT, 2, dimids, &SFpom_a4);
    ERR;
    err = NOP (ncid, SFpom_a4, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFpom_a4, "long_name", 19, "pom_a4 surface flux");
    ERR;
    err = NOP (ncid, SFpom_a4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFpom_a4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFso4_a1", NC_FLOAT, 2, dimids, &SFso4_a1);
    ERR;
    err = NOP (ncid, SFso4_a1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFso4_a1, "long_name", 19, "so4_a1 surface flux");
    ERR;
    err = NOP (ncid, SFso4_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFso4_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFso4_a2", NC_FLOAT, 2, dimids, &SFso4_a2);
    ERR;
    err = NOP (ncid, SFso4_a2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFso4_a2, "long_name", 19, "so4_a2 surface flux");
    ERR;
    err = NOP (ncid, SFso4_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFso4_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFso4_a3", NC_FLOAT, 2, dimids, &SFso4_a3);
    ERR;
    err = NOP (ncid, SFso4_a3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFso4_a3, "long_name", 19, "so4_a3 surface flux");
    ERR;
    err = NOP (ncid, SFso4_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFso4_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFsoa_a1", NC_FLOAT, 2, dimids, &SFsoa_a1);
    ERR;
    err = NOP (ncid, SFsoa_a1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFsoa_a1, "long_name", 19, "soa_a1 surface flux");
    ERR;
    err = NOP (ncid, SFsoa_a1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFsoa_a1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFsoa_a2", NC_FLOAT, 2, dimids, &SFsoa_a2);
    ERR;
    err = NOP (ncid, SFsoa_a2, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFsoa_a2, "long_name", 19, "soa_a2 surface flux");
    ERR;
    err = NOP (ncid, SFsoa_a2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFsoa_a2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SFsoa_a3", NC_FLOAT, 2, dimids, &SFsoa_a3);
    ERR;
    err = NOP (ncid, SFsoa_a3, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SFsoa_a3, "long_name", 19, "soa_a3 surface flux");
    ERR;
    err = NOP (ncid, SFsoa_a3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SFsoa_a3;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SHFLX", NC_FLOAT, 2, dimids, &SHFLX);
    ERR;
    err = NOP (ncid, SHFLX, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, SHFLX, "long_name", 26, "Surface sensible heat flux");
    ERR;
    err = NOP (ncid, SHFLX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SHFLX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SH_KCLDBASE", NC_FLOAT, 2, dimids, &SH_KCLDBASE);
    ERR;
    err = NOP (ncid, SH_KCLDBASE, "units", 1, "1");
    ERR;
    err = NOP (ncid, SH_KCLDBASE, "long_name", 35, "Shallow conv. cloudbase level index");
    ERR;
    err = NOP (ncid, SH_KCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SH_KCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SH_MFUP_MAX", NC_FLOAT, 2, dimids, &SH_MFUP_MAX);
    ERR;
    err = NOP (ncid, SH_MFUP_MAX, "units", 5, "kg/m2");
    ERR;
    err = NOP (ncid, SH_MFUP_MAX, "long_name", 42, "Shallow conv. column-max updraft mass flux");
    ERR;
    err = NOP (ncid, SH_MFUP_MAX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SH_MFUP_MAX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SH_WCLDBASE", NC_FLOAT, 2, dimids, &SH_WCLDBASE);
    ERR;
    err = NOP (ncid, SH_WCLDBASE, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, SH_WCLDBASE, "long_name", 41, "Shallow conv. cloudbase vertical velocity");
    ERR;
    err = NOP (ncid, SH_WCLDBASE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SH_WCLDBASE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SNOWHICE", NC_FLOAT, 2, dimids, &SNOWHICE);
    ERR;
    err = NOP (ncid, SNOWHICE, "units", 1, "m");
    ERR;
    err = NOP (ncid, SNOWHICE, "long_name", 19, "Snow depth over ice");
    ERR;
    err = NOP (ncid, SNOWHICE, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SNOWHICE;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SNOWHLND", NC_FLOAT, 2, dimids, &SNOWHLND);
    ERR;
    err = NOP (ncid, SNOWHLND, "units", 1, "m");
    ERR;
    err = NOP (ncid, SNOWHLND, "long_name", 27, "Water equivalent snow depth");
    ERR;
    err = NOP (ncid, SNOWHLND, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SNOWHLND;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "SNOWQM", NC_FLOAT, 3, dimids, &SNOWQM);
    ERR;
    err = NOP2 (ncid, SNOWQM, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, SNOWQM, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, SNOWQM, "long_name", 29, "Grid box averaged snow amount");
    ERR;
    err = NOP (ncid, SNOWQM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SNOWQM;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "SO2", NC_FLOAT, 3, dimids, &SO2);
    ERR;
    err = NOP2 (ncid, SO2, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, SO2, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, SO2, "long_name", 17, "SO2 concentration");
    ERR;
    err = NOP (ncid, SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SO2_CLXF", NC_FLOAT, 2, dimids, &SO2_CLXF);
    ERR;
    err = NOP (ncid, SO2_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, SO2_CLXF, "long_name", 47, "vertically intergrated external forcing for SO2");
    ERR;
    err = NOP (ncid, SO2_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SO2_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SO2_SRF", NC_FLOAT, 2, dimids, &SO2_SRF);
    ERR;
    err = NOP (ncid, SO2_SRF, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, SO2_SRF, "long_name", 19, "SO2 in bottom layer");
    ERR;
    err = NOP (ncid, SO2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SO2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SOAG_CLXF", NC_FLOAT, 2, dimids, &SOAG_CLXF);
    ERR;
    err = NOP (ncid, SOAG_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err =
        NOP (ncid, SOAG_CLXF, "long_name", 48, "vertically intergrated external forcing for SOAG");
    ERR;
    err = NOP (ncid, SOAG_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOAG_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SOAG_SRF", NC_FLOAT, 2, dimids, &SOAG_SRF);
    ERR;
    err = NOP (ncid, SOAG_SRF, "units", 7, "mol/mol");
    ERR;
    err = NOP (ncid, SOAG_SRF, "long_name", 20, "SOAG in bottom layer");
    ERR;
    err = NOP (ncid, SOAG_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOAG_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SOAG_sfgaex1", NC_FLOAT, 2, dimids, &SOAG_sfgaex1);
    ERR;
    err = NOP (ncid, SOAG_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SOAG_sfgaex1, "long_name", 49,
               "SOAG gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, SOAG_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOAG_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SOLIN", NC_FLOAT, 2, dimids, &SOLIN);
    ERR;
    err = NOP (ncid, SOLIN, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, SOLIN, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, SOLIN, "long_name", 16, "Solar insolation");
    ERR;
    err = NOP (ncid, SOLIN, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SOLIN;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SSAVIS", NC_FLOAT, 2, dimids, &SSAVIS);
    ERR;
    err = NOP2 (ncid, SSAVIS, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, SSAVIS, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, SSAVIS, "long_name", 29, "Aerosol singel-scatter albedo");
    ERR;
    err = NOP (ncid, SSAVIS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SSAVIS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SSTSFMBL", NC_FLOAT, 2, dimids, &SSTSFMBL);
    ERR;
    err = NOP (ncid, SSTSFMBL, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SSTSFMBL, "long_name", 28, "Mobilization flux at surface");
    ERR;
    err = NOP (ncid, SSTSFMBL, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SSTSFMBL;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SSTSFMBL_OM", NC_FLOAT, 2, dimids, &SSTSFMBL_OM);
    ERR;
    err = NOP (ncid, SSTSFMBL_OM, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, SSTSFMBL_OM, "long_name", 53,
               "Mobilization flux of marine organic matter at surface");
    ERR;
    err = NOP (ncid, SSTSFMBL_OM, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SSTSFMBL_OM;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SWCF", NC_FLOAT, 2, dimids, &SWCF);
    ERR;
    err = NOP (ncid, SWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, SWCF, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, SWCF, "long_name", 23, "Shortwave cloud forcing");
    ERR;
    err = NOP (ncid, SWCF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = SWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "T", NC_FLOAT, 3, dimids, &T);
    ERR;
    err = NOP2 (ncid, T, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, T, "units", 1, "K");
    ERR;
    err = NOP (ncid, T, "long_name", 11, "Temperature");
    ERR;
    err = NOP (ncid, T, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = T;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TAUGWX", NC_FLOAT, 2, dimids, &TAUGWX);
    ERR;
    err = NOP (ncid, TAUGWX, "units", 4, "N/m2");
    ERR;
    err = NOP (ncid, TAUGWX, "long_name", 33, "Zonal gravity wave surface stress");
    ERR;
    err = NOP (ncid, TAUGWX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUGWX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TAUGWY", NC_FLOAT, 2, dimids, &TAUGWY);
    ERR;
    err = NOP (ncid, TAUGWY, "units", 4, "N/m2");
    ERR;
    err = NOP (ncid, TAUGWY, "long_name", 38, "Meridional gravity wave surface stress");
    ERR;
    err = NOP (ncid, TAUGWY, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUGWY;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TAUX", NC_FLOAT, 2, dimids, &TAUX);
    ERR;
    err = NOP (ncid, TAUX, "units", 4, "N/m2");
    ERR;
    err = NOP (ncid, TAUX, "long_name", 20, "Zonal surface stress");
    ERR;
    err = NOP (ncid, TAUX, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TAUY", NC_FLOAT, 2, dimids, &TAUY);
    ERR;
    err = NOP (ncid, TAUY, "units", 4, "N/m2");
    ERR;
    err = NOP (ncid, TAUY, "long_name", 25, "Meridional surface stress");
    ERR;
    err = NOP (ncid, TAUY, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TAUY;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TGCLDCWP", NC_FLOAT, 2, dimids, &TGCLDCWP);
    ERR;
    err = NOP (ncid, TGCLDCWP, "units", 5, "kg/m2");
    ERR;
    err = NOP (ncid, TGCLDCWP, "long_name", 48, "Total grid-box cloud water path (liquid and ice)");
    ERR;
    err = NOP (ncid, TGCLDCWP, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TGCLDCWP;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TGCLDIWP", NC_FLOAT, 2, dimids, &TGCLDIWP);
    ERR;
    err = NOP (ncid, TGCLDIWP, "units", 5, "kg/m2");
    ERR;
    err = NOP (ncid, TGCLDIWP, "long_name", 35, "Total grid-box cloud ice water path");
    ERR;
    err = NOP (ncid, TGCLDIWP, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TGCLDIWP;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TGCLDLWP", NC_FLOAT, 2, dimids, &TGCLDLWP);
    ERR;
    err = NOP (ncid, TGCLDLWP, "units", 5, "kg/m2");
    ERR;
    err = NOP (ncid, TGCLDLWP, "long_name", 38, "Total grid-box cloud liquid water path");
    ERR;
    err = NOP (ncid, TGCLDLWP, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TGCLDLWP;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TH7001000", NC_FLOAT, 2, dimids, &TH7001000);
    ERR;
    err = NOP (ncid, TH7001000, "units", 1, "K");
    ERR;
    err = NOP (ncid, TH7001000, "long_name", 33, "Theta difference 700 mb - 1000 mb");
    ERR;
    err = NOP (ncid, TH7001000, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TH7001000;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TMQ", NC_FLOAT, 2, dimids, &TMQ);
    ERR;
    err = NOP (ncid, TMQ, "units", 5, "kg/m2");
    ERR;
    err = NOP (ncid, TMQ, "long_name", 48, "Total (vertically integrated) precipitable water");
    ERR;
    err = NOP (ncid, TMQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TMQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TREFHT", NC_FLOAT, 2, dimids, &TREFHT);
    ERR;
    err = NOP (ncid, TREFHT, "units", 1, "K");
    ERR;
    err = NOP (ncid, TREFHT, "long_name", 28, "Reference height temperature");
    ERR;
    err = NOP (ncid, TREFHT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TREFHT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TROP_P", NC_FLOAT, 2, dimids, &TROP_P);
    ERR;
    err = NOP2 (ncid, TROP_P, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, TROP_P, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, TROP_P, "units", 2, "Pa");
    ERR;
    err = NOP (ncid, TROP_P, "long_name", 19, "Tropopause Pressure");
    ERR;
    err = NOP (ncid, TROP_P, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TROP_P;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TROP_T", NC_FLOAT, 2, dimids, &TROP_T);
    ERR;
    err = NOP2 (ncid, TROP_T, _FillValue, NC_FLOAT, 1, &fillv);
    ERR;
    err = NOP2 (ncid, TROP_T, "missing_value", NC_FLOAT, 1, &missv);
    ERR;
    err = NOP (ncid, TROP_T, "units", 1, "K");
    ERR;
    err = NOP (ncid, TROP_T, "long_name", 22, "Tropopause Temperature");
    ERR;
    err = NOP (ncid, TROP_T, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TROP_T;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TS", NC_FLOAT, 2, dimids, &TS);
    ERR;
    err = NOP (ncid, TS, "units", 1, "K");
    ERR;
    err = NOP (ncid, TS, "long_name", 31, "Surface temperature (radiative)");
    ERR;
    err = NOP (ncid, TS, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TSMN", NC_FLOAT, 2, dimids, &TSMN);
    ERR;
    err = NOP (ncid, TSMN, "units", 1, "K");
    ERR;
    err = NOP (ncid, TSMN, "long_name", 46, "Minimum surface temperature over output period");
    ERR;
    err = NOP (ncid, TSMN, "cell_methods", 13, "time: minimum");
    ERR;
    varids[i++] = TSMN;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TSMX", NC_FLOAT, 2, dimids, &TSMX);
    ERR;
    err = NOP (ncid, TSMX, "units", 1, "K");
    ERR;
    err = NOP (ncid, TSMX, "long_name", 46, "Maximum surface temperature over output period");
    ERR;
    err = NOP (ncid, TSMX, "cell_methods", 13, "time: maximum");
    ERR;
    varids[i++] = TSMX;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TUH", NC_FLOAT, 2, dimids, &TUH);
    ERR;
    err = NOP (ncid, TUH, "units", 3, "W/m");
    ERR;
    err = NOP (ncid, TUH, "long_name", 44, "Total (vertically integrated) zonal MSE flux");
    ERR;
    err = NOP (ncid, TUH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TUH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TUQ", NC_FLOAT, 2, dimids, &TUQ);
    ERR;
    err = NOP (ncid, TUQ, "units", 6, "kg/m/s");
    ERR;
    err = NOP (ncid, TUQ, "long_name", 46, "Total (vertically integrated) zonal water flux");
    ERR;
    err = NOP (ncid, TUQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TUQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TVH", NC_FLOAT, 2, dimids, &TVH);
    ERR;
    err = NOP (ncid, TVH, "units", 3, "W/m");
    ERR;
    err = NOP (ncid, TVH, "long_name", 49, "Total (vertically integrated) meridional MSE flux");
    ERR;
    err = NOP (ncid, TVH, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TVH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TVQ", NC_FLOAT, 2, dimids, &TVQ);
    ERR;
    err = NOP (ncid, TVQ, "units", 6, "kg/m/s");
    ERR;
    err = NOP (ncid, TVQ, "long_name", 51, "Total (vertically integrated) meridional water flux");
    ERR;
    err = NOP (ncid, TVQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = TVQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "U", NC_FLOAT, 3, dimids, &U);
    ERR;
    err = NOP2 (ncid, U, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, U, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, U, "long_name", 10, "Zonal wind");
    ERR;
    err = NOP (ncid, U, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = U;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "U10", NC_FLOAT, 2, dimids, &U10);
    ERR;
    err = NOP (ncid, U10, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, U10, "long_name", 14, "10m wind speed");
    ERR;
    err = NOP (ncid, U10, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = U10;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "UU", NC_FLOAT, 3, dimids, &UU);
    ERR;
    err = NOP2 (ncid, UU, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, UU, "units", 5, "m2/s2");
    ERR;
    err = NOP (ncid, UU, "long_name", 22, "Zonal velocity squared");
    ERR;
    err = NOP (ncid, UU, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = UU;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "V", NC_FLOAT, 3, dimids, &V);
    ERR;
    err = NOP2 (ncid, V, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, V, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, V, "long_name", 15, "Meridional wind");
    ERR;
    err = NOP (ncid, V, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = V;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "VQ", NC_FLOAT, 3, dimids, &VQ);
    ERR;
    err = NOP2 (ncid, VQ, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, VQ, "units", 8, "m/skg/kg");
    ERR;
    err = NOP (ncid, VQ, "long_name", 26, "Meridional water transport");
    ERR;
    err = NOP (ncid, VQ, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VQ;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "VT", NC_FLOAT, 3, dimids, &VT);
    ERR;
    err = NOP2 (ncid, VT, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, VT, "units", 5, "K m/s");
    ERR;
    err = NOP (ncid, VT, "long_name", 25, "Meridional heat transport");
    ERR;
    err = NOP (ncid, VT, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VT;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "VU", NC_FLOAT, 3, dimids, &VU);
    ERR;
    err = NOP2 (ncid, VU, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, VU, "units", 5, "m2/s2");
    ERR;
    err = NOP (ncid, VU, "long_name", 33, "Meridional flux of zonal momentum");
    ERR;
    err = NOP (ncid, VU, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VU;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "VV", NC_FLOAT, 3, dimids, &VV);
    ERR;
    err = NOP2 (ncid, VV, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, VV, "units", 5, "m2/s2");
    ERR;
    err = NOP (ncid, VV, "long_name", 27, "Meridional velocity squared");
    ERR;
    err = NOP (ncid, VV, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = VV;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "WD_H2O2", NC_FLOAT, 2, dimids, &WD_H2O2);
    ERR;
    err = NOP (ncid, WD_H2O2, "units", 4, "kg/s");
    ERR;
    err = NOP (ncid, WD_H2O2, "long_name", 31, "H2O2             wet deposition");
    ERR;
    err = NOP (ncid, WD_H2O2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WD_H2O2;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "WD_H2SO4", NC_FLOAT, 2, dimids, &WD_H2SO4);
    ERR;
    err = NOP (ncid, WD_H2SO4, "units", 4, "kg/s");
    ERR;
    err = NOP (ncid, WD_H2SO4, "long_name", 31, "H2SO4            wet deposition");
    ERR;
    err = NOP (ncid, WD_H2SO4, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WD_H2SO4;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "WD_SO2", NC_FLOAT, 2, dimids, &WD_SO2);
    ERR;
    err = NOP (ncid, WD_SO2, "units", 4, "kg/s");
    ERR;
    err = NOP (ncid, WD_SO2, "long_name", 31, "SO2              wet deposition");
    ERR;
    err = NOP (ncid, WD_SO2, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WD_SO2;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "WSUB", NC_FLOAT, 3, dimids, &WSUB);
    ERR;
    err = NOP2 (ncid, WSUB, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, WSUB, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, WSUB, "long_name", 37, "Diagnostic sub-grid vertical velocity");
    ERR;
    err = NOP (ncid, WSUB, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = WSUB;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "Z3", NC_FLOAT, 3, dimids, &Z3);
    ERR;
    err = NOP2 (ncid, Z3, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, Z3, "units", 1, "m");
    ERR;
    err = NOP (ncid, Z3, "long_name", 37, "Geopotential Height (above sea level)");
    ERR;
    err = NOP (ncid, Z3, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = Z3;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "aero_water", NC_FLOAT, 3, dimids, &aero_water);
    ERR;
    err = NOP2 (ncid, aero_water, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, aero_water, "units", 1, "m");
    ERR;
    err = NOP (ncid, aero_water, "long_name", 70,
               "sum of aerosol water of interstitial modes wat_a1+wat_a2+wat_a3+wat_a4");
    ERR;
    err = NOP (ncid, aero_water, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = aero_water;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "airFV", NC_FLOAT, 2, dimids, &airFV);
    ERR;
    err = NOP (ncid, airFV, "units", 4, "frac");
    ERR;
    err = NOP (ncid, airFV, "long_name", 2, "FV");
    ERR;
    err = NOP (ncid, airFV, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = airFV;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a1DDF", NC_FLOAT, 2, dimids, &bc_a1DDF);
    ERR;
    err = NOP (ncid, bc_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err =
        NOP (ncid, bc_a1DDF, "long_name", 49, "bc_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, bc_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a1SFWET", NC_FLOAT, 2, dimids, &bc_a1SFWET);
    ERR;
    err = NOP (ncid, bc_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, bc_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a1_SRF", NC_FLOAT, 2, dimids, &bc_a1_SRF);
    ERR;
    err = NOP (ncid, bc_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, bc_a1_SRF, "long_name", 21, "bc_a1 in bottom layer");
    ERR;
    err = NOP (ncid, bc_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a1_sfgaex1", NC_FLOAT, 2, dimids, &bc_a1_sfgaex1);
    ERR;
    err = NOP (ncid, bc_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_a1_sfgaex1, "long_name", 51,
               "bc_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, bc_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a3DDF", NC_FLOAT, 2, dimids, &bc_a3DDF);
    ERR;
    err = NOP (ncid, bc_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err =
        NOP (ncid, bc_a3DDF, "long_name", 49, "bc_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, bc_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a3SFWET", NC_FLOAT, 2, dimids, &bc_a3SFWET);
    ERR;
    err = NOP (ncid, bc_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, bc_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a3_SRF", NC_FLOAT, 2, dimids, &bc_a3_SRF);
    ERR;
    err = NOP (ncid, bc_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, bc_a3_SRF, "long_name", 21, "bc_a3 in bottom layer");
    ERR;
    err = NOP (ncid, bc_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a4DDF", NC_FLOAT, 2, dimids, &bc_a4DDF);
    ERR;
    err = NOP (ncid, bc_a4DDF, "units", 7, "kg/m2/s");
    ERR;
    err =
        NOP (ncid, bc_a4DDF, "long_name", 49, "bc_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, bc_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a4SFWET", NC_FLOAT, 2, dimids, &bc_a4SFWET);
    ERR;
    err = NOP (ncid, bc_a4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, bc_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a4_CLXF", NC_FLOAT, 2, dimids, &bc_a4_CLXF);
    ERR;
    err = NOP (ncid, bc_a4_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, bc_a4_CLXF, "long_name", 49,
               "vertically intergrated external forcing for bc_a4");
    ERR;
    err = NOP (ncid, bc_a4_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a4_SRF", NC_FLOAT, 2, dimids, &bc_a4_SRF);
    ERR;
    err = NOP (ncid, bc_a4_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, bc_a4_SRF, "long_name", 21, "bc_a4 in bottom layer");
    ERR;
    err = NOP (ncid, bc_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_a4_sfgaex1", NC_FLOAT, 2, dimids, &bc_a4_sfgaex1);
    ERR;
    err = NOP (ncid, bc_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_a4_sfgaex1, "long_name", 50,
               "bc_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, bc_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_c1DDF", NC_FLOAT, 2, dimids, &bc_c1DDF);
    ERR;
    err = NOP (ncid, bc_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err =
        NOP (ncid, bc_c1DDF, "long_name", 49, "bc_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, bc_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_c1SFWET", NC_FLOAT, 2, dimids, &bc_c1SFWET);
    ERR;
    err = NOP (ncid, bc_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_c1SFWET, "long_name", 36, "bc_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, bc_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_c3DDF", NC_FLOAT, 2, dimids, &bc_c3DDF);
    ERR;
    err = NOP (ncid, bc_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err =
        NOP (ncid, bc_c3DDF, "long_name", 49, "bc_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, bc_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_c3SFWET", NC_FLOAT, 2, dimids, &bc_c3SFWET);
    ERR;
    err = NOP (ncid, bc_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_c3SFWET, "long_name", 36, "bc_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, bc_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_c4DDF", NC_FLOAT, 2, dimids, &bc_c4DDF);
    ERR;
    err = NOP (ncid, bc_c4DDF, "units", 7, "kg/m2/s");
    ERR;
    err =
        NOP (ncid, bc_c4DDF, "long_name", 49, "bc_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, bc_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "bc_c4SFWET", NC_FLOAT, 2, dimids, &bc_c4SFWET);
    ERR;
    err = NOP (ncid, bc_c4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, bc_c4SFWET, "long_name", 36, "bc_c4 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, bc_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = bc_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "chla", NC_FLOAT, 2, dimids, &chla);
    ERR;
    err = NOP (ncid, chla, "units", 6, "mg L-1");
    ERR;
    err = NOP (ncid, chla, "long_name", 22, "ocean input data: chla");
    ERR;
    err = NOP (ncid, chla, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = chla;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a1DDF", NC_FLOAT, 2, dimids, &dst_a1DDF);
    ERR;
    err = NOP (ncid, dst_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_a1DDF, "long_name", 50,
               "dst_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, dst_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a1SF", NC_FLOAT, 2, dimids, &dst_a1SF);
    ERR;
    err = NOP (ncid, dst_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_a1SF, "long_name", 28, "dst_a1 dust surface emission");
    ERR;
    err = NOP (ncid, dst_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a1SFWET", NC_FLOAT, 2, dimids, &dst_a1SFWET);
    ERR;
    err = NOP (ncid, dst_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, dst_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a1_SRF", NC_FLOAT, 2, dimids, &dst_a1_SRF);
    ERR;
    err = NOP (ncid, dst_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, dst_a1_SRF, "long_name", 22, "dst_a1 in bottom layer");
    ERR;
    err = NOP (ncid, dst_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a3DDF", NC_FLOAT, 2, dimids, &dst_a3DDF);
    ERR;
    err = NOP (ncid, dst_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_a3DDF, "long_name", 50,
               "dst_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, dst_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a3SF", NC_FLOAT, 2, dimids, &dst_a3SF);
    ERR;
    err = NOP (ncid, dst_a3SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_a3SF, "long_name", 28, "dst_a3 dust surface emission");
    ERR;
    err = NOP (ncid, dst_a3SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a3SFWET", NC_FLOAT, 2, dimids, &dst_a3SFWET);
    ERR;
    err = NOP (ncid, dst_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, dst_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_a3_SRF", NC_FLOAT, 2, dimids, &dst_a3_SRF);
    ERR;
    err = NOP (ncid, dst_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, dst_a3_SRF, "long_name", 22, "dst_a3 in bottom layer");
    ERR;
    err = NOP (ncid, dst_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_c1DDF", NC_FLOAT, 2, dimids, &dst_c1DDF);
    ERR;
    err = NOP (ncid, dst_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_c1DDF, "long_name", 50,
               "dst_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, dst_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_c1SFWET", NC_FLOAT, 2, dimids, &dst_c1SFWET);
    ERR;
    err = NOP (ncid, dst_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_c1SFWET, "long_name", 37, "dst_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, dst_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_c3DDF", NC_FLOAT, 2, dimids, &dst_c3DDF);
    ERR;
    err = NOP (ncid, dst_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_c3DDF, "long_name", 50,
               "dst_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, dst_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "dst_c3SFWET", NC_FLOAT, 2, dimids, &dst_c3SFWET);
    ERR;
    err = NOP (ncid, dst_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, dst_c3SFWET, "long_name", 37, "dst_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, dst_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = dst_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "hstobie_linoz", NC_FLOAT, 3, dimids, &hstobie_linoz);
    ERR;
    err = NOP2 (ncid, hstobie_linoz, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, hstobie_linoz, "units", 22, "fraction of model time");
    ERR;
    err = NOP (ncid, hstobie_linoz, "long_name", 27, "Lowest possible Linoz level");
    ERR;
    varids[i++] = hstobie_linoz;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mlip", NC_FLOAT, 2, dimids, &mlip);
    ERR;
    err = NOP (ncid, mlip, "units", 4, "uM C");
    ERR;
    err = NOP (ncid, mlip, "long_name", 22, "ocean input data: mlip");
    ERR;
    err = NOP (ncid, mlip, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mlip;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a1DDF", NC_FLOAT, 2, dimids, &mom_a1DDF);
    ERR;
    err = NOP (ncid, mom_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a1DDF, "long_name", 50,
               "mom_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a1SF", NC_FLOAT, 2, dimids, &mom_a1SF);
    ERR;
    err = NOP (ncid, mom_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a1SF, "long_name", 31, "mom_a1 seasalt surface emission");
    ERR;
    err = NOP (ncid, mom_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a1SFWET", NC_FLOAT, 2, dimids, &mom_a1SFWET);
    ERR;
    err = NOP (ncid, mom_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a1_SRF", NC_FLOAT, 2, dimids, &mom_a1_SRF);
    ERR;
    err = NOP (ncid, mom_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, mom_a1_SRF, "long_name", 22, "mom_a1 in bottom layer");
    ERR;
    err = NOP (ncid, mom_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a1_sfgaex1", NC_FLOAT, 2, dimids, &mom_a1_sfgaex1);
    ERR;
    err = NOP (ncid, mom_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a1_sfgaex1, "long_name", 51,
               "mom_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, mom_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a2DDF", NC_FLOAT, 2, dimids, &mom_a2DDF);
    ERR;
    err = NOP (ncid, mom_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a2DDF, "long_name", 50,
               "mom_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a2SF", NC_FLOAT, 2, dimids, &mom_a2SF);
    ERR;
    err = NOP (ncid, mom_a2SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a2SF, "long_name", 31, "mom_a2 seasalt surface emission");
    ERR;
    err = NOP (ncid, mom_a2SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a2SFWET", NC_FLOAT, 2, dimids, &mom_a2SFWET);
    ERR;
    err = NOP (ncid, mom_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a2_SRF", NC_FLOAT, 2, dimids, &mom_a2_SRF);
    ERR;
    err = NOP (ncid, mom_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, mom_a2_SRF, "long_name", 22, "mom_a2 in bottom layer");
    ERR;
    err = NOP (ncid, mom_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a3DDF", NC_FLOAT, 2, dimids, &mom_a3DDF);
    ERR;
    err = NOP (ncid, mom_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a3DDF, "long_name", 50,
               "mom_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a3SFWET", NC_FLOAT, 2, dimids, &mom_a3SFWET);
    ERR;
    err = NOP (ncid, mom_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a3_SRF", NC_FLOAT, 2, dimids, &mom_a3_SRF);
    ERR;
    err = NOP (ncid, mom_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, mom_a3_SRF, "long_name", 22, "mom_a3 in bottom layer");
    ERR;
    err = NOP (ncid, mom_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a4DDF", NC_FLOAT, 2, dimids, &mom_a4DDF);
    ERR;
    err = NOP (ncid, mom_a4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a4DDF, "long_name", 50,
               "mom_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a4SF", NC_FLOAT, 2, dimids, &mom_a4SF);
    ERR;
    err = NOP (ncid, mom_a4SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a4SF, "long_name", 31, "mom_a4 seasalt surface emission");
    ERR;
    err = NOP (ncid, mom_a4SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a4SFWET", NC_FLOAT, 2, dimids, &mom_a4SFWET);
    ERR;
    err = NOP (ncid, mom_a4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a4_SRF", NC_FLOAT, 2, dimids, &mom_a4_SRF);
    ERR;
    err = NOP (ncid, mom_a4_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, mom_a4_SRF, "long_name", 22, "mom_a4 in bottom layer");
    ERR;
    err = NOP (ncid, mom_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_a4_sfgaex1", NC_FLOAT, 2, dimids, &mom_a4_sfgaex1);
    ERR;
    err = NOP (ncid, mom_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_a4_sfgaex1, "long_name", 51,
               "mom_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, mom_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c1DDF", NC_FLOAT, 2, dimids, &mom_c1DDF);
    ERR;
    err = NOP (ncid, mom_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c1DDF, "long_name", 50,
               "mom_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c1SFWET", NC_FLOAT, 2, dimids, &mom_c1SFWET);
    ERR;
    err = NOP (ncid, mom_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c1SFWET, "long_name", 37, "mom_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c2DDF", NC_FLOAT, 2, dimids, &mom_c2DDF);
    ERR;
    err = NOP (ncid, mom_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c2DDF, "long_name", 50,
               "mom_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c2SFWET", NC_FLOAT, 2, dimids, &mom_c2SFWET);
    ERR;
    err = NOP (ncid, mom_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c2SFWET, "long_name", 37, "mom_c2 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c3DDF", NC_FLOAT, 2, dimids, &mom_c3DDF);
    ERR;
    err = NOP (ncid, mom_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c3DDF, "long_name", 50,
               "mom_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c3SFWET", NC_FLOAT, 2, dimids, &mom_c3SFWET);
    ERR;
    err = NOP (ncid, mom_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c3SFWET, "long_name", 37, "mom_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c4DDF", NC_FLOAT, 2, dimids, &mom_c4DDF);
    ERR;
    err = NOP (ncid, mom_c4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c4DDF, "long_name", 50,
               "mom_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, mom_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mom_c4SFWET", NC_FLOAT, 2, dimids, &mom_c4SFWET);
    ERR;
    err = NOP (ncid, mom_c4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, mom_c4SFWET, "long_name", 37, "mom_c4 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, mom_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mom_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mpoly", NC_FLOAT, 2, dimids, &mpoly);
    ERR;
    err = NOP (ncid, mpoly, "units", 4, "uM C");
    ERR;
    err = NOP (ncid, mpoly, "long_name", 23, "ocean input data: mpoly");
    ERR;
    err = NOP (ncid, mpoly, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mpoly;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "mprot", NC_FLOAT, 2, dimids, &mprot);
    ERR;
    err = NOP (ncid, mprot, "units", 4, "uM C");
    ERR;
    err = NOP (ncid, mprot, "long_name", 23, "ocean input data: mprot");
    ERR;
    err = NOP (ncid, mprot, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = mprot;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a1DDF", NC_FLOAT, 2, dimids, &ncl_a1DDF);
    ERR;
    err = NOP (ncid, ncl_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a1DDF, "long_name", 50,
               "ncl_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, ncl_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a1SF", NC_FLOAT, 2, dimids, &ncl_a1SF);
    ERR;
    err = NOP (ncid, ncl_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a1SF, "long_name", 31, "ncl_a1 seasalt surface emission");
    ERR;
    err = NOP (ncid, ncl_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a1SFWET", NC_FLOAT, 2, dimids, &ncl_a1SFWET);
    ERR;
    err = NOP (ncid, ncl_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, ncl_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a1_SRF", NC_FLOAT, 2, dimids, &ncl_a1_SRF);
    ERR;
    err = NOP (ncid, ncl_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, ncl_a1_SRF, "long_name", 22, "ncl_a1 in bottom layer");
    ERR;
    err = NOP (ncid, ncl_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a2DDF", NC_FLOAT, 2, dimids, &ncl_a2DDF);
    ERR;
    err = NOP (ncid, ncl_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a2DDF, "long_name", 50,
               "ncl_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, ncl_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a2SF", NC_FLOAT, 2, dimids, &ncl_a2SF);
    ERR;
    err = NOP (ncid, ncl_a2SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a2SF, "long_name", 31, "ncl_a2 seasalt surface emission");
    ERR;
    err = NOP (ncid, ncl_a2SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a2SFWET", NC_FLOAT, 2, dimids, &ncl_a2SFWET);
    ERR;
    err = NOP (ncid, ncl_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, ncl_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a2_SRF", NC_FLOAT, 2, dimids, &ncl_a2_SRF);
    ERR;
    err = NOP (ncid, ncl_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, ncl_a2_SRF, "long_name", 22, "ncl_a2 in bottom layer");
    ERR;
    err = NOP (ncid, ncl_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a3DDF", NC_FLOAT, 2, dimids, &ncl_a3DDF);
    ERR;
    err = NOP (ncid, ncl_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a3DDF, "long_name", 50,
               "ncl_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, ncl_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a3SF", NC_FLOAT, 2, dimids, &ncl_a3SF);
    ERR;
    err = NOP (ncid, ncl_a3SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a3SF, "long_name", 31, "ncl_a3 seasalt surface emission");
    ERR;
    err = NOP (ncid, ncl_a3SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a3SFWET", NC_FLOAT, 2, dimids, &ncl_a3SFWET);
    ERR;
    err = NOP (ncid, ncl_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, ncl_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_a3_SRF", NC_FLOAT, 2, dimids, &ncl_a3_SRF);
    ERR;
    err = NOP (ncid, ncl_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, ncl_a3_SRF, "long_name", 22, "ncl_a3 in bottom layer");
    ERR;
    err = NOP (ncid, ncl_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_c1DDF", NC_FLOAT, 2, dimids, &ncl_c1DDF);
    ERR;
    err = NOP (ncid, ncl_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_c1DDF, "long_name", 50,
               "ncl_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, ncl_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_c1SFWET", NC_FLOAT, 2, dimids, &ncl_c1SFWET);
    ERR;
    err = NOP (ncid, ncl_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_c1SFWET, "long_name", 37, "ncl_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, ncl_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_c2DDF", NC_FLOAT, 2, dimids, &ncl_c2DDF);
    ERR;
    err = NOP (ncid, ncl_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_c2DDF, "long_name", 50,
               "ncl_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, ncl_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_c2SFWET", NC_FLOAT, 2, dimids, &ncl_c2SFWET);
    ERR;
    err = NOP (ncid, ncl_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_c2SFWET, "long_name", 37, "ncl_c2 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, ncl_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_c3DDF", NC_FLOAT, 2, dimids, &ncl_c3DDF);
    ERR;
    err = NOP (ncid, ncl_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_c3DDF, "long_name", 50,
               "ncl_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, ncl_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "ncl_c3SFWET", NC_FLOAT, 2, dimids, &ncl_c3SFWET);
    ERR;
    err = NOP (ncid, ncl_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, ncl_c3SFWET, "long_name", 37, "ncl_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, ncl_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = ncl_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a1DDF", NC_FLOAT, 2, dimids, &num_a1DDF);
    ERR;
    err = NOP (ncid, num_a1DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a1DDF, "long_name", 50,
               "num_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a1SF", NC_FLOAT, 2, dimids, &num_a1SF);
    ERR;
    err = NOP (ncid, num_a1SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, num_a1SF, "long_name", 28, "num_a1 dust surface emission");
    ERR;
    err = NOP (ncid, num_a1SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a1SFWET", NC_FLOAT, 2, dimids, &num_a1SFWET);
    ERR;
    err = NOP (ncid, num_a1SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a1_CLXF", NC_FLOAT, 2, dimids, &num_a1_CLXF);
    ERR;
    err = NOP (ncid, num_a1_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, num_a1_CLXF, "long_name", 50,
               "vertically intergrated external forcing for num_a1");
    ERR;
    err = NOP (ncid, num_a1_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a1_SRF", NC_FLOAT, 2, dimids, &num_a1_SRF);
    ERR;
    err = NOP (ncid, num_a1_SRF, "units", 5, " 1/kg");
    ERR;
    err = NOP (ncid, num_a1_SRF, "long_name", 22, "num_a1 in bottom layer");
    ERR;
    err = NOP (ncid, num_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a1_sfgaex1", NC_FLOAT, 2, dimids, &num_a1_sfgaex1);
    ERR;
    err = NOP (ncid, num_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, num_a1_sfgaex1, "long_name", 51,
               "num_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, num_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a2DDF", NC_FLOAT, 2, dimids, &num_a2DDF);
    ERR;
    err = NOP (ncid, num_a2DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a2DDF, "long_name", 50,
               "num_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a2SFWET", NC_FLOAT, 2, dimids, &num_a2SFWET);
    ERR;
    err = NOP (ncid, num_a2SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a2_CLXF", NC_FLOAT, 2, dimids, &num_a2_CLXF);
    ERR;
    err = NOP (ncid, num_a2_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, num_a2_CLXF, "long_name", 50,
               "vertically intergrated external forcing for num_a2");
    ERR;
    err = NOP (ncid, num_a2_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a2_SRF", NC_FLOAT, 2, dimids, &num_a2_SRF);
    ERR;
    err = NOP (ncid, num_a2_SRF, "units", 5, " 1/kg");
    ERR;
    err = NOP (ncid, num_a2_SRF, "long_name", 22, "num_a2 in bottom layer");
    ERR;
    err = NOP (ncid, num_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a3DDF", NC_FLOAT, 2, dimids, &num_a3DDF);
    ERR;
    err = NOP (ncid, num_a3DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a3DDF, "long_name", 50,
               "num_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a3SF", NC_FLOAT, 2, dimids, &num_a3SF);
    ERR;
    err = NOP (ncid, num_a3SF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, num_a3SF, "long_name", 28, "num_a3 dust surface emission");
    ERR;
    err = NOP (ncid, num_a3SF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3SF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a3SFWET", NC_FLOAT, 2, dimids, &num_a3SFWET);
    ERR;
    err = NOP (ncid, num_a3SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a3_SRF", NC_FLOAT, 2, dimids, &num_a3_SRF);
    ERR;
    err = NOP (ncid, num_a3_SRF, "units", 5, " 1/kg");
    ERR;
    err = NOP (ncid, num_a3_SRF, "long_name", 22, "num_a3 in bottom layer");
    ERR;
    err = NOP (ncid, num_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a4DDF", NC_FLOAT, 2, dimids, &num_a4DDF);
    ERR;
    err = NOP (ncid, num_a4DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a4DDF, "long_name", 50,
               "num_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a4SFWET", NC_FLOAT, 2, dimids, &num_a4SFWET);
    ERR;
    err = NOP (ncid, num_a4SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a4_CLXF", NC_FLOAT, 2, dimids, &num_a4_CLXF);
    ERR;
    err = NOP (ncid, num_a4_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, num_a4_CLXF, "long_name", 50,
               "vertically intergrated external forcing for num_a4");
    ERR;
    err = NOP (ncid, num_a4_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a4_SRF", NC_FLOAT, 2, dimids, &num_a4_SRF);
    ERR;
    err = NOP (ncid, num_a4_SRF, "units", 5, " 1/kg");
    ERR;
    err = NOP (ncid, num_a4_SRF, "long_name", 22, "num_a4 in bottom layer");
    ERR;
    err = NOP (ncid, num_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_a4_sfgaex1", NC_FLOAT, 2, dimids, &num_a4_sfgaex1);
    ERR;
    err = NOP (ncid, num_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, num_a4_sfgaex1, "long_name", 51,
               "num_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, num_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c1DDF", NC_FLOAT, 2, dimids, &num_c1DDF);
    ERR;
    err = NOP (ncid, num_c1DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c1DDF, "long_name", 50,
               "num_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c1SFWET", NC_FLOAT, 2, dimids, &num_c1SFWET);
    ERR;
    err = NOP (ncid, num_c1SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c1SFWET, "long_name", 37, "num_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c2DDF", NC_FLOAT, 2, dimids, &num_c2DDF);
    ERR;
    err = NOP (ncid, num_c2DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c2DDF, "long_name", 50,
               "num_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c2SFWET", NC_FLOAT, 2, dimids, &num_c2SFWET);
    ERR;
    err = NOP (ncid, num_c2SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c2SFWET, "long_name", 37, "num_c2 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c3DDF", NC_FLOAT, 2, dimids, &num_c3DDF);
    ERR;
    err = NOP (ncid, num_c3DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c3DDF, "long_name", 50,
               "num_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c3SFWET", NC_FLOAT, 2, dimids, &num_c3SFWET);
    ERR;
    err = NOP (ncid, num_c3SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c3SFWET, "long_name", 37, "num_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c4DDF", NC_FLOAT, 2, dimids, &num_c4DDF);
    ERR;
    err = NOP (ncid, num_c4DDF, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c4DDF, "long_name", 50,
               "num_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, num_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "num_c4SFWET", NC_FLOAT, 2, dimids, &num_c4SFWET);
    ERR;
    err = NOP (ncid, num_c4SFWET, "units", 7, " 1/m2/s");
    ERR;
    err = NOP (ncid, num_c4SFWET, "long_name", 37, "num_c4 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, num_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = num_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a1DDF", NC_FLOAT, 2, dimids, &pom_a1DDF);
    ERR;
    err = NOP (ncid, pom_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a1DDF, "long_name", 50,
               "pom_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, pom_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a1SFWET", NC_FLOAT, 2, dimids, &pom_a1SFWET);
    ERR;
    err = NOP (ncid, pom_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, pom_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a1_SRF", NC_FLOAT, 2, dimids, &pom_a1_SRF);
    ERR;
    err = NOP (ncid, pom_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, pom_a1_SRF, "long_name", 22, "pom_a1 in bottom layer");
    ERR;
    err = NOP (ncid, pom_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a1_sfgaex1", NC_FLOAT, 2, dimids, &pom_a1_sfgaex1);
    ERR;
    err = NOP (ncid, pom_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a1_sfgaex1, "long_name", 51,
               "pom_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, pom_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a3DDF", NC_FLOAT, 2, dimids, &pom_a3DDF);
    ERR;
    err = NOP (ncid, pom_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a3DDF, "long_name", 50,
               "pom_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, pom_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a3SFWET", NC_FLOAT, 2, dimids, &pom_a3SFWET);
    ERR;
    err = NOP (ncid, pom_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, pom_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a3_SRF", NC_FLOAT, 2, dimids, &pom_a3_SRF);
    ERR;
    err = NOP (ncid, pom_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, pom_a3_SRF, "long_name", 22, "pom_a3 in bottom layer");
    ERR;
    err = NOP (ncid, pom_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a4DDF", NC_FLOAT, 2, dimids, &pom_a4DDF);
    ERR;
    err = NOP (ncid, pom_a4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a4DDF, "long_name", 50,
               "pom_a4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, pom_a4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a4SFWET", NC_FLOAT, 2, dimids, &pom_a4SFWET);
    ERR;
    err = NOP (ncid, pom_a4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a4SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, pom_a4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a4_CLXF", NC_FLOAT, 2, dimids, &pom_a4_CLXF);
    ERR;
    err = NOP (ncid, pom_a4_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, pom_a4_CLXF, "long_name", 50,
               "vertically intergrated external forcing for pom_a4");
    ERR;
    err = NOP (ncid, pom_a4_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a4_SRF", NC_FLOAT, 2, dimids, &pom_a4_SRF);
    ERR;
    err = NOP (ncid, pom_a4_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, pom_a4_SRF, "long_name", 22, "pom_a4 in bottom layer");
    ERR;
    err = NOP (ncid, pom_a4_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_a4_sfgaex1", NC_FLOAT, 2, dimids, &pom_a4_sfgaex1);
    ERR;
    err = NOP (ncid, pom_a4_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_a4_sfgaex1, "long_name", 51,
               "pom_a4 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, pom_a4_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_a4_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_c1DDF", NC_FLOAT, 2, dimids, &pom_c1DDF);
    ERR;
    err = NOP (ncid, pom_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_c1DDF, "long_name", 50,
               "pom_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, pom_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_c1SFWET", NC_FLOAT, 2, dimids, &pom_c1SFWET);
    ERR;
    err = NOP (ncid, pom_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_c1SFWET, "long_name", 37, "pom_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, pom_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_c3DDF", NC_FLOAT, 2, dimids, &pom_c3DDF);
    ERR;
    err = NOP (ncid, pom_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_c3DDF, "long_name", 50,
               "pom_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, pom_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_c3SFWET", NC_FLOAT, 2, dimids, &pom_c3SFWET);
    ERR;
    err = NOP (ncid, pom_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_c3SFWET, "long_name", 37, "pom_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, pom_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_c4DDF", NC_FLOAT, 2, dimids, &pom_c4DDF);
    ERR;
    err = NOP (ncid, pom_c4DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_c4DDF, "long_name", 50,
               "pom_c4 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, pom_c4DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c4DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "pom_c4SFWET", NC_FLOAT, 2, dimids, &pom_c4SFWET);
    ERR;
    err = NOP (ncid, pom_c4SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, pom_c4SFWET, "long_name", 37, "pom_c4 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, pom_c4SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = pom_c4SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a1DDF", NC_FLOAT, 2, dimids, &so4_a1DDF);
    ERR;
    err = NOP (ncid, so4_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a1DDF, "long_name", 50,
               "so4_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, so4_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a1SFWET", NC_FLOAT, 2, dimids, &so4_a1SFWET);
    ERR;
    err = NOP (ncid, so4_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, so4_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a1_CLXF", NC_FLOAT, 2, dimids, &so4_a1_CLXF);
    ERR;
    err = NOP (ncid, so4_a1_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, so4_a1_CLXF, "long_name", 50,
               "vertically intergrated external forcing for so4_a1");
    ERR;
    err = NOP (ncid, so4_a1_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a1_SRF", NC_FLOAT, 2, dimids, &so4_a1_SRF);
    ERR;
    err = NOP (ncid, so4_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, so4_a1_SRF, "long_name", 22, "so4_a1 in bottom layer");
    ERR;
    err = NOP (ncid, so4_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a1_sfgaex1", NC_FLOAT, 2, dimids, &so4_a1_sfgaex1);
    ERR;
    err = NOP (ncid, so4_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a1_sfgaex1, "long_name", 51,
               "so4_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, so4_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a2DDF", NC_FLOAT, 2, dimids, &so4_a2DDF);
    ERR;
    err = NOP (ncid, so4_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a2DDF, "long_name", 50,
               "so4_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, so4_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a2SFWET", NC_FLOAT, 2, dimids, &so4_a2SFWET);
    ERR;
    err = NOP (ncid, so4_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, so4_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a2_CLXF", NC_FLOAT, 2, dimids, &so4_a2_CLXF);
    ERR;
    err = NOP (ncid, so4_a2_CLXF, "units", 11, "molec/cm2/s");
    ERR;
    err = NOP (ncid, so4_a2_CLXF, "long_name", 50,
               "vertically intergrated external forcing for so4_a2");
    ERR;
    err = NOP (ncid, so4_a2_CLXF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2_CLXF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a2_SRF", NC_FLOAT, 2, dimids, &so4_a2_SRF);
    ERR;
    err = NOP (ncid, so4_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, so4_a2_SRF, "long_name", 22, "so4_a2 in bottom layer");
    ERR;
    err = NOP (ncid, so4_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a2_sfgaex1", NC_FLOAT, 2, dimids, &so4_a2_sfgaex1);
    ERR;
    err = NOP (ncid, so4_a2_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a2_sfgaex1, "long_name", 51,
               "so4_a2 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, so4_a2_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a2_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a3DDF", NC_FLOAT, 2, dimids, &so4_a3DDF);
    ERR;
    err = NOP (ncid, so4_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a3DDF, "long_name", 50,
               "so4_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, so4_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a3SFWET", NC_FLOAT, 2, dimids, &so4_a3SFWET);
    ERR;
    err = NOP (ncid, so4_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, so4_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a3_SRF", NC_FLOAT, 2, dimids, &so4_a3_SRF);
    ERR;
    err = NOP (ncid, so4_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, so4_a3_SRF, "long_name", 22, "so4_a3 in bottom layer");
    ERR;
    err = NOP (ncid, so4_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_a3_sfgaex1", NC_FLOAT, 2, dimids, &so4_a3_sfgaex1);
    ERR;
    err = NOP (ncid, so4_a3_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_a3_sfgaex1, "long_name", 51,
               "so4_a3 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, so4_a3_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_a3_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_c1DDF", NC_FLOAT, 2, dimids, &so4_c1DDF);
    ERR;
    err = NOP (ncid, so4_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_c1DDF, "long_name", 50,
               "so4_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, so4_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_c1SFWET", NC_FLOAT, 2, dimids, &so4_c1SFWET);
    ERR;
    err = NOP (ncid, so4_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_c1SFWET, "long_name", 37, "so4_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, so4_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_c2DDF", NC_FLOAT, 2, dimids, &so4_c2DDF);
    ERR;
    err = NOP (ncid, so4_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_c2DDF, "long_name", 50,
               "so4_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, so4_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_c2SFWET", NC_FLOAT, 2, dimids, &so4_c2SFWET);
    ERR;
    err = NOP (ncid, so4_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_c2SFWET, "long_name", 37, "so4_c2 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, so4_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_c3DDF", NC_FLOAT, 2, dimids, &so4_c3DDF);
    ERR;
    err = NOP (ncid, so4_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_c3DDF, "long_name", 50,
               "so4_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, so4_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "so4_c3SFWET", NC_FLOAT, 2, dimids, &so4_c3SFWET);
    ERR;
    err = NOP (ncid, so4_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, so4_c3SFWET, "long_name", 37, "so4_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, so4_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = so4_c3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a1DDF", NC_FLOAT, 2, dimids, &soa_a1DDF);
    ERR;
    err = NOP (ncid, soa_a1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a1DDF, "long_name", 50,
               "soa_a1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, soa_a1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a1SFWET", NC_FLOAT, 2, dimids, &soa_a1SFWET);
    ERR;
    err = NOP (ncid, soa_a1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a1SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, soa_a1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a1_SRF", NC_FLOAT, 2, dimids, &soa_a1_SRF);
    ERR;
    err = NOP (ncid, soa_a1_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, soa_a1_SRF, "long_name", 22, "soa_a1 in bottom layer");
    ERR;
    err = NOP (ncid, soa_a1_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a1_sfgaex1", NC_FLOAT, 2, dimids, &soa_a1_sfgaex1);
    ERR;
    err = NOP (ncid, soa_a1_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a1_sfgaex1, "long_name", 51,
               "soa_a1 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, soa_a1_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a1_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a2DDF", NC_FLOAT, 2, dimids, &soa_a2DDF);
    ERR;
    err = NOP (ncid, soa_a2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a2DDF, "long_name", 50,
               "soa_a2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, soa_a2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a2SFWET", NC_FLOAT, 2, dimids, &soa_a2SFWET);
    ERR;
    err = NOP (ncid, soa_a2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a2SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, soa_a2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a2_SRF", NC_FLOAT, 2, dimids, &soa_a2_SRF);
    ERR;
    err = NOP (ncid, soa_a2_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, soa_a2_SRF, "long_name", 22, "soa_a2 in bottom layer");
    ERR;
    err = NOP (ncid, soa_a2_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a2_sfgaex1", NC_FLOAT, 2, dimids, &soa_a2_sfgaex1);
    ERR;
    err = NOP (ncid, soa_a2_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a2_sfgaex1, "long_name", 51,
               "soa_a2 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, soa_a2_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a2_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a3DDF", NC_FLOAT, 2, dimids, &soa_a3DDF);
    ERR;
    err = NOP (ncid, soa_a3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a3DDF, "long_name", 50,
               "soa_a3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, soa_a3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a3SFWET", NC_FLOAT, 2, dimids, &soa_a3SFWET);
    ERR;
    err = NOP (ncid, soa_a3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a3SFWET, "long_name", 30, "Wet deposition flux at surface");
    ERR;
    err = NOP (ncid, soa_a3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a3_SRF", NC_FLOAT, 2, dimids, &soa_a3_SRF);
    ERR;
    err = NOP (ncid, soa_a3_SRF, "units", 5, "kg/kg");
    ERR;
    err = NOP (ncid, soa_a3_SRF, "long_name", 22, "soa_a3 in bottom layer");
    ERR;
    err = NOP (ncid, soa_a3_SRF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3_SRF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_a3_sfgaex1", NC_FLOAT, 2, dimids, &soa_a3_sfgaex1);
    ERR;
    err = NOP (ncid, soa_a3_sfgaex1, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_a3_sfgaex1, "long_name", 51,
               "soa_a3 gas-aerosol-exchange primary column tendency");
    ERR;
    err = NOP (ncid, soa_a3_sfgaex1, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_a3_sfgaex1;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_c1DDF", NC_FLOAT, 2, dimids, &soa_c1DDF);
    ERR;
    err = NOP (ncid, soa_c1DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_c1DDF, "long_name", 50,
               "soa_c1 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, soa_c1DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c1DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_c1SFWET", NC_FLOAT, 2, dimids, &soa_c1SFWET);
    ERR;
    err = NOP (ncid, soa_c1SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_c1SFWET, "long_name", 37, "soa_c1 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, soa_c1SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c1SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_c2DDF", NC_FLOAT, 2, dimids, &soa_c2DDF);
    ERR;
    err = NOP (ncid, soa_c2DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_c2DDF, "long_name", 50,
               "soa_c2 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, soa_c2DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c2DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_c2SFWET", NC_FLOAT, 2, dimids, &soa_c2SFWET);
    ERR;
    err = NOP (ncid, soa_c2SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_c2SFWET, "long_name", 37, "soa_c2 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, soa_c2SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c2SFWET;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_c3DDF", NC_FLOAT, 2, dimids, &soa_c3DDF);
    ERR;
    err = NOP (ncid, soa_c3DDF, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_c3DDF, "long_name", 50,
               "soa_c3 dry deposition flux at bottom (grav + turb)");
    ERR;
    err = NOP (ncid, soa_c3DDF, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c3DDF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "soa_c3SFWET", NC_FLOAT, 2, dimids, &soa_c3SFWET);
    ERR;
    err = NOP (ncid, soa_c3SFWET, "units", 7, "kg/m2/s");
    ERR;
    err = NOP (ncid, soa_c3SFWET, "long_name", 37, "soa_c3 wet deposition flux at surface");
    ERR;
    err = NOP (ncid, soa_c3SFWET, "cell_methods", 10, "time: mean");
    ERR;
    varids[i++] = soa_c3SFWET;

    assert (i == nvars);

fn_exit:
    return nerrs;
}

/*----< def_F_case_h1() >----------------------------------------------------*/
int def_F_case_h1_hdf5 (hid_t ncid,               /* file ID */
                        const MPI_Offset dims[2], /* dimension sizes */
                        int nvars,                /* number of variables */
                        int *varids)            /* variable IDs */
{
    /* Total 51 variables */
    int lat, lon, area, lev, hyam, hybm, P0, ilev, hyai, hybi, time, date, datesec, time_bnds,
        date_written, time_written, ndbase, nsbase, nbdate, nbsec, mdt, ndcur, nscur, co2vmr,
        ch4vmr, n2ovmr, f11vmr, f12vmr, sol_tsi, nsteph, CLDHGH, CLDLOW, CLDMED, FLNT, LWCF,
        OMEGA500, OMEGA850, PRECT, PS, SWCF, T850, TMQ, TS, U, U250, U850, UBOT, V250, V850, VBOT,
        Z500;

    int i, err, nerrs = 0, dimids[3], iattr, mdims = 1;
    int dim_ncol, dim_time, dim_nbnd, dim_chars, dim_lev, dim_ilev;

    /* global attributes: */
    iattr = 4;

    err = HDF5_PUT_ATT_INT (ncid, NC_GLOBAL, "ne", NC_INT, 1, &iattr);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, NC_GLOBAL, "np", NC_INT, 1, &iattr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "Conventions", 6, "CF-1.0");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "source", 3, "CAM");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "case", 20, "FC5AV1C-H01B_ne4_ne4");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "title", 5, "UNSET");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "logname", 6, "wkliao");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "host", 10, "compute001");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "Version", 6, "$Name$");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "revision_Id", 4, "$Id$");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, NC_GLOBAL, "initial_file", 86,
        "/home/climate1/acme/inputdata/atm/cam/inic/homme/cami_mam3_Linoz_ne4np4_L72_c160909.nc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (
        ncid, NC_GLOBAL, "topography_file", 79,
        "/home/climate1/acme/inputdata/atm/cam/topo/USGS-gtopo30_ne4np4_16x.c20160612.nc");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, NC_GLOBAL, "time_period_freq", 6, "hour_2");
    ERR;

    /* define dimensions */
    err = hdf5_def_dim (ncid, "ncol", dims[1], &dim_ncol);
    ERR;
    err = hdf5_def_dim (ncid, "time", NC_UNLIMITED, &dim_time);
    ERR;
    err = hdf5_def_dim (ncid, "nbnd", 2, &dim_nbnd);
    ERR;
    err = hdf5_def_dim (ncid, "chars", 8, &dim_chars);
    ERR;
    err = hdf5_def_dim (ncid, "lev", dims[0], &dim_lev);
    ERR;
    err = hdf5_def_dim (ncid, "ilev", dims[0] + 1, &dim_ilev);
    ERR;

    i = 0;

    /* define variables */
    dimids[0] = dim_ncol;
    err       = hdf5_def_var (ncid, "lat", NC_DOUBLE, 1, dimids, &lat);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lat, "long_name", 8, "latitude");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lat, "units", 13, "degrees_north");
    ERR;
    varids[i++] = lat;

    dimids[0] = dim_ncol;
    err       = hdf5_def_var (ncid, "lon", NC_DOUBLE, 1, dimids, &lon);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lon, "long_name", 9, "longitude");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lon, "units", 12, "degrees_east");
    ERR;
    varids[i++] = lon;

    dimids[0] = dim_ncol;
    err       = hdf5_def_var (ncid, "area", NC_DOUBLE, 1, dimids, &area);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, area, "long_name", 14, "gll grid areas");
    ERR;
    varids[i++] = area;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "lev", NC_DOUBLE, 1, dimids, &lev);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "long_name", 38, "hybrid level at midpoints (1000*(A+B))");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "units", 3, "hPa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "positive", 4, "down");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "standard_name", 43,
                             "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, lev, "formula_terms", 29, "a: hyam b: hybm p0: P0 ps: PS");
    ERR;
    varids[i++] = lev;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "hyam", NC_DOUBLE, 1, dimids, &hyam);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hyam, "long_name", 39, "hybrid A coefficient at layer midpoints");
    ERR;
    varids[i++] = hyam;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "hybm", NC_DOUBLE, 1, dimids, &hybm);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hybm, "long_name", 39, "hybrid B coefficient at layer midpoints");
    ERR;
    varids[i++] = hybm;

    dimids[0] = dim_lev;
    err       = hdf5_def_var (ncid, "P0", NC_DOUBLE, 0, NULL, &P0);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, P0, "long_name", 18, "reference pressure");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, P0, "units", 2, "Pa");
    ERR;
    varids[i++] = P0;

    dimids[0] = dim_ilev;
    err       = hdf5_def_var (ncid, "ilev", NC_DOUBLE, 1, dimids, &ilev);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, ilev, "long_name", 39, "hybrid level at interfaces (1000*(A+B))");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "units", 3, "hPa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "positive", 4, "down");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "standard_name", 43,
                             "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ilev, "formula_terms", 29, "a: hyai b: hybi p0: P0 ps: PS");
    ERR;
    varids[i++] = ilev;

    dimids[0] = dim_ilev;
    err       = hdf5_def_var (ncid, "hyai", NC_DOUBLE, 1, dimids, &hyai);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hyai, "long_name", 40, "hybrid A coefficient at layer interfaces");
    ERR;
    varids[i++] = hyai;

    dimids[0] = dim_ilev;
    err       = hdf5_def_var (ncid, "hybi", NC_DOUBLE, 1, dimids, &hybi);
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, hybi, "long_name", 40, "hybrid B coefficient at layer interfaces");
    ERR;
    varids[i++] = hybi;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "time", NC_DOUBLE, 1, dimids, &time);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "long_name", 4, "time");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "units", 30, "days since 0001-01-01 00:00:00");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "calendar", 6, "noleap");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time, "bounds", 9, "time_bnds");
    ERR;
    varids[i++] = time;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "date", NC_INT, 1, dimids, &date);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, date, "long_name", 23, "current date (YYYYMMDD)");
    ERR;
    varids[i++] = date;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "datesec", NC_INT, 1, dimids, &datesec);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, datesec, "long_name", 31, "current seconds of current date");
    ERR;
    varids[i++] = datesec;

    dimids[0] = dim_time;
    dimids[1] = dim_nbnd;
    err       = hdf5_def_var (ncid, "time_bnds", NC_DOUBLE, 2, dimids, &time_bnds);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, time_bnds, "long_name", 23, "time interval endpoints");
    ERR;
    varids[i++] = time_bnds;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = hdf5_def_var (ncid, "date_written", NC_CHAR, 2, dimids, &date_written);
    ERR;
    varids[i++] = date_written;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = hdf5_def_var (ncid, "time_written", NC_CHAR, 2, dimids, &time_written);
    ERR;
    varids[i++] = time_written;

    err = hdf5_def_var (ncid, "ndbase", NC_INT, 0, NULL, &ndbase);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ndbase, "long_name", 8, "base day");
    ERR;
    varids[i++] = ndbase;
    err         = hdf5_def_var (ncid, "nsbase", NC_INT, 0, NULL, &nsbase);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nsbase, "long_name", 19, "seconds of base day");
    ERR;
    varids[i++] = nsbase;

    err = hdf5_def_var (ncid, "nbdate", NC_INT, 0, NULL, &nbdate);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nbdate, "long_name", 20, "base date (YYYYMMDD)");
    ERR;
    varids[i++] = nbdate;

    err = hdf5_def_var (ncid, "nbsec", NC_INT, 0, NULL, &nbsec);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nbsec, "long_name", 20, "seconds of base date");
    ERR;
    varids[i++] = nbsec;

    err = hdf5_def_var (ncid, "mdt", NC_INT, 0, NULL, &mdt);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mdt, "long_name", 8, "timestep");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, mdt, "units", 1, "s");
    ERR;
    varids[i++] = mdt;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "ndcur", NC_INT, 1, dimids, &ndcur);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ndcur, "long_name", 27, "current day (from base day)");
    ERR;
    varids[i++] = ndcur;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "nscur", NC_INT, 1, dimids, &nscur);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nscur, "long_name", 30, "current seconds of current day");
    ERR;
    varids[i++] = nscur;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "co2vmr", NC_DOUBLE, 1, dimids, &co2vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, co2vmr, "long_name", 23, "co2 volume mixing ratio");
    ERR;
    varids[i++] = co2vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "ch4vmr", NC_DOUBLE, 1, dimids, &ch4vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, ch4vmr, "long_name", 23, "ch4 volume mixing ratio");
    ERR;
    varids[i++] = ch4vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "n2ovmr", NC_DOUBLE, 1, dimids, &n2ovmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, n2ovmr, "long_name", 23, "n2o volume mixing ratio");
    ERR;
    varids[i++] = n2ovmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "f11vmr", NC_DOUBLE, 1, dimids, &f11vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, f11vmr, "long_name", 23, "f11 volume mixing ratio");
    ERR;
    varids[i++] = f11vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "f12vmr", NC_DOUBLE, 1, dimids, &f12vmr);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, f12vmr, "long_name", 23, "f12 volume mixing ratio");
    ERR;
    varids[i++] = f12vmr;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "sol_tsi", NC_DOUBLE, 1, dimids, &sol_tsi);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, sol_tsi, "long_name", 22, "total solar irradiance");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, sol_tsi, "units", 4, "W/m2");
    ERR;
    varids[i++] = sol_tsi;

    dimids[0] = dim_time;
    err       = hdf5_def_var (ncid, "nsteph", NC_INT, 1, dimids, &nsteph);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, nsteph, "long_name", 16, "current timestep");
    ERR;
    varids[i++] = nsteph;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDHGH", NC_FLOAT, 2, dimids, &CLDHGH);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDHGH, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDHGH, "long_name", 32, "Vertically-integrated high cloud");
    ERR;
    varids[i++] = CLDHGH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDLOW", NC_FLOAT, 2, dimids, &CLDLOW);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDLOW, "units", 8, "fraction");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDLOW, "long_name", 31, "Vertically-integrated low cloud");
    ERR;
    varids[i++] = CLDLOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "CLDMED", NC_FLOAT, 2, dimids, &CLDMED);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, CLDMED, "units", 8, "fraction");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, CLDMED, "long_name", 37, "Vertically-integrated mid-level cloud");
    ERR;
    varids[i++] = CLDMED;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "FLNT", NC_FLOAT, 2, dimids, &FLNT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNT, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, FLNT, "long_name", 33, "Net longwave flux at top of model");
    ERR;
    varids[i++] = FLNT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "LWCF", NC_FLOAT, 2, dimids, &LWCF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LWCF, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, LWCF, "long_name", 22, "Longwave cloud forcing");
    ERR;
    varids[i++] = LWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "OMEGA500", NC_FLOAT, 2, dimids, &OMEGA500);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA500, "units", 4, "Pa/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA500, "long_name", 46,
                             "Vertical velocity at 500 mbar pressure surface");
    ERR;
    varids[i++] = OMEGA500;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "OMEGA850", NC_FLOAT, 2, dimids, &OMEGA850);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA850, "units", 4, "Pa/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, OMEGA850, "long_name", 46,
                             "Vertical velocity at 850 mbar pressure surface");
    ERR;
    varids[i++] = OMEGA850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PRECT", NC_FLOAT, 2, dimids, &PRECT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECT, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PRECT, "long_name", 65,
                             "Total (convective and large-scale) precipitation rate (liq + ice)");
    ERR;
    varids[i++] = PRECT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "PS", NC_FLOAT, 2, dimids, &PS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PS, "units", 2, "Pa");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, PS, "long_name", 16, "Surface pressure");
    ERR;
    varids[i++] = PS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "SWCF", NC_FLOAT, 2, dimids, &SWCF);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SWCF, "units", 4, "W/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, SWCF, "long_name", 23, "Shortwave cloud forcing");
    ERR;
    varids[i++] = SWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "T850", NC_FLOAT, 2, dimids, &T850);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, T850, "units", 1, "K");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, T850, "long_name", 40, "Temperature at 850 mbar pressure surface");
    ERR;
    varids[i++] = T850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TMQ", NC_FLOAT, 2, dimids, &TMQ);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TMQ, "units", 5, "kg/m2");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TMQ, "long_name", 48,
                             "Total (vertically integrated) precipitable water");
    ERR;
    varids[i++] = TMQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "TS", NC_FLOAT, 2, dimids, &TS);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TS, "units", 1, "K");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, TS, "long_name", 31, "Surface temperature (radiative)");
    ERR;
    varids[i++] = TS;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = hdf5_def_var (ncid, "U", NC_FLOAT, 3, dimids, &U);
    ERR;
    err = HDF5_PUT_ATT_INT (ncid, U, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U, "long_name", 10, "Zonal wind");
    ERR;
    varids[i++] = U;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "U250", NC_FLOAT, 2, dimids, &U250);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U250, "units", 3, "m/s");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, U250, "long_name", 39, "Zonal wind at 250 mbar pressure surface");
    ERR;
    varids[i++] = U250;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "U850", NC_FLOAT, 2, dimids, &U850);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, U850, "units", 3, "m/s");
    ERR;
    err =
        HDF5_PUT_ATT_TEXT (ncid, U850, "long_name", 39, "Zonal wind at 850 mbar pressure surface");
    ERR;
    varids[i++] = U850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "UBOT", NC_FLOAT, 2, dimids, &UBOT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, UBOT, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, UBOT, "long_name", 29, "Lowest model level zonal wind");
    ERR;
    varids[i++] = UBOT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "V250", NC_FLOAT, 2, dimids, &V250);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, V250, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, V250, "long_name", 44,
                             "Meridional wind at 250 mbar pressure surface");
    ERR;
    varids[i++] = V250;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "V850", NC_FLOAT, 2, dimids, &V850);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, V850, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, V850, "long_name", 44,
                             "Meridional wind at 850 mbar pressure surface");
    ERR;
    varids[i++] = V850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "VBOT", NC_FLOAT, 2, dimids, &VBOT);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VBOT, "units", 3, "m/s");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, VBOT, "long_name", 34, "Lowest model level meridional wind");
    ERR;
    varids[i++] = VBOT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = hdf5_def_var (ncid, "Z500", NC_FLOAT, 2, dimids, &Z500);
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Z500, "units", 1, "m");
    ERR;
    err = HDF5_PUT_ATT_TEXT (ncid, Z500, "long_name", 43,
                             "Geopotential Z at 500 mbar pressure surface");
    ERR;
    varids[i++] = Z500;

    assert (i == nvars);

fn_exit:
    return nerrs;
}

/*----< inq_F_case_h1() >----------------------------------------------------*/
int inq_F_case_h1_hdf5 (hid_t ncid,         /* file ID */
                        MPI_Offset dims[2], /* dimension sizes */
                        int nvars,          /* number of variables */
                        int *varids)      /* variable IDs */
{
    /* Total 51 variables */
    int lat, lon, area, lev, hyam, hybm, P0, ilev, hyai, hybi, time, date, datesec, time_bnds,
        date_written, time_written, ndbase, nsbase, nbdate, nbsec, mdt, ndcur, nscur, co2vmr,
        ch4vmr, n2ovmr, f11vmr, f12vmr, sol_tsi, nsteph, CLDHGH, CLDLOW, CLDMED, FLNT, LWCF,
        OMEGA500, OMEGA850, PRECT, PS, SWCF, T850, TMQ, TS, U, U250, U850, UBOT, V250, V850, VBOT,
        Z500;

    int i, err, nerrs = 0, dimids[3], iattr, mdims = 1;
    int dim_ncol, dim_time, dim_nbnd, dim_chars, dim_lev, dim_ilev;

    /* global attributes: */
    iattr = 4;
    err   = NOP2 (ncid, NC_GLOBAL, "ne", NC_INT, 1, &iattr);
    ERR;
    err = NOP2 (ncid, NC_GLOBAL, "np", NC_INT, 1, &iattr);
    ERR;
    err = NOP (ncid, NC_GLOBAL, "Conventions", 6, "CF-1.0");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "source", 3, "CAM");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "case", 20, "FC5AV1C-H01B_ne4_ne4");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "title", 5, "UNSET");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "logname", 6, "wkliao");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "host", 10, "compute001");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "Version", 6, "$Name$");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "revision_Id", 4, "$Id$");
    ERR;
    err = NOP (
        ncid, NC_GLOBAL, "initial_file", 86,
        "/home/climate1/acme/inputdata/atm/cam/inic/homme/cami_mam3_Linoz_ne4np4_L72_c160909.nc");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "topography_file", 79,
               "/home/climate1/acme/inputdata/atm/cam/topo/USGS-gtopo30_ne4np4_16x.c20160612.nc");
    ERR;
    err = NOP (ncid, NC_GLOBAL, "time_period_freq", 6, "hour_2");
    ERR;

    /* inquery dimensions */
    err = hdf5_inq_dimid (ncid, "ncol", &dim_ncol);
    ERR;
    // err = hdf5_inq_dimid(ncid, "time", &dim_time); ERR;
    // err = hdf5_inq_dimid(ncid, "nbnd", &dim_nbnd); ERR;
    // err = hdf5_inq_dimid(ncid, "chars", &dim_chars); ERR;
    err = hdf5_inq_dimid (ncid, "lev", &dim_lev);
    ERR;
    // err = hdf5_inq_dimid(ncid, "ilev", &dim_ilev); ERR;

    err = hdf5_inq_dimlen (ncid, dim_ncol, dims + 1);
    ERR;
    err = hdf5_inq_dimlen (ncid, dim_lev, dims);
    ERR;
    /*
    err = hdf5_def_dim(ncid, "ncol", dims[1],      &dim_ncol); ERR;
    err = hdf5_def_dim(ncid, "time", NC_UNLIMITED, &dim_time); ERR;
    err = hdf5_def_dim(ncid, "nbnd",  2,           &dim_nbnd); ERR;
    err = hdf5_def_dim(ncid, "chars", 8,           &dim_chars); ERR;
    err = hdf5_def_dim(ncid, "lev",   dims[0],     &dim_lev); ERR;
    err = hdf5_def_dim(ncid, "ilev",  dims[0]+1,   &dim_ilev); ERR;
    */

    i = 0;

    /* define variables */
    dimids[0] = dim_ncol;
    err       = INQ_VID (ncid, "lat", NC_DOUBLE, 1, dimids, &lat);
    ERR;
    err = NOP (ncid, lat, "long_name", 8, "latitude");
    ERR;
    err = NOP (ncid, lat, "units", 13, "degrees_north");
    ERR;
    varids[i++] = lat;

    dimids[0] = dim_ncol;
    err       = INQ_VID (ncid, "lon", NC_DOUBLE, 1, dimids, &lon);
    ERR;
    err = NOP (ncid, lon, "long_name", 9, "longitude");
    ERR;
    err = NOP (ncid, lon, "units", 12, "degrees_east");
    ERR;
    varids[i++] = lon;

    dimids[0] = dim_ncol;
    err       = INQ_VID (ncid, "area", NC_DOUBLE, 1, dimids, &area);
    ERR;
    err = NOP (ncid, area, "long_name", 14, "gll grid areas");
    ERR;
    varids[i++] = area;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "lev", NC_DOUBLE, 1, dimids, &lev);
    ERR;
    err = NOP (ncid, lev, "long_name", 38, "hybrid level at midpoints (1000*(A+B))");
    ERR;
    err = NOP (ncid, lev, "units", 3, "hPa");
    ERR;
    err = NOP (ncid, lev, "positive", 4, "down");
    ERR;
    err = NOP (ncid, lev, "standard_name", 43, "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = NOP (ncid, lev, "formula_terms", 29, "a: hyam b: hybm p0: P0 ps: PS");
    ERR;
    varids[i++] = lev;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "hyam", NC_DOUBLE, 1, dimids, &hyam);
    ERR;
    err = NOP (ncid, hyam, "long_name", 39, "hybrid A coefficient at layer midpoints");
    ERR;
    varids[i++] = hyam;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "hybm", NC_DOUBLE, 1, dimids, &hybm);
    ERR;
    err = NOP (ncid, hybm, "long_name", 39, "hybrid B coefficient at layer midpoints");
    ERR;
    varids[i++] = hybm;

    dimids[0] = dim_lev;
    err       = INQ_VID (ncid, "P0", NC_DOUBLE, 0, NULL, &P0);
    ERR;
    err = NOP (ncid, P0, "long_name", 18, "reference pressure");
    ERR;
    err = NOP (ncid, P0, "units", 2, "Pa");
    ERR;
    varids[i++] = P0;

    dimids[0] = dim_ilev;
    err       = INQ_VID (ncid, "ilev", NC_DOUBLE, 1, dimids, &ilev);
    ERR;
    err = NOP (ncid, ilev, "long_name", 39, "hybrid level at interfaces (1000*(A+B))");
    ERR;
    err = NOP (ncid, ilev, "units", 3, "hPa");
    ERR;
    err = NOP (ncid, ilev, "positive", 4, "down");
    ERR;
    err = NOP (ncid, ilev, "standard_name", 43, "atmosphere_hybrid_sigma_pressure_coordinate");
    ERR;
    err = NOP (ncid, ilev, "formula_terms", 29, "a: hyai b: hybi p0: P0 ps: PS");
    ERR;
    varids[i++] = ilev;

    dimids[0] = dim_ilev;
    err       = INQ_VID (ncid, "hyai", NC_DOUBLE, 1, dimids, &hyai);
    ERR;
    err = NOP (ncid, hyai, "long_name", 40, "hybrid A coefficient at layer interfaces");
    ERR;
    varids[i++] = hyai;

    dimids[0] = dim_ilev;
    err       = INQ_VID (ncid, "hybi", NC_DOUBLE, 1, dimids, &hybi);
    ERR;
    err = NOP (ncid, hybi, "long_name", 40, "hybrid B coefficient at layer interfaces");
    ERR;
    varids[i++] = hybi;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "time", NC_DOUBLE, 1, dimids, &time);
    ERR;
    err = NOP (ncid, time, "long_name", 4, "time");
    ERR;
    err = NOP (ncid, time, "units", 30, "days since 0001-01-01 00:00:00");
    ERR;
    err = NOP (ncid, time, "calendar", 6, "noleap");
    ERR;
    err = NOP (ncid, time, "bounds", 9, "time_bnds");
    ERR;
    varids[i++] = time;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "date", NC_INT, 1, dimids, &date);
    ERR;
    err = NOP (ncid, date, "long_name", 23, "current date (YYYYMMDD)");
    ERR;
    varids[i++] = date;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "datesec", NC_INT, 1, dimids, &datesec);
    ERR;
    err = NOP (ncid, datesec, "long_name", 31, "current seconds of current date");
    ERR;
    varids[i++] = datesec;

    dimids[0] = dim_time;
    dimids[1] = dim_nbnd;
    err       = INQ_VID (ncid, "time_bnds", NC_DOUBLE, 2, dimids, &time_bnds);
    ERR;
    err = NOP (ncid, time_bnds, "long_name", 23, "time interval endpoints");
    ERR;
    varids[i++] = time_bnds;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = INQ_VID (ncid, "date_written", NC_CHAR, 2, dimids, &date_written);
    ERR;
    varids[i++] = date_written;

    dimids[0] = dim_time;
    dimids[1] = dim_chars;
    err       = INQ_VID (ncid, "time_written", NC_CHAR, 2, dimids, &time_written);
    ERR;
    varids[i++] = time_written;

    err = INQ_VID (ncid, "ndbase", NC_INT, 0, NULL, &ndbase);
    ERR;
    err = NOP (ncid, ndbase, "long_name", 8, "base day");
    ERR;
    varids[i++] = ndbase;
    err         = INQ_VID (ncid, "nsbase", NC_INT, 0, NULL, &nsbase);
    ERR;
    err = NOP (ncid, nsbase, "long_name", 19, "seconds of base day");
    ERR;
    varids[i++] = nsbase;

    err = INQ_VID (ncid, "nbdate", NC_INT, 0, NULL, &nbdate);
    ERR;
    err = NOP (ncid, nbdate, "long_name", 20, "base date (YYYYMMDD)");
    ERR;
    varids[i++] = nbdate;

    err = INQ_VID (ncid, "nbsec", NC_INT, 0, NULL, &nbsec);
    ERR;
    err = NOP (ncid, nbsec, "long_name", 20, "seconds of base date");
    ERR;
    varids[i++] = nbsec;

    err = INQ_VID (ncid, "mdt", NC_INT, 0, NULL, &mdt);
    ERR;
    err = NOP (ncid, mdt, "long_name", 8, "timestep");
    ERR;
    err = NOP (ncid, mdt, "units", 1, "s");
    ERR;
    varids[i++] = mdt;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "ndcur", NC_INT, 1, dimids, &ndcur);
    ERR;
    err = NOP (ncid, ndcur, "long_name", 27, "current day (from base day)");
    ERR;
    varids[i++] = ndcur;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "nscur", NC_INT, 1, dimids, &nscur);
    ERR;
    err = NOP (ncid, nscur, "long_name", 30, "current seconds of current day");
    ERR;
    varids[i++] = nscur;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "co2vmr", NC_DOUBLE, 1, dimids, &co2vmr);
    ERR;
    err = NOP (ncid, co2vmr, "long_name", 23, "co2 volume mixing ratio");
    ERR;
    varids[i++] = co2vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "ch4vmr", NC_DOUBLE, 1, dimids, &ch4vmr);
    ERR;
    err = NOP (ncid, ch4vmr, "long_name", 23, "ch4 volume mixing ratio");
    ERR;
    varids[i++] = ch4vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "n2ovmr", NC_DOUBLE, 1, dimids, &n2ovmr);
    ERR;
    err = NOP (ncid, n2ovmr, "long_name", 23, "n2o volume mixing ratio");
    ERR;
    varids[i++] = n2ovmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "f11vmr", NC_DOUBLE, 1, dimids, &f11vmr);
    ERR;
    err = NOP (ncid, f11vmr, "long_name", 23, "f11 volume mixing ratio");
    ERR;
    varids[i++] = f11vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "f12vmr", NC_DOUBLE, 1, dimids, &f12vmr);
    ERR;
    err = NOP (ncid, f12vmr, "long_name", 23, "f12 volume mixing ratio");
    ERR;
    varids[i++] = f12vmr;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "sol_tsi", NC_DOUBLE, 1, dimids, &sol_tsi);
    ERR;
    err = NOP (ncid, sol_tsi, "long_name", 22, "total solar irradiance");
    ERR;
    err = NOP (ncid, sol_tsi, "units", 4, "W/m2");
    ERR;
    varids[i++] = sol_tsi;

    dimids[0] = dim_time;
    err       = INQ_VID (ncid, "nsteph", NC_INT, 1, dimids, &nsteph);
    ERR;
    err = NOP (ncid, nsteph, "long_name", 16, "current timestep");
    ERR;
    varids[i++] = nsteph;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CLDHGH", NC_FLOAT, 2, dimids, &CLDHGH);
    ERR;
    err = NOP (ncid, CLDHGH, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLDHGH, "long_name", 32, "Vertically-integrated high cloud");
    ERR;
    varids[i++] = CLDHGH;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CLDLOW", NC_FLOAT, 2, dimids, &CLDLOW);
    ERR;
    err = NOP (ncid, CLDLOW, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLDLOW, "long_name", 31, "Vertically-integrated low cloud");
    ERR;
    varids[i++] = CLDLOW;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "CLDMED", NC_FLOAT, 2, dimids, &CLDMED);
    ERR;
    err = NOP (ncid, CLDMED, "units", 8, "fraction");
    ERR;
    err = NOP (ncid, CLDMED, "long_name", 37, "Vertically-integrated mid-level cloud");
    ERR;
    varids[i++] = CLDMED;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "FLNT", NC_FLOAT, 2, dimids, &FLNT);
    ERR;
    err = NOP (ncid, FLNT, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, FLNT, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, FLNT, "long_name", 33, "Net longwave flux at top of model");
    ERR;
    varids[i++] = FLNT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "LWCF", NC_FLOAT, 2, dimids, &LWCF);
    ERR;
    err = NOP (ncid, LWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, LWCF, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, LWCF, "long_name", 22, "Longwave cloud forcing");
    ERR;
    varids[i++] = LWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "OMEGA500", NC_FLOAT, 2, dimids, &OMEGA500);
    ERR;
    err = NOP (ncid, OMEGA500, "units", 4, "Pa/s");
    ERR;
    err = NOP (ncid, OMEGA500, "long_name", 46, "Vertical velocity at 500 mbar pressure surface");
    ERR;
    varids[i++] = OMEGA500;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "OMEGA850", NC_FLOAT, 2, dimids, &OMEGA850);
    ERR;
    err = NOP (ncid, OMEGA850, "units", 4, "Pa/s");
    ERR;
    err = NOP (ncid, OMEGA850, "long_name", 46, "Vertical velocity at 850 mbar pressure surface");
    ERR;
    varids[i++] = OMEGA850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PRECT", NC_FLOAT, 2, dimids, &PRECT);
    ERR;
    err = NOP (ncid, PRECT, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, PRECT, "long_name", 65,
               "Total (convective and large-scale) precipitation rate (liq + ice)");
    ERR;
    varids[i++] = PRECT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "PS", NC_FLOAT, 2, dimids, &PS);
    ERR;
    err = NOP (ncid, PS, "units", 2, "Pa");
    ERR;
    err = NOP (ncid, PS, "long_name", 16, "Surface pressure");
    ERR;
    varids[i++] = PS;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "SWCF", NC_FLOAT, 2, dimids, &SWCF);
    ERR;
    err = NOP (ncid, SWCF, "Sampling_Sequence", 8, "rad_lwsw");
    ERR;
    err = NOP (ncid, SWCF, "units", 4, "W/m2");
    ERR;
    err = NOP (ncid, SWCF, "long_name", 23, "Shortwave cloud forcing");
    ERR;
    varids[i++] = SWCF;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "T850", NC_FLOAT, 2, dimids, &T850);
    ERR;
    err = NOP (ncid, T850, "units", 1, "K");
    ERR;
    err = NOP (ncid, T850, "long_name", 40, "Temperature at 850 mbar pressure surface");
    ERR;
    varids[i++] = T850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TMQ", NC_FLOAT, 2, dimids, &TMQ);
    ERR;
    err = NOP (ncid, TMQ, "units", 5, "kg/m2");
    ERR;
    err = NOP (ncid, TMQ, "long_name", 48, "Total (vertically integrated) precipitable water");
    ERR;
    varids[i++] = TMQ;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "TS", NC_FLOAT, 2, dimids, &TS);
    ERR;
    err = NOP (ncid, TS, "units", 1, "K");
    ERR;
    err = NOP (ncid, TS, "long_name", 31, "Surface temperature (radiative)");
    ERR;
    varids[i++] = TS;

    dimids[0] = dim_time;
    dimids[1] = dim_lev;
    dimids[2] = dim_ncol;
    err       = INQ_VID (ncid, "U", NC_FLOAT, 3, dimids, &U);
    ERR;
    err = NOP2 (ncid, U, "mdims", NC_INT, 1, &mdims);
    ERR;
    err = NOP (ncid, U, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, U, "long_name", 10, "Zonal wind");
    ERR;
    varids[i++] = U;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "U250", NC_FLOAT, 2, dimids, &U250);
    ERR;
    err = NOP (ncid, U250, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, U250, "long_name", 39, "Zonal wind at 250 mbar pressure surface");
    ERR;
    varids[i++] = U250;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "U850", NC_FLOAT, 2, dimids, &U850);
    ERR;
    err = NOP (ncid, U850, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, U850, "long_name", 39, "Zonal wind at 850 mbar pressure surface");
    ERR;
    varids[i++] = U850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "UBOT", NC_FLOAT, 2, dimids, &UBOT);
    ERR;
    err = NOP (ncid, UBOT, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, UBOT, "long_name", 29, "Lowest model level zonal wind");
    ERR;
    varids[i++] = UBOT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "V250", NC_FLOAT, 2, dimids, &V250);
    ERR;
    err = NOP (ncid, V250, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, V250, "long_name", 44, "Meridional wind at 250 mbar pressure surface");
    ERR;
    varids[i++] = V250;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "V850", NC_FLOAT, 2, dimids, &V850);
    ERR;
    err = NOP (ncid, V850, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, V850, "long_name", 44, "Meridional wind at 850 mbar pressure surface");
    ERR;
    varids[i++] = V850;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "VBOT", NC_FLOAT, 2, dimids, &VBOT);
    ERR;
    err = NOP (ncid, VBOT, "units", 3, "m/s");
    ERR;
    err = NOP (ncid, VBOT, "long_name", 34, "Lowest model level meridional wind");
    ERR;
    varids[i++] = VBOT;

    dimids[0] = dim_time;
    dimids[1] = dim_ncol;
    err       = INQ_VID (ncid, "Z500", NC_FLOAT, 2, dimids, &Z500);
    ERR;
    err = NOP (ncid, Z500, "units", 1, "m");
    ERR;
    err = NOP (ncid, Z500, "long_name", 43, "Geopotential Z at 500 mbar pressure surface");
    ERR;
    varids[i++] = Z500;

    assert (i == nvars);

fn_exit:
    return nerrs;
}
#pragma once

#include <hdf5.h>
#include <pnetcdf.h>

#include "e3sm_io.h"

#ifdef ENABLE_LOGVOL
#include "logvol.h"
#endif

extern hid_t dxplid_coll;
extern hid_t dxplid_indep;

extern hid_t f_dids[1048576];

#define CHECK_HERR HERR
#define CHECK_ERR  NCERR

#define NCERR                                                         \
    {                                                                 \
        if (err != 0) {                                               \
            printf ("Error at line %d in %s:\n", __LINE__, __FILE__); \
            goto fn_exit;                                             \
        }                                                             \
    }

#define HERR                                                          \
    {                                                                 \
        if (herr != 0) {                                              \
            printf ("Error at line %d in %s:\n", __LINE__, __FILE__); \
            H5Eprint1 (stdout);                                       \
            goto fn_exit;                                             \
        }                                                             \
    }

#define CHECK_HID(A)                                                  \
    {                                                                 \
        if (A < 0) {                                                  \
            printf ("Error at line %d in %s:\n", __LINE__, __FILE__); \
            H5Eprint1 (stdout);                                       \
            herr = -1;                                                \
            goto fn_exit;                                             \
        }                                                             \
    }

#ifdef _DOUBLE_TYPE_
#define REC_H5TYPE H5T_NATIVE_DOUBLE
#else
#define REC_H5TYPE H5T_NATIVE_FLOAT
#endif

// PUT

// VAR

#define HDF5_PUT_VAR_DOUBLE(A, B, C) \
    H5Dwrite (f_dids[B], H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, dxplid_indep, C);
#define HDF5_PUT_VAR_FLOAT(A, B, C) \
    H5Dwrite (f_dids[B], H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, dxplid_indep, C);
#define HDF5_PUT_VAR_INT(A, B, C)  H5Dwrite (f_dids[B], H5T_NATIVE_INT, H5S_ALL, H5S_ALL, dxplid_indep, C);
#define HDF5_PUT_VAR_TEXT(A, B, C) H5Dwrite (f_dids[B], H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, dxplid_indep, C);

#define HDF5_PUT_VAR_DOUBLE_ALL(A, B, C) \
    H5Dwrite (f_dids[B], H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, dxplid_coll, C);
#define HDF5_PUT_VAR_FLOAT_ALL(A, B, C) \
    H5Dwrite (f_dids[B], H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, dxplid_coll, C);
#define HDF5_PUT_VAR_INT_ALL(A, B, C) \
    H5Dwrite (f_dids[B], H5T_NATIVE_INT, H5S_ALL, H5S_ALL, dxplid_coll, C);
#define HDF5_PUT_VAR_TEXT_ALL(A, B, C) \
    H5Dwrite (f_dids[B], H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, dxplid_coll, C);

#define HDF5_IPUT_VAR_DOUBLE(A, B, C, D) HDF5_PUT_VAR_DOUBLE (A, B, C)
#define HDF5_IPUT_VAR_FLOAT(A, B, C, D)  HDF5_PUT_VAR_FLOAT (A, B, C)
#define HDF5_IPUT_VAR_INT(A, B, C, D)    HDF5_PUT_VAR_INT (A, B, C)
#define HDF5_IPUT_VAR_TEXT(A, B, C, D)   HDF5_PUT_VAR_TEXT (A, B, C)

// VARA

#define HDF5_PUT_VARA_DOUBLE(A, B, C, D, E) \
    hdf5_put_vara (B, H5T_NATIVE_DOUBLE, dxplid_indep, C, D, E);
#define HDF5_PUT_VARA_FLOAT(A, B, C, D, E) \
    hdf5_put_vara (B, H5T_NATIVE_FLOAT, dxplid_indep, C, D, E);
#define HDF5_PUT_VARA_INT(A, B, C, D, E)  hdf5_put_vara (B, H5T_NATIVE_INT, dxplid_indep, C, D, E);
#define HDF5_PUT_VARA_TEXT(A, B, C, D, E) hdf5_put_vara (B, H5T_NATIVE_CHAR, dxplid_indep, C, D, E);

#define HDF5_PUT_VARA_DOUBLE_ALL(A, B, C, D, E) \
    hdf5_put_vara (B, H5T_NATIVE_DOUBLE, dxplid_indep, C, D, E);
#define HDF5_PUT_VARA_FLOAT_ALL(A, B, C, D, E) \
    hdf5_put_vara (B, H5T_NATIVE_FLOAT, dxplid_indep, C, D, E);
#define HDF5_PUT_VARA_INT_ALL(A, B, C, D, E) \
    hdf5_put_vara (B, H5T_NATIVE_INT, dxplid_indep, C, D, E);
#define HDF5_PUT_VARA_TEXT_ALL(A, B, C, D, E) \
    hdf5_put_vara (B, H5T_NATIVE_CHAR, dxplid_indep, C, D, E);

#define HDF5_IPUT_VARA_DOUBLE(A, B, C, D, E, F) HDF5_PUT_VARA_DOUBLE (A, B, C, D, E)
#define HDF5_IPUT_VARA_FLOAT(A, B, C, D, E, F)  HDF5_PUT_VARA_FLOAT (A, B, C, D, E)
#define HDF5_IPUT_VARA_INT(A, B, C, D, E, F)    HDF5_PUT_VARA_INT (A, B, C, D, E)
#define HDF5_IPUT_VARA_TEXT(A, B, C, D, E, F)   HDF5_PUT_VARA_TEXT (A, B, C, D, E)

// VAR1

#define HDF5_PUT_VAR1_DOUBLE(A, B, C, D) hdf5_put_var1 (B, H5T_NATIVE_DOUBLE, dxplid_indep, C, D);
#define HDF5_PUT_VAR1_FLOAT(A, B, C, D)  hdf5_put_var1 (B, H5T_NATIVE_FLOAT, dxplid_indep, C, D);
#define HDF5_PUT_VAR1_INT(A, B, C, D)    hdf5_put_var1 (B, H5T_NATIVE_INT, dxplid_indep, C, D);
#define HDF5_PUT_VAR1_TEXT(A, B, C, D)   hdf5_put_var1 (B, H5T_NATIVE_CHAR, dxplid_indep, C, D);

#define HDF5_PUT_VAR1_DOUBLE_ALL(A, B, C, D) \
    hdf5_put_var1 (B, H5T_NATIVE_DOUBLE, dxplid_indep, C, D);
#define HDF5_PUT_VAR1_FLOAT_ALL(A, B, C, D) \
    hdf5_put_var1 (B, H5T_NATIVE_FLOAT, , dxplid_indep C, D);
#define HDF5_PUT_VAR1_INT_ALL(A, B, C, D)  hdf5_put_var1 (B, H5T_NATIVE_INT, dxplid_indep, C, D);
#define HDF5_PUT_VAR1_TEXT_ALL(A, B, C, D) hdf5_put_var1 (B, H5T_NATIVE_CHAR, dxplid_indep, C, D);

#define HDF5_IPUT_VAR1_DOUBLE(A, B, C, D, E) HDF5_PUT_VAR1_DOUBLE (A, B, C, D)
#define HDF5_IPUT_VAR1_FLOAT(A, B, C, D, E)  HDF5_PUT_VAR1_FLOAT (A, B, C, D)
#define HDF5_IPUT_VAR1_INT(A, B, C, D, E)    HDF5_PUT_VAR1_INT (A, B, C, D)
#define HDF5_IPUT_VAR1_TEXT(A, B, C, D, E)   HDF5_PUT_VAR1_TEXT (A, B, C, D)

// VARN
#define HDF5_PUT_VARN(A, B, C, D, E, F, G, H)     hdf5_put_varn (B, H, dxplid_indep, C, D, E, F);
#define HDF5_IPUT_VARN(A, B, C, D, E, F, G, H, I) HDF5_PUT_VARN (A, B, C, D, E, F, G, H)

// GET

// VAR

#define HDF5_GET_VAR_DOUBLE(A, B, C) \
    H5Dread (f_dids[B], H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, dxplid_indep, C);
#define HDF5_GET_VAR_FLOAT(A, B, C) \
    H5Dread (f_dids[B], H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, dxplid_indep, C);
#define HDF5_GET_VAR_INT(A, B, C)  H5Dread (f_dids[B], H5T_NATIVE_INT, H5S_ALL, H5S_ALL, dxplid_indep, C);
#define HDF5_GET_VAR_TEXT(A, B, C) H5Dread (f_dids[B], H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, dxplid_indep, C);

#define HDF5_GET_VAR_DOUBLE_ALL(A, B, C) \
    H5Dread (f_dids[B], H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, dxplid_coll, C);
#define HDF5_GET_VAR_FLOAT_ALL(A, B, C) \
    H5Dread (f_dids[B], H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, dxplid_coll, C);
#define HDF5_GET_VAR_INT_ALL(A, B, C) \
    H5Dread (f_dids[B], H5T_NATIVE_INT, H5S_ALL, H5S_ALL, dxplid_coll, C);
#define HDF5_GET_VAR_TEXT_ALL(A, B, C) \
    H5Dread (f_dids[B], H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, dxplid_coll, C);

#define HDF5_IGET_VAR_DOUBLE(A, B, C, D) HDF5_GET_VAR_DOUBLE (A, B, C)
#define HDF5_IGET_VAR_FLOAT(A, B, C, D)  HDF5_GET_VAR_FLOAT (A, B, C)
#define HDF5_IGET_VAR_INT(A, B, C, D)    HDF5_GET_VAR_INT (A, B, C)
#define HDF5_IGET_VAR_TEXT(A, B, C, D)   HDF5_GET_VAR_TEXT (A, B, C)

// VARA

#define HDF5_GET_VARA_DOUBLE(A, B, C, D, E) \
    hdf5_get_vara (B, H5T_NATIVE_DOUBLE, dxplid_indep, C, D, E);
#define HDF5_GET_VARA_FLOAT(A, B, C, D, E) \
    hdf5_get_vara (B, H5T_NATIVE_FLOAT, dxplid_indep, C, D, E);
#define HDF5_GET_VARA_INT(A, B, C, D, E)  hdf5_get_vara (B, H5T_NATIVE_INT, dxplid_indep, C, D, E);
#define HDF5_GET_VARA_TEXT(A, B, C, D, E) hdf5_get_vara (B, H5T_NATIVE_CHAR, dxplid_indep, C, D, E);

#define HDF5_GET_VARA_DOUBLE_ALL(A, B, C, D, E) \
    hdf5_get_vara (B, H5T_NATIVE_DOUBLE, dxplid_coll, C, D, E);
#define HDF5_GET_VARA_FLOAT_ALL(A, B, C, D, E) \
    hdf5_get_vara (B, H5T_NATIVE_FLOAT, dxplid_coll, C, D, E);
#define HDF5_GET_VARA_INT_ALL(A, B, C, D, E) \
    hdf5_get_vara (B, H5T_NATIVE_INT, dxplid_coll, C, D, E);
#define HDF5_GET_VARA_TEXT_ALL(A, B, C, D, E) \
    hdf5_get_vara (B, H5T_NATIVE_CHAR, dxplid_coll, C, D, E);

#define HDF5_IGET_VARA_DOUBLE(A, B, C, D, E, F) HDF5_GET_VARA_DOUBLE (A, B, C, D, E)
#define HDF5_IGET_VARA_FLOAT(A, B, C, D, E, F)  HDF5_GET_VARA_FLOAT (A, B, C, D, E)
#define HDF5_IGET_VARA_INT(A, B, C, D, E, F)    HDF5_GET_VARA_INT (A, B, C, D, E)
#define HDF5_IGET_VARA_TEXT(A, B, C, D, E, F)   HDF5_GET_VARA_TEXT (A, B, C, D, E)

// VAR1

#define HDF5_GET_VAR1_DOUBLE(A, B, C, D) hdf5_get_var1 (B, H5T_NATIVE_DOUBLE, dxplid_indep, C, D);
#define HDF5_GET_VAR1_FLOAT(A, B, C, D)  hdf5_get_var1 (B, H5T_NATIVE_FLOAT, dxplid_indep, C, D);
#define HDF5_GET_VAR1_INT(A, B, C, D)    hdf5_get_var1 (B, H5T_NATIVE_INT, dxplid_indep, C, D);
#define HDF5_GET_VAR1_TEXT(A, B, C, D)   hdf5_get_var1 (B, H5T_NATIVE_CHAR, dxplid_indep, C, D);

#define HDF5_GET_VAR1_DOUBLE_ALL(A, B, C, D) \
    hdf5_get_var1 (B, H5T_NATIVE_DOUBLE, dxplid_coll, C, D);
#define HDF5_GET_VAR1_FLOAT_ALL(A, B, C, D) hdf5_get_var1 (B, H5T_NATIVE_FLOAT, dxplid_coll, C, D);
#define HDF5_GET_VAR1_INT_ALL(A, B, C, D)   hdf5_get_var1 (B, H5T_NATIVE_INT, dxplid_coll, C, D);
#define HDF5_GET_VAR1_TEXT_ALL(A, B, C, D)  hdf5_get_var1 (B, H5T_NATIVE_CHAR, dxplid_coll, C, D);

#define HDF5_IGET_VAR1_DOUBLE(A, B, C, D, E) HDF5_GET_VAR1_DOUBLE (A, B, C, D)
#define HDF5_IGET_VAR1_FLOAT(A, B, C, D, E)  HDF5_GET_VAR1_FLOAT (A, B, C, D)
#define HDF5_IGET_VAR1_INT(A, B, C, D, E)    HDF5_GET_VAR1_INT (A, B, C, D)
#define HDF5_IGET_VAR1_TEXT(A, B, C, D, E)   HDF5_GET_VAR1_TEXT (A, B, C, D)

// VARN
#define HDF5_GET_VARN(A, B, C, D, E, F, G, H)     hdf5_get_varn (B, H, dxplid_indep, C, D, E, F);
#define HDF5_IGET_VARN(A, B, C, D, E, F, G, H, I) HDF5_GET_VARN (A, B, C, D, E, F, G, H)

// ATT
#define HDF5_PUT_ATT_TEXT(A, B, C, D, E)     hdf5_put_att (A, B, C, H5T_NATIVE_CHAR, D, E);
#define HDF5_PUT_ATT_INT(A, B, C, D, E, F)   hdf5_put_att (A, B, C, H5T_NATIVE_INT, E, F);
#define HDF5_PUT_ATT_FLOAT(A, B, C, D, E, F) hdf5_put_att (A, B, C, H5T_NATIVE_FLOAT, E, F);

#define HDF5_GET_ATT_TEXT(A, B, C, D)  hdf5_get_att (A, B, C, H5T_NATIVE_CHAR, D);
#define HDF5_GET_ATT_INT(A, B, C, D)   hdf5_get_att (A, B, C, H5T_NATIVE_INT, D);
#define HDF5_GET_ATT_FLOAT(A, B, C, D) hdf5_get_att (A, B, C, H5T_NATIVE_FLOAT, D);

// Misc
#define HDF5_INQ_PUT_SIZE(A, B)   NC_NOERR
#define HDF5_INQ_GET_SIZE(A, B)   NC_NOERR
#define HDF5_INQ_FILE_INFO(A, B)  hdf5_inq_file_info (A, B);
#define HDF5_WAIT_ALL(A, B, C, D) H5Fflush (A, H5F_SCOPE_GLOBAL);

#define HDF5_NOP1(A)    NC_NOERR
#define HDF5_NOP2(A, B) NC_NOERR

int hdf5_wrap_init ();
void hdf5_wrap_finalize ();
int hdf5_put_vara (
    int vid, hid_t mtype, hid_t dxplid, MPI_Offset *mstart, MPI_Offset *mcount, void *buf);
int hdf5_put_var1 (int vid, hid_t mtype, hid_t dxplid, MPI_Offset *mstart, void *buf);
int hdf5_put_varn (int vid,
                   MPI_Datatype mpitype,
                   hid_t dxplid,
                   int cnt,
                   MPI_Offset **mstarts,
                   MPI_Offset **mcounts,
                   void *buf);

int hdf5_get_vara (
    int vid, hid_t mtype, hid_t dxplid, MPI_Offset *mstart, MPI_Offset *mcount, void *buf);
int hdf5_get_var1 (int vid, hid_t mtype, hid_t dxplid, MPI_Offset *mstart, void *buf);
int hdf5_get_varn (int vid,
                   MPI_Datatype mpitype,
                   hid_t dxplid,
                   int cnt,
                   MPI_Offset **mstarts,
                   MPI_Offset **mcounts,
                   void *buf);

int hdf5_put_att (
    hid_t fid, int vid, const char *name, hid_t atype, MPI_Offset nelems, const void *buf);

int hdf5_get_att (hid_t fid, int vid, const char *name, hid_t atype, void *buf);

int hdf5_def_var (hid_t fid, const char *name, nc_type nctype, int ndim, int *dimids, int *vid);
int hdf5_inq_varid (hid_t fid, const char *name, int *vid);

int hdf5_def_dim (hid_t fid, const char *name, MPI_Offset msize, int *did);
int hdf5_inq_dimid (hid_t fid, const char *name, int *did);
int hdf5_inq_dimlen (hid_t fid, int did, MPI_Offset *msize);

int hdf5_inq_file_info (hid_t fid, MPI_Info *info);
int hdf5_inq_put_size (hid_t fid, size_t *size);
int hdf5_inq_get_size (hid_t fid, size_t *size);

int hdf5_close_vars (hid_t fid);
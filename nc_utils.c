#include <mpi.h>
#include <netcdf.h>

int nc_put_varn (int ncid,
                 int varid,
                 int nreq,
                 size_t **starts,
                 size_t **counts,
                 void *buf,
                 MPI_Offset bufcnt,
                 MPI_Datatype buftype) {
    int err, status = NC_NOERR;
    int i, j;
    int ndim;
    int esize;
    size_t rsize;
    char *bufp = (char *)buf;

    MPI_Type_size (buftype, &esize);

    err = nc_inq_varndims (ncid, varid, &ndim);

    for (i = 0; i < nreq; i++) {
        if (buftype == MPI_DOUBLE) {
            err = nc_put_vara_double (ncid, varid, starts[i], counts[i], (double *)bufp);
        } else if (buftype == MPI_FLOAT) {
            err = nc_put_vara_float (ncid, varid, starts[i], counts[i], (float *)bufp);
        } else if (buftype == MPI_INT) {
            err = nc_put_vara_int (ncid, varid, starts[i], counts[i], (int *)bufp);
        } else {
            err = NC_EINVAL;
        }
        if (status == NC_NOERR) status = err;

        rsize = esize;
        for (j = 0; j < ndim; j++) rsize *= counts[i][j];
        bufp += rsize;
    }

    return status;
}

int nc_get_varn (int ncid,
                 int varid,
                 int nreq,
                 size_t **starts,
                 size_t **counts,
                 void *buf,
                 MPI_Offset bufcnt,
                 MPI_Datatype buftype) {
    int err, status = NC_NOERR;
    int i, j;
    int ndim;
    int esize;
    size_t rsize;
    char *bufp = (char *)buf;

    MPI_Type_size (buftype, &esize);

    err = nc_inq_varndims (ncid, varid, &ndim);

    for (i = 0; i < nreq; i++) {
        if (buftype == MPI_DOUBLE) {
            err = nc_get_vara_double (ncid, varid, starts[i], counts[i], (double *)bufp);
        } else if (buftype == MPI_FLOAT) {
            err = nc_get_vara_float (ncid, varid, starts[i], counts[i], (float *)bufp);
        } else if (buftype == MPI_INT) {
            err = nc_get_vara_int (ncid, varid, starts[i], counts[i], (int *)bufp);
        } else {
            err = NC_EINVAL;
        }
        if (status == NC_NOERR) status = err;

        rsize = esize;
        for (j = 0; j < ndim; j++) rsize *= counts[i][j];
        bufp += rsize;
    }

    return status;
}

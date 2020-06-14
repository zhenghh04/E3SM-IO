AM_CPPFLAGS = -I$(top_srcdir)

bin_PROGRAMS = e3sm_io

e3sm_io_SOURCES = e3sm_io.c read_decomp.c var_io_F_case.c var_io_G_case.c header_io_F_case.c header_io_G_case.c
e3sm_io_SOURCES += e3sm_io.h 
#e3sm_io_LDADD = -lpnetcdf

if ENABLE_NETCDF4
e3sm_io_SOURCES += nc_utils.c var_io_F_case_nc4.c header_io_F_case_nc4.c var_io_G_case_nc4.c header_io_G_case_nc4.c
endif
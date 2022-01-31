# @configure_input@

SUFFIXES = .o .c .cpp

AM_CPPFLAGS  = -I${top_srcdir}/src
AM_CPPFLAGS += -I${top_srcdir}/src/drivers
AM_CPPFLAGS += -I${top_srcdir}/src/cases

bin_PROGRAMS = dat2nc \
               dat2h5 \
               datstat \
               pnetcdf_blob_replay

if ENABLE_ADIOS2
if HAVE_CXX17
   bin_PROGRAMS += bpstat
endif
endif

dat2nc_SOURCES = dat2nc.c
dat2nc_LDADD = -lpnetcdf

dat2h5_SOURCES = dat2h5.cpp
dat2h5_LDADD = -lpnetcdf \
               ${top_srcdir}/src/drivers/libe3sm_io_drivers.a

pnetcdf_blob_replay_SOURCES = pnetcdf_blob_replay.c
pnetcdf_blob_replay_LDADD = -lpnetcdf

datstat_SOURCES = datstat.cpp

bpstat_SOURCES = bpstat.cpp
bpstat_LDADD = -lstdc++fs

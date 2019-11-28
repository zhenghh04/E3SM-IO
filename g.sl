#!/bin/bash
#SBATCH -p regular
#SBATCH -N 64
#SBATCH -C haswell
#SBATCH -t 00:10:00
#SBATCH -o e3sm_g_64_%j.txt
#SBATCH -e e3sm_g_64_%j.err
#SBATCH -L SCRATCH
#SBATCH -A m2956

NN=${SLURM_NNODES}
#let NP=NN*1
let NP=NN*32

RUNS=(1 2) # Number of runs

INDIR=/global/cscratch1/sd/khl7265/FS_64_8M/E3SM/realdata/
OUTDIR_ROOT=/global/cscratch1/sd/khl7265/FS_64_8M/E3SM/
SRCDIR=/global/cscratch1/sd/khl7265/FS_64_8M/E3SM/src

#H0=${SRCDIR}/FC5AV1C-H01B_ne30_512.cam.h0.0001-01-01-00000.nc
#H1=${SRCDIR}/FC5AV1C-H01B_ne30_512.cam.h1.0001-01-01-00000.nc
#CONFIG=datasets/f_case_48602x72_512p.nc

#H0=${SRCDIR}/FC5AV1C-H01B_ne120_oRRS18v3_21632.cam.h0.0001-01-01-00000.nc
#H1=${SRCDIR}/FC5AV1C-H01B_ne120_oRRS18v3_21632.cam.h1.0001-01-01-00000.nc
#CONFIG=/global/cscratch1/sd/khl7265/FS_64_1M/E3SM/decom/FC5AV1C-H01B_ne120_oRRS18v3_21600p.nc

H0=${SRCDIR}/mpaso.hist.0001-01-01_00000.nc
CONFIG=/global/cscratch1/sd/khl7265/FS_64_8M/E3SM/decom/GMPAS-NYF_T62_oRRS18to6v3_9600p.nc

ZIPDRIVERS=(contig zlib)
READS=(0 1)
FILE=0
NREC=1
#CASE=F
CASE=G
TL=10

for ZIPDRIVER in ${ZIPDRIVERS[@]}
do
    echo "mkdir -p ${OUTDIR_ROOT}/${ZIPDRIVER}"
    mkdir -p ${OUTDIR_ROOT}/${ZIPDRIVER}
done

echo "mkdir -p ${INDIR}"
mkdir -p ${INDIR}
echo "rm -f ${INDIR}/*"
rm -f ${INDIR}/*
ln -s ${H0} ${INDIR}/g_case_hist_varn.nc
#ln -s ${H0} ${INDIR}/f_case_h0_varn.nc
#ln -s ${H1} ${INDIR}/f_case_h1_varn.nc
echo "ls -lah ${INDIR}"
ls -lah ${INDIR}

ulimit -c unlimited

TSTARTTIME=`date +%s.%N`

export PNETCDF_SHOW_PERFORMANCE_INFO=1

for i in ${RUNS[@]}
do
    for ZIPDRIVER in ${ZIPDRIVERS[@]}
    do
        OUTDIR=${OUTDIR_ROOT}/${ZIPDRIVER}/
        echo "rm -f ${OUTDIR}/*"
        rm -f ${OUTDIR}/*
    done

    for READ in ${READS[@]}
    do
        for ZIPDRIVER in ${ZIPDRIVERS[@]}
        do
            echo "========================== CHUNKED PROC WR =========================="
            >&2 echo "========================== CHUNKED PROC WR =========================="
            
            OUTDIR=${OUTDIR_ROOT}/${ZIPDRIVER}/

            echo "#%$: exp: e3sm"
            echo "#%$: api: ncmpi"
            echo "#%$: zip_driver: ${ZIPDRIVER}"
            echo "#%$: delay_init: 0"
            echo "#%$: nrec: ${NREC}"
            echo "#%$: read: ${READ}"
            echo "#%$: file: ${FILE}"
            echo "#%$: case: ${CASE}"
            echo "#%$: number_of_nodes: ${NN}"
            echo "#%$: number_of_proc: ${NP}"

            if [ "$ZIPDRIVER" = "zlib" ] ; then
                export PNETCDF_HINTS="nc_compression=enable;nc_zip_driver=${ZIPDRIVER};nc_zip_buffer_size=-1"
            fi

            STARTTIME=`date +%s.%N`

            if [ "$READ" = "1" ] ; then
                echo "srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${OUTDIR} -c ${FILE} ${CONFIG}"
                srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${OUTDIR} -c ${FILE} ${CONFIG}
            else 
                echo "srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${INDIR} -w -o ${OUTDIR} -c ${FILE} ${CONFIG}"
                srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${INDIR} -w -o ${OUTDIR} -c ${FILE} ${CONFIG}
            fi

            ENDTIME=`date +%s.%N`
            TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."$2}'`

            unset PNETCDF_HINTS

            echo "#%$: exe_time: $TIMEDIFF"

            echo "ls -lah ${OUTDIR}"
            ls -lah ${OUTDIR}
            echo "lfs getstripe ${OUTDIR}"
            lfs getstripe ${OUTDIR}

            echo '-----+-----++------------+++++++++--+---'
        done
    done
done

ENDTIME=`date +%s.%N`
TIMEDIFF=`echo "$ENDTIME - $TSTARTTIME" | bc | awk -F"." '{print $1"."$2}'`
echo "-------------------------------------------------------------"
echo "total_exe_time: $TIMEDIFF"
echo "-------------------------------------------------------------"

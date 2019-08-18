#!/bin/bash
#SBATCH -p regular
#SBATCH -N 8
#SBATCH -C haswell
#SBATCH -t 00:40:00
#SBATCH -o e3sm_f_0_21600_8_wr_%j.txt
#SBATCH -e e3sm_f_0_21600_8_wr_%j.err
#SBATCH -L SCRATCH
#SBATCH -A m2956

NN=${SLURM_NNODES}
#let NP=NN*1
let NP=NN*32

RUNS=(1 2) # Number of runs

INDIR=/global/cscratch1/sd/khl7265/FS_64_8M/E3SM/realdata/
OUTDIR_ROOT=/global/cscratch1/sd/khl7265/FS_64_8M/E3SM/

#SRCDIR=/global/cscratch1/sd/dqwu/e3sm_output_files/FC5AV1C-H01B_ne30_ne30_512p
#H0=${SRCDIR}/FC5AV1C-H01B_ne30_512.cam.h0.0001-01-01-00000.nc
#H1=${SRCDIR}/FC5AV1C-H01B_ne30_512.cam.h1.0001-01-01-00000.nc
#CONFIG=datasets/f_case_48602x72_512p.nc

SRCDIR=/global/cscratch1/sd/dqwu/e3sm_output_files/FC5AV1C-H01B_ne120_oRRS18v3_21632p
H0=${SRCDIR}/FC5AV1C-H01B_ne120_oRRS18v3_21632.cam.h0.0001-01-01-00000.nc
H1=${SRCDIR}/FC5AV1C-H01B_ne120_oRRS18v3_21632.cam.h1.0001-01-01-00000.nc
CONFIG=/global/cscratch1/sd/khl7265/FS_64_1M/E3SM/decom/FC5AV1C-H01B_ne120_oRRS18v3_21600p.nc

#SRCDIR=/global/cscratch1/sd/dqwu/e3sm_output_files/GMPAS-NYF_T62_oRRS18to6v3_9600p
#H0=${SRCDIR}/mpaso.hist.0001-01-01_00000.nc
#CONFIG=/global/cscratch1/sd/khl7265/FS_64_1M/E3SM/decom/GMPAS-NYF_T62_oRRS18to6v3_9600p.nc

ZIPDRIVERS=(zlib)
INITMETHODS=(0) # 1)
COMMUNITS=(proc) # chunk)
NREC=1
FILES=(0) # 1)
CASE=F
# CASE=G
TL=6

echo "mkdir -p ${OUTDIR_ROOT}/origin"
mkdir -p ${OUTDIR_ROOT}/origin
for ZIPDRIVER in ${ZIPDRIVERS[@]}
do
    echo "mkdir -p ${OUTDIR_ROOT}/${ZIPDRIVER}"
    mkdir -p ${OUTDIR_ROOT}/${ZIPDRIVER}
done

echo "mkdir -p ${INDIR}"
mkdir -p ${INDIR}
echo "rm -f ${INDIR}/*"
rm -f ${INDIR}/*
# ln -s ${H0} ${INDIR}/g_case_hist_varn.nc
ln -s ${H0} ${INDIR}/f_case_h0_varn.nc
ln -s ${H1} ${INDIR}/f_case_h1_varn.nc
echo "ls -lah ${INDIR}"
ls -lah ${INDIR}

ulimit -c unlimited

TSTARTTIME=`date +%s.%N`

export PNETCDF_SHOW_PERFORMANCE_INFO=1

for i in ${RUNS[@]}
do
    for FILE in ${FILES[@]}
    do
        # Ncmpio
        echo "========================== ORIGINAL =========================="
        >&2 echo "========================== ORIGINAL =========================="

        echo "#%$: io_driver: ncmpi"
        echo "#%$: zip_driver: NA"
        echo "#%$: delay_init: 0"
        echo "#%$: comm_unit: NA"
        echo "#%$: file: ${FILE}"
        echo "#%$: case: ${CASE}"
        echo "#%$: number_of_nodes: ${NN}"
        echo "#%$: number_of_proc: ${NP}"
        
        OUTDIR=${OUTDIR_ROOT}/origin/

        echo "rm -f ${OUTDIR}/*"
        rm -f ${OUTDIR}/*

        STARTTIME=`date +%s.%N`
        STARTTIME=`date +%s.%N`

        echo "srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${INDIR} -w -o ${OUTDIR} -c ${FILE} ${CONFIG}"
        srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${INDIR} -w -o ${OUTDIR} -c ${FILE} ${CONFIG}

        ENDTIME=`date +%s.%N`
        TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."$2}'`

        echo "#%$: exe_time: $TIMEDIFF"

        echo "ls -lah ${OUTDIR}"
        ls -lah ${OUTDIR}
        echo "lfs getstripe ${OUTDIR}"
        lfs getstripe ${OUTDIR}

        echo '-----+-----++------------+++++++++--+---'

        # Nczipio
        for ZIPDRIVER in ${ZIPDRIVERS[@]}
        do
            for INITMETHOD in ${INITMETHODS[@]}
            do
                for COMMUNIT in ${COMMUNITS[@]}
                do
                    echo "========================== CHUNKED PROC =========================="
                    >&2 echo "========================== CHUNKED PROC =========================="
                    
                    OUTDIR=${OUTDIR_ROOT}/${ZIPDRIVER}/

                    echo "#%$: io_driver: nczipio"
                    echo "#%$: zip_driver: ${ZIPDRIVER}"
                    echo "#%$: delay_init: ${INITMETHOD}"
                    echo "#%$: comm_unit: ${COMMUNIT}"
                    echo "#%$: file: ${FILE}"
                    echo "#%$: case: ${CASE}"
                    echo "#%$: number_of_nodes: ${NN}"
                    echo "#%$: number_of_proc: ${NP}"

                    echo "rm -f ${OUTDIR}/*"
                    rm -f ${OUTDIR}/*

                    export PNETCDF_HINTS="nc_compression=enable;nc_zip_driver=${ZIPDRIVER};nc_zip_delay_init=${INITMETHOD};nc_zip_comm_unit=${COMMUNIT};nc_zip_buffer_size=-1"
                    # export PNETCDF_PROFILE_PREFIX="nczipio_profile_${ZIPDRIVER}_${INITMETHOD}_${COMMUNIT}"

                    STARTTIME=`date +%s.%N`

                    echo "srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${INDIR} -w -o ${OUTDIR} -c ${FILE} ${CONFIG}"
                    srun -n ${NP} -t ${TL} ./e3sm_io -t ${NREC} -k -r -i ${INDIR} -w -o ${OUTDIR} -c ${FILE} ${CONFIG}

                    ENDTIME=`date +%s.%N`
                    TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."$2}'`

                    unset PNETCDF_HINTS
                    # unset PNETCDF_PROFILE_PREFIX

                    echo "#%$: exe_time: $TIMEDIFF"

                    echo "ls -lah ${OUTDIR}"
                    ls -lah ${OUTDIR}
                    echo "lfs getstripe ${OUTDIR}"
                    lfs getstripe ${OUTDIR}

                    echo '-----+-----++------------+++++++++--+---'
                done
            done
        done
    done
done

ENDTIME=`date +%s.%N`
TIMEDIFF=`echo "$ENDTIME - $TSTARTTIME" | bc | awk -F"." '{print $1"."$2}'`
echo "-------------------------------------------------------------"
echo "total_exe_time: $TIMEDIFF"
echo "-------------------------------------------------------------"

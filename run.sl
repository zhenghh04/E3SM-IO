#!/bin/bash
#SBATCH -p debug
#SBATCH -N 1
#SBATCH -C haswell
#SBATCH -t 00:30:00
#SBATCH -o e3sm_1_%j.txt
#SBATCH -e e3sm_1_%j.err
#SBATCH -L SCRATCH
#SBATCH -A m2956

NN=${SLURM_NNODES}
#let NP=NN*1
let NP=NN*32

export LD_LIBRARY_PATH=/global/homes/k/khl7265/.local/hdf5/1.12.0/lib:${LD_LIBRARY_PATH}

RUNS=(1 2) # Number of runs

OUTDIR_ROOT=/global/cscratch1/sd/khl7265/FS_64_8M/E3SM/

CONFIG_FSMALL=datasets/f_case_866x72_16p.nc
CONFIG_FMID=datasets/f_case_48602x72_512p.nc
CONFIG_FLARGE=/global/cscratch1/sd/khl7265/FS_64_1M/E3SM/decom/FC5AV1C-H01B_ne120_oRRS18v3_21600p.nc
CONFIG_GLARGE=/global/cscratch1/sd/khl7265/FS_64_1M/E3SM/decom/GMPAS-NYF_T62_oRRS18to6v3_9600p.nc

CONFIGS=(${CONFIG_FSMALL} ${CONFIG_FMID})
APP=e3sm_io
#APP=e3sm_io_profile
HXS=(0 1)
APIS=(pnc hdf5)
OPS=(write)
TL=6

for API in ${APIS[@]}
do
    echo "mkdir -p ${OUTDIR_ROOT}/${API}"
    mkdir -p ${OUTDIR_ROOT}/${API}
done

ulimit -c unlimited

TSTARTTIME=`date +%s.%N`

for i in ${RUNS[@]}
do
    for CONFIG in ${CONFIGS[@]}
    do
        for API in ${APIS[@]}
        do
            OUTDIR=${OUTDIR_ROOT}/${API}/
            echo "rm -f ${OUTDIR}/*"
            rm -f ${OUTDIR}/*

            for HX in ${HXS[@]}
            do
                for OP in ${OPS[@]}
                do
                    echo "========================== E3SM-IO ${API} ${OP} =========================="
                    >&2 echo "========================== E3SM-IO ${API} ${OP}=========================="
                    
                    echo "#%$: exp: e3sm_io"
                    echo "#%$: config: ${CONFIG}"
                    echo "#%$: h_num: ${HX}"
                    echo "#%$: api: ${API}"
                    echo "#%$: operation: ${OP}"
                    echo "#%$: number_of_nodes: ${NN}"
                    echo "#%$: number_of_proc: ${NP}"

                    STARTTIME=`date +%s.%N`

                    if [ "$OP" = "write" ] ; then
                        echo "srun -n ${NP} -t ${TL} ./${APP} -k -o ${OUTDIR} -n -a ${API} -f ${HX} ${CONFIG}"
                        srun -n ${NP} -t ${TL} ./${APP} -k -o ${OUTDIR} -n -a ${API} -f ${HX} ${CONFIG}
                    else 
                        echo "Reading not supproted"
                        # echo "srun -n ${NP} -t ${TL} ./e3sm_io -k -o ${OUTDIR} -n -a ${API} ${CONFIG}"
                        # srun -n ${NP} -t ${TL} ./e3sm_io -k -o ${OUTDIR} -n -a ${API} ${CONFIG}
                    fi

                    ENDTIME=`date +%s.%N`
                    TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."$2}'`

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
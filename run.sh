#!/bin/bash
#COBALT -t 10
#COBALT -n 1
#COBALT -A CSC250STDM12
#COBALT -q debug-flat-quad
#COBALT -o e3sm_1.txt
#COBALT -e e3sm_1.err

NN=${COBALT_JOBSIZE}
#PPN=1
PPN=32
let NP=NN*PPN

export n_nodes=$COBALT_JOBSIZE
export n_mpi_ranks_per_node=${PPN}
export n_mpi_ranks=$(($n_nodes * $n_mpi_ranks_per_node))
export n_openmp_threads_per_rank=1
export n_hyperthreads_per_core=1

export LD_LIBRARY_PATH=/home/khou/.local/hdf5/1.12.0/lib:/home/khou/.local/log_io_vol/profiling/lib:${LD_LIBRARY_PATH}

export H5VL_LOG_METADATA_MERGE=1
export H5VL_LOG_METADATA_ZIP=1
export H5VL_LOG_SEL_ENCODING=1

RUNS=(1 2) # Number of runs

OUTDIR_ROOT=/projects/CSC250STDM12/khou/FS_48_8M/E3SM/

CONFIG_FSMALL=datasets/f_case_866x72_16p.nc
CONFIG_FMID=datasets/f_case_48602x72_512p.nc
CONFIG_FLARGE=/projects/CSC250STDM12/khou/FS_48_1M/E3SM/decom/FC5AV1C-H01B_ne120_oRRS18v3_21600p.nc
CONFIG_GLARGE=/projects/CSC250STDM12/khou/FS_48_1M/E3SM/decom/GMPAS-NYF_T62_oRRS18to6v3_9600p.nc

CONFIGS=(${CONFIG_FMID})
APP=e3sm_io
#APP=e3sm_io_profile
HXS=(0 1)
APIS=(pnc hdf5)
OPS=(write)
TL=360

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
                    echo "#%$: app: ${APP}"
                    echo "#%$: config: ${CONFIG}"
                    echo "#%$: h_num: ${HX}"
                    echo "#%$: api: ${API}"
                    echo "#%$: operation: ${OP}"
                    echo "#%$: number_of_nodes: ${NN}"
                    echo "#%$: number_of_proc: ${NP}"
                    echo "#%$: logvol_metadata_merge: ${H5VL_LOG_METADATA_MERGE}"
                    echo "#%$: logvol_metadata_zip: ${H5VL_LOG_METADATA_ZIP}"
                    echo "#%$: logvol_metadata_encoding: ${H5VL_LOG_SEL_ENCODING}"

                    STARTTIME=`date +%s.%N`

                    if [ "$OP" = "write" ] ; then
                        echo "aprun -n ${NP} -N ${PPN} -t ${TL} -e H5VL_LOG_METADATA_MERGE=${H5VL_LOG_METADATA_MERGE} -e H5VL_LOG_METADATA_ZIP=${H5VL_LOG_METADATA_ZIP} -e H5VL_LOG_SEL_ENCODING=${H5VL_LOG_SEL_ENCODING} ./${APP} -k -o ${OUTDIR} -n -a ${API} -f ${HX} ${CONFIG}"
                        aprun -n ${NP} -N ${PPN} -t ${TL} -e H5VL_LOG_METADATA_MERGE=${H5VL_LOG_METADATA_MERGE} -e H5VL_LOG_METADATA_ZIP=${H5VL_LOG_METADATA_ZIP} -e H5VL_LOG_SEL_ENCODING=${H5VL_LOG_SEL_ENCODING} ./${APP} -k -o ${OUTDIR} -n -a ${API} -f ${HX} ${CONFIG}
                    else 
                        echo "Reading not supproted"
                        # echo "aprun -n ${NP} -N ${PPN} -t ${TL} ./e3sm_io -k -o ${OUTDIR} -n -a ${API} ${CONFIG}"
                        # aprun -n ${NP} -N ${PPN} -t ${TL} ./e3sm_io -k -o ${OUTDIR} -n -a ${API} ${CONFIG}
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

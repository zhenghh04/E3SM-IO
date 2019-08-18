#!/bin/bash
#SBATCH -p debug
#SBATCH -N 8 
#SBATCH -C haswell
#SBATCH -t 00:00:10
#SBATCH -o e3sm_8_%j.txt
#SBATCH -e e3sm_8_%j.err
#SBATCH -L SCRATCH
#SBATCH -A m844
#DW jobdw capacity=1280GiB access_mode=striped type=scratch

RUNS=(1) # Number of runs
OUTDIR=/global/cscratch1/sd/khl7265/FS_64_1M/e3sm
NN=${SLURM_NNODES}
#let NP=NN*16
let NP=NN*32

# Make sure BB stripe count is correct
srun -n 1 /global/homes/k/khl7265/sc ${DW_JOB_STRIPED}/test.bin 128
ret="$(sacct -o exitcode -n -j ${SLURM_JOB_ID}.0)"
# remove leading whitespace characters
ret="${ret#"${ret%%[![:space:]]*}"}"
# remove trailing whitespace characters
ret="${ret%"${ret##*[![:space:]]}"}"   
if [[ "x${ret}" != "x0:0" ]]; then
    echo "BB stripe count mismatch, quit"
    exit 0
fi

echo "mkdir -p ${OUTDIR}"
mkdir -p ${OUTDIR}
echo "rm -rf ${DW_JOB_STRIPED}"
rm -rf ${DW_JOB_STRIPED}

TSTARTTIME=`date +%s.%N`

for i in ${RUNS[@]}
do

    # BB LPP S NEW
    
    echo "========================== BB LPP S NEW =========================="
    >&2 echo "========================== BB LPP S NEW =========================="

    echo "#%$: io_driver: bb_new_lpp_striped"
    echo "#%$: number_of_nodes: ${NN}"
    echo "#%$: number_of_proc: ${NP}"
    echo "#%$: io_mode: blocking_coll"

    echo "rm -f ${OUTDIR}/*"
    rm -f ${OUTDIR}/*

    export PNETCDF_HINTS="nc_burst_buf=enable;nc_burst_buf_del_on_close=disable;nc_burst_buf_overwrite=enable;nc_burst_buf_dirname=${DW_JOB_STRIPED}"

    STARTTIME=`date +%s.%N`

    srun -n ${NP} ./e3sm_io_bb_eval -k -q -r 3 -m datasets/48602x72_512p.nc -o ${OUTDIR}

    ENDTIME=`date +%s.%N`
    TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."$2}'`

    unset PNETCDF_HINTS

    echo "#%$: exe_time: $TIMEDIFF"

    echo "ls -lah ${OUTDIR}"
    ls -lah ${OUTDIR}
    if [[ "${NP}" -lt 33 ]]; then
        echo "ls -lah ${DW_JOB_STRIPED}"
        ls -lah ${DW_JOB_STRIPED}
    fi
    
    echo '-----+-----++------------+++++++++--+---'
    
done

echo "BB Info: "
module load dws
sessID=$(dwstat sessions | grep $SLURM_JOBID | awk '{print $1}')
echo "session ID is: "${sessID}
instID=$(dwstat instances | grep $sessID | awk '{print $1}')
echo "instance ID is: "${instID}
echo "fragments list:"
echo "frag state instID capacity gran node"
dwstat fragments | grep ${instID}

ENDTIME=`date +%s.%N`
TIMEDIFF=`echo "$ENDTIME - $TSTARTTIME" | bc | awk -F"." '{print $1"."$2}'`
echo "-------------------------------------------------------------"
echo "total_exe_time: $TIMEDIFF"
echo "-------------------------------------------------------------"


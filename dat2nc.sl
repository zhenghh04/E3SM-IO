#!/bin/bash
#SBATCH -p debug
#SBATCH -N 1 
#SBATCH -C haswell
#SBATCH -t 00:30:00
#SBATCH -o dat2nc_1_%j.txt
#SBATCH -e dat2nc_1_%j.err
#SBATCH -L SCRATCH
#SBATCH -A m844

INDIR=/global/cscratch1/sd/dqwu/e3sm_io_decomp_files/GMPAS-NYF_T62_oRRS18to6v3_9600p/piodecomp9600tasks_D
INDIRF=/global/cscratch1/sd/dqwu/e3sm_io_decomp_files/FC5AV1C-H01B_ne120_oRRS18v3_21600p/piodecomp21600tasks_D
OUTDIR=/global/cscratch1/sd/khl7265/FS_64_1M/E3SM/decom/

TL=5

echo "mkdir -p ${OUTDIR}"
mkdir -p ${OUTDIR}

echo "ls -lah ${OUTDIR}"
ls -lah ${OUTDIR}

ulimit -c unlimited

TSTARTTIME=`date +%s.%N`


    echo "rm -f ${OUTDIR}/*"
    rm -f ${OUTDIR}/*
    
    STARTTIME=`date +%s.%N`

    echo "srun -n 16 -t ${TL} ./dat2nc -o ${OUTDIR}/GMPAS-NYF_T62_oRRS18to6v3_9600p.nc -1 ${INDIR}1_nCells.dat -2 ${INDIR}2_nEdges.dat -3 ${INDIR}3_nCells_nVertLevels.dat -4 ${INDIR}4_nEdges_nVertLevels.dat -5 ${INDIR}5_nVertices_nVertLevels.dat -6 ${INDIR}6_nCells_nVertLevelsP1.dat"
    
    srun -n 16 -t ${TL} ./dat2nc -o ${OUTDIR}/GMPAS-NYF_T62_oRRS18to6v3_9600p.nc -1 ${INDIR}1_nCells.dat -2 ${INDIR}2_nEdges.dat -3 ${INDIR}3_nCells_nVertLevels.dat -4 ${INDIR}4_nEdges_nVertLevels.dat -5 ${INDIR}5_nVertices_nVertLevels.dat -6 ${INDIR}6_nCells_nVertLevelsP1.dat

    ENDTIME=`date +%s.%N`
    TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."$2}'`

    echo "#%$: exe_time: $TIMEDIFF"

    echo "ls -lah ${OUTDIR}"
    ls -lah ${OUTDIR}
    
    STARTTIME=`date +%s.%N`
    
    echo "srun -n 16 -t ${TL} ./dat2nc -o ${OUTDIR}/FC5AV1C-H01B_ne120_oRRS18v3_21600p.nc -1 ${INDIRF}1_ncol.dat -2 ${INDIRF}2_ncol.dat -3 ${INDIRF}3_lev_ncol.dat"
    
    srun -n 16 -t ${TL} ./dat2nc -o ${OUTDIR}/FC5AV1C-H01B_ne120_oRRS18v3_21600p.nc -1 ${INDIRF}1_ncol.dat -2 ${INDIRF}2_ncol.dat -3 ${INDIRF}3_lev_ncol.dat
    
    ENDTIME=`date +%s.%N`
    TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."$2}'`

    unset PNETCDF_HINTS

    echo "#%$: exe_time: $TIMEDIFF"

    echo "ls -lah ${OUTDIR}"
    ls -lah ${OUTDIR}
   

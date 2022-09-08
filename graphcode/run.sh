#!/bin/bash
#PBS -e errorLogMST.err
#PBS -o logMST.log
#PBS -q rupesh_gpuq
#PBS -l select=1:ncpus=1:ngpus=1

tpdir=`echo $PBS_JOBID | cut -f 1 -d .`
tempdir=$HOME/scratch/job$tpdir
mkdir -p $tempdir
cd $tempdir
cp -R $PBS_O_WORKDIR/* .
module load cuda10.1
module load gcc640
nvcc -o "MST_V1_Manual".out "generated_cuda/MST_V1_Manual.cu"  -std=c++14  #-arch=sm_70
./MST_V1_Manual.out generated_cuda/testing/input1.txt > output_MST_V1_Manual.txt

rm *.out
cp -R * $PBS_O_WORKDIR/. && rm -r *
rmdir $tempdir

# /lfs1/usrscratch/phd/cs16d003/11suiteDSL
# qsub run.sh
# qstat
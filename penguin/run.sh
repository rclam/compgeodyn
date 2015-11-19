#!/bin/sh
#PBS -l nodes=1:default:ppn=16
#PBS -l walltime=00:10:00
#PBS -A CERI
#PBS -N matmult

# source the module command
source /etc/profile.d/modules.sh
# load some modules
module load openmpi/1.8.6/gcc.4.4.7

cd $PBS_O_WORKDIR
time mpirun -np `cat $PBS_NODEFILE | wc -l` ./matmultc

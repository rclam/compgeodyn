Job ID                    Name             User            Time Use S Queue
------------------------- ---------------- --------------- -------- - -----
158270.pbs                 matmult          echoi2                 0 Q thin
[echoi2@login1 penguin]$ cat run.sh
#!/bin/sh
## #PBS -l : list of resources such as nodes, walltime and mem.
## - nodes
##   run on 2 nodes using 8 cores per node, for a total of 16 cores: -l nodes=2:ppn=8
##   run on 3 nodes using the gpu only: -l nodes=3:gpus=1
##   run on 4 nodes using 1 core per node, and 2 nodes using 2 cores per node: -l nodes=4:ppn=1+2:ppn=2
## - walltime
##   run for 10 minutes: -l walltime=00:10:00
## - mem
##   To be added.
##
#PBS -l nodes=1:default:ppn=16 #:gpus=0
#PBS -l walltime=00:10:00
#PBS -A CERI        # account
#PBS -N matmult     # jobname
#PBS -j oe          # join the contests of STDOUT and STDERR into one file.
#PBS -q thin        # For full information about available queues: 'qstat -Q -f'
#PBS -o ${JOB_ID}.o # name of a file to store STDOUT
#PBS -e ${JOB_ID}.e # name of a file to store STDERR

# source the module command
source /etc/profile.d/modules.sh
# load modules that you loaded when building the application or any other that are necessary.
# e.g., i
# module load openmpi/1.8.6/gcc.4.4.7

cd $PBS_O_WORKDIR # this is the directory where you submit this job.

# if this is an MPI job: e.g.,
time mpirun -np `cat $PBS_NODEFILE | wc -l` ./matmultc

# if this is an OpenMP job: e.g.,
OMP_NUM_THREADS=4
time ./matmultc

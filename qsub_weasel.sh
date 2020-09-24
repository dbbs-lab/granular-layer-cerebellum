#! /bin/sh
#PBS -l nodes=5:ppn=12
#PBS -l walltime=1000:10:00
#PBS -q batch
#PBS -p 10
#PBS -j oe


#### Define a set of useful variables ####
EXECPATH=/home/neuron/nrn75/nrn/x86_64/bin/nrniv

cd $PBS_O_WORKDIR
pwd

INFILE=weasel_run.py

mpirun $EXECPATH -python -mpi $save_dir $INFILE >> o.txt  2>&1

exit 0

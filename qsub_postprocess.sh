#! /bin/sh
#PBS -l nodes=1:ppn=1
#PBS -l walltime=20:10:00
#PBS -q batch
#PBS -p 9
#PBS -j oe

# Dont know why it goes in my home dir
pwd
echo $PBS_O_WORKDIR
# I cd to the submit dir which is also the data dir
cd $PBS_O_WORKDIR
pwd
# Check that user is NOT root

#if [ $(id -un) == 'root' ];then
#    echo "This script should NOT be run as root user"
#    exit 1
#fi

# Copy data from the /mnt/scratch local dirs
if [ -z ${save_dir} ]; then
    echo "${save_dir} is NOT defined"
    exit 1
else
    for x in 1 2 3 4 5 ; do
	# /usr/bin/scp -C 10.0.0.21$x:${save_dir}/* ./
	/usr/bin/ssh 10.0.0.21$x "ls ${save_dir}"
	# This is a dangerous command as if $save_dir is not defined
	# and you are running as root it will move the root directories.
	/usr/bin/ssh 10.0.0.21$x "mv ${save_dir}/net* $PBS_O_WORKDIR"
	/usr/bin/ssh 10.0.0.21$x "rm -r ${save_dir}"
    done
fi

echo Running postprocess
./postprocess.sh . $structure_file
python plot_vm.py . goc
python plot_vm.py . stl
matlab -nodesktop -nosplash -r crosscorrel

chmod -R ug+rw $PBS_O_WORKDIR
chgrp -R sim $PBS_O_WORKDIR
find $PBS_O_WORKDIR -type d -exec chmod ug+x {} \;

exit 0

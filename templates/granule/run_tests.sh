#!/bin/bash
hn=`hostname`
if [ ! -d test_results ]; then
    mkdir test_results
fi

case $hn in
    'otto' )
	echo "otto"
	python test_goc_syn.py
	;;
    'cerfoglio' | blade* )
	;;
esac

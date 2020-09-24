#!/bin/bash
hn=`hostname`
if [ ! -d test_results ]; then
    mkdir test_results
fi
case $hn in
    'otto' )
	echo "otto"
	python test_syn_mf.py
	;;
    'theieras-MacBook-Pro.local' )
	echo "theiera Laptop"
	/usr/local/nrn2013/nrn/x86_64/bin/nrngui -python test_syn_mf.py
	;;
    'cerfoglio' | blade* )
	;;
esac

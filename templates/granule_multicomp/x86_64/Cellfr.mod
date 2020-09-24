: $Id: netstim.mod 2212 2008-09-08 14:32:26Z hines $
: comments at end

NEURON	{ 
  ARTIFICIAL_CELL Cellfr
  RANGE on,fr
  THREADSAFE
}

PARAMETER {
    on
}

ASSIGNED {
	isi (ms)
	fr 
	nspikes
	lastspike (ms)
	spikememory
}

INITIAL {
    fr = 0
    on = 1
    nspikes = 0
    lastspike = 0
    spikememory = 50
}

FUNCTION imin(a,b) {
	    if (a>b) { imin=b }
	    else { imin=b }
}	

NET_RECEIVE (w) { LOCAL meanisi
    if (flag == 0) { : external event
	if (w > 0 && on == 1) { : turn on spike sequence
	    if (lastspike == 0) {
		lastspike = t
	    }else {
		isi = 1e-3*(t - lastspike)
		:printf ("%g\n",isi)
		if (fr > 0) {
		    meanisi = 1/fr
		}else {
		    meanisi = 0
		}
		nspikes = imin(nspikes,spikememory)
		meanisi = meanisi*nspikes + isi
		nspikes = nspikes + 1
		meanisi = meanisi / nspikes
		fr = 1 / meanisi
		lastspike = t
	    }
	}
    }
}
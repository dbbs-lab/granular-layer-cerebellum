#! /opt/local/bin//python2.7
# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

from neuron import h
from neuron import gui
from stellate import Stellate
import numpy as np

Hines = h.CVode()
Hines.active(1)

save_dt = 0.025
cellula = Stellate(np.array([0.,0.,0.]),model_type='C',record_all = 1, Dt = save_dt, erev = -61.5)

print cellula.soma.el_MLI_lkg

fr = []

CC = h.IClamp(0.5,sec=cellula.soma)
CC.delay = 1000
CC.amp = 0.1
CC.dur = 1000


h.dt = 0.025
h.tstop = 2000
h.v_init = -65

# Store global time
time_vector = h.Vector()
time_vector.record(h._ref_t, save_dt)

h.celsius = 37
print h.celsius

import pylab
#for i in range(-42,-42):
h.run()

print "Firing rate = ", cellula.fr(1000), ' Hz'

pylab.plot(time_vector,cellula.record['vm'])
pylab.show()

    
# fr.append(cellula.fr(500))
   
# stringmli = str(mli_mli)

# filename = 'frvector_'+stringmli+'.txt'

# firing = str(fr)
# frvectorfile = open(filename,"w")
# frvectorfile.write(firing)
# frvectorfile.close()
# print fr 

# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

import h5py
import numpy as np
from matplotlib import pyplot as plt

from templates.golgi.Golgi_template import Goc
from templates.gapj.gapj import Gapj
import toolbox as tb

from neuron import h
from neuron import gui

h.nrn_load_dll('$i386/')

gocs = Goc(np.array([0.,0.,0.]),record_all=1, Dt = 0.025)

# stim = h.IClamp(.5, sec=gocs[0][1][1].soma)
# stim.amp = -0.015
# stim.dur = 200

gocs.createsyn(nmli=1,record_all=1, Dt = 0.025)

vc = h.VClamp(0.5, sec = gocs.soma)
vc.amp[0] = -70
vc.dur[0] = 1000

# cc = h.IClamp(0.5)
# cc.amp = -0.065
# cc.dur = 2000
# cc.delay = 0

stim = h.NetStim(0.5)
stim.number = 1
stim.interval = 10
stim.start = 800


nc_stl = [h.NetCon(stim,goc.input,0,0,1) for goc in gocs.STL_L]

tvec = h.Vector()
tvec.record(h._ref_t)

v = h.Vector()
v.record(vc._ref_i)


h.dt = 0.025
h.tstop = 1000
h.celsius = 23
v_init = -70
h.finitialize(v_init)
h.continuerun(h.tstop)


fig = plt.figure()
ax  = fig.add_subplot(121)

ax.plot(np.array(tvec)[10:],np.array(v)[10:]*1e3)
#ax.plot(gocs.record['time'],gocs.record['vm'])
ax.set_ylabel('VClamp current (pA)')
ax.set_xlabel('Time (ms)')
#ax.set_ylim(-20,1)


ax2  = fig.add_subplot(122)

ax2.plot(np.array(tvec),gocs.STL_L[0].i['GABA'][0].mul(1e3),label='EXPSYN')
ax2.set_ylabel('Synaptic current (pA)')
ax2.set_xlabel('Time (ms)')

plt.show()





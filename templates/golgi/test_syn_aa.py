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

gocs = Goc(np.array([0.,0.,0.]),record_all=1)

# stim = h.IClamp(.5, sec=gocs[0][1][1].soma)
# stim.amp = -0.015
# stim.dur = 200

gocs.createsyn(naa=1,record_all=1)

vc = h.VClamp(0.5, sec = gocs.soma)
vc.amp[0] = -70
vc.dur[0] = 10000

# cc = h.IClamp(0.5)
# cc.amp = -0.065
# cc.dur = 2000
# cc.delay = 0

stim = h.NetStim(0.5)
stim.number = 1
stim.interval = 10
stim.start = 2000


nc_mf = [h.NetCon(stim,goc.input,0,0,1) for goc in gocs.GRC_AA_L]

for goc in gocs.GRC_AA_L:
    print goc.postsyns

v = h.Vector()
v.record(vc._ref_i)




h.tstop = 3000
h.celsius = 32
v_init = -60
h.finitialize(v_init)
h.continuerun(h.tstop)


fig = plt.figure()
ax  = fig.add_subplot(121)

vv = np.array([gocs.record['time'],v]).transpose()

# Calc VClamp i features
# Peak current
print "Peak current = %d pA" % (np.min(vv[:,1])*1e3)
# Time to peak
print "Time to peak = %04.2f ms" % vv[np.argmin(vv[:,1]),0]
# Total charge
start_idx = np.where(vv[:,0] < stim.start)[0][-1]
EPSC = vv[start_idx:,1]
baseline = vv[start_idx,1]
print "EPSC charge = %04.2f fC" % (np.abs(np.sum(np.diff(vv[:,0])*(vv[:-1,1]-baseline)))*1e3)  # ms * nA = 1e-3 * 1e-9 C = 1e-12 C = pC 1pC = 1000 fC

ax.plot(vv[10:-1,0],vv[10:-1,1]*1e3)
# ax.plot(gocs.record['time'],gocs.record['vm'])
# ax.plot(gocs.record['time'],gocs.record['dend'][0])
ax.set_ylabel('VClamp current (pA)')
ax.set_xlabel('Time (ms)')
#ax.set_ylim(-20,1)
ax.set_xlim(1980,2300)


ax2  = fig.add_subplot(122)

ax2.plot(gocs.record['time'],gocs.GRC_AA_L[0].i['AMPA'][0].mul(1e3),label='AMPA_DET_VI')
ax2.plot(gocs.record['time'],gocs.GRC_AA_L[0].i['NMDA'][0].mul(1e3),label='NMDA_DET_VI')
ax2.set_ylabel('Synaptic current (pA)')
ax2.set_xlabel('Time (ms)')

plt.show()





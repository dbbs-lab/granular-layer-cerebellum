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

gocs.createsyn(nmf=1,record_all=1)

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


nc_mf = [h.NetCon(stim,goc.input,0,0,1) for goc in gocs.MF_L]

for goc in gocs.MF_L:
    print goc.postsyns
    print goc.postsyns['AMPA'][0].U

v = h.Vector()
v.record(vc._ref_i)

tvec = h.Vector()
tvec.record(h._ref_t)

h.tstop = 3000
h.celsius = 32  # Cesana et al. 2013: All experiments were performed at 31–33°C.
v_init = -70
h.finitialize(v_init)
h.continuerun(h.tstop)


fig = plt.figure()
ax  = fig.add_subplot(121)

vv = np.array([tvec,v]).transpose()

# Calc VClamp i features
# Holding current
start_idx = np.where(vv[:,0] < stim.start)[0][-1]
EPSC = vv[start_idx:,1]
baseline = vv[start_idx,1]

# Peak current
print "Peak current = %d pA" % (np.min(vv[:,1]-baseline)*1e3)
# Time to peak
time_to_20 = vv[vv[:,1].__le__(np.min(vv[:,1]-baseline)*.2+baseline).nonzero()[0][0],0]
time_to_80 = vv[vv[:,1].__le__(np.min(vv[:,1]-baseline)*.8+baseline).nonzero()[0][0],0]
print "Time to peak = %04.2f ms" % (vv[np.argmin(vv[:,1]),0]-stim.start)
print "Raise time (20% to 80% pf peak) = ","%04.2f ms" % (time_to_80 - time_to_20)
# Total charge
print "EPSC charge = %04.2f fC" % (np.abs(np.sum(np.diff(vv[:,0])*(vv[:-1,1]-baseline)))*1e3)  # ms * nA = 1e-3 * 1e-9 C = 1e-12 C = pC 1pC = 1000 fC

ax.plot(vv[10:-1,0],vv[10:-1,1]*1e3)
# ax.plot(gocs.record['time'],gocs.record['vm'])
# ax.plot(gocs.record['time'],gocs.record['dend'][0])
ax.set_ylabel('VClamp current (pA)')
ax.set_xlabel('Time (ms)')
#ax.set_ylim(-20,1)
ax.set_xlim(1980,2300)


ax2  = fig.add_subplot(122)

ax2.plot(tvec,gocs.MF_L[0].i['AMPA'][0].mul(1e3),label='AMPA_DET_VI')
ax2.plot(tvec,gocs.MF_L[0].i['NMDA'][0].mul(1e3),label='NMDA_DET_VI')
ax2.set_ylabel('Synaptic current (pA)')
ax2.set_xlabel('Time (ms)')

plt.show()





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

gocs.createsyn(npf=1,ngrc=1,record_all=1)

vc = h.VClamp(0.5)
vc.amp[0] = -70 #Bureau 2000 -70 , Misra 2000 -30
vc.dur[0] = 200

stim = h.NetStim(0.5)
stim.number = 1
stim.interval = 10
stim.start = 20

print gocs.GRC_L[0].postsyns.keys()
print gocs.PF_L[0].postsyns.keys()


print "*******",gocs.GRC_L[0].postsyns['NMDA'][0].U


nc1 = [h.NetCon(stim,pf.input,0,0,1) for pf in gocs.PF_L]
nc2 = [h.NetCon(stim,grc.input,0,0,1) for grc in gocs.GRC_L]
#nc2 = h.NetCon(stim,gocs.GRC_L[0].input,0,0,1)

# v = h.Vector()
# nc.record(v)

print gocs.GRC_L[0]

h.tstop = 200
h.celsius = 35.5
h.init()
print "run"
h.run() # runs properly with single thread
print "done"

# v.printf()
fig = [plt.figure(),plt.figure(),plt.figure()]
ax1  = [fig[0].add_subplot(121),fig[1].add_subplot(121),fig[2].add_subplot(121)]

for a in ax1:
#    a.plot(gocs.record['time'],gocs.record['dend'][1])
    a.plot(gocs.record['time'],gocs.record['vm'])
    a.set_ylabel('Membrane potential (mV)')
    a.set_xlabel('Time (ms)')
    a.set_ylim(-31,-29)


ax2  = [fig[0].add_subplot(122),fig[1].add_subplot(122),fig[2].add_subplot(122)]
#ax3  = fig[0].add_subplot(224)
# print gocs.GRC_L[0].SpikeTrain_input[1].printf()
print gocs.PF_L[0].SpikeTrain_input[1].printf()
print gocs.PF_L[0].postsyns['NMDA'][0].gmax
# print gocs.PF_L[0].i['AMPA'][0].printf()
ax2[0].plot(gocs.record['time'],gocs.GRC_L[0].i['NMDA'][0].mul(1e3),label='MARKOV')
ax2[0].plot(gocs.record['time'],gocs.PF_L[0].i['NMDA'][0].mul(1e3),label='EXPSYN')
ax2[1].plot(gocs.record['time'],gocs.GRC_L[0].i['AMPA'][0].mul(1e3),label='MARKOV')
ax2[1].plot(gocs.record['time'],gocs.PF_L[0].i['AMPA'][0].mul(1e3),label='EXPSYN')
ax2[2].plot(gocs.record['time'],gocs.GRC_L[0].i['KAIN'][0].mul(1e3),label='MARKOV')
#ax2[2].plot(gocs.record['time'],gocs.PF_L[0].i['KAIN'][0].mul(1e3),label='EXPSYN')
# ax2[0].plot(gocs.record['time'],gocs.GRC_L[10].g['NMDA'][0],label='MARKOV')
# ax2[0].plot(gocs.record['time'],gocs.PF_L[0].g['NMDA'][0],label='EXPSYN')
# ax2[1].plot(gocs.record['time'],gocs.GRC_L[10].g['AMPA'][0],label='MARKOV')
# ax2[1].plot(gocs.record['time'],gocs.PF_L[0].g['AMPA'][0],label='EXPSYN')
for a in ax2:
    a.set_ylabel('Synaptic current (pA)')
    a.set_xlabel('Time (ms)')

ax2[0].legend(('Markov','dual-Exponential'),loc=4)
ax2[1].legend(('Markov','dual-Exponential'),loc=4)


ax2[0].set_title('NMDA')
ax2[1].set_title('AMPA')


ax2[0].set_xlim(18,200)
ax2[1].set_xlim(18,25)
#ax2[0].set_ylim(-5,0)
#ax2[1].set_ylim(-50,0)
plt.show()





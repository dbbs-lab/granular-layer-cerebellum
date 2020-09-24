# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

import h5py
import numpy as np
from matplotlib import pyplot as plt

from templates.golgi.Golgi_template import Goc
from templates.gapj.gapj import Gapj
import toolbox as tb

from mpi4py import MPI
comm = MPI.COMM_WORLD

from neuron import h
from neuron import gui
pc = h.ParallelContext()
rank = int(pc.id())
size = int(pc.nhost())

h.nrn_load_dll('$i386/')

gocs = [tb.makecell(Goc(np.array([0.,0.,0.])), rank, rank, rank,pc)]
print gocs


if (rank == 1):
    stim = h.IClamp(.5, sec=gocs[0][1][1].soma)
    stim.amp = -0.015
    stim.dur = 200

gocs[0][1][1].creategap(1,gocs[0][1][0],50,pc,record_all=1)

print "ngapj ",len(gocs[0][1][1].GAP_L)
gocs[0][1][1].GAP_L[0].gapj.g = 130*9 # pS
for g in gocs[0][1][1].GAP_L:
    print "gapj g",g.gapj.g
    
goc2goc_gap_nc = pc.target_var(gocs[0][1][1].GAP_L[0].gapj._ref_vgap, not rank)

pc.setup_transfer()
h.tstop = 200
h.celsius = 35.5
h.init()
print "run"
h.run() # runs properly with single thread
print "done"

fig = plt.figure()
ax1  = fig.add_subplot(121)

ax1.plot(gocs[0][1][1].record['time'],gocs[0][1][1].record['vm'])
ax1.set_title('Golgi on processor %d' % rank)
ax1.set_ylabel('Membrane potential (mV)')
ax1.set_xlabel('Time (ms)')
ax2  = fig.add_subplot(122)
ax2.plot(gocs[0][1][1].record['time'],gocs[0][1][1].GAP_L[0].record['i_local'].mul(1e3))
ax2.set_ylabel('Junction current (pA)')
ax2.set_xlabel('Time (ms)')

ax1.set_ylim(-70,20)
ax2.set_ylim(-140,140)
plt.show()





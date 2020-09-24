# -*- coding: utf-8 -*-

import sys
import h5py
import numpy as np
from matplotlib import pyplot as plt


from mpi4py import MPI
comm = MPI.COMM_WORLD

from neuron import h
from neuron import gui
pc = h.ParallelContext()
rank = int(pc.id())
size = int(pc.nhost())

h.nrn_load_dll('$i386/')

soma = h.Section()
soma.diam = 10
soma.L = 100/(3.14*soma.diam)
soma.insert('hh')

soma2 = h.Section()
soma2.diam = 10
soma2.L = 100/(3.14*soma2.diam)
soma2.insert('hh')

if (rank == 0):
    stim = h.IClamp(.5)
    stim.amp = 0.5
    stim.dur = 0.1
    soma.gnabar_hh = 0
    soma.gkbar_hh = 0
    soma.el_hh = -65
    soma.gl_hh = .001

    soma2.gnabar_hh = 0
    soma2.gkbar_hh = 0
    soma2.el_hh = -65
    soma2.gl_hh = .001

gap = h.HalfGap(.5, sec = soma)
gap.g = .01 # nS

gap2 = h.HalfGap(.5, sec = soma2)
gap2.g = .01 # nS

pc.source_var(soma(.5)._ref_v, rank)
pc.source_var(soma2(.5)._ref_v, rank)

vvec = h.Vector()
print gap.vgap

pc.target_var(gap2._ref_vgap,  (rank+1)%2)
vvec.record(gap._ref_i)

pc.setup_transfer()
h.init()
print "run"
h.run() # runs properly with single thread
print "done"

vvec.printf()

# if rank == 0: vvec.printf()
# fig = plt.figure()
# ax  = fig.add_subplot(111)

# ax.plot(vvec)

# # ax.set_ylim(-20e-2,0)
# plt.show()





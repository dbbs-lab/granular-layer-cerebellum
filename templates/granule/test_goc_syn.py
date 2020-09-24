# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

from templates.granule.GRANULE_Cell import Grc
from neuron import h
from neuron import gui
from templates.synapse.synapse import Synapse
import numpy as np
from matplotlib import pyplot as plt
import h5py

save = 0
plot = 1

grc = Grc(np.array([0.,0.,0.]),record_all=1)

nmf = 0
nrel = 4
mf = [h.NetStim(0.5) for i in range(nmf)]
mfsyn = [Synapse('glom',grc,grc.soma,nrel=nrel) for i in range(nmf)]
for i in range(nmf):
    mfsyn[i].input.start = 100
    mfsyn[i].input.interval = 10
    mfsyn[i].input.number = 1
    mfsyn[i].input.noise = 0

ngoc = 1
goc = [h.NetStim(0.5) for i in range(ngoc)]
goc_syn = [Synapse('goc',grc,grc.soma,record_all=1) for i in range(ngoc)]
for i in range(ngoc):
    goc_syn[i].input.start = 100
    goc_syn[i].input.interval = 10
    goc_syn[i].input.number = 10
    goc_syn[i].input.noise = 0

tvec = h.Vector()
tvec.record(h._ref_t)

vc = h.SEClamp(0.5, sec = grc.soma)
vc.amp1 = -10  # Mapelli et al 2009
vc.dur1 = 10000

# vc = h.VClamp(0.5, sec = grc.soma)
# vc.amp[0] = 0
# vc.dur[0] = 10000


h.celsius = 37
h.dt = 0.025
h.tstop = 400
h.v_init = -65


h.run()

# for goc_s in goc_syn:
#     print goc_s.i['GABA'][0].printf()
#     print goc_s.postsyns['GABA'][0].gmaxA1
#     print goc_s.postsyns['GABA'][0].gmaxA6

if plot:
    plt.figure()
    plt.plot(tvec,grc.record['vm'])
    plt.title('Menbrane Potential')
    plt.ylabel('Vm')
    plt.xlabel('Time (ms)')
    plt.figure()
    plt.plot(tvec,np.array(goc_syn[0].i['GABA'][0])*1e3)
    plt.title('GABA Current')
    plt.ylabel('pA')
    plt.xlabel('Time (ms)')
    plt.show()

# if save:
#     f = h5py.File('grc_test.hdf5','w')
#     grc_save = f.create_group('grc')
#     grc_save.create_dataset('time',data=grc.record['time'])
#     grc_save.create_dataset('vm',data=grc.record['vm'])
#     grc_save.create_dataset('spk',data=grc.record['spk'])
#     f.close()
# else:
#     f = h5py.File('grc_test.hdf5','r')
#     time = np.array(f['grc/time'])
#     vm = np.array(f['grc/vm'])
#     spk = np.array(f['grc/spk'])
#     diff = vm-np.array(grc.record['vm'])
#     print spk.shape,np.array(grc.record['spk']).shape
#     diff_spk = spk-np.array(grc.record['spk'])
#     if np.all(diff  == 0):
#         print 'No differences!!'
#     else:
#         print ' ALERT treces changed*********'
#         print np.mean(diff)
#         print diff_spk


# f = plt.figure()
# ax = f.add_subplot(111)
# ax.plot(grc.record['time'],grc.record['vm'])
# f.show()


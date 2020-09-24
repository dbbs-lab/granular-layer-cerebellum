# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

from neuron import h
from neuron import gui
from templates.synapse.synapse import Synapse
from templates.granule.GRANULE_Cell import Grc
import numpy as np
from matplotlib import pyplot as plt
import h5py

save = 0
plot = 0

grc = Grc(np.array([0.,0.,0.]),record_all=1)
#grc = Grc(record_all=1)



nmf = 4
nrel = 0
mf = [h.NetStim(0.5) for i in range(nmf)]
mfsyn = [Synapse('glom',grc,grc.soma,nrel=nrel) for i in range(nmf)]

start = 100
mfs_interval = 10

stim_times = np.arange(start, start+(mfs_interval*nmf), mfs_interval)

for i in range(nmf):
    mfsyn[i].input.start = stim_times[i]
    mfsyn[i].input.interval = 5
    mfsyn[i].input.number = 1
    mfsyn[i].input.noise = 0


time = h.Vector()
time.record(h._ref_t,0.1)

h.celsius = 37
h.dt = 0.025
h.tstop = 500
h.v_init = -65
ica = h.Vector()
ica.record(grc.soma(0.5)._ref_cai,0.1)

h.run()

if plot:
    plt.plot(time,grc.record['vm'])
    plt.show()

if save:
    f = h5py.File('grc_test.hdf5','w')
    grc_save = f.create_group('grc')
    grc_save.create_dataset('time',data=time)
    grc_save.create_dataset('vm',data=grc.record['vm'])
    grc_save.create_dataset('spk',data=grc.record['spk'])
    f.close()
#else:
#    f = h5py.File('grc_test.hdf5','r')
#    time = np.array(f['grc/time'])
#    vm = np.array(f['grc/vm'])
#    spk = np.array(f['grc/spk'])
#    diff = vm-np.array(grc.record['vm'])
#    print spk.shape,np.array(grc.record['spk']).shape
#    diff_spk = spk-np.array(grc.record['spk'])
#    if np.all(diff  == 0):
#        print 'No differences!!'
#    else:
#        print ' ALERT treces changed*********'
#        print np.mean(diff)
#        print diff_spk
# f = plt.figure()
# ax = f.add_subplot(111)
# ax.plot(time,grc.record['vm'])
# f.show()


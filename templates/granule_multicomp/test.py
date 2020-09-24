# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

from GRANULE_Cell import Grc
from neuron import h
from neuron import gui
from templates.synapse.synapse import Synapse
import numpy as np
#from matplotlib import pyplot as plt
#import h5py

save = 0
plot = 0

grc = Grc(np.array([0.,0.,0.]))

nmf = 1
nrel = 4
mf = [h.NetStim(0.5) for i in range(nmf)]
mfsyn = [Synapse('glom',grc,grc.soma,nrel=nrel) for i in range(nmf)]
for i in range(nmf):
    mfsyn[i].input.start = 100
    mfsyn[i].input.interval = 10
    mfsyn[i].input.number = 10
    mfsyn[i].input.noise = 0

h.celsius = 37
h.dt = 0.025
h.tstop = 400
h.v_init = -65


h.run()

# if plot:
#     plt.plot(grc.record['time'],grc.record['vm'])
#     plt.show()

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


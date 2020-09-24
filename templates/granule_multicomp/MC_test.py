import sys

from GRANULE_CELL import Grc
from neuron import h
from neuron import gui
from ../synapse import Synapse
import numpy as np
#from matplotlib import pyplot as plt
import h5py

plot=1
save=0
	
grc = Grc(np.array([0.,0.,0.]))


nrel = 4			

mfsyn = [Synapse('glom',grc,grc.dend4[0],nrel=nrel)]
mfsyn.append(Synapse('glom',grc,grc.dend4[1],nrel=nrel))
mfsyn.append(Synapse('glom',grc,grc.dend4[2],nrel=nrel))
mfsyn.append(Synapse('glom',grc,grc.dend4[3],nrel=nrel))

#grc.synapses()	


for i in range(4):
    mfsyn[i].input.start = 20
    mfsyn[i].input.interval = 10
    mfsyn[i].input.number = 1
    mfsyn[i].input.noise = 0	

h.celsius=30
h.dt = 0.025
h.tstop = 150
h.v_init = -70

h.run()


if plot:
    plt.plot(grc.record['time'],grc.record['vm'])
    plt.show()

if save:
    f = h5py.File('grc_test.hdf5','w')
    grc_save = f.create_group('grc')
    grc_save.create_dataset('time',data=grc.record['time'])
    grc_save.create_dataset('vm',data=grc.record['vm'])
    grc_save.create_dataset('spk',data=grc.record['spk'])
    f.close()

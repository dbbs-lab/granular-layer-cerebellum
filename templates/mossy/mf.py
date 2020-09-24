# -*- coding: utf-8 -*-
from neuron import h
from neuron import gui
import numpy as np
import h5py
#import sys
#sys.path.append('../')
#name = sys.argv[1]

class Mf:
    def __init__(self, spike_train=None, position = np.array([0,0,0]),whatami ='mossy',record_all = 0):
        self.record_all = record_all
        self.spike_train = spike_train
        self.whatami = whatami
	
        self.position = position
        if spike_train is not None:
            self.spk_vector = h.Vector()
        
            # Populate Vector
            for time in spike_train:
                self.spk_vector.append(float(time))

            self.output = h.VecStim()
            self.output.play(self.spk_vector)
        else:
            self.output = h.NetStim(0.5)
            self.output.start = -10
            self.output.number = 0
            self.output.interval = 1e9
            
        self.record = {}
        self.nc_spike = h.NetCon(self.output,None)
        self.record['spk'] = h.Vector()
        self.nc_spike.record(self.record['spk'])

        # if record_all:
            # record here variable different from spikes

    # def pconnect(self,pc,source,syn_idx,type_syn):
    #     if type_syn == 'mf':
    #         source = int(source)
    #         self.mfncpc.append(pc.gid_connect(source, self.MF_L[syn_idx].input))
    #         self.mfncpc[-1].delay = 1
    #         self.mfncpc[-1].weight[0] = 1
    #         return self.mfncpc[-1]

    def destroy(self):
        if record_all:
            del self.nc_spike
            del self.record['spk']
        del self.output
        del self

# -*- coding: utf-8 -*-
from neuron import h
from neuron import gui
import numpy as np

class Mf_old:
    def __init__(self, spike_train=None,position = np.array([0,0,0]),background = 3.9, cv = 1,whatami ='glom'):
        self.whatami = whatami

	self.background = background
	
	self.position = position

        self.mfncpc = []
	
        self.record = {}
        if spike_train is not None:
            self.spk_vector = h.Vector()

            # Populate Vector
            for time in spike_train:
                self.spk_vector.append(float(time))
            self.spike = h.VecStim()
            self.spike.play(self.spk_vector)
        else:
            self.spike = h.NetStim(0.5)
            self.spike.start = -10
            self.spike.number = 1
            self.spike.interval = 1e9
        self.nc_spike = h.NetCon(self.spike,None)
        self.record['spk'] = h.Vector()
        self.nc_spike.record(self.record['spk'])

    def pconnect(self,pc,source,type_syn):
        if type_syn == 'mf':
            source = int(source)
            self.mfncpc.append(pc.gid_connect(source, self.spike))
            self.mfncpc[-1].delay = 1
            self.mfncpc[-1].weight[0] = 1
            return self.mfncpc[-1]
        else:
            print "WRONG SYNTYPE!!!!!"

    def destroy(self):
        for m in self.mfncpc:
            del m
        
        del self.nc_spike
        del self.record['spk']
        del self

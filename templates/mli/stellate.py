# -*- coding: utf-8 -*-
from neuron import h
from templates.synapse.synapse import Synapse
from templates.gapj.gapj import Gapj
import numpy as np
import random as rnd



class Stellate:
    def __init__(self,position, model_type='C', background = 0, erev = -62, record_all = 0,leak_range=0, Dt = 0.1):
        self.record_all = record_all
        # if record_all:
        #     print "Recording all in Stl"
	self.soma = h.Section()
	self.soma.nseg = 1 
        self.soma.cm = 1 # pF/cm2
	self.soma.diam = 11.7 # gives 4.3 pF
	self.soma.L = self.soma.diam

        self.whatami = "stl"

        self.model_type = model_type
        
        self.position = position
	self.soma.push()
	h.pt3dclear()
	h.pt3dadd(position.item(0), position.item(1) - self.soma.L, position.item(2), self.soma.diam)
	h.pt3dadd(position.item(0), position.item(1) + self.soma.L, position.item(2), self.soma.diam)
	h.pop_section()

        # Create spike output object for the pconnect() of postsynaptic  neurons
        self.spike = h.NetStim(0.5, sec= self.soma)
        self.spike.start = -10
        self.spike.number = 1
        self.spike.interval = 1e9

        # Create spike input object
        # This will be the target of input Necons defined in synapse.py for incoming spikes if the model is a Relay
        self.pre_spike = h.NetStim(0.5, sec= self.soma)
        self.pre_spike.start = -10
        self.pre_spike.number = 1
        self.pre_spike.interval = 1e9

        self.nc_spike = h.NetCon(self.pre_spike, self.spike,-20,0,1, sec = self.soma)
        if self.model_type=='Relay':
            # Set transmission of spikes to have a 1 ms delay if the model works as a relay
            self.nc_spike.delay = 1

        self.record = {}

        if self.model_type=='C':
            # Conductance based model

            self.soma.insert('MLI_lkg')
            self.soma.insert('MLI_Na')
            self.soma.insert('MLI_KV')
            self.soma.insert('MLI_KM')
            self.soma.insert('MLI_NAP')

            self.soma.insert('GRANULE_NAR')
            self.soma.insert('GRANULE_KCA')
            self.soma.insert('GRANULE_CA')
            self.soma.insert('GRANULE_CALC')

            h.usetable_GRANULE_NAR = 1
            h.usetable_GRANULE_KCA = 0
            h.usetable_GRANULE_CA = 1

            
            self.soma.el_MLI_lkg = erev 
            self.soma.gbar_MLI_Na = 0.07
            self.soma.gbar_MLI_KV = 0.05
            self.soma.gbar_GRANULE_KCA = 0.0045 * 2 
            self.soma.gbar_MLI_KM = 0.001
            self.soma.gbar_MLI_lkg = 116e-6 # S/cm2

            # Random distribution of leak conductance
            if leak_range > 0:
                lkg_rnd = 1 + rnd.uniform(-1,1) * leak_range
                self.soma.gbar_MLI_lkg = self.soma.gbar_MLI_lkg * lkg_rnd

            # Connect spike detection in soma to the pre_spike object
            self.cell_nc = h.NetCon(self.soma(1)._ref_v, self.pre_spike,0,0,1,sec = self.soma)
            
            if self.record_all:
                # Record soma Vm
                self.record['vm'] = h.Vector()
                self.record['vm'].record(self.soma(.5)._ref_v, Dt, sec = self.soma)

        else:
            
            self.bg = h.NetStim(0.5, sec= self.soma)
            self.bg.start = 0
            if background>0:
                self.bg.number = 1e9
                self.bg.interval = 1e3/background
            else:
                self.bg.number = 0
                self.bg.interval = 1e9                
            self.bg.noise = 0.54 # from (Lachamp et al., 2009) in absence of SR95531

            self.bg_nc = h.NetCon(self.bg, self.pre_spike,0,0,1,sec = self.soma)

	self.PF_L = []
	self.GRC_L = []
	self.MLI_L = []	
        self.pfncpc = []
        self.mlincpc = []
        self.GAP_L = []
        
        self.record['spk'] = h.Vector()
	self.nc_spike.record(self.record['spk'])

    #Synapses
    def createsyn(self,npf=0,ngrc=0,nmli=0,record_all=0,weight_var = 0, Dt = 0.1):
        if self.model_type=='C':
            syntype = 'E'

        if self.model_type=='Relay':
            syntype = 'R'
            npf = 1
            
        for i in range(npf):
            # Use here the source target sting name
            # so the presynaptic link is not made
            # and it will have to be manged later
            # by the gid connect for parallel simulations
            self.PF_L.append(Synapse('pf',self,self.soma,syntype = syntype,record_all = record_all,weight=1+rnd.random()*weight_var, Dt = Dt))

        for i in range(ngrc):
            # Use here the source target sting name
            # so the presynaptic link is not made
            # and it will have to be manged later
            # by the gid connect for parallel simulations
            self.GRC_L.append(Synapse('grc',self,self.soma,syntype = syntype,record_all = record_all,weight=1+rnd.random()*weight_var,Dt = Dt))

        if self.model_type=='C':
            for i in range(nmli):
                self.MLI_L.append(Synapse('stl',self,self.soma,syntype = syntype,record_all= record_all,weight=1+rnd.random()*weight_var,Dt = Dt))

    def creategap(self,ngapj,ggid,g_gap,pc = None, Dt = 0.1):
        if pc != None:
            pc.source_var(self.soma(.5)._ref_v, ggid)
        for gg in range(ngapj):
            # Remember to set the conductance!!!!
            # Gapj uses a targetting gid idea which is
            # antisymmetric with respect to the synaptic gid.
            self.GAP_L.append(Gapj(self,self.soma,g_gap,record_all=0,Dt = Dt))


        

    def fr(self,start=0):
	    v = np.array(self.record['spk'])
	    return 1000/np.mean(np.diff(v[v>start]))

    def pconnect(self,pc,source,syn_idx,type,conduction_speed=0,grc_positions=[]):
        if type == 'grc':
            source = int(source)
            if self.model_type == 'C':
                self.pfncpc.append(pc.gid_connect(source, self.GRC_L[syn_idx].input))
                self.pfncpc[-1].weight[0] = 1
            if self.model_type == 'Relay':
                self.pfncpc.append(pc.gid_connect(source, self.GRC_L[0].input))
                self.pfncpc[-1].weight[0] = 1
            self.pfncpc[-1].delay = np.abs(self.position.item(0)-grc_positions[0]) * 1e3 / conduction_speed  + 1 # 1 ms of synaptic transmission time
            return self.pfncpc[-1]
        if type == 'pf':
            source = int(source)
            if self.model_type == 'C':
                self.pfncpc.append(pc.gid_connect(source, self.PF_L[syn_idx].input))
                self.pfncpc[-1].weight[0] = 1
            if self.model_type == 'Relay':
                self.pfncpc.append(pc.gid_connect(source, self.PF_L[0].input))
                self.pfncpc[-1].weight[0] = 1
            self.pfncpc[-1].delay = np.abs(self.position.item(0)-grc_positions[0]) * 1e3 / conduction_speed  + 1 # 1 ms of synaptic transmission time
            return self.pfncpc[-1]
        if type == 'pf_fake':
            if self.model_type == 'C':
                self.pfncpc.append(h.NetCon(source.spike,self.PF_L[syn_idx].input))
                self.pfncpc[-1].delay = 1
                self.pfncpc[-1].weight[0] = 1
            if self.model_type == 'Relay':
                self.pfncpc.append(h.NetCon(source.spike,self.PF_L[0].input))
                self.pfncpc[-1].delay = 1
                self.pfncpc[-1].weight[0] = 1
            return self.pfncpc[-1]
        if type == 'stl':
            source = int(source)
            self.mlincpc.append(pc.gid_connect(source, self.MLI_L[syn_idx].input))
            self.mlincpc[-1].delay = 1
            self.mlincpc[-1].weight[0] = 1
            return self.mlincpc[-1]

    def random_boot(self):
        boot_time = rnd.uniform(0,100)
        self.soma.boot_time_MLI_lkg = boot_time

    def destroy(self):
        del self.nc_spike
        if self.model_type=='C':
            del self.cell_nc
        else:
            del self.bg_nc
       
        for f in self.PF_L:
            f.destroy()
            del f
        for f in self.MLI_L:
            f.destroy()
            del f
        for f in self.pfncpc:
            del f
        del self.pfncpc
        for f in self.mlincpc:
            del f
        for f in self.GAP_L:
            f.destroy()
            del f
        for r in self.record:
            del r
        del self

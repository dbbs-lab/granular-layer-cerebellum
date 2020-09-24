# -*- coding: utf-8 -*-
from neuron import h
from neuron import gui
import numpy as np
import random as rnd
#seed = 123456
#rnd.seed(seed)
from templates.synapse.synapse import Synapse
from templates.gapj.gapj import Gapj


class Goc:
    def __init__(self,position = np.array([0,0,0]),record_all=0,leak_range=0, Dt= 0.1):
        self.record_all = record_all
        # if record_all:
        #     print "Recording all in Goc"
	self.soma = h.Section(cell=self)
  	self.soma.nseg = 1
	self.soma.diam = 27 # 22 pF Dieudonne98
	self.soma.L = 27
	self.soma.Ra = 100 # From Roth&Hausser2000

        self.whatami = "goc"

        self.position = position
	self.soma.push()
	h.pt3dclear()
	h.pt3dadd(position.item(0), position.item(1) - self.soma.L, position.item(2), self.soma.diam)
	h.pt3dadd(position.item(0), position.item(1) + self.soma.L, position.item(2), self.soma.diam)
	h.pop_section()

	self.soma.insert('Golgi_lkg')
	self.soma.insert('Golgi_Na')
	self.soma.insert('Golgi_NaR')
	self.soma.insert('Golgi_NaP')
 	self.soma.insert('Golgi_Ca_HVA')
	self.soma.insert('Golgi_Ca_LVA')
	self.soma.insert('Golgi_KV')
        #self.soma.gbar_Golgi_KV = 0.002
	self.soma.insert('Golgi_KM')
	self.soma.insert('Golgi_KA')
	self.soma.insert('Golgi_BK')
  	self.soma.insert('Golgi_SK2')
	self.soma.insert('Golgi_hcn1')
        self.soma.insert('Golgi_hcn2')
 	self.soma.insert('Golgi_CALC')
	self.soma.insert('Golgi_CALC_ca2')

 	#h.usetable_Golgi_BK = 0
 	h.usetable_Golgi_Ca_LVA = 1
  	h.usetable_Golgi_Ca_HVA = 1
 	h.usetable_Golgi_KA = 1
 	h.usetable_Golgi_KV = 1
 	h.usetable_Golgi_NaR = 1
 	h.usetable_Golgi_KM = 1
 	h.usetable_Golgi_Na = 1
 	h.usetable_Golgi_NaP = 1

	self.soma.ena=87.39
 	self.soma.ek=-84.69

 	self.soma.cai0_Golgi_CALC = 50e-6
	self.soma.ca2i0_Golgi_CALC_ca2 = 50e-6

 	self.soma.cai = 50e-6
 	self.soma.cao = 2
	
	self.soma.ca2i = 50e-6
	self.soma.ca2o = 2

	#self.soma.el_Golgi_lkg = -65

	self.axon = h.Section(cell=self)
	self.axon.nseg = 100
	self.axon.diam = 2.4 # gives 90 pF to get to the 145 pF Forti06
	self.axon.L = 1200
	self.axon.Ra = 100
	self.axon.insert('Golgi_lkg')

	self.dendriti = [h.Section(cell=self) for x in range(3)]
        # Dendrites are assumed to be 0 and 2 basolateral, 1 apical
	for d in (self.dendriti):
	    d.nseg = 10
	    d.diam = 3
	    d.L = 113
	    d.Ra = 100
	    d.insert('Golgi_lkg')

	self.axon.connect(self.soma,0,0)
	for d in self.dendriti:
	    d.connect(self.soma,1,0)	


        # Random distribution of leak conductance
        self.compartments = [self.soma, self.axon, self.dendriti[0], self.dendriti[1], self.dendriti[2]]
        if leak_range > 0:
            lkg_rnd = 1 + rnd.uniform(-0.5,0.5) * leak_range
            for sec in self.compartments:
                sec.gbar_Golgi_lkg = sec.gbar_Golgi_lkg * lkg_rnd


	self.MF_L = []
	self.PF_L = []
	self.GRC_L = []
	self.GRC_AA_L = []
	self.STL_L = []
	self.mfncpc = []
	self.aancpc = []
	self.pfncpc = []
	self.stlncpc = []
	self.gocncpc = []
        self.GAP_L = []
        self.GOC_L = []

        self.spike = h.NetStim(0.5, sec= self.soma)
        self.spike.start = -10
        self.spike.number = 1
	self.spike.interval = 1e9
        self.nc_spike = h.NetCon(self.soma(1)._ref_v, self.spike,-20,0,1, sec = self.soma)

        #self.fr = h.Cellfr(0.5, sec = self.soma)
        #self.fr_nc = h.NetCon(self.spike,self.fr,0,0,1)
        
        self.record = {}

        self.record['spk'] = h.Vector()
	self.nc_spike.record(self.record['spk'])


        if self.record_all:
            self.record['vm'] = h.Vector()
            self.record['vm'].record(self.soma(.5)._ref_v, Dt, sec = self.soma)

            # self.record['dend'] = []
            # for d in self.dendriti:
            #     self.record['dend'].append(h.Vector())
            #     self.record['dend'][-1].record(d(.5)._ref_v, Dt, sec = d)

    #Synapses
    def createsyn(self,nmf=0,naa=0,ngrc=0,npf=0,nmli=0,ngoc=0,nrel = 0,record_all = 0,weight_var = 0, Dt = 0.1):
        # Use here the source target sting name
        # so the presynaptic link is not made
        # and it will have to be manged later
        # by the gid connect for parallel simulations
        # Mossy
	for i in range(nmf):
	    self.MF_L.append(Synapse('glom',self,self.dendriti[0],nrel,record_all=record_all,weight=1+rnd.random()*weight_var, Dt = Dt)) # To basal dendrite
            if record_all:
                self.record['glom_spk_'+str(i)] = self.MF_L[-1].SpikeTrain_input[1]
                for mfsyn_type,mf_syn in self.MF_L[-1].i.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['glom_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
        # Parallel from grc
	for i in range(ngrc):
	    self.GRC_L.append(Synapse('grc',self,self.dendriti[1],syntype='KE',record_all=record_all,weight=1+rnd.random()*weight_var, Dt = Dt)) # To apical dendrite
            if record_all:
                self.record['grc_spk_'+str(i)] = self.GRC_L[-1].SpikeTrain_input[1]
                for mfsyn_type,mf_syn in self.GRC_L[-1].i.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['grc_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                for mfsyn_type,mf_syn in self.GRC_L[-1].g.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['grc_'+str(i)+'_g_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
        # Ascending Axon from grc
	for i in range(naa):
	    self.GRC_AA_L.append(Synapse('aa',self,self.dendriti[0],syntype='AN',record_all=record_all,weight=1+rnd.random()*weight_var, Dt = Dt)) # To apical dendrite
            if record_all:
                self.record['grcaa_spk_'+str(i)] = self.GRC_AA_L[-1].SpikeTrain_input[1]
                for mfsyn_type,mf_syn in self.GRC_AA_L[-1].i.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['grcaa_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                for mfsyn_type,mf_syn in self.GRC_AA_L[-1].g.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['grcaa_'+str(i)+'_g_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
        # Parallel from netstim
	for i in range(npf):
	    self.PF_L.append(Synapse('pf',self,self.dendriti[1],syntype = 'KE',record_all=record_all,weight=1+rnd.random()*weight_var, Dt = Dt)) # To apical dendrite
            if record_all:
                self.record['pf_spk_'+str(i)] = self.PF_L[-1].SpikeTrain_input[1]
                for mfsyn_type,mf_syn in self.PF_L[-1].i.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['pf_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                for mfsyn_type,mf_syn in self.PF_L[-1].g.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['pf_'+str(i)+'_g_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
        # Inibition
	for i in range(nmli):
	    self.STL_L.append(Synapse('stl',self,self.dendriti[1],syntype = 'E',record_all=record_all,weight=1+rnd.random()*weight_var, Dt = Dt)) # To apical dendrite
            if record_all:
                self.record['mli_spk_'+str(i)] = self.STL_L[-1].SpikeTrain_input[1]
                for mfsyn_type,mf_syn in self.STL_L[-1].i.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['mli_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                for mfsyn_type,mf_syn in self.STL_L[-1].g.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['mli_'+str(i)+'_g_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                    
        # Inibition
	for i in range(ngoc):
	    self.GOC_L.append(Synapse('goc',self,self.dendriti[2],record_all=record_all,weight=1+rnd.random()*weight_var, Dt = Dt)) # To basal dendrite
            if record_all:
                self.record['goc_spk_'+str(i)] = self.GOC_L[-1].SpikeTrain_input[1]
                for mfsyn_type,mf_syn in self.GOC_L[-1].i.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['goc_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                for mfsyn_type,mf_syn in self.GOC_L[-1].g.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['goc_'+str(i)+'_g_'+mfsyn_type+'_rel_'+str(rel_n)] = rel

                        
    def creategap(self,ngapj,ggid,g_gap,pc = None, record_all = 0, max_ngap = 100, Dt = 0.1):
        if ngapj > max_ngap:
            print "Too many gapj!!!!!"
            return
        if ngapj > 0 :
            pc.source_var(self.soma(.5)._ref_v, int(ggid+2e9), sec=self.soma)
        for gg in range(ngapj):
            # Remember to set the conductance!!!!
            # Gapj uses a targetting gid idea which is
            # antisymmetric with respect to the synaptic gid.
            self.GAP_L.append(Gapj(self,self.soma,g_gap,record_all, Dt = Dt))
        self.gapid = ggid+2e9

    def pconnect(self,pc,source,syn_idx,type,conduction_speed=0,grc_positions=[]):
        if type == 'mf':
            source = int(source)
            self.mfncpc.append(pc.gid_connect(source, self.MF_L[syn_idx].input))
            self.mfncpc[-1].delay = 1
            self.mfncpc[-1].weight[0] = 1
            return self.mfncpc[-1]
        if type == 'aa':
            source = int(source)
            self.aancpc.append(pc.gid_connect(source, self.GRC_AA_L[syn_idx].input))
            self.aancpc[-1].delay = 1
            self.aancpc[-1].weight[0] = 1
            return self.aancpc[-1]

        if type == 'grc':
            source = int(source)
            self.pfncpc.append(pc.gid_connect(source, self.GRC_L[syn_idx].input))
            self.pfncpc[-1].delay = np.abs(self.position.item(0)-grc_positions[0]) * 1e3 / conduction_speed  + 1 # 1 ms of synaptic transmission time
            self.pfncpc[-1].weight[0] = 1
            return self.pfncpc[-1]
        if type == 'pf':
            source = int(source)
            self.pfncpc.append(pc.gid_connect(source, self.PF_L[0].input))
            self.pfncpc[-1].delay = 1
            self.pfncpc[-1].weight[0] = 1
            return self.pfncpc[-1]
        if type == 'pf_fake':
            self.pfncpc.append(h.NetCon(source.spike,self.PF_L[0].input))
            self.pfncpc[-1].delay = 1
            self.pfncpc[-1].weight[0] = 1
            return self.pfncpc[-1]
        if type == 'stl':
            source = int(source)
            self.stlncpc.append(pc.gid_connect(source, self.STL_L[syn_idx].input))
            self.stlncpc[-1].delay = 1
            self.stlncpc[-1].weight[0] = 1
            return self.stlncpc[-1]
        if type == 'goc':
            source = int(source)
            self.gocncpc.append(pc.gid_connect(source, self.GOC_L[syn_idx].input))
            self.gocncpc[-1].delay = 1
            self.gocncpc[-1].weight[0] = 1
            return self.gocncpc[-1]

    def fr_control(self):
        # Calc pf efficacy
        pfi = [sum([syn_mech.i for syntype in syn.postsyns for syn_mech in syntype[1]]) for syn in self.PF_L]
        return [sum(pfi),pfi]
        

    def random_boot(self):
        boot_time = rnd.uniform(0,50)
        for sec in self.compartments:
            sec.boot_time_Golgi_lkg = boot_time


    def destroy(self):
        del self.nc_spike
        #del self.fr_nc
        for f in self.MF_L:
            f.destroy()
            del f
        for f in self.PF_L:
            f.destroy()
            del f
        for f in self.GRC_L:
            f.destroy()
            del f
        for f in self.GRC_AA_L:
            f.destroy()
            del f
        for f in self.STL_L:
            f.destroy()
        for f in self.GOC_L:
            f.destroy()
            del f
        for f in self.mfncpc:
            del f
        for f in self.aancpc:
            del f
        for f in self.pfncpc:
            del f
        del self.pfncpc
        for f in self.stlncpc:
            del f
        for f in self.gocncpc:
            del f
        for f in self.GAP_L:
            f.destroy()
            del f
        for r in self.record:
            del r
        del self
        

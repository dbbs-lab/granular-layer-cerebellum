# -*- coding: utf-8 -*-
from neuron import h
from neuron import gui
import random as rnd
from templates.synapse.synapse import Synapse


class Grc:
    def __init__(self,position, record_all = 0, Dt = 0.1):
        self.record_all = record_all
        # if record_all:
        #     print "Recording all in Grc"
	self.soma = h.Section(cell=self)
	self.soma.nseg = 1 
	self.soma.diam = 9.76 
	self.soma.L = 9.76 
	self.soma.cm = 1
	self.soma.Ra = 100
	# h.celsius = 37

        self.whatami = "grc"
                
	self.soma.push()
	h.pt3dclear()
	h.pt3dadd(position.item(0), position.item(1) - self.soma.L, position.item(2), self.soma.diam)
	h.pt3dadd(position.item(0), position.item(1) + self.soma.L, position.item(2), self.soma.diam)
	h.pop_section()

	self.soma.insert('GRANULE_LKG1')
	self.soma.insert('GRANULE_LKG2')
	self.soma.insert('GRANULE_Nmda_leak')
	self.soma.insert('GRANULE_NA')
	self.soma.insert('GRANULE_NAR')
	self.soma.insert('GRANULE_PNA')
	self.soma.insert('GRANULE_KV')
	self.soma.insert('GRANULE_KA')
	self.soma.insert('GRANULE_KIR')
	self.soma.insert('GRANULE_KCA')
	self.soma.insert('GRANULE_KM')
	self.soma.insert('GRANULE_CA')
	self.soma.insert('GRANULE_CALC')

	h.usetable_GRANULE_NA = 1
	h.usetable_GRANULE_NAR = 1
	h.usetable_GRANULE_PNA = 1
	h.usetable_GRANULE_KV  = 1
	h.usetable_GRANULE_KA = 1
	h.usetable_GRANULE_KIR = 1
	h.usetable_GRANULE_KCA = 0
	h.usetable_GRANULE_KM = 1
	h.usetable_GRANULE_CA = 1

    	self.soma.ena = 87.39
	self.soma.ek = -84.69
	self.soma.eca = 129.33

	self.MF_L = []
	self.GOC_L = []	
	self.mfncpc = []
	self.gocncpc = []

        self.spike = h.NetStim(0.5, sec= self.soma)
        self.spike.start = -10
        self.spike.number = 1
	self.spike.interval = 1e9

        self.nc_spike = h.NetCon(self.soma(1)._ref_v, self.spike,-20,0,1, sec = self.soma)

        self.record = {}

        self.record['spk'] = h.Vector()
	self.nc_spike.record(self.record['spk'])

        if self.record_all:
            self.record['vm'] = h.Vector()
            self.record['vm'].record(self.soma(.5)._ref_v, Dt, sec = self.soma)
            
            # self.record['ca'] = h.Vector()
            # self.record['ca'].record(self.soma(.5)._ref_cai, Dt, sec = self.soma) #Just an attempt to record Calcium currents
            self.record['NA'] = h.Vector()
            self.record['NA'].record(self.soma(.5)._ref_ic_GRANULE_NA, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['NAR'] = h.Vector()
            self.record['NAR'].record(self.soma(.5)._ref_ic_GRANULE_NAR, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['PNA'] = h.Vector()
            self.record['PNA'].record(self.soma(.5)._ref_ic_GRANULE_NA, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['KV'] = h.Vector()
            self.record['KV'].record(self.soma(.5)._ref_ic_GRANULE_KV, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['KA'] = h.Vector()
            self.record['KA'].record(self.soma(.5)._ref_ic_GRANULE_KA, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['KIR'] = h.Vector()
            self.record['KIR'].record(self.soma(.5)._ref_ic_GRANULE_KIR, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['KCA'] = h.Vector()
            self.record['KCA'].record(self.soma(.5)._ref_ic_GRANULE_KCA, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['KM'] = h.Vector()
            self.record['KM'].record(self.soma(.5)._ref_ic_GRANULE_KM, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['CA'] = h.Vector()
            self.record['CA'].record(self.soma(.5)._ref_ic_GRANULE_CA, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['CALC'] = h.Vector()
            self.record['CALC'].record(self.soma(.5)._ref_ic_GRANULE_CALC, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['LKG1'] = h.Vector()
            self.record['LKG1'].record(self.soma(.5)._ref_ic_GRANULE_LKG1, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            self.record['LKG2'] = h.Vector()
            self.record['LKG2'].record(self.soma(.5)._ref_ic_GRANULE_LKG2, Dt, sec = self.soma) #Just an attempt to record Potassium currents

            # self.record['na'] = h.Vector()
            # self.record['na'].record(self.soma(.5)._ref_ina, Dt, sec = self.soma) #Just an attempt to record Sodium currents
            

    #Synapses
    def createsyn(self,nmf=0,nrel = 0,ngoc = -1,weight = 1, weight_var = 0,prel_LTP = None, Dt = 0.1):
        # Use here the source target sting name
        # so the presynaptic link is not made
        # and it will have to be manged later
        # by the gid connect for parallel simulations
        # Mossy
        if ngoc <0 :
            ngoc = nmf

	for i in range(nmf):
            if prel_LTP == -100 or prel_LTP is None:
                self.MF_L.append(Synapse('glom',self,self.soma,nrel,record_all=1,weight = weight + (rnd.random()-0.5) * weight_var, Dt = Dt))
                self.record['glom_spk_'+str(i)] = self.MF_L[-1].SpikeTrain_input[1]
                for mfsyn_type, mf_syn in self.MF_L[-1].i.iteritems():
                    for rel_n,rel in enumerate(mf_syn):
                        self.record['glom_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel

                # Glutamate concentration        
                for mfsyn_type, mf_syn in self.MF_L[-1].glut.iteritems():
                    if mfsyn_type == 'AMPA':
                        for rel_n ,rel in enumerate(mf_syn):
                            self.record['glom_'+str(i)+'_glut_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                # xview concentration        
                for mfsyn_type, mf_syn in self.MF_L[-1].xview.iteritems():
                    if mfsyn_type == 'AMPA':
                        for rel_n ,rel in enumerate(mf_syn):
                            self.record['glom_'+str(i)+'_xview_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                # yview concentration        
                for mfsyn_type, mf_syn in self.MF_L[-1].yview.iteritems():
                    if mfsyn_type == 'AMPA':
                        for rel_n ,rel in enumerate(mf_syn):
                            self.record['glom_'+str(i)+'_yview_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                # Pview concentration        
                for mfsyn_type, mf_syn in self.MF_L[-1].pview.iteritems():
                    if mfsyn_type == 'AMPA':
                        for rel_n ,rel in enumerate(mf_syn):
                            self.record['glom_'+str(i)+'_Pview_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
                        


            else:
                # if prel_LTP == 0.8:
                #     prel_LTP = 0.55
                self.MF_L.append(Synapse('glom',self,self.soma,nrel,record_all=1,weight = -prel_LTP, Dt = Dt))
                # for mfsyn_type, mf_syn in self.MF_L[-1].g.iteritems():
                #     for rel_n,rel in enumerate(mf_syn):
                #         self.record['glom_'+str(g)+'_g_'+mfsyn_type+'_rel_'+str(rel_n)] = rel
        #Inibition
        # print "ngoc ", ngoc
	for i in range(ngoc):
	    self.GOC_L.append(Synapse('goc',self,self.soma,record_all=1,weight = weight + (rnd.random()-0.5) * weight_var, Dt = Dt))
            self.record['goc_spk_'+str(i)] = self.GOC_L[-1].SpikeTrain_input[1]
            for mfsyn_type, mf_syn in self.GOC_L[-1].i.iteritems():
                for rel_n,rel in enumerate(mf_syn):
	            self.record['goc_'+str(i)+'_i_'+mfsyn_type+'_rel_'+str(rel_n)] = rel

                    

    def pconnect(self,pc,source,syn_idx,type_syn,delay=1):
        if type_syn == 'mf':
            source = int(source)
            self.mfncpc.append(pc.gid_connect(source, self.MF_L[syn_idx].input))
            self.mfncpc[-1].delay = 1
            self.mfncpc[-1].weight[0] = 1
            return self.mfncpc[-1]
        if type_syn == 'goc':
            source = int(source)
            # print "syn_len ", len(self.GOC_L), syn_idx, self.whatami, source
            self.gocncpc.append(pc.gid_connect(source, self.GOC_L[syn_idx].input))
            self.gocncpc[-1].delay = delay
            self.gocncpc[-1].weight[0] = 1
            return self.gocncpc[-1]


    def destroy(self):
        del self.nc_spike
        for m in self.MF_L:
            m.destroy()
            del m
        for m in self.GOC_L:
            m.destroy()
            del m
        for m in self.mfncpc:
            del m
        for m in self.gocncpc:
            del m
        del self

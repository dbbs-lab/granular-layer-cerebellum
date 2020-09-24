# -*- coding: utf-8 -*-
from neuron import h

# Gap junctions cannot setup like synapses as they are splin in
# two simmetrical pieces one on each of the two connected
# neurons, thus, in principle on two different processes.
# Therefore gapj templates have to represent only half of a
# real gap junction.


class Gapj:
    def __init__(self,target,section,conductance = 0, record_all = 0, Dt = 0.1):

        self.record_all = record_all
        if record_all:
            print "Recording all in Gapj"
        # Decide what kind of connection to create based on the source and target types
        if target.whatami == 'goc':
            self.whatami = "gapj_goc2goc"
                
        elif target.whatami == 'stl':
            self.whatami = "gapj_stl2stl"            
        else:
            print "What the hell are you doing?!?"

        self.gapj = h.HalfGap(.5, sec = section)
        self.gapj.g = conductance # nanoSiemens
        self.d = 1e9 # distance set by default to infinite
        self.CC = 1e9 # expected coupling coefficient
            
        if record_all:
            self.record = {}
            self.record['v_local'] = h.Vector()
            self.record['v_remote'] = h.Vector()
            self.record['i_local'] = h.Vector()
            
            self.record['v_remote'].record(self.gapj._ref_vgap, Dt)
            self.record['v_local'].record(section(.5)._ref_v, Dt, sec = section)
            self.record['i_local'].record(self.gapj._ref_i, Dt)
        
    def destroy(self):
        del self.gapj
        del self

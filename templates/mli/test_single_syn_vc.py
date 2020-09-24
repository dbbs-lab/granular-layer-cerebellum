#! /opt/local/bin//python2.7
# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

from neuron import h
from neuron import gui
from templates.mli.stellate import Stellate
from templates.synapse.synapse import Synapse
import numpy as np
import random as rnd

stls = []
stls.append(Stellate(np.array([0.,0.,0.]),model_type='C'))

vc = h.VClamp(.5, sec=stls[0].soma)
vc.amp[0] = -60 # mV
vc.dur[0] = 1e9

vclampi = h.Vector()
vclampi.record(vc._ref_i)

npf = 1
pf_fr = 10

ngrc = 0
grc_fr = 0

stls[0].createsyn(npf=npf,ngrc=1,record_all=1)
nc_pf = []
nc_grc = []
pfs =[]
grcs = []
for idx_stl,stl in enumerate(stls):
    pfs.append([h.NetStim(0.5) for i in range(npf)])
    for pf in pfs[idx_stl]:
        pf.number = 2000
        if pf_fr >0:
            pf.interval = 1e3/pf_fr
            pf.start = 20
        else:
            pf.interval = 1e9
            pf.start = 1e9

        pf.noise = 1
        nc_pf.append(h.NetCon(pf,stl.PF_L[0].input,0,0,1))
    grcs.append([h.NetStim(0.5) for i in range(ngrc)])
    for grc in grcs[idx_stl]:
        grc.number = 2000
        grc.interval = 1e3/grc_fr
        grc.start = 20
        grc.noise = 1
        nc_grc.append(h.NetCon(grc,stl.GRC_L[0].input,0,0,1))

pfs[0][0].seed(rnd.randint(0,2e6))



fr = []


h.dt = 0.025
h.tstop = 1500
h.v_init = -65
h.celsius = 21

import pylab
#for i in range(-42,-42):
h.run()
#pylab.plot(stls[0].record['time'],vclampi)
pylab.plot(stls[0].record['time'],stls[0].PF_L[0].i['AMPA'][0])
#pylab.ylim(-100,100)
pylab.show()

print stls[0].fr(500)
    
# fr.append(stls[0].fr(500))
   
# stringmli = str(mli_mli)

# filename = 'frvector_'+stringmli+'.txt'

# firing = str(fr)
# frvectorfile = open(filename,"w")
# frvectorfile.write(firing)
# frvectorfile.close()
# print fr 

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
stls.append(Stellate(np.array([0.,0.,0.]),model_type='C',record_all=1))

vc = h.VClamp(.5, sec=stls[0].soma)
vc.amp[0] = -60 # mV
vc.dur[0] = 1e9

vclampi = h.Vector()
vclampi.record(vc._ref_i)

npf = 1
pf_fr = 5

ngrc = 1
grc_fr = 0

nmli = 1
mli_fr = 0

stls[0].createsyn(npf=npf,ngrc=1,nmli=nmli,record_all=1)

nc_pf = []
nc_grc = []
pfs =[]
grcs = []
nc_mli = []
mlis = []
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

        pf.noise = 0
        nc_pf.append(h.NetCon(pf,stl.PF_L[0].input,0,0,1))
    grcs.append([h.NetStim(0.5) for i in range(ngrc)])
    for grc in grcs[idx_stl]:
        grc.number = 2000
        if grc_fr > 0:
            grc.interval = 1e3/grc_fr
            grc.start = 20
        else:
            grc.interval = 1e9
            grc.start = 1e9
        grc.noise = 1
        nc_grc.append(h.NetCon(grc,stl.GRC_L[0].input,0,0,1))

    mlis.append([h.NetStim(0.5) for i in range(nmli)])
    for mli in mlis[idx_stl]:
        mli.number = 2000
        if mli_fr >0:
            mli.interval = 1e3/mli_fr
            mli.start = 20
        else:
            mli.interval = 1e9
            mli.start = 1e9

        mli.noise = 0
        stls[0].MLI_L[0].postsyns['GABA'][0].e = 0
        nc_mli.append(h.NetCon(mli,stl.MLI_L[0].input,0,0,1))

# mlis[0][0].seed(rnd.randint(0,2e6))

fr = []


h.dt = 0.025
h.tstop = 1500
h.v_init = -65
h.celsius = 37

import pylab
#for i in range(-42,-42):
h.run()
print h.t
pylab.plot(np.array(stls[0].record['time'])[10:],np.array(vclampi)[10:])
pylab.plot(stls[0].record['time'],stls[0].MLI_L[0].i['GABA'][0])
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

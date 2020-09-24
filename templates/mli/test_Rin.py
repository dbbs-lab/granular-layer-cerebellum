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

stls[0].soma.push()
print h.area(.5)*1e-8,' cm2'

vc = h.VClamp(.5, sec=stls[0].soma)
vc.amp[0] = -80 # mV
vc.dur[0] = 100

vc.amp[1] = -90 # mV
vc.dur[1] = 300

vc.amp[2] = -80 # mV
vc.dur[2] = 100

vclampi = h.Vector()
vclampi.record(vc._ref_i)

npf = 1
pf_fr = 0


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
h.tstop = 1
h.v_init = -65
h.celsius = 21

import pylab
h.run()
#for i in range(-42,-42):
h.continuerun(vc.dur[0]*.9)
injects = []
injects.append(vc.i)
h.continuerun(vc.dur[0]+vc.dur[1]*.9)
injects.append(vc.i)
h.continuerun(500)
print injects
print 'Rin = ',(vc.amp[0]-vc.amp[1])*1e-3/((injects[0]-injects[1])*1e-9)*1e-6, ' MOhm,'
print h.area(.5)*1e-8
print 'Gm = ', (injects[0]-injects[1])*1e-9/((vc.amp[0]-vc.amp[1])*1e-3)/(h.area(.5)*1e-8),' S/cm2'
print 'Temperature = ',h.celsius
pylab.plot(stls[0].record['time'],vclampi)
#pylab.plot(stls[0].record['time'],stls[0].PF_L[0].i['AMPA'][0])
pylab.ylim(-.1,.1)
pylab.show()


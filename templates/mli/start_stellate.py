# -*- coding: utf-8 -*-

# from stellate import Stellate
from neuron import h
from neuron import gui
import sys
sys.path.append('../../')
from templates.synapse.synapse import Synapse
from stellate import Stellate
import numpy as np

pf_scale = 100
npf =  0 #int(1091/pf_scale) # 25 # dovrebbero essere 1500 controllo da eugenio
mli_mli = 0# 3

def go():
    h.finitialize(v_init)
    while h.t<tstop:
        h.fadvance()

cellula = Stellate(np.array([0.,0.,0.]))

fr = []
pf = []
ncpf = []
cellula.createsyn(npf=npf,nmli=mli_mli)

for i in range(npf):
    pf.append(h.NetStim())
    pf[i].start = 0
    pf[i].interval = 1e4/pf_scale
    pf[i].number = 1e9
    pf[i].noise = 1
    ncpf.append(h.NetCon(pf[i], cellula.PF_L[i].input))
    ncpf[i].delay = 1
    ncpf[i].weight[0] = 1

if npf:
    print "PF input ", npf*(1e3/pf[0].interval)/1095

pre_mli = []
nc_mli = []

for i in range(mli_mli):
    pre_mli.append(h.NetStim())
    pre_mli[i].start = 0
    pre_mli[i].interval = 20
    pre_mli[i].number = 1e9
    pre_mli[i].noise = 1
        

    nc_mli.append(h.NetCon(pre_mli[i], cellula.MLI_L[i].input))
    nc_mli[i].delay = 1
    nc_mli[i].weight[0] = 1
#    cellula.MLI_L[i].nc_rel[0].weight[0] = 5e-2

h.dt = 0.025
h.tstop = 1500
h.v_init = -65
h.celsius = 37
print h.celsius
# import pylab
#for i in range(-42,-42):
h.run()
# pylab.plot(cellula.time,cellula.vm)
# pylab.show()

print cellula.fr(500)
    
# fr.append(cellula.fr(500))
   
# stringmli = str(mli_mli)

# filename = 'frvector_'+stringmli+'.txt'

# firing = str(fr)
# frvectorfile = open(filename,"w")
# frvectorfile.write(firing)
# frvectorfile.close()
# print fr 

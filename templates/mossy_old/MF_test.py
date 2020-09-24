from mf import Mf
nrel = 4
import numpy as np
from neuron import h
from neuron import gui
h.nrn_load_dll('$i386/')
mf = Mf(np.array([0,0,0]))

stimulus = h.NetStim(0.5)
stimulus.start = 100 
stimulus.number = 7
stimulus.interval = 500

stimulator = h.NetCon(stimulus,mf.skin,0,0,1)



def go(v_init,tstop,init):
    if init:
        h.finitialize(v_init)
    while h.t<tstop:
        h.fadvance()

h.tstop = 2000
h.v_init = -60
mf.skin.number = 10
go(h.v_init,h.tstop,1)
mf.skin.number = 50
go(h.v_init,4000,0)

raster = h.Graph(0)
raster.exec_menu("Keep Lines")
mf.SpikeTrain_output[0].mark(raster, mf.SpikeTrain_output[1], "|",12,1)

# for idx,v in enumerate(mf.SpikeTrain_output):
#     v[0].mark(raster,v[1], "|",12,idx+2)

raster.view(0,0,400,nrel+1,0,48,1000,1000)
#raster.flush()


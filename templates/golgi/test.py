# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

from templates.golgi.Golgi_template import Goc
from neuron import h
from neuron import gui
import numpy as np
h.nrncontrolmenu()

#h.load_file("/home/bremen/nrn7.2alpha/nrn/share/lib/hoc/parcom.hoc")
##pc = h.ParallelContext()

#h.ParallelComputeTool[0].nthread(2)

nmf = 0 #100
npf = 00 #(30000)
nmli = 00 #300


cellula = Goc(record_all=True)

h.celsius = 37

vm = h.Vector()
tvec = h.Vector()
vm.record(cellula.soma(.5)._ref_v, sec=cellula.soma)
tvec.record(h._ref_t)

stim = [h.IClamp(cellula.soma(.5)), h.IClamp(cellula.soma(.5)), h.IClamp(cellula.soma(.5)), h.IClamp(cellula.soma(.5))]
stim[0].delay = 10000
stim[0].dur = 1000
stim[0].amp = 0.2

stim[1].delay = 12000
stim[1].dur = 1000
stim[1].amp = 0.4

stim[2].delay = 14000
stim[2].dur = 1000
stim[2].amp = 0.6

stim[3].delay = 16000
stim[3].dur = 1000
stim[3].amp = -0.2








h.dt = 0.025
tstop = 18000
v_init = -65


#g = h.Graph()
#g.size(0, 1000, -80, 50)
#g.addvar('v(0.5)', sec=cellula.soma)
#for i in range(nmli):
    ##print cellula.inhibition[0].i
    #g.addvar('cellula.inhibition[0]._ref_i')

# plot the results



def go():
    h.finitialize(v_init)
    #g.begin()
    while h.t<tstop:
        print h.t
        h.fadvance()
        #g.plot(h.t)

    #g.flush()

print h.celsius
go()

data = np.column_stack([np.array(tvec), np.array(vm)])
np.save('golgi_ic.npy', data)

# import pylab
# pylab.subplot (2 ,1 ,1)
# pylab.plot(tvec,vm)
# pylab.show()


#ncmfvec.printf()
#tvec.printf()

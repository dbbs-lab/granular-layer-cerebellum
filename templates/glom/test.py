# -*- coding: utf-8 -*-

from neuron import gui
rosetta = Glom()
Gclamp = h.IClamp(0.5,sec=rosetta.soma)
Gclamp.delay = 1
Gclamp.dur = 10
Gclamp.amp = 0.3
    
h.dt = 0.025
tstop = 400
v_init = -65

g = h.Graph()
g.size(0, 400, -80, 50)
g.addvar('v(0.5)', sec=rosetta.soma)

def go():
    h.finitialize(v_init)
    g.begin()
    while h.t<tstop:
        h.fadvance()
        g.plot(h.t)

    g.flush()


go()

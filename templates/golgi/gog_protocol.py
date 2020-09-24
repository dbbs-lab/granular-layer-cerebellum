import sys
sys.path.append('../../')

import h5py
import numpy as np
from matplotlib import pyplot as plt

from templates.golgi.Golgi_template import Goc
from templates.gapj.gapj import Gapj
import toolbox as tb

from neuron import h
from neuron import gui
import random as rnd

h.nrncontrolmenu()

cvode = h.CVode()
cvode.active(0)

gocs = Goc(np.array([0.,0.,0.]),record_all=1, Dt = 0.1)


stimdata = dict()
stimdata['stim0del'] = 2000
stimdata['stim0dur'] = 1000
stimdata['stim0amp'] = 0.9 # Nano 

#~ stimdata['stim1del'] = 3100
#~ stimdata['stim1dur'] = 1000
#~ stimdata['stim1amp'] = 0.5

stimdata['timeglobal'] = 4000
h.dt = 0.025
h.celsius = 37
h.tstop = stimdata['timeglobal']
h.v_init = -65  

stim = [h.IClamp(0.5,sec=gocs.soma)]
# Record injected current
current = h.Vector()
current.record(h._ref_i,0.1)
# Record Time
tvec = h.Vector()
tvec.record(h._ref_t, 0.1)


stim[0].delay = stimdata['stim0del']
stim[0].dur = stimdata['stim0dur']
stim[0].amp = stimdata['stim0amp'] 
#~ 
#~ stim[1].delay = stimdata['stim1del']
#~ stim[1].dur = stimdata['stim1dur']
#~ stim[1].amp = stimdata['stim1amp'] 

def initialize():
    h.finitialize()
    h.run()
    
initialize()



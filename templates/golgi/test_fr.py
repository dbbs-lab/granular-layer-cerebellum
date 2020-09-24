# -*- coding: utf-8 -*-

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

# stim = h.IClamp(.5, sec=gocs[0][1][1].soma)
# stim.amp = -0.015
# stim.dur = 200

npf = 1
#npf = 1
#npf = 4257
#npf = 3912
#npf = 1997

ngrc = 0
#ngrc = 383
#ngrc = 173
#ngrc = 1

#nmli = 9
nmli = 0

nmf = 1

naa = 0 #15

# Firing rates (Hz)
fr_pf = 0
fr_grc = 0
fr_mli = 0
fr_mf = 100
fr_aa = 0

# Initialize Random number generator
lowindex = 12344556
h.use_mcell_ran4(1)
h.mcell_ran4_init(lowindex)

gocs.createsyn(ngrc=ngrc,npf=npf,nmf=nmf,naa=naa,nmli=nmli,record_all=1)

# vc = h.VClamp(0.5)
# vc.amp[0] = -50
# vc.dur[0] = 500
# vci = h.Vector()
# vci.record(vc._ref_i)


# Setup afferent fibers
PFs = [h.NetStim(0.5) for i in range(npf)]
for s in PFs:
    s.number = 5
    if fr_pf >0:
        s.interval = 1e3/fr_pf
    else:
        s.interval = 0
    s.start = 300
    s.noise = 0
grcs = [h.NetStim(0.5) for i in range(ngrc)]
if ngrc > 0:
    grcs[0].seed(rnd.randint(0,2e6))
for s in grcs:
    s.number = 5
    if fr_grc >0:
        s.interval = 1e3/fr_grc
    else:
        s.interval = 0
    s.start = 300
    s.noise = 0
graa = [h.NetStim(0.5) for i in range(naa)]
if naa > 0:
    graa[0].seed(rnd.randint(0,2e6))
for s in graa:
    #s.number = 1e9
    s.number = 5
    if fr_aa >0:
        s.interval = 1e3/fr_aa
    else:
        s.interval = 0
    s.start = 300
    s.noise = 0
mlis = [h.NetStim(0.5) for i in range(nmli)]
if nmli > 0:
    mlis[0].seed(rnd.randint(0,2e6))
for s in mlis:
    s.number = 1e9
    if fr_mli >0:
        s.interval = 1e3/fr_mli
    else:
        s.interval = 0
    s.start = 20
    s.noise = 1
mfs = [h.NetStim(0.5) for i in range(nmf)]
if nmf > 0:
    mfs[0].seed(rnd.randint(0,2e6))
for s in mfs:
    s.number = 5
    if fr_mf >0:
        s.interval = 1e3/fr_mf
    else:
        s.interval = 0
    s.start = 300
    s.noise = 0

if ngrc>0:
    print gocs.GRC_L[0].postsyns.keys()
print gocs.PF_L[0].postsyns.keys()
if nmli>0:
    print gocs.STL_L[0].postsyns.keys()

nc1 = [h.NetCon(PFs[pf_idx],gocs.PF_L[0].input,0,0,1) for pf_idx,pf in enumerate(PFs)]
if ngrc>0:
    nc2 = [h.NetCon(grcs[grc_idx],grc.input,0,0,1) for grc_idx,grc in enumerate(gocs.GRC_L)]
if nmli>0:
    nc3 = [h.NetCon(mlis[mli_idx],mli.input,0,0,1) for mli_idx,mli in enumerate(gocs.STL_L)]
if nmf>0:
    nc4 = [h.NetCon(mfs[mf_idx],mf.input,0,0,1) for mf_idx,mf in enumerate(gocs.MF_L)]
if naa>0:
    nc5 = [h.NetCon(graa[aa_idx],aa.input,0,0,1) for aa_idx,aa in enumerate(gocs.GRC_AA_L)]


tvec = h.Vector()
tvec.record(h._ref_t, 0.1)

# A control current injection
#stim = [h.IClamp(0.5,sec=gocs.soma)]
# Record injected current
#~ stim[0].delay = 200
#~ stim[0].dur = 40
#~ stim[0].amp = 0.5 
#~ current = h.Vector()
#~ current.record(stim[0]._ref_i,0.1)


ina = h.Vector()
ibk = h.Vector()
ika = h.Vector()
ikm = h.Vector()
ikv = h.Vector()
isk2 = h.Vector()
ica = h.Vector()
ina.record(gocs.soma(0.5)._ref_ina_Golgi_Na,0.1)
ibk.record(gocs.soma(0.5)._ref_ik_Golgi_BK,0.1)
ika.record(gocs.soma(0.5)._ref_ik_Golgi_KA,0.1)
ikm.record(gocs.soma(0.5)._ref_ik_Golgi_KM,0.1)
ikv.record(gocs.soma(0.5)._ref_ik_Golgi_KV,0.1)
isk2.record(gocs.soma(0.5)._ref_ik_Golgi_SK2,0.1)
ica.record(gocs.soma(0.5)._ref_cai,0.1)
#print gocs.GRC_L[0]

h.tstop = 600
h.celsius = 37
h.v_init = -65
print h.dt
h.dt = 0.01

print gocs.soma.L,gocs.soma.diam,gocs.soma.Ra,gocs.soma.cm
print gocs.soma.gbar_Golgi_lkg, gocs.soma.el_Golgi_lkg
h.topology()
print h.celsius
# Warning!!!
gocs.soma.gbar_Golgi_KV = 0.002


print "run"
h.init()
h.run()
print "done"


fig = [plt.figure()]
ax1  = [fig[0].add_subplot(111)]

print

ax1[0].plot(tvec,gocs.record['vm'])
ax1[0].set_ylabel('Membrane potential (mV)')
ax1[0].set_xlabel('Time (ms)')
#ax1[0].set_title('10pf, 10mf, 0aa, 100 hz burst [5 spikes]')
ax1[0].set_title('2000 Pf, 50 Mf, 300 AA')

goc_fr = []
goc_fr.append(1e3/np.mean(np.diff(gocs.record['spk'])))
#PFs[0].seed(rnd.randint(0,2e6))
# for i in range(1):
#     h.run()
#     goc_fr.append(1e3/np.mean(np.diff(gocs.record['spk'])))

print goc_fr
print h.celsius

#plt.figure()
#plt.plot(tvec, ina, label='I-Na current')
#plt.legend()

#plt.figure()
#plt.plot(tvec, ibk, label='I-BK Current')
#plt.legend()

#~ plt.figure()
#~ plt.plot(tvec, ika, label='I-KA current')
#~ plt.legend()
#~ 
#~ plt.figure()
#~ plt.plot(tvec, ikm, label='I-KM current')
#~ plt.legend()
#~ 
#~ plt.figure()
#~ plt.plot(tvec, ikv, label='I-KV current')
#~ plt.legend()
#~ 
#~ plt.figure()
#~ plt.plot(tvec, isk2, label='I-SK2 current')
#~ plt.legend()
#~ 
plt.figure()
plt.plot(tvec,ica,label='Calcium Current')
plt.legend()

if naa:
    plt.figure()
    plt.plot(tvec,gocs.GRC_AA_L[0].i['AMPA'][0].mul(1e3),label='AMPA_DET_VI')
    plt.plot(tvec,gocs.GRC_AA_L[0].i['NMDA'][0].mul(1e3),label='NMDA_DET_VI')
    #plt.plot(tvec,current,label='Injected Current')
    plt.legend()
plt.show()

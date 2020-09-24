#! /opt/local/bin//python2.7

# -*- coding: utf-8 -*-

import sys
sys.path.append('../../')

import h5py
import numpy as np
import random as rnd
from matplotlib import pyplot as plt

from stellate import Stellate
import toolbox as tb

from neuron import h
from neuron import gui

pc = h.ParallelContext()
rank = int(pc.id())
size = int(pc.nhost())


plot = 1
npf = 1500
ngrc = 0

pf_fr = 0.1
grc_fr = 0.1

save_dt = 0.1

h.nrn_load_dll('$i386/')

# From Hausser&Clark97  35 C mean +- SEM
# In vitro interneurons spont firing rate = 12.3 +- 0.9 Hz
# Gaba blocker gabazine: increase of 55 +- 21 % = 19.065 +- 1.5 Hz

stls = [Stellate(np.array([0.,0.,0.]), record_all = 1, background = 0,model_type = 'C', Dt = save_dt) for i in range(50)]
for gid,stl in enumerate(stls):
    pc.set_gid2node(gid, rank)
    #nc = stl.connect2target(None)
    #pc.cell(gid, stl.nc)

# Set Temperature
h.celsius = 35

# Initialize Random number generator
lowindex = 12344556
h.use_mcell_ran4(1)
h.mcell_ran4_init(lowindex)


#print 'Passive input resistance ',1/((3.14*stls[0].soma.diam**2.)*1e-8*stls[0].soma.gbar_MLI_lkg)/1e6, ' MOhm', stls[0].soma.gbar_MLI_lkg

# stim = h.IClamp(.5, sec=stls[0][1][1].soma)
# stim.amp = -0.015
# stim.dur = 200

[stl.createsyn(npf=1,ngrc=1,record_all=1) for stl in stls]

# vc = h.VClamp(0.5)
# vc.amp[0] = -30
# vc.dur[0] = 200

nc_pf = []
nc_grc = []
pfs =[]
grcs = []
for idx_stl,stl in enumerate(stls):
    pfs.append([h.NetStim(0.5) for i in range(npf)])
    for pf in pfs[idx_stl]:
        pf.number = 2000
        pf.interval = 1e3/pf_fr
        pf.start = 20
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


# [stl.createsyn(nmli=1,record_all=1) for stl in stls]

# nc_mli = []
# # mlis = [h.NetStim(0.5) for i in range(13)]
# for stl in stls:
#     stl.number = 20
#     stl.interval = 50
#     stl.start = 20
#     stl.noise = 1
#     [nc_mli.append(h.NetCon(stl.spike,stl.MLI_L[0].input,0,0,1)) for stl in stls]

#[stl.creategap(13,gid,235,pc) for gid,stl in enumerate(stls)] # 235 pS = 4.25 GOhm from Mann-MetzerJNeurosci99

# for gid,stl in enumerate(stls):
#     for st_idx,st in enumerate(rnd.sample([s for s in stls if s != stl],13)):
#         pc.target_var(st.GAP_L[st_idx].gapj._ref_vgap, gid)

# pc.setup_transfer()



#for stl in stls:
#   stl.soma.gbar_MLI_KM = 0.001
#     print h.psection()

# Store global time
time_vector = h.Vector()
time_vector.record(h._ref_t, save_dt)


h.tstop = 1000
h.init()


print "run"
h.run() # runs properly with single thread
print "done"

fr = [stl.fr(0) for stl in stls]
[stl.destroy() for stl in stls]

print "STL firing rate ",np.mean(fr),np.std(fr)

if plot:
    fig = [plt.figure(),plt.figure()]
    ax1  = [fig[0].add_subplot(121),fig[1].add_subplot(121)]

    for idx,a in enumerate(ax1):
        a.plot(time_vector,stls[idx].record['vm'])
        a.plot(time_vector,stls[idx].record['vm'])
        #a.plot(stls[0].record['time'],stls[0].GAP_L[0].record['v_remote'])
        a.set_ylabel('Membrane potential (mV)')
        a.set_xlabel('Time (ms)')
        a.set_ylim(-70,20)


    ax2  = [fig[0].add_subplot(122),fig[1].add_subplot(122)]
    #ax3  = fig[0].add_subplot(224)
    # print stls.GRC_L[0].SpikeTrain_input[1].printf()
    # print stls.PF_L[0].SpikeTrain_input[1].printf()
    # print stls.PF_L[0].postsyns['AMPA'][0].gmax
    # print stls.PF_L[0].whatami
    # print stls.PF_L[0].i['AMPA'][0].printf()
    # ax2[0].plot(stls.record['time'],stls.GRC_L[0].i['NMDA'][0].mul(1e3),label='MARKOV')
    # ax2[0].plot(stls.record['time'],stls.PF_L[0].i['NMDA'][0].mul(1e3),label='EXPSYN')
    #ax2[1].plot(stls.record['time'],stls.GRC_L[0].i['AMPA'][0].mul(1e3),label='MARKOV')

    #ax2[1].plot(stls[0].record['time'],stls[0].PF_L[0].i['AMPA'][0].mul(1e3),label='EXPSYN')
    for a in ax2:
        a.set_ylabel('Synaptic current (pA)')
        a.set_xlabel('Time (ms)')

    ax2[0].legend(('Markov','dual-Exponential'),loc=4)
    ax2[1].legend(('Markov','dual-Exponential'),loc=4)


    ax2[0].set_title('NMDA')
    ax2[1].set_title('AMPA')


    # ax2[0].set_xlim(18,100)
    # ax2[1].set_xlim(18,25)
    # ax2[0].set_ylim(-5,0)
    # ax2[1].set_ylim(-50,0)
    plt.show()




# -*- coding: utf-8 -*-

from neuron import h


class Synapse:
    def __init__(self,source,target,section,nrel = 0,syntype = 'ANK',record_all = 0,weight = 1, Dt=0.1):
        self.record_all = record_all
        # if record_all:
        #     print "Recording all in Synapse"

	self.input = h.NetStim(0.5)
	self.input.start = -10
	self.input.number = 1
	self.input.interval = 1e9
        self.weight = weight

        self.nrel = nrel
        self.syntype = syntype

        self.postsyns = {}

        if (type(source) == type('s')):
            sourcetype = source
        else:
            sourcetype = source.whatami

        # This is set to a value not 0 to avoid problems with the pc.set_maxstep()
        nc_delay = 0.01
        # total accumultate delay = nc_delay* (1+1) = 0.02 ms
        # this should be removed from the gid_connect delay

        if self.record_all:
            self.SpikeTrain_input = [h.Vector(),h.Vector()]
            self.netcon_in = h.NetCon(self.input,None, 0, nc_delay, 1)
            self.netcon_in.record(self.SpikeTrain_input[1], self.SpikeTrain_input[0], 1)

        # Decide what kind of connection to create based on the source and target types
        if sourcetype == 'glom':
            if target.whatami == 'pf':
                ## No input to the fake grcs
                print 'Pf!!!!'
            else:
                # Make a mf synapse
                if self.nrel>0 :
                    if target.whatami == 'grc':
                        self.whatami = "syn_glom2grc_stoch"
                    elif target.whatami == 'goc':
                        self.whatami = "syn_glom2goc_stoch"
                    # Use stochastic synapses
                    self.release_sites = [h.Release_site(0.5, sec=section) for i in range(self.nrel)]
                    # Set Prob of release
                    # if weight is negative it means that we are setting the Prel based on LTP rules
                    # the weight then carries the absolute Prel value calculate offline after a simulation with stimuli for LTP induction
                    for site in self.release_sites:
                        if self.weight >= 0:
                            site.U = 0.42 * self.weight
                        elif self.weight < 0:
                            site.U = -self.weight
                        else:
                            print " WARNING mf->grc syn weight is not a Number!!!"

                    # Set netcon for spikes
                    self.netcon_out = [h.NetCon(release_site,None, 0, nc_delay, 1) for release_site in self.release_sites]
                    # Connect input
                    self.nc_rel = [h.NetCon(self.input,release_site, 0, nc_delay, 1) for release_site in self.release_sites]
                    # Add poststnaptic sites
                    if 'A'  in self.syntype:
                        # AMPA
                        self.postsyns['AMPA'] = [h.GRANULE_Ampa_stoch_vi(.5, sec=section) for r in self.release_sites]
                        if target.whatami == 'goc':
                            for p in self.postsyns['AMPA']: # set the correct gmax for MF-> GoC
                                p.gmax = 4270
                    if 'N'  in self.syntype:
                        # NMDA
                        self.postsyns['NMDA'] = [h.GRANULE_Nmda_stoch_vi(.5, sec=section) for r in self.release_sites]
                        if target.whatami == 'goc':
                            for p in self.postsyns['NMDA']: # set the correct gmax for MF-> GoC
                                p.gmax = 46500

                    for rec_site in self.postsyns['AMPA']:
                        rec_site.gmax_factor = (1./0.5)/self.nrel
                    for rec_site in self.postsyns['NMDA']:
                        rec_site.gmax_factor = (1./0.6)/self.nrel

                    # Connect pre to post synapse
                    self.nc_syn = [[h.NetCon(release_site, receptor[k], 0, nc_delay, 1) for k, release_site in enumerate(self.release_sites)] for receptor in self.postsyns.itervalues()]

                    # If required recod the timing of each vescicle release
                    if self.record_all:
                        self.SpikeTrain_output = [[h.Vector(),h.Vector()] for n in self.netcon_out]
                        for i,n in enumerate(self.netcon_out):
                            n.record(self.SpikeTrain_output[i][1],self.SpikeTrain_output[i][0],i+2)

                else:
                    if target.whatami == 'grc':
                        self.whatami = "syn_glom2grc_det"
                    elif target.whatami == 'goc':
                        self.whatami = "syn_glom2goc_det"
                    # Use deterministic synapses
                    if 'A'  in self.syntype:
                        # AMPA
                        self.postsyns['AMPA'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                        # Set Prob release
                        # if weight is negative it means that we are setting the Prel based on LTP rules
                        # the weight then carries the absolute Prel value calculate offline after a simulation with stimuli for LTP induction
                        if self.weight >= 0:
                            self.postsyns['AMPA'][0].U = self.postsyns['AMPA'][0].U * self.weight
                            self.postsyns['AMPA'][0].gmax = 1200
                        elif self.weight < 0:
                            self.postsyns['AMPA'][0].U = -self.weight
                        else:
                            print " WARNING mf->grc syn weight is not a Number!!!"
                        if target.whatami == 'goc':
                            # We set the peak cond of AMPA in order to fall within the range of 28-456 pA reported by Cesana et al. 2013 with a peak EPSC of 100 pA with Prel 0.5
                            # i.e. for Prel 1 the peak EPSC is 200 pA
                            self.postsyns['AMPA'][0].U = 0.5
                            self.postsyns['AMPA'][0].gmax = 4325 # new fit to get -100 pA at -70 mV 35 C previous with syn in soma = 4270 pS

                    if 'N'  in self.syntype:
                        # NMDA
                        self.postsyns['NMDA'] = [h.GRANULE_Nmda_det_vi(0.5, sec=section)]
                        # Set Prob release
                        # if weight is negative it means that we are setting the Prel based on LTP rules
                        # the weight then carries the absolute Prel value calculate offline after a simulation with stimuli for LTP induction
                        if self.weight >= 0:
                            self.postsyns['NMDA'][0].U = self.postsyns['NMDA'][0].U * self.weight
                            self.postsyns['NMDA'][0].gmax = 18800
                        elif self.weight < 0:
                            self.postsyns['NMDA'][0].U = -self.weight
                        else:
                            print " WARNING mf->grc syn weight is not a Number!!!"
                        if target.whatami == 'goc':
                            self.postsyns['NMDA'][0].U = 0.5
                            self.postsyns['NMDA'][0].gmax = 33000# new fit to get -34 pA at -70 mV Mg unblocked at 32 C, T20-80 2.70 ms instead of 5.0 ms as in Cesana et al. 2013

                    # Connect input to the receptors
                    self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]

        elif sourcetype == 'goc':
            if target.whatami == 'grc':
                # Make a Golgi (GABAergic) synapse onto a granule cell
                # Use deterministic synapses
                self.whatami = "syn_goc2grc_det"
                self.postsyns['GABA'] = [h.GRANULE_Gaba_det_vi(0.5, sec=section)]
                self.postsyns['GABA'][0].U = self.postsyns['GABA'][0].U * self.weight
                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]
            if target.whatami == 'goc':
                # Make a GoC synapse onto a golgi cell
                # Use deterministic synapses
                self.whatami = "syn_goc2goc_det"
                self.postsyns['GABA'] = [h.Golgi_PF_AMPA(0.5, sec=section)] # self.postsyns
                self.postsyns['GABA'][0].ref_temp = 32 # Hull et al. 2012
                self.postsyns['GABA'][0].tau2_Fix = 2 #
                self.postsyns['GABA'][0].tau2_Fix = 10 # Hull2012
                self.postsyns['GABA'][0].e = -75 # Hull they don't correct for LJP but their e-rev EPSC is +15 mv and erev IPSC -64 mv, so LJP 15 mv to make EPSC e-rev = 0 mv
                self.postsyns['GABA'][0].gmax = 130 #330 # pS Hull 2012
                self.postsyns['GABA'][0].gmax_factor = self.weight
                # self.postsyns['GABA'] = [h.GRANULE_Gaba_det_vi(0.5, sec=section)]
                # self.postsyns['GABA'][0].gmaxA1 = 4000
                # self.postsyns['GABA'][0].gmaxA6 = 0
                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]


        elif sourcetype == 'grc':
            if target.whatami == 'goc':
                # Make a PF synapse onto a golgi cell
                # Use deterministic synapses
                self.whatami = "syn_grc2goc_det"
                if 'A'  in self.syntype:
                    # AMPA
                    self.postsyns['AMPA'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                    self.postsyns['AMPA'][0].U = 0.1 * self.weight # Make it 1 to get the spontaneous peak amplitude
                    self.postsyns['AMPA'][0].diffuse = 0
                    self.postsyns['AMPA'][0].gmax = 1800  # Misra 2000 Spontaneous Ampa peak curr = 35.5 pA at -30 mV

                if 'N'  in self.syntype:
                    # NMDA
                    self.postsyns['NMDA'] = [h.GRANULE_Nmda_det_vi(0.5, sec=section)]
                    self.postsyns['NMDA'][0].gmax = 1880*4.5  # Misra 2000 Nmda peak curr = 18.5 % of Ampa peak curr = 6.4 pA at -30 mV without Mg_block
                    self.postsyns['NMDA'][0].U = 0.1 * self.weight # Make it 1 to get the spontaneous peak amplitude

                if 'K'  in self.syntype:
                    # KAINATE
                    self.postsyns['KAIN'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                    self.postsyns['KAIN'][0].U = 0.1 * self.weight
                    self.postsyns['KAIN'][0].Cdur = 0.3/5
                    self.postsyns['KAIN'][0].r1FIX = 0.1
                    self.postsyns['KAIN'][0].r2 = 0.01
                    self.postsyns['KAIN'][0].r6FIX = 0.1
                    self.postsyns['KAIN'][0].gmax = 19000/20
                if 'E'  in self.syntype:
                    # AMPA exp2syn
                    self.postsyns['AMPA'] = [h.Golgi_PF_AMPA(0.5, sec=section)]
                    self.postsyns['AMPA'][0].tau1_Fix = 0.7 # pS
                    self.postsyns['AMPA'][0].tau2_Fix = 1.8 # pS
                    self.postsyns['AMPA'][0].gmax = 135 # pS
                    self.postsyns['AMPA'][0].gmax_factor = self.weight
                    # NMDA exp2syn
                    self.postsyns['NMDA'] = [h.Golgi_PF_NMDA(0.5, sec=section)]
                    self.postsyns['NMDA'][0].tau1_Fix = 15
                    self.postsyns['NMDA'][0].tau2_Fix = 31
                    self.postsyns['NMDA'][0].gmax = 21.5*.33 # pS
                    self.postsyns['NMDA'][0].gmax_factor = self.weight
                    self.postsyns['NMDA'].append(h.Golgi_PF_NMDA(0.5, sec=section))
                    self.postsyns['NMDA'][1].tau1_Fix = 15
                    self.postsyns['NMDA'][1].tau2_Fix = 170
                    self.postsyns['NMDA'][1].gmax = 21.5*.67 # pS
                    self.postsyns['NMDA'][1].gmax_factor = self.weight

                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]

            elif target.whatami == 'stl':
                if 'A'  in self.syntype:
                    self.whatami = "syn_grc2stl_det"
                    self.postsyns['AMPA'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                    self.postsyns['AMPA'][0].tau_facil=10.8*5
                    self.postsyns['AMPA'][0].tau_rec=35.1*1
                    self.postsyns['AMPA'][0].tau_1=3*5
                    self.postsyns['AMPA'][0].gmax = 9500 #*area(0.5)/1.33 // 7.5   2050  3943 o 2790 valori a 25 gradia 37 gradi,1990 la media
                    self.postsyns['AMPA'][0].U=0.15 * self.weight
                if 'E'  in self.syntype:
                    self.whatami = "syn_grc2stl_exp"
                    self.postsyns['AMPA'] = [h.Golgi_PF_AMPA(0.5, sec=section)]
                    self.postsyns['AMPA'][0].tau1_Fix = 0.7 # pS
                    self.postsyns['AMPA'][0].tau2_Fix = 1.8 # pS
                    self.postsyns['AMPA'][0].gmax = 8500.0 / 10 #/ 100 # pS we put it small so far but refer to Carter Regehr 2000 & Liu Cull-Candy 2005
                    self.postsyns['AMPA'][0].gmax_factor = self.weight
                if 'R'  in self.syntype:
                    self.whatami = "syn_grc2stl_relay"
                    self.postsyns['Relay'] = [h.NetStim(0.5, sec=section)]
                    self.postsyns['Relay'][0].start = -10
                    self.postsyns['Relay'][0].number = 1
                    self.postsyns['Relay'][0].interval = 1e9
                    self.relay = h.NetCon(self.postsyns['Relay'][0],target.pre_spike, 0, nc_delay, 1)

                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]

        elif sourcetype == 'aa':
            if target.whatami == 'goc':
                self.whatami = "syn_grcaa2goc_det"
                # Use deterministic synapses
                if 'A'  in self.syntype:
                    # AMPA
                    self.postsyns['AMPA'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                    self.postsyns['AMPA'][0].U = self.postsyns['AMPA'][0].U * self.weight
                    self.postsyns['AMPA'][0].gmax =  4300 #4300 #1300   #pS, according to Lia, 2013 (32 celsius)

                if 'N'  in self.syntype:
                    # NMDA
                    self.postsyns['NMDA'] = [h.GRANULE_Nmda_det_vi(0.5, sec=section)]
                    self.postsyns['NMDA'][0].U = self.postsyns['NMDA'][0].U * self.weight
                    self.postsyns['NMDA'][0].gmax = 43000 #43000 # new fit to get -4pA at -30 mV 32 C and 27 pA at +50 mV , with syn in soma previous fit 46500 pS

                # Connect input to the receptors
                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]

        elif sourcetype == 'pf':
            if target.whatami == 'goc':
                # Make a PF synapse onto a golgi cell
                # Use deterministic synapses
                self.whatami = "syn_pf2goc_det"
                if 'A'  in self.syntype:
                    # AMPA
                    self.postsyns['AMPA'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                    self.postsyns['AMPA'][0].U = 0.1 * self.weight
                    self.postsyns['AMPA'][0].diffuse = 0
                    self.postsyns['AMPA'][0].gmax = 1800   #1800  # Fit to the above -> grc ->Goc

                if 'N'  in self.syntype:
                    # NMDA
                    self.postsyns['NMDA'] = [h.GRANULE_Nmda_det_vi(0.5, sec=section)]
                    self.postsyns['NMDA'][0].gmax = 1880*4.5  # Fit to the above -> grc ->Goc
                    self.postsyns['NMDA'][0].U = 0.1 * self.weight

                if 'K'  in self.syntype:
                    # KAINATE
                    self.postsyns['KAIN'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                    self.postsyns['KAIN'][0].U = 0.1 * self.weight
                    self.postsyns['KAIN'][0].Cdur = 0.3/5
                    self.postsyns['KAIN'][0].r1FIX = 0.1
                    self.postsyns['KAIN'][0].r2 = 0.01
                    self.postsyns['KAIN'][0].r6FIX = 0.1
                    self.postsyns['KAIN'][0].gmax = 19000/20
                if 'E'  in self.syntype:
                    # AMPA exp2syn
                    self.postsyns['AMPA'] = [h.Golgi_PF_AMPA(0.5, sec=section)]
                    self.postsyns['AMPA'][0].tau1_Fix = 0.7 # pS
                    self.postsyns['AMPA'][0].tau2_Fix = 1.8 # pS
                    self.postsyns['AMPA'][0].gmax = 135 # pS
                    self.postsyns['AMPA'][0].gmax_factor = self.weight
                    # NMDA exp2syn
                    self.postsyns['NMDA'] = [h.Golgi_PF_NMDA(0.5, sec=section)]
                    self.postsyns['NMDA'][0].tau1_Fix = 15
                    self.postsyns['NMDA'][0].tau2_Fix = 31
                    self.postsyns['NMDA'][0].gmax = 21.5*.33 # pS
                    self.postsyns['NMDA'][0].gmax_factor = self.weight
                    self.postsyns['NMDA'].append(h.Golgi_PF_NMDA(0.5, sec=section))
                    self.postsyns['NMDA'][1].tau1_Fix = 15
                    self.postsyns['NMDA'][1].tau2_Fix = 170
                    self.postsyns['NMDA'][1].gmax = 21.5*.67 # pS
                    self.postsyns['NMDA'][1].gmax_factor = self.weight

                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]

            elif target.whatami == 'stl':
                if 'A'  in self.syntype:
                    self.whatami = "syn_pf2stl_det"
                    self.postsyns['AMPA'] = [h.GRANULE_Ampa_det_vi(0.5, sec=section)]
                    self.postsyns['AMPA'][0].tau_facil=10.8*5
                    self.postsyns['AMPA'][0].tau_rec=35.1*1
                    self.postsyns['AMPA'][0].tau_1=3*5
                    self.postsyns['AMPA'][0].gmax = 9500 #*area(0.5)/1.33 // 7.5   2050  3943 o 2790 valori a 25 gradia 37 gradi,1990 la media
                    self.postsyns['AMPA'][0].U=0.15 * self.weight
                if 'E'  in self.syntype:
                    self.whatami = "syn_pf2stl_exp"
                    self.postsyns['AMPA'] = [h.Golgi_PF_AMPA(0.5, sec=section)]
                    self.postsyns['AMPA'][0].tau1_Fix = 0.1 # ms
                    self.postsyns['AMPA'][0].tau2_Fix = 1.5 # ms
                    self.postsyns['AMPA'][0].gmax = 250 # pS we put it small but cf. Liu,Cull-Candy 2005 yield 60 pA at 21 deg -60
                    self.postsyns['AMPA'][0].gmax_factor = self.weight
                if 'R'  in self.syntype:
                    self.whatami = "syn_pf2stl_relay"
                    self.postsyns['Relay'] = [h.NetStim(0.5, sec=section)]
                    self.postsyns['Relay'][0].start = -10
                    self.postsyns['Relay'][0].number = 1
                    self.postsyns['Relay'][0].interval = 1e9
                    self.relay = h.NetCon(self.postsyns['Relay'][0],target.pre_spike, 0, nc_delay, 1)

                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]

        elif sourcetype == 'stl':
            if target.whatami == 'stl':
                self.whatami = "syn_stl2stl_exp"
                self.postsyns['GABA'] = [h.Golgi_PF_AMPA(0.5, sec=section)] # self.postsyns
                self.postsyns['GABA'][0].tau1_Fix = 1.1 # Llano 93
                self.postsyns['GABA'][0].tau2_Fix = 8.7 # Llano 93
                self.postsyns['GABA'][0].e = -60
                self.postsyns['GABA'][0].ref_temp = 21 # Llano 93
                self.postsyns['GABA'][0].gmax = 2200 # pS Llano93 132 pA / 60 mV = 2200 pS
                self.postsyns['GABA'][0].gmax_factor = self.weight
                # self.postsyns['GABA'][0].tau = 1.1
                # self.postsyns['GABA'][0].e = -60
                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]
                # for nc in self.nc_syn:
                #     nc.weight[0] = 5e-2
            if target.whatami == 'goc':
                self.whatami = "syn_stl2goc_exp"
                self.postsyns['GABA'] = [h.Golgi_PF_AMPA(0.5, sec=section)] # self.postsyns
                self.postsyns['GABA'][0].tau2_Fix = 25.9 # Doumoulin2001
                self.postsyns['GABA'][0].e = -60
                self.postsyns['GABA'][0].gmax = 2000 / 60   #/ 3 # infered from fig.3c Doumoulin2001 to achieve 20 pA at -70 mV #
                self.postsyns['GABA'][0].gmax_factor = self.weight
                self.nc_syn = [h.NetCon(self.input,receptor[0], 0, nc_delay, 1) for receptor in self.postsyns.itervalues()]

        else:
            print 'SOURCE TYPE DOES NOT EXIST SOMETHING WRONG!!!!!!!!!'

        if self.record_all and len(self.postsyns) > 0 and 'R' not in self.syntype:
            self.i = {}
            for (post_type,post) in self.postsyns.iteritems():
                for p in post:
                    self.i[post_type] = []
                    self.i[post_type].append(h.Vector())
                    self.i[post_type][-1].record(p._ref_i,Dt)
            self.g = {}
            for (post_type,post) in self.postsyns.iteritems():
                for p in post:
                    self.g[post_type] = []
                    self.g[post_type].append(h.Vector())
                    self.g[post_type][-1].record(p._ref_g,Dt)
            self.glut = {}
            for (post_type,post) in self.postsyns.iteritems():
                if post_type == 'AMPA':
                    for p in post:
                        self.glut[post_type] = []
                        self.glut[post_type].append(h.Vector())
                        self.glut[post_type][-1].record(p._ref_Trelease, Dt)
            self.xview = {}
            for (post_type,post) in self.postsyns.iteritems():
                if post_type == 'AMPA':
                    for p in post:
                        self.xview[post_type] = []
                        self.xview[post_type].append(h.Vector())
                        self.xview[post_type][-1].record(p._ref_xview, Dt)
            self.yview = {}
            for (post_type,post) in self.postsyns.iteritems():
                if post_type == 'AMPA':
                    for p in post:
                        self.yview[post_type] = []
                        self.yview[post_type].append(h.Vector())
                        self.yview[post_type][-1].record(p._ref_yview, Dt)
            self.pview = {}
            for (post_type,post) in self.postsyns.iteritems():
                if post_type == 'AMPA':
                    for p in post:
                        self.pview[post_type] = []
                        self.pview[post_type].append(h.Vector())
                        self.pview[post_type][-1].record(p._ref_Pview, Dt)






    def prel(self,prel):
        for r in self.release_sites:
            r.U = 0.42

    def destroy(self):
        if self.record_all:
            del self.netcon_in
        if self.nrel > 0:
            for r in self.netcon_out:
                del r
            for r in self.nc_rel:
                del r
        if self.whatami == "syn_grc2stl_relay" or self.whatami == "syn_pf2stl_relay":
            del self.relay
        for r in self.nc_syn:
            del r
        del self

# Description : Python version of Diwakar et al, 2009 multicompartmental granule cell model. Script to record ionic current from all compartment is included in this model.

# Author : Harilal Parasuram, Chaitanya Medini and Shyam Diwakar
# Developed by Computational Neurosciecne Lab at School of Biotechnology, Amrita Univ., India.
# Last edited : 30-03-2014



from neuron import h
from templates.synapse.synapse import Synapse
import numpy as np
import random as rnd

class Grc:
    def __init__(self,position, record_all = 1, Dt = 0.1):	
        self.record_all = 1
	self.vext_record_all = 0
	self.ionic_record_all = 1
        #print "Recording all in GRC"
	global glL		
	glL = 5.68e-5
	global ell
	ell = -16.5

	KirGmax = 0.0009
	KaGmax = 0.0032
	CaGmax = 0.00046
	KCaGmax = 0.003
	beta = 0.6
	inicon = 0.001
	naxon = 30

	global ndend
	ndend=4

	#configuration mode flags
	Camode1 = 0
	Camode2 = 0
	Camode3 = 0
	Camode4 = 1 
	CamodeS = 0
	KCamode1 = 0
	KCamode2 = 0
	KCamode3 = 0
	KCamode4 = 1
	KCamodeS = 0
	Kirmode1 = 1
	Kirmode2 = 1
	Kirmode3 = 0
	Kirmode4 = 0
	KirmodeS = 0
	Kamode1 = 0
	Kamode2 = 0
	Kamode3 = 0
	Kamode4 = 0 
	KamodeS = 1

	global gamma
	gamma = 0.5
	KCaD = KCaGmax
	CaD = CaGmax
	KaRapp = KaGmax
	KirRapp = KirGmax
	CaRapp = CaGmax
	KCaRapp = KCaGmax

	betad = 0.8
	global gG
	gG = 3e-05

	KcaB = KCaGmax
	CaB = CaGmax

	#soma definition
	self.soma = h.Section(cell=self)
	self.soma.nseg = 1
	self.soma.diam = 5.8
	self.soma.L = 5.8
	self.soma.cm = 1
	self.soma.Ra = 100
	

	self.whatami = "grc"
	self.soma.push()
	h.celsius=30
	h.pop_section()
	
	
	self.soma.push()
	h.pt3dclear()
	h.pt3dadd(position.item(0), position.item(1) - self.soma.L, position.item(2), self.soma.diam)
	h.pt3dadd(position.item(0), position.item(1) + self.soma.L, position.item(2), self.soma.diam)
	h.pop_section()
	
	self.soma.insert('GRC_LKG1')
	self.soma.insert('GRC_LKG2')
	self.soma.insert('GRC_NA')
	self.soma.insert('GRC_KA')
	self.soma.insert('GRC_KM')
	self.soma.insert('GRC_KV')
	self.soma.insert('GRC_KCA')
	self.soma.insert('GRC_KIR')	
	self.soma.insert('GRC_CA')
	self.soma.insert('GRC_CALC')
	
	self.soma.insert('extracellular')

	#self.soma.xg[0]=1e1
	#self.soma.xraxial[0]=1e1
	

	#h.usetable_GRC_NA = 0
	h.usetable_GRC_KA = 0
	h.usetable_GRC_KIR = 0
	h.usetable_GRC_KM = 0
	#h.usetable_GRC_NA = 0
	h.usetable_GRC_KV = 0
	h.usetable_GRC_KCA = 0 
	h.usetable_GRC_CA = 0

	Nag = self.soma.gnabar_GRC_NA
	#global gG
	gG = self.soma.ggaba_GRC_LKG2
	Kvg = self.soma.gkbar_GRC_KV
	Kmg = self.soma.gkbar_GRC_KM

	global NagH
	NagH = Nag
	global KvgH
	KvgH = Kvg
	global NagA
	NagA = Nag
	KvgA = Kvg
	#KCaD = KCaGmax
	#CaD = CaGmax

	DendFact = 1

	betad = 0.8	

	self.soma.ggaba_GRC_LKG2=3e-05
	self.soma.gkbar_GRC_KCA=0
	self.soma.gcabar_GRC_CA=0

	self.soma.gnabar_GRC_NA = 0
	self.soma.gkbar_GRC_KV = 0

	SomaArea=self.soma.L*self.soma.diam*h.PI
	SomascArea=h.PI*9.76*9.76
	#RappSomaDend12 = SomascArea/(4*Dend12Area)
	#RappSomaDend34 = SomascArea/(4*Dend34Area)
	global RappSomaNew 
	RappSomaNew = SomascArea/SomaArea
	global RappSomahill
	RappSomahill = SomascArea/(3.75*h.PI)

	self.soma.gl_GRC_LKG1 = glL*(RappSomaNew)*(2/3)
	self.soma.el_GRC_LKG1 = ell

	self.soma.ena = 87.39
	self.soma.ek = -84.69
	self.soma.eca = 129.33

	#resetgs()
	self.soma.gkbar_GRC_KA=0
	self.soma.gcabar_GRC_CA=0
	self.soma.gkbar_GRC_KIR=0
	self.soma.gkbar_GRC_KCA=0

	#gGUpdate()
	self.soma.ggaba_GRC_LKG2=0
	#self.soma.ecl = -65
	#KaU function
	self.soma.gkbar_GRC_KA=KaGmax*(1/1)*RappSomaNew*1
	#CaU function
	self.soma.gcabar_GRC_CA=CaGmax*(1/1)*RappSomaNew*0
	#KCaU function
	self.soma.gkbar_GRC_KCA=KCaD*(1/1)*RappSomaNew*0
	#KirU function
	self.soma.gkbar_GRC_KIR=KirGmax*(1/1)*RappSomaNew*1
	
	KcaDe = KCaGmax
	CaDe = CaGmax
		

	self.soma.beta_GRC_CALC=1.5	


	self.MF_L = []
	self.GOC_L = []	
	self.mfncpc = []
	self.gocncpc = []

	self.spike = h.NetStim(0.5, sec= self.soma)
        #self.spike.start = -10
        #self.spike.number = 1
	#self.spike.interval = 1e9

        self.nc_spike = h.NetCon(self.soma(1)._ref_v, self.spike,-20,0,1, sec = self.soma)

	# Recording vectors
	if self.record_all:
		self.record = {}

		self.record['spk'] = h.Vector()
		self.nc_spike.record(self.record['spk'])

		#self.record['time'] = h.Vector()
		#self.record['time'].record(h._ref_t)
	
		#self.record['vm'] = h.Vector()
		#self.record['vm'].record(self.soma(.5)._ref_v, sec = self.soma)




	#hillock definition
	self.hillock = [h.Section() for x in range(5)]	
	incr_hill=0
	for w in (self.hillock):
		w.push()
		w.nseg=1
		w.diam=2.3-0.5*incr_hill
		w.L=0.5
		w.cm=1
		w.Ra=100
		
		w.insert('GRC_LKG1')
		w.insert('GRC_NA')
		w.insert('GRC_KV')
		w.insert('extracellular')
		
		w.xg[0]=1e1
		w.xraxial[0]=1e1

		w.gl_GRC_LKG1=glL*(RappSomahill)*(1/15)
		w.el_GRC_LKG1=ell

		#NaHUpdate()
		w.gnabar_GRC_NA = NagH*gamma*RappSomahill-0.00243
		w.gkbar_GRC_KV = KvgH*gamma*RappSomahill-0.00243

		w.ena=87.39
		w.ek=-84.69
		h.pop_section()
		incr_hill+=1
                h.pop_section()

	#axon definition
	self.axon = [h.Section(cell=self) for x1 in range(30)]
	for w1 in (self.axon):
		w1.push()
		w1.nseg=1
		w1.diam=0.3
		w1.L=2.3367
		w1.cm=1
		w1.Ra=100

		w1.insert('GRC_LKG1')
		w1.insert('GRC_NA')
		w1.insert('GRC_KV')
		w1.insert('extracellular')

		w1.xg[0]=1e1
		w1.xraxial[0]=1e1

		global Rappaxon
		Rappaxon = ((9.76*9.76)/(naxon*w1.L*w1.diam))
		w1.gl_GRC_LKG1 = glL*(Rappaxon)*(1/30)
		w1.el_GRC_LKG1 = ell
		
		#NaAUpdate
		w1.gnabar_GRC_NA = NagA*(1-gamma)*Rappaxon-0.00232
		w1.gkbar_GRC_KV = KvgA*(1-gamma)*Rappaxon-0.00232

		w1.ena=87.39
		w1.ek=-84.69
		
		RappAH = 3.75/(naxon*self.axon[0].L*self.axon[0].diam)

		h.pop_section()

	#dendrite 1 definition

	self.dend1 = [h.Section(cell=self) for x2 in range(4)]
	for w2 in (self.dend1):
		w2.nseg=1
		w2.diam=0.75
		w2.L=5
		w2.cm=1
		w2.Ra=100

		w2.insert('GRC_LKG1')
		w2.insert('GRC_LKG2')
		w2.insert('GRC_KIR')
		w2.insert('GRC_KA')
		w2.insert('GRC_KCA')
		w2.insert('GRC_CA')
		w2.insert('GRC_CALC')
		w2.insert('extracellular')

		w2.xg[0]=1e1
		w2.xraxial[0]=1e1

		w2.ggaba_GRC_LKG2=3e-05
				
		w2.eca=129.33
		w2.ek=-84.69
		w2.beta_GRC_CALC=1.5

		w2.beta_GRC_CALC = beta
		w2.cai0_GRC_CALC = inicon

		#resetgd1()
		w2.gkbar_GRC_KA=0
		w2.gcabar_GRC_CA=0
		w2.gkbar_GRC_KIR=0
		w2.gkbar_GRC_KCA=0


	#dendrite 2 definition
	self.dend2 = [h.Section(cell=self) for x3 in range(4)]
	for w3 in (self.dend2):
		w3.nseg=1
		w3.diam=0.75
		w3.L=5
		w3.cm=1
		w3.Ra=100

		w3.insert('GRC_LKG1')
		w3.insert('GRC_LKG2')
		w3.insert('GRC_KIR')
		w3.insert('GRC_KA')
		w3.insert('GRC_KCA')
		w3.insert('GRC_CA')
		w3.insert('GRC_CALC')
		w3.insert('extracellular')
	
		w3.xg[0]=1e1
		w3.xraxial[0]=1e1

		w3.ggaba_GRC_LKG2=3e-05
		w3.gkbar_GRC_KIR=0
		w3.gkbar_GRC_KA=0
		w3.gkbar_GRC_KCA=0
		w3.gcabar_GRC_CA=0

		w3.beta_GRC_CALC=1.5	
		Dend12Area=self.dend1[0].L*self.dend1[0].diam*h.PI
		global RappSomaDend12
		RappSomaDend12=SomascArea/(4*Dend12Area)
		w3.eca=129.33
		w3.ek=-84.69

		w3.beta_GRC_CALC=beta
		w3.cai0_GRC_CALC=inicon

		#resetgd2
		w3.gkbar_GRC_KA=0
		w3.gcabar_GRC_CA=0
		w3.gkbar_GRC_KIR=0
		w3.gkbar_GRC_KCA=0

	#dendrite 3 definition
	self.dend3 = [h.Section(cell=self) for x4 in range(4)]
	for w4 in (self.dend3):
		w4.nseg=1
		w4.diam=0.75
		w4.L=2.5
		w4.cm=1
		w4.Ra=100

		w4.insert('GRC_LKG1')
		w4.insert('GRC_LKG2')
		w4.insert('GRC_KIR')
		w4.insert('GRC_KA')
		w4.insert('GRC_KCA')
		w4.insert('GRC_CA')
		w4.insert('GRC_CALC')
		w4.insert('extracellular')

		w4.xg[0]=1e1
		w4.xraxial[0]=1e1

		w4.ggaba_GRC_LKG2=3e-05
		w4.gkbar_GRC_KIR=0
		w4.gkbar_GRC_KA=0
		w4.gkbar_GRC_KCA=0
		w4.gcabar_GRC_CA=0
		w4.beta_GRC_CALC=1.5

		w4.eca=129.33
		w4.ek=-84.69

		#w4.Inhib = h.GRC_GABA(0.5)
		w4.beta_GRC_CALC=beta
		w4.cai0_GRC_CALC=inicon
		
		#resetgd3
		w4.gkbar_GRC_KA=0
		w4.gcabar_GRC_CA=0
		w4.gkbar_GRC_KIR=0
		w4.gkbar_GRC_KCA=0
		
	#dendrite 4 definition
	self.dend4 = [h.Section() for x5 in range(4)]
	for w5 in (self.dend4):
		w5.nseg=1
		w5.diam=0.75
		w5.L=2.5
		w5.cm=1
		w5.Ra=100

		w5.insert('GRC_LKG1')
		w5.insert('GRC_LKG2')
		w5.insert('GRC_CA')
		w5.insert('GRC_KIR')
		w5.insert('GRC_KA')
		w5.insert('GRC_KCA')
		w5.insert('GRC_CA')
		w5.insert('GRC_CALC')
		w5.insert('extracellular')

		w5.xg[0]=1e1
		w5.xraxial[0]=1e1

		w5.ggaba_GRC_LKG2=3e-05
		w5.gkbar_GRC_KIR=0
		w5.gkbar_GRC_KA=0
		w5.eca=129.33
		w5.ek=-84.69

		Dend34Area = self.dend4[0].L*self.dend4[0].diam*h.PI
		global RappSomaDend34
		RappSomaDend34 = SomascArea/(4*Dend34Area)
		w5.beta_GRC_CALC=beta
		w5.cai0_GRC_CALC=inicon

		#resetgd4()
		w5.gkbar_GRC_KA=0
		w5.gcabar_GRC_CA=0
		w5.gkbar_GRC_KIR=0
		w5.gkbar_GRC_KCA=0

		#CaDup()
		w5.gcabar_GRC_CA = CaDe*RappSomaDend34
		w5.gkbar_GRC_KCA = KcaDe*RappSomaDend34

        self.record['ca'] = h.Vector()
        self.record['ca'].record(self.dend3[3](.75)._ref_cai, sec = self.dend3[3])

		
	#branch 0 definition
	self.branch0 = h.Section(cell=self)
	self.branch0.nseg=1
	self.branch0.diam=0.3
	self.branch0.L=3
	self.branch0.cm=0.5
	self.branch0.Ra=100
	#self.branch0.celsius=30
	self.branch0.insert('GRC_LKG1')
	
	#branch 1 definition
	self.branch1 = h.Section(cell=self)
	self.branch1.nseg=1
	self.branch1.diam=0.2
	self.branch1.L=5
	self.branch1.cm=0.45
	self.branch1.Ra=100
	#self.branch1.celsius=30
	self.branch1.insert('GRC_LKG1')

	#branch 2 definition
	self.branch2 = h.Section(cell=self)
	self.branch2.nseg=1
	self.branch2.diam=0.1
	self.branch2.L=10
	self.branch2.cm=1
	self.branch2.Ra=90
	#self.branch2.celsius=30
	self.branch2.insert('GRC_LKG1')

	#branch3 definition
	self.branch3 = h.Section(cell=self)
	self.branch3.nseg=1
	self.branch3.diam=0.1
	self.branch3.L=200
	self.branch3.cm=1
	self.branch3.Ra=100
	#self.branch3.celsius=30
	self.branch3.insert('GRC_LKG1')

	#connecting all compartments

	for x in range(4):
		self.dend4[x].connect(self.dend3[x], 0, 1)
		self.dend3[x].connect(self.dend2[x], 0, 1)
		self.dend2[x].connect(self.dend1[x], 0, 1)
		self.dend1[x].connect(self.soma, 0, 1)

	self.soma.connect(self.hillock[0], 0, 1)
	self.hillock[0].connect(self.hillock[1], 0, 1)
	self.hillock[1].connect(self.hillock[2], 0, 1)
	self.hillock[2].connect(self.hillock[3], 0, 1)
	self.hillock[3].connect(self.hillock[4], 0, 1)
	self.hillock[4].connect(self.axon[0], 0, 1)

	for ax in range(29):
		self.axon[ax].connect(self.axon[ax+1], 0, 1)

	self.axon[29].connect(self.branch0, 0, 1)
	self.branch0.connect(self.branch1, 0, 1)
	self.branch1.connect(self.branch2, 0, 1)
	self.branch2.connect(self.branch3, 0, 1)

	self.synlist = []
	self.synlist1 = []
	self.nclist = []
	self.nclist1 = []

	self.assign_values()
	

	if self.vext_record_all:
		self.record['soma'] = h.Vector()
		self.record['soma'].record(self.soma(.5)._ref_vext[0], sec = self.soma)

		self.record['dend10'] = h.Vector()
		self.record['dend10'].record(self.dend1[0](.5)._ref_vext[0], sec = self.dend1[0])
		self.record['dend11'] = h.Vector()
		self.record['dend11'].record(self.dend1[1](.5)._ref_vext[0], sec = self.dend1[1])
		self.record['dend12'] = h.Vector()
		self.record['dend12'].record(self.dend1[2](.5)._ref_vext[0], sec = self.dend1[2])
		self.record['dend13'] = h.Vector()
		self.record['dend13'].record(self.dend1[3](.5)._ref_vext[0], sec = self.dend1[3])

		self.record['dend20'] = h.Vector()
		self.record['dend20'].record(self.dend2[0](.5)._ref_vext[0], sec = self.dend2[0])
		self.record['dend21'] = h.Vector()
		self.record['dend21'].record(self.dend2[1](.5)._ref_vext[0], sec = self.dend2[1])
		self.record['dend22'] = h.Vector()
		self.record['dend22'].record(self.dend2[2](.5)._ref_vext[0], sec = self.dend2[2])
		self.record['dend23'] = h.Vector()
		self.record['dend23'].record(self.dend2[3](.5)._ref_vext[0], sec = self.dend2[3])

		self.record['dend30'] = h.Vector()
		self.record['dend30'].record(self.dend3[0](.5)._ref_vext[0], sec = self.dend3[0])
		self.record['dend31'] = h.Vector()
		self.record['dend31'].record(self.dend3[1](.5)._ref_vext[0], sec = self.dend3[1])
		self.record['dend32'] = h.Vector()
		self.record['dend32'].record(self.dend3[2](.5)._ref_vext[0], sec = self.dend3[2])
		self.record['dend33'] = h.Vector()
		self.record['dend33'].record(self.dend3[3](.5)._ref_vext[0], sec = self.dend3[3])

		self.record['dend40'] = h.Vector()
		self.record['dend40'].record(self.dend4[0](.5)._ref_vext[0], sec = self.dend4[0])
		self.record['dend41'] = h.Vector()
		self.record['dend41'].record(self.dend4[1](.5)._ref_vext[0], sec = self.dend4[1])
		self.record['dend42'] = h.Vector()
		self.record['dend42'].record(self.dend4[2](.5)._ref_vext[0], sec = self.dend4[2])
		self.record['dend43'] = h.Vector()
		self.record['dend43'].record(self.dend4[3](.5)._ref_vext[0], sec = self.dend4[3])

		self.record['hillock0'] = h.Vector()
		self.record['hillock0'].record(self.hillock[0](.5)._ref_vext[0], sec = self.hillock[0])
		self.record['hillock1'] = h.Vector()
		self.record['hillock1'].record(self.hillock[1](.5)._ref_vext[0], sec = self.hillock[1])
		self.record['hillock2'] = h.Vector()
		self.record['hillock2'].record(self.hillock[2](.5)._ref_vext[0], sec = self.hillock[2])
		self.record['hillock3'] = h.Vector()
		self.record['hillock3'].record(self.hillock[3](.5)._ref_vext[0], sec = self.hillock[3])
		self.record['hillock4'] = h.Vector()
		self.record['hillock4'].record(self.hillock[4](.5)._ref_vext[0], sec = self.hillock[4])

		self.record['axon0'] = h.Vector()
		self.record['axon0'].record(self.axon[0](.5)._ref_vext[0], sec = self.axon[0])
		self.record['axon1'] = h.Vector()
		self.record['axon1'].record(self.axon[1](.5)._ref_vext[0], sec = self.axon[1])
		self.record['axon2'] = h.Vector()
		self.record['axon2'].record(self.axon[2](.5)._ref_vext[0], sec = self.axon[2])
		self.record['axon3'] = h.Vector()
		self.record['axon3'].record(self.axon[3](.5)._ref_vext[0], sec = self.axon[3])
		self.record['axon4'] = h.Vector()
		self.record['axon4'].record(self.axon[4](.5)._ref_vext[0], sec = self.axon[4])
		self.record['axon5'] = h.Vector()
		self.record['axon5'].record(self.axon[5](.5)._ref_vext[0], sec = self.axon[5])
		self.record['axon6'] = h.Vector()
		self.record['axon6'].record(self.axon[6](.5)._ref_vext[0], sec = self.axon[6])
		self.record['axon7'] = h.Vector()
		self.record['axon7'].record(self.axon[7](.5)._ref_vext[0], sec = self.axon[7])
		self.record['axon8'] = h.Vector()
		self.record['axon8'].record(self.axon[8](.5)._ref_vext[0], sec = self.axon[8])
		self.record['axon9'] = h.Vector()
		self.record['axon9'].record(self.axon[9](.5)._ref_vext[0], sec = self.axon[9])
		self.record['axon10'] = h.Vector()
		self.record['axon10'].record(self.axon[10](.5)._ref_vext[0], sec = self.axon[10])
		self.record['axon11'] = h.Vector()
		self.record['axon11'].record(self.axon[11](.5)._ref_vext[0], sec = self.axon[11])
		self.record['axon12'] = h.Vector()
		self.record['axon12'].record(self.axon[12](.5)._ref_vext[0], sec = self.axon[12])
		self.record['axon13'] = h.Vector()
		self.record['axon13'].record(self.axon[13](.5)._ref_vext[0], sec = self.axon[13])
		self.record['axon14'] = h.Vector()
		self.record['axon14'].record(self.axon[14](.5)._ref_vext[0], sec = self.axon[14])
		self.record['axon15'] = h.Vector()
		self.record['axon15'].record(self.axon[15](.5)._ref_vext[0], sec = self.axon[15])
		self.record['axon16'] = h.Vector()
		self.record['axon16'].record(self.axon[16](.5)._ref_vext[0], sec = self.axon[16])
		self.record['axon17'] = h.Vector()
		self.record['axon17'].record(self.axon[17](.5)._ref_vext[0], sec = self.axon[17])
		self.record['axon18'] = h.Vector()
		self.record['axon18'].record(self.axon[18](.5)._ref_vext[0], sec = self.axon[18])
		self.record['axon19'] = h.Vector()
		self.record['axon19'].record(self.axon[19](.5)._ref_vext[0], sec = self.axon[19])
		self.record['axon20'] = h.Vector()
		self.record['axon20'].record(self.axon[20](.5)._ref_vext[0], sec = self.axon[20])
		self.record['axon21'] = h.Vector()
		self.record['axon21'].record(self.axon[21](.5)._ref_vext[0], sec = self.axon[21])
		self.record['axon22'] = h.Vector()
		self.record['axon22'].record(self.axon[22](.5)._ref_vext[0], sec = self.axon[22])
		self.record['axon23'] = h.Vector()
		self.record['axon23'].record(self.axon[23](.5)._ref_vext[0], sec = self.axon[23])
		self.record['axon24'] = h.Vector()
		self.record['axon24'].record(self.axon[24](.5)._ref_vext[0], sec = self.axon[24])
		self.record['axon25'] = h.Vector()
		self.record['axon25'].record(self.axon[25](.5)._ref_vext[0], sec = self.axon[25])
		self.record['axon26'] = h.Vector()
		self.record['axon26'].record(self.axon[26](.5)._ref_vext[0], sec = self.axon[26])
		self.record['axon27'] = h.Vector()
		self.record['axon27'].record(self.axon[27](.5)._ref_vext[0], sec = self.axon[27])
		self.record['axon28'] = h.Vector()
		self.record['axon28'].record(self.axon[28](.5)._ref_vext[0], sec = self.axon[28])
		self.record['axon29'] = h.Vector()
		self.record['axon29'].record(self.axon[29](.5)._ref_vext[0], sec = self.axon[29])

	
	   
	if self.ionic_record_all:
		self.record['i_soma'] = h.Vector()
		self.record['i_soma'].record(self.soma(.5)._ref_i_membrane, sec = self.soma)

		self.record['i_dend10'] = h.Vector()
		self.record['i_dend10'].record(self.dend1[0](.5)._ref_i_membrane, sec = self.dend1[0])
		self.record['i_dend11'] = h.Vector()
		self.record['i_dend11'].record(self.dend1[1](.5)._ref_i_membrane, sec = self.dend1[1])
		self.record['i_dend12'] = h.Vector()
		self.record['i_dend12'].record(self.dend1[2](.5)._ref_i_membrane, sec = self.dend1[2])
		self.record['i_dend13'] = h.Vector()
		self.record['i_dend13'].record(self.dend1[3](.5)._ref_i_membrane, sec = self.dend1[3])

		self.record['i_dend20'] = h.Vector()
		self.record['i_dend20'].record(self.dend2[0](.5)._ref_i_membrane, sec = self.dend2[0])
		self.record['i_dend21'] = h.Vector()
		self.record['i_dend21'].record(self.dend2[1](.5)._ref_i_membrane, sec = self.dend2[1])
		self.record['i_dend22'] = h.Vector()
		self.record['i_dend22'].record(self.dend2[2](.5)._ref_i_membrane, sec = self.dend2[2])
		self.record['i_dend23'] = h.Vector()
		self.record['i_dend23'].record(self.dend2[3](.5)._ref_i_membrane, sec = self.dend2[3])

		self.record['i_dend30'] = h.Vector()
		self.record['i_dend30'].record(self.dend3[0](.5)._ref_i_membrane, sec = self.dend3[0])
		self.record['i_dend31'] = h.Vector()
		self.record['i_dend31'].record(self.dend3[1](.5)._ref_i_membrane, sec = self.dend3[1])
		self.record['i_dend32'] = h.Vector()
		self.record['i_dend32'].record(self.dend3[2](.5)._ref_i_membrane, sec = self.dend3[2])
		self.record['i_dend33'] = h.Vector()
		self.record['i_dend33'].record(self.dend3[3](.5)._ref_i_membrane, sec = self.dend3[3])

		self.record['i_dend40'] = h.Vector()
		self.record['i_dend40'].record(self.dend4[0](.5)._ref_i_membrane, sec = self.dend4[0])
		self.record['i_dend41'] = h.Vector()
		self.record['i_dend41'].record(self.dend4[1](.5)._ref_i_membrane, sec = self.dend4[1])
		self.record['i_dend42'] = h.Vector()
		self.record['i_dend42'].record(self.dend4[2](.5)._ref_i_membrane, sec = self.dend4[2])
		self.record['i_dend43'] = h.Vector()
		self.record['i_dend43'].record(self.dend4[3](.5)._ref_i_membrane, sec = self.dend4[3])

		self.record['i_hillock0'] = h.Vector()
		self.record['i_hillock0'].record(self.hillock[0](.5)._ref_i_membrane, sec = self.hillock[0])
		self.record['i_hillock1'] = h.Vector()
		self.record['i_hillock1'].record(self.hillock[1](.5)._ref_i_membrane, sec = self.hillock[1])

		self.record['i_hillock2'] = h.Vector()
		self.record['i_hillock2'].record(self.hillock[2](.5)._ref_i_membrane, sec = self.hillock[2])
		self.record['i_hillock3'] = h.Vector()
		self.record['i_hillock3'].record(self.hillock[3](.5)._ref_i_membrane, sec = self.hillock[3])
		self.record['i_hillock4'] = h.Vector()
		self.record['i_hillock4'].record(self.hillock[4](.5)._ref_i_membrane, sec = self.hillock[4])

		self.record['i_axon0'] = h.Vector()
		self.record['i_axon0'].record(self.axon[0](.5)._ref_i_membrane, sec = self.axon[0])
		self.record['i_axon1'] = h.Vector()
		self.record['i_axon1'].record(self.axon[1](.5)._ref_i_membrane, sec = self.axon[1])
		self.record['i_axon2'] = h.Vector()
		self.record['i_axon2'].record(self.axon[2](.5)._ref_i_membrane, sec = self.axon[2])
		self.record['i_axon3'] = h.Vector()
		self.record['i_axon3'].record(self.axon[3](.5)._ref_i_membrane, sec = self.axon[3])
		self.record['i_axon4'] = h.Vector()
		self.record['i_axon4'].record(self.axon[4](.5)._ref_i_membrane, sec = self.axon[4])
		self.record['i_axon5'] = h.Vector()
		self.record['i_axon5'].record(self.axon[5](.5)._ref_i_membrane, sec = self.axon[5])
		self.record['i_axon6'] = h.Vector()
		self.record['i_axon6'].record(self.axon[6](.5)._ref_i_membrane, sec = self.axon[6])
		self.record['i_axon7'] = h.Vector()
		self.record['i_axon7'].record(self.axon[7](.5)._ref_i_membrane, sec = self.axon[7])
		self.record['i_axon8'] = h.Vector()
		self.record['i_axon8'].record(self.axon[8](.5)._ref_i_membrane, sec = self.axon[8])
		self.record['i_axon9'] = h.Vector()
		self.record['i_axon9'].record(self.axon[9](.5)._ref_i_membrane, sec = self.axon[9])
		self.record['i_axon10'] = h.Vector()
		self.record['i_axon10'].record(self.axon[10](.5)._ref_i_membrane, sec = self.axon[10])
		self.record['i_axon11'] = h.Vector()
		self.record['i_axon11'].record(self.axon[11](.5)._ref_i_membrane, sec = self.axon[11])
		self.record['i_axon12'] = h.Vector()
		self.record['i_axon12'].record(self.axon[12](.5)._ref_i_membrane, sec = self.axon[12])
		self.record['i_axon13'] = h.Vector()
		self.record['i_axon13'].record(self.axon[13](.5)._ref_i_membrane, sec = self.axon[13])
		self.record['i_axon14'] = h.Vector()
		self.record['i_axon14'].record(self.axon[14](.5)._ref_i_membrane, sec = self.axon[14])
		self.record['i_axon15'] = h.Vector()
		self.record['i_axon15'].record(self.axon[15](.5)._ref_i_membrane, sec = self.axon[15])
		self.record['i_axon16'] = h.Vector()
		self.record['i_axon16'].record(self.axon[16](.5)._ref_i_membrane, sec = self.axon[16])
		self.record['i_axon17'] = h.Vector()
		self.record['i_axon17'].record(self.axon[17](.5)._ref_i_membrane, sec = self.axon[17])
		self.record['i_axon18'] = h.Vector()
		self.record['i_axon18'].record(self.axon[18](.5)._ref_i_membrane, sec = self.axon[18])
		self.record['i_axon19'] = h.Vector()
		self.record['i_axon19'].record(self.axon[19](.5)._ref_i_membrane, sec = self.axon[19])
		self.record['i_axon20'] = h.Vector()
		self.record['i_axon20'].record(self.axon[20](.5)._ref_i_membrane, sec = self.axon[20])
		self.record['i_axon21'] = h.Vector()
		self.record['i_axon21'].record(self.axon[21](.5)._ref_i_membrane, sec = self.axon[21])
		self.record['i_axon22'] = h.Vector()
		self.record['i_axon22'].record(self.axon[22](.5)._ref_i_membrane, sec = self.axon[22])
		self.record['i_axon23'] = h.Vector()
		self.record['i_axon23'].record(self.axon[23](.5)._ref_i_membrane, sec = self.axon[23])
		self.record['i_axon24'] = h.Vector()
		self.record['i_axon24'].record(self.axon[24](.5)._ref_i_membrane, sec = self.axon[24])
		self.record['i_axon25'] = h.Vector()
		self.record['i_axon25'].record(self.axon[25](.5)._ref_i_membrane, sec = self.axon[25])
		self.record['i_axon26'] = h.Vector()
		self.record['i_axon26'].record(self.axon[26](.5)._ref_i_membrane, sec = self.axon[26])
		self.record['i_axon27'] = h.Vector()
		self.record['i_axon27'].record(self.axon[27](.5)._ref_i_membrane, sec = self.axon[27])
		self.record['i_axon28'] = h.Vector()
		self.record['i_axon28'].record(self.axon[28](.5)._ref_i_membrane, sec = self.axon[28])
		self.record['i_axon29'] = h.Vector()
		self.record['i_axon29'].record(self.axon[29](.5)._ref_i_membrane, sec = self.axon[29])





    def assign_values(self):

		inicon=0.00225
		beta=0.6
		gG=3e-05
		for dx in range(4):
			self.dend1[dx].cai0_GRC_CALC=inicon
			self.dend2[dx].cai0_GRC_CALC=inicon
			self.dend3[dx].cai0_GRC_CALC=inicon
			self.dend4[dx].cai0_GRC_CALC=inicon

			self.dend1[dx].ggaba_GRC_LKG2=gG*0.25*(RappSomaDend12)
			self.dend2[dx].ggaba_GRC_LKG2=gG*0.25*(RappSomaDend12)
			self.dend3[dx].ggaba_GRC_LKG2=gG*0.25*(RappSomaDend34)
			self.dend4[dx].ggaba_GRC_LKG2=gG*0.25*(RappSomaDend34)
			self.dend1[dx].beta_GRC_CALC=beta
			self.dend2[dx].beta_GRC_CALC=beta
			self.dend3[dx].beta_GRC_CALC=beta
			self.dend4[dx].beta_GRC_CALC=beta


		NagH = 0.019
		NagA = 0.013
		KvgA = 0.003
		KvgH = 0.003

		gamma = 0.5

		for k in range(30):
			self.axon[k].gnabar_GRC_NA = NagA*(1-gamma)*Rappaxon-0.00232
			self.axon[k].gkbar_GRC_KV = KvgA*(1-gamma)*Rappaxon-0.00232

		for i in range(5):
			self.hillock[i].gnabar_GRC_NA = NagH*gamma*RappSomahill-0.00243
			self.hillock[i].gkbar_GRC_KV = KvgH*gamma*RappSomahill-0.00243

		self.branch0.gl_GRC_LKG1=0.000000005
		self.branch1.gl_GRC_LKG1=0.000000005
		self.branch2.gl_GRC_LKG1=0.000000005
		self.branch3.gl_GRC_LKG1=0.000000005

		gamma = 0.5
		NagH = 0.019
		KvgH = 0.003
		NagA = 0.013
		KvgA = 0.003
		CaDe = 0.00046
		KcaDe = 0.003
		KaGmax = 0.0032
		KirGmax = 0.0009
		glL = 5.68e-05
		gG = 3e-05
		
	
		self.soma.gl_GRC_LKG1 = glL*(RappSomaNew)*0.666666667#*(2/3)
		self.soma.el_GRC_LKG1 = ell

		for dx_rep in range(4):
			self.dend1[dx_rep].gl_GRC_LKG1=glL*(RappSomaDend12)*0.0625#(1/16)
			self.dend2[dx_rep].gl_GRC_LKG1=glL*(RappSomaDend12)*0.0625#(1/16)
			self.dend3[dx_rep].gl_GRC_LKG1=glL*(RappSomaDend34)*0.0625#(1/16)
			self.dend4[dx_rep].gl_GRC_LKG1=glL*(RappSomaDend34)*0.0625#(1/16)

			self.dend1[dx_rep].el_GRC_LKG1=ell
			self.dend2[dx_rep].el_GRC_LKG1=ell
			self.dend3[dx_rep].el_GRC_LKG1=ell
			self.dend4[dx_rep].el_GRC_LKG1=ell

		for ax_rep in range(30):
			self.axon[ax_rep].gl_GRC_LKG1=glL*(Rappaxon)*0.033333333#(1/30)
			self.axon[ax_rep].el_GRC_LKG1=ell

			self.axon[ax_rep].gnabar_GRC_NA=NagA*(1-gamma)*Rappaxon-0.00232
			self.axon[ax_rep].gkbar_GRC_KV=KvgA*(1-gamma)*Rappaxon-0.00232

		for hk in range(5):
			self.hillock[hk].gl_GRC_LKG1=glL*(RappSomahill)*0.066666667#(1/15)
	
			self.hillock[hk].el_GRC_LKG1=ell

			self.hillock[hk].gnabar_GRC_NA=NagH*gamma*RappSomahill-0.00243
			self.hillock[hk].gkbar_GRC_KV=KvgH*gamma*RappSomahill-0.00243
	

#    def synapses(self):	# commented the function synapses
#	for k in range(4): 
#		self.synI=h.GRC_GABA(self.dend3[k](0.5))
#		self.synI.gmax=2500
#		self.synI.U=0.34
#		self.synlist1.append(self.synI)
#		self.synE=h.AmpaCOD(self.dend4[k](0.5))
#		self.synE.gmax=600
#		self.synlist.append(self.synE)
#		self.synE1=h.NMDAS(self.dend4[k](0.5))
#		self.synE1.gmax=1e1
#		self.synlist.append(self.synE1)
#		self.ap_coun = h.APCount(self.dend4[k](0.5))
#		self.ap_coun.thresh=-20




    #Synapses
    #def createsyn(self,nmf=0,nrel = 0,ngoc = -1):
    def createsyn(self,nmf=0,nrel = 0,ngoc = -1,weight = 1, weight_var = 0, Dt = 0.1):
        # Use here the source target sting name
        # so the presynaptic link is not made
        # and it will have to be manged later
        # by the gid connect for parallel simulations
        #Mossy
        if ngoc <0 :
            ngoc = nmf
	num_dend = 0
	for i in range(nmf):
	    #self.MF_L.append(Synapse('glom',self,self.soma,nrel,record_all=1))
            # num_dend should loop or mod4 in order to place syn inputs > 4 on the available dendrites
            #self.MF_L.append(Synapse('glom',self,self.dend4[np.mod(num_dend,4)],nrel,record_all=0))
	    self.MF_L.append(Synapse('glom',self,self.dend4[np.mod(num_dend,4)],nrel,record_all=0,weight=1+rnd.random()*weight_var, Dt = Dt))
            num_dend = num_dend + 1
		
		
	inh_num_dend = 0		
        #Inibition
	for i in range(ngoc):
	    #self.GOC_L.append(Synapse('goc',self,self.soma,record_all=1))
		#self.GOC_L.append(Synapse('goc',self,self.dend3[np.mod(inh_num_dend,4)],record_all=0))
		self.GOC_L.append(Synapse('goc',self,self.dend3[np.mod(inh_num_dend,4)],record_all=0,weight=1+rnd.random()*weight_var, Dt = Dt))
		inh_num_dend = inh_num_dend + 1
		
		
	
    def pconnect(self,pc,source,syn_idx,type_syn):
        if type_syn == 'mf':
            source = int(source)
            self.mfncpc.append(pc.gid_connect(source, self.MF_L[syn_idx].input))
            self.mfncpc[-1].delay = 1
            self.mfncpc[-1].weight[0] = 1
            return self.mfncpc[-1]
        if type_syn == 'goc':
            source = int(source)
            # print "syn_len ", len(self.GOC_L), syn_idx, self.whatami, source
            self.gocncpc.append(pc.gid_connect(source, self.GOC_L[syn_idx].input))
            self.gocncpc[-1].delay = 1
            self.gocncpc[-1].weight[0] = 1
            return self.gocncpc[-1]


    def destroy(self):
        del self.nc_spike
        for m in self.MF_L:
            m.destroy()
            del m
        for m in self.GOC_L:
            m.destroy()
            del m
        for m in self.mfncpc:
            del m
        for m in self.gocncpc:
            del m
        del self

#for sec in h.allsec():
#	xg[0]=100e6 #//100e3.3
#	xraxial[0]=100e-3 #//1e-3.4



# -*- coding: utf-8 -*-
import sys
import h5py
import random as rnd
import numpy as np
import cPickle

from neuron import h,gui
pc = h.ParallelContext()
rank = int(pc.id())
size = int(pc.nhost())


seed = 123456+rank*34
rnd.seed(seed)
h.use_mcell_ran4(1)
h.mcell_ran4_init(seed)

from templates.glom.Glom_t import Glom
from templates.granule.GRANULE_Cell import Grc
from templates.golgi.Golgi_template import Goc
from templates.mli.stellate import Stellate
from templates.mossy.mf import Mf
from templates.mossy_old.mf_old import Mf_old
from templates.synapse.synapse import Synapse
import toolbox as tb
from simulation_setup import *


print save_dir




if plast :
    # Example of 'plastcity mask' -- can be applied with standard parameters
    # in simulation setup 
    plastDistro = np.load('plastDistroFinal.npy')


#print 'Plasticity file loaded'

seed = 123456+rank*34
rnd.seed(seed)
h.use_mcell_ran4(1)
h.mcell_ran4_init(seed)

if not rank:
    printout = open('run_log.txt','a+')
    if cells_on['rec_all_goc']:
        tb.dump_stdout(printout,"Recording all in Golgi cells")
    if cells_on['rec_all_grc']:
        tb.dump_stdout(printout,"Recording all in GRANULE cells")

# Read file data
f = open(dumpdir + '/' + str(rank) + '.npy','r')
cells_data = cPickle.load(f)
f.close()


if cells_on['mossy']:
    if rank==0:
        tb.dump_stdout(printout,"Creating Mossy Fibers...")
    if cells_data['mossy'] is not None:
        mossy = [tb.makecell(Mf(tmkc['to_makecell']['spike_train'],position=tmkc['to_makecell']['position']), tmkc['to_makecell']['gid'], tmkc['to_makecell']['idx'], rank,pc) for tmkc in cells_data['mossy']]
    if rank==0:
        tb.dump_stdout(printout,"Done")

if cells_on['glom']:
    if rank==0:
        tb.dump_stdout(printout,"Creating Glomeruli...\n")
    gloms = [tb.makecell(Mf_old(tmkc['to_makecell']['spike_train'], tmkc['to_makecell']['position'], background = mf_background), tmkc['to_makecell']['gid'], tmkc['to_makecell']['idx'], rank,pc) for tmkc in cells_data['glom']]
    if rank==0:
        tb.dump_stdout(printout,"Done\n")

if cells_on['goc']:
    if rank==0:
        tb.dump_stdout(printout,"Creating Golgis...")
    gocs = [tb.makecell(Goc(tmkc['to_makecell']['position'],leak_range= 0.05,record_all=cells_on['rec_all_goc'], Dt = save_dt), tmkc['to_makecell']['gid'], tmkc['to_makecell']['idx'], rank,pc) for tmkc in cells_data['goc']]
    if len(gocs) == 0:
        # Create a fake section for the time vector
        fake_sec = h.Section()
    # gocs = [tb.makecell(Goc(golgis_positions[idx],leak_range= 0.05,record_all=cells_on['rec_all_goc']), goc_gid_dict.get(idx,-10), idx, rank,pc) for idx in assigned_golgi_indexes if cells_to_create['goc'][idx]]
    for g in gocs:
        g[1][1].random_boot()
    if rank==0:
        tb.dump_stdout(printout,"Done\n")


## Create grc within 100 microm as granules and others as PF spikegens from MF template
if cells_on['grc']:
    if rank==0:
        tb.dump_stdout(printout,"Creating Granules...")
    grcs = [tb.makecell(Grc(tmkc['to_makecell']['position'],record_all=cells_on['rec_all_grc'], Dt = save_dt), tmkc['to_makecell']['gid'], tmkc['to_makecell']['idx'], rank,pc)
            for tmkc in cells_data['grc']]
    if cells_on['block_grc_tonic_gaba']:
        for g in grcs:
            g[1][1].soma.gbar_GRANULE_LKG2 = 0

            if not rank:
                tb.dump_stdout(printout,"Done\n")
                tb.dump_stdout(printout,"LKG2 %g \n"%g[1][1].soma.gbar_GRANULE_LKG2 )


elif cells_on['pf']:
    grcs = []


if cells_on['stl']:
    if rank==0:
        tb.dump_stdout(printout,"Creating MLIs...")
    stls = [tb.makecell(Stellate(tmkc['to_makecell']['position'], model_type = stl_type,record_all=cells_on['rec_all_stl'], background = stl_background,leak_range= 0.05, Dt = save_dt), tmkc['to_makecell']['gid'], tmkc['to_makecell']['idx'], rank,pc)
            for tmkc in cells_data['stl']]
    for g in stls:
        g[1][1].random_boot()
tb.barrier(pc)

connections = {}

if cells_on['mossy2glom']:
    a = dict([[g[0],g[1][1]] for g in gloms])
    connections['mossy2glom_nc'] = [a.get(tmkc['to_makecell']['idx']).pconnect(pc,tmkc['to_pconnect']['mossy_source_gid'],'mf')
                                    for tmkc in cells_data['glom']]


if cells_on['grc']:
    if rank==0:
        tb.dump_stdout(printout,"Creating grc synapses...\n")


    a = dict([[g[0],g[1][1]] for g in grcs])


    if cells_on['glom2grc']:
        if plast:
            print 'File loaded'
            for tmkc in cells_data['grc']:
                if tmkc['to_makecell']['idx'] in plastDistro[:,0]: # it definetely should be here! (...)
                    targetIdx = np.where(plastDistro[:,0]==tmkc['to_makecell']['idx'])[0][0]
                    syn_w = plastDistro[targetIdx,1]
                    a.get(tmkc['to_makecell']['idx']).createsyn(nmf=len(tmkc['to_pconnect']['glom2grc']),nrel = cells_on['glom2grc_nrel'],ngoc=0, weight = syn_w/0.42, weight_var = syn_var, Dt = save_dt)
                    print 'Plasticity done!'
                else:
                    a.get(tmkc['to_makecell']['idx']).createsyn(nmf=len(tmkc['to_pconnect']['glom2grc']),nrel = cells_on['glom2grc_nrel'],ngoc=0, weight = 0.42/0.42, weight_var = syn_var, Dt = save_dt)
        else:
            [a.get(tmkc['to_makecell']['idx']).createsyn(nmf=len(tmkc['to_pconnect']['glom2grc']),nrel = cells_on['glom2grc_nrel'],ngoc=0, weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['grc']]


        tb.barrier(pc)
        connections['glom2grc_nc'] = [a.get(tmkc['to_makecell']['idx']).pconnect(pc,s[0],s[1],s[2])
                                      for tmkc in cells_data['grc'] for s in tmkc['to_pconnect']['glom2grc']]




    if cells_on['goc2grc']:
        [a.get(tmkc['to_makecell']['idx']).createsyn(ngoc=len(tmkc['to_pconnect']['goc2grc']), weight = cells_on['goc2grc_gmax_factor'],
                                                     weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['grc']]

        tb.barrier(pc)
        connections['goc2grc_nc'] = [a.get(tmkc['to_makecell']['idx']).pconnect(pc,s[0],s[1],s[2])
                                    for tmkc in cells_data['grc'] for s in tmkc['to_pconnect']['goc2grc'] if s[0] != -10]



    del a
    if rank==0:
        tb.dump_stdout(printout,"Done\n")



if cells_on['goc']:
    if rank==0:
        tb.dump_stdout(printout,"Creating goc synapses...")



    a = dict([[g[0],[g[1][1],g[1][0]]] for g in gocs])
    if cells_on['grc2goc']:
        if rank==0:
            tb.dump_stdout(printout,"Grcs -> Goc")

        [a.get(tmkc['to_makecell']['idx'])[0].createsyn(ngrc=len(tmkc['to_pconnect']['grc2goc']),record_all=cells_on['rec_all_grc2goc'], weight_var = syn_var, Dt = save_dt)
         for tmkc in cells_data['goc']]
        tb.barrier(pc)
        connections['grc2goc_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],s[1],s[2],conduction_speed=s[3],grc_positions=s[4])
                                     for tmkc in cells_data['goc'] for s in tmkc['to_pconnect']['grc2goc']]



    if cells_on['grcaa2goc']:
        if rank==0:
            tb.dump_stdout(printout,"AA -> Goc")
        [a.get(tmkc['to_makecell']['idx'])[0].createsyn(naa=len(tmkc['to_pconnect']['grcaa2goc']),record_all=cells_on['rec_all_grcaa2goc'], weight_var = syn_var, Dt = save_dt)
         for tmkc in cells_data['goc']]
        tb.barrier(pc)
        connections['grcaa2goc_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],s[1],s[2])
                                     for tmkc in cells_data['goc'] for s in tmkc['to_pconnect']['grcaa2goc']]



    if cells_on['glom2goc']:
        if rank==0:
            tb.dump_stdout(printout,"Glom -> Goc")
        [a.get(tmkc['to_makecell']['idx'])[0].createsyn(nmf=len(tmkc['to_pconnect']['glom2goc']),record_all=cells_on['rec_all_glom2goc'], weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['goc']]
        tb.barrier(pc)
        connections['glom2goc_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],s[1],s[2])
                                     for tmkc in cells_data['goc'] for s in tmkc['to_pconnect']['glom2goc']]



    if cells_on['pf2goc']:
        if rank==0:
            tb.dump_stdout(printout,"Random spike PFs -> Goc")
        pf_for_gocs = []
        if pf_collapse:
            [a.get(tmkc['to_makecell']['idx'])[0].createsyn(npf=1,record_all=cells_on['rec_all_pf2goc'], weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['goc']]
            tb.barrier(pc)
            [pf_for_gocs.append(tb.makecell(Mf_old(spike_train=None,position=np.array([1e9,1e9,1e9]), background = tmkc['to_pconnect']['pf2goc'], whatami='pf'), -1,len(grcs)+len(pf_for_gocs) , rank,pc)) for tmkc in cells_data['goc']]
            grcs.extend(pf_for_gocs)
            connections['pf2goc_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,pf[1][1],-1,'pf_fake')
                                        for (tmkc,pf) in zip(cells_data['goc'],pf_for_gocs)]
        else:
            tb.dump_stdout(printout,"SINGLE PF explicit representation\n")
            tb.dump_stdout(printout,"NOT IMPLEMENTED YET!!!!\n")



    if cells_on['gocgap']:
        if not rank:
            tb.dump_stdout(printout,"and gap junctions...")
        [a.get(tmkc['to_makecell']['idx'])[0].creategap(len(tmkc['to_target_var']['gocgap']),int(a.get(tmkc['to_makecell']['idx'])[1]),gmax_gap,pc, Dt = save_dt) for tmkc in cells_data['goc']]
        tb.barrier(pc)
        [pc.target_var(a.get(tmkc['to_makecell']['idx'])[0].GAP_L[gap[0]].gapj._ref_vgap,gap[1]) for tmkc in cells_data['goc'] for gap in tmkc['to_target_var']['gocgap']]

        for tmkc in cells_data['goc']:
            for (gap,gap_prop) in zip(a.get(tmkc['to_makecell']['idx'])[0].GAP_L,tmkc['to_target_var']['gocgapprop']):
                [gap.gapj.g,gap.d,gap.CC] = gap_prop


    if cells_on['goc2goc']:
        if not rank:
            tb.dump_stdout(printout,"Creating GoC -> GoC inhbitory synapses")
        [a.get(tmkc['to_makecell']['idx'])[0].createsyn(ngoc=len(tmkc['to_pconnect']['goc2goc']),record_all=cells_on['rec_all_goc2goc'], weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['goc']]
        tb.barrier(pc)
        connections['goc2goc_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],s[1],s[2])
                                     for tmkc in cells_data['goc'] for s in tmkc['to_pconnect']['goc2goc']]


    if cells_on['stl2goc']:
        if not rank:
            for tmkc in cells_data['goc']:
                tb.dump_stdout(printout,'Creating StC -> GoC inhbitory synapses = '+str(len(tmkc['to_pconnect']['stl2goc'])) + ' number of synapses\n')
        [a.get(tmkc['to_makecell']['idx'])[0].createsyn(nmli=tmkc['to_createsyn']['nstl'],record_all=1, weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['goc']]
        tb.barrier(pc)
        # print [(s[0],s[1],s[2])
        #       for tmkc in cells_data['goc'] for s in tmkc['to_pconnect']['stl2goc']]
        connections['stl2goc_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],s[1],s[2])
                                     for tmkc in cells_data['goc'] for s in tmkc['to_pconnect']['stl2goc']]
    if rank==0:
        tb.dump_stdout(printout,"Done\n")


if cells_on['stl']:
    if rank==0:
        tb.dump_stdout(printout,"Creating stl synapses...\n")
    a = dict([[g[0],[g[1][1],g[1][0]]] for g in stls])

    if cells_on['grc2stl']:
        if rank==0:
            tb.dump_stdout(printout,"Creating GrC->stl synapses...\n")
        if pf_collapse:
            # Create a sigle postsynaptic element on the MLIs as we are using exponential decay synapses here (see Class Synapse) and they are linear
            # Therefore all input spikes will converge to a single synapse
            [a.get(tmkc['to_makecell']['idx'])[0].createsyn(ngrc=1,record_all=0, weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['stl']]
            tb.barrier(pc)
            if not rank:
                for tmkc in cells_data['stl']:
                    tb.dump_stdout(printout,"GrC total input to stl "+str(tmkc['to_makecell']['idx'])+' = '+str(len(tmkc['to_pconnect']['grc2stl']))+' number of synapses\n')

            # S[1] is set to one as pf_collapse is active so all incoming connections are made on the single input syapse that was created above
            connections['grc2stl_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],0,s[2],conduction_speed=s[3],grc_positions=s[4])
                                         for tmkc in cells_data['stl'] for s in tmkc['to_pconnect']['grc2stl']]


    if cells_on['pf2stl']:
        if rank==0:
            tb.dump_stdout(printout,"Creating Pf->stl synapses...\n")

        # for tmkc in cells_data['stl']:
        #     tb.dump_stdout(printout,tmkc['to_createsyn'].keys()
        pf_for_stls = []
        if pf_collapse:
            [a.get(tmkc['to_makecell']['idx'])[0].createsyn(npf=1,record_all=0, weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['stl']]
            tb.barrier(pc)
            if not rank:
                for tmkc in cells_data['stl']:
                    tb.dump_stdout(printout,"PF total input to stl "+str(tmkc['to_makecell']['idx'])+' = '+str(tmkc['to_pconnect']['pf2stl'])+' Hz\n')
            [pf_for_stls.append(tb.makecell(Mf_old(position=np.array([1e9,1e9,1e9]), background = tmkc['to_pconnect']['pf2stl'], whatami='pf'), -1,len(grcs)+len(pf_for_stls) , rank,pc)) for tmkc in cells_data['stl']]

            grcs.extend(pf_for_stls)
            # for (tmkc,pf) in zip(cells_data['goc'],pf_for_gocs):
            #     tb.dump_stdout(printout,a.get(tmkc['to_makecell']['idx'])[0], pf
            if rank==0:
                tb.dump_stdout(printout,"Connecting Pf->stl synapses...\n")
            connections['pf2stl_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,pf[1][1],-1,'pf_fake')
                                        for (tmkc,pf) in zip(cells_data['stl'],pf_for_stls)]
        else:
            tb.dump_stdout(printout,"SINGLE PF explicit representation\n")
            tb.dump_stdout(printout,"NOT IMPLEMENTED YET!!!!\n")

    if cells_on['stl2stl']:
        if rank==0:
            tb.dump_stdout(printout,"Creating stl->stl synapses...\n")
        [a.get(tmkc['to_makecell']['idx'])[0].createsyn(nmli=tmkc['to_createsyn']['nmli'],record_all=0, weight_var = syn_var, Dt = save_dt) for tmkc in cells_data['stl']]
        tb.barrier(pc)
        connections['stl2stl_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],0,s[2])
                                     for tmkc in cells_data['stl'] for s in tmkc['to_pconnect']['stl2stl']]
        # connections['stl2stl_nc'] = [a.get(tmkc['to_makecell']['idx'])[0].pconnect(pc,s[0],s[1],s[2])
        #                              for tmkc in cells_data['stl'] for s in tmkc['to_pconnect']['stl2stl']]
    if cells_on['stlgap']:
        if not rank:
            tb.dump_stdout(printout,"and gap junctions...\n")
        [a.get(tmkc['to_makecell']['idx'])[0].creategap(len(tmkc['to_target_var']['stlgap']),a.get(tmkc['to_makecell']['idx'])[1],1e3,pc, Dt = save_dt) for tmkc in cells_data['stl']]

        tb.barrier(pc)
        [pc.target_var(a.get(tmkc['to_makecell']['idx'])[0].GAP_L[gap[0]].gapj._ref_vgap,gap[1]) for tmkc in cells_data['stl'] for gap in tmkc['to_target_var']['stlgap']]

    if rank==0:
        tb.dump_stdout(printout,"Done\n")

tb.barrier(pc)
# Store global time
time_vector = h.Vector()

time_vector.record(h._ref_t, save_dt)

h.celsius = simulation_temperature #35.5
if rank == 0:


    tb.dump_stdout(printout,"SET TEMPERATURE to %3.1f\n" % h.celsius)




h.tstop = 1.0

if rank == 0:
    tb.dump_stdout(printout,"Preparing data files...\n")

# Calc length of vectors to store data in the hdf5 file
save_vec_length = np.max(np.array([round((cells_on['rec_end'] - cells_on['rec_start']) / sim_dt),2000]))



# Create data files in save_dir
save_file = save_dir + '/net2_cpu%d.hdf5' % rank
data = h5py.File(save_file, 'w')
data.create_dataset('seed',data=seed)
data.create_dataset('time', (save_vec_length,1), maxshape=(None, 1), chunks=(1000,1),compression='gzip',compression_opts=9)


if cells_on['grc']:
    grc_grp = data.create_group('grc')
    for grc in grcs:
        if grc[1][1].whatami == 'grc':
            grc_cell = grc_grp.create_group(str(grc[0]))
            for to_save in grc[1][1].record:
                if 'spk' in to_save:
                    data['/grc/'+str(grc[0])].create_dataset(to_save, (1,1), maxshape=(None,1))
                else:
                    data['/grc/'+str(grc[0])].create_dataset(to_save, (save_vec_length,1),chunks=(1000,1),compression='gzip',compression_opts=9, maxshape=(None,1))
                    #                 data['/grc/'+str(grc[0])].create_group('syns')
                    #                 for mfsyn_idx,mfsyn in enumerate(grc[1][1].MF_L):
                    #                data['/grc/'+str(grc[0])+'/syns'].create_dataset('spk_'+str(mfsyn_idx), (1,1), maxshape=(None,1), compression='lzf',shuffle=True)

if cells_on['goc']:
    goc_grp = data.create_group('goc')
    for goc in gocs:
        goc_cells = data['goc'].create_group(str(goc[0]))
        for to_save in goc[1][1].record:
            if 'spk' in to_save:
                data['/goc/'+str(goc[0])].create_dataset(to_save, (1,1), maxshape=(None,1))
            else:
                data['/goc/'+str(goc[0])].create_dataset(to_save, (save_vec_length,1),chunks=(1000,1),compression='gzip',compression_opts=9)

if cells_on['glom']:
    glom_grp = data.create_group('glom')
    for glom in gloms:
        glom_cells = data['glom'].create_group(str(glom[0]))
        for to_save in glom[1][1].record:
            if 'spk' in to_save:
                data['/glom/'+str(glom[0])].create_dataset(to_save, (1,1), maxshape=(None,1))
            else:
                data['/glom/'+str(glom[0])].create_dataset(to_save, (save_vec_length,1),chunks=(1000,1),compression='gzip',compression_opts=9)

if cells_on['stl']:
    stl_grp = data.create_group('stl')
    for stl in stls:
        stl_cells = data['stl'].create_group(str(stl[0]))
        for to_save in stl[1][1].record:
            if 'spk' in to_save:
                data['/stl/'+str(stl[0])].create_dataset(to_save, (1,1), maxshape=(None,1))
            else:
                data['/stl/'+str(stl[0])].create_dataset(to_save, (save_vec_length,1),chunks=(1000,1),compression='gzip',compression_opts=9)

if cells_on['pf']:
    pf_grp = data.create_group('pf')
    for grc in grcs:
        if grc[1][1].whatami == 'pf':
            pf_cells = data['pf'].create_group(str(grc[0]))
            for to_save in grc[1][1].record:
                if 'spk' in to_save:
                    data['/pf/'+str(grc[0])].create_dataset(to_save, (1,1), maxshape=(None,1))
                else:
                    data['/pf/'+str(grc[0])].create_dataset(to_save, (save_vec_length,1),chunks=(1000,1),compression='gzip',compression_opts=9)

data.close()
tb.barrier(pc)


if rank == 0:
    tb.dump_stdout(printout,"Maxstep...")
maxdelay = pc.set_maxstep(10)
# tb.dump_stdout(printout,"Madelay %4.1f" % maxdelay)
if rank == 0:
    tb.dump_stdout(printout,"Done\n")

tb.barrier(pc)

if cells_on['gocgap'] or cells_on['stlgap']:
    if rank == 0:
        tb.dump_stdout(printout,"Setup transfer...")
    pc.setup_transfer()
    tb.barrier(pc)
    if rank == 0:
        tb.dump_stdout(printout,"Done\n")


v_init = -60
if rank == 0:
    tb.dump_stdout(printout,"Vinit...")
h.finitialize(v_init)
tb.barrier(pc)
if rank == 0:
    tb.dump_stdout(printout,"Done\n")

if run_sim:
    if rank == 0:
        tb.dump_stdout(printout,"Init...")
        past_time = pc.time()
    h.stdinit()
    tb.barrier(pc)
    if rank == 0:
        tb.dump_stdout(printout,"Real time = %f\n" %  (pc.time()-past_time))

vm = []

if rank == 0:
    tb.dump_stdout(printout,"GO\n")



tb.barrier(pc)


h.tstop = 0.1
h.dt = sim_dt
tb.barrier(pc)
h.run()



if rank == 0:
    tb.dump_stdout(printout,"RUNNING on %i\n" % size)
cnt = 1

newdata = []

def print_len_Vectors(h):
    a =np.max([v.size()  for v in h.Vector])
    tb.dump_stdout(printout,"%g\n" % a)
    for v in h.Vector:
        if v.size() == a:
            tb.dump_stdout(printout,"%g" % a)


while h.t<simtime and run_sim:
    print h.t
    print cnt
    if rank == 0:
        tb.dump_stdout(printout,"Running...")
        past_time = pc.time()
    h.continuerun(cnt*simstep)

    tb.barrier(pc)
    if rank == 0:
        tb.dump_stdout(printout,"Simulated time = %g Real time = %g \n" % (h.t, pc.time()-past_time))

    if save_on:
        if h.t > cells_on['rec_start'] and h.t < cells_on['rec_end']:
            save = 'save'
        else:
            save = 'flush'
        if rank == 0:
            tb.dump_stdout(printout,"Saving...")
            past_time = pc.time()
        newdata.append(h5py.File(save_file, 'r+'))
        print np.array(time_vector)
        print time_vector.size()

        if 'save' in save:
            tb.var_write_hdf5(newdata[-1]['time'],time_vector)
            if cells_on['grc'] or cells_on['pf']:
                for g in grcs:
                    tb.hdfwrite(newdata[-1],g)
            if cells_on['goc']:
                for g in gocs:
                    tb.hdfwrite(newdata[-1],g)
            if cells_on['glom']:
                for g in gloms:
                    tb.hdfwrite(newdata[-1],g)
            if cells_on['stl']:
                for g in stls:
                    tb.hdfwrite(newdata[-1],g)
        elif 'flush' in save:
            if cells_on['grc'] or cells_on['pf']:
                for g in grcs:
                    tb.record_flush(newdata[-1],g)
            if cells_on['goc']:
                for g in gocs:
                    tb.record_flush(newdata[-1],g)
            if cells_on['glom']:
                for g in gloms:
                    tb.record_flush(newdata[-1],g)
            if cells_on['stl']:
                for g in stls:
                    tb.record_flush(newdata[-1],g)
        newdata[-1].flush()
        newdata[-1].close()

        tb.barrier(pc)
        if rank == 0:
            tb.dump_stdout(printout,"Done: Saving time = %g\n" % (pc.time()-past_time))
    tb.barrier(pc)
    cnt = cnt +1




if not rank:
    tb.dump_stdout(printout,"Simulation completed, removing objects...\n")
if cells_on['glom']:
    for g in gloms:
        g[1][1].destroy()
    del gloms
if cells_on['grc']:
    for g in grcs:
        g[1][1].destroy()
    del grcs
    cells_on['pf'] = 0
if cells_on['pf']:
    for g in grcs:
        g[1][1].destroy()
    del grcs
if cells_on['goc']:
    for g in gocs:
        g[1][1].destroy()
    del gocs
if cells_on['stl']:
    for g in stls:
        g[1][1].destroy()
    del stls


for c_idx,c in connections.iteritems():
    for cc in c:
        del cc
    del c

if mossy_stimulation and cells_on['mossy']:
    if not rank:
        for g in mossy:
            del g

tb.barrier(pc)

if not rank:
    tb.dump_stdout(printout,"Quit all processes...\n")

print quit_all
if quit_all:
    quit()

# -*- coding: utf-8 -*-
import sys
import cPickle
import h5py
import random as rnd
import numpy as np
import toolbox as tb
import scipy.io as sio
from simulation_setup import *

size = ncores
# Fix random seed
seed = 123456
rnd.seed(seed)


f = h5py.File('network_structure_file.hdf5', 'r')


print "Reading positions...",
cells_to_create = {}

######### 1 - Check for different cells and connections #############
# 'Cells_on' tells whether a certain cell or connection is present (1) or not (0) in the network.
# This can be setted in the 'mf_test.py' file
if cells_on['glom']:
    print "Gloms..."
    glomeruli_positions = f.get('positions/glomeruli')
    # The next command will retun a dict of Boolean values; if a certain glom is in the netsize, than True, otherwise False...
    cells_to_create['glom'] = [g[0].__lt__(netsize['glom']) for g in np.abs(np.add(glomeruli_positions,-origin))]

if cells_on['mossy']:
    print "Mossy..."
    mossy_positions = f.get('positions/mossy')
    mossy2glom_connection =  f.get('connections/glom_branching')
    mossy2glom_connection = np.array(mossy2glom_connection)

if cells_on['grc'] or cells_on['glom'] or cells_on['pf']:
    print "Grcs or PFs..."
    granules_positions = f.get('positions/granules')

if cells_on['grc'] or cells_on['pf']:
    print "PFs..."
    if 'strip' in netsize['grc_struct_type']:
        cells_to_create['grc'] = [g[1].__lt__(netsize['grc']) for g in np.abs(np.add(granules_positions,-origin))]
    elif 'cube' in netsize['grc_struct_type']:
        cells_to_create['grc'] = [g[0].__lt__(netsize['grc']) and g[1].__lt__(netsize['grc']) and g[2].__lt__(netsize['grc']) for g in np.abs(np.add(granules_positions,-origin))]

if cells_on['goc']:
    print "Gocs..."
    golgis_positions = f.get('positions/golgicells')
# ... golgis (the same for remaining cells and connections)
    cells_to_create['goc'] = [g[0].__lt__(netsize['goc']) for g in np.abs(np.add(golgis_positions,-origin))]
    #cells_to_create['goc'] = [g[1].__lt__(netsize['goc']) for g in np.abs(np.add(golgis_positions,-origin))]

if cells_on['stl']:
    print "Stls..."
    mlis_positions = f.get('positions/MLInterneurons')
    cells_to_create['stl'] = [g[0].__lt__(netsize['stl']) for g in np.abs(np.add(mlis_positions,-origin))]

if cells_on['gocgap'] or cells_on['goc2goc'] :
    print "Computing GoCs coupling",
    if cells_on['goc2goc'] and not cells_on['gocgap']:
        print " for goc2goc syns only..."
    if cells_on['goc2goc'] and cells_on['gocgap']:
        print " for gap junctions and goc2goc syns..."
    if not cells_on['goc2goc'] and cells_on['gocgap']:
        print " with electrical couplingb only..."
    # Limit the number to 10 according to VervaekeNeuron2010
    # Remove exceeding gapjunctions
    if cells_on['goc'] and (cells_on['gocgap'] or cells_on['goc2goc']):
        # Load gapj connections and dend-dend overlaps
        goc_goc_gap = np.array(f.get('connections/gocs_gocs_dd'))
        print "diagonalley_gapj"
        # Build gapj simmatrical matrix of connections: default method is Pcoupling from Ververke 2010
        goc_goc_gap_matrix = tb.diagonalley_gapj(goc_goc_gap,golgis_positions,cells_to_create['goc'])
        # print np.max(goc_goc_gap_matrix)
        print "Prune"
        # Build simmtrical along main diagonal matrix of binary selection based on conn probabilties
        goc_goc_gap_matrix = tb.prune_gapj(goc_goc_gap_matrix)
        print "Done"
        print "Goc 2 goc syn matrix"
        # Use the gapj matrix to build the goc->goc inh syn matrix

        # Hull 2012 pg. 152: These experiments revealed several
        # unitary synaptic connections between Golgi cells (10/50
        # directions, 20% connected, 1 pair = 2 directions;
        # Figure 4C).

        goc_goc_syn_matrix = tb.random_transpose_gapj(goc_goc_gap_matrix,cells_to_create['goc'],10)
        # for g in goc_goc_syn_matrix:
        #     for c_idx,c in enumerate(g):
        #         if c:
        #             if not cells_to_create['goc'][c_idx]:
        #                 print "ALERT"

    if cells_on['glom']:
        print "Gloms %d " % len([c for c in cells_to_create['glom'] if c]), "of real %d" % glomeruli_positions.shape[0]
    if cells_on['goc']:
        print "Golgi %d " % len([c for c in cells_to_create['goc'] if c]), "of real %d" % golgis_positions.shape[0]
    if cells_on['grc']:
        print "Granules %d " % len([c for c in cells_to_create['grc'] if c]), "of real %d" % granules_positions.shape[0]
    if cells_on['pf']:
        print "Par fibers %d " % len([c for c in cells_to_create['grc'] if not c]), "of real %d" % granules_positions.shape[0]
    if cells_on['stl']:
        print "MLIs %d " % len([c for c in cells_to_create['stl'] if c]), "of real %d" % mlis_positions.shape[0]

# Assign indexes to created cells
print "Start partitioning..."
if cells_on['grc']:
    # granules_available = np.ones(granules_positions.shape[0],dtype=int)
    assigned_grc_indexes = tb.even_distribute_list([g for g in np.arange(granules_positions.shape[0]) if cells_to_create['grc'][g]],size)

if cells_on['glom']:
    assigned_glom_indexes = tb.even_distribute_list([g for g in np.arange(glomeruli_positions.shape[0]) if cells_to_create['glom'][g]],size)

if cells_on['goc']:
    assigned_golgi_indexes = tb.even_distribute_list([g for g in np.arange(golgis_positions.shape[0]) if cells_to_create['goc'][g]],size)

if cells_on['stl']:
    assigned_stl_indexes = tb.even_distribute_list([g for g in np.arange(mlis_positions.shape[0]) if cells_to_create['stl'][g]],size)

if cells_on['pf']:
    assigned_pf_indexes = tb.even_distribute_list([g for g in np.arange(granules_positions.shape[0]) if not cells_to_create['grc'][g]],size)
    pf_partition = assigned_pf_indexes
print "1"

# ONLY for glomeruli index=gid  !!!!
if cells_on['grc'] or cells_on['pf']:
    # Keep track of gids assigned to grcs
    grc_indexes_gid = [[[g,g] for g in assigned_grc_indexes[node]] for node in np.arange(0,size)]
    # Append the max gid possible for grcs
    gid = range(0,granules_positions.shape[0]+100)
else:
    gid = [0]
if cells_on['pf']:
    pf_indexes_gid = [[[g,g] for g in assigned_pf_indexes[node]] for node in np.arange(0,size)]

if cells_on['glom']:
    print "Gloms..."
    glom_indexes_gid = [[[g,gid[-1]+g+1] for g in assigned_glom_indexes[node]] for node in np.arange(0,size)]
    # print "SUM ",sum([len(g) for g in glom_indexes_gid])
    gid.extend(range(gid[-1]+1,gid[-1]+1+glomeruli_positions.shape[0]+2))
    # print "Last gid glom ",gid[-1]
    # glom_indexes_gid = [[[idx,tb.generate_gid(gid,granules_positions.shape[0]-1)] for idx in assigned_glom_indexes[node]] for node in np.arange(0,size)]
    # gid.extend([3e6])
if cells_on['goc']:
    print "Gocs..."
    goc_indexes_gid = [[[g,gid[-1]+g+1] for g in assigned_golgi_indexes[node]] for node in np.arange(0,size)]
    # print "SUM ",sum([len(g) for g in goc_indexes_gid])
    gid.extend(range(gid[-1]+1,gid[-1]+1+golgis_positions.shape[0]+2))
    # print "Last gid goc ",gid[-1]
    # goc_indexes_gid = [[[idx,tb.generate_gid(gid,0)] for idx in assigned_golgi_indexes[node]] for node in np.arange(0,size)]
    # gid.extend([4e6])
if cells_on['stl']:
    print "Stls..."
    stl_indexes_gid = [[[g,gid[-1]+g+1] for g in assigned_stl_indexes[node]] for node in np.arange(0,size)]
    # print "SUM ",sum([len(g) for g in stl_indexes_gid])
    gid.extend(range(gid[-1]+1,gid[-1]+1+mlis_positions.shape[0]+2))
    # print "Last gid stl ",gid[-1]
    # gid.extend([5e6])
    # stl_indexes_gid = [[[idx,tb.generate_gid(gid,0)] for idx in assigned_stl_indexes[node]] for node in np.arange(0,size)]

print "2"


# Pull together all gids in a dictionary with cell_index as keys
if cells_on['grc']:
    grc_gid_dict = dict([i for g in grc_indexes_gid for i in g])
if cells_on['glom']:
    glom_gid_dict = dict([i for g in glom_indexes_gid for i in g])
if cells_on['goc']:
    goc_gid_dict = dict([i for g in goc_indexes_gid for i in g])
    # for cgoc in np.nonzero(cells_to_create['goc'])[0]:
    #     if goc_gid_dict.get(cgoc,-10) < 0:
    #         print "ALERT!!", cgoc
    #     else:
    #         print cgoc, goc_gid_dict.get(cgoc)
if cells_on['stl']:
    stl_gid_dict = dict([i for g in stl_indexes_gid for i in g])
if cells_on['pf']:
    pf_gid_dict = dict([i for g in pf_indexes_gid for i in g])

print "Done"
print "Done"

# Now that the correct gid's were generated we can choose to
# recalc or not the connections
print recalc_all

if not recalc_all:
    # if we dont want to recal all then only mossy and glom blocks are recalculated
    print "!!!! Recalculating only MFs and gloms!!!!"
    for k in cells_on.keys():
        cells_on[k] = 0
    cells_on['mossy'] = 0
    cells_on['glom'] = 1


####### 2 - Define target glomeruli and spike input pattern ################
# Here we start saving data for the parallel simulation
# data should be saved in ncores files in order to improve parallelization

if cells_on['glom']:
    print "Creating Glomeruli...",
    # Stimulation; simply define a sphere and select glomeruli included inside
    # such sphere as targets
    if spot_stimulation:
        gloms_to_stimulate = [ [g[0].__lt__(radius)
                                and g[1].__lt__(radius)
                                and g[2].__lt__(radius)
                                for g in np.abs(np.add(np.add(glomeruli_positions, -origin), -np.add(spt,-origin)))]
                               for spt in spot_centers]

        if gloms_in_simt_center < 1:
            for gts in gloms_to_stimulate:
                # print np.nonzero(gts)[0].shape
                gloms_to_stimulate_indexes = np.nonzero(gts)[0]
                gloms_to_reject = rnd.sample(gloms_to_stimulate_indexes,int(round(len(gloms_to_stimulate_indexes) * (1-gloms_in_simt_center))))
                print 'REJECTED GLOMS: ' + str(gloms_to_reject)
                for g in gloms_to_reject:
                    gts[g] = False

        elif gloms_in_simt_center > 1:
            for gts in gloms_to_stimulate:
                gloms_to_stimulate_indexes = np.nonzero(gts)[0]
                if len(gloms_to_stimulate_indexes) > gloms_in_simt_center:
                    gloms_to_reject = rnd.sample(gloms_to_stimulate_indexes,int(len(gloms_to_stimulate_indexes)-gloms_in_simt_center))
                    for g in gloms_to_reject:
                        gts[g] = False
        else:
            pass




        # Collect all gloms from all spots
        all_glom_selected_indexes_with_repetitions = [g for gts in gloms_to_stimulate for g in np.nonzero(gts)[0]]



        gloms_to_stimulate_a = [True if g in  np.unique(all_glom_selected_indexes_with_repetitions) else False for g in range(glomeruli_positions.shape[0])]

        # Take spike times from pre-specified array in simulation_setup
        spike_trains = times[0,:]
        spike_trains = [spike_trains if gl else None for gl in gloms_to_stimulate_a]

        print "Number of spike trains assigned ",len(np.nonzero(gloms_to_stimulate)[0])


        if new_background:
            n = len(gloms_to_stimulate_a)
            mf_back = tb.spgen(rate,totalTime,n,tau)
            for i in range(len(spike_trains)):
                print spike_trains[i] == None, len(mf_back[i]) > 0
                if (spike_trains[i] is None) & (len(mf_back[i]) > 0):
                    spike_trains[i] = mf_back[i]
                elif (spike_trains[i] is None) & (len(mf_back[i]) == 0):
                    pass
                else:
                    spike_trains[i] = np.sort(np.unique(np.append(spike_trains[i],mf_back[i])))




        for_gloms = [[{'to_makecell':
                       {'position':glomeruli_positions[idx], 'gid':glom_gid_dict.get(idx,-10), 'idx':idx, 'rank':rank,'whatami':'glom', 'spike_train':spike_trains[idx]},
                   'to_pconnect':{}
                   }
                  for idx in aglomi if cells_to_create['glom'][idx]]
                 for rank,aglomi in enumerate(assigned_glom_indexes)]
        gloms_to_stimulate = np.array(gloms_to_stimulate)
    else:
        spike_trains = None
        for_gloms = [[{'to_makecell':
                       {'position':glomeruli_positions[idx], 'gid':glom_gid_dict.get(idx,-10), 'idx':idx, 'rank':rank,'whatami':'glom', 'spike_train':spike_trains},
                    'to_pconnect':{}
                   }
                for idx in aglomi if cells_to_create['glom'][idx]]
                for rank,aglomi in enumerate(assigned_glom_indexes)]
    print "Done"






if cells_on['goc']:
    print "Creating Golgis...",
    for_gocs = [[{'to_makecell':
                      {'position':golgis_positions[idx], 'gid':goc_gid_dict.get(idx,-10), 'idx':idx, 'rank':rank,'whatami':'goc'},
                  'to_pconnect':{}
                  }
                 for idx in agolgii if cells_to_create['goc'][idx]]
                for rank,agolgii in enumerate(assigned_golgi_indexes)]
    # Gocs = [tb.makecell(Goc(golgis_positions[idx],leak_range= 0.05,record_all=cells_on['rec_all_goc']), goc_gid_dict.get(idx,-10), idx, rank,pc) for idx in assigned_golgi_indexes if cells_to_create['goc'][idx]]
    print "Done"


# ## Create grc within netsize['grc'] pf,sg,rd axes microm as granules and others as PF spikegens from MF template
if cells_on['grc'] and cells_on['glom']:
    print "Creating Granules...",
    for_grcs = [[{'to_makecell':
                      {'position':granules_positions[g], 'gid':g, 'idx':g, 'rank':rank,'whatami':'grc'},
                  'to_pconnect':{}
                  }
                 for g in gt if cells_to_create['grc'][g]]
                for rank,gt in enumerate(assigned_grc_indexes)]
    # grcs = [tb.makecell(Grc(granules_positions[idx],record_all=cells_on['rec_all_grc']), g[0], g[0], rank,pc)
    #         for idx,g in enumerate(glom_targets)
    #         if cells_to_create['grc'][g[0]]]
    print "Done"
elif cells_on['pf']:
    for_grcs = []


if cells_on['stl']:
    print "Creating MLIs...",
    for_stls = [[{'to_makecell':
                      {'position':mlis_positions[idx], 'gid':stl_gid_dict.get(idx,-10), 'idx':idx, 'rank':rank,'whatami':'stl'},
                  'to_pconnect':{}
                  }
                 for idx in agolgii if cells_to_create['stl'][idx]]
                for rank,agolgii in enumerate(assigned_stl_indexes)]
    # stls = [tb.makecell(Stellate(mlis_positions[idx], model_type = stl_type, background = stl_background,leak_range= 0.05), stl_gid_dict.get(idx,-10), idx, rank,pc) for idx in assigned_stl_indexes if cells_to_create['stl'][idx]]
    print "Done"
    del mlis_positions


if cells_on['glom2grc']:
    glom_grc = np.add(np.array(f.get('connections/glom_grc')),-1)
    glom_grc_inverted = np.add(np.array(f.get('connections/glom_grc_inverted')),-1)
if cells_on['glom2goc']:
    glom_goc = np.add(np.array(f.get('connections/glom_goc-bl')),-1)
if cells_on['goc2grc']:
    goc_glom = np.add(np.array(f.get('connections/goc_glom')),-1)
if cells_on['pf2goc'] or cells_on['grc2goc']:
    pfs_goc = np.add(np.array(f.get('connections/pfs_gocs')),-1)
if cells_on['grcaa2goc']:
    aas_goc = np.add(np.array(f.get('connections/grc_goc_aa')),-1)
if cells_on['pf2stl']:
    pfs_stl = np.add(np.array(f.get('connections/pfs_mlis')),-1)
if cells_on['stl2goc']:
    stl_goc = np.array(f.get('connections/mlis_gocs_ad'))  # This is a 2 layer 2D matrix
    # First layer stl_goc[:,:,0] contains indexes+1 of STL with axon overlapping woth GOC apical dendrite
    # Second layer stl_goc[:,:,1] contains the volume of overlap in m3
    # Moltiply second layer by 1e18 to get volume in um3
    stl_goc[:,:,0] = stl_goc[:,:,0] -1
    stl_goc[:,:,1] = stl_goc[:,:,1] * 1e18 # um3

if cells_on['stl2stl']:
    stl_stl_syn = np.add(np.array(f.get('connections/mlis_mlis_ad')),-1)
if cells_on['stlgap']:
    stl_stl_gap = np.array(f.get('connections/mlis_mlis_dd')) #  Why NOT -1 here?

if cells_on['grc']:
    if cells_on['glom2grc'] or cells_on['goc2grc']:
        print "Creating grc synapses..."
        if cells_on['glom2grc']:
            for g_rank in for_grcs:
                for grc in g_rank:
                    if grc['to_makecell']['whatami'] == 'grc':
                        grc['to_createsyn'] = {'nmf':len(tb.cell_exists(cells_to_create['glom'],np.array(glom_grc[grc['to_makecell']['idx']][glom_grc[grc['to_makecell']['idx']].__gt__(-1)])))}

        # # [grc[1][1].createsyn(nmf=len(tb.cell_exists(cells_to_create['glom'],np.array(glom_grc[grc[0]][glom_grc[grc[0]].nonzero()]))),nrel=4,ngoc=0, weight_var = syn_var)
        # #                      for grc_idx,grc in enumerate(grcs) if grc[1][1].whatami == 'grc']

        if cells_on['goc'] and cells_on['goc2grc']:
            for g_rank in for_grcs:
                for grc in g_rank:
                    if grc['to_makecell']['whatami'] == 'grc':
                        #for glom in tb.cell_exists(cells_to_create['glom'], np.array(glom_grc[grc['to_makecell']['idx']][glom_grc[grc['to_makecell']['idx']].__gt__(-1)])):
                            # print
                            # print goc_glom[glom]
                            # print np.where(glom_grc_inverted[glom] == grc['to_makecell']['idx'])[0][0]
                            # print grc['to_makecell']['idx']
                            # print
                            # print glom_grc_inverted[glom]
                            # print
                        #print np.where(glom_grc_inverted[glom] == grc)[0]
                        grc['to_createsyn']['ngoc'] = len([glom for glom in
                                                           tb.cell_exists(cells_to_create['glom'],
                                                                          np.array(glom_grc[grc['to_makecell']['idx']]
                                                                                   [glom_grc[grc['to_makecell']['idx']].__gt__(-1)]))
                                                           if goc_gid_dict.get(goc_glom[glom].item(),-10) >= -1])



        print "Done"

if cells_on['goc']:
    print "Creating goc synapses...",
    if cells_on['gocgap']:
        print "and gap junctions...",

    for g_rank in for_gocs:
        for goc in g_rank:
            if cells_on['grcaa2goc'] or cells_on['grc2goc'] or cells_on['glom2goc'] or cells_on['pf2goc'] or cells_on['goc2goc'] or cells_on['stl2goc']:
                goc['to_createsyn'] = {}
            if cells_on['grc2goc']:
                indexes_afferent_grcs = pfs_goc[goc['to_makecell']['idx'],:,0].__gt__(-1)

                goc['to_createsyn']['ngrc'] = len(tb.cell_exists(cells_to_create['grc'],
                                                                 np.array(pfs_goc[goc['to_makecell']['idx'],:,0]
                                                                          [pfs_goc[goc['to_makecell']['idx'],:,0].__gt__(-1)])))

                print "GOC %i #grc2goc = %i"%(goc['to_makecell']['idx'],goc['to_createsyn']['ngrc'])
                # goc['to_createsyn']['ngrc'] = len(pfs_goc[goc['to_makecell']['idx'],:,0][pfs_goc[goc['to_makecell']['idx'],:,0].__gt__(-1)])
            if cells_on['grcaa2goc']:
                goc['to_createsyn']['naa'] = len(tb.cell_exists(cells_to_create['grc'],
                                                                np.array(aas_goc[goc['to_makecell']['idx'],:]
                                                                         [aas_goc[goc['to_makecell']['idx'],:].__gt__(-1)])))
                print "GOC %i #grcaa2goc = %i"%(goc['to_makecell']['idx'],goc['to_createsyn']['naa'])

                # goc['to_createsyn']['naa'] = len(aas_goc[goc['to_makecell']['idx'],:][aas_goc[goc['to_makecell']['idx'],:].__gt__(-1)])
            if cells_on['glom2goc']:
                goc['to_createsyn']['nmf'] = len(tb.cell_exists(cells_to_create['glom'],np.extract(glom_goc[goc['to_makecell']['idx']]>-1,glom_goc[goc['to_makecell']['idx']])))
                print "GOC %i #glom2goc = %i"%(goc['to_makecell']['idx'],goc['to_createsyn']['nmf'])

            if cells_on['pf2goc']:
                goc['to_createsyn']['npf'] = 1

            if cells_on['goc2goc']:
                goc['to_createsyn']['ngoc'] = len(tb.cell_exists(cells_to_create['goc'],np.where(goc_goc_syn_matrix[goc['to_makecell']['idx']]==1)[0]))

            if cells_on['stl2goc']:
                # We create a single synapse here as the STL->GOC synapses are modelled as exponential decay without presyn dynamics
                # and connect all incoming axons to this synapse
                goc['to_createsyn']['nstl'] = 1
            if cells_on['gocgap']:
                goc['to_creategap'] = {'ngap': len(tb.cell_exists(cells_to_create['goc'],np.where(goc_goc_gap_matrix[goc['to_makecell']['idx']]==1)[0]))}
    print "Done"

if cells_on['stl']:
    print "Creating stl synapses...",
    for s_rank in for_stls:
        for stl in s_rank:
            if cells_on['pf'] or cells_on['grc'] or cells_on['stl2stl']:
                stl['to_createsyn'] = {}

            if cells_on['pf'] or cells_on['grc']:
                stl['to_createsyn']['npf'] = 1 #int(len(pfs_stl[stl[0]].nonzero()[0]) * pfs_stl_prune)
            if cells_on['stl2stl']:
                # aa = [int(b) for b in stl_stl_syn[stl['to_makecell']['idx'],:,0][stl_stl_syn[stl['to_makecell']['idx'],:,0].__gt__(-1)]]
                stl['to_createsyn']['nmli'] = 1 # len(tb.cell_exists(cells_to_create['stl'],aa))

            if cells_on['stlgap']:
                print "and gap junctions..."
                stl['to_creategap'] = {'ngap': len(tb.cell_exists(cells_to_create['stl'],stl_stl_gap[stl['to_makecell']['idx'],:,0][stl_stl_gap[stl['to_makecell']['idx'],:,0].__gt__(-1)]))}
    print "Done"


print "Connecting neurons..."

if cells_on['glom2grc']:
    print "Creating glom2grc..."
    for g_rank in for_grcs:
        [grc['to_pconnect'].update({'glom2grc':
                                        [[int(glom_gid_dict.get(source,-10)),source_idx,'mf']
                                         for source_idx,source in enumerate(tb.cell_exists(cells_to_create['glom'],
                                                                                           np.array(glom_grc[grc['to_makecell']['idx']][glom_grc[grc['to_makecell']['idx']].__gt__(-1)])))
                                         if source >= 0]})
         for grc in [real_grc for real_grc in g_rank if real_grc['to_makecell']['whatami'] == 'grc']]




if cells_on['glom2goc']:
    print "Connecting glom2goc..."
    for g_rank in for_gocs:
        [goc['to_pconnect'].update({'glom2goc':
                                        [[int(glom_gid_dict.get(source,-10)),source_idx,'mf']
                                         for source_idx,source in
                                         enumerate(tb.cell_exists(cells_to_create['glom'],
                                                                  glom_goc[goc['to_makecell']['idx']][glom_goc[goc['to_makecell']['idx']].__gt__(-1)]))
                                         if source >= 0]})
                                         for goc in g_rank]


if cells_on['goc2grc']:
    print "Connecting goc2grc..."
    for g_rank in for_grcs:
        [grc['to_pconnect'].update({'goc2grc':
                                    [[goc_gid_dict.get(goc_glom[glom].item(),-10),glom_idx,'goc']
                                     for glom_idx,glom in enumerate(
                                             [gl for gl in tb.cell_exists(cells_to_create['glom'],np.array(glom_grc[grc['to_makecell']['idx']][glom_grc[grc['to_makecell']['idx']].__gt__(-1)]))
                                              if goc_gid_dict.get(goc_glom[gl].item(),-10) >= -1] )]})
         for grc in [real_grc for real_grc in g_rank if real_grc['to_makecell']['whatami'] == 'grc']]


if cells_on['glom2grc']:
    del glom_grc
if cells_on['goc2grc']:
    del goc_glom
    # print "goc2grc_nc",len(connections['goc2grc_nc'])

if cells_on['grc2goc']:
    print "Connecting grc2goc..."
    for g_rank in for_gocs:
        [goc['to_pconnect'].update({'grc2goc':
                                        [[pf,pf_idx,'grc',pf_conduction_speed,granules_positions[pf]]
                                         for pf_idx,pf in
                                         enumerate([pf for pf in pfs_goc[goc['to_makecell']['idx'],:,0][pfs_goc[goc['to_makecell']['idx'],:,0].__gt__(-1)] if grc_gid_dict.get(pf,-10)>-1])
                                         ]})
         for goc in g_rank]



if cells_on['grcaa2goc']:
    print "Connecting grcaa2goc..."
    for g_rank in for_gocs:
        [goc['to_pconnect'].update({'grcaa2goc':
                                        [[aa,aa_idx,'aa']
                                         for aa_idx,aa in
                                         enumerate([aa_idx for aa_idx in
                                                    aas_goc[goc['to_makecell']['idx'],:][aas_goc[goc['to_makecell']['idx'],:].__gt__(-1)]
                                                    if grc_gid_dict.get(aa_idx,-10)>-1])
                                         ]})
         for goc in g_rank]

if cells_on['pf2goc']:
    print "Connecting pf2goc..."
    for g_rank in for_gocs:
        if pf_collapse:
            not_created_grcs = [not g for g in cells_to_create['grc']]
            [goc['to_pconnect'].update({'pf2goc':
                                            pf_background * len(tb.cell_exists(not_created_grcs,np.extract(pfs_goc[goc['to_makecell']['idx'],:,0]>-1,pfs_goc[goc['to_makecell']['idx'],:,0])))
                                        })
             for goc in g_rank]

        else:
            [goc['to_pconnect'].update({'pf2goc':
                                            [[pf,pf_idx,'pf']
                                             for pf_idx,pf in enumerate(pfs_goc[goc['to_makecell']['idx'],:,0][pfs_goc[goc['to_makecell']['idx'],:,0].__gt__(-1)])
                                             if pf_gid_dict.get(pf,-10)>-1]})
             for goc in g_rank]

    del pfs_goc


if cells_on['stl2goc']:
    for g_rank in for_gocs:
        if stl_collapse:
            if stl_conn_mask_type == 'volume_threshold':
                [goc['to_pconnect'].update({'stl2goc':
                                            [[stl_gid_dict.get(source[0]),0,'stl']
                                             for source_idx,source in
                                             enumerate(stl_goc[goc['to_makecell']['idx'],stl_goc[goc['to_makecell']['idx'],...,0].__gt__(-1),:])
                                             if source[1] > stl_goc_syn_overlap_threshold and cells_to_create['stl'][int(source[0])]
                                             ]})
                 for goc in g_rank]
            elif stl_conn_mask_type == 'volume_probability':
                stl_goc[:,:,1] = stl_goc[:,:,1] / np.max(stl_goc[:,:,1])
                [goc['to_pconnect'].update({'stl2goc':
                                            [[stl_gid_dict.get(source[0]),0,'stl']
                                             for source_idx,source in
                                             enumerate(stl_goc[goc['to_makecell']['idx'],stl_goc[goc['to_makecell']['idx'],...,0].__gt__(-1),:])
                                             if source[1] < rnd.random()  and cells_to_create['stl'][int(source[0])]
                                             ]})
                 for goc in g_rank]
        else:
            if stl_conn_mask_type == 'volume_threshold':
                [goc['to_pconnect'].update({'stl2goc':
                                            [[stl_gid_dict.get(source[0]),source_idx,'stl']
                                             for source_idx,source in
                                             enumerate(stl_goc[goc['to_makecell']['idx'],stl_goc[goc['to_makecell']['idx'],...,0].__gt__(-1),:])
                                             if source[1] > stl_goc_syn_overlap_threshold and cells_to_create['stl'][int(source[0])]
                                             ]})
                 for goc in g_rank]
            elif stl_conn_mask_type == 'volume_probability':
                stl_goc[:,:,1] = stl_goc[:,:,1] / np.max(stl_goc[:,:,1])
                [goc['to_pconnect'].update({'stl2goc':
                                            [[stl_gid_dict.get(source[0]),source_idx,'stl']
                                             for source_idx,source in
                                             enumerate(stl_goc[goc['to_makecell']['idx'],stl_goc[goc['to_makecell']['idx'],...,0].__gt__(-1),:])
                                             if source[1] < rnd.random()  and cells_to_create['stl'][int(source[0])]
                                             ]})
                 for goc in g_rank]

        stl_list_dtype = [('goc_index',int),('nconns',int)]

        store_stl2goc_nconns = np.array([(goc['to_makecell']['idx'],len(goc['to_pconnect']['stl2goc'])) for goc in g_rank], dtype = stl_list_dtype)
        store_stl2goc_nconns = np.sort(store_stl2goc_nconns, order='goc_index')

        if stl2goc_max_syn:
            for goc in g_rank:
                goc['to_pconnect']['stl2goc'] = [goc['to_pconnect']['stl2goc'][x] for x in rnd.sample(range(len(goc['to_pconnect']['stl2goc'])),stl2goc_max_syn)]

            store_stl2goc_nconns_reduced = np.array([(goc['to_makecell']['idx'],len(goc['to_pconnect']['stl2goc'])) for goc in g_rank], dtype = stl_list_dtype)
            store_stl2goc_nconns_reduced = np.sort(store_stl2goc_nconns_reduced, order='goc_index')

            print "STL->GOC number of synapses "
            print "GoC index\t\tNumber of STL connections\tReduced number"
            for n,n_r in zip(store_stl2goc_nconns, store_stl2goc_nconns_reduced):
                print '{0:5d}\t\t{1:5d}\t\t{2:5d}'.format(n[0],n[1],n_r[1])
        else:
            print "STL->GOC number of synapses "
            print "GoC index\t\tNumber of STL connections"
            for n in store_stl2goc_nconns:
                print '{0:5d}\t\t{1:5d}'.format(n[0],n[1])



    del stl_goc



if cells_on['pf2stl']:
    print "Connecting pf2stl..."
    for g_rank in for_stls:
        if pf_collapse:
            not_created_grcs = [not g for g in cells_to_create['grc']]
            [stl['to_pconnect'].update({'pf2stl':
                                            pf_background * min(pfs_stl_max,
                                                                len(tb.cell_exists(not_created_grcs,
                                                                                   np.extract(pfs_stl[stl['to_makecell']['idx'],:,0],
                                                                                              pfs_stl[stl['to_makecell']['idx'],:,0]))))
                                        })
             for stl in g_rank]

            if cells_on['grc2stl']:
                [stl['to_pconnect'].update({'grc2stl':
                                                [[grc,0,'grc',pf_conduction_speed,granules_positions[grc]]
                                                 for grc_idx,grc in enumerate(tb.cell_exists(cells_to_create['grc'],
                                                                                             pfs_stl[stl['to_makecell']['idx'],:,0][pfs_stl[stl['to_makecell']['idx'],:,0].__gt__(-1)]))]
                                            })
                 for stl in g_rank]



        else:
            [stl['to_pconnect'].update({'grc2stl':[[pf,pf_idx,'pf'] for pf_idx,pf in enumerate(pfs_stl[stl['to_makecell']['idx'],:,0][pfs_stl[stl['to_makecell']['idx'],:,0].__gt__(-1)])]}) for stl in g_rank]


if cells_on['grc']:
    del granules_positions
if cells_on['pf2stl']:
    del pfs_stl

if cells_on['stl2stl']:
    print "Connecting stl2stl..."
    for g_rank in for_stls:
            [stl['to_pconnect'].update({'stl2stl':
                                            [[int(stl_gid_dict.get(source,-10)),source_idx,'stl']
                                             for source_idx,source in
                                             enumerate(tb.cell_exists(cells_to_create['stl'],
                                                                      stl_stl_syn[stl['to_makecell']['idx'],:,0][stl_stl_syn[stl['to_makecell']['idx'],:,0].__gt__(-1)]))
                                             if source >= 0]
                                        })
             for stl in g_rank]



if rank==0:
    print "Done"

if cells_on['stlgap']:
    print "Connecting gap junctions...",
    for g_rank in for_stls:
        for stl in g_rank:
            stl['to_target_var'] = {}
            stl['to_target_var']['stlgap'] = []
            for target_idx,source in enumerate(tb.cell_exists(cells_to_create['stl'],
                                                              stl_stl_gap[stl['to_makecell']['idx'],:,0][stl_stl_gap[stl['to_makecell']['idx'],:,0].nonzero()])): #stl_ggid_dict.get(stl[0],-10)):
                if source-1 == stl['to_makecell']['idx']: print "Warning!!!"
                other_stl = stl_gid_dict.get(source,-10)
                if other_stl > -1:
                    # Values for the source_variable (gid.v) associated with the source_global_index will be copied to the target_variable (vgap) every time step
                    stl['to_target_var']['stlgap'].append([target_idx, other_stl])


    print "Done"

if cells_on['stl2stl']:
    del stl_stl_syn

if cells_on['stlgap']:
    del stl_stl_gap

if cells_on['goc'] and cells_on['goc2goc']:
    print "Connecting Golgi cells with chemical synapses..",
    for g_rank in for_gocs:
        [goc['to_pconnect'].update({'goc2goc':
                                        [[int(goc_gid_dict.get(source,-10)),source_idx,'goc']
                                         for source_idx,source in enumerate(np.where(goc_goc_syn_matrix[goc['to_makecell']['idx']]==1)[0])]})
         for goc in g_rank]

    print "Done"

if cells_on['goc2goc']:
    del goc_goc_syn_matrix

if cells_on['goc'] and cells_on['gocgap']:
    print "Connecting gap junctions...",
    for g_rank in for_gocs:
        for goc in g_rank:
            goc['to_target_var'] = {}
            goc['to_target_var']['gocgap'] = []
            goc['to_target_var']['gocgapprop'] = []
            for target_idx,source in enumerate(tb.cell_exists(cells_to_create['goc'],
                                                              np.where(goc_goc_gap_matrix[goc['to_makecell']['idx']]==1)[0])):
                if source == goc['to_makecell']['idx']: print "Warning!!!"
                # Values for the source_variable (gid.v) associated with the source_global_index will be
                # copied to the target_variable (vgap) every time step
                other_goc = goc_gid_dict.get(source,-10)
                if other_goc > -1:
                    goc['to_target_var']['gocgap'].append([target_idx, other_goc+2e9])

                    # Converts the distance between two cells into their gapj coupling and then to gapj conductance (nS) according to VervaekeNeuron2010
                    goc['to_target_var']['gocgapprop'].append(tb.gapj_g(goc['to_makecell']['idx'],source,golgis_positions))


print "Done"

if cells_on['goc']:
    del golgis_positions
if cells_on['gocgap']:
    del goc_goc_gap_matrix

# Set stimulation of some Mfs in the center of the network
# Select the mfs
def mossy_idx2gid(idx):
	return 1e7+idx

f.close()

# Saving data in cPickle files
import os
import shutil
#dumpdir = dumpdir + '_new'
if os.path.exists(dumpdir) and recalc_all:
     shutil.rmtree(dumpdir)
if not os.path.exists(dumpdir):
     os.mkdir(dumpdir)


for ncpu in range(ncores):
    print 'Saving or updating data of cpu ',ncpu
    if recalc_all:
        f = open(dumpdir + '/' + str(ncpu) + '.npy','w')
    else:
        f = open(sourcedir + '/' + str(ncpu) + '.npy','r')
        new_f = open(dumpdir + '/' + str(ncpu) + '.npy','w')

    to_dump = {}
    if not recalc_all:
        if ncpu == 0:
            print "Reloading preprocesed data."
        to_read = cPickle.load(f)
        for key in ['grc','goc','stl']:
            if key in to_read.keys():
                to_dump[key] = to_read[key]


    if cells_on['grc']:
        to_dump.update({'grc':for_grcs[ncpu]})
    if cells_on['goc']:
        to_dump.update({'goc':for_gocs[ncpu]})
    if cells_on['glom']:
        to_dump.update({'glom':for_gloms[ncpu]})
        if mossy_stimulation and ncpu==0:
            to_dump.update({'mossy':for_mossy})
        else:
            to_dump.update({'mossy':None})
    if cells_on['stl']:
        to_dump.update({'stl':for_stls[ncpu]})
    if ncpu == 0:
        print to_dump.keys()
    if recalc_all:
        cPickle.dump(to_dump,f)
    else:
        cPickle.dump(to_dump,new_f)
        new_f.close()
    f.close()

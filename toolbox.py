# -*- coding: utf-8 -*-
import numpy as np
import random as rnd

# Partition here the gloms among the processes
# this could be done better using the siblings and clustring in n-processes clusters
def segment(n_elements, n_segments, n, elements_per_segment=0):
    if elements_per_segment == 0:
        elements_per_segment = int(n_elements/n_segments)
        lower_bound = n*elements_per_segment
    if n >= n_segments:
        return 'Error!'
    elif n == n_segments-1:
        upper_bound = n_elements
    else:
        upper_bound = (n+1)*elements_per_segment
    return({'lower': int(lower_bound), 'upper': int(upper_bound)})

def partition(n_gloms,size):
  # We want to assigne n gloms to the master and 3n gloms to the slaves
  # Need to cast half_glom_per_node to double not to loose the decimanls!!!
  partition_bounds = [segment(n_gloms - 1, 3*(size-1)+1,seg_num) for seg_num in np.arange(3*(size-1)+1)]
  # Get the index of the boundaries we want to  use
  partition_bounds_index = np.arange(len(partition_bounds))
  partition_bounds_index = np.append(partition_bounds_index[0],partition_bounds_index[1::3])
  # Convert the boundary index to glom indexes
  partition_indexes = np.array([x['lower'] for i, x in enumerate(partition_bounds) if i in partition_bounds_index])
  return [np.diff(np.append(partition_indexes,n_gloms)), partition_indexes]
  # print partition, partition_indexes

def enumerate_reptitions(glom_targets):
    glom_targets = np.reshape(glom_targets,glom_targets.shape[0]*glom_targets.shape[1])
    glom_targets = np.sort(glom_targets[glom_targets.nonzero()])-1
    idx = np.sort(glom_targets[(np.append(1,np.diff(glom_targets)) > 0)])
    dtype = [('index',int),('repetition',int)]
    idx = np.array([(x,len(np.where(glom_targets == x)[0])) for x in idx],dtype=dtype)
    print ".",
    return np.sort(idx, order='repetition')

## Create a cell, and set pc.cell and pc.outputcell
def makecell(cell_template, gid, idx, rank, pc):
    exec 'cell = cell_template'
    if gid > -1:
        pc.set_gid2node(gid, rank)
        #nc = cell.connect2target(None)
        pc.cell(gid, cell.nc_spike)
        pc.outputcell(gid)
        # dtype = [('cell',type(cell)),('gid',int),('idx',int)]
    return [idx,[gid,cell]]

def generate_gid(gid,start=0):
    if len(gid)>0:
        newgid = max(gid)+1
    else:
        newgid = start
    gid.append(newgid)
    return newgid

def even_distribute(n_elements,n_proc,n_rank = None):
    if n_rank is not None:
        # Create n_proc lists each contains list of int jumping n_proc elements
        return range(n_rank,n_elements,n_proc)
    else:
        return [np.arange(proc,n_elements,n_proc,dtype=int)
                for proc in np.arange(n_proc)]

def even_distribute_list(elements,n_proc):
    # elements is a list of indexes of objects to be distributed across processors
    return [[elements[e] for e in np.arange(proc,len(elements),n_proc,dtype=int)] for proc in np.arange(n_proc)]

def assign(targets,available,per_node):
    # Convert glom targets to bool vector
    targets_available = np.ones(targets.shape[0],dtype=int)
    # Compare the requested granules with the available
    targets_available = np.bitwise_and(targets_available,available[targets['index']])
    # Remove from list the unavailable cells
    targets = targets[targets_available.nonzero()]

    if len(targets) > per_node:
        notassigned = targets[:-per_node]
        targets = targets[-per_node+1:]
    else:
        notassigned = np.empty(0)
    available[ targets['index'] ] = 0
    return targets,notassigned,available

def distance(A, B, control):
    """
    Compute all the distances between two sets of points.
    A is an n by d matrix containing the coordinates of n points in a d-dimensional space, and B is an m by d matrix containing the coordinates of m points in a d-dimensional space: notice that the dimensionality of the space must be the same.
    control can be 'cityblock' or 'sqeuclidean'.
    """
    n = A.shape[0]
    m = B.shape[0]
    d = A.shape[1]
    D = np.zeros((n, m, d))
    for i in range(d):
        if control == 'cityblock':
            D[:,:,i] = np.abs(A[:,i].reshape(n,1) - B[:,i].reshape(1,m))
        elif control == 'sqeuclidean':
            D[:,:,i] = np.square(A[:,i].reshape(n,1) - B[:,i].reshape(1,m))
    return D

def extract_addresses(dataset, row):
    """
    Take a dataset (that is, a numpy array), select the row-th row, strip the zero values, substract 1 and return the result as a list. This is useful to read rows of addresses from the connection matrices in the hdf5 files.
    """
    return (dataset[row][dataset[row].nonzero()] - 1).tolist()

def feedforward_filter(gloms, file_handle, aux_golgis=[],netsize = 0, origin = []):
    """
    Consider an hdf5 description of a network. Fix a set of glomeruli (gloms). Decide which granules and which Golgi cells are excited by this set (for the Golgi cells, we consider just the excitation through the basolateral dendrites). For each granule, calculate the number of excitatory inputs from gloms and the number of inhibitory inputs from the set of excited Golgi cells.
    """
    activated_granules_lil = [extract_addresses(file_handle['/connections/glom_grc_inverted'], gl) for gl in gloms]
    granules = list(set([item for sublist in activated_granules_lil for item in sublist]))

    # activated_golgis = [go for go in range(file_handle['/positions/golgicells'].shape[0]) if any([gl in extract_addresses(file_handle['/connections/glom_goc-bl'], go) for gl in gloms])] commented cause too slow!!!
    activated_golgis = []
    for go in range(file_handle['/positions/golgicells'].shape[0]):
        gls = extract_addresses(file_handle['/connections/glom_goc-bl'], go)
        if any([gl in gls for gl in gloms]):
            activated_golgis.append(go)
            
    activated_golgis.extend(aux_golgis)
    print "Activated + auxiliary Golgi cells: %d. Unique: %d" % (len(activated_golgis), len(set(activated_golgis)))

    if netsize > 0:
        print 'Filtering for unreal grcs'
        granules_positions = file_handle.get('positions/granules')
        created_grcs = [g_idx for g_idx,g in enumerate(np.abs(np.add(granules_positions,-origin)))
                        if g[0].__lt__(netsize) and g[1].__lt__(netsize) and g[2].__lt__(netsize)]
        granules = [gr for gr in granules if gr in created_grcs]
    
    total_dendrites_by_gr = [len(extract_addresses(file_handle['/connections/glom_grc'], gr)) for gr in granules]
    activating_glomeruli_by_gr = [[gl for gl in extract_addresses(file_handle['/connections/glom_grc'], gr) if gl in gloms] for gr in granules]
    inhibiting_golgis_by_gr = [[] for each in granules]
    for i, gr in enumerate(granules):
        for gl in extract_addresses(file_handle['connections/glom_grc'], gr):
            inhibiting_golgi_through_gl = extract_addresses(file_handle['/connections/goc_glom'], gl)[0] #extract_addresses should always return a single-valued list (each glomerulus is innervated by one and only one golgi cell)
            if inhibiting_golgi_through_gl in activated_golgis and not inhibiting_golgi_through_gl in inhibiting_golgis_by_gr[i]:
                inhibiting_golgis_by_gr[i].append(inhibiting_golgi_through_gl)
    return zip(granules, [len(x) for x in activating_glomeruli_by_gr], [len(x) for x in inhibiting_golgis_by_gr], total_dendrites_by_gr)

def hdfwrite(hdf,cell):
    for to_save_name,to_save in cell[1][1].record.iteritems():
        # if to_save[0]=='spk':
            # print to_save[0],to_save[1].printf()
        var_write_hdf5(hdf[cell[1][1].whatami+'/'+str(cell[0])+'/'+to_save_name],to_save)

def var_write_hdf5(hdf,var):
    # Store orginal size of hdf5 vector
    hdf_shape =  hdf.shape
    # Resize the hdf5 vector to allocate space for new datapoints
    hdf.resize((hdf_shape[0]+var.size(),1))
    # Store new data from recorded vector in RAM
    aa = np.array(var)
    # aa = np.float16(np.array(var))
    # Somehow remove the last point of the var which is always zero
    aa.resize(hdf.shape[0]-(hdf_shape[0]-1),1)
    # Write aa in the last points of the hdf5 vectro
    hdf[hdf_shape[0]-1:hdf.shape[0]] = aa
    # Empty the vector in RAM
    var.resize(0)

def record_flush(hdf,cell):
    for to_save_name,to_save in cell[1][1].record.iteritems():
        if 'spk' in to_save_name:
            # Save spikes anyway
            var_write_hdf5(hdf[cell[1][1].whatami+'/'+str(cell[0])+'/'+to_save_name],to_save)
        else:
            var_flush(to_save)

def var_flush(var):
    # Empty the vector in RAM
    var.resize(0)

def cell_exists(indexes_created_cells,list_to_check):
    # Out of the list_to_check return only the indexes present in indexes
    # li = [int(l) for l in list_to_check]
    # print li, len(indexes_created_cells)
    # indexes = []
    # for lc in list_to_check:
    #     if lc < len(indexes_created_cells):
    #         if indexes_created_cells[int(lc)]:
    #             indexes.append(lc)
    #     else:
    #         print "len indexes ", lc, len(indexes_created_cells)
    # for lc in list_to_check:
    #     if lc >= len(indexes_created_cells)-1:
    #         print "len indexes ", lc, len(indexes_created_cells)
    indexes = [lc for lc in list_to_check if indexes_created_cells[int(lc)]==1]

    # print "indexes ", indexes

    return indexes

def Pcoupling(distance):
    """ Function from Ververke 2010 found in legent of Fig. 7. """
    return -1745 + 1836/(1 + np.exp((distance*1e6 - 267)/39))

def euclidean_distance(A,B_list):
    return [np.sqrt(np.sum(np.square(A-b))) for b in B_list]

def diagonalley_gapj(gapj_matrix,positions,cells_to_create,method='Pcoupling'):
    """
    Build a square matrix to represent gap junction coupling in binary format
    gapj_matrix: connections matrix from structure, contains 2 matrices of nrow = num gocs ncol=max number of gpaj for one goc
    first matrix is indexes of goc+1, 0 if not connection exists
    seconf matrix is amount of dend-dend overlap in um3 
    dend_dend_overlap: works considering only the dendritic overlap, eveni a minimal overlap is sufficient to have a gaj coupling
    Pcoupling: the probability of gapj coupling is calculate based on intersomatic distance using Pcoupling function
    the probability of connection is written in the matrix element.
    The output matrix should be simmetrical with respect to the main diagonal
    """
    if method == 'dend_dend_overlap':
        m = np.zeros((len(gapj_matrix),len(gapj_matrix)),dtype=int)
        for idx,goc in enumerate(gapj_matrix):
            for target in goc:
                m[idx,int(target[0])-1]=1 
    if method == 'Pcoupling': # Described by VervaekeNeuron2010 
        m = np.zeros((len(gapj_matrix),len(gapj_matrix)),dtype=float)
        for idx,goc in enumerate(gapj_matrix):
            if cells_to_create[idx]:
                # print positions[idx],[positions[g[0]-1] for g in goc if g[0]>0]
                d = euclidean_distance(np.array(positions[idx]),[positions[g[0]-1] for g in goc if g[0]>0])
                # print "dist ",d
                for target_idx,target in enumerate([g for g in goc if g[0]>0]):
                    # print "dist ", (d[target_idx]), int(Pcoupling(d[target_idx]))
                    # print target_idx
                    m[idx,int(target[0])-1]= max(0,Pcoupling(d[target_idx]))/100
    return m

# def prune_gapj_distance(gapj_matrix,golgis_positions,distance=70e-6):
#     M_distance = distance(np.array(golgis_positions), np.array(golgis_positions), 'sqeuclidean')
#     for goc_idx,g in enumerate(gapj_matrix):
#         if M_distance>distance:
#             nnz = g.nonzero()
#             for r in rnd.sample(nnz[0],sum(g)-ngapj):
#                 g[r] = 0
#     return gapj_matrix

def prune_gapj(gapj_matrix):
    """
    Prune the gapj connection matrix based on probilities wirtten in the elements.
    Using rnd.unifform distrubution convert probabilities to binary choice element by element.
    Ensure to return a matrix with zeros along the main diagonal.
    Ensure to return a matrix with lower triangle = upper triangle.
    """
    for g_idx,g in enumerate(gapj_matrix):
        # print "goc ngapj1 = ", sum(g)
        for c_idx,c in enumerate(g):
            # print gapj_matrix[g_idx,c_idx]
            # print rnd.uniform(0,1),gapj_matrix[g_idx,c_idx]
            if rnd.uniform(0,1) < gapj_matrix[g_idx,c_idx]:
                gapj_matrix[g_idx,c_idx] = 1
            else:
                gapj_matrix[g_idx,c_idx] = 0
           
    # Set the upper triangle of the output array to be a copy of the lower triangle
    # so that the array is simmetrical with respect to the main diangonal which containes only zeros
    gapj_matrix = np.tril(gapj_matrix,-1)
    return gapj_matrix + np.transpose(gapj_matrix)
                
    # Return only the lower triangle
    # return np.tril(gapj_matrix,-1)

def random_transpose_gapj(gapj_matrix,ctc,max_syn_n=0):
    """
    Starting from the gapj coupling matrix builds a connection matrix for goc->goc inh syns
    Makes bidirectional syns with a 0.5 probability which is NOT realistic see Hull 2012 pg. 152
    """
    # presevre origina matrix
    tmp = np.zeros(np.shape(gapj_matrix))
    # Limit to max_syn_n
    syn_matrix = np.zeros(np.shape(gapj_matrix))
    for g_idx,g in enumerate(np.tril(gapj_matrix)):
        selected = np.nonzero(g)[0]
        if len(selected) > 0 :
            # print "Selected",selected[np.random.randint(0,len(selected),10)]
            syn_matrix[g_idx,selected[np.random.randint(0,len(selected),20)]] = 1
    # print len(np.nonzero(syn_matrix)[0])
    # for g in syn_matrix:
    #     print len(np.nonzero(g)[0])

    # itarate over elements
    for g_idx,g in enumerate(syn_matrix):
        for c_idx,c in enumerate(g):
            # print gapj_matrix[g_idx,c_idx]
            # print rnd.uniform(0,1),gapj_matrix[g_idx,c_idx]
            # if gapj exists make also syn connection
            if c == 1:
                # random choose direction
                if rnd.uniform(0,1) < 0.5:
                    tmp[g_idx,c_idx] = 1
                    # make bidirectional synapses with 50 % chance
                    tmp[c_idx,g_idx] = rnd.uniform(0,1) < 0.5
                else:
                    tmp[g_idx,c_idx] = rnd.uniform(0,1) < 0.5
                    tmp[c_idx,g_idx] = 1
    
    # print "ones", len(np.nonzero(tmp)[0])
    
    print "ones", len(np.nonzero(tmp)[0])
    [ctc_x,ctc_y] = np.meshgrid(ctc,ctc)
    tmp = np.logical_and(tmp,ctc_x)
    # tmp = np.logical_and(tmp,ctc_y)
    print "ones", len(np.nonzero(tmp)[0])

    # for g_idx,g in enumerate(tmp):
    #     # print len(g), len(ctc)
    #     tmp[g_idx] = np.logical_and(g,ctc)
        # if ctc[g_idx]:
        #     for c_idx, c in enumerate(g):
        #         if c and ctc[c_idx]:
        #             c = 0
        #         else:
        #             c = 0
        # else:
        #     g = np.zeros(np.shape(g))
    # for g in np.transpose(tmp):
    #     # g = np.logical_and(g,ctc)
    #     for c_idx, c in enumerate(g):
    #         if c and ctc[c_idx]:
    #             c = 1
    #         else:
    #             c = 0
    # print len(np.nonzero(g)[0])
    # print "ones", len(np.nonzero(tmp)[0])


    return tmp


def gapj_g(target_idx,source_idx,golgis_positions):
    """
    Converts the distance between two cells into their gapj coupling and then to gapj conductance (nS) according to VervaekeNeuron2010
    """
    d = np.sqrt(np.sum(np.square(golgis_positions[target_idx] - golgis_positions[source_idx]))) # meters
    CC = -2.3 + 29.7 * np.exp( -d /  (70.4e-6))
    gapjpS = (0.576 * np.exp(CC / 12.4) + 0.000590 * np.exp (CC / 2.79) - 0.564) * 1e2 # pS
    if gapjpS > 0 :
        return [gapjpS,d,CC]
    else:
        return [0,1e9,0]

def barrier(pc,comm=None):
    if comm is not None:
        comm.barrier()
    return pc.barrier()

def dump_stdout(f,txt):
    f.write(txt)
    f.flush()

# Return the array of glomeruli belonging to a certain cluster/mossy starting from connection/glom_branching in structure file
def get_gloms_of_mossy(idx, glom_branching):
    glom_of_mossy = []
    for i, this_glom in enumerate(glom_branching):
        if this_glom[4] == idx:
            glom_of_mossy.append(this_glom)

    return np.array(glom_of_mossy)

def get_ex_inh_balance(network_filename, center_glomeruli, origin, dump_filename='', aux_spots_offsets=[], plot_mi=True, movie=False):
    """aux_spots_offsets is a list of three-dimensional numpy arrays.
    If movie is True, use mencoder to obtain a movie from the pngs. The command
    mencoder mf://*.png -mf w=1280:h=1024:fps=25:type=png -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:dia=4:trell:cbp:qprd -oac copy -o output.avi
    works well for me."""
    #aux_spots_offsets = [np.array([0, -100.e-6, 0]), np.array([0, 100.e-6, 0])]
    # load data
    if plot_mi:
        print 'Loading data'
        # mi_file = h5py.File('mi_qe_2inhspikes_gauss200-20head_poisson100tail.hdf5', 'r')
        mi_file = h5py.File('mi_qe_2inhspikes_uniform.hdf5', 'r')
        mi = np.array(mi_file['mi'])
        mi_file.close()
    file_handle = h5py.File(network_filename, 'r')
    granules_pos = np.array(file_handle['positions/granules'])*1e6
    # Shift GrCs in new system of reference origin
    granules_pos = granules_pos - origin*1e6
    glomeruli_pos = np.array(file_handle['positions/glomeruli'])*1e6
    glomeruli_pos = glomeruli_pos - origin*1e6

    # Activated glomeruli
    
    # print center_glomeruli

    #Activated Golgi's
    aux_golgis = [go for glomeruli in center_glomeruli for go in activated_golgis(glomeruli, file_handle)]
    # print aux_golgis,len(aux_golgis)
    file_handle.close()

    # do the actual mapping
    print 'Mapping excitatory/inhibitory structure'
    all_granules, center_granules = granules_by_gloms(network_filename, gloms[0], center_glomeruli, aux_golgis)
    granules = center_granules
    subset_keys = [(exc, inh, total_dend) for total_dend in range(1,6) for exc in range(1,6) for inh in range(6)]
    subsets = dict.fromkeys(subset_keys)
    for exc in range(1,6):
        for inh in range(6):
            for total_dend in range(1,6):
                subsets[exc, inh, total_dend] = [gr for gr in granules if gr[1]==exc and gr[2]==inh and gr[3]==total_dend]

    # plot
    print 'Plotting'
    fig = Figure(figsize=(15, 13))
    #fig=plt.figure()
    ax = Axes3D(fig) 
    #ax = fig.add_subplot(111, projection='3d')
    colors = ['y', 'g', 'b', 'r']
    markers = ['o', '^', 's', 'p', 'h']
    # proxy artists (legend workaround)
    pas = []
    plotnames = []
    active_gr_indexes = [x[0] for x in granules]
    if plot_mi:
        mi_values = np.zeros(shape=granules_pos.shape[0])
        mi_values.fill(np.NaN)
        # delay to first spike
        dfs = np.array([[11.61, 19.23, 36.13, np.Inf, np.Inf], [6.67, 7.81, 10.97, 18.29, 27.70], [4.88, 5.01, 5.20, 5.78, 7.66], [4.01, 4.05, 4.12, 4.25, 4.35]])
        velocity = 1./dfs
        vel_values = np.zeros(shape=granules_pos.shape[0])
        vel_values.fill(np.NaN)
        nspikes = np.array([[2.06, 1., 0.20, 0., 0.], [5.33, 4.31, 3.19, 1.8, 0.71], [8.52, 7.53, 6.47, 5.31, 4.08], [11.68, 10.61, 9.49, 8.33, 7.16]])
        nspike_values = np.zeros(shape=granules_pos.shape[0])

    # Store the Exc/Inh balance
    exc_inh_balance = np.zeros((6,6))
    total_number_of_grcs = len(all_granules)
    # print all_granules
    grcs_activated_by_center = float(np.sum([len(l[1]) for l in subsets.items()]))
    for ((exc, inh, total_dend), ss) in [x for x in subsets.items() if len(x[1]) > 0]:
        print 'exc=%d, inh=%d, total_dend=%d : %.1f%%' % (exc, inh, total_dend, 100*float(len(ss))/total_number_of_grcs)
        exc_inh_balance[exc,inh] = exc_inh_balance[exc,inh] + float(len(ss))
        # as a first approximation, we treat the cells having 5 dendrites as if they had just 4 of them.
        if exc == 5: exc = 4
        if inh == 5: inh = 4
        c = colors[exc-1]
        m = markers[inh]
        gr_indexes = [x[0] for x in ss]
        xs = granules_pos[gr_indexes, 0]
        ys = granules_pos[gr_indexes, 1]
        zs = granules_pos[gr_indexes, 2]

        if plot_mi:
            mi_values[gr_indexes] = mi[exc-1, inh]
            vel_values[gr_indexes] = velocity[exc-1, inh]
            nspike_values[gr_indexes] = nspikes[exc-1, inh]

        if 'exc=%d, inh=%d' % (exc, inh) not in plotnames:
            ax.scatter(xs, ys, zs, c=c, marker=m, label='exc=%d, inh=%d' % (exc, inh))
            pas.append(Line2D(xdata=[0], ydata=[0], linestyle='None', marker=m, markerfacecolor=c))
            plotnames.append('exc=%d, inh=%d' % (exc, inh))
        else:
            ax.scatter(xs, ys, zs, c=c, marker=m)
   
    # plot mi
    if plot_mi:
        mi_fig = Figure(figsize=(18, 13))
        mi_ax = mi_fig.add_subplot(111, projection='3d')
        mi_scatterplot = mi_ax.scatter(granules_pos[active_gr_indexes,0], granules_pos[active_gr_indexes,1], granules_pos[active_gr_indexes,2], c=mi_values[active_gr_indexes], marker='o')

    # radial plot
    r_values = np.sqrt(np.square(granules_pos[active_gr_indexes] - spot_center*1e6).sum(axis=1))
    granule_number_histogram = np.histogram(r_values, bins=(r_values.max()-r_values.min()))
    granules_belonging_bins = np.searchsorted(granule_number_histogram[1], r_values) - 1
    averaging_weights = np.array([1./granule_number_histogram[0][k] for k in granules_belonging_bins])
    e_i_values = np.array([(gr[1]+1)/(gr[2]+1) for gr in granules])

    radial_fig = Figure(figsize=(10,8))
    radial_ax = Axes3D(fig) 
    # radial_ax = radial_fig.add_subplot(111, projection='3d')
    
    if plot_mi:
        radial_mi = np.histogram(r_values, bins=(r_values.max()-r_values.min()), normed=True, weights=mi_values[active_gr_indexes]*averaging_weights)
        radial_e_i = np.histogram(r_values, bins=(r_values.max()-r_values.min()), normed=True, weights=e_i_values*averaging_weights)
        radial_vel = np.histogram(r_values, bins=(r_values.max()-r_values.min()), normed=True, weights=vel_values[active_gr_indexes]*averaging_weights)
        radial_nspike = np.histogram(r_values, bins=(r_values.max()-r_values.min()), normed=True, weights=nspike_values[active_gr_indexes]*averaging_weights)

    radial_pas = []
    colors = ['r', 'g', 'b', 'y']
    labels = ['Mutual information', 'E/I balance', 'Response velocity', 'Spike number']

    if plot_mi:
        for k,hist in enumerate([radial_mi, radial_e_i, radial_vel, radial_nspike]):
            radial_ax.bar(radial_mi[1][:-1], hist[0], zs=k, zdir='y', width=1, color=colors[k], alpha=0.8, label=labels[k])
            radial_pas.append(Rectangle((0, 0), 1, 1, fc=colors[k], alpha=0.8))


    # legends etc
    ax.legend(pas, plotnames, numpoints=1)
    radial_ax.legend(radial_pas, labels)
    if plot_mi:
        mi_cbar = mi_fig.colorbar(mi_scatterplot)
        mi_cbar.set_label('MI (bits)')
    ax.set_xlabel('Transverse axis ($\mu m$)')
    ax.set_ylabel('Sagittal axis ($\mu m$)')
    ax.set_zlabel('Radial axis ($\mu m$)')
    if plot_mi:
        mi_ax.set_xlabel('Transverse axis ($\mu m$)')
        mi_ax.set_ylabel('Sagittal axis ($\mu m$)')
        mi_ax.set_zlabel('Radial axis ($\mu m$)')
    radial_ax.set_xlabel('Distance from spot center ($\mu m$)')

    fig.suptitle('Excitatory/inhibitory pattern')#, %d active mossy fibers' % len(gloms))
    if plot_mi:
        mi_fig.suptitle('Single cell MI pattern - bursting prior')

    for a in radial_ax.w_yaxis.get_ticklines() + radial_ax.w_yaxis.get_ticklabels() + radial_ax.w_zaxis.get_ticklines() + radial_ax.w_zaxis.get_ticklabels():
        a.set_visible(False)

    
    if plot_mi:
        conn_canvas = FigureCanvas(fig)
        mi_canvas = FigureCanvas(mi_fig)
        radial_canvas = FigureCanvas(radial_fig)
        print('%d active mossy fibers' % len(gloms))
        if movie:
            for angle in range(0, 360):
                ax.view_init(30, angle)
                if plot_mi:
                    mi_ax.view_init(30, angle)
                    conn_canvas.print_figure('mov/excitatory_pattern_uniform_%03d.png' % angle, dpi=100)
                    if plot_mi:
                        mi_canvas.print_figure('mov/mi_pattern_uniform_%03d.png' % angle, dpi=100)
            else:
                radial_canvas.print_figure('radial_plot.png', dpi=200)
                conn_canvas.print_figure('excitatory_pattern_uniform.png', dpi=200)
                if plot_mi:
                    mi_canvas.print_figure('mi_pattern_uniform.png', dpi=200)

    # Calculate the toal number of grcs in the spherical volume containing all the activated grcs
    print "Max Glom distance from Stim center = %3.2f" % np.max(hcluster.distance.cdist(
            np.array([0,0,0]).reshape((1,3)), glomeruli_pos[[x for x in center_glomeruli]], 'euclidean'))
    max_grc_dist_from_center =  np.max(hcluster.distance.cdist(np.array([0,0,0]).reshape((1,3)), granules_pos[[x[0] for x in center_granules]], 'euclidean'))
    grcs_in_field = np.nonzero(hcluster.distance.cdist(np.array([0,0,0]).reshape((1,3)), granules_pos, 'sqeuclidean').__le__(np.power(max_grc_dist_from_center,2)))[1]
    print "Max grc distance from Stim center = %3.2f um" % max_grc_dist_from_center
    print "Number of grcs in stim sphere = %5.0f" % grcs_in_field.shape
    print "Number of grcs activated by glomeruli = %5.0f" % grcs_activated_by_center

    return exc_inh_balance,subsets,total_number_of_grcs, grcs_activated_by_center

def spgen(rate, totalTime, n, dt=1):
    ''' This function generates spike times following poisson distribution;
    rate = mean firing rate; totalTime = time interval (0:totalTime), n = number of 'neurons'
    dt = time step '''
    import random
    import numpy as np

    # isi = np.random.exponential(1000./rate, totalTime / rate * 1.5)
    # return np.cumsum(isi)
    
    nspikes = int(rate * (totalTime / 1000.0))
    neurons = []
    np.random.seed(1234567)
    for i in range(n):
       spikeTimes = []
       # for t in np.arange(1,totalTime+1,dt):
       #     if rate * dt / 1000.0 >= random.random():
       #         spikeTimes.append(t)
       # neurons.append(np.array(spikeTimes))
       # isi = np.random.exponential(rate, totalTime * 1e-3 * rate)
       spikeTimes = np.sort(np.random.uniform(0,totalTime,nspikes))
       neurons.append(spikeTimes)    
    return neurons

def rep_spikes(start_time, freq, n):
     import numpy as np
     # allocate memory
     vec = np.zeros(n)
     vec[0] = start_time
     for i in range(1,len(vec)):
         vec[i] = round(vec[i-1] + (1000.0 / freq))        
                 
     return vec



def det_oscillation(neurons=100, time=1000, start_time=0, freq=6, burst_freq=100, spikes=1):
    ''' Simple function providing deterministic oscillatory input pattern to
        a network.
        Pars:
        
        neurons = number of neurons; time = total time of simulation, 
        start_time = when the stimulation should begin, freq = stimulation frequency
        burst_freq = frequency of spikes inside bursts, spikes = number fo spikes 
        bursts '''
        
    import numpy as np
    # Define the main spike train
    spk_train = rep_spikes(start_time,burst_freq,spikes)
    length = len(spk_train)
    cells = []
    while spk_train[-1] < time:
        if len(spk_train) == length:
            #print spk_train
            spk_train = np.append(spk_train,spk_train + (1000 / freq))
        else:
            #print spk_train
            spk_train = np.append(spk_train,spk_train[len(spk_train)-length:len(spk_train)] + (1000 / freq))
    #finally create the normal list
    # Default: add some noise (sd = 5 ms)
    for i in range(neurons):
	jitter = [np.random.normal(spk, 2) for spk in spk_train]
	jitter = np.array(jitter)
        cells.append(jitter[jitter <= time])
        
    return cells
        
    
    





import random as rnd
import numpy as np

# Directory where the user want to save simulation results (full path)
save_dir = '/mnt/scratch2/production/sim_dir_1575646927_336296971/weasel'

seed = 12345
rnd.seed(seed)


simulation_temperature = 37



# Set size of simulated network
# For many of our simulations, we used 100e-6 for grc and 200e-6 for goc
netsize = {}
netsize['grc'] = 100e-6
netsize['grc_struct_type'] = 'cube'
netsize['goc'] = 200e-6
netsize['stl'] =  netsize['goc'] + 400e-6
netsize['glom'] = netsize['goc'] + 800e-6

cells_on = {}
cells_on['mossy'] = 0
cells_on['grc'] = 1
if not cells_on['grc']:
    netsize['grc'] = 0
cells_on['goc'] = 1

##################################################################################################################
## IMPORTANT: it's possible to include a simple model of Stellate cells inhibiting Golgi cells;
# this has never been done for current simulations for various reasons; BTW, if the user wants to
# perform some test, simpy change cells_on['stl'] to 1.
# Other parameters for stellate cells connectivity can be set.
### NOTE: The Stellate cells model is extremely simplified and we did not perfom specifc test with it
# So, if the user performs any network simulation with the Stellate model, errors and / or wrong results may occur

cells_on['stl'] = 0

##################################################################################################################
cells_on['pf'] = 1 # or cells_on['grc'] or cells_on['goc'] or cells_on['stl']
cells_on['glom'] = 1 # cells_on['grc'] or cells_on['goc']
cells_on['stlgap'] = 0
cells_on['stl2stl'] = 0
cells_on['gocgap'] = 1

cells_on['mossy2glom'] = 1
cells_on['glom2grc'] = cells_on['grc'] and cells_on['glom']

# If the user wants to simulate Gabazine  (i.e., inhibition OFF),
# set cells_on['goc2grc'] = 0 and cells_on['block_grc_tonic_gaba'] = 1 (see below)
cells_on['goc2grc'] = 1
cells_on['goc2grc_gmax_factor'] = 1
cells_on['glom2goc'] = 1
cells_on['grc2goc'] = 1
cells_on['grcaa2goc'] = 1

cells_on['goc2goc'] = 1
cells_on['stl2goc'] = 0
cells_on['pf2stl'] = 0
cells_on['grc2stl'] = 0
cells_on['pf2goc'] = 1

cells_on['mossy2glom'] = cells_on['mossy2glom'] and cells_on['mossy'] and cells_on['glom']
cells_on['glom2goc'] = cells_on['glom2goc'] and cells_on['goc'] and cells_on['glom']
cells_on['grc2goc'] = cells_on['grc2goc'] and cells_on['grc'] and cells_on['goc']
cells_on['grcaa2goc'] = cells_on['grcaa2goc'] and cells_on['grc'] and cells_on['goc']
cells_on['goc2grc'] = cells_on['goc2grc'] and cells_on['grc'] and cells_on['goc']
cells_on['gocgap'] = cells_on['gocgap'] and cells_on['goc']
cells_on['stlgap'] = cells_on['stlgap'] and cells_on['stl']
cells_on['stl2stl'] = cells_on['stl2stl'] and cells_on['stl']
cells_on['pf2stl'] = cells_on['pf2stl'] and cells_on['stl'] and (cells_on['pf'] or cells_on['grc'] )
cells_on['grc2stl'] = cells_on['grc2stl'] and cells_on['stl'] and (cells_on['pf'] or cells_on['grc'] )
cells_on['pf2goc'] = cells_on['pf2goc'] and cells_on['goc'] and (cells_on['pf'] or cells_on['grc'] )

cells_on['goc2goc'] = cells_on['goc2goc'] and cells_on['goc']

# Stochastic release of glutammate at MF->GrC synapses
cells_on['glom2grc_nrel'] = 0
# Switch off individual channels in templates
# set to 1 for inhibition OFF simulation
cells_on['block_grc_tonic_gaba'] = 0

cells_on['rec_all_goc'] = 0
cells_on['rec_all_grc'] = 1
cells_on['rec_all_stl'] = 0
cells_on['rec_all_glom2goc'] = 0
cells_on['rec_all_grcaa2goc'] = 0
cells_on['rec_all_grc2goc'] = 0
cells_on['rec_all_pf2goc'] = 0
cells_on['rec_all_goc2goc'] = 0

# Record data only in this time window
cells_on['rec_start'] = 120
cells_on['rec_end'] = 480



ncores = 60 # 2048 #1024

syn_var = 0.2

gmax_gap = 50.


pf_collapse = 1 # simulate all pf affrent to one cell as a single Netstim

# Simulate all stl affrent to one GOC as a single Netstim
stl_goc_syn_overlap_threshold = 10e5 # 14e3 # um3  max is 1.943.999


stl_conn_mask_type = 'volume_probability' # the synapse is created using the normalized volumentric intersection STL-axon GOC-apical dendrite as probability of connection

stl2goc_max_syn = 160 # set the max number of STL synapses made on one GoC and select those at random from all possible connections chosen by the method stl_conn_mask_type


stl_collapse = 1 # all connections are converged to a single synapse

pf_background = 0.0 # from test_syn.py stellate or golgi test_fr.py
pf_conduction_speed = 0.4 # m/s or mm/ms as all distances are expressed in m (SI)

mf_background = 0 # OLD -- DON'T CHANGE THIS VALUE

# For background acivity over glomeruli, set new_background to 1
new_background = 0
if new_background:
    rate = 4
    totalTime = 480
    tau = 0.01
    all_gloms = 1



stl_background = 0
plot_on = 0
save_on = 1
simtime = 480 # ms
simstep = 60 # ms
sim_dt = 0.025 # ms
save_dt = 0.1

run_sim = 1

stl_type = "C"
pfs_stl_max =  100

save_plot = 0

###### SET this to 0 to recalculate only MF & glom in the preprocess ########
###### if set to 1 preprocess recalculates all the connections    ########
recalc_all = 1

# We set here the origin of the GL to be in the middle of the GL this
# is done because in the structure files the orgin of the GL is set on
# the top-center of the GL
origin = np.array([0,0,-75])*1e-6

# STIMULUS DEFINITION
mossy_stimulation = 0
cells_on['mossy2glom'] = cells_on['mossy2glom'] and mossy_stimulation

spot_stimulation = 1
# The spot center are set in the system of reference of the GL in the structure (origin in the top-center of GL)
spot_centers =  [np.array([0, 0, -75])*1e-6]
n_spots = len(spot_centers)
radius = 27.7e-6 # mu

# Here we can choose among:
# gloms_in_simt_center as a probability i.e. max < 1
# gloms_in_simt_center as a number i.e. max > 1
# gloms_in_simt_center as all glomeruli i.e. = 1
# in this config we assume that we never want to have a single glom selected
gloms_in_simt_center = 1

# Input params setting:
# To reproduce a simple train @50Hz with 10 spikes,
# ignore inter_freq, set intra_freq to 50.0 and rep_num to 1

# Set to 1 to perform a simulation with release probability updated after
# plasticity protocol (for glom-grc synapse only )
plast = 0


inter_freq = 25.0
intra_freq = 50.0
rep_num = 1
spk_num = 10
start = 180.0
end = start + ((1000. / intra_freq)*spk_num)
step = (end - start) / spk_num

# This creates a single burst
a = np.arange(start, end, step)

# Now create the whole burst train
var = np.arange(start, end, step)
interval = 1000. / inter_freq
count = 1
while count < rep_num:
    a = np.append(a,var+(interval*count))
    count += 1


stim = 1

# This makes the input null
#a = np.array([])

times = np.zeros([30,len(a)])
times[0,:] = a
for i in range(1,times.shape[0]):
    times[i,:] = times[i-1,:]+100

quit_all = 1
if recalc_all:
    dumpdir = 'weasel_setup_' + str(ncores)
else:
    sourcedir = 'weasel_setup_source_' + str(ncores)
    dumpdir = 'weasel_setup_' + str(ncores)

# print "export setup_dir=%s"%dumpdir

# Set the correct structure file
structure_dir = './'
print "export structure_dir='%s' "%structure_dir,

structure_file = 'network_structure_file.hdf5'

print "export structure_file='%s'"%structure_file

import h5py
import numpy as np
import sys
import os
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import scipy.io as io

def firing_rate(files,cell_type=''):

    spikes = {}
    nspikes = {}
    spikes_all = {}

    file = h5py.File(files[0],'r')
    for cell in file.items():
        if cell[0] != 'stimulus' and cell[0] != 'burst' and cell[0] != 'seed':
            spikes[cell[0]] = []
            spikes_all[cell[0]] = []
    file.close()

    for cnt,f in enumerate(files):
        print '%d'%cnt+'    '
        if np.mod(cnt,10)==0:
            print ' '
        file = h5py.File(f,'r')
        for cell in file.items():
            if cell_type != '':
                if cell[0] == cell_type: #cell[0]!='stimulus' and cell[0]!='burst' and cell[0]!='seed':
                    # for k in cell[1].items():
                    #     for typ in k[1].items():
                    #         if typ[0] == 'spk':
                    #             print [s[0] for s in np.array(typ[1]) ]
                    # print cell[1].keys()
                    # for k in cell[1].items():
                    #     print "k",k
                    #     for typ in k[1].items():
                    #         print "typ",typ[0]
                    #         if typ[0] == 'spk':
                    #             print np.any(np.array(typ[1]))
                    #             #print np.array(typ[1])[np.nonzero(np.array(typ[1]))[0]]
                    spikes[cell[0]].extend([[int(k[0]),[s[0] for s in np.array(typ[1])[np.nonzero(np.array(typ[1]))[0]] if s[0] > 100]] for k in cell[1].items() for typ in k[1].items() if typ[0] == 'spk' and np.any(np.array(typ[1])) ])
                    # nspikes[cell[0]].extend([[int(k[0]),[s[0] for s in np.array(typ[1])[0:-1] if s[0] > 100]] for k in cell[1].items() for typ in k[1].items() if typ[0] == 'spk'])
            else:
                if cell[0]!='early' and cell[0]!='late' and cell[0]!='burst' and cell[0]!='seed':
                    # print cell
                    spikes[cell[0]].extend([[int(k[0]),[s[0] for s in np.array(typ[1])[0:-1] if s[0] > 100]] for k in cell[1].items() for typ in k[1].items() if typ[0] == 'spk'])
        file.close()
    print ' '

    ordered_spk =  {}

    f = h5py.File(sys.argv[3],'r')
    if 'grc' in cell_type:
        gp = np.array(f.get('positions/granules'))
    elif 'glom' in cell_type:
        gp = np.array(f.get('positions/glomeruli'))
    elif 'goc' in cell_type:
        gp = np.array(f.get('positions/golgicells'))
    elif 'stl' in cell_type:
        gp = np.array(f.get('positions//MLInterneurons'))
    else:
        print "Cell type WRONG!!!"

    for cell_type_n,cell_spk in spikes.iteritems():
        if cell_type_n == cell_type:
            dtype = [('index',int),('xpos',float),('ypos',float),('zpos',float),('time',float)]
            #print cell_type_n
            # for cell_spks in cell_spk:
            #     print cell_spks
            #     for spk in cell_spks[1]:
            #         ordered_spk.append((cell_spks[0],gp[cell_spks[0]][0],gp[cell_spks[0]][1],spk))
            ordered_spk[cell_type_n] = np.array([(cell_spks[0],gp[cell_spks[0]][0]*1e6,gp[cell_spks[0]][1]*1e6,gp[cell_spks[0]][2]*1e6,spk) for cell_spks in cell_spk for spk in cell_spks[1]],dtype=dtype)

                    # np.array(            ordered_spk     ,dtype=dtype)
        # for cell_spks in cell_spk:
        #     print cell_spks
    print ordered_spk[cell_type]
    ordered_spk[cell_type] = np.sort(ordered_spk[cell_type], order='time')

    # for g in ordered_spk[cell_type]:
    #     print g
# [0][0],g[0][1],g[0][2],g[0][3]
    # ordered_spk = ordered_spk[cell_type]
    o_s = {cell_type:np.array([[g[0],g[1],g[2],g[3],g[4]] for g in ordered_spk[cell_type]])}
    
    io.savemat(sys.argv[1] + '/ord_'+cell_type+'.mat',o_s)


def data_file_filter(x): 
    if 'net2' in x: 
        return(x)

filenames = filter(data_file_filter,os.listdir(sys.argv[1]))
print filenames
files = [sys.argv[1] + '/' + d  for d in filenames]
# print sys.argv[1],files
# file = h5py.File(files[0],'r')
# print file.keys()
# file.close()

cell_type = sys.argv[2]
print cell_type
firing_rate(files,cell_type=cell_type)


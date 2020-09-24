# -*- coding: utf-8 -*-
# -*- coding: utf-8 -*-
import numpy as np

class Glom:
    def __init__(self,position = np.array([0,0,0])):
        self.position = position
    ## def connect2target(self, target):
    ##     nc = h.NetCon(self.soma(1)._ref_v, target, sec = self.soma)
    ##     nc.threshold = 10
    ##     return nc

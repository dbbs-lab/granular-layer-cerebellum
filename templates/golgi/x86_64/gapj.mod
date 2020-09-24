NEURON {
        POINT_PROCESS HalfGap
        ELECTRODE_CURRENT i
        RANGE g, i, vgap
    }
    
    UNITS {
	(nA) 	= (nanoamp)
	(mV) 	= (millivolt)
	(umho)  = (micromho)
	(mM) 	= (milli/liter)
	(pS) 	= (picosiemens)
	PI   	= (pi)(1)
    }

    
PARAMETER {
        g = 0 (pS) : we choose pS for consistency with synaptic models
}

ASSIGNED {
        v (mV)
        vgap (mV)
        i (nA)
}

BREAKPOINT {
        i = (1e-6) * g * (vgap - v)
}
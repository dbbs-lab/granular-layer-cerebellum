TITLE Cerebellum Golgi Cell Model

COMMENT

Author: S. Solinas
Data from: Solinas et al. Frontiers in Cellular Neuroscience 2007
Last revised: April 2006

ENDCOMMENT

NEURON {
	SUFFIX Golgi_lkg
	NONSPECIFIC_CURRENT i
	RANGE Q10_diff,gbar_Q10
	RANGE el, gbar, g, ic, el_boot, boot_time
}

UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
}

PARAMETER {
	v (mV)
	Q10_diff	= 1.5
	gbar = 21e-6 (mho/cm2)
	celsius  (degC)
	el = -55 (mV)
	el_boot = -65 (mV)
	boot_time = 0 (ms)
}

ASSIGNED { 
    i (mA/cm2) 
    gbar_Q10 (mho/cm2)
    ic
    g
}

INITIAL  {
    gbar_Q10 = gbar*(Q10_diff^((celsius-23)/10))
}	

BREAKPOINT { 
    if (t > boot_time) { i = gbar_Q10 * (v - el ) }
    else { i = gbar_Q10 * (v - el_boot ) }
    
    ic = i
    g = gbar_Q10
}

TITLE Cerebellum Golgi Cell Model

COMMENT
        Calcium first order kinetics
   
	Author: A. Fontana
	Last revised: 12.12.98
ENDCOMMENT

NEURON {
        SUFFIX Golgi_CALC
        USEION ca READ ica, cao WRITE cai
	RANGE Q10_diff,beta_Q10, ic
        RANGE d, beta, cai0, ca_pump_i
}

UNITS {
        (mV)    = (millivolt)
        (mA)    = (milliamp)
	(um)    = (micron)
	(molar) = (1/liter)
        (mM)    = (millimolar)
   	F      = (faraday) (coulomb)
}

PARAMETER {
        ica             (mA/cm2)
        celsius    (degC)
        d = .2          (um)
        cao = 2.        (mM)         
        cai0 = 1e-4     (mM)         
        beta = 1.3        (/ms)
	Q10_diff = 1.7
}

ASSIGNED {
	beta_Q10 (mho/cm2)
	ca_pump_i	(mA)
	ic
}
STATE {
	cai (mM)
}

INITIAL {
	beta_Q10 = beta*(Q10_diff^((celsius-23)/10))
        cai = cai0 
}

BREAKPOINT {
       SOLVE conc METHOD cnexp
}

DERIVATIVE conc {    
	:  outward ionic current with valence 2+
	ca_pump_i = 2*beta_Q10*(cai-cai0)
	ic = ca_pump_i
	:  total outward Ca current
	cai' =  -ica/(2*F*d)*(1e4) - beta_Q10*(cai-cai0)
}



COMMENT
Two state kinetic scheme synapse described by rise time tau1,
and decay time constant tau2. The normalized peak condunductance is 1.
Decay time MUST be greater than rise time.

The solution of A->G->bath with rate constants 1/tau1 and 1/tau2 is
 A = a*exp(-t/tau1) and
 G = a*tau2/(tau2-tau1)*(-exp(-t/tau1) + exp(-t/tau2))
	where tau1 < tau2

If tau2-tau1 -> 0 then we have a alphasynapse.
and if tau1 -> 0 then we have just single exponential decay.

The factor is evaluated in the
initial block such that an event of weight 1 generates a
peak conductance of 1.

Because the solution is a sum of exponentials, the
coupled equations can be solved as a pair of independent equations
by the more efficient cnexp method.

ENDCOMMENT

NEURON {
	POINT_PROCESS Golgi_PF_NMDA
	RANGE tau1_Fix, tau2_Fix, e, i
	NONSPECIFIC_CURRENT i

	RANGE gmax,g, gmax_factor,syntype, synfunctype
	GLOBAL total
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
    Q10_diff = 1.1
    Q10_channel = 2.4
    gmax = 100 (pS)
    syntype = 0
    synfunctype = 6
    tau1_Fix =.1 (ms) <1e-9,1e9>
    tau2_Fix = 10 (ms) <1e-9,1e9>
    e=0	(mV)
    v0_block = -20 (mV)
    k_block = 13(mV)
    gmax_factor = 1
}

ASSIGNED {
    v (mV)
    i (nA)
    g (pS)
    factor
    total (uS)
    MgBlock (1)
    Q10
    gbar_Q10
    tau1
    tau2
}

STATE {
	A (uS)
	B (uS)
}

INITIAL {
	LOCAL tp
	total = 0
	
	gbar_Q10 = Q10_diff^((celsius-23)/10)
	Q10 = Q10_channel^((celsius-23)/10)
	tau1 = tau1_Fix / Q10
	tau2 = tau2_Fix / Q10
	
	if (tau1/tau2 > .9999) {
		tau1 = .9999*tau2
	}
	A = 0
	B = 0
	tp = (tau1*tau2)/(tau2 - tau1) * log(tau2/tau1)
	factor = -exp(-tp/tau1) + exp(-tp/tau2)
	factor = 1/factor
}

BREAKPOINT {
	rates(v)
	SOLVE state METHOD cnexp
	g = gmax * (B - A) * MgBlock  * gmax_factor
	i = 1e-6*g*(v - e)
}

DERIVATIVE state {
	A' = -A/tau1
	B' = -B/tau2
}

PROCEDURE rates(v(mV)) {
	: E' necessario includere DEPEND v0_block,k_block per aggiornare le tabelle!
	TABLE MgBlock DEPEND v0_block,k_block FROM -120 TO 30 WITH 150
	MgBlock = 1 / ( 1 + exp ( - ( v - v0_block ) / k_block ) )
}

NET_RECEIVE(weight (uS)) {
	A = A + weight*factor
	B = B + weight*factor
	total = total+weight
}

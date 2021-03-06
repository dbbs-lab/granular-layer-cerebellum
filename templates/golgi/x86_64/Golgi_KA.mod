TITLE Cerebellum Golgi Cell Model

COMMENT
        KA channel
   
        Author:E.D Angelo, T.Nieus, A. Fontana
	Last revised: Egidio 3.12.2003
ENDCOMMENT

NEURON { 
	SUFFIX Golgi_KA
	USEION k READ ek WRITE ik 
	RANGE Q10_diff,Q10_channel,gbar_Q10
	RANGE gbar, ik, g
	:RANGE Aalpha_a, Kalpha_a, V0alpha_a, alpha_a, beta_a, alpha_b
	:RANGE Abeta_a, Kbeta_a, V0beta_a, beta_b
	:RANGE Aalpha_b, Kalpha_b, V0alpha_b
	:RANGE Abeta_b, Kbeta_b, V0beta_b
	:RANGE V0_ainf, K_ainf, V0_binf, K_binf
	RANGE a, b, a_inf, tau_a, b_inf, tau_b, tcorr, ic
} 
 
UNITS { 
	(mA) = (milliamp) 
	(mV) = (millivolt) 
} 
 
PARAMETER { 
	gbar= 0.008 (mho/cm2)
	Aalpha_a = 0.8147 (/ms)
	Kalpha_a = -23.32708 (mV)
	V0alpha_a = -9.17203 (mV)
	Abeta_a = 0.1655 (/ms)
	Kbeta_a = 19.47175 (mV)
	V0beta_a = -18.27914 (mV)

	Aalpha_b = 0.0368 (/ms)
	Kalpha_b = 12.8433 (mV)
	V0alpha_b = -111.33209 (mV)   
	Abeta_b = 0.0345(/ms)
	Kbeta_b = -8.90123 (mV)
	V0beta_b = -49.9537 (mV)

	V0_ainf = -38(mV)
	K_ainf = -17(mV)

	V0_binf = -78.8 (mV)
	K_binf = 8.4 (mV)
	v (mV) 
	ek (mV) 
	celsius (degC)
	Q10_diff	= 1.5
	Q10_channel	= 3
} 

STATE { 
	a
	b 
} 

ASSIGNED { 
	ik (mA/cm2) 
	a_inf 
	b_inf 
	tau_a (ms) 
	tau_b (ms) 
	g (mho/cm2) 
	alpha_a (/ms)
	beta_a (/ms)
	alpha_b (/ms)
	beta_b (/ms)
	tcorr (1)
	gbar_Q10 (mho/cm2)
	ic
} 
 
INITIAL { 
	gbar_Q10 = gbar*(Q10_diff^((celsius-23)/10))
	rate(v) 
	a = a_inf 
	b = b_inf 
} 
 
BREAKPOINT { 
	SOLVE states METHOD cnexp 
	g = gbar_Q10 * a*a*a*b 
	ik = g*(v - ek)
	ic = ik
	alpha_a = alp_a(v)
	beta_a = bet_a(v) 
	alpha_b = alp_b(v)
	beta_b = bet_b(v) 
} 
 
DERIVATIVE states { 
	rate(v) 
	a' =(a_inf - a)/tau_a 
	b' =(b_inf - b)/tau_b 
} 
 
FUNCTION alp_a(v(mV))(/ms) {
	tcorr = Q10_channel^((celsius-25.5(degC))/10(degC))
:	alp_a = tcorr*Aalpha_a*exp(Kalpha_a*(v-V0alpha_a)) 
:	alp_a = -0.04148(/mV-ms)*linoid(v+67.697(mV),-3.857(mV))
	alp_a = tcorr*Aalpha_a*sigm(v-V0alpha_a,Kalpha_a)
} 
 
FUNCTION bet_a(v(mV))(/ms) {
	tcorr = Q10_channel^((celsius-25.5(degC))/10(degC))
:	bet_a = tcorr*Abeta_a*exp(Kbeta_a*(v-V0beta_a)) 
:	bet_a = 0.0359(/mV-ms)*linoid(v+45.878(mV),23.654(mV))
	bet_a = tcorr*Abeta_a/(exp((v-V0beta_a)/Kbeta_a))
} 
 
FUNCTION alp_b(v(mV))(/ms) {
	tcorr = Q10_channel^((celsius-25.5(degC))/10(degC))
:	alp_b = tcorr*Aalpha_b*exp(Kalpha_b*(v-V0alpha_b)) 
:	alp_b = 0.356(/mV-ms)*linoid(v+231.03(mV),17.8(mV))
	alp_b = tcorr*Aalpha_b*sigm(v-V0alpha_b,Kalpha_b)
} 
 
FUNCTION bet_b(v(mV))(/ms) {
	tcorr = Q10_channel^((celsius-25.5(degC))/10(degC))
:	bet_b = tcorr*Abeta_b*exp(Kbeta_b*(v-V0beta_b)) 
:	bet_b = -0.00825(/mV-ms)*linoid(v+43.284(mV),-8.927(mV))
	bet_b = tcorr*Abeta_b*sigm(v-V0beta_b,Kbeta_b)
} 
 
PROCEDURE rate(v (mV)) {LOCAL a_a, b_a, a_b, b_b 
	TABLE a_inf, tau_a, b_inf, tau_b 
	DEPEND Aalpha_a, Kalpha_a, V0alpha_a, 
	       Abeta_a, Kbeta_a, V0beta_a,
               Aalpha_b, Kalpha_b, V0alpha_b,
               Abeta_b, Kbeta_b, V0beta_b, celsius FROM -100 TO 30 WITH 13000 
	a_a = alp_a(v)  
	b_a = bet_a(v) 
	a_b = alp_b(v)  
	b_b = bet_b(v) 
	a_inf = 1/(1+exp((v-V0_ainf)/K_ainf)) 
	tau_a = 1/(a_a + b_a) 
	b_inf = 1/(1+exp((v-V0_binf)/K_binf))
	tau_b = 1/(a_b + b_b) 
: Bardoni Belluzzi data
:	a_inf = 1/(1+exp(-(v+46.7)/19.8))
:	tau_a = 0.41*exp(-(v+43.5)/42.8)+0.167
:	b_inf = 1/(1+exp((v+78.8)/8.4))
:	tau_b = 10.8 + 0.03*v + 1/(57.9*exp(0.127*v)+0.000134*exp(-0.059*v))
}

FUNCTION linoid(x (mV),y (mV)) (mV) {
    if (fabs(x/y) < 1e-6) {
        linoid = y*(1 - x/y/2)
    }else{
	if (fabs(x/y) < 699) { 
	    linoid = x/(exp(x/y) - 1)
	}else{
	    if (x/y > 0){
		linoid = x/(exp(699) - 1)
	    }else{
		linoid = x/(exp(-699) - 1)
	    }
	}
    }
} 

FUNCTION sigm(x (mV),y (mV)) {
    if (fabs(x/y) < 699) { 
	sigm = 1/(exp(x/y) + 1)
    }else{
	if (x/y > 0){
	    sigm = 1/(exp(699) + 1)
	}else{
	    sigm = 1/(exp(-699) + 1)
	}
    }
}

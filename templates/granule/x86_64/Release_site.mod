COMMENT 
Rewritten by S. Solinas from the original scripts by Nieus T. for
presynaptic stochastic release of neurotransmitter.

12 July 2010

A single releasing site. Receives spikes and trasmit spike with probability
dependent on fatigue and recovery.

Actually inspired to the mossy fiber granule cell synapse of 
cerebellum granular layer.

ENDCOMMENT



NEURON	{ 
    ARTIFICIAL_CELL Release_site
    : burst stores the in_burst state, it is set to 1 when event_t == the_first_spike_of_burst and to 0 when event_t == the_firs_spike_after_the_burst
    RANGE tau_1,tau_rec, tau_facil,U,Vm
    RANGE xout,yout,zout,uout
    RANGE RelDep,tsyn,Prelease
}

UNITS {
    PI   = (pi)(1)
}

PARAMETER {
    : Parametri Presinaptici
    tau_1 	= 1 (ms) 	< 1e-9, 1e9 >
    tau_rec 	= 8 (ms) 	< 1e-9, 1e9 > 	: 200 (ms)
    tau_facil 	= 5 (ms) 	< 0, 1e9 > 	: 20
    
    U 		= 0.42 (1) 	< 0, 1 >
    u0 		= 0 (1) 	< 0, 1 >	: se u0=0 al primo colpo y=U
    RelDep		= 0
}

ASSIGNED {
    Prelease
    Vm
    xout	
    yout
    zout
    uout
    x
    y
    z
    u
    xold
    yold
    zold
    uold
    tsyn (ms)
    vc
    toff (ms)
    on
}

INITIAL {
    Prelease=U
    Vm = -90
    
    on = 1
    toff = 1e9
    y = -90
    x=1
    y=0
    z=0	
    u=0
}	

PROCEDURE seed(x) { set_seed(x) }

NET_RECEIVE(w){   
    if( (flag==0) && (on==1) ){  
	:printf(" evento ! tsyn = %g \n",t)
	xold=x
	yold=y
	zold=z
	uold=u
	
	:printf("Exp(%g)rec",-(t - tsyn)/tau_rec)
	z = z*exp(-(t - tsyn)/tau_rec)
	z = z + ( y*(exp(-(t - tsyn)/tau_1) - exp(-(t - tsyn)/tau_rec)) / ((tau_1/tau_rec)-1) )
	y = y*exp(-(t - tsyn)/tau_1)			
	x = 1-y-z
	
	if(tau_facil>0){ 
	    :printf("Exp(%g)facil",-(t - tsyn)/tau_rec)
	    u=u*exp(-(t-tsyn)/tau_facil)
	    u = u+U*(1-u)
	    }else{u=U}			
	    
	    y=y+x*u
	    Prelease=y  								
	    vc=scop_random()
	    if ( vc<y ) { 	
		Vm = 20	
		net_event(t)	
	    } else {
		if(RelDep) {		
		    x=xold
		    y=yold	
		    z=zold
		    u=uold
		} 
	    }
	    xout=x
	    yout=y
	    zout=z
	    uout=u
	    
	    tsyn = t
	}
	
	if (flag == 2) { 
	    Vm = -90 
	}
    }

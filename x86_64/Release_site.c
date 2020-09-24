/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__Release_site
#define _nrn_initial _nrn_initial__Release_site
#define nrn_cur _nrn_cur__Release_site
#define _nrn_current _nrn_current__Release_site
#define nrn_jacob _nrn_jacob__Release_site
#define nrn_state _nrn_state__Release_site
#define _net_receive _net_receive__Release_site 
#define seed seed__Release_site 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define tau_1 _p[0]
#define tau_rec _p[1]
#define tau_facil _p[2]
#define U _p[3]
#define RelDep _p[4]
#define Prelease _p[5]
#define Vm _p[6]
#define xout _p[7]
#define yout _p[8]
#define zout _p[9]
#define uout _p[10]
#define tsyn _p[11]
#define x _p[12]
#define y _p[13]
#define z _p[14]
#define u _p[15]
#define xold _p[16]
#define yold _p[17]
#define zold _p[18]
#define uold _p[19]
#define vc _p[20]
#define toff _p[21]
#define on _p[22]
#define _tsav _p[23]
#define _nd_area  *_ppvar[0]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_seed();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "seed", _hoc_seed,
 0, 0
};
 /* declare global and static user variables */
#define u0 u0_Release_site
 double u0 = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "U", 0, 1,
 "tau_facil", 0, 1e+09,
 "tau_rec", 1e-09, 1e+09,
 "tau_1", 1e-09, 1e+09,
 "u0_Release_site", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "u0_Release_site", "1",
 "tau_1", "ms",
 "tau_rec", "ms",
 "tau_facil", "ms",
 "U", "1",
 "tsyn", "ms",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "u0_Release_site", &u0_Release_site,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Release_site",
 "tau_1",
 "tau_rec",
 "tau_facil",
 "U",
 "RelDep",
 0,
 "Prelease",
 "Vm",
 "xout",
 "yout",
 "zout",
 "uout",
 "tsyn",
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 24, _prop);
 	/*initialize range parameters*/
 	tau_1 = 1;
 	tau_rec = 8;
 	tau_facil = 5;
 	U = 0.42;
 	RelDep = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 24;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Release_site_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 24, 2);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
 add_nrn_artcell(_mechtype, 0);
 add_nrn_has_net_event(_mechtype);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Release_site /home/stefano/Documenti/paperRevision/GL_Model/x86_64/Release_site.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 3.14159;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int seed(double);
 
static int  seed (  double _lx ) {
   set_seed ( _lx ) ;
    return 0; }
 
static double _hoc_seed(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 seed (  *getarg(1) );
 return(_r);
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   if ( ( _lflag  == 0.0 )  && ( on  == 1.0 ) ) {
     xold = x ;
     yold = y ;
     zold = z ;
     uold = u ;
     z = z * exp ( - ( t - tsyn ) / tau_rec ) ;
     z = z + ( y * ( exp ( - ( t - tsyn ) / tau_1 ) - exp ( - ( t - tsyn ) / tau_rec ) ) / ( ( tau_1 / tau_rec ) - 1.0 ) ) ;
     y = y * exp ( - ( t - tsyn ) / tau_1 ) ;
     x = 1.0 - y - z ;
     if ( tau_facil > 0.0 ) {
       u = u * exp ( - ( t - tsyn ) / tau_facil ) ;
       u = u + U * ( 1.0 - u ) ;
       }
     else {
       u = U ;
       }
     y = y + x * u ;
     Prelease = y ;
     vc = scop_random ( ) ;
     if ( vc < y ) {
       Vm = 20.0 ;
       net_event ( _pnt, t ) ;
       }
     else {
       if ( RelDep ) {
         x = xold ;
         y = yold ;
         z = zold ;
         u = uold ;
         }
       }
     xout = x ;
     yout = y ;
     zout = z ;
     uout = u ;
     tsyn = t ;
     }
   if ( _lflag  == 2.0 ) {
     Vm = - 90.0 ;
     }
   } }

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   Prelease = U ;
   Vm = - 90.0 ;
   on = 1.0 ;
   toff = 1e9 ;
   y = - 90.0 ;
   x = 1.0 ;
   y = 0.0 ;
   z = 0.0 ;
   u = 0.0 ;
   }

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
 v=_v;
{
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/home/stefano/Documenti/paperRevision/GL_Model/templates/mossy/Release_site.mod";
static const char* nmodl_file_text = 
  "COMMENT \n"
  "Rewritten by S. Solinas from the original scripts by Nieus T. for\n"
  "presynaptic stochastic release of neurotransmitter.\n"
  "\n"
  "12 July 2010\n"
  "\n"
  "A single releasing site. Receives spikes and trasmit spike with probability\n"
  "dependent on fatigue and recovery.\n"
  "\n"
  "Actually inspired to the mossy fiber granule cell synapse of \n"
  "cerebellum granular layer.\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "\n"
  "NEURON	{ \n"
  "    ARTIFICIAL_CELL Release_site\n"
  "    : burst stores the in_burst state, it is set to 1 when event_t == the_first_spike_of_burst and to 0 when event_t == the_firs_spike_after_the_burst\n"
  "    RANGE tau_1,tau_rec, tau_facil,U,Vm\n"
  "    RANGE xout,yout,zout,uout\n"
  "    RANGE RelDep,tsyn,Prelease\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "    PI   = (pi)(1)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    : Parametri Presinaptici\n"
  "    tau_1 	= 1 (ms) 	< 1e-9, 1e9 >\n"
  "    tau_rec 	= 8 (ms) 	< 1e-9, 1e9 > 	: 200 (ms)\n"
  "    tau_facil 	= 5 (ms) 	< 0, 1e9 > 	: 20\n"
  "    \n"
  "    U 		= 0.42 (1) 	< 0, 1 >\n"
  "    u0 		= 0 (1) 	< 0, 1 >	: se u0=0 al primo colpo y=U\n"
  "    RelDep		= 0\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    Prelease\n"
  "    Vm\n"
  "    xout	\n"
  "    yout\n"
  "    zout\n"
  "    uout\n"
  "    x\n"
  "    y\n"
  "    z\n"
  "    u\n"
  "    xold\n"
  "    yold\n"
  "    zold\n"
  "    uold\n"
  "    tsyn (ms)\n"
  "    vc\n"
  "    toff (ms)\n"
  "    on\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    Prelease=U\n"
  "    Vm = -90\n"
  "    \n"
  "    on = 1\n"
  "    toff = 1e9\n"
  "    y = -90\n"
  "    x=1\n"
  "    y=0\n"
  "    z=0	\n"
  "    u=0\n"
  "}	\n"
  "\n"
  "PROCEDURE seed(x) { set_seed(x) }\n"
  "\n"
  "NET_RECEIVE(w){   \n"
  "    if( (flag==0) && (on==1) ){  \n"
  "	:printf(\" evento ! tsyn = %g \\n\",t)\n"
  "	xold=x\n"
  "	yold=y\n"
  "	zold=z\n"
  "	uold=u\n"
  "	\n"
  "	:printf(\"Exp(%g)rec\",-(t - tsyn)/tau_rec)\n"
  "	z = z*exp(-(t - tsyn)/tau_rec)\n"
  "	z = z + ( y*(exp(-(t - tsyn)/tau_1) - exp(-(t - tsyn)/tau_rec)) / ((tau_1/tau_rec)-1) )\n"
  "	y = y*exp(-(t - tsyn)/tau_1)			\n"
  "	x = 1-y-z\n"
  "	\n"
  "	if(tau_facil>0){ \n"
  "	    :printf(\"Exp(%g)facil\",-(t - tsyn)/tau_rec)\n"
  "	    u=u*exp(-(t-tsyn)/tau_facil)\n"
  "	    u = u+U*(1-u)\n"
  "	    }else{u=U}			\n"
  "	    \n"
  "	    y=y+x*u\n"
  "	    Prelease=y  								\n"
  "	    vc=scop_random()\n"
  "	    if ( vc<y ) { 	\n"
  "		Vm = 20	\n"
  "		net_event(t)	\n"
  "	    } else {\n"
  "		if(RelDep) {		\n"
  "		    x=xold\n"
  "		    y=yold	\n"
  "		    z=zold\n"
  "		    u=uold\n"
  "		} \n"
  "	    }\n"
  "	    xout=x\n"
  "	    yout=y\n"
  "	    zout=z\n"
  "	    uout=u\n"
  "	    \n"
  "	    tsyn = t\n"
  "	}\n"
  "	\n"
  "	if (flag == 2) { \n"
  "	    Vm = -90 \n"
  "	}\n"
  "    }\n"
  ;
#endif

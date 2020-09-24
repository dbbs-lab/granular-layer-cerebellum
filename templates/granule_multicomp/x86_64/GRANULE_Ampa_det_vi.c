/* Created by Language version: 6.2.0 */
/* VECTORIZED */
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
 
#define nrn_init _nrn_init__GRANULE_Ampa_det_vi
#define _nrn_initial _nrn_initial__GRANULE_Ampa_det_vi
#define nrn_cur _nrn_cur__GRANULE_Ampa_det_vi
#define _nrn_current _nrn_current__GRANULE_Ampa_det_vi
#define nrn_jacob _nrn_jacob__GRANULE_Ampa_det_vi
#define nrn_state _nrn_state__GRANULE_Ampa_det_vi
#define _net_receive _net_receive__GRANULE_Ampa_det_vi 
#define kstates kstates__GRANULE_Ampa_det_vi 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define syntype _p[0]
#define gmax_factor _p[1]
#define Q10_diff _p[2]
#define Q10_channel _p[3]
#define gmax _p[4]
#define U _p[5]
#define tau_rec _p[6]
#define tau_facil _p[7]
#define M _p[8]
#define Rd _p[9]
#define Diff _p[10]
#define Cdur _p[11]
#define r1FIX _p[12]
#define r2 _p[13]
#define r3 _p[14]
#define r4 _p[15]
#define r5 _p[16]
#define r6FIX _p[17]
#define Erev _p[18]
#define kB _p[19]
#define tau_1 _p[20]
#define Tmax _p[21]
#define diffuse _p[22]
#define lamd _p[23]
#define nd _p[24]
#define i _p[25]
#define ic _p[26]
#define g _p[27]
#define r1 _p[28]
#define r6 _p[29]
#define T _p[30]
#define Trelease _p[31]
#define tspike (_p + 32)
#define PRE (_p + 132)
#define yuno _p[232]
#define C _p[233]
#define O _p[234]
#define D _p[235]
#define x _p[236]
#define tsyn _p[237]
#define Mres _p[238]
#define numpulses _p[239]
#define tzero _p[240]
#define gbar_Q10 _p[241]
#define Q10 _p[242]
#define DC _p[243]
#define DO _p[244]
#define DD _p[245]
#define v _p[246]
#define _g _p[247]
#define _tsav _p[248]
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
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static double _hoc_diffusione();
 static double _hoc_imax();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
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
 _extcall_prop = _prop;
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
 "diffusione", _hoc_diffusione,
 "imax", _hoc_imax,
 0, 0
};
#define diffusione diffusione_GRANULE_Ampa_det_vi
#define imax imax_GRANULE_Ampa_det_vi
 extern double diffusione( _threadargsproto_ );
 extern double imax( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
#define u0 u0_GRANULE_Ampa_det_vi
 double u0 = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "U", 0, 1,
 "tau_facil", 0, 1e+09,
 "tau_rec", 1e-09, 1e+09,
 "tau_1", 1e-09, 1e+09,
 "u0_GRANULE_Ampa_det_vi", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "u0_GRANULE_Ampa_det_vi", "1",
 "gmax", "pS",
 "U", "1",
 "tau_rec", "ms",
 "tau_facil", "ms",
 "Rd", "um",
 "Diff", "um2/ms",
 "Cdur", "ms",
 "r1FIX", "/ms/mM",
 "r2", "/ms",
 "r3", "/ms",
 "r4", "/ms",
 "r5", "/ms",
 "r6FIX", "/ms/mM",
 "Erev", "mV",
 "kB", "mM",
 "tau_1", "ms",
 "Tmax", "mM",
 "lamd", "nm",
 "i", "nA",
 "ic", "nA",
 "g", "pS",
 "r1", "/ms",
 "r6", "/ms",
 "T", "mM",
 "Trelease", "mM",
 "tspike", "ms",
 0,0
};
 static double C0 = 0;
 static double D0 = 0;
 static double O0 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "u0_GRANULE_Ampa_det_vi", &u0_GRANULE_Ampa_det_vi,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"GRANULE_Ampa_det_vi",
 "syntype",
 "gmax_factor",
 "Q10_diff",
 "Q10_channel",
 "gmax",
 "U",
 "tau_rec",
 "tau_facil",
 "M",
 "Rd",
 "Diff",
 "Cdur",
 "r1FIX",
 "r2",
 "r3",
 "r4",
 "r5",
 "r6FIX",
 "Erev",
 "kB",
 "tau_1",
 "Tmax",
 "diffuse",
 "lamd",
 "nd",
 0,
 "i",
 "ic",
 "g",
 "r1",
 "r6",
 "T",
 "Trelease",
 "tspike[100]",
 "PRE[100]",
 "yuno",
 0,
 "C",
 "O",
 "D",
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
 	_p = nrn_prop_data_alloc(_mechtype, 249, _prop);
 	/*initialize range parameters*/
 	syntype = 0;
 	gmax_factor = 1;
 	Q10_diff = 1.5;
 	Q10_channel = 2.4;
 	gmax = 1200;
 	U = 0.42;
 	tau_rec = 8;
 	tau_facil = 5;
 	M = 21.515;
 	Rd = 1.03;
 	Diff = 0.223;
 	Cdur = 0.3;
 	r1FIX = 5.4;
 	r2 = 0.82;
 	r3 = 0;
 	r4 = 0;
 	r5 = 0.013;
 	r6FIX = 1.12;
 	Erev = 0;
 	kB = 0.44;
 	tau_1 = 1;
 	Tmax = 1;
 	diffuse = 1;
 	lamd = 20;
 	nd = 1;
  }
 	_prop->param = _p;
 	_prop->param_size = 249;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 
#define _tqitem &(_ppvar[2]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 static void _net_init(Point_process*, double*, double);
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _GRANULE_Ampa_det_vi_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 3,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
  _extcall_thread = (Datum*)ecalloc(2, sizeof(Datum));
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
  hoc_register_prop_size(_mechtype, 249, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_init[_mechtype] = _net_init;
 pnt_receive_size[_mechtype] = 8;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 GRANULE_Ampa_det_vi /home/neuron/projects/rete/control_sims/weasel/templates/granule_multicomp/x86_64/GRANULE_Ampa_det_vi.mod\n");
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
 extern double *_nrn_thread_getelm();
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3]; static double *_temp1;
 static int kstates();
 
double imax ( _threadargsprotocomma_ double _la , double _lb ) {
   double _limax;
 if ( _la > _lb ) {
     _limax = _la ;
     }
   else {
     _limax = _lb ;
     }
   
return _limax;
 }
 
static double _hoc_imax(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  imax ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 return(_r);
}
 
double diffusione ( _threadargsproto_ ) {
   double _ldiffusione;
 double _lDifWave , _li , _lcntc , _lfi , _laaa ;
 _lDifWave = 0.0 ;
   _lcntc = imax ( _threadargscomma_ numpulses - 100.0 , 0.0 ) ;
   {int  _li ;for ( _li = ((int) _lcntc ) ; _li <= ((int) numpulses ) ; _li ++ ) {
     _lfi = fmod ( ((double) _li ) , 100.0 ) ;
     tzero = tspike [ ((int) _lfi ) ] ;
     if ( t > tzero ) {
       _laaa = ( - Rd * Rd / ( 4.0 * Diff * ( t - tzero ) ) ) ;
       if ( fabs ( _laaa ) < 699.0 ) {
         _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( _laaa ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
         }
       else {
         if ( _laaa > 0.0 ) {
           _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( 699.0 ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
           }
         else {
           _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( - 699.0 ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
           }
         }
       }
     } }
   _ldiffusione = _lDifWave ;
   
return _ldiffusione;
 }
 
static double _hoc_diffusione(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  diffusione ( _p, _ppvar, _thread, _nt );
 return(_r);
}
 
static int kstates (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<3;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 r1 = r1FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
   r6 = r6FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
   /* ~ C <-> O ( r1 * Q10 , r2 * Q10 )*/
 f_flux =  r1 * Q10 * C ;
 b_flux =  r2 * Q10 * O ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  r1 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  r2 * Q10 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ D <-> C ( r5 * Q10 , r6 * Q10 )*/
 f_flux =  r5 * Q10 * D ;
 b_flux =  r6 * Q10 * C ;
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  r5 * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 _term =  r6 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + O + D = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= D ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= O ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= C ;
 /*CONSERVATION*/
   } return _reset;
 }
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   double _lfi ;
 if ( _lflag  == 0.0 ) {
     _args[2] = _args[2] + 1.0 ;
     if (  ! _args[1] ) {
       _args[3] = t ;
       _args[1] = 1.0 ;
       _args[5] = _args[5] * exp ( - ( t - _args[7] ) / ( tau_rec ) ) ;
       _args[5] = _args[5] + ( _args[4] * ( exp ( - ( t - _args[7] ) / tau_1 ) - exp ( - ( t - _args[7] ) / ( tau_rec ) ) ) / ( ( tau_1 / ( tau_rec ) ) - 1.0 ) ) ;
       _args[4] = _args[4] * exp ( - ( t - _args[7] ) / tau_1 ) ;
       x = 1.0 - _args[4] - _args[5] ;
       if ( tau_facil > 0.0 ) {
         _args[6] = _args[6] * exp ( - ( t - _args[7] ) / tau_facil ) ;
         _args[6] = _args[6] + U * ( 1.0 - _args[6] ) ;
         }
       else {
         _args[6] = U ;
         }
       _args[4] = _args[4] + x * _args[6] ;
       T = Tmax * _args[4] ;
       yuno = _args[4] ;
       _lfi = fmod ( numpulses , 100.0 ) ;
       PRE [ ((int) _lfi ) ] = _args[4] ;
       tspike [ ((int) _lfi ) ] = t ;
       numpulses = numpulses + 1.0 ;
       _args[7] = t ;
       }
     net_send ( _tqitem, _args, _pnt, t +  Cdur , _args[2] ) ;
     }
   if ( _lflag  == _args[2] ) {
     _args[3] = t ;
     T = 0.0 ;
     _args[1] = 0.0 ;
     }
   } }
 
static void _net_init(Point_process* _pnt, double* _args, double _lflag) {
       double* _p = _pnt->_prop->param;
    Datum* _ppvar = _pnt->_prop->dparam;
    Datum* _thread = (Datum*)0;
    _NrnThread* _nt = (_NrnThread*)_pnt->_vnt;
 _args[4] = 0.0 ;
   _args[5] = 0.0 ;
   _args[6] = u0 ;
   _args[7] = t ;
   _args[2] = 1.0 ;
   }
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<3;_i++) _p[_dlist1[_i]] = 0.0;}
 r1 = r1FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 r6 = r6FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 /* ~ C <-> O ( r1 * Q10 , r2 * Q10 )*/
 f_flux =  r1 * Q10 * C ;
 b_flux =  r2 * Q10 * O ;
 DC -= (f_flux - b_flux);
 DO += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ D <-> C ( r5 * Q10 , r6 * Q10 )*/
 f_flux =  r5 * Q10 * D ;
 b_flux =  r6 * Q10 * C ;
 DD -= (f_flux - b_flux);
 DC += (f_flux - b_flux);
 
 /*REACTION*/
   /* C + O + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<3;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 r1 = r1FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 r6 = r6FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 /* ~ C <-> O ( r1 * Q10 , r2 * Q10 )*/
 _term =  r1 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  r2 * Q10 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ D <-> C ( r5 * Q10 , r6 * Q10 )*/
 _term =  r5 * Q10 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 1 ,0)  -= _term;
 _term =  r6 * Q10 ;
 _MATELM1( 0 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + O + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 3, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  C = C0;
  D = D0;
  O = O0;
 {
   C = 1.0 ;
   O = 0.0 ;
   D = 0.0 ;
   T = 0.0 ;
   yuno = 0.0 ;
   numpulses = 0.0 ;
   Trelease = 0.0 ;
   tspike [ 0 ] = 1e12 ;
   gbar_Q10 = pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Q10 = pow( Q10_channel , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Mres = 1e3 * ( 1e3 * 1e15 / 6.022e23 * M ) ;
   numpulses = 0.0 ;
   {int  _li ;for ( _li = 1 ; _li <= 100 ; _li ++ ) {
     PRE [ _li - 1 ] = 0.0 ;
     tspike [ _li - 1 ] = 0.0 ;
     } }
   tspike [ 0 ] = 1e12 ;
   if ( tau_1 >= tau_rec ) {
     printf ( "Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\n" , tau_1 , tau_rec ) ;
     tau_rec = tau_1 + 1e-5 ;
     }
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   if ( diffuse  && ( t > tspike [ 0 ] ) ) {
     Trelease = T + diffusione ( _threadargs_ ) ;
     }
   else {
     Trelease = T ;
     }
   g = gmax * gbar_Q10 * O ;
   i = ( 1e-6 ) * g * ( v - Erev ) * gmax_factor ;
   ic = i ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 {  sparse_thread(&_thread[_spth1]._pvoid, 3, _slist1, _dlist1, _p, &t, dt, kstates, _linmat1, _ppvar, _thread, _nt);
  }}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(D) - _p;  _dlist1[0] = &(DD) - _p;
 _slist1[1] = &(C) - _p;  _dlist1[1] = &(DC) - _p;
 _slist1[2] = &(O) - _p;  _dlist1[2] = &(DO) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

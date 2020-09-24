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
 
#define nrn_init _nrn_init__GRANULE_Nmda_stoch_vi
#define _nrn_initial _nrn_initial__GRANULE_Nmda_stoch_vi
#define nrn_cur _nrn_cur__GRANULE_Nmda_stoch_vi
#define _nrn_current _nrn_current__GRANULE_Nmda_stoch_vi
#define nrn_jacob _nrn_jacob__GRANULE_Nmda_stoch_vi
#define nrn_state _nrn_state__GRANULE_Nmda_stoch_vi
#define _net_receive _net_receive__GRANULE_Nmda_stoch_vi 
#define _f_rates _f_rates__GRANULE_Nmda_stoch_vi 
#define kstates kstates__GRANULE_Nmda_stoch_vi 
#define rates rates__GRANULE_Nmda_stoch_vi 
 
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
#define syntype _p[0]
#define gmax_factor _p[1]
#define gmax _p[2]
#define Q10_diff _p[3]
#define Q10_channel _p[4]
#define M _p[5]
#define Rd _p[6]
#define Diff _p[7]
#define Tmax _p[8]
#define T_factor _p[9]
#define Cdur _p[10]
#define Rb _p[11]
#define Ru _p[12]
#define RdRate _p[13]
#define Rr _p[14]
#define Ro _p[15]
#define Rc _p[16]
#define Erev _p[17]
#define v0_block _p[18]
#define k_block _p[19]
#define nd _p[20]
#define diffuse _p[21]
#define lamd _p[22]
#define i _p[23]
#define ic _p[24]
#define g _p[25]
#define rb _p[26]
#define T _p[27]
#define Trelease _p[28]
#define PRE (_p + 29)
#define MgBlock _p[129]
#define C0 _p[130]
#define C1 _p[131]
#define C2 _p[132]
#define D _p[133]
#define O _p[134]
#define x _p[135]
#define tspike (_p + 136)
#define Mres _p[236]
#define numpulses _p[237]
#define tzero _p[238]
#define gbar_Q10 _p[239]
#define Q10 _p[240]
#define DC0 _p[241]
#define DC1 _p[242]
#define DC2 _p[243]
#define DD _p[244]
#define DO _p[245]
#define _g _p[246]
#define _tsav _p[247]
#define _nd_area  *_ppvar[0]._pval
#define y	*_ppvar[2]._pval
#define _p_y	_ppvar[2]._pval
 
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
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static double _hoc_diffusione();
 static double _hoc_imax();
 static double _hoc_rates();
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
 "diffusione", _hoc_diffusione,
 "imax", _hoc_imax,
 "rates", _hoc_rates,
 0, 0
};
#define diffusione diffusione_GRANULE_Nmda_stoch_vi
#define imax imax_GRANULE_Nmda_stoch_vi
 extern double diffusione( );
 extern double imax( double , double );
 /* declare global and static user variables */
#define usetable usetable_GRANULE_Nmda_stoch_vi
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_GRANULE_Nmda_stoch_vi", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gmax", "pS",
 "Rd", "um",
 "Diff", "um2/ms",
 "Tmax", "mM",
 "Cdur", "ms",
 "Rb", "/ms/mM",
 "Ru", "/ms",
 "RdRate", "/ms",
 "Rr", "/ms",
 "Ro", "/ms",
 "Rc", "/ms",
 "Erev", "mV",
 "v0_block", "mV",
 "k_block", "mV",
 "lamd", "nm",
 "i", "nA",
 "ic", "nA",
 "g", "pS",
 "rb", "/ms",
 "T", "mM",
 "Trelease", "mM",
 0,0
};
 static double C20 = 0;
 static double C10 = 0;
 static double C00 = 0;
 static double D0 = 0;
 static double O0 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "usetable_GRANULE_Nmda_stoch_vi", &usetable_GRANULE_Nmda_stoch_vi,
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
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"GRANULE_Nmda_stoch_vi",
 "syntype",
 "gmax_factor",
 "gmax",
 "Q10_diff",
 "Q10_channel",
 "M",
 "Rd",
 "Diff",
 "Tmax",
 "T_factor",
 "Cdur",
 "Rb",
 "Ru",
 "RdRate",
 "Rr",
 "Ro",
 "Rc",
 "Erev",
 "v0_block",
 "k_block",
 "nd",
 "diffuse",
 "lamd",
 0,
 "i",
 "ic",
 "g",
 "rb",
 "T",
 "Trelease",
 "PRE[100]",
 "MgBlock",
 0,
 "C0",
 "C1",
 "C2",
 "D",
 "O",
 0,
 "y",
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
 	_p = nrn_prop_data_alloc(_mechtype, 248, _prop);
 	/*initialize range parameters*/
 	syntype = 0;
 	gmax_factor = 1;
 	gmax = 18800;
 	Q10_diff = 1.5;
 	Q10_channel = 2.4;
 	M = 21.515;
 	Rd = 1.03;
 	Diff = 0.223;
 	Tmax = 1;
 	T_factor = 0.5;
 	Cdur = 0.3;
 	Rb = 5;
 	Ru = 0.1;
 	RdRate = 0.012;
 	Rr = 0.009;
 	Ro = 0.03;
 	Rc = 0.966;
 	Erev = -3.7;
 	v0_block = -20;
 	k_block = 13;
 	nd = 1;
 	diffuse = 1;
 	lamd = 20;
  }
 	_prop->param = _p;
 	_prop->param_size = 248;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
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
 
#define _tqitem &(_ppvar[3]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 static void _net_init(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _GRANULE_Nmda_stoch_vi_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 248, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "netsend");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_init[_mechtype] = _net_init;
 pnt_receive_size[_mechtype] = 4;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 GRANULE_Nmda_stoch_vi /home/stefano/Documenti/paperRevision/GL_Model/x86_64/GRANULE_Nmda_stoch_vi.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 3.14159;
 static double *_t_MgBlock;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_rates(double);
static int rates(double);
 extern double *_getelm();
 
#define _MATELM1(_row,_col)	*(_getelm(_row + 1, _col + 1))
 
#define _RHS1(_arg) _coef1[_arg + 1]
 static double *_coef1;
 
#define _linmat1  1
 static void* _sparseobj1;
 static void* _cvsparseobj1;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_rates(double);
 static int _slist1[5], _dlist1[5]; static double *_temp1;
 static int kstates();
 
double imax (  double _la , double _lb ) {
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
    _hoc_setdata(_vptr);
 _r =  imax (  *getarg(1) , *getarg(2) );
 return(_r);
}
 
double diffusione (  ) {
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
    _hoc_setdata(_vptr);
 _r =  diffusione (  );
 return(_r);
}
 
static int kstates ()
 {_reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<5;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 Trelease = diffusione ( _threadargs_ ) ;
   rb = Rb * Trelease ;
   /* ~ C0 <-> C1 ( rb * Q10 , Ru * Q10 )*/
 f_flux =  rb * Q10 * C0 ;
 b_flux =  Ru * Q10 * C1 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  rb * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  Ru * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ C1 <-> C2 ( rb * Q10 , Ru * Q10 )*/
 f_flux =  rb * Q10 * C1 ;
 b_flux =  Ru * Q10 * C2 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  rb * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  Ru * Q10 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C2 <-> D ( RdRate * Q10 , Rr * Q10 )*/
 f_flux =  RdRate * Q10 * C2 ;
 b_flux =  Rr * Q10 * D ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  RdRate * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  Rr * Q10 ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ C2 <-> O ( Ro * Q10 , Rc * Q10 )*/
 f_flux =  Ro * Q10 * C2 ;
 b_flux =  Rc * Q10 * O ;
 _RHS1( 1) -= (f_flux - b_flux);
 
 _term =  Ro * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _term =  Rc * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 /*REACTION*/
   /* C0 + C1 + C2 + D + O = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= O ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= D ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= C2 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= C1 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= C0 ;
 /*CONSERVATION*/
   } return _reset;
 }
 static double _mfac_rates, _tmin_rates;
 static void _check_rates();
 static void _check_rates() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_v0_block;
  static double _sav_k_block;
  if (!usetable) {return;}
  if (_sav_v0_block != v0_block) { _maktable = 1;}
  if (_sav_k_block != k_block) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_rates =  - 120.0 ;
   _tmax =  30.0 ;
   _dx = (_tmax - _tmin_rates)/150.; _mfac_rates = 1./_dx;
   for (_i=0, _x=_tmin_rates; _i < 151; _x += _dx, _i++) {
    _f_rates(_x);
    _t_MgBlock[_i] = MgBlock;
   }
   _sav_v0_block = v0_block;
   _sav_k_block = k_block;
  }
 }

 static int rates(double _lv){ _check_rates();
 _n_rates(_lv);
 return 0;
 }

 static void _n_rates(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_rates(_lv); return; 
}
 _xi = _mfac_rates * (_lv - _tmin_rates);
 if (isnan(_xi)) {
  MgBlock = _xi;
  return;
 }
 if (_xi <= 0.) {
 MgBlock = _t_MgBlock[0];
 return; }
 if (_xi >= 150.) {
 MgBlock = _t_MgBlock[150];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 MgBlock = _t_MgBlock[_i] + _theta*(_t_MgBlock[_i+1] - _t_MgBlock[_i]);
 }

 
static int  _f_rates (  double _lv ) {
   MgBlock = 1.0 / ( 1.0 + exp ( - ( _lv - v0_block ) / k_block ) ) ;
    return 0; }
 
static double _hoc_rates(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
  _r = 1.;
 rates (  *getarg(1) );
 return(_r);
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   double _lfi ;
 if ( _lflag  == 0.0 ) {
     _args[2] = _args[2] + 1.0 ;
     if (  ! _args[1] ) {
       _args[3] = t ;
       _args[1] = 1.0 ;
       T = Tmax * T_factor ;
       _lfi = fmod ( numpulses , 100.0 ) ;
       PRE [ ((int) _lfi ) ] = T_factor ;
       tspike [ ((int) _lfi ) ] = t ;
       numpulses = numpulses + 1.0 ;
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
       _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
 _args[2] = 1.0 ;
   }
 
/*CVODE ode begin*/
 static int _ode_spec1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<5;_i++) _p[_dlist1[_i]] = 0.0;}
 Trelease = diffusione ( _threadargs_ ) ;
 rb = Rb * Trelease ;
 /* ~ C0 <-> C1 ( rb * Q10 , Ru * Q10 )*/
 f_flux =  rb * Q10 * C0 ;
 b_flux =  Ru * Q10 * C1 ;
 DC0 -= (f_flux - b_flux);
 DC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C1 <-> C2 ( rb * Q10 , Ru * Q10 )*/
 f_flux =  rb * Q10 * C1 ;
 b_flux =  Ru * Q10 * C2 ;
 DC1 -= (f_flux - b_flux);
 DC2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C2 <-> D ( RdRate * Q10 , Rr * Q10 )*/
 f_flux =  RdRate * Q10 * C2 ;
 b_flux =  Rr * Q10 * D ;
 DC2 -= (f_flux - b_flux);
 DD += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C2 <-> O ( Ro * Q10 , Rc * Q10 )*/
 f_flux =  Ro * Q10 * C2 ;
 b_flux =  Rc * Q10 * O ;
 DC2 -= (f_flux - b_flux);
 DO += (f_flux - b_flux);
 
 /*REACTION*/
   /* C0 + C1 + C2 + D + O = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<5;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 Trelease = diffusione ( _threadargs_ ) ;
 rb = Rb * Trelease ;
 /* ~ C0 <-> C1 ( rb * Q10 , Ru * Q10 )*/
 _term =  rb * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  Ru * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ C1 <-> C2 ( rb * Q10 , Ru * Q10 )*/
 _term =  rb * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  Ru * Q10 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C2 <-> D ( RdRate * Q10 , Rr * Q10 )*/
 _term =  RdRate * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  Rr * Q10 ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ C2 <-> O ( Ro * Q10 , Rc * Q10 )*/
 _term =  Ro * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 0 ,1)  -= _term;
 _term =  Rc * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
   /* C0 + C1 + C2 + D + O = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 5;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 5; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse(&_cvsparseobj1, 5, _dlist1, _p, _ode_matsol1, &_coef1);
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  C2 = C20;
  C1 = C10;
  C0 = C00;
  D = D0;
  O = O0;
 {
   rates ( _threadargscomma_ v ) ;
   C0 = 1.0 ;
   C1 = 0.0 ;
   C2 = 0.0 ;
   D = 0.0 ;
   O = 0.0 ;
   T = 0.0 ;
   numpulses = 0.0 ;
   gbar_Q10 = pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Q10 = pow( Q10_channel , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Mres = 1e3 * ( 1e3 * 1e15 / 6.022e23 * M ) ;
   {int  _li ;for ( _li = 1 ; _li <= 100 ; _li ++ ) {
     PRE [ _li - 1 ] = 0.0 ;
     tspike [ _li - 1 ] = 0.0 ;
     } }
   tspike [ 0 ] = 1e12 ;
   }
  _sav_indep = t; t = _save;

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
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   rates ( _threadargscomma_ v ) ;
   g = gmax * gbar_Q10 * O * gmax_factor ;
   i = ( 1e-6 ) * g * ( v - Erev ) * MgBlock ;
   ic = i ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
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
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 { error = sparse(&_sparseobj1, 5, _slist1, _dlist1, _p, &t, dt, kstates,&_coef1, _linmat1);
 if(error){fprintf(stderr,"at line 149 in file GRANULE_Nmda_stoch_vi.mod:\n	SOLVE kstates METHOD sparse	\n"); nrn_complain(_p); abort_run(error);}
    if (secondorder) {
    int _i;
    for (_i = 0; _i < 5; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 }}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
   _t_MgBlock = makevector(151*sizeof(double));
 _slist1[0] = &(O) - _p;  _dlist1[0] = &(DO) - _p;
 _slist1[1] = &(C2) - _p;  _dlist1[1] = &(DC2) - _p;
 _slist1[2] = &(C1) - _p;  _dlist1[2] = &(DC1) - _p;
 _slist1[3] = &(C0) - _p;  _dlist1[3] = &(DC0) - _p;
 _slist1[4] = &(D) - _p;  _dlist1[4] = &(DD) - _p;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/home/stefano/Documenti/paperRevision/GL_Model/templates/synapse/GRANULE_Nmda_stoch_vi.mod";
static const char* nmodl_file_text = 
  "NEURON {\n"
  "	POINT_PROCESS GRANULE_Nmda_stoch_vi\n"
  "	POINTER y\n"
  "	NONSPECIFIC_CURRENT i\n"
  "	RANGE Q10_diff,Q10_channel\n"
  "	RANGE g , ic\n"
  "	RANGE Cdur,Erev,T,Tmax\n"
  "	RANGE Rb, Ru, Rd, Rr, Ro, Rc,rb,gmax,RdRate\n"
  "	RANGE PRE\n"
  "	RANGE Used\n"
  "	RANGE MgBlock,v0_block,k_block\n"
  "	RANGE diffuse,Trelease,lamd, Diff, M, Rd, nd, syntype, gmax_factor\n"
  "	RANGE T_factor\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(nA) = (nanoamp)	\n"
  "	(mV) = (millivolt)\n"
  "	(umho) = (micromho)\n"
  "	(mM) = (milli/liter)\n"
  "	(pS) = (picosiemens)\n"
  "	(nS) = (nanosiemens)\n"
  "	(um) = (micrometer)\n"
  "	PI	= (pi)		(1)\n"
  "    }\n"
  "    \n"
  "    PARAMETER {\n"
  "	syntype\n"
  "	gmax_factor = 1\n"
  "	: Parametri Presinaptici\n"
  "	gmax		= 18800  	(pS)	: 7e3 : 4e4\n"
  "	Q10_diff	= 1.5\n"
  "	Q10_channel	= 2.4\n"
  "\n"
  "	M	= 21.515 : numero di (kilo) molecole in una vescicola		\n"
  "	Rd	= 1.03 (um)\n"
  "	Diff	= 0.223 (um2/ms)\n"
  "	\n"
  "	Tmax		= 1  	(mM)\n"
  "	T_factor = 0.5\n"
  "\n"
  "\n"
  "	: Postsinaptico, Westbrook scheme\n"
  "	\n"
  "	Cdur	= 0.3	(ms)\n"
  "	Rb	=  5		(/ms/mM)  	: binding\n"
  "	Ru	=  0.1		(/ms)		: unbinding\n"
  "	RdRate	=  12e-3  	(/ms)		: desensitization\n"
  "	Rr	=  9e-3		(/ms)		: resensitization\n"
  "	Ro	=  3e-2 	(/ms)		: opening\n"
  "	Rc	=  0.966	(/ms)		: closing\n"
  "	Erev	= -3.7  (mV)	: 0 (mV)\n"
  "	\n"
  "	v0_block = -20 (mV)	: -16 -8.69 (mV)	: -18.69 (mV) : -32.7 (mV)\n"
  "	k_block  = 13 (mV)\n"
  "	nd	 = 1\n"
  "	: kB	 = 0.44	(mM)\n"
  "\n"
  "	: Diffusion			\n"
  "	diffuse	= 1\n"
  "	lamd	= 20 (nm)\n"
  "	celsius (degC)\n"
  "}\n"
  "\n"
  "\n"
  "ASSIGNED {\n"
  "	v		(mV)		: postsynaptic voltage\n"
  "	i 		(nA)		: current = g*(v - Erev)\n"
  "	ic 		(nA)		: current = g*(v - Erev)\n"
  "	g 		(pS)		: actual conductance\n"
  "\n"
  "	rb		(/ms)    : binding\n"
  "	\n"
  "	T		(mM)\n"
  "	x \n"
  "	\n"
  "	Trelease	(mM)\n"
  "	tspike[100]	(ms)	: will be initialized by the pointprocess\n"
  "	PRE[100]\n"
  "	Mres		(mM)	\n"
  "	\n"
  "	MgBlock\n"
  "	numpulses\n"
  "	tzero\n"
  "	gbar_Q10 (mho/cm2)\n"
  "	Q10 (1)\n"
  "	y\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	: Channel states (all fractions)\n"
  "	C0		: unbound\n"
  "	C1		: single bound\n"
  "	C2		: double bound\n"
  "	D		: desensitized\n"
  "	O		: open\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rates(v)\n"
  "	C0 = 1\n"
  "	C1 = 0\n"
  "	C2 = 0\n"
  "	D  = 0\n"
  "	O  = 0\n"
  "	T  = 0\n"
  "	numpulses=0\n"
  "\n"
  "	gbar_Q10 = Q10_diff^((celsius-30)/10)\n"
  "	Q10 = Q10_channel^((celsius-30)/10)\n"
  "\n"
  "	Mres = 1e3 * (1e3 * 1e15 / 6.022e23 * M)     : (M) to (mM) so 1e3, 1um^3=1dm^3*1e-15 so 1e15\n"
  "	FROM i=1 TO 100{ PRE[i-1]=0 tspike[i-1]=0 } :PRE_2[500]=0}\n"
  "	tspike[0]=1e12	(ms)\n"
  "\n"
  "}\n"
  "\n"
  "FUNCTION imax(a,b) {\n"
  "    if (a>b) { imax=a }\n"
  "    else { imax=b }\n"
  "}\n"
  "\n"
  "FUNCTION diffusione(){	 \n"
  "	LOCAL DifWave,i,cntc,fi,aaa\n"
  "	DifWave=0\n"
  "	cntc=imax(numpulses-100,0)\n"
  "	FROM i=cntc  TO numpulses{\n"
  "	    fi=fmod(i,100)\n"
  "		tzero=tspike[fi]\n"
  "		if(t>tzero){\n"
  "		    aaa = (-Rd*Rd/(4*Diff*(t-tzero)))\n"
  "		    if(fabs(aaa)<699){\n"
  "			DifWave=DifWave+PRE[fi]*Mres*exp(aaa)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "		    }else{\n"
  "			if(aaa>0){\n"
  "			    DifWave=DifWave+PRE[fi]*Mres*exp(699)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "			}else{\n"
  "			    DifWave=DifWave+PRE[fi]*Mres*exp(-699)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "			}\n"
  "		    }\n"
  "			\n"
  "		}\n"
  "	}    \n"
  "	diffusione=DifWave\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	rates(v)\n"
  "	SOLVE kstates METHOD sparse	\n"
  "	g = gmax * gbar_Q10 * O * gmax_factor\n"
  "	\n"
  "	: E' piu' logico spostare * MgBlock * PRE sul calcolo della corrente!\n"
  "	i = (1e-6) * g * (v - Erev) * MgBlock\n"
  "	ic = i\n"
  "    }\n"
  "\n"
  "KINETIC kstates {	\n"
  "	:if ( diffuse && (t>tspike[0]) ) { Trelease= T + diffusione() } else { Trelease=T }\n"
  "	Trelease = diffusione()\n"
  "	rb = Rb * Trelease	:^2 / (Trelease + kB)^2 \n"
  "	~ C0 <-> C1	(rb*Q10,Ru*Q10) 	: (fattore*rb,Ru) qui 2* per descrizione part.identiche\n"
  "	~ C1 <-> C2	(rb*Q10,Ru*Q10)		: (rb,fattore*Ru)	idem\n"
  "	~ C2 <-> D	(RdRate*Q10,Rr*Q10)\n"
  "	~ C2 <-> O	(Ro*Q10,Rc*Q10)\n"
  "	CONSERVE C0+C1+C2+D+O = 1\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v(mV)) {\n"
  "	: E' necessario includere DEPEND v0_block,k_block per aggiornare le tabelle!\n"
  "	TABLE MgBlock DEPEND v0_block,k_block FROM -120 TO 30 WITH 150\n"
  "	MgBlock = 1 / ( 1 + exp ( - ( v - v0_block ) / k_block ) )\n"
  "}\n"
  "\n"
  "\n"
  "NET_RECEIVE(weight, on, nspike, tzero (ms)) {LOCAL fi :,y, z, u, tsyn (ms)\n"
  "\n"
  ": *********** ATTENZIONE! ***********\n"
  ":\n"
  ": Qualora si vogliano utilizzare impulsi di glutammato saturanti e' \n"
  ": necessario che il pulse sia piu' corto dell'intera simulazione\n"
  ": altrimenti la variabile on non torna al suo valore di default.\n"
  "\n"
  "INITIAL {\n"
  "	nspike = 1\n"
  "    }\n"
  "    if (flag == 0) { \n"
  "		: Qui faccio rientrare la modulazione presinaptica\n"
  "		nspike = nspike + 1\n"
  "		if (!on) {\n"
  "			tzero = t\n"
  "			on = 1				\n"
  "			T=Tmax * T_factor :* y			\n"
  "			fi=fmod(numpulses,100)\n"
  "			PRE[fi]= T_factor :y :(use with pointer)	: PRE[numpulses]=y\n"
  "			tspike[fi] = t\n"
  "			numpulses=numpulses+1\n"
  "		}\n"
  "		net_send(Cdur, nspike)	: !\n"
  "    }\n"
  "	if (flag == nspike) { \n"
  "			tzero = t\n"
  "			T = 0\n"
  "			on = 0\n"
  "		    }\n"
  "}\n"
  ;
#endif

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
 
#define nrn_init _nrn_init__Golgi_KA
#define _nrn_initial _nrn_initial__Golgi_KA
#define nrn_cur _nrn_cur__Golgi_KA
#define _nrn_current _nrn_current__Golgi_KA
#define nrn_jacob _nrn_jacob__Golgi_KA
#define nrn_state _nrn_state__Golgi_KA
#define _net_receive _net_receive__Golgi_KA 
#define _f_rate _f_rate__Golgi_KA 
#define rate rate__Golgi_KA 
#define states states__Golgi_KA 
 
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
#define gbar _p[0]
#define Q10_diff _p[1]
#define Q10_channel _p[2]
#define ik _p[3]
#define a_inf _p[4]
#define b_inf _p[5]
#define tau_a _p[6]
#define tau_b _p[7]
#define g _p[8]
#define tcorr _p[9]
#define gbar_Q10 _p[10]
#define ic _p[11]
#define a _p[12]
#define b _p[13]
#define ek _p[14]
#define Da _p[15]
#define Db _p[16]
#define alpha_a _p[17]
#define beta_a _p[18]
#define alpha_b _p[19]
#define beta_b _p[20]
#define v _p[21]
#define _g _p[22]
#define _ion_ek	*_ppvar[0]._pval
#define _ion_ik	*_ppvar[1]._pval
#define _ion_dikdv	*_ppvar[2]._pval
 
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
 static void _hoc_alp_b(void);
 static void _hoc_alp_a(void);
 static void _hoc_bet_b(void);
 static void _hoc_bet_a(void);
 static void _hoc_linoid(void);
 static void _hoc_rate(void);
 static void _hoc_sigm(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_Golgi_KA", _hoc_setdata,
 "alp_b_Golgi_KA", _hoc_alp_b,
 "alp_a_Golgi_KA", _hoc_alp_a,
 "bet_b_Golgi_KA", _hoc_bet_b,
 "bet_a_Golgi_KA", _hoc_bet_a,
 "linoid_Golgi_KA", _hoc_linoid,
 "rate_Golgi_KA", _hoc_rate,
 "sigm_Golgi_KA", _hoc_sigm,
 0, 0
};
#define alp_b alp_b_Golgi_KA
#define alp_a alp_a_Golgi_KA
#define bet_b bet_b_Golgi_KA
#define bet_a bet_a_Golgi_KA
#define linoid linoid_Golgi_KA
#define sigm sigm_Golgi_KA
 extern double alp_b( _threadargsprotocomma_ double );
 extern double alp_a( _threadargsprotocomma_ double );
 extern double bet_b( _threadargsprotocomma_ double );
 extern double bet_a( _threadargsprotocomma_ double );
 extern double linoid( _threadargsprotocomma_ double , double );
 extern double sigm( _threadargsprotocomma_ double , double );
 
static void _check_rate(double*, Datum*, Datum*, _NrnThread*); 
static void _check_table_thread(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, int _type) {
   _check_rate(_p, _ppvar, _thread, _nt);
 }
 /* declare global and static user variables */
#define Abeta_b Abeta_b_Golgi_KA
 double Abeta_b = 0.0345;
#define Aalpha_b Aalpha_b_Golgi_KA
 double Aalpha_b = 0.0368;
#define Abeta_a Abeta_a_Golgi_KA
 double Abeta_a = 0.1655;
#define Aalpha_a Aalpha_a_Golgi_KA
 double Aalpha_a = 0.8147;
#define K_binf K_binf_Golgi_KA
 double K_binf = 8.4;
#define K_ainf K_ainf_Golgi_KA
 double K_ainf = -17;
#define Kbeta_b Kbeta_b_Golgi_KA
 double Kbeta_b = -8.90123;
#define Kalpha_b Kalpha_b_Golgi_KA
 double Kalpha_b = 12.8433;
#define Kbeta_a Kbeta_a_Golgi_KA
 double Kbeta_a = 19.4718;
#define Kalpha_a Kalpha_a_Golgi_KA
 double Kalpha_a = -23.3271;
#define V0_binf V0_binf_Golgi_KA
 double V0_binf = -78.8;
#define V0_ainf V0_ainf_Golgi_KA
 double V0_ainf = -38;
#define V0beta_b V0beta_b_Golgi_KA
 double V0beta_b = -49.9537;
#define V0alpha_b V0alpha_b_Golgi_KA
 double V0alpha_b = -111.332;
#define V0beta_a V0beta_a_Golgi_KA
 double V0beta_a = -18.2791;
#define V0alpha_a V0alpha_a_Golgi_KA
 double V0alpha_a = -9.17203;
#define usetable usetable_Golgi_KA
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_Golgi_KA", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Aalpha_a_Golgi_KA", "/ms",
 "Kalpha_a_Golgi_KA", "mV",
 "V0alpha_a_Golgi_KA", "mV",
 "Abeta_a_Golgi_KA", "/ms",
 "Kbeta_a_Golgi_KA", "mV",
 "V0beta_a_Golgi_KA", "mV",
 "Aalpha_b_Golgi_KA", "/ms",
 "Kalpha_b_Golgi_KA", "mV",
 "V0alpha_b_Golgi_KA", "mV",
 "Abeta_b_Golgi_KA", "/ms",
 "Kbeta_b_Golgi_KA", "mV",
 "V0beta_b_Golgi_KA", "mV",
 "V0_ainf_Golgi_KA", "mV",
 "K_ainf_Golgi_KA", "mV",
 "V0_binf_Golgi_KA", "mV",
 "K_binf_Golgi_KA", "mV",
 "gbar_Golgi_KA", "mho/cm2",
 "ik_Golgi_KA", "mA/cm2",
 "tau_a_Golgi_KA", "ms",
 "tau_b_Golgi_KA", "ms",
 "g_Golgi_KA", "mho/cm2",
 "tcorr_Golgi_KA", "1",
 "gbar_Q10_Golgi_KA", "mho/cm2",
 0,0
};
 static double a0 = 0;
 static double b0 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "Aalpha_a_Golgi_KA", &Aalpha_a_Golgi_KA,
 "Kalpha_a_Golgi_KA", &Kalpha_a_Golgi_KA,
 "V0alpha_a_Golgi_KA", &V0alpha_a_Golgi_KA,
 "Abeta_a_Golgi_KA", &Abeta_a_Golgi_KA,
 "Kbeta_a_Golgi_KA", &Kbeta_a_Golgi_KA,
 "V0beta_a_Golgi_KA", &V0beta_a_Golgi_KA,
 "Aalpha_b_Golgi_KA", &Aalpha_b_Golgi_KA,
 "Kalpha_b_Golgi_KA", &Kalpha_b_Golgi_KA,
 "V0alpha_b_Golgi_KA", &V0alpha_b_Golgi_KA,
 "Abeta_b_Golgi_KA", &Abeta_b_Golgi_KA,
 "Kbeta_b_Golgi_KA", &Kbeta_b_Golgi_KA,
 "V0beta_b_Golgi_KA", &V0beta_b_Golgi_KA,
 "V0_ainf_Golgi_KA", &V0_ainf_Golgi_KA,
 "K_ainf_Golgi_KA", &K_ainf_Golgi_KA,
 "V0_binf_Golgi_KA", &V0_binf_Golgi_KA,
 "K_binf_Golgi_KA", &K_binf_Golgi_KA,
 "usetable_Golgi_KA", &usetable_Golgi_KA,
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
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"Golgi_KA",
 "gbar_Golgi_KA",
 "Q10_diff_Golgi_KA",
 "Q10_channel_Golgi_KA",
 0,
 "ik_Golgi_KA",
 "a_inf_Golgi_KA",
 "b_inf_Golgi_KA",
 "tau_a_Golgi_KA",
 "tau_b_Golgi_KA",
 "g_Golgi_KA",
 "tcorr_Golgi_KA",
 "gbar_Q10_Golgi_KA",
 "ic_Golgi_KA",
 0,
 "a_Golgi_KA",
 "b_Golgi_KA",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 23, _prop);
 	/*initialize range parameters*/
 	gbar = 0.008;
 	Q10_diff = 1.5;
 	Q10_channel = 3;
 	_prop->param = _p;
 	_prop->param_size = 23;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Golgi_KA_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
     _nrn_thread_table_reg(_mechtype, _check_table_thread);
  hoc_register_prop_size(_mechtype, 23, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Golgi_KA /home/neuron/projects/rete/control_sims/weasel/templates/golgi/x86_64/Golgi_KA.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double *_t_a_inf;
 static double *_t_tau_a;
 static double *_t_b_inf;
 static double *_t_tau_b;
static int _reset;
static char *modelname = "Cerebellum Golgi Cell Model";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_rate(_threadargsprotocomma_ double);
static int rate(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_rate(_threadargsprotocomma_ double _lv);
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   rate ( _threadargscomma_ v ) ;
   Da = ( a_inf - a ) / tau_a ;
   Db = ( b_inf - b ) / tau_b ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 rate ( _threadargscomma_ v ) ;
 Da = Da  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_a )) ;
 Db = Db  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_b )) ;
 return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   rate ( _threadargscomma_ v ) ;
    a = a + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_a)))*(- ( ( ( a_inf ) ) / tau_a ) / ( ( ( ( - 1.0) ) ) / tau_a ) - a) ;
    b = b + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_b)))*(- ( ( ( b_inf ) ) / tau_b ) / ( ( ( ( - 1.0) ) ) / tau_b ) - b) ;
   }
  return 0;
}
 
double alp_a ( _threadargsprotocomma_ double _lv ) {
   double _lalp_a;
 tcorr = pow( Q10_channel , ( ( celsius - 25.5 ) / 10.0 ) ) ;
   _lalp_a = tcorr * Aalpha_a * sigm ( _threadargscomma_ _lv - V0alpha_a , Kalpha_a ) ;
   
return _lalp_a;
 }
 
static void _hoc_alp_a(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alp_a ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double bet_a ( _threadargsprotocomma_ double _lv ) {
   double _lbet_a;
 tcorr = pow( Q10_channel , ( ( celsius - 25.5 ) / 10.0 ) ) ;
   _lbet_a = tcorr * Abeta_a / ( exp ( ( _lv - V0beta_a ) / Kbeta_a ) ) ;
   
return _lbet_a;
 }
 
static void _hoc_bet_a(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  bet_a ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double alp_b ( _threadargsprotocomma_ double _lv ) {
   double _lalp_b;
 tcorr = pow( Q10_channel , ( ( celsius - 25.5 ) / 10.0 ) ) ;
   _lalp_b = tcorr * Aalpha_b * sigm ( _threadargscomma_ _lv - V0alpha_b , Kalpha_b ) ;
   
return _lalp_b;
 }
 
static void _hoc_alp_b(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alp_b ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double bet_b ( _threadargsprotocomma_ double _lv ) {
   double _lbet_b;
 tcorr = pow( Q10_channel , ( ( celsius - 25.5 ) / 10.0 ) ) ;
   _lbet_b = tcorr * Abeta_b * sigm ( _threadargscomma_ _lv - V0beta_b , Kbeta_b ) ;
   
return _lbet_b;
 }
 
static void _hoc_bet_b(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  bet_b ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 static double _mfac_rate, _tmin_rate;
  static void _check_rate(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_Aalpha_a;
  static double _sav_Kalpha_a;
  static double _sav_V0alpha_a;
  static double _sav_Abeta_a;
  static double _sav_Kbeta_a;
  static double _sav_V0beta_a;
  static double _sav_Aalpha_b;
  static double _sav_Kalpha_b;
  static double _sav_V0alpha_b;
  static double _sav_Abeta_b;
  static double _sav_Kbeta_b;
  static double _sav_V0beta_b;
  static double _sav_celsius;
  if (!usetable) {return;}
  if (_sav_Aalpha_a != Aalpha_a) { _maktable = 1;}
  if (_sav_Kalpha_a != Kalpha_a) { _maktable = 1;}
  if (_sav_V0alpha_a != V0alpha_a) { _maktable = 1;}
  if (_sav_Abeta_a != Abeta_a) { _maktable = 1;}
  if (_sav_Kbeta_a != Kbeta_a) { _maktable = 1;}
  if (_sav_V0beta_a != V0beta_a) { _maktable = 1;}
  if (_sav_Aalpha_b != Aalpha_b) { _maktable = 1;}
  if (_sav_Kalpha_b != Kalpha_b) { _maktable = 1;}
  if (_sav_V0alpha_b != V0alpha_b) { _maktable = 1;}
  if (_sav_Abeta_b != Abeta_b) { _maktable = 1;}
  if (_sav_Kbeta_b != Kbeta_b) { _maktable = 1;}
  if (_sav_V0beta_b != V0beta_b) { _maktable = 1;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_rate =  - 100.0 ;
   _tmax =  30.0 ;
   _dx = (_tmax - _tmin_rate)/13000.; _mfac_rate = 1./_dx;
   for (_i=0, _x=_tmin_rate; _i < 13001; _x += _dx, _i++) {
    _f_rate(_p, _ppvar, _thread, _nt, _x);
    _t_a_inf[_i] = a_inf;
    _t_tau_a[_i] = tau_a;
    _t_b_inf[_i] = b_inf;
    _t_tau_b[_i] = tau_b;
   }
   _sav_Aalpha_a = Aalpha_a;
   _sav_Kalpha_a = Kalpha_a;
   _sav_V0alpha_a = V0alpha_a;
   _sav_Abeta_a = Abeta_a;
   _sav_Kbeta_a = Kbeta_a;
   _sav_V0beta_a = V0beta_a;
   _sav_Aalpha_b = Aalpha_b;
   _sav_Kalpha_b = Kalpha_b;
   _sav_V0alpha_b = V0alpha_b;
   _sav_Abeta_b = Abeta_b;
   _sav_Kbeta_b = Kbeta_b;
   _sav_V0beta_b = V0beta_b;
   _sav_celsius = celsius;
  }
 }

 static int rate(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _lv) { 
#if 0
_check_rate(_p, _ppvar, _thread, _nt);
#endif
 _n_rate(_p, _ppvar, _thread, _nt, _lv);
 return 0;
 }

 static void _n_rate(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_rate(_p, _ppvar, _thread, _nt, _lv); return; 
}
 _xi = _mfac_rate * (_lv - _tmin_rate);
 if (isnan(_xi)) {
  a_inf = _xi;
  tau_a = _xi;
  b_inf = _xi;
  tau_b = _xi;
  return;
 }
 if (_xi <= 0.) {
 a_inf = _t_a_inf[0];
 tau_a = _t_tau_a[0];
 b_inf = _t_b_inf[0];
 tau_b = _t_tau_b[0];
 return; }
 if (_xi >= 13000.) {
 a_inf = _t_a_inf[13000];
 tau_a = _t_tau_a[13000];
 b_inf = _t_b_inf[13000];
 tau_b = _t_tau_b[13000];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 a_inf = _t_a_inf[_i] + _theta*(_t_a_inf[_i+1] - _t_a_inf[_i]);
 tau_a = _t_tau_a[_i] + _theta*(_t_tau_a[_i+1] - _t_tau_a[_i]);
 b_inf = _t_b_inf[_i] + _theta*(_t_b_inf[_i+1] - _t_b_inf[_i]);
 tau_b = _t_tau_b[_i] + _theta*(_t_tau_b[_i+1] - _t_tau_b[_i]);
 }

 
static int  _f_rate ( _threadargsprotocomma_ double _lv ) {
   double _la_a , _lb_a , _la_b , _lb_b ;
 _la_a = alp_a ( _threadargscomma_ _lv ) ;
   _lb_a = bet_a ( _threadargscomma_ _lv ) ;
   _la_b = alp_b ( _threadargscomma_ _lv ) ;
   _lb_b = bet_b ( _threadargscomma_ _lv ) ;
   a_inf = 1.0 / ( 1.0 + exp ( ( _lv - V0_ainf ) / K_ainf ) ) ;
   tau_a = 1.0 / ( _la_a + _lb_a ) ;
   b_inf = 1.0 / ( 1.0 + exp ( ( _lv - V0_binf ) / K_binf ) ) ;
   tau_b = 1.0 / ( _la_b + _lb_b ) ;
    return 0; }
 
static void _hoc_rate(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 
#if 1
 _check_rate(_p, _ppvar, _thread, _nt);
#endif
 _r = 1.;
 rate ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double linoid ( _threadargsprotocomma_ double _lx , double _ly ) {
   double _llinoid;
 if ( fabs ( _lx / _ly ) < 1e-6 ) {
     _llinoid = _ly * ( 1.0 - _lx / _ly / 2.0 ) ;
     }
   else {
     if ( fabs ( _lx / _ly ) < 699.0 ) {
       _llinoid = _lx / ( exp ( _lx / _ly ) - 1.0 ) ;
       }
     else {
       if ( _lx / _ly > 0.0 ) {
         _llinoid = _lx / ( exp ( 699.0 ) - 1.0 ) ;
         }
       else {
         _llinoid = _lx / ( exp ( - 699.0 ) - 1.0 ) ;
         }
       }
     }
   
return _llinoid;
 }
 
static void _hoc_linoid(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  linoid ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double sigm ( _threadargsprotocomma_ double _lx , double _ly ) {
   double _lsigm;
 if ( fabs ( _lx / _ly ) < 699.0 ) {
     _lsigm = 1.0 / ( exp ( _lx / _ly ) + 1.0 ) ;
     }
   else {
     if ( _lx / _ly > 0.0 ) {
       _lsigm = 1.0 / ( exp ( 699.0 ) + 1.0 ) ;
       }
     else {
       _lsigm = 1.0 / ( exp ( - 699.0 ) + 1.0 ) ;
       }
     }
   
return _lsigm;
 }
 
static void _hoc_sigm(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  sigm ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
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
  ek = _ion_ek;
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  a = a0;
  b = b0;
 {
   gbar_Q10 = gbar * ( pow( Q10_diff , ( ( celsius - 23.0 ) / 10.0 ) ) ) ;
   rate ( _threadargscomma_ v ) ;
   a = a_inf ;
   b = b_inf ;
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

#if 0
 _check_rate(_p, _ppvar, _thread, _nt);
#endif
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
  ek = _ion_ek;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   g = gbar_Q10 * a * a * a * b ;
   ik = g * ( v - ek ) ;
   ic = ik ;
   alpha_a = alp_a ( _threadargscomma_ v ) ;
   beta_a = bet_a ( _threadargscomma_ v ) ;
   alpha_b = alp_b ( _threadargscomma_ v ) ;
   beta_b = bet_b ( _threadargscomma_ v ) ;
   }
 _current += ik;

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
  ek = _ion_ek;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
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
  ek = _ion_ek;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(a) - _p;  _dlist1[0] = &(Da) - _p;
 _slist1[1] = &(b) - _p;  _dlist1[1] = &(Db) - _p;
   _t_a_inf = makevector(13001*sizeof(double));
   _t_tau_a = makevector(13001*sizeof(double));
   _t_b_inf = makevector(13001*sizeof(double));
   _t_tau_b = makevector(13001*sizeof(double));
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

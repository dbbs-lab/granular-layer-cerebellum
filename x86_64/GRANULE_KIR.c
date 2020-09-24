/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
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
 
#define nrn_init _nrn_init__GRANULE_KIR
#define _nrn_initial _nrn_initial__GRANULE_KIR
#define nrn_cur _nrn_cur__GRANULE_KIR
#define _nrn_current _nrn_current__GRANULE_KIR
#define nrn_jacob _nrn_jacob__GRANULE_KIR
#define nrn_state _nrn_state__GRANULE_KIR
#define _net_receive _net_receive__GRANULE_KIR 
#define _f_rate _f_rate__GRANULE_KIR 
#define rate rate__GRANULE_KIR 
#define states states__GRANULE_KIR 
 
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
#define Aalpha_d _p[0]
#define Kalpha_d _p[1]
#define V0alpha_d _p[2]
#define Abeta_d _p[3]
#define Kbeta_d _p[4]
#define V0beta_d _p[5]
#define Q10_diff _p[6]
#define Q10_channel _p[7]
#define gbar _p[8]
#define ic _p[9]
#define d_inf _p[10]
#define tau_d _p[11]
#define g _p[12]
#define alpha_d _p[13]
#define beta_d _p[14]
#define gbar_Q10 _p[15]
#define d _p[16]
#define ek _p[17]
#define Dd _p[18]
#define ik _p[19]
#define v _p[20]
#define _g _p[21]
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
 static void _hoc_alp_d(void);
 static void _hoc_bet_d(void);
 static void _hoc_rate(void);
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
 "setdata_GRANULE_KIR", _hoc_setdata,
 "alp_d_GRANULE_KIR", _hoc_alp_d,
 "bet_d_GRANULE_KIR", _hoc_bet_d,
 "rate_GRANULE_KIR", _hoc_rate,
 0, 0
};
#define alp_d alp_d_GRANULE_KIR
#define bet_d bet_d_GRANULE_KIR
 extern double alp_d( _threadargsprotocomma_ double );
 extern double bet_d( _threadargsprotocomma_ double );
 
static void _check_rate(double*, Datum*, Datum*, _NrnThread*); 
static void _check_table_thread(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, int _type) {
   _check_rate(_p, _ppvar, _thread, _nt);
 }
 /* declare global and static user variables */
#define usetable usetable_GRANULE_KIR
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_GRANULE_KIR", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Aalpha_d_GRANULE_KIR", "/ms",
 "Kalpha_d_GRANULE_KIR", "mV",
 "V0alpha_d_GRANULE_KIR", "mV",
 "Abeta_d_GRANULE_KIR", "/ms",
 "Kbeta_d_GRANULE_KIR", "mV",
 "V0beta_d_GRANULE_KIR", "mV",
 "gbar_GRANULE_KIR", "mho/cm2",
 "ic_GRANULE_KIR", "mA/cm2",
 "tau_d_GRANULE_KIR", "ms",
 "g_GRANULE_KIR", "mho/cm2",
 "alpha_d_GRANULE_KIR", "/ms",
 "beta_d_GRANULE_KIR", "/ms",
 "gbar_Q10_GRANULE_KIR", "mho/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double d0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "usetable_GRANULE_KIR", &usetable_GRANULE_KIR,
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
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"GRANULE_KIR",
 "Aalpha_d_GRANULE_KIR",
 "Kalpha_d_GRANULE_KIR",
 "V0alpha_d_GRANULE_KIR",
 "Abeta_d_GRANULE_KIR",
 "Kbeta_d_GRANULE_KIR",
 "V0beta_d_GRANULE_KIR",
 "Q10_diff_GRANULE_KIR",
 "Q10_channel_GRANULE_KIR",
 "gbar_GRANULE_KIR",
 0,
 "ic_GRANULE_KIR",
 "d_inf_GRANULE_KIR",
 "tau_d_GRANULE_KIR",
 "g_GRANULE_KIR",
 "alpha_d_GRANULE_KIR",
 "beta_d_GRANULE_KIR",
 "gbar_Q10_GRANULE_KIR",
 0,
 "d_GRANULE_KIR",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 22, _prop);
 	/*initialize range parameters*/
 	Aalpha_d = 0.13289;
 	Kalpha_d = -24.3902;
 	V0alpha_d = -83.94;
 	Abeta_d = 0.16994;
 	Kbeta_d = 35.714;
 	V0beta_d = -83.94;
 	Q10_diff = 1.5;
 	Q10_channel = 3;
 	gbar = 0.00135;
 	_prop->param = _p;
 	_prop->param_size = 22;
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
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _GRANULE_KIR_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
     _nrn_thread_table_reg(_mechtype, _check_table_thread);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 22, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 GRANULE_KIR /home/stefano/Documenti/paperRevision/GL_Model/x86_64/GRANULE_KIR.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double *_t_d_inf;
 static double *_t_tau_d;
static int _reset;
static char *modelname = "Cerebellum Granule Cell Model";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_rate(_threadargsprotocomma_ double);
static int rate(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_rate(_threadargsprotocomma_ double _lv);
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   rate ( _threadargscomma_ v ) ;
   Dd = ( d_inf - d ) / tau_d ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 rate ( _threadargscomma_ v ) ;
 Dd = Dd  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_d )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   rate ( _threadargscomma_ v ) ;
    d = d + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_d)))*(- ( ( ( d_inf ) ) / tau_d ) / ( ( ( ( - 1.0 ) ) ) / tau_d ) - d) ;
   }
  return 0;
}
 
double alp_d ( _threadargsprotocomma_ double _lv ) {
   double _lalp_d;
 double _lQ10 ;
 _lQ10 = pow( Q10_channel , ( ( celsius - 20.0 ) / 10.0 ) ) ;
   _lalp_d = _lQ10 * Aalpha_d * exp ( ( _lv - V0alpha_d ) / Kalpha_d ) ;
   
return _lalp_d;
 }
 
static void _hoc_alp_d(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alp_d ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double bet_d ( _threadargsprotocomma_ double _lv ) {
   double _lbet_d;
 double _lQ10 ;
 _lQ10 = pow( Q10_channel , ( ( celsius - 20.0 ) / 10.0 ) ) ;
   _lbet_d = _lQ10 * Abeta_d * exp ( ( _lv - V0beta_d ) / Kbeta_d ) ;
   
return _lbet_d;
 }
 
static void _hoc_bet_d(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  bet_d ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 static double _mfac_rate, _tmin_rate;
  static void _check_rate(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_Aalpha_d;
  static double _sav_Kalpha_d;
  static double _sav_V0alpha_d;
  static double _sav_Abeta_d;
  static double _sav_Kbeta_d;
  static double _sav_V0beta_d;
  static double _sav_celsius;
  if (!usetable) {return;}
  if (_sav_Aalpha_d != Aalpha_d) { _maktable = 1;}
  if (_sav_Kalpha_d != Kalpha_d) { _maktable = 1;}
  if (_sav_V0alpha_d != V0alpha_d) { _maktable = 1;}
  if (_sav_Abeta_d != Abeta_d) { _maktable = 1;}
  if (_sav_Kbeta_d != Kbeta_d) { _maktable = 1;}
  if (_sav_V0beta_d != V0beta_d) { _maktable = 1;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_rate =  - 100.0 ;
   _tmax =  30.0 ;
   _dx = (_tmax - _tmin_rate)/13000.; _mfac_rate = 1./_dx;
   for (_i=0, _x=_tmin_rate; _i < 13001; _x += _dx, _i++) {
    _f_rate(_p, _ppvar, _thread, _nt, _x);
    _t_d_inf[_i] = d_inf;
    _t_tau_d[_i] = tau_d;
   }
   _sav_Aalpha_d = Aalpha_d;
   _sav_Kalpha_d = Kalpha_d;
   _sav_V0alpha_d = V0alpha_d;
   _sav_Abeta_d = Abeta_d;
   _sav_Kbeta_d = Kbeta_d;
   _sav_V0beta_d = V0beta_d;
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
  d_inf = _xi;
  tau_d = _xi;
  return;
 }
 if (_xi <= 0.) {
 d_inf = _t_d_inf[0];
 tau_d = _t_tau_d[0];
 return; }
 if (_xi >= 13000.) {
 d_inf = _t_d_inf[13000];
 tau_d = _t_tau_d[13000];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 d_inf = _t_d_inf[_i] + _theta*(_t_d_inf[_i+1] - _t_d_inf[_i]);
 tau_d = _t_tau_d[_i] + _theta*(_t_tau_d[_i+1] - _t_tau_d[_i]);
 }

 
static int  _f_rate ( _threadargsprotocomma_ double _lv ) {
   double _la_d , _lb_d ;
 _la_d = alp_d ( _threadargscomma_ _lv ) ;
   _lb_d = bet_d ( _threadargscomma_ _lv ) ;
   tau_d = 1.0 / ( _la_d + _lb_d ) ;
   d_inf = _la_d / ( _la_d + _lb_d ) ;
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
 
static int _ode_count(int _type){ return 1;}
 
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
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
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
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  d = d0;
 {
   gbar_Q10 = gbar * ( pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ) ;
   rate ( _threadargscomma_ v ) ;
   d = d_inf ;
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
   g = gbar_Q10 * d ;
   ik = g * ( v - ek ) ;
   ic = ik ;
   alpha_d = alp_d ( _threadargscomma_ v ) ;
   beta_d = bet_d ( _threadargscomma_ v ) ;
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
 _slist1[0] = &(d) - _p;  _dlist1[0] = &(Dd) - _p;
   _t_d_inf = makevector(13001*sizeof(double));
   _t_tau_d = makevector(13001*sizeof(double));
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/stefano/Documenti/paperRevision/GL_Model/templates/granule/GRANULE_KIR.mod";
static const char* nmodl_file_text = 
  "TITLE Cerebellum Granule Cell Model\n"
  "\n"
  "COMMENT\n"
  "        Kir channel\n"
  "   \n"
  "	Author: E.D'Angelo, T.Nieus, A. Fontana\n"
  "	Last revised: 8.10.2000\n"
  "	Old values:\n"
  "			gkbar = 0.0003 (mho/cm2) \n"
  "			\n"
  "ENDCOMMENT\n"
  " \n"
  "NEURON { \n"
  "	SUFFIX GRANULE_KIR\n"
  "	USEION k READ ek WRITE ik \n"
  "	RANGE Q10_diff,Q10_channel,gbar_Q10\n"
  "	RANGE gbar, ic, g, alpha_d, beta_d \n"
  "	RANGE Aalpha_d, Kalpha_d, V0alpha_d\n"
  "	RANGE Abeta_d, Kbeta_d, V0beta_d\n"
  "	RANGE d_inf, tau_d \n"
  "} \n"
  " \n"
  "UNITS { \n"
  "	(mA) = (milliamp) \n"
  "	(mV) = (millivolt) \n"
  "} \n"
  " \n"
  "PARAMETER { \n"
  "	Aalpha_d = 0.13289 (/ms)\n"
  "\n"
  "	Kalpha_d = -24.3902 (mV)\n"
  "\n"
  "	V0alpha_d = -83.94 (mV)\n"
  "	Abeta_d = 0.16994 (/ms)\n"
  "\n"
  "	Kbeta_d = 35.714 (mV)\n"
  "\n"
  "	V0beta_d = -83.94 (mV)\n"
  "	v (mV) \n"
  "	Q10_diff	= 1.5\n"
  "	Q10_channel	= 3\n"
  "	gbar = 0.00135 (mho/cm2) : increased by 150% for Jorntell\n"
  "	ek = -84.69 (mV) \n"
  "	celsius (degC)\n"
  "} \n"
  "\n"
  "STATE { \n"
  "	d \n"
  "} \n"
  "\n"
  "ASSIGNED { \n"
  "	ik (mA/cm2) \n"
  "	ic (mA/cm2) \n"
  "	d_inf \n"
  "	tau_d (ms) \n"
  "	g (mho/cm2) \n"
  "	alpha_d (/ms) \n"
  "	beta_d (/ms) \n"
  "	gbar_Q10 (mho/cm2)\n"
  "} \n"
  " \n"
  "INITIAL { \n"
  "	gbar_Q10 = gbar*(Q10_diff^((celsius-30)/10))\n"
  "	rate(v) \n"
  "	d = d_inf \n"
  "} \n"
  " \n"
  "BREAKPOINT { \n"
  "	SOLVE states METHOD cnexp\n"
  "	g = gbar_Q10*d   : primo ordine!!!\n"
  "	ik = g*(v - ek) \n"
  "	ic = ik\n"
  "	alpha_d = alp_d(v) \n"
  "	beta_d = bet_d(v) \n"
  "} \n"
  " \n"
  "DERIVATIVE states { \n"
  "	rate(v) \n"
  "	d' =(d_inf - d)/tau_d \n"
  "} \n"
  " \n"
  "FUNCTION alp_d(v(mV))(/ms) { LOCAL Q10\n"
  "	Q10 = Q10_channel^((celsius-20(degC))/10(degC))\n"
  "	alp_d = Q10*Aalpha_d*exp((v-V0alpha_d)/Kalpha_d) \n"
  "} \n"
  " \n"
  "FUNCTION bet_d(v(mV))(/ms) { LOCAL Q10\n"
  "	Q10 = Q10_channel^((celsius-20(degC))/10(degC))\n"
  "	bet_d = Q10*Abeta_d*exp((v-V0beta_d)/Kbeta_d) \n"
  "} \n"
  " \n"
  "PROCEDURE rate(v (mV)) {LOCAL a_d, b_d \n"
  "	TABLE d_inf, tau_d  \n"
  "	DEPEND Aalpha_d, Kalpha_d, V0alpha_d, \n"
  "	       Abeta_d, Kbeta_d, V0beta_d, celsius FROM -100 TO 30 WITH 13000 \n"
  "	a_d = alp_d(v)  \n"
  "	b_d = bet_d(v) \n"
  "	tau_d = 1/(a_d + b_d) \n"
  "	d_inf = a_d/(a_d + b_d) \n"
  "} \n"
  "\n"
  ;
#endif

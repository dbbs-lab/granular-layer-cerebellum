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
 
#define nrn_init _nrn_init__Golgi_KM
#define _nrn_initial _nrn_initial__Golgi_KM
#define nrn_cur _nrn_cur__Golgi_KM
#define _nrn_current _nrn_current__Golgi_KM
#define nrn_jacob _nrn_jacob__Golgi_KM
#define nrn_state _nrn_state__Golgi_KM
#define _net_receive _net_receive__Golgi_KM 
#define _f_rate _f_rate__Golgi_KM 
#define rate rate__Golgi_KM 
#define states states__Golgi_KM 
 
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
#define n_inf _p[4]
#define tau_n _p[5]
#define g _p[6]
#define tcorr _p[7]
#define gbar_Q10 _p[8]
#define ic _p[9]
#define n _p[10]
#define ek _p[11]
#define Dn _p[12]
#define alpha_n _p[13]
#define beta_n _p[14]
#define v _p[15]
#define _g _p[16]
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
 static void _hoc_alp_n(void);
 static void _hoc_bet_n(void);
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
 "setdata_Golgi_KM", _hoc_setdata,
 "alp_n_Golgi_KM", _hoc_alp_n,
 "bet_n_Golgi_KM", _hoc_bet_n,
 "rate_Golgi_KM", _hoc_rate,
 0, 0
};
#define alp_n alp_n_Golgi_KM
#define bet_n bet_n_Golgi_KM
 extern double alp_n( _threadargsprotocomma_ double );
 extern double bet_n( _threadargsprotocomma_ double );
 
static void _check_rate(double*, Datum*, Datum*, _NrnThread*); 
static void _check_table_thread(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, int _type) {
   _check_rate(_p, _ppvar, _thread, _nt);
 }
 #define _zdelta _thread[0]._pval[0]
 #define _zq10 _thread[0]._pval[1]
 /* declare global and static user variables */
#define Abeta_n Abeta_n_Golgi_KM
 double Abeta_n = 0.0033;
#define Aalpha_n Aalpha_n_Golgi_KM
 double Aalpha_n = 0.0033;
#define B_ninf B_ninf_Golgi_KM
 double B_ninf = 6;
#define Kbeta_n Kbeta_n_Golgi_KM
 double Kbeta_n = -20;
#define Kalpha_n Kalpha_n_Golgi_KM
 double Kalpha_n = 40;
#define V0_ninf V0_ninf_Golgi_KM
 double V0_ninf = -35;
#define V0beta_n V0beta_n_Golgi_KM
 double V0beta_n = -30;
#define V0alpha_n V0alpha_n_Golgi_KM
 double V0alpha_n = -30;
#define usetable usetable_Golgi_KM
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_Golgi_KM", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Aalpha_n_Golgi_KM", "/ms",
 "Kalpha_n_Golgi_KM", "mV",
 "V0alpha_n_Golgi_KM", "mV",
 "Abeta_n_Golgi_KM", "/ms",
 "Kbeta_n_Golgi_KM", "mV",
 "V0beta_n_Golgi_KM", "mV",
 "V0_ninf_Golgi_KM", "mV",
 "B_ninf_Golgi_KM", "mV",
 "gbar_Golgi_KM", "mho/cm2",
 "ik_Golgi_KM", "mA/cm2",
 "tau_n_Golgi_KM", "ms",
 "g_Golgi_KM", "mho/cm2",
 "tcorr_Golgi_KM", "1",
 "gbar_Q10_Golgi_KM", "mho/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double n0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "Aalpha_n_Golgi_KM", &Aalpha_n_Golgi_KM,
 "Kalpha_n_Golgi_KM", &Kalpha_n_Golgi_KM,
 "V0alpha_n_Golgi_KM", &V0alpha_n_Golgi_KM,
 "Abeta_n_Golgi_KM", &Abeta_n_Golgi_KM,
 "Kbeta_n_Golgi_KM", &Kbeta_n_Golgi_KM,
 "V0beta_n_Golgi_KM", &V0beta_n_Golgi_KM,
 "V0_ninf_Golgi_KM", &V0_ninf_Golgi_KM,
 "B_ninf_Golgi_KM", &B_ninf_Golgi_KM,
 "usetable_Golgi_KM", &usetable_Golgi_KM,
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
"Golgi_KM",
 "gbar_Golgi_KM",
 "Q10_diff_Golgi_KM",
 "Q10_channel_Golgi_KM",
 0,
 "ik_Golgi_KM",
 "n_inf_Golgi_KM",
 "tau_n_Golgi_KM",
 "g_Golgi_KM",
 "tcorr_Golgi_KM",
 "gbar_Q10_Golgi_KM",
 "ic_Golgi_KM",
 0,
 "n_Golgi_KM",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 17, _prop);
 	/*initialize range parameters*/
 	gbar = 0.001;
 	Q10_diff = 1.5;
 	Q10_channel = 3;
 	_prop->param = _p;
 	_prop->param_size = 17;
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
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Golgi_KM_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 2);
  _extcall_thread = (Datum*)ecalloc(1, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
     _nrn_thread_table_reg(_mechtype, _check_table_thread);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 17, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Golgi_KM /home/stefano/Documenti/paperRevision/GL_Model/x86_64/Golgi_KM.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 /*Top LOCAL _zdelta */
 /*Top LOCAL _zq10 */
 static double *_t_n_inf;
 static double *_t_tau_n;
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
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   rate ( _threadargscomma_ v ) ;
   Dn = ( n_inf - n ) / tau_n ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 rate ( _threadargscomma_ v ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_n )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   rate ( _threadargscomma_ v ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( n_inf ) ) / tau_n ) / ( ( ( ( - 1.0 ) ) ) / tau_n ) - n) ;
   }
  return 0;
}
 
double alp_n ( _threadargsprotocomma_ double _lv ) {
   double _lalp_n;
 _lalp_n = Aalpha_n * exp ( ( _lv - V0alpha_n ) / Kalpha_n ) ;
   
return _lalp_n;
 }
 
static void _hoc_alp_n(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alp_n ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double bet_n ( _threadargsprotocomma_ double _lv ) {
   double _lbet_n;
 _lbet_n = Abeta_n * exp ( ( _lv - V0beta_n ) / Kbeta_n ) ;
   
return _lbet_n;
 }
 
static void _hoc_bet_n(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  bet_n ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 static double _mfac_rate, _tmin_rate;
  static void _check_rate(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_Aalpha_n;
  static double _sav_Kalpha_n;
  static double _sav_V0alpha_n;
  static double _sav_Abeta_n;
  static double _sav_Kbeta_n;
  static double _sav_V0beta_n;
  static double _sav_V0_ninf;
  static double _sav_B_ninf;
  static double _sav_celsius;
  if (!usetable) {return;}
  if (_sav_Aalpha_n != Aalpha_n) { _maktable = 1;}
  if (_sav_Kalpha_n != Kalpha_n) { _maktable = 1;}
  if (_sav_V0alpha_n != V0alpha_n) { _maktable = 1;}
  if (_sav_Abeta_n != Abeta_n) { _maktable = 1;}
  if (_sav_Kbeta_n != Kbeta_n) { _maktable = 1;}
  if (_sav_V0beta_n != V0beta_n) { _maktable = 1;}
  if (_sav_V0_ninf != V0_ninf) { _maktable = 1;}
  if (_sav_B_ninf != B_ninf) { _maktable = 1;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_rate =  - 100.0 ;
   _tmax =  30.0 ;
   _dx = (_tmax - _tmin_rate)/13000.; _mfac_rate = 1./_dx;
   for (_i=0, _x=_tmin_rate; _i < 13001; _x += _dx, _i++) {
    _f_rate(_p, _ppvar, _thread, _nt, _x);
    _t_n_inf[_i] = n_inf;
    _t_tau_n[_i] = tau_n;
   }
   _sav_Aalpha_n = Aalpha_n;
   _sav_Kalpha_n = Kalpha_n;
   _sav_V0alpha_n = V0alpha_n;
   _sav_Abeta_n = Abeta_n;
   _sav_Kbeta_n = Kbeta_n;
   _sav_V0beta_n = V0beta_n;
   _sav_V0_ninf = V0_ninf;
   _sav_B_ninf = B_ninf;
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
  n_inf = _xi;
  tau_n = _xi;
  return;
 }
 if (_xi <= 0.) {
 n_inf = _t_n_inf[0];
 tau_n = _t_tau_n[0];
 return; }
 if (_xi >= 13000.) {
 n_inf = _t_n_inf[13000];
 tau_n = _t_tau_n[13000];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 n_inf = _t_n_inf[_i] + _theta*(_t_n_inf[_i+1] - _t_n_inf[_i]);
 tau_n = _t_tau_n[_i] + _theta*(_t_tau_n[_i+1] - _t_tau_n[_i]);
 }

 
static int  _f_rate ( _threadargsprotocomma_ double _lv ) {
   double _la_n , _lb_n , _ls_n ;
 _la_n = alp_n ( _threadargscomma_ _lv ) ;
   _lb_n = bet_n ( _threadargscomma_ _lv ) ;
   tcorr = pow( Q10_diff , ( ( celsius - 22.0 ) / 10.0 ) ) ;
   _ls_n = tcorr * ( _la_n + _lb_n ) ;
   tau_n = 1.0 / _ls_n ;
   n_inf = 1.0 / ( 1.0 + exp ( - ( _lv - V0_ninf ) / B_ninf ) ) ;
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
 
static void _thread_mem_init(Datum* _thread) {
   _thread[0]._pval = (double*)ecalloc(2, sizeof(double));
 }
 
static void _thread_cleanup(Datum* _thread) {
   free((void*)(_thread[0]._pval));
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  n = n0;
 {
   gbar_Q10 = gbar * ( pow( Q10_diff , ( ( celsius - 23.0 ) / 10.0 ) ) ) ;
   rate ( _threadargscomma_ v ) ;
   n = n_inf ;
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
   g = gbar_Q10 * n ;
   ik = g * ( v - ek ) ;
   ic = ik ;
   alpha_n = alp_n ( _threadargscomma_ v ) ;
   beta_n = bet_n ( _threadargscomma_ v ) ;
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
 _slist1[0] = &(n) - _p;  _dlist1[0] = &(Dn) - _p;
   _t_n_inf = makevector(13001*sizeof(double));
   _t_tau_n = makevector(13001*sizeof(double));
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/stefano/Documenti/paperRevision/GL_Model/templates/golgi/Golgi_KM.mod";
static const char* nmodl_file_text = 
  "TITLE Cerebellum Golgi Cell Model\n"
  "\n"
  "COMMENT\n"
  "        K-slow channel\n"
  "   \n"
  "	Author: E.DAngelo, T.Nieus, A. Fontana\n"
  "	Last revised: 8.5.2000\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON { \n"
  "	SUFFIX Golgi_KM \n"
  "	USEION k READ ek WRITE ik \n"
  "	RANGE Q10_diff,Q10_channel,gbar_Q10\n"
  "	RANGE gbar, ik, g\n"
  "	:RANGE Aalpha_n, Kalpha_n, V0alpha_n, alpha_n, beta_n \n"
  "	:RANGE Abeta_n, Kbeta_n, V0beta_n\n"
  "	:RANGE V0_ninf, B_ninf\n"
  "	RANGE n, n_inf, tau_n, tcorr, ic\n"
  "} \n"
  " \n"
  "UNITS { \n"
  "	(mA) = (milliamp) \n"
  "	(mV) = (millivolt) \n"
  "} \n"
  " \n"
  "PARAMETER { \n"
  "	Aalpha_n = 0.0033 (/ms)\n"
  "	Kalpha_n = 40 (mV)\n"
  "	V0alpha_n = -30 (mV)\n"
  "	\n"
  "	Abeta_n = 0.0033 (/ms)\n"
  "	Kbeta_n = -20 (mV)\n"
  "	V0beta_n = -30 (mV)\n"
  "	\n"
  "	V0_ninf = -35 (mV)\n"
  "	B_ninf =  6 (mV)\n"
  "	\n"
  "	gbar= 0.001 (mho/cm2)\n"
  "	ek   (mV)\n"
  "	celsius (degC) \n"
  "	Q10_diff	= 1.5\n"
  "	Q10_channel	= 3\n"
  "}\n"
  "\n"
  "STATE { \n"
  "	n \n"
  "} \n"
  "\n"
  "ASSIGNED { \n"
  "	v (mV) \n"
  "	ik (mA/cm2) \n"
  "	n_inf \n"
  "	tau_n (ms) \n"
  "	g (mho/cm2) \n"
  "	alpha_n (/ms) \n"
  "	beta_n (/ms) \n"
  "	tcorr (1)\n"
  "	gbar_Q10 (mho/cm2)\n"
  "	ic\n"
  "} \n"
  " \n"
  "INITIAL { \n"
  "	gbar_Q10 = gbar*(Q10_diff^((celsius-23)/10))\n"
  "	rate(v) \n"
  "	n = n_inf \n"
  "} \n"
  " \n"
  "BREAKPOINT { \n"
  "	SOLVE states METHOD cnexp \n"
  "	g = gbar_Q10*n \n"
  "	ik = g*(v - ek) \n"
  "	ic = ik\n"
  "	alpha_n = alp_n(v) \n"
  "	beta_n = bet_n(v) \n"
  "} \n"
  " \n"
  "DERIVATIVE states { \n"
  "	rate(v) \n"
  "	n' =(n_inf - n)/tau_n \n"
  "} \n"
  " \n"
  "FUNCTION alp_n(v(mV))(/ms) { \n"
  "	alp_n = Aalpha_n*exp((v-V0alpha_n)/Kalpha_n) \n"
  "} \n"
  " \n"
  "FUNCTION bet_n(v(mV))(/ms) { \n"
  "	bet_n = Abeta_n*exp((v-V0beta_n)/Kbeta_n) \n"
  "} \n"
  "\n"
  "UNITSOFF\n"
  "\n"
  "LOCAL delta\n"
  "LOCAL q10\n"
  " \n"
  "PROCEDURE rate(v (mV)) {LOCAL a_n, b_n, s_n  \n"
  "	TABLE n_inf, tau_n \n"
  "	DEPEND Aalpha_n, Kalpha_n, V0alpha_n, \n"
  "	       Abeta_n, Kbeta_n, V0beta_n, V0_ninf, B_ninf, celsius FROM -100 TO 30 WITH 13000 \n"
  "	a_n = alp_n(v)  \n"
  "	b_n = bet_n(v)\n"
  "\n"
  "	tcorr = Q10_diff^((celsius - 22)/10)\n"
  "	s_n = tcorr*(a_n + b_n) \n"
  "	tau_n = 1/s_n\n"
  " \n"
  ":  n_inf = a_n/(a_n + b_n) \n"
  "	n_inf = 1/(1+exp(-(v-V0_ninf)/B_ninf))\n"
  "} \n"
  "\n"
  ;
#endif

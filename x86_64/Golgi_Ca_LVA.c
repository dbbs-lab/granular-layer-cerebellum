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
 
#define nrn_init _nrn_init__Golgi_Ca_LVA
#define _nrn_initial _nrn_initial__Golgi_Ca_LVA
#define nrn_cur _nrn_cur__Golgi_Ca_LVA
#define _nrn_current _nrn_current__Golgi_Ca_LVA
#define nrn_jacob _nrn_jacob__Golgi_Ca_LVA
#define nrn_state _nrn_state__Golgi_Ca_LVA
#define _net_receive _net_receive__Golgi_Ca_LVA 
#define _f_evaluate_fct _f_evaluate_fct__Golgi_Ca_LVA 
#define ca2state ca2state__Golgi_Ca_LVA 
#define evaluate_fct evaluate_fct__Golgi_Ca_LVA 
 
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
#define shift _p[1]
#define Q10_diff _p[2]
#define Q10_channel _p[3]
#define ica2 _p[4]
#define ca2rev _p[5]
#define g _p[6]
#define m_inf _p[7]
#define tau_m _p[8]
#define h_inf _p[9]
#define tau_h _p[10]
#define phi_m _p[11]
#define phi_h _p[12]
#define gbar_Q10 _p[13]
#define ic _p[14]
#define m _p[15]
#define h _p[16]
#define ca2i _p[17]
#define ca2o _p[18]
#define Dm _p[19]
#define Dh _p[20]
#define v _p[21]
#define _g _p[22]
#define _ion_ca2i	*_ppvar[0]._pval
#define _ion_ca2o	*_ppvar[1]._pval
#define _ion_ica2	*_ppvar[2]._pval
#define _ion_dica2dv	*_ppvar[3]._pval
 
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
 static void _hoc_evaluate_fct(void);
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
 "setdata_Golgi_Ca_LVA", _hoc_setdata,
 "evaluate_fct_Golgi_Ca_LVA", _hoc_evaluate_fct,
 0, 0
};
 
static void _check_evaluate_fct(double*, Datum*, Datum*, _NrnThread*); 
static void _check_table_thread(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, int _type) {
   _check_evaluate_fct(_p, _ppvar, _thread, _nt);
 }
 /* declare global and static user variables */
#define eca2 eca2_Golgi_Ca_LVA
 double eca2 = 0;
#define usetable usetable_Golgi_Ca_LVA
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_Golgi_Ca_LVA", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "eca2_Golgi_Ca_LVA", "mV",
 "gbar_Golgi_Ca_LVA", "mho/cm2",
 "shift_Golgi_Ca_LVA", "mV",
 "ica2_Golgi_Ca_LVA", "mA/cm2",
 "ca2rev_Golgi_Ca_LVA", "mV",
 "g_Golgi_Ca_LVA", "mho/cm2",
 "tau_m_Golgi_Ca_LVA", "ms",
 "tau_h_Golgi_Ca_LVA", "ms",
 "gbar_Q10_Golgi_Ca_LVA", "mho/cm2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double m0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "eca2_Golgi_Ca_LVA", &eca2_Golgi_Ca_LVA,
 "usetable_Golgi_Ca_LVA", &usetable_Golgi_Ca_LVA,
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
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Golgi_Ca_LVA",
 "gbar_Golgi_Ca_LVA",
 "shift_Golgi_Ca_LVA",
 "Q10_diff_Golgi_Ca_LVA",
 "Q10_channel_Golgi_Ca_LVA",
 0,
 "ica2_Golgi_Ca_LVA",
 "ca2rev_Golgi_Ca_LVA",
 "g_Golgi_Ca_LVA",
 "m_inf_Golgi_Ca_LVA",
 "tau_m_Golgi_Ca_LVA",
 "h_inf_Golgi_Ca_LVA",
 "tau_h_Golgi_Ca_LVA",
 "phi_m_Golgi_Ca_LVA",
 "phi_h_Golgi_Ca_LVA",
 "gbar_Q10_Golgi_Ca_LVA",
 "ic_Golgi_Ca_LVA",
 0,
 "m_Golgi_Ca_LVA",
 "h_Golgi_Ca_LVA",
 0,
 0};
 static Symbol* _ca2_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 23, _prop);
 	/*initialize range parameters*/
 	gbar = 0.00025;
 	shift = 2;
 	Q10_diff = 1.5;
 	Q10_channel = 3;
 	_prop->param = _p;
 	_prop->param_size = 23;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca2_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* ca2i */
 	_ppvar[1]._pval = &prop_ion->param[2]; /* ca2o */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ica2 */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dica2dv */
 
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

 void _Golgi_Ca_LVA_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca2", 2.0);
 	_ca2_sym = hoc_lookup("ca2_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
     _nrn_thread_table_reg(_mechtype, _check_table_thread);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 23, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "ca2_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca2_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca2_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca2_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Golgi_Ca_LVA /home/stefano/Documenti/paperRevision/GL_Model/x86_64/Golgi_Ca_LVA.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.3145;
 static double *_t_m_inf;
 static double *_t_tau_m;
 static double *_t_h_inf;
 static double *_t_tau_h;
static int _reset;
static char *modelname = "Low threshold calcium current Cerebellum Golgi Cell Model";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_evaluate_fct(_threadargsprotocomma_ double);
static int evaluate_fct(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_evaluate_fct(_threadargsprotocomma_ double _lv);
 static int _slist1[2], _dlist1[2];
 static int ca2state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   evaluate_fct ( _threadargscomma_ v ) ;
   Dm = ( m_inf - m ) / tau_m ;
   Dh = ( h_inf - h ) / tau_h ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 evaluate_fct ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_m )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_h )) ;
  return 0;
}
 /*END CVODE*/
 static int ca2state (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   evaluate_fct ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( m_inf ) ) / tau_m ) / ( ( ( ( - 1.0 ) ) ) / tau_m ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( h_inf ) ) / tau_h ) / ( ( ( ( - 1.0 ) ) ) / tau_h ) - h) ;
   }
  return 0;
}
 static double _mfac_evaluate_fct, _tmin_evaluate_fct;
  static void _check_evaluate_fct(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_celsius;
  static double _sav_shift;
  static double _sav_phi_m;
  static double _sav_phi_h;
  if (!usetable) {return;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_sav_shift != shift) { _maktable = 1;}
  if (_sav_phi_m != phi_m) { _maktable = 1;}
  if (_sav_phi_h != phi_h) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_evaluate_fct =  - 100.0 ;
   _tmax =  30.0 ;
   _dx = (_tmax - _tmin_evaluate_fct)/13000.; _mfac_evaluate_fct = 1./_dx;
   for (_i=0, _x=_tmin_evaluate_fct; _i < 13001; _x += _dx, _i++) {
    _f_evaluate_fct(_p, _ppvar, _thread, _nt, _x);
    _t_m_inf[_i] = m_inf;
    _t_tau_m[_i] = tau_m;
    _t_h_inf[_i] = h_inf;
    _t_tau_h[_i] = tau_h;
   }
   _sav_celsius = celsius;
   _sav_shift = shift;
   _sav_phi_m = phi_m;
   _sav_phi_h = phi_h;
  }
 }

 static int evaluate_fct(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _lv) { 
#if 0
_check_evaluate_fct(_p, _ppvar, _thread, _nt);
#endif
 _n_evaluate_fct(_p, _ppvar, _thread, _nt, _lv);
 return 0;
 }

 static void _n_evaluate_fct(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_evaluate_fct(_p, _ppvar, _thread, _nt, _lv); return; 
}
 _xi = _mfac_evaluate_fct * (_lv - _tmin_evaluate_fct);
 if (isnan(_xi)) {
  m_inf = _xi;
  tau_m = _xi;
  h_inf = _xi;
  tau_h = _xi;
  return;
 }
 if (_xi <= 0.) {
 m_inf = _t_m_inf[0];
 tau_m = _t_tau_m[0];
 h_inf = _t_h_inf[0];
 tau_h = _t_tau_h[0];
 return; }
 if (_xi >= 13000.) {
 m_inf = _t_m_inf[13000];
 tau_m = _t_tau_m[13000];
 h_inf = _t_h_inf[13000];
 tau_h = _t_tau_h[13000];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 m_inf = _t_m_inf[_i] + _theta*(_t_m_inf[_i+1] - _t_m_inf[_i]);
 tau_m = _t_tau_m[_i] + _theta*(_t_tau_m[_i+1] - _t_tau_m[_i]);
 h_inf = _t_h_inf[_i] + _theta*(_t_h_inf[_i+1] - _t_h_inf[_i]);
 tau_h = _t_tau_h[_i] + _theta*(_t_tau_h[_i+1] - _t_tau_h[_i]);
 }

 
static int  _f_evaluate_fct ( _threadargsprotocomma_ double _lv ) {
   phi_m = pow( 5.0 , ( ( celsius - 24.0 ) / 10.0 ) ) ;
   phi_h = pow( Q10_channel , ( ( celsius - 24.0 ) / 10.0 ) ) ;
   m_inf = 1.0 / ( 1.0 + exp ( - ( _lv + shift + 50.0 ) / 7.4 ) ) ;
   h_inf = 1.0 / ( 1.0 + exp ( ( _lv + shift + 78.0 ) / 5.0 ) ) ;
   tau_m = ( 3.0 + 1.0 / ( exp ( ( _lv + shift + 25.0 ) / 10.0 ) + exp ( - ( _lv + shift + 100.0 ) / 15.0 ) ) ) / phi_m ;
   tau_h = ( 85.0 + 1.0 / ( exp ( ( _lv + shift + 46.0 ) / 4.0 ) + exp ( - ( _lv + shift + 405.0 ) / 50.0 ) ) ) / phi_h ;
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 
#if 1
 _check_evaluate_fct(_p, _ppvar, _thread, _nt);
#endif
 _r = 1.;
 evaluate_fct ( _p, _ppvar, _thread, _nt, *getarg(1) );
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
  ca2i = _ion_ca2i;
  ca2o = _ion_ca2o;
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
  ca2i = _ion_ca2i;
  ca2o = _ion_ca2o;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca2_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca2_sym, _ppvar, 1, 2);
   nrn_update_ion_pointer(_ca2_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_ca2_sym, _ppvar, 3, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  h = h0;
  m = m0;
 {
   gbar_Q10 = gbar * ( pow( Q10_diff , ( ( celsius - 23.0 ) / 10.0 ) ) ) ;
   evaluate_fct ( _threadargscomma_ v ) ;
   m = m_inf ;
   h = h_inf ;
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
 _check_evaluate_fct(_p, _ppvar, _thread, _nt);
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
  ca2i = _ion_ca2i;
  ca2o = _ion_ca2o;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ca2rev = ( 1e3 ) * ( R * ( celsius + 273.15 ) ) / ( 2.0 * FARADAY ) * log ( ca2o / ca2i ) ;
   g = gbar_Q10 * m * m * h ;
   ica2 = gbar_Q10 * m * m * h * ( v - ca2rev ) ;
   ic = ica2 ;
   }
 _current += ica2;

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
  ca2i = _ion_ca2i;
  ca2o = _ion_ca2o;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dica2;
  _dica2 = ica2;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dica2dv += (_dica2 - ica2)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica2 += ica2 ;
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
  ca2i = _ion_ca2i;
  ca2o = _ion_ca2o;
 {   ca2state(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m) - _p;  _dlist1[0] = &(Dm) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
   _t_m_inf = makevector(13001*sizeof(double));
   _t_tau_m = makevector(13001*sizeof(double));
   _t_h_inf = makevector(13001*sizeof(double));
   _t_tau_h = makevector(13001*sizeof(double));
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/stefano/Documenti/paperRevision/GL_Model/templates/golgi/Golgi_Ca_LVA.mod";
static const char* nmodl_file_text = 
  "TITLE Low threshold calcium current Cerebellum Golgi Cell Model\n"
  ":\n"
  ":   Ca++ current responsible for low threshold spikes (LTS)\n"
  ":   RETICULAR THALAMUS\n"
  ":   Differential equations\n"
  ":\n"
  ":   Model of Huguenard & McCormick, J Neurophysiol 68: 1373-1383, 1992.\n"
  ":   The kinetics is described by standard equations (NOT GHK)\n"
  ":   using a m2h format, according to the voltage-clamp data\n"
  ":   (whole cell patch clamp) of Huguenard & Prince, J Neurosci.\n"
  ":   12: 3804-3817, 1992.  The model was introduced in Destexhe et al.\n"
  ":   J. Neurophysiology 72: 803-818, 1994.\n"
  ":   See http://www.cnl.salk.edu/~alain , http://cns.fmed.ulaval.ca\n"
  ":\n"
  ":    - Kinetics adapted to fit the T-channel of reticular neuron\n"
  ":    - Q10 changed to 5 and 3\n"
  ":    - Time constant tau_h fitted from experimental data\n"
  ":    - shift parameter for screening charge\n"
  ":\n"
  ":   ACTIVATION FUNCTIONS FROM EXPERIMENTS (NO CORRECTION)\n"
  ":\n"
  ":   Reversal potential taken from Nernst Equation\n"
  ":\n"
  ":   Written by Alain Destexhe, Salk Institute, Sept 18, 1992\n"
  ":\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "        SUFFIX Golgi_Ca_LVA\n"
  "        USEION ca2 READ ca2i, ca2o WRITE ica2 VALENCE 2\n"
  "	RANGE Q10_diff,Q10_channel,gbar_Q10, ic\n"
  "        RANGE g, gbar, m_inf, tau_m, h_inf, tau_h, shift\n"
  "	RANGE ica2, m ,h, ca2rev\n"
  "	RANGE phi_m, phi_h\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "        (molar) = (1/liter)\n"
  "        (mV) =  (millivolt)\n"
  "        (mA) =  (milliamp)\n"
  "        (mM) =  (millimolar)\n"
  "\n"
  "        FARADAY = (faraday) (coulomb)\n"
  "        R = (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v               (mV)\n"
  "        celsius (degC)\n"
  "        eca2 (mV)\n"
  "	gbar  = 2.5e-4 (mho/cm2)\n"
  "        shift   = 2     (mV)            : screening charge for Ca_o = 2 mM\n"
  "        ca2i  (mM)           : adjusted for eca=120 mV\n"
  "        ca2o  (mM)\n"
  "	Q10_diff	= 1.5\n"
  "	Q10_channel	= 3\n"
  "}\n"
  "\n"
  "STATE {\n"
  "        m h\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "        ica2     (mA/cm2)\n"
  "        ca2rev   (mV)\n"
  "	g        (mho/cm2) \n"
  "        m_inf\n"
  "        tau_m   (ms)\n"
  "        h_inf\n"
  "        tau_h   (ms)\n"
  "        phi_m\n"
  "        phi_h\n"
  "	gbar_Q10 (mho/cm2)\n"
  "	ic\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "        SOLVE ca2state METHOD cnexp\n"
  "        ca2rev = (1e3) * (R*(celsius+273.15))/(2*FARADAY) * log (ca2o/ca2i)\n"
  "        g = gbar_Q10 * m*m*h\n"
  "        ica2 = gbar_Q10 * m*m*h * (v-ca2rev)\n"
  "	ic = ica2\n"
  "}\n"
  "\n"
  "DERIVATIVE ca2state {\n"
  "        evaluate_fct(v)\n"
  "\n"
  "        m' = (m_inf - m) / tau_m\n"
  "        h' = (h_inf - h) / tau_h\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "INITIAL {\n"
  ":\n"
  ":   Activation functions and kinetics were obtained from\n"
  ":   Huguenard & Prince, and were at 23-25 deg.\n"
  ":   Transformation to 36 deg assuming Q10 of 5 and 3 for m and h\n"
  ":   (as in Coulter et al., J Physiol 414: 587, 1989)\n"
  ":\n"
  "	gbar_Q10 = gbar*(Q10_diff^((celsius-23)/10))\n"
  "        evaluate_fct(v)\n"
  "        m = m_inf\n"
  "        h = h_inf\n"
  "}\n"
  "\n"
  "PROCEDURE evaluate_fct(v(mV)) { \n"
  ":\n"
  ":   Time constants were obtained from J. Huguenard\n"
  ":\n"
  "	TABLE m_inf, tau_m, h_inf, tau_h\n"
  "	DEPEND celsius, shift, phi_m, phi_h FROM -100 TO 30 WITH 13000 \n"
  "        phi_m = 5.0 ^ ((celsius-24)/10)\n"
  "        phi_h = Q10_channel ^ ((celsius-24)/10)\n"
  "	\n"
  "        m_inf = 1.0 / ( 1 + exp(-(v+shift+50)/7.4) )\n"
  "        h_inf = 1.0 / ( 1 + exp((v+shift+78)/5.0) )\n"
  "\n"
  "        tau_m = ( 3 + 1.0 / ( exp((v+shift+25)/10) + exp(-(v+shift+100)/15) ) ) / phi_m\n"
  "        tau_h = ( 85 + 1.0 / ( exp((v+shift+46)/4) + exp(-(v+shift+405)/50) ) ) / phi_h\n"
  "}\n"
  "UNITSON\n"
  ;
#endif

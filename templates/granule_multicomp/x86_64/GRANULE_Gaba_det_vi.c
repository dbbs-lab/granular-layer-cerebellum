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
 
#define nrn_init _nrn_init__GRANULE_Gaba_det_vi
#define _nrn_initial _nrn_initial__GRANULE_Gaba_det_vi
#define nrn_cur _nrn_cur__GRANULE_Gaba_det_vi
#define _nrn_current _nrn_current__GRANULE_Gaba_det_vi
#define nrn_jacob _nrn_jacob__GRANULE_Gaba_det_vi
#define nrn_state _nrn_state__GRANULE_Gaba_det_vi
#define _net_receive _net_receive__GRANULE_Gaba_det_vi 
#define kstates kstates__GRANULE_Gaba_det_vi 
 
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
#define gmaxA1 _p[2]
#define gmaxA6 _p[3]
#define Q10_diff _p[4]
#define Q10_channel _p[5]
#define Cdur _p[6]
#define kon _p[7]
#define koff _p[8]
#define d3 _p[9]
#define r3 _p[10]
#define d1d2 _p[11]
#define r1r2 _p[12]
#define a1 _p[13]
#define b1 _p[14]
#define a2 _p[15]
#define b2 _p[16]
#define r1 _p[17]
#define r2 _p[18]
#define d1 _p[19]
#define d2 _p[20]
#define kon_a6 _p[21]
#define koff_a6 _p[22]
#define d3_a6 _p[23]
#define r3_a6 _p[24]
#define d1d2_a6 _p[25]
#define r1r2_a6 _p[26]
#define a1_a6 _p[27]
#define b1_a6 _p[28]
#define a2_a6 _p[29]
#define b2_a6 _p[30]
#define r1_a6 _p[31]
#define r2_a6 _p[32]
#define d1_a6 _p[33]
#define d2_a6 _p[34]
#define Erev _p[35]
#define tau_1 _p[36]
#define tau_rec _p[37]
#define tau_facil _p[38]
#define U _p[39]
#define Tmax _p[40]
#define onSET _p[41]
#define M _p[42]
#define Rd _p[43]
#define Diff _p[44]
#define lamd _p[45]
#define diff_flag _p[46]
#define nd _p[47]
#define i _p[48]
#define ic _p[49]
#define g _p[50]
#define gA1 _p[51]
#define gA6 _p[52]
#define Open _p[53]
#define Open_a6 _p[54]
#define diffus _p[55]
#define T _p[56]
#define Trelease _p[57]
#define xout _p[58]
#define yout _p[59]
#define zout _p[60]
#define uout _p[61]
#define C _p[62]
#define CA1 _p[63]
#define CA2 _p[64]
#define DA1 _p[65]
#define DA2 _p[66]
#define DA2f _p[67]
#define OA1 _p[68]
#define OA2 _p[69]
#define C_a6 _p[70]
#define CA1_a6 _p[71]
#define CA2_a6 _p[72]
#define DA1_a6 _p[73]
#define DA2_a6 _p[74]
#define DA2f_a6 _p[75]
#define OA1_a6 _p[76]
#define OA2_a6 _p[77]
#define Mres _p[78]
#define tpre _p[79]
#define tspike (_p + 80)
#define PRE (_p + 180)
#define numpulses _p[280]
#define tzero _p[281]
#define gbar_Q10 _p[282]
#define Q10 _p[283]
#define DC _p[284]
#define DCA1 _p[285]
#define DCA2 _p[286]
#define DDA1 _p[287]
#define DDA2 _p[288]
#define DDA2f _p[289]
#define DOA1 _p[290]
#define DOA2 _p[291]
#define DC_a6 _p[292]
#define DCA1_a6 _p[293]
#define DCA2_a6 _p[294]
#define DDA1_a6 _p[295]
#define DDA2_a6 _p[296]
#define DDA2f_a6 _p[297]
#define DOA1_a6 _p[298]
#define DOA2_a6 _p[299]
#define v _p[300]
#define _g _p[301]
#define _tsav _p[302]
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
#define diffusione diffusione_GRANULE_Gaba_det_vi
#define imax imax_GRANULE_Gaba_det_vi
 extern double diffusione( _threadargsproto_ );
 extern double imax( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
#define Cdur_2 Cdur_2_GRANULE_Gaba_det_vi
 double Cdur_2 = 0.3;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "U", 0, 1,
 "tau_facil", 0, 1e+09,
 "tau_rec", 1e-09, 1e+09,
 "tau_1", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Cdur_2_GRANULE_Gaba_det_vi", "ms",
 "gmaxA1", "pS",
 "gmaxA6", "pS",
 "Cdur", "ms",
 "kon", "/ms/mM",
 "koff", "/ms",
 "d3", "/ms",
 "r3", "/ms",
 "d1d2", "/ms/mM",
 "r1r2", "/ms",
 "a1", "/ms",
 "b1", "/ms",
 "a2", "/ms",
 "b2", "/ms",
 "r1", "/ms",
 "r2", "/ms",
 "d1", "/ms",
 "d2", "/ms",
 "kon_a6", "/ms/mM",
 "koff_a6", "/ms",
 "d3_a6", "/ms",
 "r3_a6", "/ms",
 "d1d2_a6", "/ms/mM",
 "r1r2_a6", "/ms",
 "a1_a6", "/ms",
 "b1_a6", "/ms",
 "a2_a6", "/ms",
 "b2_a6", "/ms",
 "r1_a6", "/ms",
 "r2_a6", "/ms",
 "d1_a6", "/ms",
 "d2_a6", "/ms",
 "Erev", "mV",
 "tau_1", "ms",
 "tau_rec", "ms",
 "tau_facil", "ms",
 "Tmax", "mM",
 "Rd", "um",
 "Diff", "um2/ms",
 "lamd", "nm",
 "i", "nA",
 "ic", "nA",
 "g", "pS",
 "gA1", "nA",
 "gA6", "nA",
 "T", "mM",
 "Trelease", "mM",
 0,0
};
 static double CA2_a60 = 0;
 static double CA1_a60 = 0;
 static double C_a60 = 0;
 static double CA20 = 0;
 static double CA10 = 0;
 static double C0 = 0;
 static double DA2f_a60 = 0;
 static double DA2_a60 = 0;
 static double DA1_a60 = 0;
 static double DA2f0 = 0;
 static double DA20 = 0;
 static double DA10 = 0;
 static double OA2_a60 = 0;
 static double OA1_a60 = 0;
 static double OA20 = 0;
 static double OA10 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "Cdur_2_GRANULE_Gaba_det_vi", &Cdur_2_GRANULE_Gaba_det_vi,
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
"GRANULE_Gaba_det_vi",
 "syntype",
 "gmax_factor",
 "gmaxA1",
 "gmaxA6",
 "Q10_diff",
 "Q10_channel",
 "Cdur",
 "kon",
 "koff",
 "d3",
 "r3",
 "d1d2",
 "r1r2",
 "a1",
 "b1",
 "a2",
 "b2",
 "r1",
 "r2",
 "d1",
 "d2",
 "kon_a6",
 "koff_a6",
 "d3_a6",
 "r3_a6",
 "d1d2_a6",
 "r1r2_a6",
 "a1_a6",
 "b1_a6",
 "a2_a6",
 "b2_a6",
 "r1_a6",
 "r2_a6",
 "d1_a6",
 "d2_a6",
 "Erev",
 "tau_1",
 "tau_rec",
 "tau_facil",
 "U",
 "Tmax",
 "onSET",
 "M",
 "Rd",
 "Diff",
 "lamd",
 "diff_flag",
 "nd",
 0,
 "i",
 "ic",
 "g",
 "gA1",
 "gA6",
 "Open",
 "Open_a6",
 "diffus",
 "T",
 "Trelease",
 "xout",
 "yout",
 "zout",
 "uout",
 0,
 "C",
 "CA1",
 "CA2",
 "DA1",
 "DA2",
 "DA2f",
 "OA1",
 "OA2",
 "C_a6",
 "CA1_a6",
 "CA2_a6",
 "DA1_a6",
 "DA2_a6",
 "DA2f_a6",
 "OA1_a6",
 "OA2_a6",
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
 	_p = nrn_prop_data_alloc(_mechtype, 303, _prop);
 	/*initialize range parameters*/
 	syntype = 0;
 	gmax_factor = 1;
 	gmaxA1 = 918.807;
 	gmaxA6 = 132.842;
 	Q10_diff = 1.5;
 	Q10_channel = 2.4;
 	Cdur = 0.3;
 	kon = 17.7;
 	koff = 2;
 	d3 = 21.703;
 	r3 = 0.97325;
 	d1d2 = 0;
 	r1r2 = 0;
 	a1 = 0.4144;
 	b1 = 0.03;
 	a2 = 1.0002;
 	b2 = 10;
 	r1 = 0.0007;
 	r2 = 0.14208;
 	d1 = 0.00033;
 	d2 = 3.4898;
 	kon_a6 = 54.8;
 	koff_a6 = 0.31061;
 	d3_a6 = 15;
 	r3_a6 = 7.4132;
 	d1d2_a6 = 24.2;
 	r1r2_a6 = 0.091668;
 	a1_a6 = 0.06;
 	b1_a6 = 0.03;
 	a2_a6 = 0.4;
 	b2_a6 = 10;
 	r1_a6 = 0.040001;
 	r2_a6 = 0.4316;
 	d1_a6 = 0.86042;
 	d2_a6 = 2.7012;
 	Erev = -65;
 	tau_1 = 0.1;
 	tau_rec = 36.169;
 	tau_facil = 58.517;
 	U = 0.35;
 	Tmax = 1;
 	onSET = 1;
 	M = 7.506;
 	Rd = 0.978;
 	Diff = 0.223;
 	lamd = 20;
 	diff_flag = 1;
 	nd = 1;
  }
 	_prop->param = _p;
 	_prop->param_size = 303;
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

 void _GRANULE_Gaba_det_vi_reg() {
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
  hoc_register_prop_size(_mechtype, 303, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_init[_mechtype] = _net_init;
 pnt_receive_size[_mechtype] = 9;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 GRANULE_Gaba_det_vi /home/neuron/projects/rete/control_sims/weasel/templates/granule_multicomp/x86_64/GRANULE_Gaba_det_vi.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 3.14159;
static int _reset;
static char *modelname = "Gaba mod file only for fitting purpose ";

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
 static int _slist1[16], _dlist1[16]; static double *_temp1;
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
for(_i=2;_i<16;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 diffus = diffusione ( _threadargs_ ) ;
   Trelease = T + diffus ;
   /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 f_flux =  2.0 * kon * Trelease * Q10 * C ;
 b_flux =  koff * Q10 * CA1 ;
 _RHS1( 7) -= (f_flux - b_flux);
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  2.0 * kon * Trelease * Q10 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 6 ,7)  -= _term;
 _term =  koff * Q10 ;
 _MATELM1( 7 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 f_flux =  kon * Trelease * Q10 * CA1 ;
 b_flux =  2.0 * koff * Q10 * CA2 ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  kon * Trelease * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  2.0 * koff * Q10 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 f_flux =  d3 * Q10 * CA2 ;
 b_flux =  r3 * Q10 * DA2f ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 11) += (f_flux - b_flux);
 
 _term =  d3 * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 11 ,5)  -= _term;
 _term =  r3 * Q10 ;
 _MATELM1( 5 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 f_flux =  d1d2 * Trelease * Q10 * DA1 ;
 b_flux =  r1r2 * Q10 * DA2 ;
 _RHS1( 13) -= (f_flux - b_flux);
 _RHS1( 12) += (f_flux - b_flux);
 
 _term =  d1d2 * Trelease * Q10 ;
 _MATELM1( 13 ,13)  += _term;
 _MATELM1( 12 ,13)  -= _term;
 _term =  r1r2 * Q10 ;
 _MATELM1( 13 ,12)  -= _term;
 _MATELM1( 12 ,12)  += _term;
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 f_flux =  a1 * Q10 * OA1 ;
 b_flux =  b1 * Q10 * CA1 ;
 _RHS1( 15) -= (f_flux - b_flux);
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  a1 * Q10 ;
 _MATELM1( 15 ,15)  += _term;
 _MATELM1( 6 ,15)  -= _term;
 _term =  b1 * Q10 ;
 _MATELM1( 15 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 f_flux =  a2 * Q10 * OA2 ;
 b_flux =  b2 * Q10 * CA2 ;
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  a2 * Q10 ;
 _MATELM1( 5 ,1)  -= _term;
 _term =  b2 * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 f_flux =  r1 * Q10 * DA1 ;
 b_flux =  d1 * Q10 * CA1 ;
 _RHS1( 13) -= (f_flux - b_flux);
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  r1 * Q10 ;
 _MATELM1( 13 ,13)  += _term;
 _MATELM1( 6 ,13)  -= _term;
 _term =  d1 * Q10 ;
 _MATELM1( 13 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 f_flux =  r2 * Q10 * DA2 ;
 b_flux =  d2 * Q10 * CA2 ;
 _RHS1( 12) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  r2 * Q10 ;
 _MATELM1( 12 ,12)  += _term;
 _MATELM1( 5 ,12)  -= _term;
 _term =  d2 * Q10 ;
 _MATELM1( 12 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 _RHS1(1) =  1.0;
 _MATELM1(1, 1) = 1;
 _RHS1(1) -= OA2 ;
 _MATELM1(1, 15) = 1;
 _RHS1(1) -= OA1 ;
 _MATELM1(1, 11) = 1;
 _RHS1(1) -= DA2f ;
 _MATELM1(1, 12) = 1;
 _RHS1(1) -= DA2 ;
 _MATELM1(1, 13) = 1;
 _RHS1(1) -= DA1 ;
 _MATELM1(1, 5) = 1;
 _RHS1(1) -= CA2 ;
 _MATELM1(1, 6) = 1;
 _RHS1(1) -= CA1 ;
 _MATELM1(1, 7) = 1;
 _RHS1(1) -= C ;
 /*CONSERVATION*/
 /* ~ C_a6 <-> CA1_a6 ( 2.0 * kon_a6 * diffus * Q10 , koff_a6 * Q10 )*/
 f_flux =  2.0 * kon_a6 * diffus * Q10 * C_a6 ;
 b_flux =  koff_a6 * Q10 * CA1_a6 ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  2.0 * kon_a6 * diffus * Q10 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  koff_a6 * Q10 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ CA1_a6 <-> CA2_a6 ( kon_a6 * diffus * Q10 , 2.0 * koff_a6 * Q10 )*/
 f_flux =  kon_a6 * diffus * Q10 * CA1_a6 ;
 b_flux =  2.0 * koff_a6 * Q10 * CA2_a6 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  kon_a6 * diffus * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  2.0 * koff_a6 * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CA2_a6 <-> DA2f_a6 ( d3_a6 * Q10 , r3_a6 * Q10 )*/
 f_flux =  d3_a6 * Q10 * CA2_a6 ;
 b_flux =  r3_a6 * Q10 * DA2f_a6 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 8) += (f_flux - b_flux);
 
 _term =  d3_a6 * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 8 ,2)  -= _term;
 _term =  r3_a6 * Q10 ;
 _MATELM1( 2 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ DA1_a6 <-> DA2_a6 ( d1d2_a6 * diffus * Q10 , r1r2_a6 * Q10 )*/
 f_flux =  d1d2_a6 * diffus * Q10 * DA1_a6 ;
 b_flux =  r1r2_a6 * Q10 * DA2_a6 ;
 _RHS1( 10) -= (f_flux - b_flux);
 _RHS1( 9) += (f_flux - b_flux);
 
 _term =  d1d2_a6 * diffus * Q10 ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 9 ,10)  -= _term;
 _term =  r1r2_a6 * Q10 ;
 _MATELM1( 10 ,9)  -= _term;
 _MATELM1( 9 ,9)  += _term;
 /*REACTION*/
  /* ~ OA1_a6 <-> CA1_a6 ( a1_a6 * Q10 , b1_a6 * Q10 )*/
 f_flux =  a1_a6 * Q10 * OA1_a6 ;
 b_flux =  b1_a6 * Q10 * CA1_a6 ;
 _RHS1( 14) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  a1_a6 * Q10 ;
 _MATELM1( 14 ,14)  += _term;
 _MATELM1( 3 ,14)  -= _term;
 _term =  b1_a6 * Q10 ;
 _MATELM1( 14 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ OA2_a6 <-> CA2_a6 ( a2_a6 * Q10 , b2_a6 * Q10 )*/
 f_flux =  a2_a6 * Q10 * OA2_a6 ;
 b_flux =  b2_a6 * Q10 * CA2_a6 ;
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  a2_a6 * Q10 ;
 _MATELM1( 2 ,0)  -= _term;
 _term =  b2_a6 * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ DA1_a6 <-> CA1_a6 ( r1_a6 * Q10 , d1_a6 * Q10 )*/
 f_flux =  r1_a6 * Q10 * DA1_a6 ;
 b_flux =  d1_a6 * Q10 * CA1_a6 ;
 _RHS1( 10) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  r1_a6 * Q10 ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 3 ,10)  -= _term;
 _term =  d1_a6 * Q10 ;
 _MATELM1( 10 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ DA2_a6 <-> CA2_a6 ( r2_a6 * Q10 , d2_a6 * Q10 )*/
 f_flux =  r2_a6 * Q10 * DA2_a6 ;
 b_flux =  d2_a6 * Q10 * CA2_a6 ;
 _RHS1( 9) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  r2_a6 * Q10 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 2 ,9)  -= _term;
 _term =  d2_a6 * Q10 ;
 _MATELM1( 9 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
   /* C_a6 + CA1_a6 + CA2_a6 + DA1_a6 + DA2_a6 + DA2f_a6 + OA1_a6 + OA2_a6 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= OA2_a6 ;
 _MATELM1(0, 14) = 1;
 _RHS1(0) -= OA1_a6 ;
 _MATELM1(0, 8) = 1;
 _RHS1(0) -= DA2f_a6 ;
 _MATELM1(0, 9) = 1;
 _RHS1(0) -= DA2_a6 ;
 _MATELM1(0, 10) = 1;
 _RHS1(0) -= DA1_a6 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= CA2_a6 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= CA1_a6 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= C_a6 ;
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
 if ( onSET ) {
     _args[1] = 0.0 ;
     onSET = 0.0 ;
     }
   if ( _lflag  == 0.0 ) {
     _args[2] = _args[2] + 1.0 ;
     if (  ! _args[1] ) {
       _args[3] = t ;
       tpre = t ;
       _args[1] = 1.0 ;
       _args[6] = _args[6] * exp ( - ( t - _args[8] ) / tau_rec ) ;
       _args[6] = _args[6] + ( _args[5] * ( exp ( - ( t - _args[8] ) / tau_1 ) - exp ( - ( t - _args[8] ) / tau_rec ) ) / ( ( tau_1 / tau_rec ) - 1.0 ) ) ;
       _args[5] = _args[5] * exp ( - ( t - _args[8] ) / tau_1 ) ;
       _args[4] = 1.0 - _args[5] - _args[6] ;
       if ( tau_facil > 0.0 ) {
         _args[7] = _args[7] * exp ( - ( t - _args[8] ) / tau_facil ) ;
         _args[7] = _args[7] + U * ( 1.0 - _args[7] ) ;
         }
       else {
         _args[7] = U ;
         }
       _args[5] = _args[5] + _args[4] * _args[7] ;
       T = Tmax * _args[5] ;
       _lfi = fmod ( numpulses , 100.0 ) ;
       PRE [ ((int) _lfi ) ] = _args[5] ;
       tspike [ ((int) _lfi ) ] = t ;
       numpulses = numpulses + 1.0 ;
       _args[8] = t ;
       }
     net_send ( _tqitem, _args, _pnt, t +  Cdur , _args[2] ) ;
     }
   if ( _lflag  == _args[2] ) {
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
   _args[6] = 0.0 ;
   _args[7] = 0.0 ;
   xout = _args[4] ;
   yout = _args[5] ;
   zout = _args[6] ;
   uout = _args[7] ;
   _args[8] = t ;
   _args[2] = 1.0 ;
   }
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<16;_i++) _p[_dlist1[_i]] = 0.0;}
 diffus = diffusione ( _threadargs_ ) ;
 Trelease = T + diffus ;
 /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 f_flux =  2.0 * kon * Trelease * Q10 * C ;
 b_flux =  koff * Q10 * CA1 ;
 DC -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 f_flux =  kon * Trelease * Q10 * CA1 ;
 b_flux =  2.0 * koff * Q10 * CA2 ;
 DCA1 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 f_flux =  d3 * Q10 * CA2 ;
 b_flux =  r3 * Q10 * DA2f ;
 DCA2 -= (f_flux - b_flux);
 DDA2f += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 f_flux =  d1d2 * Trelease * Q10 * DA1 ;
 b_flux =  r1r2 * Q10 * DA2 ;
 DDA1 -= (f_flux - b_flux);
 DDA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 f_flux =  a1 * Q10 * OA1 ;
 b_flux =  b1 * Q10 * CA1 ;
 DOA1 -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 f_flux =  a2 * Q10 * OA2 ;
 b_flux =  b2 * Q10 * CA2 ;
 DOA2 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 f_flux =  r1 * Q10 * DA1 ;
 b_flux =  d1 * Q10 * CA1 ;
 DDA1 -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 f_flux =  r2 * Q10 * DA2 ;
 b_flux =  d2 * Q10 * CA2 ;
 DDA2 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 /*CONSERVATION*/
 /* ~ C_a6 <-> CA1_a6 ( 2.0 * kon_a6 * diffus * Q10 , koff_a6 * Q10 )*/
 f_flux =  2.0 * kon_a6 * diffus * Q10 * C_a6 ;
 b_flux =  koff_a6 * Q10 * CA1_a6 ;
 DC_a6 -= (f_flux - b_flux);
 DCA1_a6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA1_a6 <-> CA2_a6 ( kon_a6 * diffus * Q10 , 2.0 * koff_a6 * Q10 )*/
 f_flux =  kon_a6 * diffus * Q10 * CA1_a6 ;
 b_flux =  2.0 * koff_a6 * Q10 * CA2_a6 ;
 DCA1_a6 -= (f_flux - b_flux);
 DCA2_a6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA2_a6 <-> DA2f_a6 ( d3_a6 * Q10 , r3_a6 * Q10 )*/
 f_flux =  d3_a6 * Q10 * CA2_a6 ;
 b_flux =  r3_a6 * Q10 * DA2f_a6 ;
 DCA2_a6 -= (f_flux - b_flux);
 DDA2f_a6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1_a6 <-> DA2_a6 ( d1d2_a6 * diffus * Q10 , r1r2_a6 * Q10 )*/
 f_flux =  d1d2_a6 * diffus * Q10 * DA1_a6 ;
 b_flux =  r1r2_a6 * Q10 * DA2_a6 ;
 DDA1_a6 -= (f_flux - b_flux);
 DDA2_a6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA1_a6 <-> CA1_a6 ( a1_a6 * Q10 , b1_a6 * Q10 )*/
 f_flux =  a1_a6 * Q10 * OA1_a6 ;
 b_flux =  b1_a6 * Q10 * CA1_a6 ;
 DOA1_a6 -= (f_flux - b_flux);
 DCA1_a6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA2_a6 <-> CA2_a6 ( a2_a6 * Q10 , b2_a6 * Q10 )*/
 f_flux =  a2_a6 * Q10 * OA2_a6 ;
 b_flux =  b2_a6 * Q10 * CA2_a6 ;
 DOA2_a6 -= (f_flux - b_flux);
 DCA2_a6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1_a6 <-> CA1_a6 ( r1_a6 * Q10 , d1_a6 * Q10 )*/
 f_flux =  r1_a6 * Q10 * DA1_a6 ;
 b_flux =  d1_a6 * Q10 * CA1_a6 ;
 DDA1_a6 -= (f_flux - b_flux);
 DCA1_a6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA2_a6 <-> CA2_a6 ( r2_a6 * Q10 , d2_a6 * Q10 )*/
 f_flux =  r2_a6 * Q10 * DA2_a6 ;
 b_flux =  d2_a6 * Q10 * CA2_a6 ;
 DDA2_a6 -= (f_flux - b_flux);
 DCA2_a6 += (f_flux - b_flux);
 
 /*REACTION*/
   /* C_a6 + CA1_a6 + CA2_a6 + DA1_a6 + DA2_a6 + DA2f_a6 + OA1_a6 + OA2_a6 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<16;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 diffus = diffusione ( _threadargs_ ) ;
 Trelease = T + diffus ;
 /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 _term =  2.0 * kon * Trelease * Q10 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 6 ,7)  -= _term;
 _term =  koff * Q10 ;
 _MATELM1( 7 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 _term =  kon * Trelease * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  2.0 * koff * Q10 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 _term =  d3 * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 11 ,5)  -= _term;
 _term =  r3 * Q10 ;
 _MATELM1( 5 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 _term =  d1d2 * Trelease * Q10 ;
 _MATELM1( 13 ,13)  += _term;
 _MATELM1( 12 ,13)  -= _term;
 _term =  r1r2 * Q10 ;
 _MATELM1( 13 ,12)  -= _term;
 _MATELM1( 12 ,12)  += _term;
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 _term =  a1 * Q10 ;
 _MATELM1( 15 ,15)  += _term;
 _MATELM1( 6 ,15)  -= _term;
 _term =  b1 * Q10 ;
 _MATELM1( 15 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 _term =  a2 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 5 ,1)  -= _term;
 _term =  b2 * Q10 ;
 _MATELM1( 1 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 _term =  r1 * Q10 ;
 _MATELM1( 13 ,13)  += _term;
 _MATELM1( 6 ,13)  -= _term;
 _term =  d1 * Q10 ;
 _MATELM1( 13 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 _term =  r2 * Q10 ;
 _MATELM1( 12 ,12)  += _term;
 _MATELM1( 5 ,12)  -= _term;
 _term =  d2 * Q10 ;
 _MATELM1( 12 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 /*CONSERVATION*/
 /* ~ C_a6 <-> CA1_a6 ( 2.0 * kon_a6 * diffus * Q10 , koff_a6 * Q10 )*/
 _term =  2.0 * kon_a6 * diffus * Q10 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  koff_a6 * Q10 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ CA1_a6 <-> CA2_a6 ( kon_a6 * diffus * Q10 , 2.0 * koff_a6 * Q10 )*/
 _term =  kon_a6 * diffus * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  2.0 * koff_a6 * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CA2_a6 <-> DA2f_a6 ( d3_a6 * Q10 , r3_a6 * Q10 )*/
 _term =  d3_a6 * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 8 ,2)  -= _term;
 _term =  r3_a6 * Q10 ;
 _MATELM1( 2 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ DA1_a6 <-> DA2_a6 ( d1d2_a6 * diffus * Q10 , r1r2_a6 * Q10 )*/
 _term =  d1d2_a6 * diffus * Q10 ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 9 ,10)  -= _term;
 _term =  r1r2_a6 * Q10 ;
 _MATELM1( 10 ,9)  -= _term;
 _MATELM1( 9 ,9)  += _term;
 /*REACTION*/
  /* ~ OA1_a6 <-> CA1_a6 ( a1_a6 * Q10 , b1_a6 * Q10 )*/
 _term =  a1_a6 * Q10 ;
 _MATELM1( 14 ,14)  += _term;
 _MATELM1( 3 ,14)  -= _term;
 _term =  b1_a6 * Q10 ;
 _MATELM1( 14 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ OA2_a6 <-> CA2_a6 ( a2_a6 * Q10 , b2_a6 * Q10 )*/
 _term =  a2_a6 * Q10 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 2 ,0)  -= _term;
 _term =  b2_a6 * Q10 ;
 _MATELM1( 0 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ DA1_a6 <-> CA1_a6 ( r1_a6 * Q10 , d1_a6 * Q10 )*/
 _term =  r1_a6 * Q10 ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 3 ,10)  -= _term;
 _term =  d1_a6 * Q10 ;
 _MATELM1( 10 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ DA2_a6 <-> CA2_a6 ( r2_a6 * Q10 , d2_a6 * Q10 )*/
 _term =  r2_a6 * Q10 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 2 ,9)  -= _term;
 _term =  d2_a6 * Q10 ;
 _MATELM1( 9 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
   /* C_a6 + CA1_a6 + CA2_a6 + DA1_a6 + DA2_a6 + DA2f_a6 + OA1_a6 + OA2_a6 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 16;}
 
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
	for (_i=0; _i < 16; ++_i) {
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
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 16, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  CA2_a6 = CA2_a60;
  CA1_a6 = CA1_a60;
  C_a6 = C_a60;
  CA2 = CA20;
  CA1 = CA10;
  C = C0;
  DA2f_a6 = DA2f_a60;
  DA2_a6 = DA2_a60;
  DA1_a6 = DA1_a60;
  DA2f = DA2f0;
  DA2 = DA20;
  DA1 = DA10;
  OA2_a6 = OA2_a60;
  OA1_a6 = OA1_a60;
  OA2 = OA20;
  OA1 = OA10;
 {
   C = 1.0 ;
   CA1 = 0.0 ;
   CA2 = 0.0 ;
   DA1 = 0.0 ;
   DA2 = 0.0 ;
   DA2f = 0.0 ;
   OA1 = 0.0 ;
   OA2 = 0.0 ;
   CA1 = 0.0 ;
   CA2 = 0.0 ;
   C_a6 = 1.0 ;
   CA1_a6 = 0.0 ;
   CA2_a6 = 0.0 ;
   DA1_a6 = 0.0 ;
   DA2_a6 = 0.0 ;
   DA2f_a6 = 0.0 ;
   OA1_a6 = 0.0 ;
   OA2_a6 = 0.0 ;
   CA1_a6 = 0.0 ;
   CA2_a6 = 0.0 ;
   Open = 0.0 ;
   T = 0.0 ;
   gbar_Q10 = pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Q10 = pow( Q10_channel , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   numpulses = 0.0 ;
   Mres = 1e3 * ( 1e3 * 1e15 / 6.022e23 * M ) ;
   {int  _li ;for ( _li = 1 ; _li <= 100 ; _li ++ ) {
     PRE [ _li - 1 ] = 0.0 ;
     tspike [ _li - 1 ] = 0.0 ;
     } }
   tspike [ 0 ] = 1e12 ;
   if ( tau_1 >= tau_rec ) {
     printf ( "Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\n" , tau_1 , tau_rec ) ;
     tau_rec = tau_1 + 1e-5 ;
     }
   onSET = 1.0 ;
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
   Open = OA1 + OA2 ;
   Open_a6 = OA1_a6 + OA2_a6 ;
   gA1 = gmaxA1 * gbar_Q10 * Open ;
   gA6 = gmaxA6 * gbar_Q10 * Open_a6 ;
   g = ( gA1 + gA6 ) * gmax_factor ;
   i = ( 1e-6 ) * g * ( v - Erev ) ;
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
 {  sparse_thread(&_thread[_spth1]._pvoid, 16, _slist1, _dlist1, _p, &t, dt, kstates, _linmat1, _ppvar, _thread, _nt);
  }}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(OA2_a6) - _p;  _dlist1[0] = &(DOA2_a6) - _p;
 _slist1[1] = &(OA2) - _p;  _dlist1[1] = &(DOA2) - _p;
 _slist1[2] = &(CA2_a6) - _p;  _dlist1[2] = &(DCA2_a6) - _p;
 _slist1[3] = &(CA1_a6) - _p;  _dlist1[3] = &(DCA1_a6) - _p;
 _slist1[4] = &(C_a6) - _p;  _dlist1[4] = &(DC_a6) - _p;
 _slist1[5] = &(CA2) - _p;  _dlist1[5] = &(DCA2) - _p;
 _slist1[6] = &(CA1) - _p;  _dlist1[6] = &(DCA1) - _p;
 _slist1[7] = &(C) - _p;  _dlist1[7] = &(DC) - _p;
 _slist1[8] = &(DA2f_a6) - _p;  _dlist1[8] = &(DDA2f_a6) - _p;
 _slist1[9] = &(DA2_a6) - _p;  _dlist1[9] = &(DDA2_a6) - _p;
 _slist1[10] = &(DA1_a6) - _p;  _dlist1[10] = &(DDA1_a6) - _p;
 _slist1[11] = &(DA2f) - _p;  _dlist1[11] = &(DDA2f) - _p;
 _slist1[12] = &(DA2) - _p;  _dlist1[12] = &(DDA2) - _p;
 _slist1[13] = &(DA1) - _p;  _dlist1[13] = &(DDA1) - _p;
 _slist1[14] = &(OA1_a6) - _p;  _dlist1[14] = &(DOA1_a6) - _p;
 _slist1[15] = &(OA1) - _p;  _dlist1[15] = &(DOA1) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

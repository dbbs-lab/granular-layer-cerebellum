/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
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
 
#define nrn_init _nrn_init__MF_SpikeGenerator_SS
#define _nrn_initial _nrn_initial__MF_SpikeGenerator_SS
#define nrn_cur _nrn_cur__MF_SpikeGenerator_SS
#define _nrn_current _nrn_current__MF_SpikeGenerator_SS
#define nrn_jacob _nrn_jacob__MF_SpikeGenerator_SS
#define nrn_state _nrn_state__MF_SpikeGenerator_SS
#define _net_receive _net_receive__MF_SpikeGenerator_SS 
#define event_time event_time__MF_SpikeGenerator_SS 
#define seed seed__MF_SpikeGenerator_SS 
 
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
#define IntraBurstInterval _p[0]
#define IntraBurstNoise _p[1]
#define InterBurstInterval _p[2]
#define burst_len _p[3]
#define start_background _p[4]
#define start_burst _p[5]
#define end _p[6]
#define BackgroundNoise _p[7]
#define InterBurstIntervalNoise _p[8]
#define delay _p[9]
#define tonic _p[10]
#define y _p[11]
#define burst _p[12]
#define burst_off _p[13]
#define burst_on _p[14]
#define Stim (_p + 15)
#define last_event_t _p[1015]
#define set_burst _p[1016]
#define event _p[1017]
#define next_burst_on _p[1018]
#define toff _p[1019]
#define on _p[1020]
#define inter_burst_ISI _p[1021]
#define cnt _p[1022]
#define _tsav _p[1023]
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
 static double _hoc_ISI_modulated();
 static double _hoc_event_time();
 static double _hoc_interval();
 static double _hoc_seed();
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
 "ISI_modulated", _hoc_ISI_modulated,
 "event_time", _hoc_event_time,
 "interval", _hoc_interval,
 "seed", _hoc_seed,
 0, 0
};
#define ISI_modulated ISI_modulated_MF_SpikeGenerator_SS
#define interval interval_MF_SpikeGenerator_SS
 extern double ISI_modulated( double , double , double , double , double );
 extern double interval( double , double );
 /* declare global and static user variables */
#define sin_phase sin_phase_MF_SpikeGenerator_SS
 double sin_phase = 0;
#define sin_freq sin_freq_MF_SpikeGenerator_SS
 double sin_freq = 10;
#define sin_amp sin_amp_MF_SpikeGenerator_SS
 double sin_amp = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "IntraBurstInterval", "ms",
 "InterBurstInterval", "ms",
 "start_background", "ms",
 "start_burst", "ms",
 "end", "ms",
 "burst_off", "ms",
 "burst_on", "ms",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "sin_amp_MF_SpikeGenerator_SS", &sin_amp_MF_SpikeGenerator_SS,
 "sin_freq_MF_SpikeGenerator_SS", &sin_freq_MF_SpikeGenerator_SS,
 "sin_phase_MF_SpikeGenerator_SS", &sin_phase_MF_SpikeGenerator_SS,
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
 "6.2.0",
"MF_SpikeGenerator_SS",
 "IntraBurstInterval",
 "IntraBurstNoise",
 "InterBurstInterval",
 "burst_len",
 "start_background",
 "start_burst",
 "end",
 "BackgroundNoise",
 "InterBurstIntervalNoise",
 "delay",
 "tonic",
 0,
 "y",
 "burst",
 "burst_off",
 "burst_on",
 "Stim[1000]",
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
 	_p = nrn_prop_data_alloc(_mechtype, 1024, _prop);
 	/*initialize range parameters*/
 	IntraBurstInterval = 10;
 	IntraBurstNoise = 0;
 	InterBurstInterval = 1000;
 	burst_len = 2;
 	start_background = 50;
 	start_burst = 100;
 	end = 1e+10;
 	BackgroundNoise = 0;
 	InterBurstIntervalNoise = 0;
 	delay = 0;
 	tonic = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 1024;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[2]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _MF_pregen_modul_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 1024, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
 add_nrn_has_net_event(_mechtype);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 MF_SpikeGenerator_SS /home/neuron/projects/rete/control_sims/weasel/templates/granule/x86_64/MF_pregen_modul.mod\n");
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
static int event_time();
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
 
double interval (  double _lmean , double _lnoise ) {
   double _linterval;
 if ( _lmean <= 0. ) {
     _lmean = .01 ;
     }
   if ( _lnoise  == 0.0 ) {
     _linterval = _lmean ;
     }
   else {
     _linterval = ( 1. - _lnoise ) * _lmean + _lnoise * ( _lmean * exprand ( 1.0 ) + delay ) ;
     }
   
return _linterval;
 }
 
static double _hoc_interval(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  interval (  *getarg(1) , *getarg(2) );
 return(_r);
}
 
double ISI_modulated (  double _ltonic , double _lsin_amp , double _lsin_freq , double _lsin_phase , double _levent ) {
   double _lISI_modulated;
 _lISI_modulated = 1000. / ( _ltonic + _lsin_amp * sin ( 2.0 * PI * _lsin_freq * _levent / 1000.0 + _lsin_phase ) ) ;
   
return _lISI_modulated;
 }
 
static double _hoc_ISI_modulated(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  ISI_modulated (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) );
 return(_r);
}
 
static int  event_time (  ) {
   if ( InterBurstInterval  == 0.0  || ( burst  != 0.  && burst_len > 1.0 ) ) {
     event = event + interval ( _threadargscomma_ IntraBurstInterval , IntraBurstNoise ) ;
     if ( event > burst_on + burst_off ) {
       burst = 0. ;
       set_burst = 0.0 ;
       }
     }
   else {
     if ( burst_len  == 1.0  && burst  == 1. ) {
       burst = 0. ;
       set_burst = 0.0 ;
       }
     burst_off = interval ( _threadargscomma_ ( burst_len - 1.0 ) * IntraBurstInterval , IntraBurstNoise ) - 1e-6 ;
     if ( set_burst  == 0.0 ) {
       burst_on = next_burst_on ;
       next_burst_on = burst_on + interval ( _threadargscomma_ InterBurstInterval , InterBurstIntervalNoise ) ;
       set_burst = 1.0 ;
       }
     inter_burst_ISI = ISI_modulated ( _threadargscomma_ tonic , sin_amp , sin_freq , sin_phase , event ) ;
     if ( start_background < start_burst  || event > start_background ) {
       event = event + interval ( _threadargscomma_ inter_burst_ISI , BackgroundNoise ) ;
       }
     else {
       event = burst_on ;
       }
     if ( event >= burst_on ) {
       burst = 1. ;
       event = burst_on ;
       Stim [ ((int) cnt ) ] = burst_on ;
       Stim [ ((int) cnt ) + 1 ] = burst_on + burst_off ;
       cnt = cnt + 2.0 ;
       }
     }
   if ( event > end ) {
     on = 0.0 ;
     }
    return 0; }
 
static double _hoc_event_time(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 event_time (  );
 return(_r);
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 1.0  && on  == 1.0 ) {
     y = 20.0 ;
     net_event ( _pnt, t ) ;
     event_time ( _threadargs_ ) ;
     last_event_t = t ;
     net_send ( _tqitem, _args, _pnt, t +  event - t , 1.0 ) ;
     net_send ( _tqitem, _args, _pnt, t +  .1 , 2.0 ) ;
     }
   if ( _lflag  == 2.0 ) {
     y = - 90.0 ;
     }
   } }

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   on = 1.0 ;
   toff = 1e9 ;
   y = - 90.0 ;
   burst = 0.0 ;
   burst_on = start_burst ;
   Stim [ 0 ] = burst_on ;
   cnt = 0.0 ;
   next_burst_on = burst_on + interval ( _threadargscomma_ InterBurstInterval , InterBurstIntervalNoise ) ;
   set_burst = 1.0 ;
   event = start_background ;
   event_time ( _threadargs_ ) ;
   while ( on  == 1.0  && event < 0.0 ) {
     event_time ( _threadargs_ ) ;
     }
   if ( on  == 1.0 ) {
     net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, t +  event , 1.0 ) ;
     }
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
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

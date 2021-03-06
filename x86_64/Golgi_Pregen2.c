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
 
#define nrn_init _nrn_init__Golgi_SpikeGenerator2
#define _nrn_initial _nrn_initial__Golgi_SpikeGenerator2
#define nrn_cur _nrn_cur__Golgi_SpikeGenerator2
#define _nrn_current _nrn_current__Golgi_SpikeGenerator2
#define nrn_jacob _nrn_jacob__Golgi_SpikeGenerator2
#define nrn_state _nrn_state__Golgi_SpikeGenerator2
#define _net_receive _net_receive__Golgi_SpikeGenerator2 
#define event_time event_time__Golgi_SpikeGenerator2 
 
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
#define start _p[0]
#define end _p[1]
#define y _p[2]
#define on _p[3]
#define time (_p + 4)
#define event _p[5004]
#define toff _p[5005]
#define indice _p[5006]
#define v _p[5007]
#define _tsav _p[5008]
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
 /* declaration of user functions */
 static double _hoc_event_time();
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
 "event_time", _hoc_event_time,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "start", "ms",
 "end", "ms",
 "time", "ms",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
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
"Golgi_SpikeGenerator2",
 "start",
 "end",
 0,
 "y",
 "on",
 "time[5000]",
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
 	_p = nrn_prop_data_alloc(_mechtype, 5009, _prop);
 	/*initialize range parameters*/
 	start = 100000;
 	end = 1e+10;
  }
 	_prop->param = _p;
 	_prop->param_size = 5009;
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
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Golgi_Pregen2_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 5009, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
 add_nrn_has_net_event(_mechtype);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Golgi_SpikeGenerator2 /home/stefano/Documenti/paperRevision/GL_Model/x86_64/Golgi_Pregen2.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int event_time(_threadargsproto_);
 
static int  event_time ( _threadargsproto_ ) {
   event = event + time [ ((int) indice ) ] ;
   indice = indice + 1.0 ;
   if ( event > end ) {
     on = 0.0 ;
     }
    return 0; }
 
static double _hoc_event_time(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r = 1.;
 event_time ( _p, _ppvar, _thread, _nt );
 return(_r);
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 1.0  && on  == 1.0 ) {
     y = 20.0 ;
     net_event ( _pnt, t ) ;
     event_time ( _threadargs_ ) ;
     net_send ( _tqitem, _args, _pnt, t +  event - t , 1.0 ) ;
     net_send ( _tqitem, _args, _pnt, t +  .1 , 2.0 ) ;
     }
   if ( _lflag  == 2.0 ) {
     y = - 90.0 ;
     }
   } }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
 {
   indice = 0.0 ;
   on = 1.0 ;
   toff = 1e9 ;
   y = - 90.0 ;
   event = start ;
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

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{
} return _current;
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
}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/stefano/Documenti/paperRevision/GL_Model/templates/golgi/Golgi_Pregen2.mod";
static const char* nmodl_file_text = 
  ": $Id: pregen2.mod 1.2 Wed, 02 Feb 2005 16:10:51 +0100 sergio $\n"
  ": comments at end\n"
  "\n"
  "NEURON	{ \n"
  "  POINT_PROCESS Golgi_SpikeGenerator2\n"
  "  RANGE y\n"
  "  RANGE fast_invl, slow_invl, burst_len, start, end, delay,on\n"
  "  RANGE noise,time\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	:burst_len	= 40		: burst length (# spikes)\n"
  "	start		= 100000 (ms)	: start of first interburst interval\n"
  "	end		= 1e10 (ms)	: time to stop bursting\n"
  "	:noise		= 1		: amount of randomeaness (0.0 - 1.0)\n"
  "	:delay		= 4 (ms)	: to avoid \n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	y\n"
  "	:burst\n"
  "	event (ms)\n"
  "	:burst_off (ms)\n"
  "	:burst_on (ms)\n"
  "	toff (ms)\n"
  "	on\n"
  "\n"
  "	time[5000] (ms)	\n"
  "	indice\n"
  "}\n"
  "\n"
  ":PROCEDURE inits(){\n"
  ":}\n"
  "\n"
  "INITIAL {	\n"
  "	:init()\n"
  "	indice=0\n"
  "	on = 1\n"
  "	toff = 1e9\n"
  "	y = -90\n"
  "	:burst = 0\n"
  "	event = start \n"
  "	event_time()\n"
  "	while (on == 1 && event < 0) {\n"
  "		event_time()\n"
  "	}\n"
  "	if (on == 1) {\n"
  "		net_send(event, 1)\n"
  "	}\n"
  "}	\n"
  "\n"
  "PROCEDURE event_time() {\n"
  "	event=event+time[indice] \n"
  "	indice=indice+1\n"
  "	if (event > end) {\n"
  "		on = 0\n"
  "	}\n"
  "}\n"
  "\n"
  "NET_RECEIVE (w) {\n"
  ":printf(\"Pregen receive t=%g flag=%g\\n\", t, flag) \n"
  "	if (flag == 1 && on == 1) {\n"
  "		y = 20\n"
  "		net_event(t)\n"
  "		event_time()\n"
  "		net_send(event - t, 1)\n"
  "		net_send(.1, 2)\n"
  "	}\n"
  "	if (flag == 2) {\n"
  "		y = -90\n"
  "	}\n"
  "}\n"
  "\n"
  "COMMENT\n"
  "Presynaptic spike generator\n"
  "---------------------------\n"
  "\n"
  "This mechanism has been written to be able to use synapses in a single\n"
  "neuron receiving various types of presynaptic trains.  This is a \"fake\"\n"
  "presynaptic compartment containing a fast spike generator.  The trains\n"
  "of spikes can be either periodic or noisy (Poisson-distributed), and \n"
  "either tonic or bursting.\n"
  "\n"
  "Parameters;\n"
  "   noise: 	between 0 (no noise-periodic) and 1 (fully noisy)\n"
  "   fast_invl: 	fast interval, mean time between spikes (ms)\n"
  "   slow_invl:	slow interval, mean burst silent period (ms), 0=tonic train\n"
  "   burst_len: 	mean burst length (nb. spikes)\n"
  "\n"
  "Written by Z. Mainen, modified by A. Destexhe, The Salk Institute\n"
  "\n"
  "Modified by Michael Hines for use with CVode\n"
  "\n"
  "Modified by Michael Hines to use logical event style with NET_RECEIVE\n"
  "ENDCOMMENT\n"
  "\n"
  ;
#endif

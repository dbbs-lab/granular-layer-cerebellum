#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _Golgi_BK_reg(void);
extern void _Golgi_CALC_reg(void);
extern void _Golgi_CALC_ca2_reg(void);
extern void _Golgi_Ca_HVA_reg(void);
extern void _Golgi_Ca_LVA_reg(void);
extern void _Golgi_KA_reg(void);
extern void _Golgi_KM_reg(void);
extern void _Golgi_KV_reg(void);
extern void _Golgi_Na_reg(void);
extern void _Golgi_NaP_reg(void);
extern void _Golgi_NaR_reg(void);
extern void _Golgi_Pregen_reg(void);
extern void _Golgi_Pregen2_reg(void);
extern void _Golgi_SK2_reg(void);
extern void _Golgi_hcn1_reg(void);
extern void _Golgi_hcn2_reg(void);
extern void _Golgi_lkg_reg(void);
extern void _vecevent_reg(void);
extern void _GRANULE_Ampa_det_Prel_reg(void);
extern void _GRANULE_Ampa_det_vi_reg(void);
extern void _GRANULE_Ampa_stoch_vi_reg(void);
extern void _GRANULE_Gaba_det_vi_reg(void);
extern void _GRANULE_Nmda_det_vi_reg(void);
extern void _GRANULE_Nmda_leak_reg(void);
extern void _GRANULE_Nmda_stoch_vi_reg(void);
extern void _Golgi_PF_AMPA_reg(void);
extern void _Golgi_PF_NMDA_reg(void);
extern void _gapj_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," ./Golgi_BK.mod");
    fprintf(stderr," ./Golgi_CALC.mod");
    fprintf(stderr," ./Golgi_CALC_ca2.mod");
    fprintf(stderr," ./Golgi_Ca_HVA.mod");
    fprintf(stderr," ./Golgi_Ca_LVA.mod");
    fprintf(stderr," ./Golgi_KA.mod");
    fprintf(stderr," ./Golgi_KM.mod");
    fprintf(stderr," ./Golgi_KV.mod");
    fprintf(stderr," ./Golgi_Na.mod");
    fprintf(stderr," ./Golgi_NaP.mod");
    fprintf(stderr," ./Golgi_NaR.mod");
    fprintf(stderr," ./Golgi_Pregen.mod");
    fprintf(stderr," ./Golgi_Pregen2.mod");
    fprintf(stderr," ./Golgi_SK2.mod");
    fprintf(stderr," ./Golgi_hcn1.mod");
    fprintf(stderr," ./Golgi_hcn2.mod");
    fprintf(stderr," ./Golgi_lkg.mod");
    fprintf(stderr," ../mossy//vecevent.mod");
    fprintf(stderr," ../synapse//GRANULE_Ampa_det_Prel.mod");
    fprintf(stderr," ../synapse//GRANULE_Ampa_det_vi.mod");
    fprintf(stderr," ../synapse//GRANULE_Ampa_stoch_vi.mod");
    fprintf(stderr," ../synapse//GRANULE_Gaba_det_vi.mod");
    fprintf(stderr," ../synapse//GRANULE_Nmda_det_vi.mod");
    fprintf(stderr," ../synapse//GRANULE_Nmda_leak.mod");
    fprintf(stderr," ../synapse//GRANULE_Nmda_stoch_vi.mod");
    fprintf(stderr," ../synapse//Golgi_PF_AMPA.mod");
    fprintf(stderr," ../synapse//Golgi_PF_NMDA.mod");
    fprintf(stderr," ../gapj//gapj.mod");
    fprintf(stderr, "\n");
  }
  _Golgi_BK_reg();
  _Golgi_CALC_reg();
  _Golgi_CALC_ca2_reg();
  _Golgi_Ca_HVA_reg();
  _Golgi_Ca_LVA_reg();
  _Golgi_KA_reg();
  _Golgi_KM_reg();
  _Golgi_KV_reg();
  _Golgi_Na_reg();
  _Golgi_NaP_reg();
  _Golgi_NaR_reg();
  _Golgi_Pregen_reg();
  _Golgi_Pregen2_reg();
  _Golgi_SK2_reg();
  _Golgi_hcn1_reg();
  _Golgi_hcn2_reg();
  _Golgi_lkg_reg();
  _vecevent_reg();
  _GRANULE_Ampa_det_Prel_reg();
  _GRANULE_Ampa_det_vi_reg();
  _GRANULE_Ampa_stoch_vi_reg();
  _GRANULE_Gaba_det_vi_reg();
  _GRANULE_Nmda_det_vi_reg();
  _GRANULE_Nmda_leak_reg();
  _GRANULE_Nmda_stoch_vi_reg();
  _Golgi_PF_AMPA_reg();
  _Golgi_PF_NMDA_reg();
  _gapj_reg();
}

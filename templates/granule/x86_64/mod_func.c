#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _GRANULE_CA_reg(void);
extern void _GRANULE_CALC_reg(void);
extern void _GRANULE_KA_reg(void);
extern void _GRANULE_KCA_reg(void);
extern void _GRANULE_KIR_reg(void);
extern void _GRANULE_KM_reg(void);
extern void _GRANULE_KV_reg(void);
extern void _GRANULE_LKG1_reg(void);
extern void _GRANULE_LKG2_reg(void);
extern void _GRANULE_NA_reg(void);
extern void _GRANULE_NAR_reg(void);
extern void _GRANULE_PNA_reg(void);
extern void _MF_pregen_modul_reg(void);
extern void _Release_site_reg(void);
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

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," ./GRANULE_CA.mod");
    fprintf(stderr," ./GRANULE_CALC.mod");
    fprintf(stderr," ./GRANULE_KA.mod");
    fprintf(stderr," ./GRANULE_KCA.mod");
    fprintf(stderr," ./GRANULE_KIR.mod");
    fprintf(stderr," ./GRANULE_KM.mod");
    fprintf(stderr," ./GRANULE_KV.mod");
    fprintf(stderr," ./GRANULE_LKG1.mod");
    fprintf(stderr," ./GRANULE_LKG2.mod");
    fprintf(stderr," ./GRANULE_NA.mod");
    fprintf(stderr," ./GRANULE_NAR.mod");
    fprintf(stderr," ./GRANULE_PNA.mod");
    fprintf(stderr," ./MF_pregen_modul.mod");
    fprintf(stderr," ../mossy//Release_site.mod");
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
    fprintf(stderr, "\n");
  }
  _GRANULE_CA_reg();
  _GRANULE_CALC_reg();
  _GRANULE_KA_reg();
  _GRANULE_KCA_reg();
  _GRANULE_KIR_reg();
  _GRANULE_KM_reg();
  _GRANULE_KV_reg();
  _GRANULE_LKG1_reg();
  _GRANULE_LKG2_reg();
  _GRANULE_NA_reg();
  _GRANULE_NAR_reg();
  _GRANULE_PNA_reg();
  _MF_pregen_modul_reg();
  _Release_site_reg();
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
}

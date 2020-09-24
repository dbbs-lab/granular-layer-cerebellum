#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _GRC_CA_reg(void);
extern void _GRC_CALC_reg(void);
extern void _GRC_KA_reg(void);
extern void _GRC_KCA_reg(void);
extern void _GRC_KIR_reg(void);
extern void _GRC_KM_reg(void);
extern void _GRC_KV_reg(void);
extern void _GRC_LKG1_reg(void);
extern void _GRC_LKG2_reg(void);
extern void _GRC_NA_reg(void);
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

    fprintf(stderr," ./GRC_CA.mod");
    fprintf(stderr," ./GRC_CALC.mod");
    fprintf(stderr," ./GRC_KA.mod");
    fprintf(stderr," ./GRC_KCA.mod");
    fprintf(stderr," ./GRC_KIR.mod");
    fprintf(stderr," ./GRC_KM.mod");
    fprintf(stderr," ./GRC_KV.mod");
    fprintf(stderr," ./GRC_LKG1.mod");
    fprintf(stderr," ./GRC_LKG2.mod");
    fprintf(stderr," ./GRC_NA.mod");
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
  _GRC_CA_reg();
  _GRC_CALC_reg();
  _GRC_KA_reg();
  _GRC_KCA_reg();
  _GRC_KIR_reg();
  _GRC_KM_reg();
  _GRC_KV_reg();
  _GRC_LKG1_reg();
  _GRC_LKG2_reg();
  _GRC_NA_reg();
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

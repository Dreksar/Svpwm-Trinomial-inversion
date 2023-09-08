#include "Smping.h"
#include "adc.h"
#include "Ave_FL.h"

AVE Ave_uV,Ave_uI,Ave_vV,Ave_vI,Ave_wV,Ave_wI;

uint16_t AD_Buf[7]={0};



void Get_ADC(AD_Detc *AD_detc)
{
		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)AD_Buf,7);
	  
		AD_detc->Udetc_f=(AD_Buf[0]/4096.0f*3.3f);
		AD_detc->Vdetc_f=(AD_Buf[1]/4096.0f*3.3f);
		AD_detc->Wdetc_f=(AD_Buf[2]/4096.0f*3.3f);
	  
	  AD_detc->Uidetc_f=(AD_Buf[3]/4096.0f*3.3f);
	  AD_detc->Videtc_f=(AD_Buf[4]/4096.0f*3.3f);
	  AD_detc->Widetc_f=(AD_Buf[5]/4096.0f*3.3f);
	
}

void Get_Real(AD_Detc *AD_detc)
{
	AD_detc->uV_ref=Ave_Sam(AD_detc->Udetc_f,10,&Ave_uV);
	AD_detc->uI_ref=Ave_Sam(AD_detc->Uidetc_f,10,&Ave_uI);
	AD_detc->vV_ref=Ave_Sam(AD_detc->Vdetc_f,10,&Ave_vV);
	AD_detc->vI_ref=Ave_Sam(AD_detc->Videtc_f,10,&Ave_vI);
	AD_detc->wV_ref=Ave_Sam(AD_detc->Wdetc_f,10,&Ave_wV);
	AD_detc->wI_ref=Ave_Sam(AD_detc->Widetc_f,10,&Ave_wI);
	
	AD_detc->uV_data=(AD_detc->uV_ref-1.654f)/0.0202f;
	AD_detc->uI_data=(AD_detc->uI_ref-1.654f)/0.4f;
	AD_detc->vV_data=(AD_detc->vV_ref-1.654f)/0.0202f;
	AD_detc->vI_data=(AD_detc->vI_ref-1.654f)/0.4f;
	AD_detc->wV_data=(AD_detc->wV_ref-1.654f)/0.0202f;
	AD_detc->wI_data=(AD_detc->wI_ref-1.654f)/0.4f;
	
}

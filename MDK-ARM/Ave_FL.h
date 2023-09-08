#ifndef _AVE_FL_H
#define _AVE_FL_H

#include "Ave_FL.h"
#include "main.h"


typedef struct
{
	//·´Cleck±ä»»

  float Ave[200];
	float ref;
	uint16_t Ave_flag;
	uint16_t n;
	float sum;
	
}AVE;

float Ave_Sam(float u_in,int Sam_num,AVE *Ave);
#endif
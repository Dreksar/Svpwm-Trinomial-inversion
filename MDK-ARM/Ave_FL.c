#include "Ave_FL.h"



float Ave_Sam(float u_in,int Sam_num,AVE *Ave)
{
  
	if(Ave->Ave_flag==1)
		{
			Ave->Ave[Ave->n]=u_in;
		}
		if(Ave->Ave_flag==0)
		{
			Ave->Ave[Ave->n]=u_in;
			Ave->n++;
			
		}
		
		if(Ave->n==Sam_num || Ave->Ave_flag==1)
		{
			
			for(Ave->n=0;Ave->n<Sam_num;Ave->n++)
			{
				Ave->sum=Ave->Ave[Ave->n]+Ave->sum;
				
			}
			Ave->ref=Ave->sum / Sam_num;
			for(Ave->n=0;Ave->n<Sam_num;Ave->n++)
			{
				Ave->Ave[Ave->n]=Ave->Ave[Ave->n+1];
			}
			Ave->sum=0;
			Ave->Ave_flag=1;
		}
		return Ave->ref;
}


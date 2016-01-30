#include "pf_calc_data_file_io.h"

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
PF_CALC_DATA_FILE_IEEE* ReadDataFileIEEE(const char* fileName)
{
				PF_CALC_DATA_FILE_IEEE*	pfdf=(PF_CALC_DATA_FILE_IEEE*)
																	malloc(sizeof(PF_CALC_DATA_FILE_IEEE));



				FILE									*	fp=fopen(fileName,"wb");



				pfdf->blNodeNbr=0;
				pfdf->pqNodeNbr=0;
				pfdf->pvNodeNbr=0;

				PF_CALC_DATA_TYPE   r,x,bb,gij,bij,k0,kmin,kmax;
				pf_uint32						nodeNbr,branchNbr;
				pf_uint32						tmp,branchNo=0,nodeNoi=0,nodeNoj=0;
				PF_CALC_DATA_TYPE	baseCapacity;
				PF_CALC_DATA_TYPE	central;
				pf_uint32						targetFunctionClassCode;
				PF_CALC_DATA_TYPE	ble,blf;
				pf_uint32						blNodeNo;

				PF_CALC_DATA_TYPE	Pg,Qg,Pl,Ql;


/*Get the header of IEEE standard file.*/
				fscanf(fp,"%d %d %lf %d %lf",&pfdf->header.nodeNbr,&pfdf->header.branchNbr,&pfdf->header.Capacity,&pfdf->header.maxIterTimes,&pfdf->header.centralPara
						);
				fscanf(fp,"%lf %d",&pfdf->header.precision,&pfdf->header.functionClass);
				fscanf(fp,"%d %lf",&pfdf->header.blNodeNo,&pfdf->header.blNodeE);
/*Done.*/

/*Get the parameters of Lines.*/
				fscanf(fp,"%d",&tmp);         
				/*线路参数*/
				fscanf(fp,"%d",&branchNo);     
				pf_uint32	i_linep=0;
				while(branchNo!=0)                                           
				{	
					pfdf->lineParameters[i_linep]=(PF_CALC_DF_IEEE_LINE_PARA)malloc(sizeof(PF_CALC_DF_IEEE_LINE_PARA));
					fscanf(fp,"%d %d %lf %lf %lf",&nodeNoi,&nodeNoj,&r,&x,&bb); 
					pfdf->lineParameters[i_linep].bDiv2=bb;
					pfdf->lineParameters[i_linep].branchNo=branchNo;
					pfdf->lineParameters[i_linep].nodei=nodeNoi;
					pfdf->lineParameters[i_linep].nodej=nodeNoj;
					fscanf(fp,"%d",&branchNo);	
					i_linep++;
				}
/*Done.*/

/*Get the parameters of Grounding Lines.*/
				fscanf(fp,"%d",&tmp); 
				/*接地支路参数*/
				fscanf(fp,"%d",&nodeNoi);    
				pf_uint32	i_glinep=0;
				while(branchNo!=0)                               
				{	
					fscanf(fp,",%lf",&gij);
					pfdf->gLineParameters[i_glinep]=(PF_CALC_DF_IEEE_GNDLINE_PARA)malloc(sizeof(PF_CALC_DF_IEEE_GNDLINE_PARA));      
					pfdf->gLineParameters[i_glinep].nodeNo=nodeNoi;
					pfdf->gLineParameters[i_glinep].G=gij;
					fscanf(fp,"%d",&nodeNoi);
					i_glinep++;
				}
/*Done.*/


/*Get the parameters of Transformer.*/
				fscanf(fp,"%d",&tmp);	
				/*变压器参数*/
				fscanf(fp,"%d",&branchNo); 
				pf_uint32 i_tp=0;
				while(branchNo!=0)          
				{	
					fscanf(fp,"%d %d %lf %lf %lf %lf %lf",&nodeNoi,&nodeNoj,&r,&x,&k0,&kmin,&kmax);
					pfdf->transParameters[i_tp]=(PF_CALC_DF_IEEE_TRANSFORMER_PARA)
																	malloc(sizeof(PF_CALC_DF_IEEE_TRANSFORMER_PARA));      
					pfdf->transParameters[i_tp].branchNo=branchNo;
					pfdf->transParameters[i_tp].k0=k0;
					pfdf->transParameters[i_tp].kMax=kmax;
					pfdf->transParameters[i_tp].kMin=kmin;
					pfdf->transParameters[i_tp].nodei=nodeNoi;
					pfdf->transParameters[i_tp].nodej=nodeNoj;
					pfdf->transParameters[i_tp].R=r;
					pfdf->transParameters[i_tp].X=x;
					fscanf(fp,"%d",&branchNo);			
					i_tp++;
				}
/*Done.*/

/*Get the Running parameters.*/

				fscanf(fp,"%d",&tmp);	
				fscanf(fp,"%d",&nodeNoi);  
				pf_uint32 i_run=0;
				while(branchNo!=0)          
				{	
					pfdf->runningParameters[i_run]=(pf_calc_data_file_ieee_running_para)(malloc(sizeof(pf_calc_data_file_ieee_running_para)));
					fscanf(fp,"%lf %lf %lf %lf",&Pg,&Qg,&Pl,&Ql);
					pfdf->runningParameters[i_run].nodeNo=nodeNoi;
					pfdf->runningParameters[i_run].Pg=Pg;
					pfdf->runningParameters[i_run].Qg=Qg;
					pfdf->runningParameters[i_run].Pl=Pl;
					pfdf->runningParameters[i_run].Ql=Ql;
					fscanf(fp,"%d",&nodeNoi);	
					i_run++;
				}
/*Done.*/

/*Get the PV Node parameters.*/
				PF_CALC_DATA_TYPE	pvQmin,pvQmax,u;
				fscanf(fp,"%d",&tmp);	
				fscanf(fp,"%d",&nodeNoi);  
				pf_uint32 i_pvp=0;
				while(nodeNoi!=0)          
				{
					pfdf->pvNodeParameters[i_pvp]=(PF_CALC_DF_IEEE_PVNODE_PARA)
						malloc(sizeof(PF_CALC_DF_IEEE_PVNODE_PARA));
					fscanf(fp,"%lf %lf %lf",&u,&pvQmin,&pvQmax);

					pfdf->pvNodeParameters[i_pvp].nodeNo=nodeNoi;
					pfdf->pvNodeParameters[i_pvp].QMax=pvQmax;
					pfdf->pvNodeParameters[i_pvp].QMin=pvQmin;
					pfdf->pvNodeParameters[i_pvp].u=u;

					fscanf(fp,"%d",&nodeNoi);	
					i_pvp++;
				}
/*Done.*/

/*Get the generator cost parameters.*/
				PF_CALC_DATA_TYPE	a,b,c,gcPgmax,gcPgmin;
				fscanf(fp,"%d",&tmp);	
				fscanf(fp,"%d",&nodeNoi);  
				pf_uint32 i_gcp=0;
				while(nodeNoi!=0)          
				{
					pfdf->gcostParameters[i_gcp]=(PF_CALC_DF_IEEE_GENERATOR_COST_PARA)
						malloc(sizeof(PF_CALC_DF_IEEE_GENERATOR_COST_PARA));
					fscanf(fp,"%lf %lf %lf %lf %lf",&c,&b,&a,&gcPgmin,&gcPgmax);

					pfdf->gcostParameters[i_gcp].a=a;
					pfdf->gcostParameters[i_gcp].b=b;
					pfdf->gcostParameters[i_gcp].c=c;
					pfdf->gcostParameters[i_gcp].nodeNo=nodeNoi;
					pfdf->gcostParameters[i_gcp].PgMax=gcPgmax;
					pfdf->gcostParameters[i_gcp].PgMin=gcPgmin;
					fscanf(fp,"%d",&nodeNoi);	
					i_gcp++;
				}
/*Done.*/
				fclose(fp);
				return	pfdf;

}
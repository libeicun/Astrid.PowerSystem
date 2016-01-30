#include "pf_calc_data_io.h"



#include <stdio.h>	        //定义输入/输出函数
#include <stdlib.h>
#include <string.h>
 int		PfDataCheck(PF_CALC_CB* pfcb,ePfDataStructType datatructType)
 {
		switch(datatructType)
		{
		case ePfDataStructTypeLBCTest:{
			if(pfcb->dataCheckFlag==127)
				return 1;
			else
				return 0;
			break;}
		default:{break;}
		}
 }
void		PfDataReadFile		(PF_CALC_CB* pfcb, const char* fileName, ePfDataStructType datatructType)
{
	FILE*		fp;
	fp=fopen(fileName,"rb");
	if(fp==NULL)
		return;

	switch(datatructType)
	{
	case ePfDataStructTypeLBCTest:
		{
#if 0
			char		sf[20];
			int i,j,nbr;
			PF_CALC_DATA_TYPE	data;
			/*读PQ、PV、BL节点数*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"NODE_NBR")==0)
			{
				fscanf(fp,"%d %d %d",&(pfcb->pqNodeNbr),&(pfcb->pvNodeNbr),&(pfcb->blNodeNbr));
			}

			nbr=pfcb->blNodeNbr+pfcb->pqNodeNbr+pfcb->pvNodeNbr;

			/*读最大迭代次数和迭代精度*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"ITER_CTRL")==0)
			{
				fscanf(fp,"%d %lf",&(pfcb->maxIterTimes),&(pfcb->precision));
			}

			/*读电导矩阵*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"G")==0)
			{

				for(i=0;i<nbr;i++)
					for(j=0;j<nbr;j++)
					{
						fscanf(fp,"%lf",&data);
						if(abs(data)>pfcb->precision)
							SetElem(pfcb->Gij,data,i,j);

					}
			}
			/*读电纳矩阵*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"B")==0)
			{
				for(i=0;i<nbr;i++)
					for(j=0;j<nbr;j++)
					{
						fscanf(fp,"%lf",&data);
						if(abs(data)>pfcb->precision)
							SetElem(pfcb->Bij,data,i,j);

					}
			}

			/*读有功给定*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"P_SET")==0)
			{
				for(i=0;i<nbr;i++)
				{
					fscanf(fp,"%lf",&(pfcb->PiSET[i]));
				}

			}

			/*读无功给定*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"Q_SET")==0)
			{
				for(i=0;i<nbr;i++)
				{
					fscanf(fp,"%lf",&(pfcb->QiSET[i]));
				}

			}


			/*读电压给定*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"U2_SET")==0)
			{
				for(i=0;i<pfcb->pvNodeNbr;i++)
				{
					fscanf(fp,"%lf",&(pfcb->U2iSET[i]));
				}

			}

			/*读迭代初始值：电压实部*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"e_INIT")==0)
			{
				for(i=0;i<nbr;i++)
				{
					fscanf(fp,"%lf",&(pfcb->ei[i]));
				}

			}

			/*读迭代初始值：电压实部*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"f_INIT")==0)
			{
				for(i=0;i<nbr;i++)
				{
					fscanf(fp,"%lf",&(pfcb->fi[i]));
				}

			}


			/*读最大迭代次数和迭代精度*/
			fscanf(fp,"%s",sf);
			if(strcmp(sf,"DATA_CHECK")==0)
			{
				fscanf(fp,"%d",&(pfcb->dataCheckFlag));
			}
#endif
			break;
		}
		case ePfDataStructTypeIEEE:
			{
				PF_CALC_CB* pfcb=(PF_CALC_CB*) malloc(sizeof(PF_CALC_CB));
	int pqNodeNbr=0, pvNodeNbr=0, blNodeNbr  =0;
	
	pfcb->pvNodeNbr=pvNodeNbr;
	pfcb->blNodeNbr=blNodeNbr;
	pfcb->pqNodeNbr=pqNodeNbr;
	
	int pqvNbr	=pqNodeNbr+pvNodeNbr;
	int nbr			=pqvNbr+blNodeNbr;
	int pqvNbrTimes2=pqvNbr*2;

	pfcb->curIterTime=0;
	pfcb->dataCheckFlag=0;
	pfcb->maxIterTimes=maxIterTimes;
	pfcb->precision=precision;

	/*allocate all the fields which needs dynamic memory of *pfcb.*/



	/*	set the .deltaEF[], .deltaPQPU2[], .HNJLRS[][] fields to zero.
		if don't clear these field before use them, problems will occur.*/
	for (int i=0;i<pqvNbrTimes2;i++)
	{
		pfcb->deltaEF[i]=0;
		pfcb->deltaPQPU2[i]=0;
		for (int j=0;j<pqvNbrTimes2;j++)
		{
			pfcb->HNJLRS[i][j]=0;
		}
	}
	/*set the .Bij[][], .Gij[][] fields to zero.*/
	/*for (int i=0;i<nbr;i++)
	{
		for (int j=0;j<nbr;j++)
		{
			SetElem(pfcb->Bij,0,i,j);
			SetElem(pfcb->Gij,0,i,j);
		}
	}*/

	/*set the .blNodeTabl[], pqNodeTable[], pvNodeTable[] fields to zero.*/
	PF_CALC_NODE_BL blNode;
	blNode.e=0;blNode.f=0;blNode.index=0;blNode.Pg=0;blNode.Pl=0;blNode.Qg=0;blNode.Ql=0;
	for (int i=0;i<blNodeNbr;i++)
	{
		pfcb->blNodeTable[i]=blNode;
	}



	for (int i=0;i<pvNodeNbr;i++)
	{
		pfcb->pvNodeTable[i]=pvNode;
	}



	/*After read the data file, update the .id.offset field.*/
	for(pf_uint32 i=0;i<blNodeNbr)
	{
		for(pf_uint32 j=0;j<pqNodeNbr;j++)
		{
			if(pfcb->pqNodeTable[j].id.index>pfcb->blNodeTable[i].index)
				pfcb->pqNodeTable[j].id.offset++;
		}

		for(pf_uint32 j=0;j<pvNodeNbr;j++)
		{
			if(pfcb->pvNodeTable[j].id.index>pfcb->blNodeTable[i].index)
				pfcb->pvNodeTable[j].id.offset++;
		}
	}



				PF_CALC_DATA_TYPE   r,x,bb,gij,bij,k0;
				pf_uint32						nodeNbr,branchNbr;
				pf_uint32								tmp,branchNo=0,nodeNoi=0,nodeNoj=0;
				PF_CALC_DATA_TYPE	baseCapacity;
				PF_CALC_DATA_TYPE	central;
				pf_uint32								targetFunctionClassCode;
				PF_CALC_DATA_TYPE	ble,blf;
				pf_uint32						blNodeNo;
/*Get the header of IEEE standard file.*/
				fscanf(fp,"%d %d %lf %lf %d %lf",&nodeNbr,&branchNbr,&baseCapacity,&pfcb->maxIterTimes,&central);
/*allocate the memory for pfcb->Gij and Bij.*/
				pfcb->Bij	=CreateEmptySMatrix(nodeNbr,nodeNbr);
				pfcb->Gij	=CreateEmptySMatrix(nodeNbr,nodeNbr);
/*QU: Does an IEEE standard system only include one BL Node?*/
				blNodeNbr=1;
				pfcb->blNodeTable=(PF_CALC_NODE_BL*)malloc(sizeof(PF_CALC_NODE_BL)*(blNodeNbr));
				fscanf(fp,"%lf %d",&pfcb->precision,&targetFunctionClassCode);
				fscanf(fp,"%d %lf",&pfcb->blNodeTable[0].index,&ble);
				/*The Index of balance Node, 0*/
				pfcb->blNodeTable[0].index-=1;
				/*平衡节点电压数据*/
				pfcb->blNodeTable[0].e=ble;
/*Done.*/
/*Get the parameters of Lines and Update pfcb->Gij and Bij.*/
				fscanf(fp,"%d",&tmp);         
				/*线路参数*/
				fscanf(fp,"%d",&branchNo);                          
				while(branchNo!=0)                                           
				{	
					fscanf(fp,"%d %d %lf %lf %lf",&nodeNoi,&nodeNoj,&r,&x,&bb); 
					gij=r/(r*r+x*x);             
					bij=-x/(r*r+x*x);
					PF_CALC_DATA_TYPE	t;
#if 0
					pfcb->Gij[nodeNoj-1][nodeNoi-1]=-gij;             	
					pfcb->Gij[nodeNoi-1][nodeNoj-1]=-gij;						
					pfcb->Bij[nodeNoj-1][nodeNoi-1]=-bij;				    
					pfcb->Bij[nodeNoi-1][nodeNoj-1]=-bij;
					pfcb->Gij[nodeNoi-1][nodeNoi-1]=pfcb->Gij[nodeNoi-1][nodeNoi-1]+gij;
					pfcb->Bij[nodeNoi-1][nodeNoi-1]=pfcb->Bij[nodeNoi-1][nodeNoi-1]+bij+bb;                     //因为线路电纳只包含在自电纳中，所以bb加在b[i][i]和b[j][j]里面
					pfcb->Gij[nodeNoj-1][nodeNoj-1]=pfcb->Gij[nodeNoj-1][nodeNoj-1]+gij;
					pfcb->Bij[nodeNoj-1][nodeNoj-1]=pfcb->Bij[nodeNoj-1][nodeNoj-1]+bij+bb;
					
#endif
					SetElem(pfcb->Gij,-gij,nodeNoj-1,nodeNoi-1);             	
					SetElem(pfcb->Gij,-gij,nodeNoi-1,nodeNoj-1);					
					SetElem(pfcb->Bij,-bij,nodeNoj-1,nodeNoi-1);				    
					SetElem(pfcb->Bij,-bij,nodeNoi-1,nodeNoj-1);

					GetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,&t);
					SetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,t+gij);
					GetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,&t);
					SetElem(pfcb->Bij,nodeNoi-1,nodeNoi-1,t+bij+bb);                     //因为线路电纳只包含在自电纳中，所以bb加在b[i][i]和b[j][j]里面
					GetElem(pfcb->Gij,nodeNoj-1,nodeNoj-1,&t);
					SetElem(pfcb->Gij,nodeNoj-1,nodeNoj-1,t+gij);
					GetElem(pfcb->Gij,nodeNoj-1,nodeNoj-1,&t);
					SetElem(pfcb->Bij,nodeNoj-1,nodeNoj-1,t+bij+bb);

					fscanf(fp,"%d",&branchNo);			   
				}
/*Done.*/

/*Get the parameters of Grounding Lines and Update pfcb->Gij and Bij.*/
				fscanf(fp,"%d",&tmp); 
				/*接地支路参数*/
				fscanf(fp,"%d",&branchNo);    
				while(branchNo!=0)                               
				{	
					fscanf(fp,",%d %lf %lf",&nodeNoi,&r,&x);
					PF_CALC_DATA_TYPE	t;
					GetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,&t);
					SetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,t+r);
					GetElem(pfcb->Bij,nodeNoi-1,nodeNoi-1,&t);
					SetElem(pfcb->Bij,nodeNoi-1,nodeNoi-1,t+x);        
					fscanf(fp,"%d",&branchNo);		      
				}
/*Done.*/
/*Get the parameters of Transformer and Grounding Lines and Update pfcb->Gij and Bij.*/
				fscanf(fp,"%d",&tmp);	
				/*变压器参数*/
				fscanf(fp,"%d",&branchNo);    
				while(branchNo!=0)          
				{	
					PF_CALC_DATA_TYPE	t;
					fscanf(fp,"%d %d %lf %lf %lf",&nodeNoi,&nodeNoj,&r,&x,&k0);
					gij=r/(r*r+x*x);
					bij=-x/(r*r+x*x);	//归算到j点
					SetElem(pfcb->Gij,nodeNoi-1,nodeNoj-1,-gij/k0);
					SetElem(pfcb->Gij,nodeNoj-1,nodeNoi-1,gij/k0);
					SetElem(pfcb->Bij,nodeNoi-1,nodeNoj-1,-bij/k0);
					SetElem(pfcb->Bij,nodeNoj-1,nodeNoi-1,-bij/k0);

					GetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,&t);
					SetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,t+gij/k0/k0);
					GetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,&t);
					SetElem(pfcb->Gij,nodeNoi-1,nodeNoi-1,t+bij/k0/k0);
					GetElem(pfcb->Bij,nodeNoj-1,nodeNoj-1,&t);
					SetElem(pfcb->Bij,nodeNoj-1,nodeNoj-1,t+gij);
					GetElem(pfcb->Bij,nodeNoj-1,nodeNoj-1,&t);
					SetElem(pfcb->Bij,nodeNoj-1,nodeNoj-1,t+bij);
					fscanf(fp,"%d",&branchNo);			
				}
/*Done.*/
/*Here we get the Running parameters, or to say PQ Node Parameters from IEEE standard file.*/
				PF_CALC_DATA_TYPE	Pg,Qg,Pl,Ql;
				fscanf(fp,"%d",&tmp);	
				/*Running parameters.
				from these we know PQNode Number.*/
				PF_CALC_NODE_PQ pqNode;
				pqNode.e=0;pqNode.f=0;pqNode.id.index=0;pqNode.id.offset=0;pqNode.P=0;pqNode.Q=0;
				fscanf(fp,"%d",&nodeNoi);  
				pf_uint32 i_run=0;
				while(branchNo!=0)          
				{	
					pqNodeNbr++;
					pfcb->pqNodeTable[i_run]=(PF_CALC_NODE_PQ)(malloc(sizeof(PF_CALC_NODE_PQ)));
					pfcb->pqNodeTable[i_run]=pqNode;
					fscanf(fp,"%lf %lf %lf %lf",&Pg,&Qg,&Pl,&Ql);
					pfcb->pqNodeTable[i_run].P=Pg-Pl;
					pfcb->pqNodeTable[i_run].Q=Qg-Ql;
					pfcb->pqNodeTable[i_run].id.index=nodeNoi-1;
					fscanf(fp,"%d",&nodeNoi);	
					i_run++;
				}
/*Done.*/

/*Get the PV Node parameters.*/
				PF_CALC_DATA_TYPE	pvQmin,pvQmax;
				fscanf(fp,"%d",&tmp);	
				PF_CALC_NODE_PV pvNode;
				pvNode.e=0;pvNode.f=0;pvNode.id.index=0;pvNode.id.offset=0;pvNode.P=0;pvNode.Qg=0;pvNode.Ql=0;pvNode.U2=0;
				fscanf(fp,"%d",&nodeNoi);  
				pf_uint32 i_run=0;
				while(branchNo!=0)          
				{	
					pqNodeNbr++;
					pfcb->pqNodeTable[i_run]=(PF_CALC_NODE_PQ)(malloc(sizeof(PF_CALC_NODE_PQ)));
					pfcb->pqNodeTable[i_run]=pqNode;
					fscanf(fp,"%lf %lf %lf %lf",&Pg,&Qg,&Pl,&Ql);
					pfcb->pqNodeTable[i_run].P=Pg-Pl;
					pfcb->pqNodeTable[i_run].Q=Qg-Ql;
					pfcb->pqNodeTable[i_run].id.index=nodeNoi-1;
					fscanf(fp,"%d",&nodeNoi);	
					i_run++;
				}
/*Done.*/

				pfcb->deltaEF=(PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*(pqvNbrTimes2));
				pfcb->deltaPQPU2=(PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*(pqvNbrTimes2));
				for(int i=0;i<pqvNbrTimes2;i++)
				{
					pfcb->HNJLRS[i]=(PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*(pqvNbrTimes2));
				}
				pfcb->pvNodeTable=(PF_CALC_NODE_PV*)malloc(sizeof(PF_CALC_NODE_PV)*(pvNodeNbr));
				break;
			}
	default:{break;}
	}

	fclose(fp);


}



void		PfDataWriteFile		(PF_CALC_CB* pfcb, const char* fileName, ePfDataStructType datatructType)
{
	FILE*		fp;
	char		sf[10];
	int i,j,nbr;
	PF_CALC_DATA_TYPE	data;
nbr=pfcb->blNodeNbr+pfcb->pqNodeNbr+pfcb->pvNodeNbr;

	fp=fopen(fileName,"wb");
	if(fp==NULL)
		return;
	fprintf(fp,"%s","Test	Data	Output\n\n\n\n\n");


	fprintf(fp,"%s","NODE_NBR\n");
	fprintf(fp,"%d %d %d\n",(pfcb->pqNodeNbr),(pfcb->pvNodeNbr),(pfcb->blNodeNbr));

	

	fprintf(fp,"%s","ITER_CTRL\n");
	fprintf(fp,"%d %lf\n",(pfcb->maxIterTimes),(pfcb->precision));


	fprintf(fp,"%s","G\n");
	for(i=0;i<nbr;i++)
	{
		for(j=0;j<nbr;j++)
		{
			GetElem(pfcb->Gij,i,j,&data);
			fprintf(fp,"%lf ",data);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");

	fprintf(fp,"%s","B\n");
	for(i=0;i<nbr;i++)
	{
		for(j=0;j<nbr;j++)
		{
			GetElem(pfcb->Bij,i,j,&data);
			fprintf(fp,"%lf ",data);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");

	fprintf(fp,"%s","P_SET\n");
	for(i=0;i<nbr;i++)
	{
		fprintf(fp,"%lf ",(pfcb->PiSET[i]));
	}
	fprintf(fp,"\n");


	fprintf(fp,"%s","Q_SET\n");
	for(i=0;i<nbr;i++)
	{
		fprintf(fp,"%lf ",(pfcb->QiSET[i]));
	}
	fprintf(fp,"\n");



	fprintf(fp,"%s","U2_SET\n");
	for(i=0;i<pfcb->pvNodeNbr;i++)
	{
		fprintf(fp,"%lf ",(pfcb->U2iSET[i]));
	}
	fprintf(fp,"\n");


	fprintf(fp,"%s","e_INIT\n");
	for(i=0;i<nbr;i++)
	{
		fprintf(fp,"%lf ",(pfcb->ei[i]));
	}
	fprintf(fp,"\n");


	fprintf(fp,"%s","f_INIT\n");

	for(i=0;i<nbr;i++)
	{
		fprintf(fp,"%lf ",(pfcb->fi[i]));
	}
	fprintf(fp,"\n");

	fclose(fp);
}

void		PfResultOutput		(PF_CALC_CB* pfcb, const char* fileName)
{
	FILE*		fp;
	char		sf[10];
	int i,j,nbr;
	PF_CALC_DATA_TYPE	data;

nbr=pfcb->blNodeNbr+pfcb->pqNodeNbr+pfcb->pvNodeNbr;
int pqvNbr=pfcb->pqNodeNbr+pfcb->pvNodeNbr;

	PfStringDataAppendFile(fileName,"Once Iterate Data Output");
	Pf1DArrayDataAppendFile(fileName,pfcb->deltaPQPU2,"deltaPQPU2",pqvNbr*2," ");
	Pf2DArrayDataAppendFile(fileName,pfcb->HNJLRS,"HNJLRS",pqvNbr*2,pqvNbr*2," ",";");
	Pf1DArrayDataAppendFile(fileName,pfcb->deltaEF,"deltaEF",pqvNbr*2," ");

}



void Pf2DArrayDataAppendFile(
							const pf_char* filename,
							PF_CALC_DATA_TYPE data**,
							pf_char*					caption,
							pf_uint32 sizei,
							pf_uint32 sizej,
							pf_char* divChari,pf_char* divCharj)
{

	FILE*		fp;
	fp=fopen(filename,"a");
	if(fp==NULL)
		return;

	fprintf(fp,caption);
	fprintf(fp,"\n");
	for(pf_uint32 i=0;i<sizei;i++)
	{
		for(pf_uint32	j=0;j<sizej;j++)
		{
			fprintf(fp,"%8.5f",data[i][j]);
			fprintf(fp,divChari);
		}
		fprintf(fp,divCharj);
	}
	fprintf(fp,"\n");

	fclose(fp);
}

void Pf1DArrayDataAppendFile(
									const pf_char*					filename,
									PF_CALC_DATA_TYPE*   	data,
									pf_char*							caption,
									pf_uint32							sizei,
									pf_char*							divChari)
{

	FILE*		fp;
	fp=fopen(filename,"a");
	if(fp==NULL)
		return;

	fprintf(fp,caption);
	fprintf(fp,"\n");
		for(pf_uint32	i=0;i<sizei;i++)
		{
			fprintf(fp,"%8.5f",data[i]);
			fprintf(fp,divChari);
		}
		
	
	fprintf(fp,"\n");

	fclose(fp);
}

void PfStringDataAppendFile(
							pf_char*	filename;
pf_char*	str
)
{
	FILE*		fp;
	fp=fopen(filename,"a");
	if(fp==NULL)
		return;

    fprintf(fp,"\n");
	fprintf(fp,str);
	fprintf(fp,"\n");

	fclose(fp);
}
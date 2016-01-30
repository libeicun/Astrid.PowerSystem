#include "pf_calc.h"
#include "pf_calc_matrix_calc.h"
#include "pf_calc_data_io.h"
#include "pf_calc_def_data_type.h"
#include <math.h>
#include <stdio.h>
static int isConverge(PF_CALC_CB* pfcb);
static void setAiiBiiUseEquation441(
									PF_CALC_CB*	pfcb,
									pf_uint32			index_i,
									pf_uint32			nbrj
									);
static int UpdateEifiFromDeltaEifi(PF_CALC_CB* pfcb);
static	void	setHNRSWhenNotEqual(
									PF_CALC_CB	*pfcb,
									pf_uint32	index_iTimes2,
									pf_uint32	index_jTimes2,
									PF_CALC_DATA_TYPE	bij,
									PF_CALC_DATA_TYPE	gij,
									pf_uint32	index_i);
static	void	setHNRSWhenEqual(
									PF_CALC_CB	*pfcb,
									pf_uint32	index_iTimes2,
									pf_uint32	index_jTimes2,
									PF_CALC_DATA_TYPE	bij,
									PF_CALC_DATA_TYPE	gij,
									pf_uint32	index_i);
static	void	setHNJLWhenNotEqual(
								 PF_CALC_CB	*pfcb,
								 pf_uint32	index_iTimes2,
								 pf_uint32	index_jTimes2,
								 PF_CALC_DATA_TYPE	bij,
								 PF_CALC_DATA_TYPE	gij,
								 pf_uint32	index_i);
static	void	setHNJLWhenEqual(
								 PF_CALC_CB	*pfcb,
								 pf_uint32	index_iTimes2,
								 pf_uint32	index_jTimes2,
								 PF_CALC_DATA_TYPE	bij,
								 PF_CALC_DATA_TYPE	gij,
								 pf_uint32	index_i );
int Newton_RaphsonIter(PF_CALC_CB* pfcb)
{
#if 1
	do
	{
		
		if(pfcb->curIterTime>=pfcb->maxIterTimes)
		{
			printf("The Power Flow Cannot Converge!\nPlease check the input data.\n");
			break;
		}
		Newton_RaphsonIterOnetime(pfcb);
		SolveAEqualBx(pfcb->deltaPQPU2,pfcb->HNJLRS,pfcb->deltaEF,(pfcb->pqNodeNbr+pfcb->pvNodeNbr)*2,ePfSolveAeBxMethodLU);
		PfResultOutput(pfcb,"result_output.txt");
		UpdateEifiFromDeltaEifi(pfcb);
	}while(!isConverge((pfcb)))
		;
#endif
	return 0;
}

pf_int32 Newton_RaphsonIterOnetime(PF_CALC_CB* pfcb)
{
	pfcb->curIterTime++;
	pf_uint32 maxIter,blNbr=pfcb->blNodeNbr,pqNbr=pfcb->pqNodeNbr,pvNbr=pfcb->pvNodeNbr,Nbr=pqNbr+pvNbr+pfcb->blNodeNbr;
	pf_uint32 pqvNbr=pqNbr+pvNbr;
	pf_uint32	pqvNbrTimes2=2*pqvNbr;
	pf_uint32	pqNbrTimes2=2*pqNbr;
	pf_uint32 i=0,index=0,j=0,index_i,index_j;

	PF_CALC_DATA_TYPE data_gij,data_bij;
	PF_CALC_DATA_TYPE	p=0, q=0,u2=0;
/*Update the deltaP and deltaQ of equation 4-37 from the pqNodeTable[], use equation 4-38.*/
		for ( i=0;i<pqNbr;i++)
		{
			index_i=pfcb->pqNodeTable[i].id.index;
			p=0;
			q=0;
			for( j=0;j<pqNbr;j++)
			{
				index_j=pfcb->pqNodeTable[j].id.index;
				GetElem(pfcb->Gij,index_i,index_j,&data_gij);
				GetElem(pfcb->Bij,index_i,index_j,&data_bij);
				p+=pfcb->pqNodeTable[i].e*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))+pfcb->pqNodeTable[i].f*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
				q+=pfcb->pqNodeTable[i].f*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))-pfcb->pqNodeTable[i].e*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
			}
			for( j=0;j<pvNbr;j++)
			{

				index_j=pfcb->pvNodeTable[j].id.index;
				GetElem(pfcb->Gij,index_i,index_j,&data_gij);
				GetElem(pfcb->Bij,index_i,index_j,&data_bij);
				p+=pfcb->pqNodeTable[i].e*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))+pfcb->pqNodeTable[i].f*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
				q+=pfcb->pqNodeTable[i].f*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))-pfcb->pqNodeTable[i].e*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
			}
			for( j=0;j<blNbr;j++)
			{

				index_j=pfcb->blNodeTable[j].index;
				GetElem(pfcb->Gij,index_i,index_j,&data_gij);
				GetElem(pfcb->Bij,index_i,index_j,&data_bij);
				p+=pfcb->pqNodeTable[i].e*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))+pfcb->pqNodeTable[i].f*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
				q+=pfcb->pqNodeTable[i].f*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))-pfcb->pqNodeTable[i].e*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
			}
			index_i=pfcb->pqNodeTable[i].id.index-pfcb->pqNodeTable[i].id.offset;
			pfcb->deltaPQPU2[2*index_i]=pfcb->pqNodeTable[i].P-p;
			pfcb->deltaPQPU2[2*index_i+1]=pfcb->pqNodeTable[i].Q-q;
		}
/*Done.*/
/*Update the deltaP and deltaU2 of equation 4-37 from the pvNodeTable[], use equation 4-38/c.*/
		for (i=0;i<pvNbr;i++)
		{
			p=0;
			index_i=pfcb->pvNodeTable[i].id.index;
			for( j=0;j<pqNbr;j++)
			{
				index_j=pfcb->pqNodeTable[j].id.index;
				GetElem(pfcb->Gij,index_i,index_j,&data_gij);
				GetElem(pfcb->Bij,index_i,index_j,&data_bij);
				p+=pfcb->pvNodeTable[i].e*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))+pfcb->pvNodeTable[i].f*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
			}
			for( j=0;j<pvNbr;j++)
			{
				index_j=pfcb->pvNodeTable[j].id.index;
				GetElem(pfcb->Gij,index_i,index_j,&data_gij);
				GetElem(pfcb->Bij,index_i,index_j,&data_bij);
				p+=pfcb->pvNodeTable[i].e*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))+pfcb->pvNodeTable[i].f*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
			}
			for( j=0;j<blNbr;j++)
			{

				index_j=pfcb->blNodeTable[j].index;
				GetElem(pfcb->Gij,index_i,index_j,&data_gij);
				GetElem(pfcb->Bij,index_i,index_j,&data_bij);
				p+=pfcb->pvNodeTable[i].e*(data_gij*(*(pfcb->e[index_j]))-data_bij*(*(pfcb->f[index_j])))+pfcb->pvNodeTable[i].f*(data_gij*(*(pfcb->f[index_j]))+data_bij*(*(pfcb->e[index_j])));
			}
			u2=pfcb->pvNodeTable[i].e*pfcb->pvNodeTable[i].e+pfcb->pvNodeTable[i].f*pfcb->pvNodeTable[i].f;
			index_i=pfcb->pvNodeTable[i].id.index-pfcb->pvNodeTable[i].id.offset;
			pfcb->deltaPQPU2[2*index_i]=pfcb->pvNodeTable[i].P-p;
			pfcb->deltaPQPU2[2*index_i+1]=pfcb->pvNodeTable[i].U2*pfcb->pvNodeTable[i].U2-u2;
		}
/*Done.*/
//FOR TEST
#if 1
		PF_CALC_DATA_TYPE	data[8];
		for (i=0;i<8;i++)
		{
			data[i]=0;
		}
		for (i=0;i<8;i++)
		{
			data[i]=pfcb->deltaPQPU2[i];
		}
#endif
//FOR TEST

/*	100012
	Update the .aii[] and .bii[] of Equation 4-41/b, use Equation 4-41/a.*/
	/*for( i=0;i<pqNbr;i++)
	{	
		pf_f64 d;
		d=pfcb->pqNodeTable[i].e*pfcb->pqNodeTable[i].e+pfcb->pqNodeTable[i].f*pfcb->pqNodeTable[i].f;
		index=pfcb->pqNodeTable[i].id.index-pfcb->pqNodeTable[i].id.offset2;
		pfcb->aii[index]=(pfcb->pqNodeTable[i].P*pfcb->pqNodeTable[i].e+pfcb->pqNodeTable[i].Q*pfcb->pqNodeTable[i].f)/d;
		pfcb->bii[index]=(pfcb->pqNodeTable[i].P*pfcb->pqNodeTable[i].f-pfcb->pqNodeTable[i].Q*pfcb->pqNodeTable[i].e)/d;
	}*/
		for (pf_uint32	i=0;i<blNbr;i++)
		{
			index=pfcb->blNodeTable[i].index;
			setAiiBiiUseEquation441(pfcb,index,Nbr);
		}

		for (pf_uint32	i=0;i<pqNbr;i++)
		{
			index=pfcb->pqNodeTable[i].id.index;
			setAiiBiiUseEquation441(pfcb,index,Nbr);
		}
		for (pf_uint32 i=0;i<pvNbr;i++)
		{
			index=pfcb->pvNodeTable[i].id.index;
			setAiiBiiUseEquation441(pfcb,index,Nbr);
		}
/*	Done.
	100012*/

/*	100017
	Update the .HNJLRS[][] field, see Equation 4-41/a and 4-41/b. Because we will put only the PQ and PV data(exclude BL) in the Jacob Matrix
	and .deltaPQPU2[] and .deltaEF[], we use .id.index and .id.offset to ReCalc the actual index.*/
	//Update the part of PQ Node's.
	pf_uint32	index_iTimes2=0,index_jTimes2=0;
	pf_uint32	index_i2=0,index_j2=0;
	for (	i=0;i<pqNbr;i++)
	{
		index_i=pfcb->pqNodeTable[i].id.index;//-pfcb->pqNodeTable[i].id.offset;
		index_iTimes2=2*(pfcb->pqNodeTable[i].id.index-pfcb->pqNodeTable[i].id.offset);
		for ( j=0;j<pqNbr;j++)
		{
			index_j=pfcb->pqNodeTable[j].id.index;
			index_jTimes2=2*(pfcb->pqNodeTable[j].id.index-pfcb->pqNodeTable[j].id.offset);
			GetElem(pfcb->Gij,index_i,index_j,&data_gij);
			GetElem(pfcb->Bij,index_i,index_j,&data_bij);
			if(index_i==index_j)//See Equation 4-41/b
			{
				setHNJLWhenEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);
			}
			else//See Equation 4-41/a
			{
				setHNJLWhenNotEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);	
			}
		}
		for ( j=0;j<pvNbr;j++)
		{
			index_j=pfcb->pvNodeTable[j].id.index;
			index_jTimes2=2*(pfcb->pvNodeTable[j].id.index-pfcb->pvNodeTable[j].id.offset);
			GetElem(pfcb->Gij,index_i,index_j,&data_gij);
			GetElem(pfcb->Bij,index_i,index_j,&data_bij);
			if(index_i==index_j)//See Equation 4-41/b
			{
				setHNJLWhenEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);
			}
			else//See Equation 4-41/a
			{
				setHNJLWhenNotEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);	
			}
		}
	}
	//Update the part of PV Node's.
	for (	i=0;i<pvNbr;i++)
	{

		index_i=pfcb->pvNodeTable[i].id.index;//-pfcb->pvNodeTable[i].id.offset;
		index_iTimes2=2*(pfcb->pvNodeTable[i].id.index-pfcb->pvNodeTable[i].id.offset);
		for ( j=0;j<pqNbr;j++)
		{
			index_j=pfcb->pqNodeTable[j].id.index;//-pfcb->pvNodeTable[j].id.offset;
			index_jTimes2=2*(pfcb->pqNodeTable[j].id.index-pfcb->pqNodeTable[j].id.offset);
			GetElem(pfcb->Gij,index_i,index_j,&data_gij);
			GetElem(pfcb->Bij,index_i,index_j,&data_bij);
			if(index_i==index_j)//Use Equation 4-41/b
			{
				setHNRSWhenEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);
			}
			else//Use Equation 4-41/a
			{
				setHNRSWhenNotEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);	
			}
		}
		for ( j=0;j<pvNbr;j++)
		{
			index_j=pfcb->pvNodeTable[j].id.index;//-pfcb->pvNodeTable[j].id.offset;
			index_jTimes2=2*(pfcb->pvNodeTable[j].id.index-pfcb->pvNodeTable[j].id.offset);
			GetElem(pfcb->Gij,index_i,index_j,&data_gij);
			GetElem(pfcb->Bij,index_i,index_j,&data_bij);
			if(index_i==index_j)//Use Equation 4-41/b
			{
				setHNRSWhenEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);
			}
			else//Use Equation 4-41/a
			{
				setHNRSWhenNotEqual(pfcb,index_iTimes2,index_jTimes2,data_bij,data_gij,index_i);	
			}
		}
	}

/*	Done		
	100017.*/
//FOR TEST
#if 1
PF_CALC_DATA_TYPE	data1[8][8];
printf("\nHNJLRS  %d\n\n",pfcb->curIterTime);
for (i=0;i<8;i++)
{
	for (j=0;j<8;j++)
	{
		data1[i][j]=pfcb->HNJLRS[i][j];
		printf("%4.4f  ",data1[i][j]);
	}
	printf("\n");
}
#endif
//FOR TEST

#if 0
	printf("e+j*f\n");
	for(int i=0;i<pqvNbr;i++)
	{
		printf("%8.4f+j%8.4f ",pfcb->ei[i+pfcb->blNodeNbr],pfcb->fi[i+pfcb->blNodeNbr]);
	}
	printf("\n");
	printf("deltaP+j* deltaQ\n");
	for(int i=0;i<pqvNbr;i++)
	{
			printf("%8.4f+j%8.4f ",pfcb->deltaPi[i+pfcb->blNodeNbr],pfcb->deltaQi[i+pfcb->blNodeNbr]);
	}
	printf("\n");

#endif

return 0;
}

static int UpdateEifiFromDeltaEifi(PF_CALC_CB* pfcb)
{
#if 1
	int pqvNbr=(pfcb->pqNodeNbr+pfcb->pvNodeNbr);
	int Nbr=(pfcb->pqNodeNbr+pfcb->pvNodeNbr+pfcb->blNodeNbr);
	int pqNbr=pfcb->pqNodeNbr;
	int pvNbr=pfcb->pvNodeNbr;

	pf_uint32	index_i,index_i_with_offset;
	for(unsigned int i=0;i<pqNbr;i++)
	{
		index_i=pfcb->pqNodeTable[i].id.index;
		index_i_with_offset=pfcb->pqNodeTable[i].id.index-pfcb->pqNodeTable[i].id.offset;

		*(pfcb->e[index_i])-=pfcb->deltaEF[index_i_with_offset*2];
		*(pfcb->f[index_i])-=pfcb->deltaEF[index_i_with_offset*2+1];
	}
	for(unsigned int i=0;i<pvNbr;i++)
	{
		index_i=pfcb->pvNodeTable[i].id.index;
		index_i_with_offset=pfcb->pvNodeTable[i].id.index-pfcb->pvNodeTable[i].id.offset;

		*(pfcb->e[index_i])+=pfcb->deltaEF[index_i_with_offset*2];
		*(pfcb->f[index_i])+=pfcb->deltaEF[index_i_with_offset*2+1];
	}
#endif
	return 0;
}
static int isConverge(PF_CALC_CB* pfcb)
{
#if 1
	int nbr=(pfcb->pqNodeNbr+pfcb->pvNodeNbr)*2;
	for(int i=0;i<nbr;i++)
		if(abs(pfcb->deltaPQPU2[i])>pfcb->precision)
					return 0;

#endif
	return 1;

}

static	void	setHNJLWhenEqual(
								   PF_CALC_CB	*pfcb,
								   pf_uint32	index_iTimes2,
								   pf_uint32	index_jTimes2,
								   PF_CALC_DATA_TYPE	bij,
								   PF_CALC_DATA_TYPE	gij,
								   pf_uint32	index_i

								   )
{
	pfcb->HNJLRS[index_iTimes2][index_jTimes2+1]=-(-bij*(pfcb->e[index_i][0])+gij*(pfcb->f[index_i][0])+pfcb->bii[index_i]);
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2+1]=gij*(pfcb->e[index_i][0])+bij*(pfcb->f[index_i][0])+pfcb->aii[index_i];
	pfcb->HNJLRS[index_iTimes2][index_jTimes2]=-gij*(pfcb->e[index_i][0])-bij*(pfcb->f[index_i][0])+pfcb->aii[index_i];
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2]=-(-bij*(pfcb->e[index_i][0])+gij*(pfcb->f[index_i][0])-pfcb->bii[index_i]);
}
static	void	setHNJLWhenNotEqual(
														PF_CALC_CB	*pfcb,
														pf_uint32	index_iTimes2,
														pf_uint32	index_jTimes2,
														PF_CALC_DATA_TYPE	bij,
														PF_CALC_DATA_TYPE	gij,
														pf_uint32	index_i

)
{				
	pfcb->HNJLRS[index_iTimes2][index_jTimes2+1]=-(-bij*(pfcb->e[index_i][0])+gij*(pfcb->f[index_i][0]));
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2+1]=gij*(pfcb->e[index_i][0])+bij*(pfcb->f[index_i][0]);
	pfcb->HNJLRS[index_iTimes2][index_jTimes2]=-gij*(pfcb->e[index_i][0])-bij*(pfcb->f[index_i][0]);
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2]=-(-bij*(pfcb->e[index_i][0])+gij*(pfcb->f[index_i][0]));		
}


static	void	setHNRSWhenEqual(
								 PF_CALC_CB	*pfcb,
								 pf_uint32	index_iTimes2,
								 pf_uint32	index_jTimes2,
								 PF_CALC_DATA_TYPE	bij,
								 PF_CALC_DATA_TYPE	gij,
								 pf_uint32	index_i

								 )
{
	pfcb->HNJLRS[index_iTimes2][index_jTimes2+1]=-(-bij*(pfcb->e[index_i][0])+gij*(pfcb->f[index_i][0])+pfcb->bii[index_i]);
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2+1]= gij*(pfcb->e[index_i][0])+ bij*(pfcb->f[index_i][0])+pfcb->aii[index_i];
	pfcb->HNJLRS[index_iTimes2][index_jTimes2]=2*(pfcb->f[index_i][0]);
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2]=-(2*(pfcb->e[index_i][0]));

}
static	void	setHNRSWhenNotEqual(
									PF_CALC_CB	*pfcb,
									pf_uint32	index_iTimes2,
									pf_uint32	index_jTimes2,
									PF_CALC_DATA_TYPE	bij,
									PF_CALC_DATA_TYPE	gij,
									pf_uint32	index_i

									)
{								
	pfcb->HNJLRS[index_iTimes2][index_jTimes2+1]=-(-bij*(pfcb->e[index_i][0])+ gij*(pfcb->f[index_i][0]));
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2+1]= gij*(pfcb->e[index_i][0])+ bij*(pfcb->f[index_i][0]);
	pfcb->HNJLRS[index_iTimes2][index_jTimes2]=0;
	pfcb->HNJLRS[index_iTimes2+1][index_jTimes2]=-0;		
}


	
static void setAiiBiiUseEquation441(
									PF_CALC_CB*	pfcb,
									pf_uint32			index_i,
									pf_uint32			nbrj
									)
{

		PF_CALC_DATA_TYPE	data_gij,data_bij;
		pfcb->aii[index_i]=0;
		pfcb->bii[index_i]=0;
		for (pf_uint32	j=0;j<nbrj;j++)
		{
			if (index_i!=j)
			{
				GetElem(pfcb->Gij,index_i,j,&data_gij);
				GetElem(pfcb->Bij,index_i,j,&data_bij);
				pfcb->aii[index_i]+=data_gij*pfcb->e[j][0]-data_bij*pfcb->f[j][0];
				pfcb->bii[index_i]+=data_gij*pfcb->f[j][0]+data_bij*pfcb->e[j][0];
			}
		}
		GetElem(pfcb->Gij,index_i,index_i,&data_gij);
		GetElem(pfcb->Bij,index_i,index_i,&data_bij);
		pfcb->aii[index_i]+=data_gij*pfcb->e[index_i][0]-data_bij*pfcb->f[index_i][0];
		pfcb->bii[index_i]+=data_gij*pfcb->f[index_i][0]+data_bij*pfcb->e[index_i][0];
	
}

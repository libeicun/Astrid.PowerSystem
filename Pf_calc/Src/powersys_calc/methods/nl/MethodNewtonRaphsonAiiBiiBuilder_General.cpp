#include "MethodNewtonRaphsonAiiBiiBuilder_General.h"


CMethodNewtonRaphsonAiiBiiBuilder_General::CMethodNewtonRaphsonAiiBiiBuilder_General()
{
}


CMethodNewtonRaphsonAiiBiiBuilder_General::~CMethodNewtonRaphsonAiiBiiBuilder_General()
{
}
pf_bool CMethodNewtonRaphsonAiiBiiBuilder_General::BuilderInit(
	
	pf_uint32 pqNbr, pf_uint32 pvNbr, pf_uint32 blNbr,
	CPfCalcNodePq*	pqNodeTable, CPfCalcNodePv* pvNodeTable, CPfCalcNodeBl* blNodeTable,
	PF_CALC_DATA_TYPE*	aii, PF_CALC_DATA_TYPE*	bii,
	CSMatrix<PF_CALC_DATA_TYPE>*	Bij, CSMatrix<PF_CALC_DATA_TYPE>*	Gij,
	PF_CALC_DATA_TYPE**	e, PF_CALC_DATA_TYPE** f
	){


	this->aii=aii;
	this->bii=bii;
	this->e=e;
	this->f=f;
	this->Gij=Gij;
	this->Bij=Bij;
	this->pqNbr=pqNbr;
	this->pvNbr=pvNbr;
	this->blNbr=blNbr;
	this->pqNodeTable=pqNodeTable;
	this->pvNodeTable=pvNodeTable;
	this->blNodeTable=blNodeTable;

	return pf_bool();
}
pf_bool	CMethodNewtonRaphsonAiiBiiBuilder_General::Build() {
	pf_uint32	Nbr = pqNbr + pvNbr + blNbr;
	pf_uint32	index = 0;
	for (pf_uint32 i = 0; i < blNbr; i++)
	{
		index = blNodeTable[i].index;
		setAiiBiiUseEquation441(index, Nbr);
	}

	for (pf_uint32 i = 0; i < pqNbr; i++)
	{
		index = pqNodeTable[i].index;
		setAiiBiiUseEquation441(index, Nbr);
	}
	for (pf_uint32 i = 0; i < pvNbr; i++)
	{
		index = pvNodeTable[i].index;
		setAiiBiiUseEquation441(index, Nbr);
	}
	return pf_bool();
}
void CMethodNewtonRaphsonAiiBiiBuilder_General::setAiiBiiUseEquation441(
	pf_uint32			index_i,
	pf_uint32			nbrj
	)
{

	PF_CALC_DATA_TYPE	data_gij, data_bij;
	aii[index_i] = 0;
	bii[index_i] = 0;
	for (pf_uint32 j = 0; j < nbrj; j++)
	{
		if (index_i != j)
		{
			Gij->Get_r_Lwr(index_i, j, data_gij);
			Bij->Get_r_Lwr(index_i, j, data_bij);
			//if (!(isZero(data_gij) && isZero(data_bij)))
			{
				aii[index_i] += data_gij* e[j][0] - data_bij* f[j][0];
				bii[index_i] += data_gij* f[j][0] + data_bij* e[j][0];
			}

		}
	}
	Gij->Get_r(index_i, index_i, data_gij);
	Bij->Get_r(index_i, index_i, data_bij);
	//if (!(isZero(data_gij) && isZero(data_bij)))
	{
		aii[index_i] += data_gij* e[index_i][0] - data_bij* f[index_i][0];
		bii[index_i] += data_gij* f[index_i][0] + data_bij* e[index_i][0];
	}


}
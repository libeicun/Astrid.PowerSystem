#pragma once
#include "MethodNewtonRaphsonAiiBiiBuilder.h"
#include "PfCalcNode.h"
#include "Matrix.h"
class CMethodNewtonRaphsonAiiBiiBuilder_General :
	public CMethodNewtonRaphsonAiiBiiBuilder
{
private:
	PF_CALC_DATA_TYPE*	aii;
	PF_CALC_DATA_TYPE*	bii;
	PF_CALC_DATA_TYPE**	e;
	PF_CALC_DATA_TYPE**	f;
	CMatrix<PF_CALC_DATA_TYPE>*									Gij;
	CMatrix<PF_CALC_DATA_TYPE>*									Bij;
	pf_uint32					pqNbr;
	pf_uint32					pvNbr;
	pf_uint32					blNbr;
	CPfCalcNodePq*		pqNodeTable;
	CPfCalcNodePv*		pvNodeTable;
	CPfCalcNodeBl*		blNodeTable;


	void setAiiBiiUseEquation441(pf_uint32			index_i,pf_uint32			nbrj);

public:
	pf_bool BuilderInit(
										pf_uint32 pqNbr,pf_uint32 pvNbr,pf_uint32 blNbr,
										CPfCalcNodePq*	tablePq,CPfCalcNodePv* tablePv,CPfCalcNodeBl* tableBl,
										PF_CALC_DATA_TYPE*	aii,PF_CALC_DATA_TYPE*	bii,
										CSMatrix<PF_CALC_DATA_TYPE>*	Bij, CSMatrix<PF_CALC_DATA_TYPE>*	Gij,
										PF_CALC_DATA_TYPE**	e, PF_CALC_DATA_TYPE** f
										) ;
	pf_bool	Build();
	CMethodNewtonRaphsonAiiBiiBuilder_General();
	~CMethodNewtonRaphsonAiiBiiBuilder_General();
};


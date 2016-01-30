#pragma once
#include "MethodNewtonRaphsonAiiBiiBuilder.h"
class CMethodNewtonRaphsonAiiBiiBuilder_IterCSR :
	public CMethodNewtonRaphsonAiiBiiBuilder
{
private:
	PF_CALC_DATA_TYPE*	aii;
	PF_CALC_DATA_TYPE*	bii;
	PF_CALC_DATA_TYPE**	e;
	PF_CALC_DATA_TYPE**	f;
	CSMatrix<PF_CALC_DATA_TYPE>*									Gij;
	CSMatrix<PF_CALC_DATA_TYPE>*									Bij;
	pf_uint32					pqNbr;
	pf_uint32					pvNbr;
	pf_uint32					blNbr;
	CPfCalcNodePq*		pqNodeTable;
	CPfCalcNodePv*		pvNodeTable;
	CPfCalcNodeBl*		blNodeTable;


	void setAiiBiiUseEquation441(pf_uint32			index_i, pf_uint32			nbrj);

public:
	pf_bool BuilderInit(
		pf_uint32 pqNbr, pf_uint32 pvNbr, pf_uint32 blNbr,
		CPfCalcNodePq*	tablePq, CPfCalcNodePv* tablePv, CPfCalcNodeBl* tableBl,
		PF_CALC_DATA_TYPE*	aii, PF_CALC_DATA_TYPE*	bii,
		CSMatrix<PF_CALC_DATA_TYPE>*	Bij, CSMatrix<PF_CALC_DATA_TYPE>*	Gij,
		PF_CALC_DATA_TYPE**	e, PF_CALC_DATA_TYPE** f
		);
	pf_bool	Build();
public:
	CMethodNewtonRaphsonAiiBiiBuilder_IterCSR();
	~CMethodNewtonRaphsonAiiBiiBuilder_IterCSR();
};


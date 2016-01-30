#pragma once
#include "pf_calc_def_data_type.h"
#include "pf_calc_sys_cfg.h"
#include "PfCalcNode.h"
#include "SMatrix.h"
class CMethodNewtonRaphsonAiiBiiBuilder
{
public:
	virtual pf_bool BuilderInit(pf_uint32 pqNbr, pf_uint32 pvNbr, pf_uint32 blNbr,
		CPfCalcNodePq*	tablePq, CPfCalcNodePv* tablePv, CPfCalcNodeBl* tableBl,
		PF_CALC_DATA_TYPE*	aii, PF_CALC_DATA_TYPE*	bii,
		CSMatrix<PF_CALC_DATA_TYPE>*	Bij, CSMatrix<PF_CALC_DATA_TYPE>*	Gij,
		PF_CALC_DATA_TYPE**	e, PF_CALC_DATA_TYPE**	f
		)=0;

	virtual	pf_bool	Build()=0;
	CMethodNewtonRaphsonAiiBiiBuilder();
	~CMethodNewtonRaphsonAiiBiiBuilder();
};


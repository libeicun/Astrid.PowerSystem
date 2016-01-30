#pragma once
#include "pf_calc_def_data_type.h"
#include "PfCalcNode.h"
#include "SMatrix.h"

class CMethodNewtonRaphsonDeltaPQU2Builder
{
public:
	CMethodNewtonRaphsonDeltaPQU2Builder();
	virtual ~CMethodNewtonRaphsonDeltaPQU2Builder();

	virtual pf_bool		BuilderInit(
		PF_CALC_DATA_TYPE**	e,
		PF_CALC_DATA_TYPE**	f,
		pf_uint32					pqNbr,
		pf_uint32					pvNbr,
		pf_uint32					blNbr,

	CPfCalcNodePq*		pqNodeTable,
	CPfCalcNodePv*		pvNodeTable,

	CSMatrix<PF_CALC_DATA_TYPE>	*Gij,
	CSMatrix<PF_CALC_DATA_TYPE>	*Bij,

	PF_CALC_DATA_TYPE*			deltaPQPU2,
	ePfNodeClass*							nodeClass


	) = 0;
	virtual pf_bool		Build()=0;
};


#pragma once
#include "PfCalcNode.h"
#include"pf_calc_def_data_type.h"
#include "Matrix.h"
#include "SMatrix.h"
#include "SMatrixSP1_3.h"
class CMethodNewtonRaphsonHnjlsrBuilder
{
public:
	CMethodNewtonRaphsonHnjlsrBuilder();
	~CMethodNewtonRaphsonHnjlsrBuilder();

	virtual pf_bool BuilderInit(pf_uint32 pqNbr, pf_uint32 pvNbr,
		CPfCalcNodePq*	tablePq, CPfCalcNodePv* tablePv,
		pf_uint32	blNo,
		PF_CALC_DATA_TYPE*	aii, PF_CALC_DATA_TYPE*	bii,
		CSMatrix<PF_CALC_DATA_TYPE>*	Bij, CSMatrix<PF_CALC_DATA_TYPE>*	Gij,
		PF_CALC_DATA_TYPE**	e, PF_CALC_DATA_TYPE**	f,
		CSMatrixSP1_3<PF_CALC_DATA_TYPE>*			HNJLRS,
		PF_CALC_DATA_TYPE	precision
		) = 0;

	virtual	pf_bool	Build() = 0;

};


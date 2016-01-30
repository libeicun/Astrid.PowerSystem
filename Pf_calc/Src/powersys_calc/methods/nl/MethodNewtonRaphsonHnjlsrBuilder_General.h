#pragma once
#include "MethodNewtonRaphsonHnjlsrBuilder.h"
#include "NumericGeneral.h"
#include "SMatrix.h"
class CMethodNewtonRaphsonHnjlsrBuilder_General :
	public CMethodNewtonRaphsonHnjlsrBuilder
{
	pf_uint32 pqNbr;
	pf_uint32 pvNbr;
	CPfCalcNodePq*	pqNodeTable;
	CPfCalcNodePv* pvNodeTable;
	PF_CALC_DATA_TYPE*	aii;
	PF_CALC_DATA_TYPE*	bii;
	CSMatrix<PF_CALC_DATA_TYPE>*	Bij;
	CSMatrix<PF_CALC_DATA_TYPE>*	Gij;
	PF_CALC_DATA_TYPE**	e;
	PF_CALC_DATA_TYPE**	f;
	CSMatrix<PF_CALC_DATA_TYPE>*			HNJLRS;

public:
	CMethodNewtonRaphsonHnjlsrBuilder_General();
	~CMethodNewtonRaphsonHnjlsrBuilder_General();
	pf_bool BuilderInit(pf_uint32 pqNbr, pf_uint32 pvNbr,
		CPfCalcNodePq*	tablePq, CPfCalcNodePv* tablePv,
		pf_uint32	blNo,
		PF_CALC_DATA_TYPE*	aii, PF_CALC_DATA_TYPE*	bii,
		CSMatrix<PF_CALC_DATA_TYPE>*	Bij, CSMatrix<PF_CALC_DATA_TYPE>*	Gij,
		PF_CALC_DATA_TYPE**	e, PF_CALC_DATA_TYPE**	f,
		CSMatrixSP1_3<PF_CALC_DATA_TYPE>*			HNJLRS,
		PF_CALC_DATA_TYPE	precision
		) ;

		pf_bool	Build() ;

private:
	CNumericGeneral	*pZeroDetector;
	void	setHNJLWhenEqual(
		pf_uint32	index_iTimes2,
		pf_uint32	index_jTimes2,
		PF_CALC_DATA_TYPE	bij,
		PF_CALC_DATA_TYPE	gij,
		pf_uint32	index_i
		);
	void	setHNJLWhenNotEqual(
		pf_uint32	index_iTimes2,
		pf_uint32	index_jTimes2,
		PF_CALC_DATA_TYPE	bij,
		PF_CALC_DATA_TYPE	gij,
		pf_uint32	index_i
		);
	void	setHNRSWhenEqual(
		pf_uint32	index_iTimes2,
		pf_uint32	index_jTimes2,
		PF_CALC_DATA_TYPE	bij,
		PF_CALC_DATA_TYPE	gij,
		pf_uint32	index_i
		);
	void	setHNRSWhenNotEqual(
		pf_uint32	index_iTimes2,
		pf_uint32	index_jTimes2,
		PF_CALC_DATA_TYPE	bij,
		PF_CALC_DATA_TYPE	gij,
		pf_uint32	index_i
		);
};


#pragma once
#include "MethodSolvePowerSysNlEquations.h"
#include "pf_calc_def_data_type.h"
#include "PfcalcNode.h"
#include "MatrixCalculator.h"
#include "pf_calc_def_data_type.h"
#include "pf_calc_sys_cfg.h"
#include "DataFileReader.h"
#include "DMatrix.h"
#include "SMatrixSP1_3.h"
#include "SMatrixCSC.h"
#include <math.h>
#include "PowerFlowCalcObjSelector.h"
#include "MethodNewtonRaphsonAiiBiiBuilder.h"
#include "MethodNewtonRaphsonDeltaPQU2Builder.h"
#include "MethodNewtonRaphsonHnjlsrBuilder.h"
#include "NumericGeneral.h"

class CMethodNewtonRaphson :
	public CMethodSolvePowerSysNlEquations
{

public:
	virtual ePfCalcMethodErr Iterate();
	CMethodNewtonRaphson();
	virtual ~CMethodNewtonRaphson();


	public:
	CPowerFlowCalcObjSelector								*ObjFactory;
	CDataFileReader													*DataReader;
	CMethodNewtonRaphsonHnjlsrBuilder				*pHnjlsrBuilder;
	CMethodNewtonRaphsonAiiBiiBuilder				*pAiiBiiBuilder;
	CMethodNewtonRaphsonDeltaPQU2Builder	*pDeltaPQU2Builder;
	CNumericGeneral													*pZeroDetecter;


	pf_uint32														dataCheckFlag;
	pf_uint32						maxIterTimes;
	pf_uint32						curIterTime;
	pf_f64								precision;


	pf_uint32			blNodeNbr;
	pf_uint32			pqNodeNbr;
	pf_uint32			pvNodeNbr;

	CPfCalcNodePq*										pqNodeTable	/*		Array[pqNbr]		*/;
	CPfCalcNodePv*										pvNodeTable	/*		Array[pvNbr]		*/;
	CPfCalcNodeBl*										blNodeTable		/*		Array[blNbr]		*/;
	/*Only Store their Lower Triangle!!!*/
	CSMatrix<PF_CALC_DATA_TYPE>	*Gij;
	CSMatrix<PF_CALC_DATA_TYPE>	*Bij;

	PF_CALC_DATA_TYPE*			deltaPQPU2/*Array[pqNbr+pvNbr]*/;
	ePfNodeClass*							nodeClass;
	PF_CALC_DATA_TYPE*			deltaEF/*Array[pqNbr+pvNbr]*/;
	CSMatrixSP1_3<PF_CALC_DATA_TYPE>*			HNJLRS/*2DArray[pqNbr+pvNbr][pqNbr+pvNbr]*/;
	PF_CALC_DATA_TYPE*			aii;/*Array[Nbr]*/;
	PF_CALC_DATA_TYPE*			bii;/*Array[Nbr]*/;
	PF_CALC_DATA_TYPE**			e;/*pArray[Nbr]*/
	PF_CALC_DATA_TYPE**			f;/*pArray[Nbr]*/



	pf_bool isConverge();



	pf_int32 UpdateEifiFromDeltaEifi();
	pf_int32 NewtonRaphsonIterOnetime();
};


#pragma once
#include "pf_calc_sys_cfg.h"
#include "SMatrix.h"
#include "DMatrix.h"
enum ePfMatrixCalcErr
{
	ePfMatrixCalcErrOK
};
enum	ePfSolveAeBxMethod
{
	ePfSolveAeBxMethodLU
};
class CMatrixCalculator
{
public:
	ePfMatrixCalcErr		SetMethod(ePfSolveAeBxMethod method);
	ePfMatrixCalcErr		SolveAEqualBx(PF_CALC_DATA_TYPE* vectorA, PF_CALC_DATA_TYPE** matB, PF_CALC_DATA_TYPE* x, int rank);
	ePfMatrixCalcErr		SolveAEqualBx(PF_CALC_DATA_TYPE* vectorA, CMatrix<PF_CALC_DATA_TYPE>& matB, PF_CALC_DATA_TYPE* x, int rank);
	CMatrixCalculator();
	virtual ~CMatrixCalculator();

private:
	ePfSolveAeBxMethod	method;
};


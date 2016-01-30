#pragma once
#include "pf_calc_def_data_type.h"
#include "MethodSolvePowerSysNlEquations.h"
class CPowerSysCalculation
{
public:
	CPowerSysCalculation();
	~CPowerSysCalculation();
private:
	CMethodSolvePowerSysNlEquations* pMethodSloveNlEquations;
public:
	
	

	virtual pf_bool Calc() = 0;
};

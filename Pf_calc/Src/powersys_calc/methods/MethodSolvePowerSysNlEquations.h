#pragma once
#include "pf_calc_def_data_type.h"

enum ePfCalcMethodErr
{
	ePfCalcMethodOK,
	ePfCalcMethodFailToConverge
};

class CMethodSolvePowerSysNlEquations
{

public:
	CMethodSolvePowerSysNlEquations();
	virtual ~CMethodSolvePowerSysNlEquations();

	virtual							ePfCalcMethodErr		Iterate() = 0;
};


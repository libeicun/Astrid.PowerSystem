
#pragma once
#include "pf_calc_def_data_type.h"
#include "PowerSysCalculation.h"


	class CPowerSysCalcFlow:
		public CPowerSysCalculation
	{
	private:
		CMethodSolvePowerSysNlEquations		*pMethodSloveNlEquations;

	public:
		CPowerSysCalcFlow();
		~CPowerSysCalcFlow();

	   pf_bool Calc() ;
	};

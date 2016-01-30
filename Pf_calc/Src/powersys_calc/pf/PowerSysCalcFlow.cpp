#include "PowerSysCalcFlow.h"
#include "MethodNewtonRaphson.h"

CPowerSysCalcFlow::CPowerSysCalcFlow()
{
}


CPowerSysCalcFlow::~CPowerSysCalcFlow()
{
}

pf_bool CPowerSysCalcFlow::Calc(){
	pMethodSloveNlEquations = new CMethodNewtonRaphson();
	pMethodSloveNlEquations->Iterate();
	delete	pMethodSloveNlEquations;
	return  pf_bool();
}

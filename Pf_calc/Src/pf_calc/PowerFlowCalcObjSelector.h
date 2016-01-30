#pragma once
#include "DataFileReader.h"
class CPowerFlowCalcObjSelector
{
public:
	virtual CDataFileReader* SelectDFR() =0;

	CPowerFlowCalcObjSelector();
	virtual ~CPowerFlowCalcObjSelector();
};


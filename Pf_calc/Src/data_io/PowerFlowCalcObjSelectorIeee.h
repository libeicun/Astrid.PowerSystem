#pragma once
#include "PowerFlowCalcObjSelector.h"
#include "DataFileReaderForIeee.h"
class CPowerFlowCalcObjSelectorIeee :
	public CPowerFlowCalcObjSelector
{
public:
	CDataFileReader* SelectDFR() ;
	CPowerFlowCalcObjSelectorIeee();
	~CPowerFlowCalcObjSelectorIeee();
};


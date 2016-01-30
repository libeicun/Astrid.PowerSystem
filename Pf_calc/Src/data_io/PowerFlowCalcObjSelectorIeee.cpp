#include "PowerFlowCalcObjSelectorIeee.h"


CPowerFlowCalcObjSelectorIeee::CPowerFlowCalcObjSelectorIeee()
{
}


CPowerFlowCalcObjSelectorIeee::~CPowerFlowCalcObjSelectorIeee()
{
}
CDataFileReader* CPowerFlowCalcObjSelectorIeee::SelectDFR(){
	return new CDataFileReaderForIeee();
}
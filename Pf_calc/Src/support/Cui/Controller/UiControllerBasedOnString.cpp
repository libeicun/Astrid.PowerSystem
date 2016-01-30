#include "UiControllerBasedOnString.h"
#include "UserInputPaserCSyntax.h"

CUiControllerBasedOnString::CUiControllerBasedOnString()
{
	pUser = new CUserInputPaserCSyntax;
}


CUiControllerBasedOnString::~CUiControllerBasedOnString()
{
	delete pUser;
}

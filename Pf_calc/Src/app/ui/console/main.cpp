#include <stdlib.h>
#include <stdio.h>
#include "UserCmdAndStatus.h"

#include "UserProcesses.h"
#include "UiControllerBasedOnString.h"
#include "UiControllerConsole.h"
#include "SMatrixCSC.h"
#include "SMatrixSP1_3.h"
#include "Timing.h"

int main()
{
	CUiControllerBasedOnString*		pUiController = new CUiControllerConsole();

	pUiController->SetDefaultProc(fDefaultProc);

	pUiController->RegisterUserProc(eStatusWaitForCmd, eStatusWaitForCmd, fPfCalcOnce, "powerflowlodafolwcalc");
	pUiController->RegisterUserProc(eStatusWaitForCmd, eStatusWaitForCmd, fSyscall, "systemcall");

	CTiming::On();
	while(1)
	{
		//system("cls");
		//cui.FsmInteractOnce();

		pUiController->Execute();
	}
	return 0;

	
}
 
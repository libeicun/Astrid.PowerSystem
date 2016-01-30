#ifndef PF_CALC_UI_CONSOLE_DEF_H
#define PF_CALC_UI_CONSOLE_DEF_H
#include "pf_calc_data_io.h"
enum ePfCuiState{
	ePfCuiStateWaitForCmd,
	ePfCuiStateBootUp
};
enum ePfCuiCmdCode{
	ePfCuiCmdCodePowerFlowCalc,
	ePfCuiCmdCodeBuildDataFile,
	ePfCuiCmdCodeUndefined
};
enum ePfCuiFileClass
{
	ePfCuiFileClassInput,
	ePfCuiFileClassOutput
};

class CPfCalcCuiSettings{
public:
	int bHistory;
	int bFuzzyCmd;
}
;

class CPfCalcCuiCmdInfo{
public:
	ePfCuiCmdCode	code;
}
;

class CPfCalcDfInfo{
public:
	char							path[40];
	ePfCuiFileClass				fileClass;
	ePfDataStructType			dataStructType;
}
;

class CPfCalcCuiCtrlBlock{
public:
	CPfCalcCuiSettings				settings;
	CPfCalcCuiCmdInfo				cmdExecJustNow;
	CPfCalcCuiCmdInfo				cmdToExec;
	/*Cmd History*/
	ePfCuiState						state;
	char								userInputString[20];

	ePfCuiState	CuiFsmInteractOneTime();
}
;




#endif PF_CALC_UI_CONSOLE_DEF_H

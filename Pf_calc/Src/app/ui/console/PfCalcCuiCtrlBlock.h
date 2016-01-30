#pragma once
#include "DataIOTool.h"

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

class CPfCalcCuiCtrlBlock
{
public:
	CPfCalcCuiCtrlBlock();
	virtual ~CPfCalcCuiCtrlBlock();

private:

	char								userInputString[20];

public:
	ePfCuiState			CuiFsmInteractOneTime();
	CPfCalcCuiCmdInfo	CuiGetUserCmd();
	char*					CuiGetUserInputString();

	CPfCalcCuiSettings				settings;
	CPfCalcCuiCmdInfo				cmdExecJustNow;
	CPfCalcCuiCmdInfo				cmdToExec;
	/*Cmd History*/
	ePfCuiState						state;

};


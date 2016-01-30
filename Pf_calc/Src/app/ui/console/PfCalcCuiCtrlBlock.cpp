#include "PfCalcCuiCtrlBlock.h"

#include <stdio.h>
#include "stringExtends.h"
CPfCalcCuiCtrlBlock::CPfCalcCuiCtrlBlock()
{
}


CPfCalcCuiCtrlBlock::~CPfCalcCuiCtrlBlock()
{
}

ePfCuiState	CPfCalcCuiCtrlBlock::CuiFsmInteractOneTime()
{
	char				 filename[30];
	switch (cmdToExec.code)
	{
	case ePfCuiCmdCodePowerFlowCalc:{

		

		printf("Please Enter the Path of Data File\n");
		scanf("%s", &filename);
		//PfDataReadFile(pccb,filename,ePfDataStructTypeLBCTest);


		CPfCalcDataFileIeee					df(filename);
		CDataFileReaderForIeee 
		CPfCalcMethodNewtonRaphson		nl_iter(df);
		CDataIOTool								dio(nl_iter);

		//if(!PfDataCheck(pccb,ePfDataStructTypeLBCTest))
		//	printf("Data Input Is Invalid.\nPlease Check them for OK.\n");

		dio.SetMethodObjPtr(&nl_iter);
		dio.DataWriteFile(&nl_iter,"test_data_output.txt");
		nl_iter.Iterate();
		//SolveAEqualBxTest();
		//PfCalcCbFree(pccb);		

		state = ePfCuiStateWaitForCmd;
		break; }
	default:{break; }
	}
	return state;

}



CPfCalcCuiCmdInfo	CPfCalcCuiCtrlBlock::CuiGetUserCmd()
{
	CPfCalcCuiCmdInfo	cmd;
	switch (state)
	{
	case ePfCuiStateWaitForCmd:{
		if (strsubstr(PF_CALC_UI_CONSOLE_CMD_STRING_CALC_POWER_FLOW, userInputString))
		{
			cmd.code = ePfCuiCmdCodePowerFlowCalc;
		}
		else
		{
			cmd.code = ePfCuiCmdCodeUndefined;
		}
		break; }
	default:{
		cmd.code = ePfCuiCmdCodeUndefined;
		break; }
	}
	cmdToExec = cmd;
	return cmd;

}
char*	CPfCalcCuiCtrlBlock::CuiGetUserInputString()
{
	printf(">>");
	scanf("%s", &userInputString);
	return userInputString;
}
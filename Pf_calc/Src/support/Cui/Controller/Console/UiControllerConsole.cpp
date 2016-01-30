#include "UiControllerConsole.h"
CUiControllerConsole::CUiControllerConsole()
{
	Status = 0;
	bStatusAlreadySetup = 0;
	fpDefaultProc = default_proc_when_input_invalid;
}
CUiControllerConsole::~CUiControllerConsole()
{
}
pf_bool			CUiControllerConsole::SetDefaultProc(tUI_FPTypeNonePara fp){
	fpDefaultProc = fp;
	return pf_bool(0);
}
pf_bool			CUiControllerConsole::Execute(){

	CConsoleUiTransform	Trans;

	pUser->GetAndParse();
	pf_uint32	Size = pUser->UserInputIteratorReset();
	string				CmdString;
	list<string>		ParaStringList;

	for (pf_uint32 i = 0; i <Size; i++, pUser->UserInputIteratorForward()){
		CmdString = pUser->UserInputIteratorGetCmdString();
		ParaStringList = pUser->UserInputIteratorGetParaList();

		pf_bool	find = GetItem(Status, CmdString.c_str(), Trans);
		if (!find)
		{
			(*fpDefaultProc)();
		}
		else
		{
				Trans.Exec(ParaStringList);
				Status = Trans.GetStatusCode();
		}

	}
	return pf_bool(0);
}
pf_bool			CUiControllerConsole::RegisterUserProc(pf_uint32 StatusCodeFrom, pf_uint32 StatusCodeTo, tUI_FPType1Paras pUserProc, string CmdString){

	list<CConsoleUiStatusTableLine>::iterator p;
	if (!bStatusAlreadySetup){
		Status = StatusCodeFrom;
		bStatusAlreadySetup = 1;
	}



	pf_bool	find = LocateLine(StatusCodeFrom, p);
	if (!find)
	{
		CConsoleUiStatusTableLine	newLine;
		newLine.SetStatusCode(StatusCodeFrom);
		newLine.AddNode(pUserProc, 0, CmdString.c_str(), StatusCodeTo);
		StatusTable.push_back(newLine);
	}
	else
	{
		p->AddNode(pUserProc, 0, CmdString.c_str(), StatusCodeTo);
	}
	return pf_bool();
}
pf_uint32		CUiControllerConsole::GetStatus(){
	return pf_uint32(Status);
}
void default_proc_when_input_invalid()
{
	printf("Invalid Input Dectected.\nPlease Check it out.\n");
}
pf_bool	CUiControllerConsole::GetItem(pf_uint32 statusCodeFrom, const char*	strCode, CConsoleUiTransform& item)
{
	pf_bool	ret = 0;

	list<CConsoleUiStatusTableLine>::iterator	pLine;
	list<CConsoleUiTransform>::iterator				pNode;
	pf_bool	findLine = LocateLine(statusCodeFrom, pLine);
	if (!findLine)/*There is no line match the statusCodeFrom.*/
		return 0;
	else/*An matched line found.*/
	{
		pf_bool	findNode = (*pLine).LocateNode( strCode, pNode);
		if (!findNode)/*There is no found node in the line.*/
		{
			return 0;
		}
		else/*Matched node found.*/
		{
			item = *pNode;
			ret = 1;
		}
	}
	return ret;
}
pf_bool	CUiControllerConsole::LocateLine(pf_uint32 statusCodeFrom, list<CConsoleUiStatusTableLine>::iterator& in)
{

	list<CConsoleUiStatusTableLine>::iterator	p;
	pf_bool																	ret = 0;
	CConsoleUiStatusTableLine							StatusTableLineData;

	for (p = StatusTable.begin(); p != StatusTable.end(); p++)
	{
		StatusTableLineData = *(p);
		if (StatusTableLineData.GetStatusCode() == statusCodeFrom)
		{
			ret = 1;
			in = p;
			break;
		}
	}
	return	ret;
}

#pragma once
#include "UiControllerBasedOnString.h"
#include "ConsoleUiStatusTableLine.h"
#include <list>
using namespace std;
void	default_proc_when_input_invalid();

class CUiControllerConsole :
	public CUiControllerBasedOnString
{
private:
	pf_bool															bStatusAlreadySetup;
	pf_uint32														Status;
	list<CConsoleUiStatusTableLine>			StatusTable;
	tUI_FPTypeNonePara									fpDefaultProc;

private:
	pf_bool								LocateLine(pf_uint32 statusCodeFrom, list<CConsoleUiStatusTableLine>::iterator& iter);
	pf_bool								GetItem(pf_uint32 statusCodeFrom, const char*	strCode, CConsoleUiTransform& item);


public:
	virtual pf_bool			SetDefaultProc(tUI_FPTypeNonePara fp);
	virtual pf_bool			Execute() ;
	virtual pf_bool			RegisterUserProc(pf_uint32 StatusCodeFrom, pf_uint32 StatusCodeTo, tUI_FPType1Paras pUserProc, string CmdString) ;
	virtual pf_uint32		GetStatus() ;

public:
	CUiControllerConsole();
	~CUiControllerConsole();




	
	

};

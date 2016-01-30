#include "ConsoleUiStatusTableLine.h"
#include "stringExtends.h"

CConsoleUiStatusTableLine::CConsoleUiStatusTableLine()
{
}



CConsoleUiStatusTableLine::~CConsoleUiStatusTableLine()
{
}
void	CConsoleUiStatusTableLine::AddNode(tUI_FPType1Paras fp, pf_uint32	 userCmdCode, const pf_int8* strCode,  pf_uint32	statusTo)
{
	CConsoleUiTransform	t;
	t.SetFuncPtr(fp);
	t.SetStatusCode(statusTo);
	t.SetUserCmdCode(userCmdCode);
	t.SetUserCmdString(strCode);
	Nodes.push_back(t);
}

pf_bool	CConsoleUiStatusTableLine::LocateNode(const pf_int8* strCode, list<CConsoleUiTransform>::iterator& iter){
	pf_bool	ret = 0;

	list<CConsoleUiTransform>::iterator	t;
	CConsoleUiTransform					tData;
	for (t = Nodes.begin(); t != Nodes.end(); t++)
	{
		tData = *t;
		if (strsubstr(tData.GetUserCmdString(), strCode))
		{
			iter = t;
			ret = 1;
			break;
		}
	}
	return	ret;
}
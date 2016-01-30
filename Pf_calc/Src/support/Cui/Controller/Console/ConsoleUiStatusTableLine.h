#pragma once
#include "ConsoleUiTransform.h"
#include <list>
using namespace std;
class CConsoleUiStatusTableLine
{
private:
	pf_uint32										StatusCodeFrom;
	list<CConsoleUiTransform>		Nodes;



public:
	void					AddNode(tUI_FPType1Paras fp, pf_uint32	 userCmdCode, const pf_int8* strCode, pf_uint32	statusTo );
	pf_bool				LocateNode(const pf_int8* strCode, list<CConsoleUiTransform>::iterator& iter);
	pf_uint32 GetStatusCode(){
		return StatusCodeFrom;
	}
	void	SetStatusCode(pf_uint32 code){
		StatusCodeFrom = code;
	}
	CConsoleUiStatusTableLine();
	virtual ~CConsoleUiStatusTableLine();
};


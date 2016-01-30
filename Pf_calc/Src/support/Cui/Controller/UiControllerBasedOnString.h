#pragma once
#include "pf_calc_def_data_type.h"
#include "def_data_type_fptr.h"
#include "UserInputParser.h"

#include <string>
#include <list>
using namespace std;



class CUiControllerBasedOnString
{
protected:
	CUserInputParser*									pUser;
public:
	CUiControllerBasedOnString();
	virtual ~CUiControllerBasedOnString();
	virtual pf_bool			SetDefaultProc(tUI_FPTypeNonePara fp) = 0;
	virtual pf_bool			Execute() = 0;
	virtual pf_bool			RegisterUserProc(pf_uint32 StatusCodeFrom, pf_uint32 StatusCodeTo, tUI_FPType1Paras pUserProc, string CmdString) = 0;
	virtual pf_uint32		GetStatus() = 0;
};


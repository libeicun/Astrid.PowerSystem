#pragma once
#include "pf_calc_def_data_type.h"
#include <list>
#include <string>
#include "UserInputObtainer.h"

using namespace std;
struct UserInput 
{
	string				CmdString;
	pf_uint32		ParaNbr;
	list<string>		ParaList;
};
class CUserInputParser
{
protected:
	CUserInputObtainer	*pUserInputObtainer;
public:
	CUserInputParser();
	virtual ~CUserInputParser();

	virtual		pf_uint32		UserInputIteratorReset() = 0;
	virtual		pf_bool			UserInputIteratorForward() = 0;
	virtual		pf_bool			UserInputIteratorAtEnd() = 0;

	virtual		UserInput		UserInputIteratorGet() = 0;
	virtual		string				UserInputIteratorGetCmdString() = 0;
	virtual		list<string>		UserInputIteratorGetParaList() = 0;

	virtual		pf_uint32		UserParaListIteratorReset() = 0;
	virtual		pf_bool			UserParaIteratorForward() = 0;
	virtual		pf_bool			UserParaIteratorAtEnd() = 0;

	virtual		string				UserParaIteratorGetPara() = 0;

	virtual		pf_bool			GetAndParse()=0;
	
};


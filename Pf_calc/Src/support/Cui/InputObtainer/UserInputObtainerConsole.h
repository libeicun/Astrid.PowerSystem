#pragma once
#include "UserInputObtainer.h"
#include <list>
class CUserInputObtainerConsole :
	public CUserInputObtainer
{
private:
	string								UserInputString;
	list<string>						UserInputStringList;
	list<string>::iterator		StringIter;
public:

	pf_uint32		StringIteratorReset();
	string				StringIteratorGets();
	pf_bool			StringIteratorForward() ;
	pf_bool			StringIteratorAtEnd() ;
	pf_bool			GetInput() ;

public:
	CUserInputObtainerConsole();
	~CUserInputObtainerConsole();
};


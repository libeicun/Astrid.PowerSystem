// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "UserInputObtainer.h"
#include "UserInputObtainerConsole.h"
#include "UserInputPaserCSyntax.h"
#include "UserInputParser.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	CUserInputObtainer*	User = new CUserInputObtainerConsole;
	string								UserString;
	/*
	while (1)
	{
		User->GetInput();
		pf_uint32 size= User->StringIteratorReset();
		for (pf_uint32 i = 0; i < size;i++,User->StringIteratorForward()){
			UserString = User->StringIteratorGets();
			cout << UserString << endl;
		}
	}*/

	CUserInputParser*	Parser = new CUserInputPaserCSyntax;

	while (1){
		Parser->GetAndParse();
		string	CmdString;
		list<string>		ParaStringList;
		pf_uint32	i = 0, size = Parser->UserInputIteratorReset();
		for (i = 0; i < size; i++, Parser->UserInputIteratorForward()){
			CmdString = Parser->UserInputIteratorGetCmdString();
			ParaStringList = Parser->UserInputIteratorGetParaList();

			cout << endl << "Command Code: " << CmdString << endl;
			cout << "Parameters: ";
			list<string>::iterator	ItPara;
			for (ItPara = ParaStringList.begin(); ItPara != ParaStringList.end(); ItPara++){
				cout << *ItPara << " ";
			}
			cout << endl;
		}
	}




	return 0;
}


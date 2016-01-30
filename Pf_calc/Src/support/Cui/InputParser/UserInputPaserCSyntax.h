#pragma once
#include "UserInputParser.h"
#include "UserInputObtainer.h"
class CUserInputPaserCSyntax :
	public CUserInputParser
{

private:
	list<string>				newLIst;
	pf_bool	AddAnItemOfUserInputStringList(string str);

	string										UserInputString;
	/*
	Like
		|pf		-ieee5.txt			-res.txt|
	We get each UserInputString by requesting CUserInputObtainer.
	*/

	list<string>::iterator				IterUserInputStringList;
	list<string>								UserInputStringList;
	/*
	UserInputStringList is represented as
		|pf|		|-ieee5.txt|			|-res.txt|
	It is actually an item of ListOfUserInputStringList, and we can build it from decomposing an UserInputString.
	*/


	list<list<string>>::iterator	IterListUserInputStringList;
	list<list<string>>					ListOfUserInputStringList;
	/*
	UserInputStringList is represented as
		||pf|		|ieee5.txt|				|res.txt| |
		||pf|		|ieee1047.dat|		|res.txt| |
		||pf|		|ieee118.dat|			|res.txt| |
		It is a collection of UserInputString, and it can built from UserInputStringList,and then cutoff dividers.
	*/

	string									UserCmdString;
	/*
	Like
		|pf|
	It is an Item of a ListOfUserInputStringList.
	*/

	list<string>::iterator			IterUserParaStringList;
	list<string>							UserParaStringList;
	/*
	Like
		|ieee118.dat|		|res.txt|	
	It is equal to (*ListOfUserInputStringList::Iterator-UserCmdString).
	*/
	



public:
	pf_bool			GetAndParse() ;
	pf_uint32		UserInputIteratorReset() ;
	pf_bool			UserInputIteratorForward() ;
	pf_bool			UserInputIteratorAtEnd() ;

	UserInput		UserInputIteratorGet() ;
	string				UserInputIteratorGetCmdString() ;
	list<string>		UserInputIteratorGetParaList() ;

	pf_uint32		UserParaListIteratorReset() ;
	pf_bool			UserParaIteratorForward() ;
	pf_bool			UserParaIteratorAtEnd() ;

	string				UserParaIteratorGetPara();
public:
	CUserInputPaserCSyntax();
	~CUserInputPaserCSyntax();
};


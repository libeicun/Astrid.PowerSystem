#include "UserInputObtainerConsole.h"


CUserInputObtainerConsole::CUserInputObtainerConsole()
{
}


CUserInputObtainerConsole::~CUserInputObtainerConsole()
{
}


pf_uint32		CUserInputObtainerConsole::StringIteratorReset(){

	pf_uint32	size = UserInputStringList.size();
	if (size>0){
		StringIter = UserInputStringList.begin();
	}
	return size;
}
string				CUserInputObtainerConsole::StringIteratorGets(){
	return *StringIter;
}
pf_bool			CUserInputObtainerConsole::StringIteratorForward(){
	StringIter++;
	return pf_bool();

}
pf_bool			CUserInputObtainerConsole::StringIteratorAtEnd(){
	return pf_bool(StringIter==UserInputStringList.end());
}
pf_bool			CUserInputObtainerConsole::GetInput(){

	UserInputStringList.clear();

	printf(">>");
	char	str[100]; 
	pf_uint32	len;
	pf_bool		endLineIsEmpty=0;

	gets_s(str);
	len = strlen(str);
	if (len != 0){
		UserInputStringList.push_back(str);
	}
	while( (str[len - 1] == ';'))	{
		printf("  ");
		gets_s(str);
		len = strlen(str);
		if (len != 0){
			UserInputStringList.push_back(str);
		}
		else{
			endLineIsEmpty = 1;
		}
	}

	pf_uint32 size=UserInputStringList.size();
	if (size>1){
		list<string>::iterator	iter;
		pf_uint32	i = 0;

		pf_uint32	end = endLineIsEmpty ? size : size - 1;
		for (i = 0,iter=UserInputStringList.begin(); i < end;i++,iter++){
			(*iter).pop_back();
		}
	}
	return pf_bool();

}


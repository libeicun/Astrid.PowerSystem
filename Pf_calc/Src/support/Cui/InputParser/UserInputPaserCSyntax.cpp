#include "UserInputPaserCSyntax.h"

CUserInputPaserCSyntax::CUserInputPaserCSyntax(){

}
CUserInputPaserCSyntax::~CUserInputPaserCSyntax(){

}

pf_bool			CUserInputPaserCSyntax::AddAnItemOfUserInputStringList(string str){

	if (str.at(0)=='-'){
		str = str.substr(1, str.length() - 1);
	}
	newLIst.push_back(str);
	return pf_bool();
}
pf_bool			CUserInputPaserCSyntax::GetAndParse(){

	ListOfUserInputStringList.clear();

	pUserInputObtainer->GetInput();
	pf_uint32	size = pUserInputObtainer->StringIteratorReset();

	
	string						userInputString,StringBeforeDiv,StringAfterDiv;
	pf_uint32	i = 0;
	pf_uint32	pos = 0, len=0,subLen = 0;
	for (i = 0; i < size;i++,pUserInputObtainer->StringIteratorForward()){

		newLIst.clear();
		/*Get a line of user input string.*/
		userInputString=pUserInputObtainer->StringIteratorGets();

		StringAfterDiv = userInputString;
		len = StringAfterDiv.length();
		while (len){
			pos = StringAfterDiv.find_first_of(' ');
			if (pos >= len){
				AddAnItemOfUserInputStringList(StringAfterDiv);
				break;
			}else{/*if there is a divider, split the string.*/
				subLen = len - pos;
				StringBeforeDiv = StringAfterDiv.substr(0, pos);
				StringAfterDiv = StringAfterDiv.substr(pos + 1, subLen);

				while (StringAfterDiv.length()>0 && StringAfterDiv.at(0) == ' '){
					StringAfterDiv = StringAfterDiv.substr(1, StringAfterDiv.length() - 1);
					if (StringAfterDiv.length() == 0){
						break;
					}
				}
				if (StringBeforeDiv.length()>0){
					AddAnItemOfUserInputStringList(StringBeforeDiv);
				}
				
			}
			len = StringAfterDiv.length();
		}
		ListOfUserInputStringList.push_back(newLIst);

	}


#if 0
	string	dividerSpace = " ";
	string	dividerSpaceAndSubOp = " -";
	list<list<string>>::iterator				IterUserCmdAndParaStringList;
	list<string>::iterator							IterCmdAndParaString;
	for (IterUserCmdAndParaStringList = UserInputStringList.begin(); IterUserCmdAndParaStringList != UserInputStringList.end(); IterUserCmdAndParaStringList++){
		IterCmdAndParaString = (IterUserCmdAndParaStringList->begin());

		(*IterCmdAndParaString).at(dividerSpaceAndSubOp, (*IterCmdAndParaString).length());
	}

#endif
	return pf_bool();
}

pf_uint32		CUserInputPaserCSyntax::UserInputIteratorReset(){
	pf_uint32	size = ListOfUserInputStringList.size();
	if (size>0){
		IterListUserInputStringList = ListOfUserInputStringList.begin();
	}
	
	return pf_uint32(size);
}

pf_bool			CUserInputPaserCSyntax::UserInputIteratorForward(){
	IterListUserInputStringList++;
return pf_bool();
}
pf_bool			CUserInputPaserCSyntax::UserInputIteratorAtEnd(){
	return pf_bool(IterListUserInputStringList==ListOfUserInputStringList.end());
}

UserInput		CUserInputPaserCSyntax::UserInputIteratorGet(){
	UserInput		User;
	list<string>		List = *IterListUserInputStringList;

	User.CmdString =* (List.begin());
	(List).pop_front();
	User.ParaNbr = (List).size();
	User.ParaList = (List);
	return UserInput(User);
}
string				CUserInputPaserCSyntax::UserInputIteratorGetCmdString(){
	string	CmdString;
	CmdString =*( (*IterListUserInputStringList).begin());

	return string(CmdString);
}
list<string>		CUserInputPaserCSyntax::UserInputIteratorGetParaList(){

	list<string>		ParaList;
	list<string>		List;
	List = *IterListUserInputStringList;

	(List).pop_front();
	ParaList = List;

	return list < string >(ParaList);
}

pf_uint32		CUserInputPaserCSyntax::UserParaListIteratorReset(){
	return pf_uint32();
}
pf_bool			CUserInputPaserCSyntax::UserParaIteratorForward(){
	return pf_bool();
}
pf_bool			CUserInputPaserCSyntax::UserParaIteratorAtEnd(){
	return pf_bool();
}

string				CUserInputPaserCSyntax::UserParaIteratorGetPara(){

	return string();
}
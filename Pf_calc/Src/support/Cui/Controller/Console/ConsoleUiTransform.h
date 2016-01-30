#pragma once
#include "pf_calc_def_data_type.h"
#include "def_data_type_fptr.h"
#include "BindingsOfUserCmdCodeAndString.h"
#include <string.h>

class CConsoleUiTransform
{
public:
	CConsoleUiTransform();
	virtual ~CConsoleUiTransform();
private:
	pf_uint32			StatusCodeTo;
	pf_char*				StatusToString;
	BindingsOfUserCmdCodeAndString
								UserCmd;

	tUI_FPType1Paras 	fp;



public:

	void	Exec(list<string> ParaList){
		if (fp == 0)
			return;
		(*fp)(ParaList);
	}
	void		SetUserCmdString(const pf_int8*	str){
		UserCmd.SetString(str);
	}
	pf_int8*			GetUserCmdString(){
		return UserCmd.GetString();
	}
	void		SetUserCmdCode(pf_uint32 code){
		UserCmd.SetCode( code);
	}
	pf_uint32	GetUserCmdCode(){
		return	UserCmd.GetCode();
	}


	void		SetStatusCode(pf_uint32 code){
		StatusCodeTo = code;
	}
	pf_uint32	GetStatusCode(){ 
		return StatusCodeTo; 
	}
	void		SetFuncPtr(tUI_FPType1Paras fp);
	void		SetStatusString(const pf_char* str){
		delete[] StatusToString;
		StatusToString = new pf_char[strlen(str)+1];
		strcpy(StatusToString, str);
	}
	pf_char*		GetStatusString(){
		return	StatusToString;
	}

};


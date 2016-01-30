#pragma once
#include "pf_calc_def_data_type.h"
#include <list>
#include <string.h>

class BindingsOfUserCmdCodeAndString
{
private:
	char*		String;
	pf_uint32	Code;
public:
	BindingsOfUserCmdCodeAndString();
	BindingsOfUserCmdCodeAndString(pf_uint32	cmdCode, const char*  str);
	BindingsOfUserCmdCodeAndString(const BindingsOfUserCmdCodeAndString& b){
		//delete	String;
		String = new char[strlen(b.String) + 1];
		strcpy(String, b.String);
		Code = b.Code;
	}
	BindingsOfUserCmdCodeAndString& operator=(const BindingsOfUserCmdCodeAndString b)
	{
		delete	String;
		//BindingsOfUserCmdCodeAndString	r;
		String = new char[strlen(b.String) + 1];
		strcpy(String, b.String);
		Code = b.Code;
		return *this;
	}
	~BindingsOfUserCmdCodeAndString();
	void SetCode(pf_uint32 cmdCode){
		Code = cmdCode;
	}
	pf_uint32	GetCode(){
		return  Code;
	}
	void SetString(const pf_int8*	str){
		delete String;
		String = new char[strlen(str) + 1];
		strcpy(String, str);
	}
	pf_int8*	GetString(){
		return	String;
	}
};
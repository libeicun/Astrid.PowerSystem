#include "BindingsOfUserCmdCodeAndString.h"
BindingsOfUserCmdCodeAndString::BindingsOfUserCmdCodeAndString(pf_uint32	cmdCode, const char*  str)
{
	String = new char[strlen(str) + 1];
	strcpy(String, str);
	Code = cmdCode;
}
BindingsOfUserCmdCodeAndString::BindingsOfUserCmdCodeAndString()
{
	String = new char[1];
}

BindingsOfUserCmdCodeAndString::~BindingsOfUserCmdCodeAndString()
{
	delete	String;
}

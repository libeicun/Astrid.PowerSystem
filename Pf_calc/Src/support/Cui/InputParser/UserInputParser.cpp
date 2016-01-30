#include "UserInputParser.h"
#include "UserInputObtainerConsole.h"
#include "UserInputObtainerTextFile.h"

CUserInputParser::CUserInputParser()
{
	pUserInputObtainer = new CUserInputObtainerConsole;
}


CUserInputParser::~CUserInputParser()
{
	delete pUserInputObtainer;
}

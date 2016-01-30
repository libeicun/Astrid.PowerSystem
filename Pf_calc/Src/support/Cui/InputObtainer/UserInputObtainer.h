#pragma once
#include "pf_calc_def_data_type.h"
#include <string>
using namespace std;
class CUserInputObtainer
{
public:
	CUserInputObtainer();
	virtual ~CUserInputObtainer();
	virtual pf_uint32		StringIteratorReset() = 0;
	virtual string			StringIteratorGets() = 0;
	virtual pf_bool			StringIteratorForward() = 0;
	virtual pf_bool			StringIteratorAtEnd() = 0;
	virtual pf_bool			GetInput() = 0;
};


#ifndef DEF_DATA_TYPE_FPTR_H
#define DEF_DATA_TYPE_FPTR_H
#include "pf_calc_def_data_type.h"
#include <string>
#include <list>
using namespace std;

typedef	void(*FPTypeStringListParas_r)(list<string>& );
typedef	void(*FPTypeNonePara)();


typedef	void(*tUI_FPType2Paras)(string, list<string>);
typedef	void(*tUI_FPType1Paras)(list<string>& );
typedef	void(*tUI_FPTypeNonePara)();


#endif 
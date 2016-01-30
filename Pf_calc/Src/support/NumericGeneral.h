#pragma once
#include "pf_calc_def_data_type.h"
#include <math.h>
class CNumericGeneral
{
private:
	pf_f64	thre;
public:
	CNumericGeneral();
	~CNumericGeneral();
	pf_bool	SetThreshold(pf_f64 thre){
		this->thre = thre;
		return pf_bool();
	}
	pf_bool	isNoneZero(pf_f64 data)
	{
		if (fabs(data) >= thre)
		{
			return 1;
		}
		return 0;
	}
	pf_bool	isZero(pf_f64 data)
	{
		return fabs(data) < thre;
	}
};


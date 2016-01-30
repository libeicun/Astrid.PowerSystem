#pragma once
#include "pf_calc_def_data_type.h"
class CTiming
{
public:
	CTiming();
	~CTiming();
	static	pf_bool	off;
	static void		On();
	static void		Off();
	static void		TimeLable(char* label);
};


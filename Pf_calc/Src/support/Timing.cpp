#include "Timing.h"
#include "afx.h"

CTiming::CTiming()
{
}


CTiming::~CTiming()
{
}
pf_bool	CTiming::off=1;

void CTiming::TimeLable(char* label){
	if (off)
		return;
	SYSTEMTIME	syst;
	GetLocalTime(&syst);
	printf("Timer>>Hit -%s\n           -%d :%d :%d.\n",
		label, syst.wMinute, syst.wSecond, syst.wMilliseconds);
}

void		CTiming::On(){
	off =0;
}
void		CTiming::Off(){
	off = 1;
}
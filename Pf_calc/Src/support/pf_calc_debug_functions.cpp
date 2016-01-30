#include "pf_calc_debug_defs.h"

void dbg_1darray_cpy(PF_CALC_DATA_TYPE*	ArrayDest	,PF_CALC_DATA_TYPE*	 ArraySrc,pf_uint32 Size)
{
	for (pf_uint32	i=0;i<Size;i++)
	{
	ArrayDest[i]=ArraySrc[i];
	}
}

void dbg_1darray_set(PF_CALC_DATA_TYPE*	ArrayDest	,pf_uint32 Size,PF_CALC_DATA_TYPE	val)
{
	for (pf_uint32	i=0;i<Size;i++)
	{
		ArrayDest[i]=val;
	}
}
void dbg_1darray_printf(PF_CALC_DATA_TYPE*	ArrayDest,pf_uint32	Size)				
{
	printf("/n");
	for (pf_uint32	i=0;i<Size;i++)
	{
		printf("%4.4f ",ArrayDest[i]);
	}
}


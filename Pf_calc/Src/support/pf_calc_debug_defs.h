#ifndef PF_CALC_DEBUG_DEFS_H
#define PF_CALC_DEBUG_DEFS_H
#include "pf_calc_def_data_type.h"
#include "pfcalcNode.h"
#include <stdio.h>

void dbg_1darray_cpy(PF_CALC_DATA_TYPE*	ArrayDest	,PF_CALC_DATA_TYPE*	 ArraySrc,pf_uint32 Size);
void dbg_1darray_set(PF_CALC_DATA_TYPE*	ArrayDest	,pf_uint32 Size,PF_CALC_DATA_TYPE	val);
void dbg_1darray_printf(PF_CALC_DATA_TYPE*	ArrayDest,pf_uint32	Size)	;


#define		DEBUG_2DARRAY_DEF(Type,ArrayName,SizeI,sizeJ)				Type	ArrayName[SizeI][sizeJ]
#define		DEBUG_1DARRAY_DEF(Type,ArrayName,SizeI)						Type	ArrayName[SizeI]

#define		DEBUG_1DARRAY_COPY(ArrayDest,ArraySrc,Size)   dbg_1darray_cpy(ArrayDest,ArraySrc,Size)

#define		DEBUG_2DARRAY_COPY(ArrayDest,ArraySrc,SizeI,SizeJ)	;

#define		DEBUG_1DARRAY_CLR(ArrayDest,Size)			dbg_1darray_set(ArrayDest,Size,0)
#define		DEBUG_2DARRAY_CLR(ArrayDest,SizeI,SizeJ)	;
#define		DEBUG_1DARRAY_PRINTF(ArrayDest,Size)	dbg_1darray_printf(ArrayDest,Size)	
#define		DEBUG_2DARRAY_PRINTF(ArrayDest,SizeI,SizeJ)		;

#endif
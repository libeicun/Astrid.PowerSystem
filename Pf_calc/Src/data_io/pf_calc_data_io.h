#ifndef PF_CALC_DATA_IO_H
#define PF_CALC_DATA_IO_H

#include "pf_calc_def_upr.h"
enum ePfDataStructType
{
	ePfDataStructTypeIEEE,
	ePfDataStructTypeGB1235,
	ePfDataStructTypeLBCTest,
}
;
extern		void		PfDataReadFile		(PF_CALC_CB* pfcb, const char* fileName, ePfDataStructType datatructType);
extern      int		PfDataCheck(PF_CALC_CB* pfcb,ePfDataStructType datatructType);
extern		void		PfDataWriteFile		(PF_CALC_CB* pfcb, const char* fileName, ePfDataStructType datatructType);
extern		void		PfResultOutput		(PF_CALC_CB* pfcb, char* fileName);

extern void PfStringDataAppendFile(
								   pf_char*	filename,
									pf_char*	str
								   );

#if 0
extern void Pf2DArrayDataAppendFile(
									const pf_char*					filename,
									PF_CALC_DATA_TYPE**	data,
									pf_char*							caption,
									pf_uint32							sizei,
									pf_uint32							sizej,
									pf_char*							divChari,
									pf_char*							divCharj);
#endif

extern void Pf1DArrayDataAppendFile(
									const pf_char*					filename,
									PF_CALC_DATA_TYPE*   	data,
									pf_char*							caption,
									pf_uint32							sizei,
									pf_char*							divChari);

#endif PF_CALC_DATA_IO_H
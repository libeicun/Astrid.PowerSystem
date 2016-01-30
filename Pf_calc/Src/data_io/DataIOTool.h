#pragma once
#include "MethodNewtonRaphson.h"
enum ePfDataStructType
{
	ePfDataStructTypeIEEE,
	ePfDataStructTypeGB1235,
	ePfDataStructTypeLBCTest,
}
;
class CDataIOTool
{
private:
	CMethodSolvePowerSysNlEquations* pMethodObj;
public:
	CDataIOTool(CMethodSolvePowerSysNlEquations&pMethod);
	CDataIOTool();
	virtual ~CDataIOTool();
	void	SetMethodObjPtr(CMethodSolvePowerSysNlEquations*	pMethod);
	void	DataReadFile( pf_char* fileName, ePfDataStructType datatructType);
	int		DataCheck( ePfDataStructType datatructType);
	void	DataWriteFile(CMethodNewtonRaphson*	pfcb, pf_char* fileName);
	void	ResultOutput(CMethodNewtonRaphson*	pfcb, pf_char* fileName);

	static void PfStringDataAppendFile(
		pf_char*	filename,
		pf_char*	str
		);
	static void Pf1DArrayDataAppendFile(
		const pf_char*					filename,
		PF_CALC_DATA_TYPE*   	data,
		pf_char*							caption,
		pf_uint32							sizei,
		pf_char*							divChari);
	static void CDataIOTool::Pf2DArrayDataAppendFile(
		const pf_char*					filename,
		PF_CALC_DATA_TYPE**	data,
		pf_char*							caption,
		pf_uint32							sizei,
		pf_uint32							sizej,
		pf_char*							divChari,
		pf_char*							divCharj);
	static void CDataIOTool::PfMatrixDataAppendFile(
		const pf_char*					filename,
		CSMatrixSP1_3<double>*	data,
		pf_char*							caption,
		pf_uint32							sizei,
		pf_uint32							sizej,
		pf_char*							divChari,
		pf_char*							divCharj);

};


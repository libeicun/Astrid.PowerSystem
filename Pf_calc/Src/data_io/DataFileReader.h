#pragma once
#include "pf_calc_def_data_type.h"
#include "PfCalcNode.h"
#include "DMatrix.h"
enum eReadDataFileErr
{
	eReadDataFileErrInvalidPath,
	eReadDataFileErrFileNotFound,
	eReadDataFileErrInvalidData
};

class CDataFileReader
{
public:
	CDataFileReader();
	virtual ~CDataFileReader();


	virtual eReadDataFileErr ReadDataFile(pf_char* path) = 0;


	virtual		pf_bool	GetMaxIterTimes(pf_uint32&	times)=0;
	virtual		pf_bool	GetPresion(pf_f64& pre)=0;

	
	virtual pf_bool GetBlNodeNbr(pf_uint32& nbr) = 0;
	virtual pf_bool GetPqNodeNbr(pf_uint32& nbr) = 0;
	virtual pf_bool GetPvNodeNbr(pf_uint32& nbr) = 0;


	virtual pf_bool GetPqNodeTable(CPfCalcNodePq* table, pf_uint32 size) = 0;
	virtual pf_bool GetPvNodeTable(CPfCalcNodePv* table, pf_uint32 size) = 0;
	virtual pf_bool GetBlNodeTable(CPfCalcNodeBl* table, pf_uint32 size) = 0;
	virtual pf_bool GetNodeTables(CPfCalcNodeBl* tablebl,  
		CPfCalcNodePq* tablepq,  
		CPfCalcNodePv* tablepv)=0;

	virtual pf_bool GetMatGij(CMatrix<PF_CALC_DATA_TYPE>* g_mat) = 0;
	virtual pf_bool GetMatBij(CMatrix<PF_CALC_DATA_TYPE>	* b_mat) = 0;
	virtual pf_bool GetMatY(
		CMatrix<PF_CALC_DATA_TYPE>	* g_mat,
		CMatrix<PF_CALC_DATA_TYPE>	* b_mat) = 0;



};


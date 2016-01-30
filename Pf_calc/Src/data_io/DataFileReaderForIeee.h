#pragma once
#include "DataFileReader.h"
#include <list>
using namespace std;
class CPfCalcDfIeeeBlNodePara
{
public:
	CPfCalcDfIeeeBlNodePara(){};
	virtual ~CPfCalcDfIeeeBlNodePara(){};
	pf_uint32	nodeNo;
}
;
class 	CPfCalcDfIeeeLinePara
{
public:
	virtual ~CPfCalcDfIeeeLinePara(){};
	CPfCalcDfIeeeLinePara(){};
	pf_uint32	branchNo;
	pf_uint32	nodei;
	pf_uint32	nodej;
	PF_CALC_DATA_TYPE	R;
	PF_CALC_DATA_TYPE	X;
	PF_CALC_DATA_TYPE	bDiv2;
}
;
class 	CPfCalcDfIeeeGLinePara
{
public:
	CPfCalcDfIeeeGLinePara(){};
	virtual ~CPfCalcDfIeeeGLinePara(){};
	pf_uint32 nodeNo;
	PF_CALC_DATA_TYPE	G;

}
;
class 	CPfCalcDfIeeeTransPara
{
public:
	CPfCalcDfIeeeTransPara(){};
	virtual	~CPfCalcDfIeeeTransPara(){};
	pf_uint32	branchNo;
	pf_uint32	nodei;
	pf_uint32	nodej;
	PF_CALC_DATA_TYPE	R;
	PF_CALC_DATA_TYPE	X;
	PF_CALC_DATA_TYPE	k0;
	PF_CALC_DATA_TYPE	kMin;
	PF_CALC_DATA_TYPE	kMax;
}
;
class 	CPfCalcDfIeeeRunningPara
{
public:
	CPfCalcDfIeeeRunningPara(){};
	virtual	~CPfCalcDfIeeeRunningPara(){};
	pf_uint32						nodeNo;
	PF_CALC_DATA_TYPE	Pg;
	PF_CALC_DATA_TYPE	Qg;
	PF_CALC_DATA_TYPE	Pl;
	PF_CALC_DATA_TYPE	Ql;
}
;
class 	CPfCalcDfIeeePvNodePara
{
public:
	CPfCalcDfIeeePvNodePara(){};
	virtual	~CPfCalcDfIeeePvNodePara(){};
	pf_uint32						nodeNo;
	PF_CALC_DATA_TYPE						u;
	PF_CALC_DATA_TYPE	QMin;
	PF_CALC_DATA_TYPE	QMax;

}
;
class CPfCalcDfIeeeGCostPara
{
public:
	CPfCalcDfIeeeGCostPara(){};
	virtual	~CPfCalcDfIeeeGCostPara(){};

	pf_uint32						nodeNo;
	PF_CALC_DATA_TYPE	c;
	PF_CALC_DATA_TYPE	b;
	PF_CALC_DATA_TYPE	a;
	PF_CALC_DATA_TYPE	PgMin;
	PF_CALC_DATA_TYPE	PgMax;
}
;
class CPfCalcDfHdrIeee
{
public:
	CPfCalcDfHdrIeee(){};
	virtual	~CPfCalcDfHdrIeee(){};
	pf_uint32						nodeNbr;
	pf_uint32						branchNbr;
	PF_CALC_DATA_TYPE	Capacity;
	pf_uint32						maxIterTimes;
	PF_CALC_DATA_TYPE	centralPara;
	PF_CALC_DATA_TYPE	precision;
	pf_uint32						functionClass;
}
;

class CDataFileReaderForIeee :
	public CDataFileReader
{
private:
	CPfCalcDfHdrIeee															MyFileHeader;
	pf_uint32																			pqNodeNbr;
	pf_uint32																			pvNodeNbr;
	pf_uint32																			blNodeNbr;
	list	<CPfCalcDfIeeeBlNodePara>								blNodeParaList;
	list	<CPfCalcDfIeeeLinePara>									lineParaList;
	list	<CPfCalcDfIeeeGLinePara>									gLineParaList;
	list	<CPfCalcDfIeeeTransPara>									transParaList;
	list	<CPfCalcDfIeeeRunningPara>							runningParaList;
	list	<CPfCalcDfIeeePvNodePara>								pvNodeParaList;
	list	<CPfCalcDfIeeeGCostPara>									gcostParaList;

public:
	CDataFileReaderForIeee();
	virtual ~CDataFileReaderForIeee();
     eReadDataFileErr ReadDataFile(pf_char* path)  ;
     pf_bool GetBlNodeNbr(pf_uint32& nbr)  ;
     pf_bool GetPqNodeNbr(pf_uint32& nbr)  ;
	 pf_bool GetPvNodeNbr(pf_uint32& nbr)  ;


	 pf_bool GetPqNodeTable(CPfCalcNodePq* table, pf_uint32 size)  ;
	 pf_bool GetPvNodeTable(CPfCalcNodePv* table, pf_uint32 size)  ;
	 pf_bool GetBlNodeTable(CPfCalcNodeBl* table, pf_uint32 size)  ;
	 pf_bool GetNodeTables(CPfCalcNodeBl* tablebl,  
		 CPfCalcNodePq* tablepq, 
		 CPfCalcNodePv* tablepv);


	 pf_bool GetMatGij(CMatrix<PF_CALC_DATA_TYPE>* g_mat);
	 pf_bool GetMatBij(CMatrix<PF_CALC_DATA_TYPE>	* b_mat);
	 pf_bool GetMatY(
		 CMatrix<PF_CALC_DATA_TYPE>	* g_mat,
		 CMatrix<PF_CALC_DATA_TYPE>	* b_mat);

	 pf_bool CheckDataFile(pf_char* path);


	 virtual		pf_bool	GetMaxIterTimes(pf_uint32&	times);
	 virtual		pf_bool	GetPresion(pf_f64& pre);

};


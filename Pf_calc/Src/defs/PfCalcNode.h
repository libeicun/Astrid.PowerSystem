#pragma once
#include "pf_calc_def_data_type.h"
#include "pf_calc_sys_cfg.h"

class CPfCalcNode{
public:
	pf_uint32							index;
	PF_CALC_DATA_TYPE		e;//未知量
	PF_CALC_DATA_TYPE		f;//未知量

	CPfCalcNode();
	virtual ~CPfCalcNode();
};

class CPfCalcNodePq : public CPfCalcNode
{
public:
	PF_CALC_DATA_TYPE		P;//已知量
	PF_CALC_DATA_TYPE		Q;//已知量
	pf_uint32 offset;//Use for Jacorb Matrix and .deltaPQPU2[] and deltaEF[];
	pf_uint32	offset2;//Use for .aii[] and .bii[]
	CPfCalcNodePq();
	virtual ~CPfCalcNodePq();
private:

};
class CPfCalcNodePv : public CPfCalcNode
{
public:
	PF_CALC_DATA_TYPE		P;//已知量
	PF_CALC_DATA_TYPE		Ql;//已知量
	PF_CALC_DATA_TYPE		Qg;//未知量
	PF_CALC_DATA_TYPE		U2;//已知量
	pf_uint32 offset;//Use for Jacorb Matrix and .deltaPQPU2[] and deltaEF[];
	pf_uint32	offset2;//Use for .aii[] and .bii[]
	CPfCalcNodePv();
	virtual ~CPfCalcNodePv();
private:
};

class CPfCalcNodeBl : public CPfCalcNode
{
public:

	PF_CALC_DATA_TYPE	Pl;//已知量
	PF_CALC_DATA_TYPE	Ql;//已知量
	PF_CALC_DATA_TYPE	Pg;//未知量
	PF_CALC_DATA_TYPE	Qg;//未知量
	pf_uint32 offset;//Use for Jacorb Matrix and .deltaPQPU2[] and deltaEF[];
	pf_uint32	offset2;//Use for .aii[] and .bii[]
	CPfCalcNodeBl();
	virtual ~CPfCalcNodeBl();
private:
};




/*节点类型定义*/
enum ePfNodeClass
{
	ePfNodeClassPV,
	ePfNodeClassPQ,
	ePfNodeClassBL,
};
class CComplex
{
public:
	PF_CALC_DATA_TYPE real;
	PF_CALC_DATA_TYPE image;
	CComplex();
	virtual ~CComplex();
}
;



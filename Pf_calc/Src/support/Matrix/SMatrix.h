#pragma once
#include "pf_calc_def_data_type.h"
#include <stdio.h>
#include<assert.h>

#include "Matrix.h"
#include "SMatrix_Enum.h"
#include "pf_calc_sys_cfg.h"

template <class T>
class CSMatrix:public CMatrix<T>
{
public:	
	CSMatrix(){
	}
	CSMatrix(pf_uint32 sizeM, pf_uint32 sizeN)
	{
	}
	CSMatrix<T>(CSMatrix<T>& mat);
	~CSMatrix(){}

	virtual	T			Get(pf_uint32	i, pf_uint32	j) = 0;
	virtual	void	Get_r(pf_uint32	i, pf_uint32	j, T&		val) = 0;
	virtual	void	Set(pf_uint32		i, pf_uint32	j, const T&		val) = 0;
	virtual	void	Add(pf_uint32		i, pf_uint32	j, const T&		val) = 0;

	virtual	T			Get_Lwr(pf_uint32	i, pf_uint32	j) = 0;
	virtual	void	Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val) = 0;
	virtual	void	Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val) = 0;
	virtual	void	Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val) = 0;

	virtual	void				IteratorReset() = 0;
	virtual	void				IteratorMove() = 0;
	virtual	S_MATRIX_NODE	IteratorGetNode() = 0;
	virtual	pf_bool			IteratorReachEnd() = 0;
	virtual	pf_uint32		GetNoneZeroNbr() = 0;

	virtual	pf_uint32			SubIteratorReset(pf_uint32 MainIndex){
		return pf_uint32();
	}
	virtual	pf_bool			SubIteratorMove(){
		return pf_bool();
	}
	virtual	pf_uint32		SubIteratorGetMainIndex(){
		return pf_uint32();
	}
	virtual	pf_uint32		SubIteratorGetSubIndex(){
		return pf_uint32();
	}
	virtual	pf_f64				SubIteratorGetVal() {
		return pf_f64();
	}
	virtual	pf_bool			SubIteratorReachEnd() {
		return  pf_bool();
	}
};

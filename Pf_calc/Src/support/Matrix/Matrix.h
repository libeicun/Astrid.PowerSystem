#pragma once

#include <stdio.h>
#include "pf_calc_def_data_type.h"
#include "pf_calc_sys_cfg.h"
struct S_MATRIX_NODE
{
	pf_uint32							i;
	pf_uint32							j;
	PF_CALC_DATA_TYPE	Val;
};
template	<class T>
class CMatrix 
{
protected:
	pf_uint32	iNbr;
	pf_uint32	jNbr;
public:
	CMatrix();
	virtual ~CMatrix();

	/*virtual	pf_f32			GetSparsity()=0;
	virtual	void			Print()=0;
	*/

	virtual	T			Get(pf_uint32	i, pf_uint32	j) = 0;
	virtual	void	Get_r(pf_uint32	i, pf_uint32	j, T&		val) = 0;
	virtual	void	Set(pf_uint32		i, pf_uint32	j, const T&		val) = 0;
	virtual	void	Add(pf_uint32		i, pf_uint32	j, const T&		val) = 0;

	virtual	T			Get_Lwr(pf_uint32	i, pf_uint32	j) = 0;
	virtual	void	Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val) = 0;
	virtual	void	Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val) = 0;
	virtual	void	Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val) = 0;

};

template <class T>
CMatrix<T>::CMatrix()
{
}

template <class T>
CMatrix<T>::~CMatrix()
{
}



#pragma once
#include "SMatrix.h"

#include "spdefs.h"
#include "spconfig.h"
#include "spmatrix.h"
#include "Timing.h"
#include <stdio.h>
template <class T>
class CSMatrixSP1_3 :
	public CSMatrix < T >
{
protected:
	pf_uint32	StatCalls_fGet;
	pf_uint32	StatCalls_fGet_r;
	pf_uint32	StatCalls_fSet;
	char*		pMat;
	pf_uint8	IndicesOffset;
	pf_bool	bNeedOrderAndFactor;
public:
	CSMatrixSP1_3(pf_uint32 iNbr, pf_uint32 jNbr);
	CSMatrixSP1_3(CSMatrixSP1_3<T>& mat);
	CSMatrixSP1_3<T>& operator=(CSMatrixSP1_3<T> mat);
	virtual ~CSMatrixSP1_3();

	void	Set(pf_uint32	i, pf_uint32	j, const T&		val);
	void	Add(pf_uint32	i, pf_uint32	j, const T&		val);
	void	Get_r(pf_uint32	i, pf_uint32	j, T&		val);
	T		Get(pf_uint32	i, pf_uint32	j);

	T		Get_Lwr(pf_uint32	i, pf_uint32	j);
	void	Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val);
	void	Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val);
	void	Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val);
	pf_uint32 GetNoneZeroNbr();

	void			Solve(T* RHS, T* Solution, pf_uint32	VectSize);
	void			SetIndicesOffsetZero(){
		IndicesOffset = 0;
	}
	void			SetIndicesOffsetOne(){
		IndicesOffset = 1;
	}
	void			OrderAndFactorOn(){
		bNeedOrderAndFactor = 1;
	}
	void			OrderAndFactorOff(){
		bNeedOrderAndFactor = 0;
	}
	virtual	void				IteratorReset(){
	}
	virtual	void				IteratorMove(){
	}
	virtual	S_MATRIX_NODE	IteratorGetNode()	{
		return S_MATRIX_NODE();
	}
	virtual	pf_bool			IteratorReachEnd() {
		return pf_bool();
	}



	
};


template <class T>
CSMatrixSP1_3<T>::~CSMatrixSP1_3()
{
	CTiming::TimeLable("Distruct CSMatrixSP1_3");
	printf("-%d Times Call Get\n", StatCalls_fGet);
	
	printf("-%d Times Call Get_r\n", StatCalls_fGet_r);
	printf("-%d Times Call Set\n", StatCalls_fSet);
	spDestroy(pMat);
}

template <class T>
CSMatrixSP1_3<T>::CSMatrixSP1_3(pf_uint32 iNbr, pf_uint32 jNbr){
	CTiming::TimeLable("Contruct CSMatrixSP1_3");
	assert(iNbr > 0 && jNbr > 0);

	IndicesOffset = 1;
	bNeedOrderAndFactor=1;

	StatCalls_fGet=0;
	StatCalls_fGet_r = 0;
	StatCalls_fSet = 0;

	this->iNbr = iNbr;
	this->jNbr = jNbr;
	pf_int32	err;
	pMat = spCreate(0, 0, &err);
	if (err!=spOKAY)
	{
		printf("Fatal error occur when construct CSMatrixSP1_3 obj\n");
	}
	spSetReal(pMat);
}
template <class T>
CSMatrixSP1_3<T>::CSMatrixSP1_3(CSMatrixSP1_3<T>& mat){
}
template <class T>
CSMatrixSP1_3<T>& CSMatrixSP1_3<T>::operator=(CSMatrixSP1_3<T> mat){
	CSMatrixSP1_3<T> newMat;
	return newMat;

}
template <class T>
void	CSMatrixSP1_3<T>::Set(pf_uint32	i, pf_uint32	j, const T&		val){
	//StatCalls_fSet++;
	if (IndicesOffset){
		i++; j++;
	}
	else{

	}
	spREAL*	ele=spGetElement(pMat,i,j);
	spADD_REAL_ELEMENT(ele, val-*ele);
}
template <class T>
void	CSMatrixSP1_3<T>::Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val){
	if (IndicesOffset){
		i++; j++;
	}
	else{

	}
	spREAL*	ele;
	if (i >= j){
			ele = spGetElement(pMat, i, j);
	}
	else{
			ele = spGetElement(pMat, j, i);
	}
	spADD_REAL_ELEMENT(ele, val - *ele);
}
template <class T>
void	CSMatrixSP1_3<T>::Add(pf_uint32	i, pf_uint32	j, const T&		val){
	if (IndicesOffset){
		i++; j++;
	}
	else{

	}
	spREAL*	ele = spGetElement(pMat, i, j);
	spADD_REAL_ELEMENT(ele, val);
}
template <class T>
void	CSMatrixSP1_3<T>::Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val){
	if (IndicesOffset){
		i++; j++;
	}
	else{

	}
	spREAL*	ele;
	if (i >= j){
			ele = spGetElement(pMat, i, j);
	}
	else{
			ele = spGetElement(pMat, j, i);
	}
	
	spADD_REAL_ELEMENT(ele, val);
}

template <class T>
void	CSMatrixSP1_3<T>::Get_r(pf_uint32	i, pf_uint32	j, T&		val){
	val = this->Get(i, j);
}
template <class T>
void	CSMatrixSP1_3<T>::Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val){
	val = this->Get_Lwr(i, j);
}
template <class T>
T		CSMatrixSP1_3<T>::Get(pf_uint32	i, pf_uint32	j){
	if (IndicesOffset){
		i++; j++;
	}
	else{

	}
	spREAL*	ele = spGetElement(pMat, i, j);
	return *ele;

}
template <class T>
T		CSMatrixSP1_3<T>::Get_Lwr(pf_uint32	i, pf_uint32	j){
	if (IndicesOffset){
		i++; j++;
	}
	else{

	}
	spREAL*	ele;
	if (i >= j){
			ele = spGetElement(pMat, i, j);
	}
	else{
			ele = spGetElement(pMat, j, i);
	}

	
	return *ele;
}
template <class T>
pf_uint32 CSMatrixSP1_3<T>::GetNoneZeroNbr()	{
	return spElementCount(pMat);
}
template <class T>
void		CSMatrixSP1_3<T>::Solve(T* RHS, T* Solution, pf_uint32	size){
	/*Use the Sparse 1.3 to Solve the system.*/
	if (bNeedOrderAndFactor){
		CTiming::TimeLable("Enter spMNA_Preorder");
		spMNA_Preorder(pMat);
		CTiming::TimeLable("Exit  spMNA_Preorder");
		CTiming::TimeLable("Enter spOrderAndFactor");
		int	err = spOrderAndFactor(pMat, RHS, 0.0001, 0.0001, YES);
		CTiming::TimeLable("Exit  spOrderAndFactor");
	}else{
		CTiming::TimeLable("Enter spOrderAndFactor");
		int	err = spOrderAndFactor(pMat, RHS, 0.0001, 0.0001, YES);
		CTiming::TimeLable("Exit  spOrderAndFactor");
	}
	
	/*CTiming::TimeLable("Enter spFactor");
	err = spFactor(pMat);
	CTiming::TimeLable("Exit  spFactor");*/
	CTiming::TimeLable("Enter spSolve");
	spSolve(pMat, RHS, Solution);
	CTiming::TimeLable("Exit  spSolve");
}
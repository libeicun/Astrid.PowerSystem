#pragma once
#include "Matrix.h"
#include <math.h>
template <class T>
class CDMatrix :
	public CMatrix < T >
{
protected:
	T**		pMat;
public:
	CDMatrix(pf_uint32 iNbr, pf_uint32 jNbr);
	CDMatrix(CDMatrix<T>& mat);
	CDMatrix<T>&	operator=(CDMatrix<T> mat);
	virtual ~CDMatrix();


	inline T		Get(pf_uint32	i, pf_uint32	j);
	inline void		Get_r(pf_uint32	i, pf_uint32	j, T&		val);
	inline void		Set(pf_uint32		i, pf_uint32	j, const T&		val);
	inline	void	Add(pf_uint32		i, pf_uint32	j, const T&		val);

	inline	T		Get_Lwr(pf_uint32	i, pf_uint32	j);
	inline	void	Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val);
	inline	void	Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val);
	inline	void	Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val);
};

template <class  T>
CDMatrix<T>::CDMatrix(pf_uint32 iNbr, pf_uint32 jNbr){
	this->iNbr = iNbr;
	this->jNbr = jNbr;
	pf_uint32	i, j;
	pMat = new T*[iNbr];
	for (i = 0; i < iNbr; i++){
		pMat[i] = new T[jNbr];
		for (j = 0; j < jNbr; j++){
			pMat[i][j] = 0;
		}
	}
}

template <class T>
CDMatrix<T>::CDMatrix(CDMatrix<T>& mat){
	this->iNbr = mat.iNbr;
	this->jNbr = mat.jNbr;
	pf_uint32	i, j;
	this->pMat = new T*[iNbr];
	for (i = 0; i < iNbr; i++){
		this->pMat[i] = new T[jNbr];
		for (j = 0; j < jNbr; j++){
			this->pMat[i][j] = mat.pMat[i][j];
		}
	}
}
template <class T>
CDMatrix<T>& CDMatrix<T>::operator=(CDMatrix<T> mat){
	CDMatrix<T> newMat;
	newMat.NoneZeroNbr = mat.NoneZeroNbr;
	newMat.iNbr = mat.iNbr;
	newMat.jNbr = mat.jNbr;

	newMat.Set(i, j, mat.pMat[i][j]);
	return newMat;

}
template <class  T>
CDMatrix<T>::~CDMatrix(){
	//GetSparsity();
	for (pf_uint32 i = 0; i < iNbr; i++){
		delete pMat[i];
	}
	delete pMat;
}




template <class  T>
inline T		CDMatrix<T>::Get(pf_uint32	i, pf_uint32	j) {
	return pMat[i][j];
}
template <class  T>
inline	T		CDMatrix<T>::Get_Lwr(pf_uint32	i, pf_uint32	j){
	if (i >= j){
		return pMat[i][j];
	}
	else{
		return pMat[j][i];
	}
}

template <class  T>
inline void	CDMatrix<T>::Get_r(pf_uint32	i, pf_uint32	j, T&		val) {
	val = pMat[i][j];
}
template <class  T>
inline	void	CDMatrix<T>::Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val){
	if (i >= j){
		val = pMat[i][j];
	}
	else{
		val = pMat[j][i];
	}
}

template <class  T>
inline void	 CDMatrix<T>::Set(pf_uint32		i, pf_uint32	j, const T&		val) {
	pMat[i][j] = val;

}

template <class  T>
inline	void	CDMatrix<T>::Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val){
	if (i >= j){
		pMat[i][j] = val;
	}
	else{
		pMat[j][i] = val;
	}
}
template <class  T>
inline void	CDMatrix<T>::Add(pf_uint32		i, pf_uint32	j, const T&		val) {
	pMat[i][j] += val;

}
template <class  T>
inline	void	CDMatrix<T>::Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val) {
	if (i>=j){
		pMat[i][j] += val;
	}
	else{
		pMat[j][i] += val;
	}
	
}



#pragma once
#include "SMatrix.h"
#include "SMatrixCS.h"
template <class T>
class CSMatrixCSC :
	public CSMatrix < T >
{
private:
	CSMatrixCS<T>*		pMyMat;
public:
	CSMatrixCSC(pf_uint32 iNbr, pf_uint32 jNbr){
		pMyMat = new CSMatrixCS<T>(iNbr, jNbr);
	}
	~CSMatrixCSC(){
		delete pMyMat;
	}
	T			Get(pf_uint32	i, pf_uint32	j);
	void	Get_r(pf_uint32	i, pf_uint32	j, T&		val);
	void	Set(pf_uint32		i, pf_uint32	j, const T&		val);
	void	Add(pf_uint32		i, pf_uint32	j, const T&		val);

	T			Get_Lwr(pf_uint32	i, pf_uint32	j);
	void	Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val);
	void	Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val);
	void	Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val);

	pf_uint32					GetNoneZeroNbr();

	void							IteratorReset();
	void							IteratorMove();
	S_MATRIX_NODE	IteratorGetNode();
	pf_bool						IteratorReachEnd();


	virtual	pf_uint32			SubIteratorReset(pf_uint32 MainIndex){

		return pMyMat->SubIteratorReset(MainIndex);
	}
	virtual	pf_bool			SubIteratorMove(){
		return pMyMat->SubIteratorMove();
	}
	virtual	pf_uint32		SubIteratorGetMainIndex(){
		return pMyMat->IteratorGetMainIndex();
	}
	virtual	pf_uint32		SubIteratorGetSubIndex(){
		return pMyMat->SubIteratorGetSubIndex();
	}
	virtual	pf_f64				SubIteratorGetVal() {
		return pMyMat->SubIteratorGetVal();
	}
	virtual	pf_bool			SubIteratorReachEnd() {
		return  pMyMat->SubIteratorReachEnd();
	}
};

template <class T>
void	CSMatrixCSC<T>::IteratorReset(){
	pMyMat->IteratorReset();
}
template <class T>
void	CSMatrixCSC<T>::IteratorMove(){
	pMyMat->IteratorMove();

}
template <class T>
S_MATRIX_NODE	CSMatrixCSC<T>::IteratorGetNode(){
	S_MATRIX_NODE	tmp;
	tmp.i = pMyMat->IteratorGetMainIndex();
	tmp.j = pMyMat->iteratorGetSubIndex();
	tmp.Val = pMyMat->IteratorGetVal();
	return tmp;

}
template <class T>
pf_bool	CSMatrixCSC<T>::IteratorReachEnd(){
	return  pMyMat->IteratorReachEnd();
}




template <class T>
pf_uint32	CSMatrixCSC<T>::GetNoneZeroNbr(){
	return  pMyMat->GetNoneZeroNbr();
}


template <class T>
void	CSMatrixCSC<T>::Add_Lwr(pf_uint32		i, pf_uint32	j, const T&		val){
	if (j>= i){
		pMyMat->Add(j, i, val);
	}
	else{
		pMyMat->Add(i, j, val);
	}
}


template <class T>
void	CSMatrixCSC<T>::Set_Lwr(pf_uint32		i, pf_uint32	j, const T&		val){
	if (j >= i){
		pMyMat->Set(j,i, val);
	}
	else{
		pMyMat->Set(i,j, val);
	}
}


template <class T>
void	CSMatrixCSC<T>::Get_r_Lwr(pf_uint32	i, pf_uint32	j, T&		val){
	if (j>=i){
		val = pMyMat->Get(j,i);
	}
	else{
		val = pMyMat->Get(i, j);
	}
}

template <class T>
T	CSMatrixCSC<T>::Get_Lwr(pf_uint32 i, pf_uint32 j){
	if (j >=i){
		return pMyMat->Get(j, i);
	}
	else{
		return pMyMat->Get(i, j);
	}


}





template <class T>
void	CSMatrixCSC<T>::Add(pf_uint32		i, pf_uint32	j, const T&		val){
	pMyMat->Add(j, i ,val);
}


template <class T>
void	CSMatrixCSC<T>::Set(pf_uint32		i, pf_uint32	j, const T&		val){
	pMyMat->Set(j, i, val);
}


template <class T>
void	CSMatrixCSC<T>::Get_r(pf_uint32	i, pf_uint32	j, T&		val){
	val = pMyMat->Get(j,i);
}

template <class T>
T	CSMatrixCSC<T>::Get(pf_uint32 i, pf_uint32 j){
	return pMyMat->Get(j, i);
}


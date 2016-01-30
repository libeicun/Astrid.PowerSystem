#pragma once
#include "SMatrix.h"
#include <list>

using namespace std;

/*template <class T>
class CBindingOfAxAi
{
public:
	pf_int32		Ai;
	T				Ax;
	CBindingOfAxAi(){}
	virtual ~CBindingOfAxAi(){}
};*/
template <class T>
class CApPackage
{
public:
	
	list<pf_uint32>							IndexList;
	list<T>										ValList;
	CApPackage(){}
	virtual ~CApPackage(){}
};


template <class T>
class CSMatrixCS 
{
private:
	pf_uint32								MainNbr;
	CApPackage<T>*				pApp;
	pf_uint32								NoneZeroNbr;
	T												Threshold;

	pf_uint32								MainPlusSubIndexOfEnd;
	pf_bool									bReachEnd;
	PF_CALC_DATA_TYPE		CurrentVal;
	pf_uint32								CurrentMainIndex;
	pf_uint32								CurrentSubIndex;
	list<pf_f64>::iterator				CurrentIteratorVal;
	list<pf_uint32>::iterator		CurrentIteratorSubIndex;




	T												Sub_CurrentVal;
	pf_uint32								Sub_CurrentMainIndex;
	pf_uint32								Sub_CurrentSubIndex;
	list<pf_f64>::iterator				Sub_CurrentIteratorVal;
	list<pf_uint32>::iterator		Sub_CurrentIteratorSubIndex;


	eSparseMatrixErr					LocateNode(pf_uint32 i, pf_uint32 j, list<pf_uint32>::iterator& it_RowIndex, list<double>::iterator& it_Val);

public:

	CSMatrixCS(pf_uint32	MainNbr, pf_uint32	SubNbr);
	CSMatrixCS(CSMatrixCS<T>& mat);
	CSMatrixCS<T>& operator=(CSMatrixCS<T> mat);
	virtual ~CSMatrixCS();

	void	Set(pf_uint32	MainIndex, pf_uint32	SubIndex, const T&		val);
	void	Add(pf_uint32	MainIndex, pf_uint32	SubIndex, const T&		val);

	void	Get_r(pf_uint32	MainIndex, pf_uint32	SubIndex, T&		val);
	T			Get(pf_uint32	MainIndex, pf_uint32	SubIndex);

	pf_bool			IteratorReset();
	pf_bool			IteratorMove();
	pf_f64				IteratorGetVal() ;
	inline			pf_uint32		IteratorGetMainIndex();
	inline			pf_uint32		iteratorGetSubIndex();
	inline			pf_bool			IteratorReachEnd();
	inline			pf_uint32		GetNoneZeroNbr(){
		return NoneZeroNbr;
	}
	void			Solve(T* RightVect, T* X, pf_uint32	VectSize);

	pf_uint32			SubIteratorReset(pf_uint32 MainIndex) ;
	pf_bool			SubIteratorMove() ;
	pf_uint32		SubIteratorGetMainIndex() ;
	pf_uint32		SubIteratorGetSubIndex() ;
	pf_f64				SubIteratorGetVal() ;
	pf_bool			SubIteratorReachEnd() ;

};

template <class T>
CSMatrixCS<T>::CSMatrixCS(pf_uint32	MainNbr, pf_uint32	SubNbr){
	pApp = new CApPackage<T>[MainNbr];
	//this->MainNbr = MainNbr;
	this->MainNbr = MainNbr;
	MainPlusSubIndexOfEnd = 0;
	NoneZeroNbr = 0;
	bReachEnd = 0;
	Threshold = 0.00001;
}
template <class T>
CSMatrixCS<T>::~CSMatrixCS(){
	delete[] pApp;
}

template <class T>
CSMatrixCS<T>::CSMatrixCS(CSMatrixCS<T>& mat){
	this->NoneZeroNbr = mat.NoneZeroNbr;
	//this->iNbr = mat.iNbr;
	this->MainNbr = mat.MainNbr;
	this->pApp = new CApPackage < T >[MainNbr];
	for (pf_uint32 i = 0; i < MainNbr; i++){
		this->pApp[i] = mat.pApp[i];
	}

}
template <class T>
CSMatrixCS<T>& CSMatrixCS<T>::operator=(CSMatrixCS<T> mat){
	CSMatrixCS<T> newMat(mat);
	return newMat;

}
template <class T>
T	CSMatrixCS<T>::Get(pf_uint32 MainIndex, pf_uint32 SubIndex){
	list<pf_uint32>	::iterator    it_RowIndex;
	list<double>::iterator		 it_Val;

	eSparseMatrixErr	err = LocateNode(MainIndex, SubIndex, it_RowIndex, it_Val);
	if (err == eSparseMatrixErrNodeExist)
	{
		return *it_Val;
	}
	else
	{
		return 0;
	}
}
template <class T>
void	CSMatrixCS<T>::Get_r(pf_uint32	MainIndex, pf_uint32	SubIndex, T&		val){
	val = this->Get(MainIndex, SubIndex);
}
template <class T>
void	CSMatrixCS<T>::Set(pf_uint32 MainIndex, pf_uint32 SubIndex, const T& val){
	if (MainIndex >=MainNbr)
	{
		return;
	}
	if (fabs(val)<Threshold){
		return ;
	}
	pf_uint32	apIndex, aiIndex, axIndex, k;

	list<pf_uint32>::iterator				it_RowIndex;
	list<double>::iterator				it_Val;
	eSparseMatrixErr							err = LocateNode(MainIndex, SubIndex, it_RowIndex, it_Val);

	if (err == eSparseMatrixErrNodeExist)
	{
		*it_RowIndex = SubIndex;
		*it_Val = val;
	}
	else if (err == eSparseMatrixErrOK)
	{
		pApp[MainIndex].IndexList.insert(it_RowIndex, SubIndex);
		pApp[MainIndex].ValList.insert(it_Val, val);
		NoneZeroNbr++;

		pf_uint32	sum = MainIndex + SubIndex;
		if (sum>MainPlusSubIndexOfEnd){
			MainPlusSubIndexOfEnd = sum;
		}
	}

	return;

}

template <class T>
void	CSMatrixCS<T>::Add(pf_uint32 MainIndex, pf_uint32 SubIndex, const T& val){
	if (MainIndex >= MainNbr)
	{
		return;
	}
	pf_uint32	apIndex, aiIndex, axIndex, k;

	list<pf_uint32>::iterator				it_RowIndex;
	list<double>::iterator					it_Val;
	eSparseMatrixErr							err = LocateNode(MainIndex, SubIndex, it_RowIndex, it_Val);

	if (err == eSparseMatrixErrNodeExist)
	{
		*it_Val += val;
		if ((*it_Val) < Threshold)
		{

		}
	}
	else if (err == eSparseMatrixErrOK)
	{
		if (fabs(val)<Threshold)
		{
			return;
		}
		pApp[MainIndex].IndexList.insert(it_RowIndex, SubIndex);
		pApp[MainIndex].ValList.insert(it_Val, val);
		NoneZeroNbr++;

		pf_uint32	sum = MainIndex + SubIndex;
		if (sum > MainPlusSubIndexOfEnd){
			MainPlusSubIndexOfEnd = sum;
		}
	}

	return;

}


template <class T>
eSparseMatrixErr				CSMatrixCS<T>::LocateNode(pf_uint32 MainIndex, pf_uint32 SubIndex, list<pf_uint32>::iterator& it_RowIndex, list<double>::iterator& it_Val/*,
																																						  std::list<CBindingOfAxAi<T>>::iterator& it_binding*/){

	CApPackage<T>*			p = &pApp[MainIndex];

	for (it_Val = p->ValList.begin(), it_RowIndex = p->IndexList.begin();
		it_Val != p->ValList.end() && it_RowIndex != p->IndexList.end();
		it_Val++, it_RowIndex++)
	{
		if (*it_RowIndex == SubIndex)
		{
			return eSparseMatrixErrNodeExist;
		}
		else if (*it_RowIndex>SubIndex)
		{

			return eSparseMatrixErrOK;
		}
	}

	return eSparseMatrixErrOK;
}

template <class T>
pf_bool				CSMatrixCS<T>::IteratorReset(){
	CurrentMainIndex = 0;
	CurrentSubIndex = 0;
	CurrentVal = 0;
	bReachEnd = 0;
	if (NoneZeroNbr==0){
		return 1;
	}
	list<pf_f64>::iterator			it_Val;
	list<pf_uint32>::iterator	it_SubIndex;

	CApPackage<pf_f64>*	p=this->pApp;
	for (pf_uint32 i = 0; i < MainNbr;i++){
		if (p[i].ValList.size() > 0){
			CurrentIteratorVal = (p[i].ValList.begin());

			CurrentIteratorSubIndex = p[i].IndexList.begin();
			CurrentMainIndex = i;
			CurrentVal =*CurrentIteratorVal;
			CurrentSubIndex = *CurrentIteratorSubIndex;
			return 0;
		}
	}

	/*for (it_Val = p->ValList.begin(), it_SubIndex = p->IndexList.begin();
		it_Val != p->ValList.end() && it_SubIndex != p->IndexList.end();
		it_Val++, it_SubIndex++){

	}*/

	return pf_bool();
}
template <class T>
pf_bool				CSMatrixCS<T>::IteratorMove(){
	if (NoneZeroNbr==0){
		return 1;
	}
	/*if IteratorReachEnd(){
		return 1;
	}*/
	list<pf_f64>::iterator	it_val = CurrentIteratorVal;
	it_val++;

	if (it_val != pApp[CurrentMainIndex].ValList.end()){
		CurrentIteratorSubIndex++;
		CurrentIteratorVal++;
		CurrentSubIndex = *CurrentIteratorSubIndex;
		CurrentVal = *CurrentIteratorVal;
	}
	else{
		pf_uint32	mainindex=CurrentMainIndex;
		do {
			mainindex++;
			if (mainindex>=MainNbr){
				bReachEnd = 1;
				return 1;
			}
		} while (pApp[mainindex].ValList.size()==0);

		CurrentMainIndex = mainindex;
		CurrentIteratorSubIndex = pApp[CurrentMainIndex].IndexList.begin();
		CurrentIteratorVal = pApp[CurrentMainIndex].ValList.begin();
		CurrentSubIndex = *CurrentIteratorSubIndex;
		CurrentVal = *CurrentIteratorVal;
	}

	return pf_bool();
}
template <class T>
pf_f64				CSMatrixCS<T>::IteratorGetVal(){
	return pf_f64(CurrentVal);
}
template <class T>
pf_uint32		CSMatrixCS<T>::IteratorGetMainIndex(){
	return pf_uint32(CurrentMainIndex);
}
template <class T>
pf_uint32		CSMatrixCS<T>::iteratorGetSubIndex(){
	return pf_uint32(CurrentSubIndex);
}
template <class T>
pf_bool			CSMatrixCS<T>::IteratorReachEnd(){
//return pf_bool(CurrentMainIndex+CurrentSubIndex==MainPlusSubIndexOfEnd);
		return bReachEnd;
}

template <class T>
pf_uint32			CSMatrixCS<T>::SubIteratorReset(pf_uint32 MainIndex){
	Sub_CurrentMainIndex = MainIndex;
	Sub_CurrentIteratorVal = pApp[MainIndex].ValList.begin();
	Sub_CurrentIteratorSubIndex = pApp[MainIndex].IndexList.begin();
	pf_uint32 size = pApp[MainIndex].ValList.size();
	if (size==0 ){
		Sub_CurrentSubIndex =0;
		Sub_CurrentVal = 0;
	}else{
		Sub_CurrentSubIndex = *Sub_CurrentIteratorSubIndex;
		Sub_CurrentVal = *Sub_CurrentIteratorVal;
	}
	return size;
		
}
template <class T>
pf_bool			CSMatrixCS<T>::SubIteratorMove(){
	Sub_CurrentIteratorSubIndex++;
	Sub_CurrentIteratorVal++;
	if (SubIteratorReachEnd()){
		return 1;
	}
	Sub_CurrentSubIndex = *Sub_CurrentIteratorSubIndex;
	Sub_CurrentVal = *Sub_CurrentIteratorVal;
	return pf_bool();
}
template <class T>
pf_uint32		CSMatrixCS<T>::SubIteratorGetMainIndex(){
	return Sub_CurrentMainIndex;
}
template <class T>
pf_uint32		CSMatrixCS<T>::SubIteratorGetSubIndex(){
	return Sub_CurrentSubIndex;
}
template <class T>
pf_f64				CSMatrixCS<T>::SubIteratorGetVal(){
	return Sub_CurrentVal;
}
template <class T>
pf_bool			CSMatrixCS<T>::SubIteratorReachEnd(){
	return (Sub_CurrentIteratorSubIndex==pApp[Sub_CurrentMainIndex].IndexList.end());
}

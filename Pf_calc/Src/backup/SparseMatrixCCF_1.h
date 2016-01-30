#pragma once
#include "SMatrix.h"
#include <list>
using namespace std;

template <class T>
class CBindingOfAxAi
{
public:
	pf_int32		Ai;
	T				Ax;
	//CBindingOfAxAi(){}
	virtual ~CBindingOfAxAi(){}
};
template <class T>
class CApPackage
{
public:
	pf_uint32								Nbr;
	//list<CBindingOfAxAi<T>>				ColumnList;
	list<pf_int32>							ColumnListRowIndex;
	list<T>									ColumnListVal;
	CApPackage(){}
	virtual ~CApPackage(){}
};


template <class T>
class CSparseMatrixCCF :
	public CSparseMatrix < T >
{
private:
	CApPackage<T>*				pApp;
	

public:
	eSparseMatrixErr			LocateNode(pf_uint32 i, pf_uint32 j, list<pf_int32>::iterator& it_RowIndex, list<double>::iterator& it_Val);
	CSparseMatrixCCF(pf_uint32	iNbr, pf_uint32	jNbr){
		
		pApp = new CApPackage<T>[jNbr];
		this->iNbr = iNbr;
		this->jNbr = jNbr;
#if 0
/*
		CApPackage<T> app;
		app.Nbr = 0;
		app.ColumnListRowIndex.clear();
		app.ColumnListVal.clear();

		CBindingOfAxAi<T> binding;
		binding.Ai = -1;
		binding.Ax = 0;
		for (pf_uint32 i = 0; i < jNbr;i++)
		{
			pApp[i]=app;
			pApp[i].ColumnListRowIndex.push_back(binding.Ai);
			pApp[i].ColumnListVal.push_back(binding.Ax);
			//pApp[i].ColumnList.push_back(binding);Add a NoneSense node to represent the tail of list.
		}
*/	
#endif
	}
	virtual ~CSparseMatrixCCF(){}
	virtual	eSparseMatrixErr	Set(pf_uint32	i, pf_uint32	j, T		val);
	virtual	eSparseMatrixErr	Get_r(pf_uint32	i, pf_uint32	j, T&		val){
		return eSparseMatrixErrOK;
	}
	virtual	T						Get(pf_uint32	i, pf_uint32	j);
	virtual	pf_uint8				DelElem(pf_uint32 i, pf_uint32 j){ 
		return 0; 
	}
	pf_uint8				CpySparseMatrix(CSparseMatrixCCF& dest);

};

template <class T>
T				CSparseMatrixCCF<T>::Get(pf_uint32 i, pf_uint32 j){	
	list<pf_int32>	::iterator    it_RowIndex;
	list<double>::iterator		 it_Val;

	eSparseMatrixErr	err = LocateNode(i, j, it_RowIndex, it_Val);
	if (err==eSparseMatrixErrNodeExist)
	{
		return *it_Val;
	}
	else
	{
		return 0;
	}
}

template <class T>
eSparseMatrixErr	CSparseMatrixCCF<T>::Set(pf_uint32 i, pf_uint32 j, T val){
	if (i>=iNbr || j>=jNbr )
	{
		return eSparseMatrixErrInvalidPos;
	}
	pf_uint32	apIndex, aiIndex, axIndex,k;
#if 0
	list<pf_uint32>::iterator	it_ap;
	list<CBindingOfAxAi<T>>::iterator	 it_binding;
	CBindingOfAxAi<T>					b;
	if (BindingsAiAx.size()==0)
	{
		list<pf_uint32>::iterator	it_ap = pAp->begin();
		list<CBindingOfAxAi<T>>::iterator	 it_binding;
		aiIndex = 0;
		axIndex = 0;

		b.Ai = axIndex;
		b.Ax = val;
		BindingsAiAx.push_back(b);
	}
	else
	{
		it_ap = pAp->begin();
		for ( k = 0; k <=j; k++){
			it_ap++;
		}

		aiIndex =/* (*it_ap) +*/ (*(it_ap));
		axIndex = aiIndex;

		b.Ai =i;
		b.Ax = val;
		for (k = 0, it_binding = BindingsAiAx.begin(); k < axIndex; k++)
			it_binding++;
		list<CBindingOfAxAi<T>>::const_iterator cit = it_binding;
		BindingsAiAx.insert(it_binding,b);
	}
	

	
	/*Update the field Ap[].*/
	it_ap = pAp->begin();
	it_ap++;
	for (k = 0; k < j; k++, it_ap++);
	for (k = j ; k < jNbr; k++, it_ap++){
		(*it_ap)++; 
	}
#endif

	list<pf_int32>::iterator 	it_RowIndex;
	list<double>::iterator				it_Val;
	eSparseMatrixErr							err = LocateNode(i, j,it_RowIndex,it_Val);

	if (err==eSparseMatrixErrNodeExist)
	{
		*it_RowIndex = i;
		*it_Val = val;
	}
	else if (err==eSparseMatrixErrOK)
	{
		pApp[j].ColumnListRowIndex.insert(it_RowIndex, i);
		pApp[j].ColumnListVal.insert(it_Val, val);
	}

	return eSparseMatrixErrOK;

}
template <class T>
eSparseMatrixErr				CSparseMatrixCCF<T>::LocateNode(pf_uint32 i, pf_uint32 j, list<pf_int32>::iterator& it_RowIndex, list<double>::iterator& it_Val/*,
	std::list<CBindingOfAxAi<T>>::iterator& it_binding*/){

	CApPackage<T>*			p = &pApp[j];
#if 1
	for (it_Val = p->ColumnListVal.begin(), it_RowIndex = p->ColumnListRowIndex.begin();
		it_Val != p->ColumnListVal.end() && it_RowIndex != p->ColumnListRowIndex.end();
		it_Val++,it_RowIndex++)
	{
		if (*it_RowIndex==i)
		{
			return eSparseMatrixErrNodeExist;
		}
		else if (*it_RowIndex>i)
		{

			return eSparseMatrixErrOK;
		}
	}
#else
	if (size== 0){
		it_RowIndex = p->ColumnListRowIndex.end();
		it_Val = p->ColumnListVal.end();
		return eSparseMatrixErrOK;
	}
	if (size == 1){
		it_RowIndex = p->ColumnListRowIndex.begin();
		it_Val = p->ColumnListVal.begin();
		if (i==*it_RowIndex)
		{
			return eSparseMatrixErrNodeExist;
		}
		else if (i<*it_RowIndex){
		}
		else{
			it_RowIndex++, it_Val++;
		}
		return eSparseMatrixErrOK;

	}
	it_insert_point = p->ColumnListRowIndex.begin(); it_insert_point++;
	for (it_RowIndex = p->ColumnListRowIndex.begin(),it_Val=p->ColumnListVal.begin(), k = 0;
		k<size;
		it_RowIndex++, it_Val++, k++, it_insert_point++)
	{
		if (*it_RowIndex==i)
		{
			return eSparseMatrixErrNodeExist;
		}
		else if (i>*(it_RowIndex) && i<*(it_insert_point ))
		{
			it_RowIndex++, it_Val++;
			return eSparseMatrixErrOK;
		}
		else if (i<*(it_RowIndex))
		{
			return eSparseMatrixErrOK;
		}
	}
#endif
	return eSparseMatrixErrOK;
}

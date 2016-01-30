#include "MethodNewtonRaphsonHnjlsrBuilder_IterCSR.h"


CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::CMethodNewtonRaphsonHnjlsrBuilder_IterCSR()
{
	pZeroDetector = new CNumericGeneral;
}


CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::~CMethodNewtonRaphsonHnjlsrBuilder_IterCSR()
{
	delete pZeroDetector;
}



pf_bool CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::Build(){

	pf_uint32	i = 0, j = 0;
	pf_uint32	index_i = 0, index_iTimes2 = 0, index_j = 0, index_jTimes2 = 0;
	PF_CALC_DATA_TYPE	data_bij, data_gij;
	pf_uint32	Nbr;

	for (i = 0; i < pqNbr; i++)
	{
		index_i = pqNodeTable[i].index;//- pqNodeTable[i].id.offset;
		index_iTimes2 = 2 * (pqNodeTable[i].index - pqNodeTable[i].offset);

		Nbr = Bij->SubIteratorReset(index_i);
		for (j = 0; j < Nbr; j++,Bij->SubIteratorMove())
		{
			index_j = Bij->SubIteratorGetSubIndex();
			if (index_j==blNo){
				continue;
			}else if (index_j>blNo){
				index_jTimes2 = ( index_j-1)<<1;
			}else{
				index_jTimes2 = (index_j ) << 1;
			}
			data_bij = Bij->SubIteratorGetVal();
			data_gij = 0;
			if (index_i == index_j)//See Equation 4-41/b
			{
				setHNJLWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				setHNJLWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}
		Nbr = Gij->SubIteratorReset(index_i);
		for (j = 0; j < Nbr; j++, Gij->SubIteratorMove())
		{
			index_j = Gij->SubIteratorGetSubIndex();
			if (index_j == blNo){
				continue;
			}
			else if (index_j > blNo){
				index_jTimes2 = (index_j - 1) << 1;
			}
			else{
				index_jTimes2 = (index_j) << 1;
			}
			data_bij =0; 
			data_gij = Gij->SubIteratorGetVal();
			if (index_i == index_j)//See Equation 4-41/b
			{
				setHNJLWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				setHNJLWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}

	}



	for (i = 0; i < pvNbr; i++)
	{

		index_i = pvNodeTable[i].index;//- pvNodeTable[i].id.offset;
		index_iTimes2 = 2 * (pvNodeTable[i].index - pvNodeTable[i].offset);

		Nbr = Bij->SubIteratorReset(index_i);
		for (j = 0; j < Nbr; j++, Bij->SubIteratorMove())
		{
			index_j = Bij->SubIteratorGetSubIndex();
			if (index_j == blNo){
				continue;
			}
			else if (index_j > blNo){
				index_jTimes2 = (index_j - 1) << 1;
			}
			else{
				index_jTimes2 = (index_j) << 1;
			}
			data_bij = Bij->SubIteratorGetVal();
			data_gij = 0;
			if (index_i == index_j)//See Equation 4-41/b
			{
				setHNRSWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				setHNRSWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}


		Nbr = Gij->SubIteratorReset(index_i);
		for (j = 0; j < Nbr; j++, Gij->SubIteratorMove())
		{
			index_j = Gij->SubIteratorGetSubIndex();
			if (index_j == blNo){
				continue;
			}
			else if (index_j > blNo){
				index_jTimes2 = (index_j - 1) << 1;
			}
			else{
				index_jTimes2 = (index_j) << 1;
			}
			data_bij = 0;
			data_gij = Gij->SubIteratorGetVal();
			if (index_i == index_j)//See Equation 4-41/b
			{
				setHNRSWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				setHNRSWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}

	}


	for (i = 0; i < pqNbr;i++){
		index_i = pqNodeTable[i].index;
		index_iTimes2 = (pqNodeTable[i].index - pqNodeTable[i].offset) << 1;
		HNJLRS->Add(index_iTimes2, index_iTimes2, bii[index_i]);
		HNJLRS->Add(index_iTimes2, index_iTimes2 + 1, aii[index_i]);
		HNJLRS->Add(index_iTimes2 + 1, index_iTimes2, aii[index_i]);
		HNJLRS->Add(index_iTimes2 + 1, index_iTimes2+1, -bii[index_i]);
	}
	for (i = 0; i < pvNbr; i++){
		index_i = pvNodeTable[i].index;
		index_iTimes2 = (pvNodeTable[i].index - pvNodeTable[i].offset) << 1;
		HNJLRS->Add(index_iTimes2, index_iTimes2, bii[index_i]);
		HNJLRS->Add(index_iTimes2, index_iTimes2 + 1,aii[index_i]);
		HNJLRS->Add(index_iTimes2 + 1, index_iTimes2, 2* f[index_i][0]);
		HNJLRS->Add(index_iTimes2 + 1, index_iTimes2 + 1,2*e[index_i][0]);
	}

	return pf_bool();
}

void	CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::setHNJLWhenEqual(
	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00, X01, X10, X11;

	X00 = -bij*(e[index_i][0]) + gij*(f[index_i][0]) /*+ bii[index_i]*/;
	if (pZeroDetector->isNoneZero(X00))
		HNJLRS->Add(index_iTimes2, index_jTimes2, X00);

	X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]) /*+ aii[index_i]*/;
	if (pZeroDetector->isNoneZero(X01))
		HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);

	X10 = -gij*(e[index_i][0]) - bij*(f[index_i][0]) /*+ aii[index_i]*/;
	if (pZeroDetector->isNoneZero(X10))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2, X10);

	X11 = -bij*(e[index_i][0]) + gij*(f[index_i][0]) /*- bii[index_i]*/;
	if (pZeroDetector->isNoneZero(X11))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2 + 1, X11);
}
void	CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::setHNJLWhenNotEqual(

	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00, X01, X10, X11;

	X00 = (-bij*(e[index_i][0]) + gij*(f[index_i][0]));
	if (pZeroDetector->isNoneZero(X00))
	HNJLRS->Add(index_iTimes2, index_jTimes2, X00);

	X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]);
	if (pZeroDetector->isNoneZero(X01))
	HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);

	X10 = -gij*(e[index_i][0]) - bij*(f[index_i][0]);
	if (pZeroDetector->isNoneZero(X10))
	HNJLRS->Add(index_iTimes2 + 1, index_jTimes2, X10);

	X11 = (-bij*(e[index_i][0]) + gij*(f[index_i][0]));
	if (pZeroDetector->isNoneZero(X11))
	HNJLRS->Add(index_iTimes2 + 1, index_jTimes2 + 1, X11);
}


void	CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::setHNRSWhenEqual(

	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00, X01, X10, X11;

	X00 = -bij*(e[index_i][0]) + gij*(f[index_i][0]) /*+ bii[index_i]*/;
	if (pZeroDetector->isNoneZero(X00))
		HNJLRS->Add(index_iTimes2, index_jTimes2, X00);

	X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]) /*+ aii[index_i]*/;
	if (pZeroDetector->isNoneZero(X01))
		HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);

	X10 =0/* 2 * (f[index_i][0])*/;
	if (pZeroDetector->isNoneZero(X10))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2, X10);

	X11 =0 /*2 * (e[index_i][0])*/;
	if (pZeroDetector->isNoneZero(X11))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2 + 1, (X11));
}
void	CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::setHNRSWhenNotEqual(

	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00 = (-bij*(e[index_i][0]) + gij*(f[index_i][0])), X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]);
	if (pZeroDetector->isNoneZero(X00))
	HNJLRS->Add(index_iTimes2, index_jTimes2, X00);
	if (pZeroDetector->isNoneZero(X01))
	HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);
	//HNJLRS->Add(index_iTimes2 + 1,index_jTimes2,0);
	//HNJLRS->Add(index_iTimes2 + 1,index_jTimes2 + 1,0);

}

pf_bool CMethodNewtonRaphsonHnjlsrBuilder_IterCSR::BuilderInit(pf_uint32 pqNbr, pf_uint32 pvNbr,
	CPfCalcNodePq*	tablePq, CPfCalcNodePv* tablePv,
	pf_uint32	blNo,
	PF_CALC_DATA_TYPE*	aii, PF_CALC_DATA_TYPE*	bii,
	CSMatrix<PF_CALC_DATA_TYPE>*	Bij, CSMatrix<PF_CALC_DATA_TYPE>*	Gij,
	PF_CALC_DATA_TYPE**	e, PF_CALC_DATA_TYPE**	f,
	CSMatrixSP1_3<PF_CALC_DATA_TYPE>*			HNJLRS,
	PF_CALC_DATA_TYPE	precision
	){

	this->aii = aii;
	this->bii = bii;
	this->Bij = Bij;
	this->Gij = Gij;
	this->e = e;
	this->f = f;
	this->HNJLRS = HNJLRS;
	this->pqNbr = pqNbr;
	this->pvNbr = pvNbr;
	this->pqNodeTable = tablePq;
	this->pvNodeTable = tablePv;
	this->blNo = blNo;
	pZeroDetector->SetThreshold(precision);
	return pf_bool();
}
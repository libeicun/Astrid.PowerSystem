#include "MethodNewtonRaphsonHnjlsrBuilder_General.h"


CMethodNewtonRaphsonHnjlsrBuilder_General::CMethodNewtonRaphsonHnjlsrBuilder_General()
{
	pZeroDetector = new CNumericGeneral;
}


CMethodNewtonRaphsonHnjlsrBuilder_General::~CMethodNewtonRaphsonHnjlsrBuilder_General()
{
	delete pZeroDetector;
}
pf_bool CMethodNewtonRaphsonHnjlsrBuilder_General::Build(){
	pf_uint32	i = 0,j = 0;
	pf_uint32	index_i = 0, index_iTimes2 = 0, index_j = 0, index_jTimes2=0;
	PF_CALC_DATA_TYPE	data_bij, data_gij;
	for (i = 0; i < pqNbr; i++)
	{
		index_i = pqNodeTable[i].index;//- pqNodeTable[i].id.offset;
		index_iTimes2 = 2 * (pqNodeTable[i].index - pqNodeTable[i].offset);

		for (j = 0; j < pqNbr; j++)
		{
			index_j = pqNodeTable[j].index;
			index_jTimes2 = 2 * (pqNodeTable[j].index - pqNodeTable[j].offset);
			if (index_i == index_j)//See Equation 4-41/b
			{
				Gij->Get_r(index_i, index_j, data_gij);
				Bij->Get_r(index_i, index_j, data_bij);
				setHNJLWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				Gij->Get_r_Lwr(index_i, index_j, data_gij);
				Bij->Get_r_Lwr(index_i, index_j, data_bij);
				if (!(pZeroDetector->isZero(data_gij) && pZeroDetector->isZero(data_bij)))
					setHNJLWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}

		for (j = 0; j < pvNbr; j++)
		{
			index_j = pvNodeTable[j].index;
			index_jTimes2 = 2 * (pvNodeTable[j].index - pvNodeTable[j].offset);

			if (index_i == index_j)//See Equation 4-41/b
			{
				Gij->Get_r(index_i, index_j, data_gij);
				Bij->Get_r(index_i, index_j, data_bij);
				setHNJLWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				Gij->Get_r_Lwr(index_i, index_j, data_gij);
				Bij->Get_r_Lwr(index_i, index_j, data_bij);
				if (!(pZeroDetector->isZero(data_gij) && pZeroDetector->isZero(data_bij)))
					setHNJLWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}
	}

	for (i = 0; i < pvNbr; i++)
	{

		index_i = pvNodeTable[i].index;//- pvNodeTable[i].id.offset;
		index_iTimes2 = 2 * (pvNodeTable[i].index - pvNodeTable[i].offset);
		for (j = 0; j < pqNbr; j++)
		{
			index_j = pqNodeTable[j].index;//- pvNodeTable[j].id.offset;
			index_jTimes2 = 2 * (pqNodeTable[j].index - pqNodeTable[j].offset);

			if (index_i == index_j)//Use Equation 4-41/b
			{
				Gij->Get_r(index_i, index_j, data_gij);
				Bij->Get_r(index_i, index_j, data_bij);
				setHNRSWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				Gij->Get_r_Lwr(index_i, index_j, data_gij);
				Bij->Get_r_Lwr(index_i, index_j, data_bij);
				if (!(pZeroDetector->isZero(data_gij) &&pZeroDetector-> isZero(data_bij)))
					setHNRSWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}
		for (j = 0; j < pvNbr; j++)
		{
			index_j = pvNodeTable[j].index;//- pvNodeTable[j].id.offset;
			index_jTimes2 = 2 * (pvNodeTable[j].index - pvNodeTable[j].offset);
			if (index_i == index_j)//Use Equation 4-41/b
			{
				Gij->Get_r(index_i, index_j, data_gij);
				Bij->Get_r(index_i, index_j, data_bij);
				setHNRSWhenEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
			else{
				Gij->Get_r_Lwr(index_i, index_j, data_gij);
				Bij->Get_r_Lwr(index_i, index_j, data_bij);
				if (!(pZeroDetector->isZero(data_gij) && pZeroDetector->isZero(data_bij)))
					setHNRSWhenNotEqual(index_iTimes2, index_jTimes2, data_bij, data_gij, index_i);
			}
		}
	}
	return pf_bool();
}

void	CMethodNewtonRaphsonHnjlsrBuilder_General::setHNJLWhenEqual(
	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00, X01, X10, X11;

	X00 = -bij*(e[index_i][0]) + gij*(f[index_i][0]) + bii[index_i];
	if (pZeroDetector->isNoneZero(X00))
		HNJLRS->Add(index_iTimes2, index_jTimes2, X00);

	X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]) + aii[index_i];
	if (pZeroDetector->isNoneZero(X01))
		HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);

	X10 = -gij*(e[index_i][0]) - bij*(f[index_i][0]) + aii[index_i];
	if (pZeroDetector->isNoneZero(X10))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2, X10);

	X11 = (-bij*(e[index_i][0]) + gij*(f[index_i][0]) - bii[index_i]);
	if (pZeroDetector->isNoneZero(X11))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2 + 1, X11);
}
void	CMethodNewtonRaphsonHnjlsrBuilder_General::setHNJLWhenNotEqual(

	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00, X01, X10, X11;

	X00 = (-bij*(e[index_i][0]) + gij*(f[index_i][0]));
	//if (isNoneZero(X00))
	HNJLRS->Add(index_iTimes2, index_jTimes2, X00);

	X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]);
	//if (isNoneZero(X01))
	HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);

	X10 = -gij*(e[index_i][0]) - bij*(f[index_i][0]);
	//if (isNoneZero(X10))
	HNJLRS->Add(index_iTimes2 + 1, index_jTimes2, X10);

	X11 = (-bij*(e[index_i][0]) + gij*(f[index_i][0]));
	//if (isNoneZero(X11))
	HNJLRS->Add(index_iTimes2 + 1, index_jTimes2 + 1, X11);
}


void	CMethodNewtonRaphsonHnjlsrBuilder_General::setHNRSWhenEqual(

	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00, X01, X10, X11;

	X00 = (-bij*(e[index_i][0]) + gij*(f[index_i][0]) + bii[index_i]);
	if (pZeroDetector->isNoneZero(X00))
		HNJLRS->Add(index_iTimes2, index_jTimes2, X00);

	X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]) + aii[index_i];
	if (pZeroDetector->isNoneZero(X01))
		HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);

	X10 = 2 * (f[index_i][0]);
	if (pZeroDetector->isNoneZero(X10))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2, X10);

	X11 = 2 * (e[index_i][0]);
	if (pZeroDetector->isNoneZero(X11))
		HNJLRS->Add(index_iTimes2 + 1, index_jTimes2 + 1, (X11));
}
void	CMethodNewtonRaphsonHnjlsrBuilder_General::setHNRSWhenNotEqual(

	pf_uint32	index_iTimes2,
	pf_uint32	index_jTimes2,
	PF_CALC_DATA_TYPE	bij,
	PF_CALC_DATA_TYPE	gij,
	pf_uint32	index_i

	)
{
	PF_CALC_DATA_TYPE	X00 = (-bij*(e[index_i][0]) + gij*(f[index_i][0])), X01 = gij*(e[index_i][0]) + bij*(f[index_i][0]);
	//if (isNoneZero(X00))
	HNJLRS->Add(index_iTimes2, index_jTimes2, X00);
	//if (isNoneZero(X01))
	HNJLRS->Add(index_iTimes2, index_jTimes2 + 1, X01);
	//HNJLRS->Add(index_iTimes2 + 1,index_jTimes2,0);
	//HNJLRS->Add(index_iTimes2 + 1,index_jTimes2 + 1,0);

}

pf_bool CMethodNewtonRaphsonHnjlsrBuilder_General::BuilderInit(pf_uint32 pqNbr, pf_uint32 pvNbr,
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
	pZeroDetector->SetThreshold(precision);
	return pf_bool();
}
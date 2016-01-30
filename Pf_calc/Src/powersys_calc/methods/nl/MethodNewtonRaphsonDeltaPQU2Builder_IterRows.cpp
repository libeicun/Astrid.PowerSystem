#include "MethodNewtonRaphsonDeltaPQU2Builder_IterRows.h"


CMethodNewtonRaphsonDeltaPQU2Builder_IterRows::CMethodNewtonRaphsonDeltaPQU2Builder_IterRows()
{
}


CMethodNewtonRaphsonDeltaPQU2Builder_IterRows::~CMethodNewtonRaphsonDeltaPQU2Builder_IterRows()
{
}


pf_bool		CMethodNewtonRaphsonDeltaPQU2Builder_IterRows::BuilderInit(
	PF_CALC_DATA_TYPE**	e,
	PF_CALC_DATA_TYPE**	f,
	pf_uint32					pqNbr,
	pf_uint32					pvNbr,
	pf_uint32					blNbr,
	CPfCalcNodePq*		pqNodeTable,
	CPfCalcNodePv*		pvNodeTable,
	CSMatrix<PF_CALC_DATA_TYPE>	*Gij,
	CSMatrix<PF_CALC_DATA_TYPE>	*Bij,

	PF_CALC_DATA_TYPE*			deltaPQPU2,
	ePfNodeClass*							nodeClass
	){
	this->e = e;
	this->f = f;
	this->pqNbr = pqNbr;
	this->pvNbr = pvNbr;
	this->blNbr = blNbr;
	this->pqNodeTable = pqNodeTable;
	this->pvNodeTable = pvNodeTable;
	this->Nbr = pqNbr + pvNbr + blNbr;
	this->Gij = Gij;
	this->Bij = Bij;
	this->deltaPQPU2 = deltaPQPU2;
	return pf_bool();
}


pf_bool		CMethodNewtonRaphsonDeltaPQU2Builder_IterRows::Build(){
	pf_uint32	index_i = 0, index_j = 0;
	pf_uint32	i = 0, j = 0;
	PF_CALC_DATA_TYPE	p, q, u2, data_gij, data_bij;

	for (i = 0; i < pqNbr; i++)
	{
		index_i = pqNodeTable[i].index;
		p = 0;
		q = 0;

		Nbr = Bij->SubIteratorReset(index_i);
		for (j = 0;j<Nbr; j++,Bij->SubIteratorMove())
		{
			index_j = Bij->SubIteratorGetSubIndex();
			data_gij = 0;
			data_bij = Bij->SubIteratorGetVal();
			p += pqNodeTable[i].e*(data_gij*(*(e[index_j])) - data_bij*(*(f[index_j]))) + pqNodeTable[i].f*(data_gij*(*(f[index_j])) + data_bij*(*(e[index_j])));
			q += pqNodeTable[i].f*(data_gij*(*(e[index_j])) - data_bij*(*(f[index_j]))) - pqNodeTable[i].e*(data_gij*(*(f[index_j])) + data_bij*(*(e[index_j])));
			
		}

		Nbr = Gij->SubIteratorReset(index_i);
		for (j = 0; j < Nbr;j++,Gij->SubIteratorMove())
		{
			index_j = Gij->SubIteratorGetSubIndex();
			data_gij = Gij->SubIteratorGetVal();
			data_bij = 0;
			p += pqNodeTable[i].e*(data_gij*(*(e[index_j])) - data_bij*(*(f[index_j]))) + pqNodeTable[i].f*(data_gij*(*(f[index_j])) + data_bij*(*(e[index_j])));
			q += pqNodeTable[i].f*(data_gij*(*(e[index_j])) - data_bij*(*(f[index_j]))) - pqNodeTable[i].e*(data_gij*(*(f[index_j])) + data_bij*(*(e[index_j])));

		}

		index_i = pqNodeTable[i].index - pqNodeTable[i].offset;
		deltaPQPU2[2 * index_i] = pqNodeTable[i].P - p;
		deltaPQPU2[2 * index_i + 1] = pqNodeTable[i].Q - q;
	}

	/*Done.*/
	/*Update the deltaP and deltaU2 of equation 4-37 from the pvNodeTable[], use equation 4-38/c.*/
	PF_CALC_DATA_TYPE	ei, ej, fj, fi;
	for (i = 0; i < pvNbr; i++)
	{
		p = 0;
		index_i = pvNodeTable[i].index;


		Nbr = Bij->SubIteratorReset(index_i);
		for (j = 0; j < Nbr; j++, Bij->SubIteratorMove())
		{
			index_j = Bij->SubIteratorGetSubIndex();
			data_gij = 0;
			data_bij = Bij->SubIteratorGetVal();
			ei = pvNodeTable[i].e;
			fi = pvNodeTable[i].f;
			ej = ((e[index_j][0]));
			fj = ((f[index_j][0]));
			//if (!(isZero(data_gij) && isZero(data_bij)))
			{
				p += ei*(data_gij*ej - data_bij*fj) + fi*(data_gij*fj + data_bij*ej);
			}
		}

		Nbr = Gij->SubIteratorReset(index_i);
		for (j = 0; j < Nbr; j++, Gij->SubIteratorMove())
		{
			index_j = Gij->SubIteratorGetSubIndex();
			data_gij = Gij->SubIteratorGetVal();
			data_bij = 0;
			ei = pvNodeTable[i].e;
			fi = pvNodeTable[i].f;
			ej = ((e[index_j][0]));
			fj = ((f[index_j][0]));
			//if (!(isZero(data_gij) && isZero(data_bij)))
			{
				p += ei*(data_gij*ej - data_bij*fj) + fi*(data_gij*fj + data_bij*ej);
			}
		}


		u2 = pvNodeTable[i].e* pvNodeTable[i].e + pvNodeTable[i].f* pvNodeTable[i].f;
		index_i = pvNodeTable[i].index - pvNodeTable[i].offset;
		deltaPQPU2[2 * index_i] = pvNodeTable[i].P - p;
		deltaPQPU2[2 * index_i + 1] = pvNodeTable[i].U2* pvNodeTable[i].U2 - u2;
	}
	return pf_bool();
}

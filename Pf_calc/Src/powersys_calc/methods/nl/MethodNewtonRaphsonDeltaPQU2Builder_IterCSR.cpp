#include "MethodNewtonRaphsonDeltaPQU2Builder_IterCSR.h"


CMethodNewtonRaphsonDeltaPQU2Builder_IterCSR::CMethodNewtonRaphsonDeltaPQU2Builder_IterCSR()
{
}


CMethodNewtonRaphsonDeltaPQU2Builder_IterCSR::~CMethodNewtonRaphsonDeltaPQU2Builder_IterCSR()
{
}


pf_bool		CMethodNewtonRaphsonDeltaPQU2Builder_IterCSR::BuilderInit(
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
	this->nodeClass = nodeClass;
	return pf_bool();
}


pf_bool		CMethodNewtonRaphsonDeltaPQU2Builder_IterCSR::Build(){
	S_MATRIX_NODE	MatNode;
	pf_uint32	MatNode_i, MatNode_j; 
	PF_CALC_DATA_TYPE MatNode_Val;

	PF_CALC_DATA_TYPE	p, q, u2, data_gij, data_bij;

	pf_uint32	NoneZeroNbrOfBij = Bij->GetNoneZeroNbr();
	pf_uint32	NoneZeroNbrOfGij = Gij->GetNoneZeroNbr();
	pf_uint32	i, j;
	pf_uint32	index_i = 0, index_j = 0;
	pf_uint32	PqvNbrMulti2 = 2 * (pqNbr + pvNbr);
	PF_CALC_DATA_TYPE*		SumPQU2_RelatingGij = new PF_CALC_DATA_TYPE[PqvNbrMulti2];
	PF_CALC_DATA_TYPE*		SumPQU2_RelatingBij = new PF_CALC_DATA_TYPE[PqvNbrMulti2];
	
	for (i = 0; i < PqvNbrMulti2;i++){
		SumPQU2_RelatingGij[i] = 0;
		SumPQU2_RelatingGij[i] = 0;
	}

	for (Gij->IteratorReset(),i = 0; i < NoneZeroNbrOfGij; i++, Gij->IteratorMove()){
		MatNode = Gij->IteratorGetNode();
		MatNode_i = MatNode.i;
		MatNode_j = MatNode.j;
		MatNode_Val = MatNode.Val;

		switch (nodeClass[MatNode_i])
		{
		case ePfNodeClassPQ:{
			//index_i = pqNodeTable[i].index;
			SumPQU2_RelatingGij[i<<1] += MatNode_Val*(e[MatNode_i][0] * e[MatNode_j][0] + f[MatNode_i][0] * f[MatNode_j][0]);//P
			SumPQU2_RelatingGij[i << 1+1] += MatNode_Val*(f[MatNode_i][0] * e[MatNode_j][0] - e[MatNode_i][0] * f[MatNode_j][0]);//Q
			break;
		}
		case ePfNodeClassPV:{
			SumPQU2_RelatingGij[i << 1] += MatNode_Val*(e[MatNode_i][0] * e[MatNode_j][0] + f[MatNode_i][0] * f[MatNode_j][0]);//P
			break;
		}
		default:
			break;
		}
	}

	for (Bij->IteratorReset(), i = 0; i < NoneZeroNbrOfBij; i++, Bij->IteratorMove()){
		MatNode = Bij->IteratorGetNode();
		MatNode_i = MatNode.i;
		MatNode_j = MatNode.j;
		MatNode_Val = MatNode.Val;
		switch (nodeClass[MatNode_i])
		{
		case ePfNodeClassPQ:{
			SumPQU2_RelatingBij[i << 1] += MatNode_Val*(f[MatNode_i][0] * e[MatNode_j][0] - e[MatNode_i][0] * f[MatNode_j][0]);//P
			SumPQU2_RelatingGij[i << 1 + 1] += (-MatNode_Val)*(f[MatNode_i][0] * f[MatNode_j][0] + e[MatNode_i][0] * e[MatNode_j][0]);//Q
			break;
		}
		case ePfNodeClassPV:{
			SumPQU2_RelatingBij[i << 1] += MatNode_Val*(f[MatNode_i][0] * e[MatNode_j][0] - e[MatNode_i][0] * f[MatNode_j][0]);//P
			break;
		}
		default:
			break;
		}
	}
	for (i = 0; i < pvNbr;i++){
		index_i = pqNodeTable[i].index;
		deltaPQPU2[2 * index_i + 1] = pvNodeTable[i].U2* pvNodeTable[i].U2 - u2;
	}




	

	for (i = 0; i < pqNbr; i++)
	{
		index_i = pqNodeTable[i].index;
		p = 0;
		q = 0;
		for (j = 0; j < Nbr; j++)
		{
			index_j = j;
			Gij->Get_r_Lwr(index_i, index_j, data_gij);
			Bij->Get_r_Lwr(index_i, index_j, data_bij);
			//if (!(isZero(data_gij) && isZero(data_bij)))
			{
				p += pqNodeTable[i].e*(data_gij*(*(e[index_j])) - data_bij*(*(f[index_j]))) + pqNodeTable[i].f*(data_gij*(*(f[index_j])) + data_bij*(*(e[index_j])));
				q += pqNodeTable[i].f*(data_gij*(*(e[index_j])) - data_bij*(*(f[index_j]))) - pqNodeTable[i].e*(data_gij*(*(f[index_j])) + data_bij*(*(e[index_j])));
			}

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
		for (j = 0; j < Nbr; j++)
		{
			index_j = j;
			Gij->Get_r_Lwr(index_i, index_j, data_gij);
			Bij->Get_r_Lwr(index_i, index_j, data_bij);
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

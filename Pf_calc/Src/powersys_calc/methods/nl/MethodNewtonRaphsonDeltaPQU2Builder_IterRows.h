#pragma once
#include "MethodNewtonRaphsonDeltaPQU2Builder.h"
class CMethodNewtonRaphsonDeltaPQU2Builder_IterRows :
	public CMethodNewtonRaphsonDeltaPQU2Builder
{
private:

	PF_CALC_DATA_TYPE**	e;
	PF_CALC_DATA_TYPE**	f;
	pf_uint32					pqNbr;
	pf_uint32					pvNbr;
	pf_uint32					blNbr;
	pf_uint32					Nbr;
	CPfCalcNodePq*		pqNodeTable;
	CPfCalcNodePv*		pvNodeTable;
	CSMatrix<PF_CALC_DATA_TYPE>	*Gij;
	CSMatrix<PF_CALC_DATA_TYPE>	*Bij;
	PF_CALC_DATA_TYPE*			deltaPQPU2;


public:
	pf_bool		BuilderInit(
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
		);
	pf_bool		Build();

public:
	CMethodNewtonRaphsonDeltaPQU2Builder_IterRows();
	~CMethodNewtonRaphsonDeltaPQU2Builder_IterRows();
};


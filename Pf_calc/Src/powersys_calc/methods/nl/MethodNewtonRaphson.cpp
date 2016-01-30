#include "MethodNewtonRaphson.h"
#include <math.h>
#include "PfCalcNode.h"
#include "DataIOTool.h"
#include <stdio.h>
#include "SMatrixCSR.h"
#include "timing.h"
#include "PowerFlowCalcObjSelectorIeee.h"
#include "MethodNewtonRaphsonAiiBiiBuilder_General.h"
#include "MethodNewtonRaphsonAiiBiiBuilder_IterCSR.h"
#include "MethodNewtonRaphsonHnjlsrBuilder_General.h"
#include "MethodNewtonRaphsonHnjlsrBuilder_IterCSR.h"
#include "MethodNewtonRaphsonDeltaPQU2Builder_General.h"
#include "MethodNewtonRaphsonDeltaPQU2Builder_IterCSR.h"
#include "MethodNewtonRaphsonDeltaPQU2Builder_IterRows.h"


CMethodNewtonRaphson::CMethodNewtonRaphson()
{

	ObjFactory = new CPowerFlowCalcObjSelectorIeee();

	DataReader = ObjFactory->SelectDFR();

	pAiiBiiBuilder = new CMethodNewtonRaphsonAiiBiiBuilder_IterCSR;
	pDeltaPQU2Builder = new CMethodNewtonRaphsonDeltaPQU2Builder_IterRows;
	pHnjlsrBuilder = new CMethodNewtonRaphsonHnjlsrBuilder_IterCSR;

	pZeroDetecter = new CNumericGeneral;



	DataReader->ReadDataFile("F:/Resource/IEEE1047.dat");

	DataReader->GetBlNodeNbr(blNodeNbr);
	DataReader->GetPqNodeNbr(pqNodeNbr);
	DataReader->GetPvNodeNbr(pvNodeNbr);


	/*set the .blNodeTabl[], pqNodeTable[], pvNodeTable[] fields to zero.*/
	this->blNodeTable = (CPfCalcNodeBl*)malloc(sizeof(CPfCalcNodeBl)*(blNodeNbr));
	CPfCalcNodeBl blNode;
	blNode.e = 0; blNode.f = 0; blNode.index = 0; blNode.Pg = 0; blNode.Pl = 0; blNode.Qg = 0; blNode.Ql = 0;
	for (int i = 0; i<blNodeNbr; i++)
	{
		this->blNodeTable[i] = blNode;
	}

	pf_uint32 pqvNbr = pqNodeNbr + pvNodeNbr;
	pf_uint32 nbr = pqvNbr + blNodeNbr;
	pf_uint32 pqvNbrTimes2 = pqvNbr * 2;

	curIterTime = 0;
	dataCheckFlag = 0;
	DataReader->GetMaxIterTimes(maxIterTimes);
	DataReader->GetPresion(precision);

	/*allocate all the fields which needs dynamic memory of *pfcb.*/
	this->Bij = new CSMatrixCSR<PF_CALC_DATA_TYPE>(nbr, nbr);
	this->Gij = new CSMatrixCSR<PF_CALC_DATA_TYPE>(nbr, nbr);
	this->deltaEF = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*(pqvNbrTimes2));
	this->deltaPQPU2 = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*(pqvNbrTimes2));
	this->nodeClass = (ePfNodeClass*)malloc(sizeof(ePfNodeClass)*(pqvNbrTimes2));
	//this->HNJLRS = new CSMatrixSP1_3<PF_CALC_DATA_TYPE>(1, 1);

	this->pqNodeTable = (CPfCalcNodePq*)malloc(sizeof(CPfCalcNodePq)*(pqNodeNbr));
	this->pvNodeTable = (CPfCalcNodePv*)malloc(sizeof(CPfCalcNodePv)*(pvNodeNbr));
	this->e = (PF_CALC_DATA_TYPE**)malloc(sizeof(PF_CALC_DATA_TYPE*)*(nbr));
	//pf_uint32	size=sizeof(this->e)/sizeof(PF_CALC_DATA_TYPE*);
	this->f = (PF_CALC_DATA_TYPE**)malloc(sizeof(PF_CALC_DATA_TYPE*)*(nbr));
	this->aii = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*(nbr));
	this->bii = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*(nbr));
	/*	set the .deltaEF[], .deltaPQPU2[], .HNJLRS->Add(][] fields to zero.
	if don't clear these field before use them, problems will occur.*/
	for (int i = 0; i<pqvNbrTimes2; i++)
	{
		this->deltaEF[i] = PF_CALC_DATA_INIT_VAL_SPEC;
		this->deltaPQPU2[i] = PF_CALC_DATA_INIT_VAL_SPEC;

	}
	for (int i = 0; i<nbr; i++)
	{
		this->aii[i] = PF_CALC_DATA_INIT_VAL_SPEC;
		this->bii[i] = PF_CALC_DATA_INIT_VAL_SPEC;
		this->e[i] = NULL;
		this->f[i] = NULL;
	}
	/*set the .Bij[][], .Gij[][] fields to zero.*/
	/*for (int i=0;i<nbr;i++)
	{
	for (int j=0;j<nbr;j++)
	{
	Set(this->Bij,0,i,j);
	Set(this->Gij,0,i,j);
	}
	}*/

	/*set the .blNodeTabl[], pqNodeTable[], pvNodeTable[] fields to zero.*/
	CPfCalcNodePq pqNode;
	pqNode.e = 0; pqNode.f = 0; pqNode.index = 0; pqNode.offset = 0; pqNode.P = 0; pqNode.Q = 0; pqNode.offset2 = 0;
	for (int i = 0; i<pqNodeNbr; i++)
	{
		this->pqNodeTable[i] = pqNode;
	}
	CPfCalcNodePv pvNode;
	pvNode.e = 0; pvNode.f = 0; pvNode.index = 0; pvNode.offset = 0; pvNode.P = 0; pvNode.Qg = 0; pvNode.Ql = 0; pvNode.U2 = 0;

	for (int i = 0; i<pvNodeNbr; i++)
	{
		this->pvNodeTable[i] = pvNode;
	}



	/*	102318
	Done.*/


	DataReader->GetMatY(Gij, Bij);
	DataReader->GetNodeTables(blNodeTable, pqNodeTable, pvNodeTable);



	/*	102318
	Build the links between .e[], .f[] and .pqNodeTable[].e, .pvNodeTable[].f*/

	for (pf_uint32 i = 0; i<blNodeNbr; i++)
	{
		this->e[this->blNodeTable[i].index] = &(this->blNodeTable[i].e);
		this->f[this->blNodeTable[i].index] = &(this->blNodeTable[i].f);
	}
	for (pf_uint32 i = 0; i<pqNodeNbr; i++)
	{
		this->e[this->pqNodeTable[i].index] = &(this->pqNodeTable[i].e);
		this->f[this->pqNodeTable[i].index] = &(this->pqNodeTable[i].f);
	}
	for (pf_uint32 i = 0; i<pvNodeNbr; i++)
	{
		this->e[this->pvNodeTable[i].index] = &(this->pvNodeTable[i].e);
		this->f[this->pvNodeTable[i].index] = &(this->pvNodeTable[i].f);
	}

	FILE*		fp = fopen("checkef.txt", "wb");
	for (pf_uint32 i = 0; i<nbr; i++)
	{
		if (this->e[i] == NULL)
		{
			fprintf(fp, "e[%d] is NULL!\n", i);
			printf("e[%d] is NULL!\n", i);
		}
		if (this->f[i] == NULL)
		{
			fprintf(fp, "f[%d] is NULL!\n", i);
			printf("f[%d] is NULL!\n", i);
		}
	}
	fclose(fp);


	pAiiBiiBuilder->BuilderInit(pqNodeNbr, pvNodeNbr, blNodeNbr, pqNodeTable, pvNodeTable, blNodeTable, aii, bii, Bij, Gij, e, f);
	pDeltaPQU2Builder->BuilderInit(e, f, pqNodeNbr, pvNodeNbr, blNodeNbr, pqNodeTable, pvNodeTable, Gij, Bij, deltaPQPU2,nodeClass);
	
	pZeroDetecter->SetThreshold(precision);

	CDataIOTool								dio;
	//dio.SetMethodObjPtr(&nl_iter);

	//dio.DataWriteFile(this, "test_data_output.txt");

	CPfCalcNodePq	npq;
	CPfCalcNodePv	npv;
	CPfCalcNodeBl nbl;
	pf_uint32	index;
	for (pf_uint32 i = 0; i < pqNodeNbr; i++){
		npq = pqNodeTable[i];
		index = 2 * (npq.index - npq.offset);
		nodeClass[index] = ePfNodeClassPQ;
		nodeClass[index+1] = ePfNodeClassPQ;
	}	
	for (pf_uint32 i = 0; i < pvNodeNbr; i++){
		npv = pvNodeTable[i];
		index = 2 * (npv.index - npv.offset);
		nodeClass[index] = ePfNodeClassPV;
		nodeClass[index+1] = ePfNodeClassPV;
	}

	fp = fopen("Y.dat", "wb");

	fprintf(fp, "Y = [\n");
	for (size_t i = 0; i < nbr; i++)
	{
		for (size_t j = 0; j < nbr; j++) {
			fprintf(fp, "%4.4f+%4.4fi ", Gij->Get(i,j), Bij->Get(i,j));
			//printf( "%4.4f+%4.4fi ", Gij->Get(i, j), Bij->Get(i, j));
		}
		fprintf(fp, ";\n");
	}
	fprintf(fp, "];\n");

	
	double* S_P = new double[nbr];
	double* S_Q = new double[nbr];

	for (pf_uint32 i = 0; i < pqNodeNbr; i++) {
		npq = pqNodeTable[i];
		S_P[npq.index] = npq.P;
		S_Q[npq.index] = npq.Q;
	}
	for (pf_uint32 i = 0; i < pvNodeNbr; i++) {
		npv = pvNodeTable[i];
		S_P[npv.index] = npv.P;
		S_Q[npv.index] = npv.U2*npv.U2;
	}

	for (pf_uint32 i = 0; i < blNodeNbr; i++) {
		nbl = blNodeTable[i];
		S_P[nbl.index] = 0;
		S_Q[nbl.index] = 0;
	}
	
	fprintf(fp, "P = [\n");
	for (size_t i = 0; i < nbr; i++)
	{
		fprintf(fp, "%4.4f;\n", S_P[i]);
	}
	fprintf(fp, "];\n");
	fprintf(fp, "Q = [\n");
	for (size_t i = 0; i < nbr; i++)
	{
		fprintf(fp, "%4.4f;\n", S_Q[i]);
	}
	fprintf(fp, "];\n");



	fprintf(fp, "PQNodes = [\n");
	for (pf_uint32 i = 0; i < pqNodeNbr; i++) {
		npq = pqNodeTable[i];
		fprintf(fp, "%d;\n", npq.index+1);
	}
	fprintf(fp, "];\n");
	fprintf(fp, "PVNodes = [\n");
	for (pf_uint32 i = 0; i < pvNodeNbr; i++) {
		npv = pvNodeTable[i];
		fprintf(fp, "%d;\n", npv.index+1);
	}
	fprintf(fp, "];\n");
	fprintf(fp, "U = [\n");
	for (pf_uint32 i = 0; i < pvNodeNbr; i++) {
		npv = pvNodeTable[i];
		fprintf(fp, "%4.4f;\n", npv.U2);
	}
	fprintf(fp, "];\n");
	fprintf(fp, "BLNodes = [\n");
	for (pf_uint32 i = 0; i < blNodeNbr; i++) {
		nbl = blNodeTable[i];
		fprintf(fp, "%d;\n", nbl.index+1);
	}
	fprintf(fp, "];\n");


	fclose(fp);
	

}


CMethodNewtonRaphson::~CMethodNewtonRaphson()
{
	//delete this->HNJLRS;
	delete this->Gij;
	delete this->Bij;
	delete	pHnjlsrBuilder;
	delete	pAiiBiiBuilder;
	delete pDeltaPQU2Builder;
}


ePfCalcMethodErr CMethodNewtonRaphson::Iterate()
{
	pf_uint8	converge = 0;
	pf_char	ok[10];
	ePfCalcMethodErr	err;
	//CMatrixCalculator	calc;
	do
	{
		if (curIterTime >= maxIterTimes)
		{
			err = ePfCalcMethodFailToConverge;
			printf("The power flow cannot converge in %d iters.\n", maxIterTimes);
			break;
		}


		this->HNJLRS = new CSMatrixSP1_3<PF_CALC_DATA_TYPE>(1, 1);



		pHnjlsrBuilder->BuilderInit(pqNodeNbr, pvNodeNbr, pqNodeTable, pvNodeTable, blNodeTable[0].index, aii, bii, Bij, Gij, e, f, HNJLRS, precision);
		NewtonRaphsonIterOnetime();
		//CDataIOTool::PfMatrixDataAppendFile("J.dat", HNJLRS, "Jacobi", (pqNodeNbr + pvNodeNbr) * 2, (pqNodeNbr + pvNodeNbr) * 2, " ", ";\n");



		//calc.SetMethod(ePfSolveAeBxMethodLU);
		HNJLRS->Solve(deltaPQPU2, deltaEF, (pqNodeNbr + pvNodeNbr) * 2);
		HNJLRS->OrderAndFactorOff();
		delete this->HNJLRS;

		CDataIOTool	 dio;
		dio.ResultOutput(this, "result_output.txt");

		UpdateEifiFromDeltaEifi();
		converge = isConverge();
		if (converge)
		{
			err = ePfCalcMethodOK;
			printf("The power flow converge after %d iters.\n", curIterTime);
			break;
		}
	} while (1)
		;

	return err;
}

pf_int32 CMethodNewtonRaphson::NewtonRaphsonIterOnetime()
{
	curIterTime++;
	pf_uint32 maxIter, blNbr = blNodeNbr, pqNbr = pqNodeNbr, pvNbr = pvNodeNbr, Nbr = pqNbr + pvNbr + blNodeNbr;
	pf_uint32 pqvNbr = pqNbr + pvNbr;
	pf_uint32	pqvNbrTimes2 = 2 * pqvNbr;
	pf_uint32	pqNbrTimes2 = 2 * pqNbr;
	pf_uint32 i = 0, index = 0, j = 0, index_i, index_j;
	PF_CALC_DATA_TYPE data_gij, data_bij;
	PF_CALC_DATA_TYPE	p = 0, q = 0, u2 = 0;

	/*Update the deltaP and deltaQ of equation 4-37 from the pqNodeTable[], use equation 4-38.*/
	CTiming::TimeLable("Enter deltaPQPU2");
	pDeltaPQU2Builder->Build();
	CTiming::TimeLable("Exit deltaPQPU2");

	/*Done.*/
	//FOR TEST
#if 0
	DEBUG_1DARRAY_DEF(pf_f64, dbg_pqpu2, 8);
	DEBUG_1DARRAY_CLR(dbg_pqpu2, 8);
	DEBUG_1DARRAY_COPY(dbg_pqpu2, deltaPQPU2, 8);
#endif
	//FOR TEST

	/*	100012
	Update the .aii[] and .bii[] of Equation 4-41/b, use Equation 4-41/a.*/
	/*for( i=0;i<pqNbr;i++)
	{
	pf_f64 d;
	d= pqNodeTable[i].e* pqNodeTable[i].e+ pqNodeTable[i].f* pqNodeTable[i].f;
	index= pqNodeTable[i].id.index- pqNodeTable[i].id.offset2;
	aii[index]=( pqNodeTable[i].P* pqNodeTable[i].e+ pqNodeTable[i].Q* pqNodeTable[i].f)/d;
	bii[index]=( pqNodeTable[i].P* pqNodeTable[i].f- pqNodeTable[i].Q* pqNodeTable[i].e)/d;
	}*/
	CTiming::TimeLable("Enter Aii[] Bii[]");
	pAiiBiiBuilder->Build();
	CTiming::TimeLable("Exit  Aii[] Bii[]");
	/*	Done.
	100012*/

	/*	100017
	Update the .HNJLRS->Add(][] field, see Equation 4-41/a and 4-41/b. Because we will put only the PQ and PV data(exclude BL) in the Jacob Matrix
	and .deltaPQPU2[] and .deltaEF[], we use .id.index and .id.offset to ReCalc the actual index.*/
	//Update the part of PQ Node's.
	pf_uint32	index_iTimes2 = 0, index_jTimes2 = 0;
	pf_uint32	index_i2 = 0, index_j2 = 0;
	CTiming::TimeLable("Enter HNJLRS");
	pHnjlsrBuilder->Build();

	CTiming::TimeLable("Exit HNJLRS");
	/*	Done
	100017.*/
#if 0
	printf("\n");
	printf("\n");
	FILE* fpH = fopen("H.dat", "wb");
	FILE* fpN = fopen("N.dat", "wb");
	FILE* fpJ = fopen("J.dat", "wb");
	FILE* fpL = fopen("L.dat", "wb");
	for (i = 0; i < pqvNbr; i++)
	{
		for (j = 0; j < pqvNbr; j++)
		{
			//printf("%4.4f ", this->HNJLRS->Get(2 * i, 2 * j));
			//printf("%4.4f ", this->HNJLRS->Get(2 * i, 2 * j+1));
			//printf("%4.4f ", this->HNJLRS->Get(2 * i+1, 2 * j));
			//printf("%4.4f ", this->HNJLRS->Get(2 * i+1, 2 * j+1));
			fprintf(fpH,"%4.4f ", this->HNJLRS->Get(2 * i, 2 * j));
			fprintf(fpN,"%4.4f ", this->HNJLRS->Get(2 * i, 2 * j+1));
			fprintf(fpJ,"%4.4f ", this->HNJLRS->Get(2 * i+1, 2 * j));
			fprintf(fpL,"%4.4f ", this->HNJLRS->Get(2 * i+1, 2 * j+1));
		}
		fprintf(fpH, "\n");
		fprintf(fpN, "\n");
		fprintf(fpJ, "\n");
		fprintf(fpL, "\n");
	}
	printf("\n");
	fclose(fpH);
	fclose(fpN);
	fclose(fpJ);
	fclose(fpL);
#endif

#if 1
	printf("e+fi\n");
	printf("\n");
	for (i = 0; i < Nbr; i++)
	{
		printf("%4.4f+%4.4fi ", this->e[i], this->f[i]);

		printf("\n");
	}
	printf("\n");
	printf("\n");
#endif

#if 0
	printf("\n");
	printf("\n");
	for (i = 0; i < Nbr; i++)
	{
		printf("%4.4f+%4.4fi ", this->aii[i],this->bii[i]);

		printf("\n");
	}
	printf("\n");
	printf("\n");
#endif
#if 0
	printf("\n");
	printf("\n");
	for (i = 0; i < pqvNbr*2; i++)
	{
		for (j = 0; j < pqvNbr*2; j++)
		{
			printf("%4.4f ", this->HNJLRS->Get(i, j));
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
#endif
	return 0;
}

int CMethodNewtonRaphson::UpdateEifiFromDeltaEifi()
{

	int pqvNbr = (pqNodeNbr + pvNodeNbr);
	int Nbr = (pqNodeNbr + pvNodeNbr + blNodeNbr);
	int pqNbr = pqNodeNbr;
	int pvNbr = pvNodeNbr;

	pf_uint32	index_i, index_i_with_offset;
	for (unsigned int i = 0; i<pqNbr; i++)
	{
		index_i = pqNodeTable[i].index;
		index_i_with_offset = pqNodeTable[i].index - pqNodeTable[i].offset;

		*(e[index_i]) += deltaEF[index_i_with_offset * 2 + 1];
		*(f[index_i]) += deltaEF[index_i_with_offset * 2];
	}
	for (unsigned int i = 0; i<pvNbr; i++)
	{
		index_i = pvNodeTable[i].index;
		index_i_with_offset = pvNodeTable[i].index - pvNodeTable[i].offset;

		*(e[index_i]) += deltaEF[index_i_with_offset * 2 + 1];
		*(f[index_i]) += deltaEF[index_i_with_offset * 2];
	}
	return 0;
}

pf_bool CMethodNewtonRaphson::isConverge()
{

	int nbr = (pqNodeNbr + pvNodeNbr) * 2;
	for (int i = 0; i < nbr; i++)
		if (abs(deltaPQPU2[i]) >  precision)
			return 0;
	return 1;

}





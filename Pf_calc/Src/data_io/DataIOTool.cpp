#include "DataIOTool.h"
#include <stdio.h>

CDataIOTool::CDataIOTool(CMethodSolvePowerSysNlEquations&	pMethod)
{
	pMethodObj = NULL;
}
CDataIOTool::CDataIOTool()
{
	pMethodObj = NULL;
}

CDataIOTool::~CDataIOTool()
{

}
void	CDataIOTool::SetMethodObjPtr(CMethodSolvePowerSysNlEquations*	pMethod)
{
	pMethodObj = pMethod;
}
void	CDataIOTool::DataReadFile(pf_char* fileName, ePfDataStructType datatructType)
{

}
int		CDataIOTool::DataCheck(ePfDataStructType datatructType)
{
	switch (datatructType)
	{
	case ePfDataStructTypeLBCTest:{
		
		//if (pMethodObj->dataCheckFlag == 127)
		if (0)
			return 1;
		else
			return 0;
		break; }
	default:{break; }
	}
}
void	CDataIOTool::DataWriteFile(CMethodNewtonRaphson*	pfcb, pf_char* fileName)
{
	FILE*		fp;
	char		sf[10];
	int i, j, nbr, pqvnbr;
	PF_CALC_DATA_TYPE	data;
	nbr = pfcb->blNodeNbr + pfcb->pqNodeNbr + pfcb->pvNodeNbr;
	pqvnbr = nbr - pfcb->blNodeNbr;
	fp = fopen(fileName, "wb");
	if (fp == NULL)
		return;
	fprintf(fp, "%s", "Test	Data	Output\n\n\n\n\n");


	fprintf(fp, "Header\n");
	fprintf(fp, "%d %d %d %6.4f, %d\n", pfcb->blNodeNbr, pfcb->pvNodeNbr, pfcb->pqNodeNbr, pfcb->precision, pfcb->maxIterTimes);


	fprintf(fp, "\nBl Nodes\n");
	fprintf(fp, "e  	f	  index	  Pg  	Pl	  	Qg  	Ql\n");
	for (pf_uint32 i = 0; i < pfcb->blNodeNbr; i++)
	{
		fprintf(fp, "%6.4f ,%6.4f ,%d ,%6.4f ,%6.4f ,%6.4f ,%6.4f\n",
			pfcb->blNodeTable[i].e, pfcb->blNodeTable[i].f,
			pfcb->blNodeTable[i].index,
			pfcb->blNodeTable[i].Pg, pfcb->blNodeTable[i].Pl, pfcb->blNodeTable[i].Qg, pfcb->blNodeTable[i].Ql);
	}
	fprintf(fp, "\nPq Nodes\n");
	fprintf(fp, "e	  f  	index  	offset  	  offset2	  P	Q\n");
	for (pf_uint32 i = 0; i < pfcb->pqNodeNbr; i++)
	{
		fprintf(fp, "%6.4f ,%6.4f ,%d ,%d ,%d ,%6.4f ,%6.4f\n",
			pfcb->pqNodeTable[i].e, pfcb->pqNodeTable[i].f,
			pfcb->pqNodeTable[i].index, pfcb->pqNodeTable[i].offset, pfcb->pqNodeTable[i].offset2,
			pfcb->pqNodeTable[i].P, pfcb->pqNodeTable[i].Q);
	}

	fprintf(fp, "\nPv Nodes\n");
	fprintf(fp, "e  	f	  index	  offset	    P	  Qg  	Ql		U2\n");
	for (pf_uint32 i = 0; i < pfcb->pvNodeNbr; i++)
	{
		fprintf(fp, "%6.4f ,%6.4f ,%d ,%d ,%6.4f ,%6.4f ,%6.4f ,%6.4f\n",
			pfcb->pvNodeTable[i].e, pfcb->pvNodeTable[i].f,
			pfcb->pvNodeTable[i].index, pfcb->pvNodeTable[i].offset,
			pfcb->pvNodeTable[i].P, pfcb->pvNodeTable[i].Qg, pfcb->pvNodeTable[i].Ql, pfcb->pvNodeTable[i].U2);
	}

	fprintf(fp, "%s", "G\n");
	for (i = 0; i < nbr; i++)
	{
		for (j = 0; j < nbr; j++)
		{
			pfcb->Gij->Get_r(i, j, data);
			fprintf(fp, "%lf ", data);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	fprintf(fp, "%s", "B\n");
	for (i = 0; i < nbr; i++)
	{
		for (j = 0; j < nbr; j++)
		{
			pfcb->Bij->Get_r( i, j, data);
			fprintf(fp, "%lf ", data);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	fprintf(fp, "%s", "\ne[]\n");
	for (pf_uint32 n = 0; n < nbr; n++)
	{
		if (pfcb->e[n] != NULL)
		{
			fprintf(fp, "%6.4f, ", pfcb->e[n][0]);
		}
		else
		{
			fprintf(fp, "\nPtr==NULL!\n");
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, "%s", "\nf[]\n");
	for (pf_uint32 m = 0; m < nbr; m++)
	{
		if (pfcb->f[m] != NULL)
		{
			fprintf(fp, "%6.4f, ", pfcb->f[m][0]);
		}
		else
		{
			fprintf(fp, "\nPtr==NULL!\n");
		}

	}
	fprintf(fp, "\n");

	fclose(fp);
}
void	CDataIOTool::ResultOutput(CMethodNewtonRaphson*	pfcb, pf_char* fileName)
{
	FILE*		fp;
	char		sf[10];
	int i, j, nbr;
	PF_CALC_DATA_TYPE	data;

	nbr = pfcb->blNodeNbr + pfcb->pqNodeNbr + pfcb->pvNodeNbr;
	int pqvNbr = pfcb->pqNodeNbr + pfcb->pvNodeNbr;

	PfStringDataAppendFile(fileName, "Once Iterate Data Output");
	//Pf1DArrayDataAppendFile(fileName, pfcb->deltaPQPU2, "deltaPQPU2", pqvNbr * 2, " ");
	
	fp = fopen("result_output.txt", "a");
	fprintf(fp, "DELTA");
	fprintf(fp, "\n");
	for (pf_uint32 i = 0; i < pqvNbr; i++)
	{
		fprintf(fp, "%8.5f\n", pfcb->deltaPQPU2[i * 2]);
	}
	for (pf_uint32 i = 0; i < pqvNbr; i++)
	{
		fprintf(fp, "%8.5f\n", pfcb->deltaPQPU2[i * 2 + 1]);
	}

	fprintf(fp, "\n");

	fclose(fp);


	//PfMatrixDataAppendFile(fileName,pfcb->HNJLRS,"HNJLRS",pqvNbr*2,pqvNbr*2," ",";");
	Pf1DArrayDataAppendFile(fileName, pfcb->deltaEF, "deltaEF", pqvNbr * 2, " ");

	fp = fopen(fileName, "a");
	if (fp == NULL)
		return;

	fprintf(fp, "E+F");
	fprintf(fp, "\n[");
	for (pf_uint32 i = 0; i < nbr; i++)
	{
		if (pfcb->f[i][0] > 0)
		{
			fprintf(fp, "%8.5f+%8.5fi; ", pfcb->e[i][0], pfcb->f[i][0]);
		}
		else
		{
			fprintf(fp, "%8.5f-%8.5fi; ", pfcb->e[i][0], -pfcb->f[i][0]);
		}

	}
	fprintf(fp, "]\n");
	fprintf(fp, "\n");
	fclose(fp);
}

 void CDataIOTool::PfStringDataAppendFile(
	pf_char*	filename,
	pf_char*	str
	)
 {
	 FILE*		fp;
	 fp = fopen(filename, "a");
	 if (fp == NULL)
		 return;

	 fprintf(fp, "\n");
	 fprintf(fp, str);
	 fprintf(fp, "\n");

	 fclose(fp);
 }
 void CDataIOTool::Pf1DArrayDataAppendFile(
	const pf_char*					filename,
	PF_CALC_DATA_TYPE*   	data,
	pf_char*							caption,
	pf_uint32							sizei,
	pf_char*							divChari)
 {
	 FILE*		fp;
	 fp = fopen(filename, "a");
	 if (fp == NULL)
		 return;

	 fprintf(fp, caption);
	 fprintf(fp, "\n");
	 for (pf_uint32 i = 0; i < sizei; i++)
	 {
		 fprintf(fp, "%8.5f", data[i]);
		 fprintf(fp, divChari);
	 }


	 fprintf(fp, "\n");

	 fclose(fp);
 }
 void CDataIOTool::Pf2DArrayDataAppendFile(
	 const pf_char*					filename,
	 PF_CALC_DATA_TYPE**	data,
	 pf_char*							caption,
	 pf_uint32							sizei,
	 pf_uint32							sizej,
	 pf_char*							divChari,
	 pf_char*							divCharj)
 {
	 FILE*		fp;
	 fp = fopen(filename, "a");
	 if (fp == NULL)
		 return;

	 fprintf(fp, caption);
	 fprintf(fp, "\n");
	 for (pf_uint32 i = 0; i < sizei; i++)
	 {
		 for (pf_uint32 j = 0; j < sizej; j++)
		 {
			 fprintf(fp, "%4.4f", data[i][j]);
			 fprintf(fp, divChari);
		 }
		 fprintf(fp, divCharj);
	 }


	 fprintf(fp, "\n");

	 fclose(fp);
 }
 void CDataIOTool::PfMatrixDataAppendFile(
	 const pf_char*					filename,
	 CSMatrixSP1_3<double>*	data,
	 pf_char*							caption,
	 pf_uint32							sizei,
	 pf_uint32							sizej,
	 pf_char*							divChari,
	 pf_char*							divCharj)
 {
	 FILE*		fp;
	 fp = fopen(filename, "a");
	 if (fp == NULL)
		 return;

	 fprintf(fp, caption);
	 fprintf(fp, "\n");
	 for (pf_uint32 i = 0; i < sizei; i++)
	 {
		 for (pf_uint32 j = 0; j < sizej; j++)
		 {
			 fprintf(fp, "%4.4f", data->Get(i,j));
			 fprintf(fp, divChari);
		 }
		 fprintf(fp, divCharj);
	 }


	 fprintf(fp, "\n");

	 fclose(fp);
 }
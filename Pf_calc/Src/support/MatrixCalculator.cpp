#include "MatrixCalculator.h"
#include "malloc.h"
CMatrixCalculator::CMatrixCalculator()
{
	method = ePfSolveAeBxMethodLU;
}


CMatrixCalculator::~CMatrixCalculator()
{

}
ePfMatrixCalcErr		CMatrixCalculator::SetMethod(ePfSolveAeBxMethod method)
{
	this->method = method;
	return ePfMatrixCalcErrOK;
}

ePfMatrixCalcErr		CMatrixCalculator::SolveAEqualBx(PF_CALC_DATA_TYPE* vectorA, PF_CALC_DATA_TYPE** matB, PF_CALC_DATA_TYPE* x, int rank)
{

	switch (method)
	{
	case ePfSolveAeBxMethodLU:
	{
		{
			PF_CALC_DATA_TYPE** L = (PF_CALC_DATA_TYPE**)malloc(sizeof(PF_CALC_DATA_TYPE)*rank);
			PF_CALC_DATA_TYPE** U = (PF_CALC_DATA_TYPE**)malloc(sizeof(PF_CALC_DATA_TYPE)*rank);
			for (int i = 0; i < rank; i++)
			{
				L[i] = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*rank);
				U[i] = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*rank);
			}
			for (int i = 0; i < rank; i++)
				for (int j = 0; j < rank; j++)
				{
				L[i][j] = 0;
				U[i][j] = 0;
				}
			PF_CALC_DATA_TYPE* y = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*rank);
			PF_CALC_DATA_TYPE	eleOfL, eleOfU, eleOfA, eleTmp;
			/*构造L对角元*/
			for (int i = 0; i < rank; i++)//
			{
				//Set(psMatL,1,i,i);
				L[i][i] = 1;
				y[i] = 0;
				x[i] = 0;
			}
			/*LU分解迭代过程*/
			for (int i = 0; i < rank; i++)
			{
				for (int j = i; j < rank; j++)
				{
					PF_CALC_DATA_TYPE	temp = 0;
	
					for (int m = 0; m < i; m++)
					{
						eleOfL = L[i][m];
						eleOfU = U[m][j];
						temp += eleOfL*eleOfU;
					}
					eleOfA = matB[i][j];
					U[i][j] = eleOfA - temp;
				}
				/*构造L矩阵*/
				for (int k = i + 1; k < rank; k++)
				{
					PF_CALC_DATA_TYPE	temp = 0;
					/*求和*/
					for (int m = 0; m < i; m++)
					{
						eleOfL = L[k][m];
						eleOfU = U[m][i];
						temp += eleOfL*eleOfU;
					}
					eleOfA = matB[k][i];
					eleOfU = U[i][i];
					L[k][i] = (eleOfA - temp) / eleOfU;
				}
			}
			/*已完成L、U矩阵构造*/
			/*解L*y=VectorA之y*/
			y[0] = vectorA[0];
			for (int i = 1; i < rank; i++)
			{
				PF_CALC_DATA_TYPE	temp = 0;
				for (int j = 0; j < rank; j++)
				{
					temp += L[i][j] * y[j];
				}
				y[i] = 0;
				y[i] = vectorA[i] - temp;
			}
			/*解U*x=y之x*/
			x[rank - 1] = y[rank - 1] / U[rank - 1][rank - 1];
			for (int i = rank - 1 - 1; i >= 0; i--)
			{
				PF_CALC_DATA_TYPE	temp = 0;
				for (int j = i; j < rank; j++)
				{
					temp += U[i][j] * x[j];
				}
				x[i] = (y[i] - temp) / U[i][i];
			}
#if 0
			printf("L\n");
			for (int i = 0; i < rank; i++)
			{
				for (int j = 0; j < rank; j++)
				{
					//Get_r(psMatL,i,j,&eleTmp);
					printf("%8.4f ", L[i][j]);
				}
				printf("\n");
			}
			printf("U\n");
			for (int i = 0; i < rank; i++)
			{
				for (int j = 0; j < rank; j++)
				{
					//Get_r(psMatU,i,j,&eleTmp);
					printf("%8.4f ", U[i][j]);
				}
				printf("\n");
			}
			;
#endif
			free(y);
			for (int i = 0; i < rank; i++)
			{
				free(L[i]);
				free(U[i]);
			}
			free(L);
			free(U);

		}

		break;
	}


	default:
		break;
	}

	return ePfMatrixCalcErrOK;

}


ePfMatrixCalcErr		CMatrixCalculator::SolveAEqualBx(PF_CALC_DATA_TYPE* vectorA, CMatrix<PF_CALC_DATA_TYPE>& matB, PF_CALC_DATA_TYPE* x, int rank)
{

	switch (method)
	{
	case ePfSolveAeBxMethodLU:
	{
		{
			CDMatrix<PF_CALC_DATA_TYPE> L(rank, rank);
			CDMatrix<PF_CALC_DATA_TYPE> U(rank, rank);

			for (int i = 0; i < rank; i++)
				for (int j = 0; j < rank; j++)
				{
				L.Set(i, j, 0);
				U.Set(i, j, 0);
				}

			PF_CALC_DATA_TYPE* y = (PF_CALC_DATA_TYPE*)malloc(sizeof(PF_CALC_DATA_TYPE)*rank);
			PF_CALC_DATA_TYPE	eleOfL, eleOfU, eleOfA, eleTmp;
			/*构造L对角元*/
			for (int i = 0; i < rank; i++)//
			{
				L.Set(i, i,1);
				y[i] = 0;
				x[i] = 0;
			}
			/*LU分解迭代过程*/
			for (int i = 0; i < rank; i++)
			{
				for (int j = i; j < rank; j++)
				{
					PF_CALC_DATA_TYPE	temp = 0;

					for (int m = 0; m < i; m++)
					{
						eleOfL = L.Get(i,m);
						eleOfU = U.Get(m,j);
						temp += eleOfL*eleOfU;
					}
					eleOfA = matB.Get(i,j);
					U.Set(i, j, eleOfA - temp);
				}
				/*构造L矩阵*/
				for (int k = i + 1; k < rank; k++)
				{
					PF_CALC_DATA_TYPE	temp = 0;
					/*求和*/
					for (int m = 0; m < i; m++)
					{
						eleOfL = L.Get(k,m);
						eleOfU = U.Get(m,i);
						temp += eleOfL*eleOfU;
					}
					eleOfA = matB.Get(k,i);
					eleOfU = U.Get(i,i);
					L.Set(k,i,(eleOfA - temp) / eleOfU);
				}
			}
			/*已完成L、U矩阵构造*/
			/*解L*y=VectorA之y*/
			y[0] = vectorA[0];
			for (int i = 1; i < rank; i++)
			{
				PF_CALC_DATA_TYPE	temp = 0;
				for (int j = 0; j < rank; j++)
				{
					temp += L.Get(i,j) * y[j];
				}
				y[i] = 0;
				y[i] = vectorA[i] - temp;
			}
			/*解U*x=y之x*/
			x[rank - 1] = y[rank - 1] / U.Get(rank - 1,rank - 1);
			for (int i = rank - 1 - 1; i >= 0; i--)
			{
				PF_CALC_DATA_TYPE	temp = 0;
				for (int j = i; j < rank; j++)
				{
					temp += U.Get(i,j) * x[j];
				}
				x[i] = (y[i] - temp) / U.Get(i,i);
			}
#if 0
			printf("L\n");
			for (int i = 0; i < rank; i++)
			{
				for (int j = 0; j < rank; j++)
				{
					//Get_r(psMatL,i,j,&eleTmp);
					printf("%8.4f ", L[i][j]);
				}
				printf("\n");
			}
			printf("U\n");
			for (int i = 0; i < rank; i++)
			{
				for (int j = 0; j < rank; j++)
				{
					//Get_r(psMatU,i,j,&eleTmp);
					printf("%8.4f ", U[i][j]);
				}
				printf("\n");
			}
			;
#endif
			free(y);

		}

		break;
	}


	default:
		break;
	}

	return ePfMatrixCalcErrOK;

}
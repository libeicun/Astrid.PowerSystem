#include "UserProcesses.h"
#include "MethodNewtonRaphson.h"
#include "DataIOTool.h"
#include "Timing.h"
#include "PowerSysCalcFlow.h"
#include "MethodNewtonRaphson.h"
#include <string.h>
#include <stdio.h>
void	fPfCalcOnce(list<string>& paras)
{
	char		filename[20];
	
	/*if (strcmp(para1,"")!=0)
	{
		strcpy(filename, para1);
	}
	else
	{
		printf("Please Enter the Path of Data File\n");
		gets(filename);
	}
	FILE*	fp=fopen(filename,"rb");
	if (fp == NULL)
	{
		printf("File not found or invalid file name.\n");
		return;
	}
	fclose(fp);*/
	//CTiming::TimeLable("Begin Construct CPfCalcDataFileIeee");
	//CPfCalcDataFileIeee					df(filename);
	//CTiming::TimeLable("End Construct CPfCalcDataFileIeee");

	//CTiming::TimeLable("Begin Construct CPfCalcMethodNewtonRaphson");
	//MethodNewtonRaphson		nl_iter;
	//CTiming::TimeLable("End Construct CPfCalcMethodNewtonRaphson");



	//CTiming::On();
	CTiming::TimeLable("Enter Iterate");
	CPowerSysCalculation*	pPfCalc = new CPowerSysCalcFlow;
	CTiming::Off();
	pPfCalc->Calc();
	CTiming::On();
	//
	//nl_iter.Iterate();
	//
	CTiming::TimeLable("Exit Iterate");
	
}
void	fPfBDF(list<string>& paras)
{
	//printf("Build Data File\n");
}
void	fReturn(list<string>& paras)
{
	//printf("Return\n");
}
void	fSyscall(list<string>& paras)
{
	//if (strcmp(para1,"clc")==0)
	{
		system("cls");
	}
}


static char	password[50];
void	fLock(list<string>& paras)
{
	/*if (strcmp(para1,"")==0)
	{
		printf("Please enter a password.\n");
		gets(password);
	}
	else
	{
		strcpy(password, para1);
	}*/
	system("cls");
	//cui.DisableExec();
	//cui.DisableStausTrans();

}
void	fUnLock(list<string>& paras)
{
	/*if (strcmp(para1,password)==0)
	{
		cui.EnableExec();
		cui.EnableStausTrans();
	}
	else
	{
		printf("You have enter a invalid password.\n");
	}*/
}



void	fDefaultProc()
{
	/*printf("\n--------------------------------------------------------------------\n");
	printf("A Tool for Power System Calculation Developped by Libeicun.\nVersion 1.0\nCopyrights 2014-2018\n");
	printf("\n--------------------------------------------------------------------\n");*/
	static pf_uint8	ctr = 0;
	ctr++;
	if (ctr==3)
	{ 
		ctr = 0;
		pf_char	in[10];
		while (1){
			printf("Are you a Doubi?\n");
			gets_s(in);
			if (strcmp(in,"yes")==0)
			{
				break;
			}
		}

	}
		

}
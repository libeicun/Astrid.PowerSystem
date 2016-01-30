#include "DataFileReaderForIeee.h"


CDataFileReaderForIeee::CDataFileReaderForIeee()
{
}


CDataFileReaderForIeee::~CDataFileReaderForIeee()
{
}

pf_bool CDataFileReaderForIeee::CheckDataFile(pf_char* path)
{
	return pf_bool();
}
eReadDataFileErr CDataFileReaderForIeee::ReadDataFile(pf_char* path)
{
	FILE *fp = fopen(path, "rb");

	blNodeNbr = 0;
	pqNodeNbr = 0;
	pvNodeNbr = 0;

	PF_CALC_DATA_TYPE   r, x, bb, gij, bij, k0, kmin, kmax;
	pf_uint32						nodeNbr, branchNbr;
	pf_uint32						tmp, branchNo = 0, nodeNoi = 0, nodeNoj = 0;
	PF_CALC_DATA_TYPE	baseCapacity;
	PF_CALC_DATA_TYPE	central;
	pf_uint32						targetFunctionClassCode;
	PF_CALC_DATA_TYPE	ble, blf;
	pf_uint32						blNodeNo;

	PF_CALC_DATA_TYPE	Pg, Qg, Pl, Ql;


	/*Get the header of IEEE standard file.*/
	fscanf(fp, "%d %d %lf %d %lf", &MyFileHeader.nodeNbr, &MyFileHeader.branchNbr, &MyFileHeader.Capacity, &MyFileHeader.maxIterTimes, &MyFileHeader.centralPara
		);
	fscanf(fp, "%lf %d", &MyFileHeader.precision, &MyFileHeader.functionClass);
	/*Done.*/

	/*Get the Bl Node parameters.*/
	CPfCalcDfIeeeBlNodePara	blnode;
	fscanf(fp, "%d", &nodeNoi);
	while (nodeNoi != 0)
	{
		/* lineParameters[i_linep]=(PF_CALC_DF_IEEE_LINE_PARA)malloc(sizeof(PF_CALC_DF_IEEE_LINE_PARA));
		fscanf(fp,"%d %d %lf %lf %lf",&nodeNoi,&nodeNoj,&r,&x,&bb);
		lineParameters[i_linep].bDiv2=bb;
		lineParameters[i_linep].branchNo=branchNo;
		lineParameters[i_linep].nodei=nodeNoi;
		lineParameters[i_linep].nodej=nodeNoj;
		fscanf(fp,"%d",&branchNo);	*/
		fscanf(fp, "%d", &nodeNoj);
		blnode.nodeNo = nodeNoj;
		blNodeParaList.push_back(blnode);
		fscanf(fp, "%d", &nodeNoi);
	}
	/*Done*/
	/*Get the parameters of Lines.*/
	CPfCalcDfIeeeLinePara	line;
	//fscanf(fp,"%d",&tmp);         
	/*线路参数*/
	fscanf(fp, "%d", &branchNo);
	pf_uint32	i_linep = 0;
	while (branchNo != 0)
	{
		/* lineParameters[i_linep]=(PF_CALC_DF_IEEE_LINE_PARA)malloc(sizeof(PF_CALC_DF_IEEE_LINE_PARA));
		fscanf(fp,"%d %d %lf %lf %lf",&nodeNoi,&nodeNoj,&r,&x,&bb);
		lineParameters[i_linep].bDiv2=bb;
		lineParameters[i_linep].branchNo=branchNo;
		lineParameters[i_linep].nodei=nodeNoi;
		lineParameters[i_linep].nodej=nodeNoj;
		fscanf(fp,"%d",&branchNo);	*/
		fscanf(fp, "%d %d %lf %lf %lf", &nodeNoi, &nodeNoj, &r, &x, &bb);
		line.bDiv2 = bb;
		line.branchNo = branchNo;
		line.nodei = nodeNoi;
		line.nodej = nodeNoj;
		line.R = r;
		line.X = x;
		lineParaList.push_back(line);
		fscanf(fp, "%d", &branchNo);
		i_linep++;
	}
	/*Done.*/

	/*Get the parameters of Grounding Lines.*/
	CPfCalcDfIeeeGLinePara	gline;
	//fscanf(fp,"%d",&tmp); 
	/*接地支路参数*/
	fscanf(fp, "%d", &nodeNoi);
	pf_uint32	i_glinep = 0;
	while (nodeNoi != 0)
	{
		fscanf(fp, "%lf", &gij);
		/* gLineParameters[i_glinep]=(PF_CALC_DF_IEEE_GNDLINE_PARA)malloc(sizeof(PF_CALC_DF_IEEE_GNDLINE_PARA));
		gLineParameters[i_glinep].nodeNo=nodeNoi;
		gLineParameters[i_glinep].G=gij;*/

		gline.G = gij;
		gline.nodeNo = nodeNoi;
		gLineParaList.push_back(gline);
		fscanf(fp, "%d", &nodeNoi);
		i_glinep++;
	}
	/*Done.*/


	/*Get the parameters of Transformer.*/
	CPfCalcDfIeeeTransPara	trans;
	//fscanf(fp,"%d",&tmp);	
	/*变压器参数*/
	fscanf(fp, "%d", &branchNo);
	pf_uint32 i_tp = 0;
	while (branchNo != 0)
	{
		fscanf(fp, "%d %d %lf %lf %lf %lf %lf", &nodeNoi, &nodeNoj, &r, &x, &k0, &kmin, &kmax);
		/* transParameters[i_tp]=(PF_CALC_DF_IEEE_TRANSFORMER_PARA)
		malloc(sizeof(PF_CALC_DF_IEEE_TRANSFORMER_PARA));
		transParameters[i_tp].branchNo=branchNo;
		transParameters[i_tp].k0=k0;
		transParameters[i_tp].kMax=kmax;
		transParameters[i_tp].kMin=kmin;
		transParameters[i_tp].nodei=nodeNoi;
		transParameters[i_tp].nodej=nodeNoj;
		transParameters[i_tp].R=r;
		transParameters[i_tp].X=x;*/
		trans.branchNo = branchNo;
		trans.k0 = k0;
		trans.kMax = kmax;
		trans.kMin = kmin;
		trans.nodei = nodeNoi;
		trans.nodej = nodeNoj;
		trans.R = r;
		trans.X = x;
		transParaList.push_back(trans);
		fscanf(fp, "%d", &branchNo);
		i_tp++;
	}
	/*Done.*/

	/*Get the Running parameters.*/
	CPfCalcDfIeeeRunningPara 	run;
	//fscanf(fp,"%d",&tmp);	
	fscanf(fp, "%d", &nodeNoi);
	pf_uint32 i_run = 0;
	while (nodeNoi != 0)
	{
		// runningParameters[i_run]=(pf_calc_data_file_ieee_running_para)(malloc(sizeof(pf_calc_data_file_ieee_running_para)));
		fscanf(fp, "%lf %lf %lf %lf", &Pg, &Qg, &Pl, &Ql);
		/* runningParameters[i_run].nodeNo=nodeNoi;
		runningParameters[i_run].Pg=Pg;
		runningParameters[i_run].Qg=Qg;
		runningParameters[i_run].Pl=Pl;
		runningParameters[i_run].Ql=Ql;*/
		run.nodeNo = nodeNoi;
		run.Pg = Pg;
		run.Qg = Qg;
		run.Pl = Pl;
		run.Ql = Ql;
		runningParaList.push_back(run);
		fscanf(fp, "%d", &nodeNoi);
		i_run++;
	}
	/*Done.*/

	/*Get the PV Node parameters.*/
	CPfCalcDfIeeePvNodePara	pv;
	PF_CALC_DATA_TYPE	pvQmin, pvQmax, u;
	//fscanf(fp,"%d",&tmp);	
	fscanf(fp, "%d", &nodeNoi);
	pf_uint32 i_pvp = 0;
	while (nodeNoi != 0)
	{
		// pvNodeParameters[i_pvp]=(PF_CALC_DF_IEEE_PVNODE_PARA)
		//malloc(sizeof(PF_CALC_DF_IEEE_PVNODE_PARA));
		fscanf(fp, "%lf %lf %lf", &u, &pvQmin, &pvQmax);

		/* pvNodeParameters[i_pvp].nodeNo=nodeNoi;
		pvNodeParameters[i_pvp].QMax=pvQmax;
		pvNodeParameters[i_pvp].QMin=pvQmin;
		pvNodeParameters[i_pvp].u=u;*/
		pv.nodeNo = nodeNoi;
		pv.QMax = pvQmax;
		pv.QMin = pvQmin;
		pv.u = u;
		pvNodeParaList.push_back(pv);
		fscanf(fp, "%d", &nodeNoi);
		i_pvp++;
	}
	/*Done.*/

	/*Get the generator cost parameters.*/
	CPfCalcDfIeeeGCostPara	gc;
	PF_CALC_DATA_TYPE	a, b, c, gcPgmax, gcPgmin;
	//fscanf(fp,"%d",&tmp);	
	fscanf(fp, "%d", &nodeNoi);
	pf_uint32 i_gcp = 0;
	while (nodeNoi != 0)
	{
		// gcostParameters[i_gcp]=(PF_CALC_DF_IEEE_GENERATOR_COST_PARA)
		//malloc(sizeof(PF_CALC_DF_IEEE_GENERATOR_COST_PARA));
		fscanf(fp, "%lf %lf %lf %lf %lf", &c, &b, &a, &gcPgmin, &gcPgmax);
		/* gcostParameters[i_gcp].a=a;
		gcostParameters[i_gcp].b=b;
		gcostParameters[i_gcp].c=c;
		gcostParameters[i_gcp].nodeNo=nodeNoi;
		gcostParameters[i_gcp].PgMax=gcPgmax;
		gcostParameters[i_gcp].PgMin=gcPgmin;*/
		gc.a = a;
		gc.b = b;
		gc.c = c;
		gc.nodeNo = nodeNoi;
		gc.PgMax = gcPgmax;
		gc.PgMin = gcPgmin;
		gcostParaList.push_back(gc);
		fscanf(fp, "%d", &nodeNoi);
		i_gcp++;
	}
	/*Done.*/
	fclose(fp);
	return eReadDataFileErr();
}


pf_bool CDataFileReaderForIeee::GetBlNodeNbr(pf_uint32& nbr)
{
	nbr=blNodeParaList.size();
	return pf_bool();
}


pf_bool CDataFileReaderForIeee::GetPqNodeNbr(pf_uint32& nbr)
{
	nbr = MyFileHeader.nodeNbr - blNodeParaList.size() - pvNodeParaList.size()+1;
	return pf_bool();
}


pf_bool CDataFileReaderForIeee::GetPvNodeNbr(pf_uint32& nbr)
{
	nbr = pvNodeParaList.size()-1;
	return pf_bool();
}


pf_bool  CDataFileReaderForIeee::GetPqNodeTable(CPfCalcNodePq* table, pf_uint32 size)
{
	return pf_bool();
}

pf_bool  CDataFileReaderForIeee::GetPvNodeTable(CPfCalcNodePv* table, pf_uint32 size)
{

	return pf_bool();
}

pf_bool  CDataFileReaderForIeee::GetNodeTables(
	CPfCalcNodeBl* tablebl,
	CPfCalcNodePq* tablepq,
	CPfCalcNodePv* tablepv)
{
	pf_uint32	pvNodeNbr =pvNodeParaList.size();
	pf_uint32	blNodeNbr = blNodeParaList.size();
	pf_uint32	pqNodeNbr = MyFileHeader.nodeNbr - pvNodeNbr - blNodeNbr;

	/*	Update the .blNodeTable[].*/
	CPfCalcDfIeeeBlNodePara					bldata;
	list<CPfCalcDfIeeeBlNodePara>::iterator	it_bldata;
	pf_uint32 i;
	for (it_bldata = blNodeParaList.begin(), i = 0; it_bldata != blNodeParaList.end(); it_bldata++, i++)
	{
		bldata = *it_bldata;
	    tablebl[i].e = 1.05;
		tablebl[i].f = 0;
		tablebl[i].index = bldata.nodeNo - 1;
	}
	/*	Done.*/
	pf_uint32	nodeNoi = 0, nodeNoj = 0;
	PF_CALC_DATA_TYPE	Ql, Pl, Qg, Pg, P, Q, u;

	list<CPfCalcDfIeeePvNodePara>::iterator     it_pv;
	CPfCalcDfIeeePvNodePara						pvdata;
	pf_uint8	pvDataIncludeInBl = 0;
	CPfCalcNodePv*	ppv = tablepv;
	for (it_pv = pvNodeParaList.begin(); it_pv != pvNodeParaList.end(); it_pv++)
	{

		pvDataIncludeInBl = 0;
		pvdata = *it_pv;
		nodeNoi = pvdata.nodeNo;
		u = pvdata.u;

		for (pf_uint32 j = 0; j<blNodeNbr; j++)
		{
			if (pvdata.nodeNo == tablebl[j].index + 1)
			{
				pvDataIncludeInBl = 1;
				 pvNodeNbr--;
				 pqNodeNbr++;
			}
		}
	}
	pf_uint32 pqvNbr = pqNodeNbr + pvNodeNbr;
	pf_uint32 nbr = pqvNbr + blNodeNbr;
	pf_uint32 pqvNbrTimes2 = pqvNbr * 2;
	/*Here we get the Running parameters, or to say PQ/PV/BL Node Parameters from IEEE standard file.*/
	list<CPfCalcDfIeeeRunningPara>::iterator	it_running;
	CPfCalcDfIeeeRunningPara						runningdata;
	pf_uint32		sizeRunningPara = runningParaList.size();
	pvDataIncludeInBl = 0;
	ppv = tablepv;
	for (it_pv = pvNodeParaList.begin(); it_pv != pvNodeParaList.end(); it_pv++)
	{

		pvDataIncludeInBl = 0;

		pvdata = *it_pv;
		nodeNoi = pvdata.nodeNo;
		u = pvdata.u;

		for (pf_uint32 j = 0; j<blNodeNbr; j++)
		{
			if (pvdata.nodeNo == tablebl[j].index + 1)
			{
				pvDataIncludeInBl = 1;
			    tablebl[j].e = u;
			}
		}
		if (pvDataIncludeInBl == 0)
		{
			(*ppv).index = nodeNoi - 1;
			(*ppv).U2 = u;
			ppv++;
		}

	}
	CPfCalcNodePq*	ppq = tablepq;
	pf_uint8	runningDataIncludedInPv = 0, runningDataIncludeInBl = 0;
	for (it_running = runningParaList.begin(); it_running != runningParaList.end(); it_running++)
	{
		runningDataIncludedInPv = 0;
		runningDataIncludeInBl = 0;
		runningdata = *it_running;

		for (pf_uint32 j = 0; j<pvNodeNbr; j++)
		{
			if (runningdata.nodeNo == tablepv[j].index + 1)
			{
				runningDataIncludedInPv = 1;
				tablepv[j].P = runningdata.Pg - runningdata.Pl;
#if PQ_USE_1BASE_VAL
				tablepv[j].P /= MyFileHeader.Capacity;
#endif
			}
		}
		if (runningDataIncludedInPv == 0)//it is not a PV Node.
		{
			for (pf_uint32 j = 0; j<blNodeNbr; j++)
			{
				if (runningdata.nodeNo == tablebl[j].index + 1)
				{
					runningDataIncludeInBl = 1;
				}
			}
			if (runningDataIncludeInBl == 0)// and it is not a BL Node.
			{			//then it is a PQ Node.
				(*ppq).index = runningdata.nodeNo - 1;
				(*ppq).P = runningdata.Pg - runningdata.Pl;
				(*ppq).Q = runningdata.Qg - runningdata.Ql;
#if PQ_USE_1BASE_VAL
				(*ppq).P /= MyFileHeader.Capacity;
				(*ppq).Q /= MyFileHeader.Capacity;
#endif
				ppq++;
			}
		}

	}
	/*Done.*/
	/*After read the data file, update the .id.offset field.*/
	for (pf_uint32 i = 0; i<blNodeNbr; i++)
	{
		for (pf_uint32 j = 0; j<pqNodeNbr; j++)
		{
			if (tablepq[j].index>tablebl[i].index)
				tablepq[j].offset++;
		}

		for (pf_uint32 j = 0; j<pvNodeNbr; j++)
		{
			if (tablepv[j].index>tablebl[i].index)
				tablepv[j].offset++;
		}
	}
	/*Then update the .id.offset2 field.*/
	for (pf_uint32 i = 0; i<pvNodeNbr; i++)
	{
		for (pf_uint32 j = 0; j<pqNodeNbr; j++)
		{
			if (tablepq[j].index - tablepq[j].offset>tablepv[i].index - tablepv[i].offset)
				tablepq[j].offset2++;
		}
	}
	for (pf_uint32 j = 0; j<pqNodeNbr; j++)
	{
		tablepq[j].offset2 += tablepq[j].offset;
	}
	/*Done.*/
	for (pf_uint32 i = 0; i<pqNodeNbr; i++)
	{
		tablepq[i].e = 1;
		tablepq[i].f = 0;
	}
	for (pf_uint32 i = 0; i<pvNodeNbr; i++)
	{
		tablepv[i].e = tablepv[i].U2;
		tablepv[i].f = 0;
	}
	return pf_bool();
}
pf_bool CDataFileReaderForIeee::GetBlNodeTable(CPfCalcNodeBl* table, pf_uint32 size){
	/*	Update the .blNodeTable[].*/
	CPfCalcDfIeeeBlNodePara							bldata;
	list<CPfCalcDfIeeeBlNodePara>::iterator	it_bldata;
	pf_uint32	i = 0;
	for (it_bldata = blNodeParaList.begin(), i = 0; it_bldata != blNodeParaList.end(); it_bldata++, i++)
	{
		bldata = *it_bldata;
		table[i].e = 1.05;
		table[i].f = 0;
		table[i].index = bldata.nodeNo - 1;
	}
	/*	Done.*/
	return pf_bool();
}


pf_bool CDataFileReaderForIeee::GetMatGij(CMatrix<PF_CALC_DATA_TYPE>* g_mat)
{

	return pf_bool();
}
pf_bool CDataFileReaderForIeee::GetMatBij(CMatrix<PF_CALC_DATA_TYPE>	* b_mat)
{
	return pf_bool();
}

pf_bool CDataFileReaderForIeee::GetMatY(
	CMatrix<PF_CALC_DATA_TYPE>	* Gij,
	CMatrix<PF_CALC_DATA_TYPE>	* Bij)
{

	/*	Get the Parameters of Lines.*/
	PF_CALC_DATA_TYPE	gij, bij, t, bb;
	pf_uint32 nodeNoi=0, nodeNoj=0;


	pf_uint32	sizeLinesPara = lineParaList.size();
	list<CPfCalcDfIeeeLinePara>::iterator 	it_line;
	CPfCalcDfIeeeLinePara	linedata;

	for (it_line = lineParaList.begin(); it_line != lineParaList.end(); it_line++)
	{

		linedata = *it_line;
		gij = linedata.R / (linedata.R*linedata.R + linedata.X*linedata.X);
		bij = -linedata.X / (linedata.R*linedata.R + linedata.X*linedata.X);
		nodeNoi = linedata.nodei;
		nodeNoj = linedata.nodej;
		bb = linedata.bDiv2;
		t = 0;
		Gij->Add_Lwr(nodeNoi - 1, nodeNoj - 1, -gij);
		Bij->Add_Lwr(nodeNoi - 1, nodeNoj - 1, -bij);
		Bij->Add(nodeNoi - 1, nodeNoi - 1, bij + bb);                     //因为线路电纳只包含在自电纳中，所以bb加在b[i][i]和b[j][j]里面
		Bij->Add(nodeNoj - 1, nodeNoj - 1, bij + bb);
		Gij->Add(nodeNoi - 1, nodeNoi - 1, gij);                     //因为线路电纳只包含在自电纳中，所以bb加在b[i][i]和b[j][j]里面
		Gij->Add(nodeNoj - 1, nodeNoj - 1, gij);
	}
	/*	Done.*/


	/*Get the parameters of Grounding Lines and Update this->Gij and Bij.*/
	list<CPfCalcDfIeeeGLinePara>::iterator it_gline;
	CPfCalcDfIeeeGLinePara						glinedata;

	pf_uint32		sizeGLinePara = gLineParaList.size();

	for (it_gline = gLineParaList.begin(); it_gline != gLineParaList.end(); it_gline++)
	{

		glinedata = *it_gline;
		nodeNoi = glinedata.nodeNo;
		bij = glinedata.G;
		Bij->Add(nodeNoi - 1, nodeNoi - 1, bij);

	}
	/*Done.*/

	/*Get the parameters of Transformer and Grounding Lines and Update this->Gij and Bij.*/
	list<CPfCalcDfIeeeTransPara>::iterator it_trans;
	CPfCalcDfIeeeTransPara						transdata;
	PF_CALC_DATA_TYPE											r, x, k0, kMax, kMin;
	pf_uint32		sizeTransPara = transParaList.size();

	for (it_trans = transParaList.begin(); it_trans != transParaList.end(); it_trans++)
	{

		transdata = *it_trans;
		nodeNoi = transdata.nodei;
		nodeNoj = transdata.nodej;
		kMin = transdata.kMin;
		kMax = transdata.kMax;
		k0 = transdata.k0;
		r = transdata.R;
		x = transdata.X;
		gij = r / (r*r + x*x);
		bij = -x / (r*r + x*x);	//归算到j点

		Gij->Add_Lwr(nodeNoi - 1, nodeNoj - 1, -gij / k0);
		Bij->Add_Lwr(nodeNoi - 1, nodeNoj - 1, -bij / k0);
		Gij->Add(nodeNoi - 1, nodeNoi - 1, gij / k0 / k0);
		Bij->Add(nodeNoi - 1, nodeNoi - 1, bij / k0 / k0);
		Gij->Add(nodeNoj - 1, nodeNoj - 1, gij);
		Bij->Add(nodeNoj - 1, nodeNoj - 1, bij);

	}
	/*Done.*/
	return pf_bool();
}

pf_bool CDataFileReaderForIeee::GetMaxIterTimes(pf_uint32& times){
	times = MyFileHeader.maxIterTimes;
	return pf_bool();
}
pf_bool	CDataFileReaderForIeee::GetPresion(pf_f64& pre){
	pre = MyFileHeader.precision;
	return pf_bool();
}
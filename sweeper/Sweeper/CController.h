#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <windows.h>

#include "CMineSweeper.h"
#include "CGenAlg.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"

using namespace std;

class CController{
private:
	vector<SGenome>			m_vecThePopulation;	//存放所有扫雷车的基因
	vector<CMinesweeper>	m_vecSweepers;		//存放所有的扫雷车
	vector<SVector2D>		m_vecMines;			//存放所有的地雷
	CGenAlg*				m_pGA;
	int						m_NumSweepers;		//扫雷车的数量
	int						m_NumMines;			//地雷的数量
	int						m_NumWeightsInNN;	//输入权重的数量
	vector<SPoint>			m_SweeperVB;		//一个扫雷车所有顶点，长度16
	vector<SPoint>			m_MineVB;			//一个地雷的所有顶点，长度4

	vector<double>			m_vecAvFitness;		//保存每一代的平均分
	vector<double>			m_vecBestFitness;	//保存没一代最好的分

	HPEN			m_RedPen;
	HPEN			m_BluePen;
	HPEN			m_GreenPen;
	HPEN			m_OldPen;

	HWND			m_hwndMain;
	bool			m_bFastRender;
	int				m_iTicks;			//记录每一代演进的时间，如果高于某值，就进行下一代
	int				m_iGenerations;
	int				cxClient, cyClient;
	void			PlotStats(HDC surface);

public:
	CController(HWND hwndMain);
	~CController();
	void		Render(HDC surface);
	void		WorldTransform(vector<SPoint> &VBuffer, SVector2D vPos);
	bool		Update();
	bool		FastRender()const	{return m_bFastRender;}
	void		FastRender(bool arg){m_bFastRender = arg;}
	void		FastRenderToggle()	{m_bFastRender = !m_bFastRender;}
};


#endif
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
	vector<SGenome>			m_vecThePopulation;	//�������ɨ�׳��Ļ���
	vector<CMinesweeper>	m_vecSweepers;		//������е�ɨ�׳�
	vector<SVector2D>		m_vecMines;			//������еĵ���
	CGenAlg*				m_pGA;
	int						m_NumSweepers;		//ɨ�׳�������
	int						m_NumMines;			//���׵�����
	int						m_NumWeightsInNN;	//����Ȩ�ص�����
	vector<SPoint>			m_SweeperVB;		//һ��ɨ�׳����ж��㣬����16
	vector<SPoint>			m_MineVB;			//һ�����׵����ж��㣬����4

	vector<double>			m_vecAvFitness;		//����ÿһ����ƽ����
	vector<double>			m_vecBestFitness;	//����ûһ����õķ�

	HPEN			m_RedPen;
	HPEN			m_BluePen;
	HPEN			m_GreenPen;
	HPEN			m_OldPen;

	HWND			m_hwndMain;
	bool			m_bFastRender;
	int				m_iTicks;			//��¼ÿһ���ݽ���ʱ�䣬�������ĳֵ���ͽ�����һ��
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
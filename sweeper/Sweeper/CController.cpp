#include "CController.h"

const int	NumSweeperVerts = 16;
const SPoint	sweeper[NumSweeperVerts] = {SPoint(-1, -1),		SPoint(-1,1),	SPoint(-0.5, 1),	SPoint(-0.5, -1),
											SPoint(0.5, -1),	SPoint(1,-1),	SPoint(1,1),		SPoint(0.5,1),
											SPoint(-0.5,-0.5),	SPoint(0.5,0.5),SPoint(-0.5,0.5),	SPoint(-0.25,0.5),
											SPoint(-0.25,1.75),	SPoint(0.25,1.75),	SPoint(0.25,0.25),	SPoint(0.5,0.5)};

const int NumMineVerts = 4;
const SPoint	mine[NumMineVerts] = {SPoint(-1, -1), SPoint(-1,1), SPoint(1,1), SPoint(1,-1)};

CController::CController(HWND hwndMain):m_NumSweepers(CParams::iNumSweepers),
										m_pGA(NULL),
										m_bFastRender(false),
										m_iTicks(0),
										m_NumMines(CParams::iNumMines),
										m_hwndMain(hwndMain),
										m_iGenerations(0),
										cxClient(CParams::WindowWidth),
										cyClient(CParams::WindowHeight)
{
	for(int i=0; i<m_NumSweepers; ++i)
		m_vecSweepers.push_back(CMinesweeper());

	m_NumWeightsInNN = m_vecSweepers[0].GetNumberOfWeights();

	//创建种群
	m_pGA = new CGenAlg(m_NumSweepers, CParams::dMutationRate, CParams::dCrossoverRate, m_NumWeightsInNN);
	m_vecThePopulation = m_pGA->GetChromos();

	//每个扫雷车放一个染色体进去
	for(int i=0; i<m_NumSweepers; i++)
		m_vecSweepers[i].PutWeights(m_vecThePopulation[i].vecWeights);

	for(int i=0; i<m_NumMines; ++i)
		m_vecMines.push_back(SVector2D(RandFloat() * cxClient, RandFloat() * cyClient));

	m_BluePen	= CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_RedPen	= CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_GreenPen	= CreatePen(PS_SOLID, 1, RGB(0, 150, 0));
	m_OldPen	= NULL;

	for(int i=0; i<NumSweeperVerts; ++i)
		m_SweeperVB.push_back(sweeper[i]);

	for(int i=0; i<NumMineVerts; ++i)
		m_MineVB.push_back(mine[i]);
}

CController::~CController(){
	if(m_pGA)
		delete	m_pGA;

	DeleteObject(m_BluePen);
	DeleteObject(m_RedPen);
	DeleteObject(m_GreenPen);
	DeleteObject(m_OldPen);
}

//将vbbuffer移动到vPos处
void CController::WorldTransform(vector<SPoint> &VBuffer, SVector2D vPos){
	C2DMatrix matTransform;
	matTransform.Scale(CParams::dMineScale, CParams::dMineScale);
	matTransform.Translate(vPos.x, vPos.y);
	matTransform.TransformSPoints(VBuffer);
}

bool CController::Update(){
	if(m_iTicks++ < CParams::iNumTicks){	//本代基因演进
		for(int i=0; i<m_NumSweepers; ++i){
			if(!m_vecSweepers[i].Update(m_vecMines)){
				MessageBox(m_hwndMain, "Wrong amount of NN inputs!", "Error", MB_OK);
				return false;
			}

			int GrabHit = m_vecSweepers[i].CheckForMine(m_vecMines, CParams::dMineScale);
			if(GrabHit >= 0){
				m_vecSweepers[i].IncrementFitness();
				m_vecMines[GrabHit] = SVector2D(RandFloat() * cxClient, RandFloat() * cyClient);
			}

			m_vecThePopulation[i].dFitness = m_vecSweepers[i].Fitness();
		}
	}else{	//下一代演进
		m_vecAvFitness.push_back(m_pGA->AverageFitness());
		m_vecBestFitness.push_back(m_pGA->BestFitness());
		++m_iGenerations;
		m_iTicks = 0;
		m_vecThePopulation = m_pGA->Epoch(m_vecThePopulation);

		for(int i=0; i<m_NumSweepers; ++i){
			m_vecSweepers[i].PutWeights(m_vecThePopulation[i].vecWeights);
			m_vecSweepers[i].Reset();
		}
	}
	return true;
}

void CController::Render(HDC surface){
	string s = "Generation:           " + itos(m_iGenerations);
	TextOut(surface, 5, 0, s.c_str(), s.size());

	if(!m_bFastRender){
		m_OldPen = (HPEN)SelectObject(surface, m_GreenPen);
		for(int i=0; i<m_NumMines; ++i){
			vector<SPoint> mineVB = m_MineVB;
			WorldTransform(mineVB, m_vecMines[i]);

			MoveToEx(surface, (int)mineVB[0].x, (int)mineVB[0].y, NULL);
			for(int vert=1; vert<mineVB.size(); ++vert)
				LineTo(surface, (int)mineVB[vert].x, (int)mineVB[vert].y);
			LineTo(surface, (int)mineVB[0].x, (int)mineVB[0].y);
		}

		SelectObject(surface, m_RedPen);
		for(int i=0; i<m_NumSweepers; i++){	//因为上一代的精英，是最先保存的，所以他们的索引，是最靠前的
			if(i == CParams::iNumElite){
				SelectObject(surface, m_OldPen);//绘制精英就选择红笔
			}
			vector<SPoint> sweeperVB = m_SweeperVB;
			m_vecSweepers[i].WorldTransform(sweeperVB);

			//绘制左半边
			MoveToEx(surface, (int)sweeperVB[0].x, (int)sweeperVB[0].y, NULL);
			for(int vert=1; vert<4; ++vert){
				LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
			}
			LineTo(surface, (int)sweeperVB[0].x, (int)sweeperVB[0].y);

			//绘制右半边
			MoveToEx(surface, (int)sweeperVB[4].x, (int)sweeperVB[4].y, NULL);
			for(int vert=5; vert<8; ++vert)
				LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
			LineTo(surface, (int)sweeperVB[4].x, (int)sweeperVB[4].y);

			MoveToEx(surface, (int)sweeperVB[8].x, (int)sweeperVB[8].y, NULL);
			LineTo(surface, (int)sweeperVB[9].x, (int)sweeperVB[9].y);

			MoveToEx(surface, (int)sweeperVB[10].x, (int)sweeperVB[10].y, NULL);

			for(int vert=11; vert<16; ++vert)
				LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
		}
		SelectObject(surface, m_OldPen);
	}else{
		PlotStats(surface);
	}
}

void CController::PlotStats(HDC surface){
	string s = "Best Fitness:          " + ftos(m_pGA->BestFitness());
	TextOut(surface, 5, 20, s.c_str(), s.size());

	s = "Average Fitness: " + ftos(m_pGA->AverageFitness());
	TextOut(surface, 5, 40, s.c_str(), s.size());

	//坐标轴的刻度
	float HSlice = (float)cxClient/(m_iGenerations+1);
	float VSlice = (float)cyClient/((m_pGA->BestFitness()+1)*2);

	float x = 0;
	m_OldPen = (HPEN)SelectObject(surface, m_RedPen);
	MoveToEx(surface, 0, cyClient, NULL);

	for(int i=0; i<m_vecBestFitness.size(); ++i){
		LineTo(surface, x, cyClient - VSlice*m_vecBestFitness[i]);
		x += HSlice;
	}
	x = 0;
	SelectObject(surface, m_BluePen);
	MoveToEx(surface, 0, cyClient, NULL);

	for(int i=0; i<m_vecAvFitness.size(); ++i){
		LineTo(surface, (int)x, (int)(cyClient - VSlice*m_vecAvFitness[i]));
		x += HSlice;
	}
	SelectObject(surface, m_OldPen);
}
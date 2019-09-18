#ifndef CMINESWEEPER_H
#define CMINESWEEPER_H

#include <vector>
#include <math.h>
#include "CNeuralNet.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"

using namespace std;

class CMinesweeper{
private:
	CNeuralNet	m_ItsBrain;
	SVector2D	m_vPosition;	//位置坐标
	SVector2D	m_vLookAt;		//方向向量
	double		m_dRotation;	//旋转角度
	double		m_dSpeed;		//速度
	double		m_lTrack, m_rTrack;	//左右履带速度
	double		m_dFitness;
	double		m_dScale;
	int			m_iClosestMine;	//最近地雷的索引

public:
	CMinesweeper();

	//更新扫雷车的位置，朝向，使用了神经网络算法
	bool		Update(vector<SVector2D> &mines);

	void		WorldTransform(vector<SPoint> &sweeper);
	SVector2D	GetClosestMine(vector<SVector2D> &objects);

	//检测是否碰撞到地雷
	int			CheckForMine(vector<SVector2D> &mines, double size);

	void		Reset();

	SVector2D	Position()const{return m_vPosition;}

	//增加分数
	void		IncrementFitness(){++m_dFitness;}

	double		Fitness()const{return m_dFitness;}
	void		PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}
	int			GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}
};

#endif
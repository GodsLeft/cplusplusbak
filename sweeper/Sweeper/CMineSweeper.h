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
	SVector2D	m_vPosition;	//λ������
	SVector2D	m_vLookAt;		//��������
	double		m_dRotation;	//��ת�Ƕ�
	double		m_dSpeed;		//�ٶ�
	double		m_lTrack, m_rTrack;	//�����Ĵ��ٶ�
	double		m_dFitness;
	double		m_dScale;
	int			m_iClosestMine;	//������׵�����

public:
	CMinesweeper();

	//����ɨ�׳���λ�ã�����ʹ�����������㷨
	bool		Update(vector<SVector2D> &mines);

	void		WorldTransform(vector<SPoint> &sweeper);
	SVector2D	GetClosestMine(vector<SVector2D> &objects);

	//����Ƿ���ײ������
	int			CheckForMine(vector<SVector2D> &mines, double size);

	void		Reset();

	SVector2D	Position()const{return m_vPosition;}

	//���ӷ���
	void		IncrementFitness(){++m_dFitness;}

	double		Fitness()const{return m_dFitness;}
	void		PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}
	int			GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}
};

#endif
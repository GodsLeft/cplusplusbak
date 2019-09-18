#ifndef CGENALG_H
#define CGENALG_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "utils.h"
#include "CParams.h"

using namespace std;

struct SGenome{
	vector<double>	vecWeights;	//�洢����
	double			dFitness;	//�û�����ķ���
	
	SGenome():dFitness(0){}
	SGenome(vector<double> w, double f):vecWeights(w), dFitness(f){}

	friend bool operator<(const SGenome& lhs, const SGenome& rhs){
		return (lhs.dFitness < rhs.dFitness);
	}
};

class CGenAlg{
private:
	vector<SGenome>		m_vecPop;//����ȫ���Ļ���
	int		m_iPopSize;		//�����ǻ�����ܸ���
	int		m_iChromoLength;//ÿ��Ⱦɫ���ж��ٸ�Ȩ��
	double	m_dTotalFitness;//�����ۺ�
	double	m_dBestFitness;	//��Ⱥ����÷���
	double	m_dAverageFitness;	//��Ⱥƽ������
	double	m_dWorstFitness;	//��Ⱥ����
	int		m_iFittestGenome;	//����������õ�Ⱦɫ��
	double	m_dMutationRate;	
	double	m_dCrossoverRate;
	int		m_cGeneration;		//���ܴ���ͳ��

	void	Crossover(const vector<double> &mum, const vector<double> &dad, vector<double> &baby1, vector<double> &baby2);
	void	Mutate(vector<double> &chromo);

	//����ѡ�����̣�
	SGenome	GetChromoRoulette();
	void	GrabNBest(int NBest, const int NumCopies, vector<SGenome> &vecPop);

	void	FitnessScaleRank();
	void	CalculateBestWorstAvTot();
	void	Reset();

public:
	CGenAlg(int popsize, double MutRat, double CrossRat, int numweights);
	vector<SGenome>	Epoch(vector<SGenome> &old_pop);

	//������Ⱥ���ж��ٸ�Ⱦɫ��
	vector<SGenome> GetChromos()const{return m_vecPop;}
	double			AverageFitness()const{return m_dTotalFitness / m_iPopSize;}
	double			BestFitness()const{return m_dBestFitness;}
};

#endif
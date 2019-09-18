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
	vector<double>	vecWeights;	//存储基因
	double			dFitness;	//该基因组的分数
	
	SGenome():dFitness(0){}
	SGenome(vector<double> w, double f):vecWeights(w), dFitness(f){}

	friend bool operator<(const SGenome& lhs, const SGenome& rhs){
		return (lhs.dFitness < rhs.dFitness);
	}
};

class CGenAlg{
private:
	vector<SGenome>		m_vecPop;//保存全部的基因
	int		m_iPopSize;		//好像是基因的总个数
	int		m_iChromoLength;//每个染色体有多少个权重
	double	m_dTotalFitness;//分数综合
	double	m_dBestFitness;	//种群的最好分数
	double	m_dAverageFitness;	//种群平均分数
	double	m_dWorstFitness;	//种群最差分
	int		m_iFittestGenome;	//持续跟踪最好的染色体
	double	m_dMutationRate;	
	double	m_dCrossoverRate;
	int		m_cGeneration;		//繁衍代数统计

	void	Crossover(const vector<double> &mum, const vector<double> &dad, vector<double> &baby1, vector<double> &baby2);
	void	Mutate(vector<double> &chromo);

	//基因选择（轮盘）
	SGenome	GetChromoRoulette();
	void	GrabNBest(int NBest, const int NumCopies, vector<SGenome> &vecPop);

	void	FitnessScaleRank();
	void	CalculateBestWorstAvTot();
	void	Reset();

public:
	CGenAlg(int popsize, double MutRat, double CrossRat, int numweights);
	vector<SGenome>	Epoch(vector<SGenome> &old_pop);

	//返回种群中有多少个染色体
	vector<SGenome> GetChromos()const{return m_vecPop;}
	double			AverageFitness()const{return m_dTotalFitness / m_iPopSize;}
	double			BestFitness()const{return m_dBestFitness;}
};

#endif
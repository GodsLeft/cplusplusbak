#include "CGenAlg.h"

CGenAlg::CGenAlg(int popsize, double MutRat, double CrossRat, int numweights):m_iPopSize(popsize),
																				m_dMutationRate(MutRat),
																				m_dCrossoverRate(CrossRat),
																				m_iChromoLength(numweights),
																				m_dTotalFitness(0),
																				m_cGeneration(0),
																				m_iFittestGenome(0),
																				m_dBestFitness(0),
																				m_dWorstFitness(99999999),
																				m_dAverageFitness(0)
{
	for(int i=0; i<m_iPopSize; ++i){
		m_vecPop.push_back(SGenome());
		for(int j=0; j<m_iChromoLength; ++j)
			m_vecPop[i].vecWeights.push_back(RandomClamped());
	}
}

//基因突变
void CGenAlg::Mutate(vector<double> &chromo){
	for(int i=0; i<chromo.size(); ++i)
		if(RandFloat() < m_dMutationRate)
			chromo[i] += (RandomClamped() * CParams::dMaxPerturbation);
}

//基因选择：优胜劣汰，适者生存
SGenome CGenAlg::GetChromoRoulette(){
	double Slice = (double)(RandFloat() * m_dTotalFitness);
	SGenome TheChosenOne;
	double	FitnessSoFar = 0;
	for(int i=0; i<m_iPopSize; ++i){
		FitnessSoFar += m_vecPop[i].dFitness;
		if(FitnessSoFar >= Slice){
			TheChosenOne = m_vecPop[i];
			break;
		}
	}
	return TheChosenOne;
}

//基因杂交
void CGenAlg::Crossover(const vector<double> &mum, const vector<double> &dad, vector<double> &baby1, vector<double> &baby2){
	if((RandFloat() > m_dCrossoverRate) || (mum == dad)){
		baby1 = mum;
		baby2 = dad;
		return;
	}
	//杂交点
	int cp = RandInt(0, m_iChromoLength - 1);
	int i;
	for(i=0; i<cp; ++i){
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}
	for(i=cp; i<mum.size(); ++i){
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
	return;
}

vector<SGenome> CGenAlg::Epoch(vector<SGenome> &old_pop){
	m_vecPop = old_pop;
	//
	Reset();
	sort(m_vecPop.begin(), m_vecPop.end());
	CalculateBestWorstAvTot();
	vector<SGenome> vecNewPop;//用来保存新的基因,最开始保存的是上一代的精英

	if(!(CParams::iNumCopiesElite * CParams::iNumElite % 2))
		GrabNBest(CParams::iNumElite, CParams::iNumCopiesElite, vecNewPop);

	while(vecNewPop.size() < m_iPopSize){
		SGenome mum = GetChromoRoulette();
		SGenome dad = GetChromoRoulette();

		vector<double>	baby1, baby2;
		Crossover(mum.vecWeights, dad.vecWeights, baby1, baby2);

		Mutate(baby1);
		Mutate(baby2);

		vecNewPop.push_back(SGenome(baby1, 0));
		vecNewPop.push_back(SGenome(baby2, 0));
	}

	m_vecPop = vecNewPop;
	return m_vecPop;
}

//放大fitness
void CGenAlg::FitnessScaleRank(){
	const int FitnessMultiplier = 1;
	for(int i=0; i<m_iPopSize; i++)
		m_vecPop[i].dFitness = i * FitnessMultiplier;

	CalculateBestWorstAvTot();
}

//NBest备份NumCopies个到下一代
void CGenAlg::GrabNBest(int NBest, const int NumCopies, vector<SGenome> &Pop){
	while(NBest--){
		for(int i=0; i<NumCopies; ++i)
			Pop.push_back(m_vecPop[(m_iPopSize-1) - NBest]);
	}
}

void CGenAlg::CalculateBestWorstAvTot(){
	m_dTotalFitness = 0;
	double HighestSoFar = 0;	//保存最高的fitness
	double LowestSoFar = 99999999;
	for(int i=0; i<m_iPopSize; ++i){
		if(m_vecPop[i].dFitness > HighestSoFar){
			HighestSoFar		= m_vecPop[i].dFitness;
			m_iFittestGenome	= i;
			m_dBestFitness		= HighestSoFar;
		}

		if(m_vecPop[i].dFitness < LowestSoFar){
			LowestSoFar		= m_vecPop[i].dFitness;
			m_dWorstFitness	= LowestSoFar;
		}

		m_dTotalFitness += m_vecPop[i].dFitness;
	}
	m_dAverageFitness = m_dTotalFitness / m_iPopSize;
}

void CGenAlg::Reset(){
	m_dTotalFitness		= 0;
	m_dBestFitness		= 0;
	m_dWorstFitness		= 99999999;
	m_dAverageFitness	= 0;
}
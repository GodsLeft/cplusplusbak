#ifndef CGABOB_H
#define CGABOB_H

#include <vector>
#include <sstream>

#include "defines.h"
#include "CBobsMap.h"
#include "utils.h"

using namespace std;

struct SGenome{
	vector<int>	vecBits;
	double		dFitness;

	SGenome():dFitness(0){}
	SGenome(const int num_bits):dFitness(0){
		for(int i=0; i<num_bits; ++i){
			vecBits.push_back(RandInt(0, 1));
		}
	}
};

class CgaBob{
private:
	vector<SGenome>	m_vecGenomes;	//基因组群体
	int		m_iPopSize;				//群体大小
	double	m_dCrossoverRate;
	double	m_dMutationRate;

	int		m_iChromoLength;		//每个染色有多少个bit
	int		m_iGeneLength;			//每个基因有多少个bit
	int		m_iFittestGenome;
	
	double	m_dBestFitnessScore;
	double	m_dTotalFitnessScore;

	int		m_iGeneration;

	CBobsMap	m_BobsMap;		//地图实例
	CBobsMap	m_BobsBrain;

	bool	m_bBusy;

	void	Mutate(vector<int> &vecBits);
	void	Crossover(const vector<int> &num, const vector<int> &dad, vector<int> &baby1, vector<int> &baby2);

	SGenome&	RouletteWheelSelection();
	void	UpdateFitnessScores();
	vector<int>	Decode(const vector<int> &bits);
	int		BinToInt(const vector<int> &v);
	void	CreateStartPopulation();

public:
	CgaBob(double cross_rat, double mut_rat, int pop_size, int num_bits, int gene_len):
	  m_dCrossoverRate(cross_rat),
		  m_dMutationRate(mut_rat),
		  m_iPopSize(pop_size),
		  m_iChromoLength(num_bits),
		  m_dTotalFitnessScore(0.0),
		  m_iGeneration(0),
		  m_iGeneLength(gene_len),
		  m_bBusy(false)
	  {
		  CreateStartPopulation();
	  }

	  void	Run(HWND hwnd);
	  void	Render(int cxClient, int cyClient, HDC surface);
	  void	Epoch();
	  

	  int	Generation(){return m_iGeneration;}
	  int	GetFittest(){return m_iFittestGenome;}

	  bool	Started(){return m_bBusy;}
	  void	Stop(){m_bBusy = false;}
};


#endif
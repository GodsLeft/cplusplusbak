#include "CgaBob.h"

//轮盘游戏
SGenome& CgaBob::RouletteWheelSelection(){
	double fSlice = RandFloat()*m_dTotalFitnessScore;
	double cfTotal = 0.0;
	int SelectedGenome	= 0;

	for(int i=0; i<m_iPopSize; ++i){
		cfTotal += m_vecGenomes[i].dFitness;
		if(cfTotal > fSlice){
			SelectedGenome = i;
			break;
		}
	}

	return m_vecGenomes[SelectedGenome];
}

//基因突变
void CgaBob::Mutate(vector<int> &vecBits){
	for(int curBit=0; curBit<vecBits.size(); curBit++){
		if(RandFloat() < m_dMutationRate){
			vecBits[curBit] = !vecBits[curBit];
		}
	}
}

//杂交
void CgaBob::Crossover(const vector<int> &mum, const vector<int> &dad, vector<int> &baby1, vector<int> &baby2){
	if( (RandFloat() > m_dCrossoverRate) || (mum == dad)){
		baby1 = mum;
		baby2 = dad;
		return;
	}

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
}

void CgaBob::Run(HWND hwnd){
	CreateStartPopulation();
	m_bBusy = true;
}

void CgaBob::CreateStartPopulation(){
	m_vecGenomes.clear();
	for(int i=0; i<m_iPopSize; i++){
		m_vecGenomes.push_back(SGenome(m_iChromoLength));
	}

	m_iGeneration		= 0;
	m_iFittestGenome	= 0;
	m_dBestFitnessScore	= 0;
	m_dTotalFitnessScore	= 0;
}

void CgaBob::Epoch(){
	UpdateFitnessScores();
	int NewBabies = 0;
	vector<SGenome> vecBabyGenomes;

	while(NewBabies < m_iPopSize){
		SGenome mum = RouletteWheelSelection();
		SGenome dad = RouletteWheelSelection();
		
		SGenome baby1, baby2;
		Crossover(mum.vecBits, dad.vecBits, baby1.vecBits, baby2.vecBits);

		Mutate(baby1.vecBits);
		Mutate(baby2.vecBits);

		vecBabyGenomes.push_back(baby1);
		vecBabyGenomes.push_back(baby2);

		NewBabies += 2;
	}

	m_vecGenomes = vecBabyGenomes;
	++m_iGeneration;
}

void CgaBob::UpdateFitnessScores(){
	m_iFittestGenome		= 0;
	m_dBestFitnessScore		= 0;
	m_dTotalFitnessScore	= 0;

	CBobsMap TempMemory;

	for(int i=0; i<m_iPopSize; ++i){
		vector<int> vecDirections = Decode(m_vecGenomes[i].vecBits);
		m_vecGenomes[i].dFitness = m_BobsMap.TestRoute(vecDirections, TempMemory);
		m_dTotalFitnessScore += m_vecGenomes[i].dFitness;
		if(m_vecGenomes[i].dFitness > m_dBestFitnessScore){
			m_dBestFitnessScore = m_vecGenomes[i].dFitness;
			m_iFittestGenome = i;
			m_BobsBrain	= TempMemory;

			if(m_vecGenomes[i].dFitness == 1){
				m_bBusy = false;
			}
		}
		TempMemory.ResetMemory();
	}
}

vector<int> CgaBob::Decode(const vector<int> &bits){
	vector<int> directions;
	for(int gene=0; gene < bits.size(); gene += m_iGeneLength){
		vector<int> ThisGene;
		for(int bit=0; bit<m_iGeneLength; ++bit){
			ThisGene.push_back(bits[gene+bit]);
		}
		directions.push_back(BinToInt(ThisGene));
	}
	return directions;
}

int CgaBob::BinToInt(const vector<int> &vec){
	int val = 0;
	int multiplier = 1;

	for(int cBit=vec.size(); cBit>0; cBit--){
		val += vec[cBit-1] * multiplier;
		multiplier *= 2;
	}
	return val;
}

void CgaBob::Render(int cxClient, int cyClient, HDC surface){
	m_BobsMap.Render(cxClient, cyClient, surface);
	m_BobsBrain.MemoryRender(cxClient, cyClient, surface);
	string s = "Generation: "+itos(m_iGeneration);
	TextOut(surface, 5, 0, s.c_str(), s.size());

	if(!m_bBusy){
		string Start = "Press Return to start a new run";
		TextOut(surface, cxClient/2 - (Start.size()*3),cyClient - 20, Start.c_str(), Start.size());
	}else{
		string Start = "space to stop";
		TextOut(surface, cxClient/2-(Start.size()*3), cyClient - 20, Start.c_str(), Start.size());
	}
}
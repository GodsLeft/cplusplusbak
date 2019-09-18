#ifndef CNEURALNET_H
#define CNEURALNET_H

#include <vector>
#include <fstream>
#include <math.h>

#include "utils.h"
#include "CParams.h"

using namespace std;

//��ϸ��
struct SNeuron{
	int				m_NumInputs;//�񾭵�Ԫ�������
	vector<double>	m_vecWeight;//�񾭵�Ԫ����Ȩ��
	SNeuron(int NumInputs);
};

//�������
struct SNeuronLayer{
	int				m_NumNeurons;	//�ò��ж��ٸ��񾭵�Ԫ
	vector<SNeuron>	m_vecNeurons;	//�洢�ò���񾭵�Ԫ
	SNeuronLayer(int NumNeurons, int NumInputsPerNeuron);
};

class CNeuralNet{
private:
	int			m_NumInputs;
	int			m_NumOutputs;
	int			m_NumHiddenLayers;
	int			m_NeuronsPerHiddenLyr;//��ÿ�����ز��ϸ������,����һ�����ز���������

	vector<SNeuronLayer>	m_vecLayers;

public:
	CNeuralNet();
	void			CreateNet();
	vector<double>	GetWeights()const;
	int				GetNumberOfWeights()const;
	void			PutWeights(vector<double> &weights);
	vector<double>	Update(vector<double> &inputs);		//��������������

	inline double	Sigmoid(double activation, double response);
};

#endif
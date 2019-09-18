#ifndef CNEURALNET_H
#define CNEURALNET_H

#include <vector>
#include <fstream>
#include <math.h>

#include "utils.h"
#include "CParams.h"

using namespace std;

//神经细胞
struct SNeuron{
	int				m_NumInputs;//神经单元输入个数
	vector<double>	m_vecWeight;//神经单元输入权重
	SNeuron(int NumInputs);
};

//神经网络层
struct SNeuronLayer{
	int				m_NumNeurons;	//该层有多少个神经单元
	vector<SNeuron>	m_vecNeurons;	//存储该层的神经单元
	SNeuronLayer(int NumNeurons, int NumInputsPerNeuron);
};

class CNeuralNet{
private:
	int			m_NumInputs;
	int			m_NumOutputs;
	int			m_NumHiddenLayers;
	int			m_NeuronsPerHiddenLyr;//是每个隐藏层的细胞个数,是下一个隐藏层的输入个数

	vector<SNeuronLayer>	m_vecLayers;

public:
	CNeuralNet();
	void			CreateNet();
	vector<double>	GetWeights()const;
	int				GetNumberOfWeights()const;
	void			PutWeights(vector<double> &weights);
	vector<double>	Update(vector<double> &inputs);		//根据输入计算输出

	inline double	Sigmoid(double activation, double response);
};

#endif
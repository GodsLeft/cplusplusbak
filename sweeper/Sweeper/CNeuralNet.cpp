#include "CNeuralNet.h"

//初始化神经单元，权重随机
SNeuron::SNeuron(int NumInputs):m_NumInputs(NumInputs+1){
	for(int i=0; i<NumInputs+1; ++i)
		m_vecWeight.push_back(RandomClamped());
}

//初始化一个神经网络层，参数:神经单元个数，每个神经单元输入个数
SNeuronLayer::SNeuronLayer(int NumNeurons, int NumInputsPerNeuron):m_NumNeurons(NumNeurons){
	for(int i=0; i<NumNeurons; ++i)
		m_vecNeurons.push_back(SNeuron(NumInputsPerNeuron));
}

//神经网络初始化
CNeuralNet::CNeuralNet(){
	m_NumInputs			= CParams::iNumInputs;
	m_NumOutputs		= CParams::iNumOutputs;
	m_NumHiddenLayers	= CParams::iNumHidden;
	m_NeuronsPerHiddenLyr	= CParams::iNeuronsPerHiddenLayer;

	CreateNet();
}

//很奇怪，这里没有将网络各层之间连接起来？
void CNeuralNet::CreateNet(){
	if(m_NumHiddenLayers > 0){
		//创建第一个隐藏层
		m_vecLayers.push_back(SNeuronLayer(m_NeuronsPerHiddenLyr, m_NumInputs));
		//创建其余的隐藏层
		for(int i=0; i<m_NumHiddenLayers-1; ++i){
			m_vecLayers.push_back(SNeuronLayer(m_NeuronsPerHiddenLyr, m_NeuronsPerHiddenLyr));
		}
		//输出层
		m_vecLayers.push_back(SNeuronLayer(m_NumOutputs, m_NeuronsPerHiddenLyr));
	}else{
		m_vecLayers.push_back(SNeuronLayer(m_NumOutputs, m_NumInputs));
	}
}

vector<double> CNeuralNet::GetWeights()const{
	vector<double> weights;
	//每一层
	for(int i=0; i<m_NumHiddenLayers+1; ++i)
		//每个神经单元
		for(int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
			//每个权重
			for(int k=0; k<m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
				weights.push_back(m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k]);

	return weights;
}

void CNeuralNet::PutWeights(vector<double> &weights){
	int cWeight = 0;
	for(int i=0; i<m_NumHiddenLayers+1; ++i)
		for(int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
			for(int k=0; k<m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
				m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] = weights[cWeight++];
	return;
}

int CNeuralNet::GetNumberOfWeights()const{
	int weights = 0;
	for(int i=0; i<m_NumHiddenLayers + 1; ++i)
		for(int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
			for(int k=0; k<m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
				weights++;
	return weights;
}

vector<double> CNeuralNet::Update(vector<double> &inputs){
	vector<double> outputs;
	int cWeight = 0;

	//如果输入个数不对，直接输出空向量
	if(inputs.size() != m_NumInputs){
		return outputs;
	}

	for(int i=0; i<m_NumHiddenLayers+1; ++i){
		//当不是第一层的时候，清空输入
		if(i>0){
			inputs = outputs;
		}
		outputs.clear();
		cWeight = 0;
		for(int j=0; j<m_vecLayers[i].m_NumNeurons; ++j){
			double netinput = 0;
			int NumInputs = m_vecLayers[i].m_vecNeurons[j].m_NumInputs;//该层神经单元的输入个数
			for(int k=0; k<NumInputs-1; ++k){
				netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] * inputs[cWeight++];
			}
			netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[NumInputs-1] * CParams::dBias;

			outputs.push_back(Sigmoid(netinput, CParams::dActivationResponse));
			cWeight = 0;
		}
	}
	return outputs;
}

double CNeuralNet::Sigmoid(double netinput, double response){
	return (1/(1 + exp(-netinput / response)));
}

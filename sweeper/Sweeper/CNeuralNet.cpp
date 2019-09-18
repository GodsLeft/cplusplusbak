#include "CNeuralNet.h"

//��ʼ���񾭵�Ԫ��Ȩ�����
SNeuron::SNeuron(int NumInputs):m_NumInputs(NumInputs+1){
	for(int i=0; i<NumInputs+1; ++i)
		m_vecWeight.push_back(RandomClamped());
}

//��ʼ��һ��������㣬����:�񾭵�Ԫ������ÿ���񾭵�Ԫ�������
SNeuronLayer::SNeuronLayer(int NumNeurons, int NumInputsPerNeuron):m_NumNeurons(NumNeurons){
	for(int i=0; i<NumNeurons; ++i)
		m_vecNeurons.push_back(SNeuron(NumInputsPerNeuron));
}

//�������ʼ��
CNeuralNet::CNeuralNet(){
	m_NumInputs			= CParams::iNumInputs;
	m_NumOutputs		= CParams::iNumOutputs;
	m_NumHiddenLayers	= CParams::iNumHidden;
	m_NeuronsPerHiddenLyr	= CParams::iNeuronsPerHiddenLayer;

	CreateNet();
}

//����֣�����û�н��������֮������������
void CNeuralNet::CreateNet(){
	if(m_NumHiddenLayers > 0){
		//������һ�����ز�
		m_vecLayers.push_back(SNeuronLayer(m_NeuronsPerHiddenLyr, m_NumInputs));
		//������������ز�
		for(int i=0; i<m_NumHiddenLayers-1; ++i){
			m_vecLayers.push_back(SNeuronLayer(m_NeuronsPerHiddenLyr, m_NeuronsPerHiddenLyr));
		}
		//�����
		m_vecLayers.push_back(SNeuronLayer(m_NumOutputs, m_NeuronsPerHiddenLyr));
	}else{
		m_vecLayers.push_back(SNeuronLayer(m_NumOutputs, m_NumInputs));
	}
}

vector<double> CNeuralNet::GetWeights()const{
	vector<double> weights;
	//ÿһ��
	for(int i=0; i<m_NumHiddenLayers+1; ++i)
		//ÿ���񾭵�Ԫ
		for(int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
			//ÿ��Ȩ��
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

	//�������������ԣ�ֱ�����������
	if(inputs.size() != m_NumInputs){
		return outputs;
	}

	for(int i=0; i<m_NumHiddenLayers+1; ++i){
		//�����ǵ�һ���ʱ���������
		if(i>0){
			inputs = outputs;
		}
		outputs.clear();
		cWeight = 0;
		for(int j=0; j<m_vecLayers[i].m_NumNeurons; ++j){
			double netinput = 0;
			int NumInputs = m_vecLayers[i].m_vecNeurons[j].m_NumInputs;//�ò��񾭵�Ԫ���������
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

#include "CMineSweeper.h"

CMinesweeper::CMinesweeper():m_dRotation(RandFloat()*CParams::dTwoPi),
								m_lTrack(0.16),
								m_rTrack(0.16),
								m_dFitness(0),
								m_dScale(CParams::iSweeperScale),
								m_iClosestMine(0)
{
	m_vPosition = SVector2D((RandFloat() * CParams::WindowWidth), (RandFloat() * CParams::WindowHeight));
}

void CMinesweeper::Reset(){
	m_vPosition = SVector2D((RandFloat() * CParams::WindowWidth), (RandFloat() * CParams::WindowHeight));
	m_dFitness = 0;
	m_dRotation = RandFloat() * CParams::dTwoPi;
	return;
}

void CMinesweeper::WorldTransform(vector<SPoint> &sweeper){
	C2DMatrix matTransform;
	matTransform.Scale(m_dScale, m_dScale);
	matTransform.Rotate(m_dRotation);
	matTransform.Translate(m_vPosition.x, m_vPosition.y);
	matTransform.TransformSPoints(sweeper);
}

//根据扫雷车的输入，算出输出
bool CMinesweeper::Update(vector<SVector2D> &mines){
	vector<double> inputs;
	SVector2D vClosestMine = GetClosestMine(mines);
	Vec2DNormalize(vClosestMine);
	inputs.push_back(vClosestMine.x);
	inputs.push_back(vClosestMine.y);

	inputs.push_back(m_vLookAt.x);
	inputs.push_back(m_vLookAt.y);

	vector<double> output = m_ItsBrain.Update(inputs);
	if(output.size() < CParams::iNumOutputs){
		return false;
	}

	m_lTrack = output[0];
	m_rTrack = output[1];

	double RotForce = m_lTrack - m_rTrack;	//旋转力
	Clamp(RotForce, -CParams::dMaxTurnRate, CParams::dMaxTurnRate);
	m_dRotation += RotForce;
	m_dSpeed = (m_lTrack + m_rTrack);

	m_vLookAt.x = -sin(m_dRotation);
	m_vLookAt.y = cos(m_dRotation);

	m_vPosition += (m_vLookAt * m_dSpeed);

	if(m_vPosition.x > CParams::WindowWidth) m_vPosition.x = 0;
	if(m_vPosition.x < 0) m_vPosition.x = CParams::WindowWidth;
	if(m_vPosition.y > CParams::WindowHeight) m_vPosition.y = 0;
	if(m_vPosition.y < 0) m_vPosition.y = CParams::WindowHeight;
	return true;
}

SVector2D CMinesweeper::GetClosestMine(vector<SVector2D> &mines){
	double		closest_so_far = 99999999;
	SVector2D	vClosestObject(0, 0);
	for(int i=0; i<mines.size(); i++){
		double len_to_object = Vec2DLength(mines[i] - m_vPosition);
		if(len_to_object < closest_so_far){
			closest_so_far = len_to_object;
			vClosestObject = m_vPosition - mines[i];
			m_iClosestMine = i;
		}
	}
	return vClosestObject;
}

//检测碰撞
int CMinesweeper::CheckForMine(vector<SVector2D> &mines, double size){
	SVector2D DistToObject = m_vPosition - mines[m_iClosestMine];
	if(Vec2DLength(DistToObject) < (size + 5))
		return m_iClosestMine;

	return -1;
}
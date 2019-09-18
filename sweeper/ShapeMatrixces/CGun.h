#ifndef CGUN_H
#define CGUN_H

#include <vector>
#include <windows.h>

#include "defines.h"
#include "utils.h"
#include "C2DMatrix.h"

using namespace std;

class CGun{
public:
	double		m_dPosX,
				m_dPosY;

	double		m_dRotation;

	double		m_dScale;

	vector<SPoint>	m_vecGunVB;
	vector<SPoint>	m_vecGunVBTrans;

	CGun(double x, double y, double scale, double rot);

	void WorldTransform();
	void Render(HDC &surface);
	void Update();
};

#endif
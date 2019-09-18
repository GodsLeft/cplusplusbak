#ifndef CBOBSMAP_H
#define CBOBSMAP_H

#include "stdlib.h"
#include "windows.h"
#include <vector>

#include "defines.h"
using namespace std;

class CBobsMap{
private:
	static const int	map[MAP_HEIGHT][MAP_WIDTH];

	static const int	m_iMapWidth;
	static const int	m_iMapHeight;

	static const int	m_iStartX;
	static const int	m_iStartY;

	static const int	m_iEndX;
	static const int	m_iEndY;

public:
	int		memory[MAP_HEIGHT][MAP_WIDTH];
	CBobsMap(){
		ResetMemory();
	}

	double TestRoute(const vector<int> &vecPath, CBobsMap &memory);

	void Render(const int cxClient, const int cyClient, HDC surface);

	void MemoryRender(const int cxClient, const int cyClient, HDC surface);

	void ResetMemory();
};

#endif
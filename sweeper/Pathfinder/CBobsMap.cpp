#include "CBobsMap.h"

const int CBobsMap::map[MAP_HEIGHT][MAP_WIDTH] = {
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5,
1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

const int CBobsMap::m_iMapHeight = MAP_HEIGHT;
const int CBobsMap::m_iMapWidth = MAP_WIDTH;

const int CBobsMap::m_iStartX = 14;
const int CBobsMap::m_iStartY = 7;

const int CBobsMap::m_iEndX = 0;
const int CBobsMap::m_iEndY = 2;

void CBobsMap::Render(const int cxClient, const int cyClient, HDC surface){
	const int border = 20;
	int BlockSizeX = (cxClient - 2*border)/m_iMapWidth;
	int BlockSizeY = (cyClient - 2*border)/m_iMapHeight;

	HBRUSH	BlackBrush, RedBrush, OldBrush;
	HPEN	NullPen, OldPen;

	NullPen = (HPEN)GetStockObject(NULL_PEN);
	BlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	RedBrush = CreateSolidBrush(RGB(255,0,0));

	OldBrush	= (HBRUSH)SelectObject(surface, BlackBrush);
	OldPen		= (HPEN)SelectObject(surface, NullPen);

	for(int y = 0; y<m_iMapHeight; ++y){
		for(int x=0; x<m_iMapWidth; ++x){
			int left	= border + (BlockSizeX * x);
			int right	= left + BlockSizeX;

			int top		= border + (BlockSizeY * y);
			int bottom	= top + BlockSizeY;

			if(map[y][x] == 1){
				SelectObject(surface, BlackBrush);
				Rectangle(surface, left, top, right, bottom);
			}

			if((map[y][x] == 5) || (map[y][x] == 8)){
				SelectObject(surface, RedBrush);
				Rectangle(surface, left, top, right, bottom);
			}
		}
	}

	SelectObject(surface, OldBrush);
	SelectObject(surface, OldPen);
}

void CBobsMap::MemoryRender(const int cxClient, const int cyClient, HDC surface){
	const int border = 20;
	int BlockSizeX = (cxClient - 2*border)/m_iMapWidth;
	int BlockSizeY = (cyClient - 2*border)/m_iMapHeight;

	HBRUSH	GreyBrush, OldBrush;
	HPEN	NullPen, OldPen;

	GreyBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	NullPen	= (HPEN)GetStockObject(NULL_PEN);

	OldBrush	= (HBRUSH)SelectObject(surface, GreyBrush);
	OldPen		= (HPEN)SelectObject(surface, NullPen);

	for(int y=0; y<m_iMapHeight; ++y){
		for(int x=0; x<m_iMapWidth; ++x){
			int left	= border + (BlockSizeX * x);
			int right	= left + BlockSizeX;

			int top		= border + (BlockSizeY * y);
			int bottom	= top + BlockSizeY;

			if(memory[y][x] == 1){
				Rectangle(surface, left, top, right, bottom);
			}
		}
	}

	SelectObject(surface, OldBrush);
	SelectObject(surface, OldPen);
}

double CBobsMap::TestRoute(const vector<int> &vecPath, CBobsMap &Bobs){
	int posX = m_iStartX;
	int posY = m_iStartY;

	for(int dir=0; dir<vecPath.size(); ++dir){
		int NextDir = vecPath[dir];
		switch(vecPath[dir]){
		case 0:{
			if(((posY-1)<0) || (map[posY-1][posX] == 1)){
				break;
			}else{
				posY -= 1;
			}
		}
		break;

		case 1:{
			if( ((posY+1) >= m_iMapHeight) || (map[posY+1][posX] == 1) ){
				break;
			}else{
				posY += 1;
			}
		}
			break;

		case 2:{
			if( ((posX+1) >= m_iMapWidth) || (map[posY][posX+1] == 1) ){
				break;
			}else{
				posX += 1;
			}
		}
			break;

		case 3:{
			if( ((posX-1) < 0) || (map[posY][posX-1] == 1)){
				break;
			}else{
				posX -= 1;
			}
		}
			   break;
		}

		Bobs.memory[posY][posX] = 1;
	}

	int DiffX = abs(posX - m_iEndX);
	int DiffY = abs(posY - m_iEndY);

	return 1/(double)(DiffX+DiffY+1);
}

void CBobsMap::ResetMemory(){
	for(int y=0; y<m_iMapHeight; ++y){
		for(int x=0; x<m_iMapWidth; ++x){
			memory[y][x] = 0;
		}
	}
}
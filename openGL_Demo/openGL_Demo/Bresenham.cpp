#include "line.h"

//|k|<1.0
void lineBres_lk(int x0, int y0, int xEnd,int yEnd){
	int dx=fabs(double(xEnd-x0)), dy=fabs(double(yEnd-y0));
	if(dy<=dx){
		int p=2*dy - dx;
		int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
		int x, y;
		//如果始点位置高于重点位置
		if(x0 > xEnd){
			x = xEnd;
			y = yEnd;
			xEnd = x0;
		}else{
			x = x0; 
			y = y0;
		}
		setPixel(x,y);

		while(x < xEnd){
			x++;
			if(p < 0)
				p += twoDy;
			else{
				y++;
				p += twoDyMinusDx;
			}
			setPixel(x,y);
		}
		printf("Bresenham Function!!\n");
	}else{
		int p=2*dx - dy;
		int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
		int x, y;
		//如果始点位置高于重点位置
		if(y0 > yEnd){
			x = xEnd;
			y = yEnd;
			yEnd = y0;
		}else{
			x = x0; 
			y = y0;
		}
		setPixel(x,y);

		while(y < yEnd){
			y++;
			if(p < 0)
				p += twoDx;
			else{
				x++;
				p += twoDxMinusDy;
			}
			setPixel(x,y);
		}
		//printf("zhu\n");
	}
}
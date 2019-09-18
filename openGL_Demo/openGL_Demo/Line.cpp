#include "line.h"


void Line::setEnthesis(int x,int y,int xE,int yE){
		x0=x;
		y0=y;
		xEnd=xE;
		yEnd=yE;
}
void Line::setEnthPoint(Point a,Point b){
	x0=a.X;
	y0=a.Y;
	xEnd=b.X;
	yEnd=b.Y;
}
//P(k+1)-P(k)=2det(y)-2det(x)[y(k+1)-y(k)]:决策参数
void Line::lineBres(){
	int dx=fabs(double(xEnd-x0)), dy=fabs(double(yEnd-y0));
	if(dx==0){
		if(y0>yEnd){
			int temp;
			temp=y0;
			y0=yEnd;
			yEnd=temp;
		}else{
			for(int i=0;i<(yEnd-y0);i++){
				setPixel(x0,y0+i);
			}
		}
	}
	if(dy==0){
		if(x0>xEnd){
			int temp;
			temp=x0;
			x0=xEnd;
			xEnd=temp;
		}else{
			for(int i=0;i<(xEnd-x0);i++){
				setPixel(x0+i,y0);
			}
		}
	}
	if(dy<=dx &&(dx!=0 || dy!=0)){
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
	}
}
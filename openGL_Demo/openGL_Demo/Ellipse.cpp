#include "line.h"
extern queue<Point> Ellque;
int Ellquesize;
void Ellipse::setEllipse(int x,int y,int a,int b){
	center.X = x;
	center.Y = y;
	Rx = a;
	Ry = b;
}

void Ellipse::ellipseMid(){
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2=2*Rx2;
	int twoRy2=2*Ry2;
	int p;
	int x=0;
	int y=Ry;
	int px=0;
	int py=twoRx2*y;
	ellipsePlotPoints(center.X,center.Y,x,y);
	p=round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while(px < py){
		x++;
		px += twoRy2;
		if(p < 0)
			p += Ry2 + px;
		else{
			y--;
			py -= twoRx2;
			p += Ry2 + px -py;
		}
		ellipsePlotPoints(center.X,center.Y,x,y);
	}

	p = round(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while(y > 0){
		y--;
		py -= twoRx2;
		if(p > 0)
			p += Rx2 - py;
		else{
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints(center.X,center.Y,x,y);
	}
	Ellquesize = Ellque.size();
}

void Ellipse::ellipsePlotPoints(int xCenter,int yCenter,int x,int y){
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);

	//为了将所有的椭圆上的点保存在队列中，没用了
	/*Point a;
	a.X=xCenter + x;a.Y=yCenter + y;
	Ellque.push(a);
	a.X=xCenter - x;a.Y=yCenter + y;
	Ellque.push(a);
	a.X=xCenter + x;a.Y=yCenter - y;
	Ellque.push(a);
	a.X=xCenter - x;a.Y=yCenter - y;
	Ellque.push(a);*/
}
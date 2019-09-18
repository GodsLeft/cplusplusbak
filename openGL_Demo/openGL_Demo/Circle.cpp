#include "line.h"

void Circle::setCircle(Point center,int R){
	a.X=center.X;
	a.Y=center.Y;
	radius=R;
};

void Circle::setPosition(Point position){
	a.X=position.X;
	a.Y=position.Y;
}

void Circle::setRadius(int R){
	radius=R;
}

void Circle::circleMid(){
	Point circPt;
	int p = 1 - radius;

	circPt.X=0;
	circPt.Y=radius;
	circlePlotPoints(a.X, a.Y, circPt);

	while(circPt.X<circPt.Y){
		circPt.X++;
		if(p < 0)
			p += 2 * circPt.X + 1;
		else{
			circPt.Y--;
			p += 2 * (circPt.X - circPt.Y) + 1;
		}
		circlePlotPoints(a.X,a.Y,circPt);
	}
}

void Circle::circlePlotPoints(int xc, int yc, Point circPt){
	setPixel(xc + circPt.X, yc + circPt.Y);
	setPixel(xc - circPt.X, yc + circPt.Y);
	setPixel(xc + circPt.X, yc - circPt.Y);
	setPixel(xc - circPt.X, yc - circPt.Y);

	setPixel(xc + circPt.Y, yc + circPt.X);
	setPixel(xc - circPt.Y, yc + circPt.X);
	setPixel(xc + circPt.Y, yc - circPt.X);
	setPixel(xc - circPt.Y, yc - circPt.X);
}

Point Circle::getPosition(){
	Point temp;
	temp.X=a.X;
	temp.Y=a.Y;
	return temp;
}

float Circle::getRadius(){
	return radius;
}
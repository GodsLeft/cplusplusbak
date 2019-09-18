#include "line.h"

class screenPt{
private:
	GLint x,y;
public:
	screenPt(){			//构造函数
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue){
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getX() const {
		return x;
	}
	GLint getY() const {
		return y;
	}
	void incrementx(){
		x++;
	}
	void decrementy(){
		y--;
	}
};
//函数声明
void circlePlotPoints(GLint,GLint,screenPt);

void circleMidpoint(GLint xc,GLint yc,GLint radius){
	screenPt circPt;		//声明一个圆上的点
	GLint p = 1 - radius;

	circPt.setCoords(0, radius);	//设置圆的最高点

	circlePlotPoints(xc,yc,circPt);

	while(circPt.getX() < circPt.getY()){
		circPt.incrementx();
		if(p < 0)
			p += 2 * circPt.getX() + 1;
		else{
			circPt.decrementy();
			p += 2 * (circPt.getX() - circPt.getY()) + 1;
		}
		circlePlotPoints(xc,yc,circPt);
	}
}

//每一个要绘的点，都有8个点与之对应
void circlePlotPoints(GLint xc, GLint yc, screenPt circPt){
	setPixel(xc + circPt.getX(), yc + circPt.getY());
	setPixel(xc - circPt.getX(), yc + circPt.getY());
	setPixel(xc + circPt.getX(), yc - circPt.getY());
	setPixel(xc - circPt.getX(), yc - circPt.getY());

	setPixel(xc + circPt.getY(), yc + circPt.getX());
	setPixel(xc - circPt.getY(), yc + circPt.getX());
	setPixel(xc + circPt.getY(), yc - circPt.getX());
	setPixel(xc - circPt.getY(), yc - circPt.getX());
}
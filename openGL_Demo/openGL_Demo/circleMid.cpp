#include "line.h"

class screenPt{
private:
	GLint x,y;
public:
	screenPt(){			//���캯��
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
//��������
void circlePlotPoints(GLint,GLint,screenPt);

void circleMidpoint(GLint xc,GLint yc,GLint radius){
	screenPt circPt;		//����һ��Բ�ϵĵ�
	GLint p = 1 - radius;

	circPt.setCoords(0, radius);	//����Բ����ߵ�

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

//ÿһ��Ҫ��ĵ㣬����8������֮��Ӧ
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
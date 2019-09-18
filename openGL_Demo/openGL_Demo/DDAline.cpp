#include "line.h"

void lineDDA(int x0,int y0,int xEnd,int yEnd){
	int dx = xEnd - x0, dy = yEnd - y0, steps, k;
	float xIncrement, yIncrement, x = x0, y = y0;

	if(fabs(double(dx)) > fabs(double(dy)))
		steps = fabs(double(dx));
	else
		steps = fabs(double (dy));
	xIncrement = float(dx)/float(steps);
	yIncrement = float(dy)/float(steps);

	setPixel(round(x),round(y));	//绘制第一个点
	for(k = 0; k < steps; k++){
		x += xIncrement;
		y += yIncrement;
		setPixel(round(x),round(y));
	}
}
//这里openGL并不会直接画出来 而是等到缓冲区满或者glFlush
void setPixel(int x,int y){
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

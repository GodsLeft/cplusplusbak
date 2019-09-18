#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <queue>
using namespace std;


inline int round(const float a){return int (a+0.5);}

struct Point{
	int X;
	int Y;
};


void setPixel(int x,int y);


void lineDDA(int x0,int y0,int xEnd,int yEnd);
void lineBres_lk(int x0, int y0, int xEnd,int yEnd);

void circleMidpoint(GLint xc,GLint yc,GLint radius);



class Line{
private:
	int x0, y0, xEnd, yEnd;
public:
	Line(int x=0,int y=0,int xE=10,int yE=10){
		x0=x;
		y0=y;
		xEnd=xE;
		yEnd=yE;
	}

	void setEnthesis(int x,int y,int xE,int yE);
	void setEnthPoint(Point a,Point b);
	void lineBres();
};

class Circle{
private:
	Point a;
	int radius;
public:
	Circle(int x0 = 50,int y0 = 50, int R=50){
		a.X = x0;
		a.Y = y0;
		radius = R;
	}

	void setCircle(Point center,int R);
	void setPosition(Point position);
	void Circle::setRadius(int R);
	void circlePlotPoints(GLint xc, GLint yc, Point circPt);
	void circleMid();
	float getRadius();
	Point getPosition();
};

class Ellipse{
private:
	Point center;
	int Rx,Ry;
public:
	Ellipse(int x = 0,int y = 0,int a = 20,int b = 10){
		center.X=x;
		center.Y=y;
		Rx=a;
		Ry=b;
	}
	void setEllipse(int x,int y,int a,int b);
	void ellipseMid();
	void ellipsePlotPoints(int xCenter,int yCenter,int x,int y);
};

class Bullet{
private:
	Circle circ;
	Point bp;
	float vx;
	float vy;
public:
	Bullet(int radius=20);
	void bulletdraw();
	void BorderDet();
	float getVx();
	float getVy();
	void setV(float velx,float vely);
	Circle getCirc();
	Point getPosition();
};


class Matrix3x3{
private:
	float matrix[3][3];
public:
	Matrix3x3(){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				matrix[i][j]=0;
			}
		}
	}
	float getElem(int x,int y);
	void setElem(int x,int y,float value);
	void setAllElem(float a[3][3]);
	void setTrM(float x,float y);
	void setRotM(float angle);
	void setScaleM(float sx,float sy);
	Matrix3x3 operator + (Matrix3x3 M);
	Matrix3x3 operator - (Matrix3x3 M);
	Matrix3x3 operator * (Matrix3x3 M);
	Matrix3x3 operator / (Matrix3x3 M);
};

class Matrix3x1{
private:
	float matrix[3];
public:
	float getElem(int x);
	Point getPoint();
	void setElem(int x,int value);
	void setAllElem(float a[]);
	void setAllElem1(float x1,float x2,float x3);
	void setAllElem2(Point a,float x3 = 1);
	friend Matrix3x1 operator*(Matrix3x3 a,Matrix3x1 b);
};

class eightLight{
private:
	Line line[7];
	Point sixQue[6];
	Point position;
public:
	eightLight(int x=280,int y=20);
	void setPosition(int x=380,int y=0);
	void showNum(int num);
};



int collisionDet(Bullet *bullet,Circle *wo);
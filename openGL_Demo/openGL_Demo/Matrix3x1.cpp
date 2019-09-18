#include "line.h"


Matrix3x1 operator*(Matrix3x3 a,Matrix3x1 b){
	Matrix3x1 tmp;
	tmp.setAllElem1(0,0,0);
	for(int i=0;i<3;i++){
		for(int k=0;k<3;k++){
			tmp.matrix[i] += (a.getElem(i,k)) * (b.matrix[k]);
		}
	}
	return tmp;
}
void Matrix3x1::setAllElem(float a[]){
	for(int i=0;i<3;i++){
		matrix[i]=a[i];
	}
}

void Matrix3x1::setAllElem1(float x1,float x2,float x3){
	matrix[0]=x1;
	matrix[1]=x2;
	matrix[2]=x3;
}

void Matrix3x1::setAllElem2(Point a,float x3){
	matrix[0]=a.X;
	matrix[1]=a.Y;
	matrix[2]=x3;
}

float Matrix3x1::getElem(int x){
	return matrix[x];
}

Point Matrix3x1::getPoint(){
	Point temp;
	temp.X=matrix[0];
	temp.Y=matrix[1];
	return temp;
}

void Matrix3x1::setElem(int x,int value){
	matrix[x]=value;
}
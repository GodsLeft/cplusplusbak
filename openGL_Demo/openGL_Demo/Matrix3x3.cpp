#include "line.h"

Matrix3x3 Matrix3x3::operator + (Matrix3x3 M){
	Matrix3x3 a;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			a.matrix[i][j] = matrix[i][j] + M.matrix[i][j];
		}
	}
	return a;
}
Matrix3x3 Matrix3x3::operator*(Matrix3x3 M){
	Matrix3x3 a;
	for(int i=0;i<3;i++){
		for(int j=0;j<i;j++){
			for(int k=0;k<3;k++){
				a.matrix[i][j]+=matrix[i][k]*M.matrix[k][j];
			}
		}
	}
	return a;
}

Matrix3x3 Matrix3x3::operator - (Matrix3x3 M){
	Matrix3x3 a;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			a.matrix[i][j] = matrix[i][j] - M.matrix[i][j];
		}
	}
	return a;
}

float Matrix3x3::getElem(int x,int y){
	return matrix[x][y];
}
void Matrix3x3::setElem(int x,int y,float value){
	matrix[x][y]=value;
}
void Matrix3x3::setAllElem(float a[3][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			matrix[i][j]=a[i][j];
		}
	}
}
void Matrix3x3::setRotM(float angle){
	matrix[0][0] = cos(angle);
	matrix[0][1] = -sin(angle);
	matrix[1][0] = sin(angle);
	matrix[1][1] = cos(angle);
	matrix[2][2] = 1;
}
void Matrix3x3::setTrM(float x,float y){
	matrix[0][0]=1;
	matrix[1][1]=1;
	matrix[2][2]=1;

	matrix[0][2]=x;
	matrix[1][2]=y;
}

void Matrix3x3::setScaleM(float sx,float sy){
	matrix[0][0]=sx;
	matrix[1][1]=sy;
	matrix[2][2]=1;
}
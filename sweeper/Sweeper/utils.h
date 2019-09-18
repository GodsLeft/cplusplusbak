#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

inline int		RandInt(int x, int y){return rand()%(y-x+1)+x;}
inline double	RandFloat()	{return (rand())/(RAND_MAX+1.0);}

inline bool		RandBool(){
	if(RandInt(0,1)) return true;
	else return false;
}

inline double RandomClamped(){return RandFloat() - RandFloat();}

string itos(int arg);
string ftos(float arg);

//返回不超过 min--max 之间的 arg
void Clamp(double &arg, float min, float max);
void Clamp(int &arg, int min, int max);

struct SPoint{
	double x, y;
	SPoint(double a=0, double b=0):x(a), y(b){}
};

#endif
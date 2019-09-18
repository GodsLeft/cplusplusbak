#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

inline int RandInt(int x, int y){return rand()%(y-x+1)+x;}
inline double RandFloat() {return (rand())/(RAND_MAX+1.0);}

inline bool RandBool(){
	if(RandInt(0, 1)) return true;
	else return false;
}

inline double RandomClamped(){return RandFloat() - RandFloat();}

string itos(int arg);

#endif
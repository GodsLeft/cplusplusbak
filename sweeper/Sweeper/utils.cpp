#include "utils.h"
#include <math.h>

string itos(int arg){
	ostringstream buffer;
	buffer << arg;
	return buffer.str();
}

string ftos(float arg){
	ostringstream buffer;
	buffer << arg;
	return buffer.str();
}

void Clamp(double &arg, float min, float max){
	if(arg < min) arg = min;
	if(arg > max) arg = max;
}

void Clamp(int &arg, int min, int max){
	if(arg < min) arg = min;
	if(arg > max) arg = max;
}
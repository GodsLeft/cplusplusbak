#include "utils.h"

string itos(int arg){
	ostringstream buffer;
	buffer << arg;
	return buffer.str();
}

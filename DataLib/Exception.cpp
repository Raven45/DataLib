#include "Exception.h"
using namespace DataLib;

Exception::Exception(): Object() {
	State = States::Error;
	Error = "Unknown Exception has occurred.";
}

char * Exception::GetError(){
	return Error;
}
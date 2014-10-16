#include "Object.h"
using namespace DataLib;

Object::Object() {
	State = Uninitialized;
}

state Object::GetState(){
	return State;
}
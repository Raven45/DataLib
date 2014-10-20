#include "Object.h"
using namespace DataLib;

Object::Object() {
	State = Uninitialized;
}

state Object::GetState(){
	return State;
}

bool Object::IsInValidState() {

	return (State != States::Valid) ? false : true;
}

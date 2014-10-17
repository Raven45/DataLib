#ifndef EXCEPTION
#define EXCEPTION

#include "Object.h"

namespace DataLib {

	class Exception : public Object {

	public:
		Exception();
		char * GetError();

	protected:
		char * Error;

	};
}

#endif
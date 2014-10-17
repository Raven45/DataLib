#ifndef OBJECTNOTINIT
#define OBJECTNOTINIT

#include "Exception.h"

namespace DataLib {

	class ObjectNotInitializedException : public Exception {

	public:
		ObjectNotInitializedException() {
			State = States::Error;
			Error = "Object is not initialized.";
		}
	};
}

#endif
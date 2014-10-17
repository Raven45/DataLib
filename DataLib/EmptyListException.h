#ifndef EMPTYLIST
#define EMPTYLIST

#include "Exception.h"

namespace DataLib {

	class EmptyListException : public Exception {

	public:
		EmptyListException() {
			State = States::Error;
			Error = "List is empty; there is nothing to retrieve.";
		}
	};
}

#endif
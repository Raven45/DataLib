#include "Exception.h"

namespace DataLib {

	class MemoryException : public Exception {

	public:
		MemoryException() {
			State = States::Error;
			Error = "Was not able to allocate memory.";
		}
	};
}
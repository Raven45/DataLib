#include "Exception.h"

namespace DataLib {

	class DivideByZeroException : public Exception {

	public:
		DivideByZeroException() {
			State = States::Error;
			Error = "Was not able to allocate memory.";
		}
	};
}
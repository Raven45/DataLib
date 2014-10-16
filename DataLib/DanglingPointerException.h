#include "Exception.h"

namespace DataLib {

	class DanglingPointerException : public Exception{

	public:
		DanglingPointerException() {

			State = States::Error;
			Error = "An attempt to access a dangling (null) pointer was made.";
		}
	};
}
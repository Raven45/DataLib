
#ifndef OBJECT
#define OBJECT

#define DATALIB_DLL _declspec(dllexport)

namespace DataLib {

	typedef unsigned short int state;

	enum States{
		Uninitialized,
		Empty,
		Error,
		Invalid,
		Valid
	};

	class Object {

	public:
		Object();
		state GetState();

	protected:
		state State;
	};
}

#endif
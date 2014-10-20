#ifndef STACK
#define STACK

#include "List.hpp"

namespace DataLib {

	template<class DataType>
	class Stack : public List<DataType> {

	public:
		Node<DataType> Pop();
		void Push(Node<DataType> Data);
	};

	template<class DataType>
	Node<DataType> Stack<DataType>::Pop() {

		if (State == States::Valid) {
			NodeSingle<DataType>* Temp = HeadOfList;
			HeadOfList = HeadOfList->GetPointer();

			if (HeadOfList == NULL) {
				State = States::Empty;
			}
		}

		else if (GetState() == States::Uninitialized || GetState() == States::Empty) {
			throw EmptyListException;
		}

		else {
			throw Exception;
		}
	}
}

#endif
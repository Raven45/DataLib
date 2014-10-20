#ifndef LIST
#define LIST

#include "NodeFactory.hpp"
#include "EmptyListException.h"
#include "ObjectNotInitializedException.h"

namespace DataLib {

	template <class DataType>
	class List : public NodeFactory<DataType> {

	public:

		List();
		~List();

		Node<DataType> operator [](int i) const;
		Node<DataType>& operator [](int i);

	protected:
		NodeSingle<DataType>* HeadOfList;
		unsigned int Size;

		Node<DataType>* Seek(Node<DataType>* P, int i);
	};

	template<class DataType>
	List<DataType>::List() : NodeFactory<DataType>() {
		HeadOfList = NULL;
		Size = 0;
		State = States::Uninitialized;
	}

	template<class DataType>
	List<DataType>::~List() {
		delete HeadOfList;
		HeadOfList = NULL;
	}

	template<class DataType>
	Node<DataType> List<DataType>::operator[](int i) const {

		if (State == States::Empty) {
			throw EmptyListException;
		}
		else if (State == States::Uninitialized) {
			throw ObjectNotInitializedException;
		}
		else if (State == States::Valid) {
			return *Seek(HeadOfList, i);
		}
		else {
			throw Exception;
		}
	}

	template<class DataType>
	Node<DataType>& List<DataType>::operator[](int i) {

		if (State == States::Empty) {
			throw EmptyListException;
		}
		else if (State == States::Uninitialized) {
			throw ObjectNotInitializedException;
		}
		else if (State == States::Valid) {
			return *Seek(HeadOfList, i);
		}
		else {
			throw Exception;
		}
	}

	template<class DataType>
	Node<DataType>* List<DataType>::Seek(Node<DataType>* P, int i) {

		if (i > 0) {
			return Seek(P->Next, --i);
		}
		else {
			return P;
		}
	}

}

#endif
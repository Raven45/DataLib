#include "Node.hpp"
#include "EmptyListException.h"

namespace DataLib {

	template<class DataType>
	class NodeFactoryCache : Object {

		friend class NodeFactory;

	private:

		struct CacheNode {
			Node<DataType>* Data;
			CacheNode* Next;
		};

		//Members
		CacheNode * TopOfStack;
		unsigned int Size;

		//Methods
		NodeFactoryCache();
		~NodeFactoryCache();
		Node<DataType>* Pop();
		void Push(Node<DataType> Data);
		unsigned int GetSize();

	};

	template<class DataType>
	NodeFactoryCache<DataType>::NodeFactoryCache() : Object() {
		TopOfStack = NULL;
	}

	template<class DataType>
	NodeFactoryCache<DataType>::~NodeFactoryCache() {

	}

	template<class DataType>
	Node<DataType>* NodeFactoryCache<DataType>::Pop() {

		//empty stack case
		if (State == States::Uninitialized) {
			throw EmptyListException;
		}

		else {
			Node<DataType>* Return = TopOfStack->Data;
			TopOfStack = TopOfStack->Next;
			return Return;
		}
	}
}
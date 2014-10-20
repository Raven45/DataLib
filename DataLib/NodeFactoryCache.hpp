#ifndef NODEFACTORYCACHE
#define NODEFACTORYCACHE

#include "Node.hpp"
#include "EmptyListException.h"
#include "ObjectNotInitializedException.h"
#include "MemoryException.h"

namespace DataLib {

	template<class DataType>
	class NodeFactory;

	template<class DataType>
	class NodeFactoryCache : Object {

		friend class NodeFactory<DataType>;

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
		void Push(Node<DataType>* Data);

		unsigned int GetSize();

		void Flush(CacheNode * P);

	};

	template<class DataType>
	NodeFactoryCache<DataType>::NodeFactoryCache() : Object() {
		TopOfStack = NULL;
	}

	template<class DataType>
	NodeFactoryCache<DataType>::~NodeFactoryCache() {
		Flush(TopOfStack);
	}

	template<class DataType>
	Node<DataType>* NodeFactoryCache<DataType>::Pop() {

		//Non-empty and healthy stack case
		if (GetState() == States::Valid) {

			CacheNode * Temp = TopOfStack;
			Node<DataType>* Return = TopOfStack->Data;
			TopOfStack = TopOfStack->Next;

			if (TopOfStack == NULL) {
				State = States::Empty;
			}

			Size--;

			//Prevent memory leak.
			delete Temp;
			Temp = NULL;

			return Return;
		}

		//empty or unhealthy stack casees
		else if (GetState() == States::Uninitialized)	throw ObjectNotInitializedException;
		else if (GetState() == States::Empty)			throw EmptyListException;
	}

	template<class DataType>
	void NodeFactoryCache<DataType>::Push(Node<DataType>* Data) {

		if (GetState() == States::Valid) {

			try {
				CacheNode * Temp = new CacheNode;
				Temp->Data = Data;
				Temp->Next = TopOfStack;
				TopOfStack = Temp;
				Temp = NULL;
				Size++;
			}

			catch (std::bad_alloc) {
				Temp = NULL;
				State = States::Error;
				throw MemoryException;
			}
		}

		else if (GetState() == States::Uninitialized || GetState() == States::Empty) {
			State = States::Valid;
			Push(Data);
		}

		//in event of error, throw unknown exception.
		else {
			throw Exception;
		}

	}

	template<class DataType>
	unsigned int NodeFactoryCache<DataType>::GetSize() {
		return Size;
	}

	template<class DataType>
	void NodeFactoryCache<DataType>::Flush(CacheNode* P){

		if (P != NULL) {

			Flush(P->Next);

			delete P;
			P = NULL;
			Size--;

			if (Size == 0) {
				State = States::Uninitialized;
			}
		}
	}
}

#endif
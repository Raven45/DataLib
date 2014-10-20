#ifndef NODEFACTORY	
#define NODEFACTORY

#include "NodeDouble.hpp"
#include "NodeSingle.hpp"
#include "NodeFactoryCache.hpp"

namespace DataLib {

	enum NodeTypes {
		Single,
		Double,
		Advance
	};

	template<class DataType>
	class NodeFactory : public Object {

		typedef Node<DataType>* NodePointer;

	public:

		NodeFactory();
		~NodeFactory();
	
		NodePointer RequestNode(unsigned short int Type);
		void ReturnNode(NodePointer N);

		void EnableCache();
		void DisableCache();

	private:
		NodeFactoryCache<DataType> Cache;
		bool CacheEnabled;
	};

	template<class DataType>
	NodeFactory<DataType>::NodeFactory() : Object() {
		CacheEnabled = true;
	}

	template<class DataType>
	NodeFactory<DataType>::~NodeFactory(){
		Cache.Flush(Flush.TopOfStack);
	}

	template<class DataType>
	Node<DataType>* NodeFactory<DataType>::RequestNode(unsigned short int Type) {

		if (GetState() == States::Valid) {

			if (Type == Single) {

				if (CacheEnabled && Cache.GetSize() > 0)
					return Cache.Pop();
				else 
					return new NodeSingle<DataType>;
			}

			else if (Type == Double) {

				if (CacheEnabled && Cache.GetSize() > 0)
					return Cache.Pop();
				else
					return new NodeDouble<DataType>;
			}

			else if (Type == Advance) {

				if (CacheEnabled && Cache.GetSize() > 0) 
					return Cache.Pop();
				else
					//return new NodeAdvance<DataType>; //Not yet implemented
			}
		}
	}

	template<class DataType>
	void NodeFactory<DataType>::ReturnNode(Node<DataType>* N) {

		if (CacheEnabled) {

			try {
				Cache.Push(N);
			}

			catch (...) {
				Cache.Flush();
				delete N;
				N = NULL;
			}
		}

		else {
			delete N;
			N = NULL;
		}
	}

	template<class DataType>
	void NodeFactory<DataType>::EnableCache() {
		CacheEnabled = true;
	}

	template<class DataType>
	void NodeFactory<DataType>::DisableCache(){
		CacheEnabled = false;
		Cache.Flush();
	}
}

#endif
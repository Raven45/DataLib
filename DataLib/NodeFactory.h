#include "NodeDouble.hpp"
#include "NodeSingle.hpp"

namespace DataLib {

	enum NodeTypes {
		Single,
		Double,
		Advance
	};

	template<class DataType>
	class NodeFactory : Object {

		typedef Node<DataType>* NodePointer;

	public:
		NodeFactory();
	
		NodePointer RequestNode(unsigned short int Type);
		void ReturnNode(NodePointer N);
	private:
	};

	template<class DataType>
	Node<DataType>* NodeFactory<DataType>::RequestNode(unsigned short int Type) {

		if (Type == Single) {
			return new NodeSingle<DataType>;
		}

		else if (Type == Double) {
			return new NodeDouble<DataType>;
		}

		else if (Type == Advance) {
			//return new NodeAdvance<DataType>; //Not yet implemented
		}
	}

	template<class DataType>
	void NodeFactory<DataType>::ReturnNode(Node<DataType>* N) {

	}
}
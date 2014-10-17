#include "Node.hpp"

namespace DataLib {

	template <class DataType>
	class NodeSingle : public Node<DataType> {

	public:

		NodeSingle();
		NodeSingle(DataType Data);
		NodeSingle(NodeSingle<DataType>* Pointer);
		NodeSingle(DataType Data, NodeSingle<DataType>* Pointer);
		NodeSingle(NodeSingle<DataType> &Copy);

		NodeSingle<DataType>* GetPointer();
		void SetPointer(NodeSingle<DataType>* P);

	private:
		NodeSingle<DataType>* P;

	};

	template<class DataType>
	NodeSingle<DataType>::NodeSingle() : Node<DataType>() {

	}

	template<class DataType>
	NodeSingle<DataType>::NodeSingle(DataType Data) : Node<DataType>(Data) {
		
	}

	template<class DataType>
	NodeSingle<DataType>::NodeSingle(NodeSingle<DataType>* Pointer) : Node<DataType>() {
		P = Pointer;
	}

	template<class DataType>
	NodeSingle<DataType>::NodeSingle(DataType Data, NodeSingle<DataType>* Pointer) : Node<DataType>(Data) {
		P = Pointer;
	}

	template<class DataType>
	NodeSingle<DataType>::NodeSingle(NodeSingle<DataType> &Copy) : Node<DataType>(Copy) {
		this->P = Copy.P;
	}

	template<class DataType>
	NodeSingle<DataType>* NodeSingle<DataType>::GetPointer() {
		return P;
	}

	template<class DataType>
	void NodeSingle<DataType>::SetPointer(NodeSingle<DataType>* P) {
		this->P = P;
	}

}
#include "Node.hpp"

namespace DataLib {

	template <class DataType>
	class NodeDouble : public Node<DataType> {

	public:

		NodeDouble();
		NodeDouble(DataType Data);
		NodeDouble(NodeDouble<DataType>* Left);
		NodeDouble(NodeDouble<DataType>* Left, NodeDouble<DataType>* Right);
		NodeDouble(DataType Data, NodeDouble<DataType>* Pointer);
		NodeDouble(DataType Data, NodeDouble<DataType>* Left, NodeDouble<DataType>* Right);
		NodeDouble(NodeDouble<DataType> &Copy);

		NodeDouble<DataType>* GetLeft();
		NodeDouble<DataType>* GetRight(); 
		void SetLeft(NodeDouble<DataType>* Left);
		void SetRight(NodeDouble<DataType>* Right);

	private:
		Node<DataType>* Left;
		Node<DataType>* Right;
	};

	template<class DataType>
	NodeDouble<DataType>::NodeDouble() : Node<DataType>() {

	}

	template<class DataType>
	NodeDouble<DataType>::NodeDouble(DataType Data) : Node<DataType>(Data) {

	}

	template<class DataType>
	NodeDouble<DataType>::NodeDouble(NodeDouble<DataType>* Left) : Node<DataType>() {
		this->Left = Left;
	}

	template<class DataType>
	NodeDouble<DataType>::NodeDouble(NodeDouble<DataType>* Left, NodeDouble<DataType>* Right) {
		this->Left = Left;
		this->Right = Right;
	}

	template<class DataType>
	NodeDouble<DataType>::NodeDouble(DataType Data, NodeDouble<DataType>* Left) : Node<DataType>(Data) {
		this->Left = Left;
	}

	template<class DataType>
	NodeDouble<DataType>::NodeDouble(DataType Data, NodeDouble<DataType>* Left, NodeDouble<DataType>* Right) : Node<DataType>(Data) {
		this->Left = Left;
		this->Right = Right;
	}

	template<class DataType>
	NodeDouble<DataType>::NodeDouble(NodeDouble<DataType> &Copy) : Node<DataType>(Copy) {
		this->Left = Copy.Left;
		this->Right = Copy.Right;
	}

	template<class DataType>
	NodeDouble<DataType>* NodeDouble<DataType>::GetLeft() {
		return Left;
	}

	template<class DataType>
	NodeDouble<DataType>* NodeDouble<DataType>::GetRight() {
		return Right;
	}

	template<class DataType>
	void NodeDouble<DataType>::SetLeft(NodeDouble<DataType>* Left) {
		this->Left = Left;
	}

	template<class DataType>
	void NodeDouble<DataType>::SetRight(NodeDouble<DataType>* Right) {
		this->Right = Right;
	}
}
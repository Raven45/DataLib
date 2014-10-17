#ifndef NODE
#define NODE

#include "Object.h"
#include <fstream>
#include "DivideByZeroException.h"
#include "ObjectNotInitializedException.h"


namespace DataLib {

	template <class DataType>
	class Node : private Object {

	public:

		//Constructors
		Node();
		Node(DataType Data);
		Node(Node<DataType> &Copy);

		//Destructor
		//virtual ~Node() = 0;

		//Typecast operator
		operator DataType();

		//Arithmetic Operator Overloads
		DataType operator+(DataType B) const;
		DataType operator-(DataType B) const;
		DataType operator*(DataType B) const;
		DataType operator/(DataType B) const;
		DataType operator%(DataType B) const;
		DataType& operator++();
		DataType& operator--();
		DataType operator++(int);
		DataType operator--(int);

		//Assignment operators overloads
		DataType operator=(const DataType& B);
		DataType operator+=(const DataType& B);
		DataType operator-=(const DataType& B);
		DataType operator*=(const DataType& B);
		DataType operator/=(const DataType& B);

		//Comparison operator overloads
		bool operator==(const Node<DataType> B) const;
		bool operator!=(const Node<DataType> B) const;
		bool operator<(const Node<DataType> B) const;
		bool operator>(const Node<DataType> B) const;
		bool operator<=(const Node<DataType> B) const;
		bool operator>=(const Node<DataType> B) const;

		//IO operator overloads
		template<class DataType>
		friend std::ostream& operator<< (std::ostream &output, const Node<DataType> &Data);
		template<class DataType>
		friend std::istream& operator>> (std::istream &input, Node<DataType> &Data);

	protected:

		DataType Data;

		void CheckForInitialization();
	};

	template<class DataType>
	Node<DataType>::Node() : Object() {

	}

	template<class DataType>
	Node<DataType>::Node(DataType Data) : Object()  {
		this->Data = Data;
		State = States::Valid;
	}

	template<class DataType>
	Node<DataType>::Node(Node<DataType> &Copy) {
		this->State = Copy.GetState();
		this->Data = Copy.Data;
	}

	template<class DataType>
	Node<DataType>::operator DataType() {
		CheckForInitialization();
		return Data;
	}

	template<class DataType>
	DataType Node<DataType>::operator+(DataType B) const {
		CheckForInitialization();
		return this->Data + B.Data;
	}

	template<class DataType>
	DataType Node<DataType>::operator-(DataType B) const {
		CheckForInitialization();
		return this->Data - B.Data;
	}

	template<class DataType>
	DataType Node<DataType>::operator*(DataType B) const {
		CheckForInitialization();
		return this->Data * B.Data;
	}

	template<class DataType>
	DataType Node<DataType>::operator/(DataType B) const {
		CheckForInitialization();
		if (B.Data == 0)
			throw DivideByZeroException;
		else
			return this->Data / B.Data;
	}

	template<class DataType>
	DataType Node<DataType>::operator%(DataType B) const {
		CheckForInitialization();
		if (B.Data == 0)
			throw DivideByZeroException;
		else
			return this->Data % B.Data;
	}

	template<class DataType>
	DataType& Node<DataType>::operator++() {
		CheckForInitialization();
		return ++Data;
	}

	template<class DataType>
	DataType& Node<DataType>::operator--() {
		CheckForInitialization();
		return --Data;
	}

	template<class DataType>
	DataType Node<DataType>::operator++(int) {
		CheckForInitialization();
		return Data++;
	}

	template<class DataType>
	DataType Node<DataType>::operator--(int) {
		CheckForInitialization();
		return Data--;
	}

	template<class DataType>
	DataType Node<DataType>::operator=(const DataType& B) {
		this->Data = B.Data;
		if (GetState() == States::Uninitialized)
			State = States::Valid;
		return *this
	}

	template<class DataType>
	DataType Node<DataType>::operator+=(const DataType& B) {
		CheckForInitialization();
		this->Data += B.Data;
		return *this;
	}

	template<class DataType>
	DataType Node<DataType>::operator-=(const DataType& B) {
		CheckForInitialization();
		this->Data -= B.Data;
		return *this;
	}

	template<class DataType>
	DataType Node<DataType>::operator*=(const DataType& B) {
		CheckForInitialization();
		this->Data *= B.Data;
		return *this;
	}

	template<class DataType>
	DataType Node<DataType>::operator/=(const DataType& B) {
		CheckForInitialization();
		if (B.Data == 0)
			throw DivideByZeroException;
		else {
			this->Data /= B.Data;
			return *this;
		}
	}

	template<class DataType>
	bool Node<DataType>::operator==(const Node<DataType> B) const {
		return (this->Data == B.Data) ? true : false;
	}

	template<class DataType>
	bool Node<DataType>::operator!=(const Node<DataType> B) const {
		return (this->Data == B.Data) ? false : true;
	}

	template<class DataType>
	bool Node<DataType>::operator<(const Node<DataType> B) const {
		return (this->Data < B.Data) ? true : false;
	}

	template<class DataType>
	bool Node<DataType>::operator>(const Node<DataType> B) const {
		return (this->Data > B.Data) ? true : false;
	}

	template<class DataType>
	bool Node<DataType>::operator<=(const Node<DataType> B) const {
		return (this->Data <= B.Data) ? true : false;
	}

	template<class DataType>
	bool Node<DataType>::operator>=(const Node<DataType> B) const {
		return (this->Data >= B.Data) ? true : false;
	}

	template<class DataType>
	std::ostream& operator<< (std::ostream &output, const Node<DataType> &Data) {
		output << Data.Data;
		return output;
	}


	template<class DataType>
	std::istream& operator>> (std::istream &input, Node<DataType> &Data) {
		input >> Data.Data;
		if (GetState() == States::Uninitialized)
			State = States::Valid;
		return input;
	}

	template<class DataType>
	void Node<DataType>::CheckForInitialization() {
		if (GetState() == States::Uninitialized)
			throw ObjectNotInitializedException;
	}
}

#endif
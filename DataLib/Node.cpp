#include "Node.h"
using namespace DataLib;

template<class DataType>
Node<DataType>::Node() : Object {

}

template<class DataType>
Node<class DataType>::Node(DataType Data) : Object() {
	this->Data = Data;
}

template<class DataType>
Node<DataType>::Node(Node<DataType> &Copy) {
	this->State = Copy.GetState();
	this->Data = Copy.Data;
}

template<class DataType>
DataType Node<DataType>::operator+(DataType B) const {
	return this->Data + B.Data;
}

template<class DataType>
DataType Node<DataType>::operator-(DataType B) const {
	return this->Data - B.Data;
}

template<class DataType>
DataType Node<DataType>::operator*(DataType B) const {
	return this->Data * B.Data;
}

template<class DataType>
DataType Node<DataType>::operator/(DataType B) const {
	if (B.Data == 0)
		throw DivideByZeroException;
	else
		return this->Data / B.Data;
}

template<class DataType>
DataType Node<DataType>::operator%(DataType B) const {
	if (B.Data == 0)
		throw DivideByZeroException;
	else
		return this->Data % B.Data;
}

template<class DataType>
DataType& Node<DataType>::operator++() {
	return ++Data;
}

template<class DataType>
DataType& Node<DataType>::operator--() {
	return --Data;
}

template<class DataType>
DataType Node<DataType>::operator++(int) {
	return Data++;
}

template<class DataType>
DataType Node<DataType>::operator--(int) {
	return Data--;
}

template<class DataType>
DataType Node<DataType>::operator=(const DataType& B) {
	this->Data = B.Data;
	return *this
}

template<class DataType>
DataType Node<DataType>::operator+=(const DataType& B) {
	this->Data += B.Data;
	return *this;
}

template<class DataType>
DataType Node<DataType>::operator-=(const DataType& B) {
	this->Data -= B.Data;
	return *this;
}

template<class DataType>
DataType Node<DataType>::operator*=(const DataType& B) {
	this->Data *= B.Data;
	return *this;
}

template<class DataType>
DataType Node<DataType>::operator/=(const DataType& B) {
	if (B.Data == 0)
		throw DivideByZeroException;
	else {
		this->Data /= B.Data;
		return *this;
	}
}

template<class DataType>
std::ostream& operator<< (std::ostream &output, const Node<DataType> &Data) {
	output << Data.Data;
	return output;
}


template<class DataType>
std::ostream& operator>> (std::ostream &input, const Node<DataType> &Data) {
	input >> Data.Data;
	return input;
}





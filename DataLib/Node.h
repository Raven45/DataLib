#include "Object.h"
#include <fstream>
#include "DivideByZeroException.h"


namespace DataLib {

	template <class DataType>
	class Node : private Object {

	public:

		//Constructors
		Node();
		Node(DataType Data);
		Node(Node<DataType> &Copy);

		//Destructor
		virtual ~Node() = 0;

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

		//IO operator overloads
		friend std::ostream& operator<< (std::ostream &output, const Node<DataType> &Data);
		friend std::istream& operator>> (std::istream &input, Node<DataType> &Data);

	protected:

		DataType Data;
	};
}
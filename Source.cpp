#include "List.hpp"
#include <iostream>



template <class DataType>
class CompareTest: public DataLib::Comparator<DataType> {
	virtual bool Compare(DataType A, DataType B) {
		if (B >= A) {
			return false;
		}
		else {
			return true;
		}
	}
};



/****************************************************************
Name:			List Test Case 1
Tests the random number generator and the sorting algorithm
by randomly generating 1000 numbers and then sorting them.
****************************************************************/
void List_TestCase1() {

	DataLib::List<unsigned int> A;			//Declare List
	A.EnableMoveToFront();

	for (int i = 0; i < 1000; i++) {
		A.Insert(A.Random(), 0);
	}
	A.Sort();
	int size = A.GetSize();
	for (int i = 0; i < size; i++) {
		std::cout << i << ": " << A.Remove(0) << std::endl;
	}
}

/****************************************************************
Name:			List Test Case 2
Tests the random number generator and the sorting algorithm
by randomly generating 5000 numbers and then sorting them. This
specifically is testing to ensure that the sorting algorithm
does not cause a stack overflow error. 
****************************************************************/
void List_TestCase2() {

	DataLib::List<unsigned int> A;			//Declare List
	A.EnableMoveToFront();

	for (int i = 0; i < 5000; i++) {
		A.Insert(A.Random(), 0);
	}
	A.Sort();
	int size = A.GetSize();
	for (int i = 0; i < size; i++) {
		std::cout << i << ": " << A.Remove(0) << std::endl;
	}
}

void List_TestCase3() {

	DataLib::List<unsigned int> A;			//Declare List
	A.EnableMoveToFront();

	for (int i = 0; i < 1000; i++) {
		A.Insert(0, 0);
	}

	A[4] = 5;
	A[450] = 45;
	A[455] = 46;

	A.Search(46);
	A.Search(45);
	A.Search(5);

	int size = A.GetSize();
	for (int i = 0; i < size; i++) {
		std::cout << i << ": " << A.Remove(0) << std::endl;
	}
}

void List_TestCase4() {

	DataLib::List<unsigned int> A;
	CompareTest<unsigned int> C;
	
	for (int i = 0; i < 5000; i++) {
		A.Insert(A.Random(), 0);
	}
	A.Sort(&C);
	int size = A.GetSize();
	for (int i = 0; i < size; i++) {
		std::cout << i << ": " << A.Remove(0) << std::endl;
	}
}

int main(){

	//List_TestCase1();
	List_TestCase4();
	//List_TestCase3();

	//while (1);
	return 0;
}

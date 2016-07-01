#include "List.hpp"
#include <iostream>




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

int main(){

	//List_TestCase1();
	List_TestCase2();
	//List_TestCase3();

	//while (1);
	return 0;
}

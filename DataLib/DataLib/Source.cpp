#include "List.hpp"
#include <iostream>

void main(){



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

	while (1);
}
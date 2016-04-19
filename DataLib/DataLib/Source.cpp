#include "Core\Object.h"
#include <iostream>

void main(){



	DataLib::Object A;
	unsigned int a = A.GetHash();
	unsigned int b = A.Random();

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	while (1);
}
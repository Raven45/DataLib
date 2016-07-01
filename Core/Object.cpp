/************************************************************************
Copyright 2016 Aaron Burns

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
************************************************************************/

#include "Object.h"

/****************************************************************
Name:			Default Constructor
Input:			N/A
Output:			N/A
Description:	The default constructor will initialize the object
to the "Unintialized" state and set the name to a blank string.
It will also initialize the random number generator by using the
object's hash as the initial seed.
****************************************************************/
DataLib::Object::Object(): State(Uninitialized) {

	try {
		this->Name = new char[SIZE_OF_NAME];
		Name = (char*)"DataLib::Object";
	}
	catch (...) {
		this->Name = nullptr;
		State = Error;
	}
	srand(GetHash());
}

/****************************************************************
Name:			Copy Constructor
Input:			N/A
Output:			N/A
Description:	The copy constructor will make a copy of the
object.
****************************************************************/
DataLib::Object::Object(Object & Copy) {
	this->Name = Copy.Name;
	this->State = Copy.State;
}

/****************************************************************
Name:			Clone
Input:			N/A
Output:			N/A
Description:	Clone will make and return a pointer to a copy
of the object. Useful for copying to already existing objects.
****************************************************************/
DataLib::Object * DataLib::Object::Clone() const{

	try {
		Object* Clone = new Object;
		Clone->Name = this->Name;
		Clone->State = this->State;
		return Clone;
	}
	catch (...) {
		return nullptr;
	}
}

/****************************************************************
Name:			Random
Input:			N/A
Output:			A psuedo random number
Description:	The "Random" function will use a cryptographically
secure psuedo-random number generator to generate a random number.
The algorithm used is the Blum Blum Shub algorithm. The Seed
and the two primes are randomly generated.
****************************************************************/
unsigned int DataLib::Object::Random() const {
	return GenerateRandom(0, 0);
}

/****************************************************************
Name:			Random
Input:			Lower: The lower limit of the output.
Upper: The upper limit of the output.
Output:			A psuedo random number
Description:	The "Random" function will use a cryptographically
secure psuedo-random number generator to generate a random number.
The algorithm used is the Blum Blum Shub algorithm. The Seed
and the two primes are randomly generated. The random number
returned will fall in between the inputs "Lower" and "Upper."
If "Lower" is greater than "Upper," then zero will always be
returned.
****************************************************************/
unsigned int DataLib::Object::Random(unsigned int Lower, unsigned int Upper) const {
	return GenerateRandom(Lower, Upper);
}

/****************************************************************
Name:			GetState
Input:			N/A
Output:			The state of the object
Description:	This will return the current state of the object.
Possible States:
0 = Uninitialized
1 = Empty
2 = Error
3 = Invalid
4 = Valid
****************************************************************/
unsigned int DataLib::Object::GetState() const {
	return this->State;
}

/****************************************************************
Name:			GetHash
Input:			N/A
Output:			The hash of the object
Description:	This will compute and return the hash of the
object. The algorithm used is the same as that used in Java.
****************************************************************/
unsigned int DataLib::Object::GetHash() const {
	
	int Hash = 0;
	int Length = sizeof(*this);
	char* Data = (char*)(this);
	
	for (int i = 0; i < Length; i++) {
		Hash += Data[i]*Power(31, Length-1);
	}
	
	return Hash;
}

/****************************************************************
Name:			GetName
Input:			N/A
Output:			the name of the object
Description:	This will return the name of the object. The
name of an object is an empty string by default; it is up to the
developer to assign a name if they so choose.
****************************************************************/
char * DataLib::Object::GetName() const {
	return Name;
}

/****************************************************************
Name:			ToString
Input:			N/A
Output:			A string representation of the object
Description:	This will return the string representation of
the object.
****************************************************************/
char * DataLib::Object::ToString() const {

	return Name;
}

/****************************************************************
Name:			SetName
Input:			Name: The value to set.
Output:			N/A
Description:	This will allow a developer to assign an
arbitrary name to the object.
****************************************************************/
void DataLib::Object::SetName(char* Name) {
	this->Name = Name;
}

void DataLib::Object::WriteLock() {

	if (State != Uninitialized || State != Error) {
		SavedState = State;
		State = Locked;
	}
}

void DataLib::Object::WriteUnlock() {

	if (State == Locked) {
		State = SavedState;
	}
}

/****************************************************************
Name:			GenerateRandom
Input:			Lower: The lower limit of the output.
Upper:			The upper limit of the output.
Output:			A psuedo random number
Description:	A helper function used to generate a random
number for the "Random" function.
The algorithm used is the Blum Blum Shub algorithm. The Seed
and the two primes are randomly generated. The random number
returned will fall in between the inputs "Lower" and "Upper."
If "Lower" is greater than "Upper," then zero will always be
returned.
****************************************************************/
unsigned int DataLib::Object::GenerateRandom(unsigned int Lower, unsigned int Upper) const{
	
	//generate random prime numbers if inputs are zero
	unsigned int P = GenerateBlumPrime();
	unsigned int Q = GenerateBlumPrime(); 

	//Calculate N
	unsigned int N = P*Q;

	//Generate random seed if input is zero
	unsigned int Seed = GenerateRandomSeed(N); 
	//unsigned int Seed = GetHash();

	//Declare bit arrays.
	unsigned int X[sizeof(unsigned int)* 8];
	unsigned int Z[sizeof(unsigned int)* 8];

	//Generate random bits, one bit at a time.
	X[0] = Power(Seed, 2) % N;
	for (int i = 1; i < sizeof(unsigned int)* 8; i++) {
		X[i] = Power(X[i - 1], 2) % N;
		Z[i] = parity(X[i]);
	}

	//Set bits in return value.
	unsigned int _Key = 0;
	for (int i = 1; i < sizeof(unsigned int)* 8 - 1; i++) {
		//use i-1 for return value, else the result will always be even.
		if (Z[i] != 0) { _Key = _Key | Power(2, i-1); }
		//if (Z[i] == 0) { _Key = _Key | 1 << i-1; }
	}
	
	if (Lower == Upper) {
		return _Key;
	}
	else if (Lower < Upper) {
		
		if (_Key >= Lower && _Key <= Upper) {
			return _Key;
		}
		else {
			return GenerateRandom(Lower, Upper);
		}
	}
	else {
		return 0;
	}
}


bool DataLib::Object::parity(unsigned int N) const {

	unsigned int Totals = 0;

	for (int i = 0; i < sizeof(unsigned int)* 8; i++) {

		//even parity
		if (N & Power(2, i)) {
			Totals++;
		}
	}

	return (Totals % 2 == 0) ? false : true;
}


unsigned int DataLib::Object::Power(unsigned int X, unsigned int Y) const {

	unsigned int ReturnValue = X;

	if (Y == 0) {
		ReturnValue = 1;
	}

	else if (Y > 1) {

		for (unsigned int i = 1; i < Y; i++){
			ReturnValue *= X;
		}
	}

	return ReturnValue;
}


unsigned int DataLib::Object::GenerateBlumPrime() const {

	unsigned int B;

	do {
		//srand(time(NULL));
		B = rand() % Power(2, (sizeof(unsigned int)* 8) - 1) + Power(2, 24);
	} while (B < Power(2, 24) || B % 4 != 3);

	return B;
}


unsigned int DataLib::Object::GenerateRandomSeed(unsigned int N) const {

	unsigned int Seed = 0;

	while (Seed < 1 || Seed >(N - 1) || !IsCoprime(Seed, N)) {
		//srand(time(NULL));
		Seed = rand() % Power(2, (sizeof(unsigned int)* 8) - 1);
	}

	return Seed;
}


bool DataLib::Object::IsCoprime(unsigned int X, unsigned int Y) const {

	bool ReturnValue = false;
	unsigned int R;

	if (Y == 0) {
		if (X == 1){
			ReturnValue = true;
		}
	}

	else {

		R = X%Y;
		if (R == 0){
			if (Y == 1) {
				ReturnValue = true;
			}
		}

		else { ReturnValue = IsCoprime(Y, R); }
	}

	return ReturnValue;
}

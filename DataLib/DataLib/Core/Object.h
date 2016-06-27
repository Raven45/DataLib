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


#ifndef DATALIB_OBJECT
#define DATALIB_OBJECT

#include <stdlib.h>

namespace DataLib {

	const unsigned int SIZE_OF_NAME = 64;
	
	enum State{
		Uninitialized,
		Empty,
		Error,
		Locked,
		Valid
	};
	
	/********************************************************************
	Class Name:		Object
	Description:	The "Object" object is the superclass of which all
	other classes in DataLib are inherited from. It implements a common
	template across all classes and objects within DataLib.
	********************************************************************/
	class Object{
		
	public:
		
		/****************************************************************
		Name:			Default Constructor
		Input:			N/A
		Output:			N/A
		Description:	The default constructor will initialize the object
		to the "Unintialized" state and set the name to a blank string.
		It will also initialize the random number generator by using the
		object's hash as the initial seed.
		****************************************************************/
		Object();

		/****************************************************************
		Name:			Copy Constructor
		Input:			N/A
		Output:			N/A
		Description:	The copy constructor will make a copy of the 
		object.
		****************************************************************/
		Object(Object &Copy);

		/****************************************************************
		Name:			Clone
		Input:			N/A
		Output:			N/A
		Description:	Clone will make and return a pointer to a copy
		of the object. Useful for copying to already existing objects.
		****************************************************************/
		virtual Object*	Clone() const;
		
		/****************************************************************
		Name:			Random
		Input:			N/A
		Output:			A psuedo random number
		Description:	The "Random" function will use a cryptographically
		secure psuedo-random number generator to generate a random number.
		The algorithm used is the Blum Blum Shub algorithm. The Seed
		and the two primes are randomly generated. 
		****************************************************************/
		unsigned int 	Random() 	const;

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
		unsigned int	Random(unsigned int Lower, unsigned int Upper) const;

		/****************************************************************
		Name:			GetState
		Input:			N/A
		Output:			The state of the object
		Description:	This will return the current state of the object.
		Possible States:
			0 = Uninitialized
			1 = Empty
			2 = Error
			3 = Locked
			4 = Valid
		****************************************************************/
		unsigned int 	GetState() 	const;

		/****************************************************************
		Name:			GetHash
		Input:			N/A
		Output:			The hash of the object
		Description:	This will compute and return the hash of the
		object. The algorithm used is the same as that used in Java.
		****************************************************************/
		unsigned int 	GetHash() 	const;

		/****************************************************************
		Name:			GetName
		Input:			N/A
		Output:			the name of the object
		Description:	This will return the name of the object. The 
		name of an object is an empty string by default; it is up to the
		developer to assign a name if they so choose.
		****************************************************************/
		char* GetName() const;

		/****************************************************************
		Name:			ToString
		Input:			N/A
		Output:			A string representation of the object
		Description:	This will return the string representation of
		the object. 
		****************************************************************/
		virtual char* ToString() const;
		
		/****************************************************************
		Name:			SetName
		Input:			Name: The value to set.
		Output:			N/A
		Description:	This will allow a developer to assign an 
		arbitrary name to the object.
		****************************************************************/
		void			SetName(char* Name);

		void			WriteLock();
		void			WriteUnlock();
		
	protected:
	
		char* Name;
		unsigned int State;
		unsigned int SavedState;

		/****************************************************************
		Name:			GenerateRandom
		Input:			Lower: The lower limit of the output.
						Upper: The upper limit of the output.
		Output:			A psuedo random number
		Description:	A helper function used to generate a random
		number for the "Random" function.
		The algorithm used is the Blum Blum Shub algorithm. The Seed
		and the two primes are randomly generated. The random number
		returned will fall in between the inputs "Lower" and "Upper."
		If "Lower" is greater than "Upper," then zero will always be
		returned.
		****************************************************************/
		unsigned int 	GenerateRandom(unsigned int Lower, unsigned int Upper) const;
		
		bool 			parity(unsigned int N) const;
		unsigned int 	Power(unsigned int X, unsigned int Y) const;
		unsigned int 	GenerateBlumPrime() const;
		unsigned int 	GenerateRandomSeed(unsigned int N) const;
		bool 			IsCoprime(unsigned int X, unsigned int Y) const;
	};
}

#endif /*DATALIB_OBJECT*/
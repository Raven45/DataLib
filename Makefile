
#Main build of the application.
DataLib: Source.o List.o Object.o Exception.o
	g++ -o DataLib Source.o List.o Object.o Exception.o
	
#Compile the main application.
Source.o: Source.cpp
	g++ -c Source.cpp
	
#Compile the linked list library.
List.o: List.hpp
	g++ -c -x c++ List.hpp
	
#Compile the core object library.
Object.o: Core/Object.cpp
	g++ -c Core/Object.cpp
	
#Compile the Exceptions library.
Exception.o: Core/Exception.cpp
	g++ -c Core/Exception.cpp

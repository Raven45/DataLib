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

#ifndef DATALIB_LIST
#define DATALIB_LIST

#include "Core\Exception.h"
#include "Core\Object.h"


namespace DataLib {

	

	template <class DataType>
	class List : public Object {

	private:

		class Node {
		public:

			DataType Data;
			Node* Next;

			Node();
			Node(Node &Copy);
			Node(DataType Data);
			Node(DataType Data, Node* Next);
			~Node();

			operator DataType() const;
			Node& operator=(const DataType& B);
		};

		Node* TopOfList;
		unsigned int Size;
		bool MoveToFront;

		Node* Seek(unsigned int Position);
		bool Swap(Node* A, Node* B);

		Node* MergeSort(Node* P);
		Node* MergeSortIterative(Node* P);
		Node* Merge(Node* A, Node* B);
		Node* MergeIterative(Node* A, Node* B);
		Node* Split(Node* P);

	public:

		/****************************************************************
		Name:			Default Constructor
		Input:			N/A
		Output:			N/A
		Description:	The default constructor will initialize the list
		to an empty list, and then set the internal state to the "empty"
		state.
		****************************************************************/
		List();

		/****************************************************************
		Name:			Copy Constructor
		Input:			N/A
		Output:			N/A
		Description:	The copy constructor will make a copy of the
		list.
		****************************************************************/
		List(List<DataType> &Copy);

		/****************************************************************
		Name:			Copy Constructor
		Input:			Head: Pointer to the array
						Length: the length of the array.
		Output:			N/A
		Description:	An alternate constructor that allows a standard
		C-style array to be converted to a list.
		****************************************************************/
		List(DataType* Head, unsigned int Length);
		~List();

		/****************************************************************
		Name:			IsEmpty
		Input:			N/A
		Output:			"true" if list is empty.
						"false" if list is not empty.
		Description:	Returns whether or not the list is in an empty
						state. Returns true if the list is empty, else
						it returns false.
		****************************************************************/
		bool			IsEmpty() const;

		/****************************************************************
		Name:			GetSize
		Input:			N/A
		Output:			Size of the list
		Description:	Returns the current size of the list as an
						unsigned integer.
		****************************************************************/
		unsigned int	GetSize() const;

		/****************************************************************
		Name:			IsMoveToFrontEnabled
		Input:			N/A
		Output:			"true" if move to front is enabled.
						"false" if move to front is not enabled.
		Description:	Returns whether or not "move to front" is 
						enabled. 
		****************************************************************/
		bool			IsMoveToFrontEnabled() const;

		/****************************************************************
		Name:			EnableMoveToFront
		Input:			N/A
		Output:			N/A
		Description:	Enables "Move to front."
		****************************************************************/
		void			EnableMoveToFront();

		/****************************************************************
		Name:			EnableMoveToFront
		Input:			N/A
		Output:			N/A
		Description:	Disables "Move to front."
		****************************************************************/
		void			DisableMoveToFront();

		/****************************************************************
		Name:			Insert
		Input:			"Data": A single data element to be inserted into
							the list.
						"Position": indicates at which position in the
							list the specified element of data is to be
							inserted.
		Output:			"true": if the operation was succesful.
						"false": if the operation failed or threw an
							error.
		Description:	Inserts a piece of data into the list at the
						specified position. A position of "0" will
						insert the element to the front of the list, and 
						a position greater than the list's size will
						insert the element at the end of the list. 
		****************************************************************/
		bool			Insert(DataType Data, unsigned int Position);

		/****************************************************************
		Name:			Insert
		Input:			"Data": An array of data to be inserted into
							the list.
						"Position": indicates at which position in the
							list the specified element of data is to be
							inserted.
						"Length": The length of the array to be inserted.
		Output:			"true": if the operation was succesful.
						"false": if the operation failed or threw an
							error.
		Description:	Inserts an array of data into the list at the
							specified position. A position of "0" will
							insert the element to the front of the list, and
							a position greater than the list's size will
							insert the element at the end of the list.
		****************************************************************/
		bool			Insert(DataType* Data, unsigned int Position, unsigned int Length);

		/****************************************************************
		Name:			Remove
		Input:			Position: The position at which to remove a node
							from.
		Output:			Returns the node that was removed from the list.
		Description:	Removes a node at the position in the list
							indicated by "Position." A position of 0
							will remove the first node in the list, and
							a position greater than the list's size will
							remove the last node in the list. The 
							node that was removed is then returned by
							value to the caller.
		****************************************************************/
		Node			Remove(unsigned int Position);

		/****************************************************************
		Name:			Sort
		Input:			N/A
		Output:			"true": the sort operation was succesful.
						"false": errors were encountered during the sort.
		Description:	Sorts the list in ascending order. If the list
							is smaller than 4,000 nodes, recursive
							mergesort is used to sort the list. However,
							if the list is greater than 4,000 nodes, then
							an iterative mergesort is used to sort the 
							list.

							This function is reliant on the DataType of
							the List having the comparison operators
							overloaded.
		****************************************************************/
		bool			Sort();

		/****************************************************************
		Name:			Search
		Input:			SearchTerm: the node to search for.
		Output:			A pointer to the first matching node in the list.
		Description:	Searches for a node that matches the value in
							the supplied node "SearchTerm." This 
							variation of "Search" will return  a pointer
							to the first node that is a match. A null
							pointer will be returned if the search term
							was not found in the list.

						If "Move to front" is enabled, then the first
							matching node will be moved to the front of 
							the list.
		****************************************************************/
		Node*			Search(Node SearchTerm);
		Node			SearchAndRemove(Node SearchTerm);
		int				SearchPosition(Node SearchTerm) const;

		const Node&		operator[](const int Index) const;
		Node&			operator[](const int Index);
	};

	template<class DataType>
	inline typename List<DataType>::Node * List<DataType>::Seek(unsigned int Position) {

		if (Position > Size) {
			Position = Size - 1;
		}
		
		Node* P = TopOfList;
		for (unsigned int i = 0; i < Position; i++) {

			if (P != nullptr) {
				P = P->Next;
			}
			else {
				break;
			}
		}
		return P;
	}

	template<class DataType>
	inline bool List<DataType>::Swap(Node * A, Node * B) {

		if (State != State::Valid) {
			return false;
		}
		else {
			try {
				WriteLock();
				DataType Temp = A->Data;
				A->Data = B->Data;
				B->Data = Temp;
				WriteUnlock();
				return true;
			}
			catch (...) {
				return false;
			}
		}
	}

	template<class DataType>
	inline typename List<DataType>::Node * List<DataType>::MergeSort(Node * P) {
		
		if (P == nullptr || P->Next == nullptr) {
			return P;
		}
		Node* Middle = Split(P);
		Node* half = Middle->Next;
		Middle->Next = nullptr;

		return MergeIterative(MergeSort(P), MergeSort(half));
		
	}

	template<class DataType>
	inline typename List<DataType>::Node * List<DataType>::MergeSortIterative(Node * P) {
		
		if (P == nullptr || P->Next == nullptr) {
			return P;
		}

		Node** WorkingList = new Node*[GetSize()];
		//Node* P = TopOfList;
		unsigned int k = 0;
		unsigned int j;
		for (k = 0; k < Size; k++) {
			WorkingList[k] = P;
			P = P->Next;
			WorkingList[k]->Next = nullptr;
		}

		for (unsigned int i = Size; i > 1; i = (i + 1) / 2) {
			for (j = k = 0; k < i; j++, k += 2) {
				WorkingList[j] = MergeIterative(WorkingList[k], WorkingList[k + 1]);
			}
			WorkingList[j] = nullptr;
		}
		return WorkingList[0];
	}

	template<class DataType>
	inline typename List<DataType>::Node * List<DataType>::Merge(Node * A, Node * B) {

		if (A == nullptr) {
			return B;
		}
		else if (B == nullptr) {
			return A;
		}
		else if (A->Data <= B->Data) {
			A->Next = Merge(A->Next, B);
			return A;
		}
		else {
			B->Next = Merge(A, B->Next);
			return B;
		}
	}

	template<class DataType>
	inline typename List<DataType>::Node * List<DataType>::MergeIterative(Node * A, Node * B) {
		
		//if both lists are empty
		if (!A && !B) {
			return 0;
		}
		//either of list is empty
		else if (!A) return B;
		else if (!B) return A;
		else {
			Node* head = NULL;//this will be the head of the newList
			Node* previous = NULL;//this will act as the

								  /* In this algorithm we will keep the
								  previous pointer that will point to the last node of the output list.
								  And, as given we have A & B as pointer to the given lists.

								  The algorithm will keep on going untill either one of the list become empty.
								  Inside of the while loop, it will divide the algorithm in two parts:
								  - First, if the head of the output list is not obtained yet
								  - Second, if head is already there then we will just compare the values and keep appending to the 'previous' pointer.
								  When one of the list become empty we will append the other 'left over' list to the output list.
								  */
			while (A && B) {
				if (!head) {
					if (A->Data <= B->Data) {
						head = A;//setting head of the output list to A
						previous = A; //initializing previous
						A = A->Next;
					}
					else {
						head = B;//setting head of the output list to B
						previous = B;//initializing previous
						B = B->Next;
					}
				}
				else//when head is already set
				{
					if (A->Data <= B->Data) {
						if (previous->Next != A)
							previous->Next = A;
						A = A->Next;//Moved A forward but keeping B at the same position
					}
					else {
						if (previous->Next != B)
							previous->Next = B;
						B = B->Next; //Moved B forward but keeping A at the same position
					}
					previous = previous->Next;//Moving the Output list pointer forward
				}
			}
			//at the end either one of the list would finish
			//and we have to append the other list to the output list
			if (!A)
				previous->Next = B;

			if (!B)
				previous->Next = A;

			return head; //returning the head of the output list
		}
	}

	template<class DataType>
	inline typename List<DataType>::Node * List<DataType>::Split(Node * P) {

		if (P == nullptr) {
			return nullptr;
		}
		
		Node * Slow;
		Node * Fast; 
		Slow = P;
		Fast = P;
		while (Fast->Next != nullptr && Fast->Next->Next != nullptr) {
			Slow = Slow->Next; 
			Fast = Fast->Next->Next;
		}
		return Slow;
	}

	template<class DataType>
	inline List<DataType>::List() {

		this->SetName("DataLib::List");
		this->TopOfList = nullptr;
		this->Size = 0;
		State = State::Empty;
	}

	template<class DataType>
	inline List<DataType>::List(List<DataType>& Copy) {
	}

	template<class DataType>
	inline List<DataType>::List(DataType * Head, unsigned int Length) {

		if (Head == nullptr || Length == 0) {
			State = State::Empty;
		}

		else {

			for (unsigned int i = 0; i < Length; i++) {
				try {
					Insert(Head[i]);
				}
				catch (...) {
					break;
				}
			}

			State = State::Valid;
		}
	}

	template<class DataType>
	inline List<DataType>::~List() {

		State = State::Uninitialized;
		
		if (TopOfList != nullptr) {
			delete TopOfList;
		}
	}

	template<class DataType>
	inline bool List<DataType>::IsEmpty() const {

		if (State == State::Empty) {
			return true;
		}
		else {
			return false;
		}
	}

	template<class DataType>
	inline unsigned int List<DataType>::GetSize() const {
		return Size;
	}

	template<class DataType>
	inline bool List<DataType>::IsMoveToFrontEnabled() const {
		return MoveToFront;
	}

	template<class DataType>
	inline void List<DataType>::EnableMoveToFront() {
		WriteLock(); MoveToFront = true; WriteUnlock();
	}

	template<class DataType>
	inline void List<DataType>::DisableMoveToFront() {
		WriteLock(); MoveToFront = false; WriteUnlock();
	}

	template<class DataType>
	inline bool List<DataType>::Insert(DataType Data, unsigned int Position) {

		try {

			//Empty list case.
			if (IsEmpty()) {

				WriteLock();

				TopOfList = new Node(Data);
				State = State::Valid;
				Size++;

				WriteUnlock();
			}

			else if (State == State::Valid) {

				WriteLock();

				//Insert before TopOfList.
				if (Position == 0) {
					Node* T = new Node(Data, TopOfList);
					TopOfList = T;
				}

				//Insert in middle of list.
				else {
					Node* P = Seek(--Position);
					Node* T = new Node(Data, P->Next);
					P->Next = T;
				}
				Size++;

				WriteUnlock();
			}

			else {
				return false;
			}

			return true;
		}

		catch (...) {
			return false;
		}
	}

	template<class DataType>
	inline bool List<DataType>::Insert(DataType * Data, unsigned int Position, unsigned int Length) {
		

		try {

			//Empty list case.
			if (IsEmpty()) {

				WriteLock();

				for (unsigned int i = 0; i < Length; i++) {
					try {
						Insert(Data[i]);
					}
					catch (...) {
						break;
					}
				}

				State = State::Valid;

				WriteUnlock();
			}

			else if (State == State::Valid) {

				WriteLock();

				//Insert before TopOfList.
				if (Position == 0) {
					Node* T = new Node(Data, TopOfList);
					TopOfList = T;
				}

				//Insert in middle of list.
				else {
					Node* P = Seek(--Position);
					Node* T = new Node(Data, P->Next);
					P->Next = T;
				}
				Size++;

				WriteUnlock();
			}

			else {
				return false;
			}

			return true;
		}

		catch (...) {
			return false;
		}



		if (Head == nullptr || Length == 0) {
			State = State::Empty;
		}

		else {

			for (unsigned int i = 0; i < Length; i++) {
				try {
					Insert(Head[i]);
				}
				catch (...) {
					break;
				}
			}

			State = State::Valid;
		}
	}

	template<class DataType>
	inline typename List<DataType>::Node List<DataType>::Remove(unsigned int Position) {

		if (Position > Size) {
			Position = Size - 1;
		}

		//Empty list condition.
		if (State == State::Empty) {
			DataLib::Exception EmptyCondition;
			EmptyCondition.Error = "Attempt to remove node from empty list!";
			throw EmptyCondition;
		}

		else if (State == State::Locked) {
			DataLib::Exception EmptyCondition;
			EmptyCondition.Error = EXCEPTION_LOCKED;
			throw EmptyCondition;
		}

		//Non-empty, and valid data structure condition.
		else if (State == State::Valid) {

			WriteLock();

			//If we want to remove the first node in the list.
			if (Position == 0) {
				Node* P = TopOfList->Next;
				TopOfList->Next = nullptr;
				if (P == nullptr) { State = State::Empty; }
				Node ReturnValue(*TopOfList);
				delete TopOfList;
				TopOfList = P;
				Size--;
				WriteUnlock();
				return ReturnValue;
			}

			//If we want the last node in the list.
			else if (Position == Size - 1) {
				Node* P = Seek(--Position);
				Node ReturnValue(*P->Next);
				delete P->Next;
				P->Next = nullptr;
				Size--;
				WriteUnlock();
				return ReturnValue;
			}

			else {
				Node* P = Seek(--Position);
				Node* T = P->Next->Next;
				Node ReturnValue(*P->Next);
				delete P->Next;
				P->Next = T;
				Size--;
				WriteUnlock();
				return ReturnValue;
			}
		}
		else {
			DataLib::Exception UnknownError;
			UnknownError.Error = "An unknown error occurred!";
			throw UnknownError;
		}
		return DataType();
	}

	template<class DataType>
	inline bool List<DataType>::Sort() {
		
		if (State == State::Empty || Size == 1) {
			return true;
		}
		else if (State == State::Valid) {
			if (Size <= 4000) {
				TopOfList = MergeSort(TopOfList);
			}
			else if (Size > 4000) {
				TopOfList = MergeSortIterative(TopOfList);
			}
			else {
				return false;
			}
			return true;
		}
		else {
			return false;
		}
	}

	template<class DataType>
	inline typename List<DataType>::Node * List<DataType>::Search(Node SearchTerm) {

		if (State != State::Valid) {
			return nullptr;
		}
		else {

			Node* P = TopOfList;

			for (unsigned int i = 0; i < Size; i++) {

				if (P->Next != nullptr && P->Next->Data == SearchTerm.Data) {

					if (IsMoveToFrontEnabled()) {
						
						Node * temp = P->Next;

						if (temp != nullptr) {
							P->Next = temp->Next;
							temp->Next = TopOfList;
							TopOfList = temp;
						}

					}
					return P->Next;
				}

				else {
					P = P->Next;
				}
			}
			return nullptr;
		}
	}

	template<class DataType>
	inline typename List<DataType>::Node List<DataType>::SearchAndRemove(Node SearchTerm) {
		
		if (State != State::Valid) {
			return nullptr;
		}
		else {

			Node* P = TopOfList;

			for (unsigned int i = 0; i < Size; i++) {

				if (P->Data == SearchTerm.Data) {

					Node T(P);

					WriteLock();
					Remove(i);
					WriteUnlock();

					return T;
				}
				else {
					P = P->Next;
				}
			}
			return nullptr;
		}
	}

	template<class DataType>
	inline int List<DataType>::SearchPosition(Node SearchTerm) const {
		
		if (State != State::Valid) {
			return nullptr;
		}
		else {

			Node* P = TopOfList;

			for (unsigned int i = 0; i < Size; i++) {

				if (P->Data == SearchTerm.Data) {

					return i;
				}
				else {
					P = P->Next;
				}
			}
			return nullptr;
		}
	}

	template<class DataType>
	inline List<DataType>::Node::Node() {
		this->Next = nullptr;
	}

	template<class DataType>
	inline List<DataType>::Node::Node(Node & Copy) {
		this->Data = Copy.Data;
		this->Next = nullptr;
	}

	template<class DataType>
	inline List<DataType>::Node::Node(DataType Data) {
		this->Data = Data;
		this->Next = nullptr;
	}

	template<class DataType>
	inline List<DataType>::Node::Node(DataType Data, Node * Next) {
		this->Data = Data;
		this->Next = Next;
	}

	template<class DataType>
	inline List<DataType>::Node::~Node() {}

	template<class DataType>
	inline List<DataType>::Node::operator DataType() const {
		return Data;
	}

	template<class DataType>
	inline typename List<DataType>::Node & List<DataType>::Node::operator=(const DataType & B) {	
		Data = B;
		return *this;
	}

	template<class DataType>
	inline const typename List<DataType>::Node & List<DataType>::operator[](const int Index) const {
		return (Seek(Index));
	}

	template<class DataType>
	inline typename List<DataType>::Node& List<DataType>::operator[](const int Index) {
		return *Seek(Index);
	}

}

#endif
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

		typedef bool(*callback_compare)(DataType, DataType);
		typedef bool(List<DataType>::*method_compare)(DataType, DataType);
		

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

		List();
		List(List<DataType> &Copy);
		List(DataType* Head, unsigned int Length);
		~List();

		bool			IsEmpty() const;
		unsigned int	GetSize() const;
		bool			IsMoveToFrontEnabled() const;
		void			EnableMoveToFront();
		void			DisableMoveToFront();

		bool			Insert(DataType Data, unsigned int Position);
		Node			Remove(unsigned int Position);

		bool			Sort();

		Node*			Search(Node SearchTerm);
		Node			Search(char * SearchTerm);
		Node			SearchAndRemove(Node SearchTerm);
		Node			SearchAndRemove(char* SearchTerm);
		int				SearchPosition(Node SearchTerm) const;
		int				SearchPosition(char * SearchTerm) const;

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
		int k = 0;
		int j;
		for (k = 0; k < Size; k++) {
			WorkingList[k] = P;
			P = P->Next;
			WorkingList[k]->Next = nullptr;
		}

		for (int i = Size; i > 1; i = (i + 1) / 2) {
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

				TopOfList = new Node(Data);
				State = State::Valid;
				Size++;
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

				if (P->Data == SearchTerm.Data) {

					if (IsMoveToFrontEnabled()) {
						Swap(TopOfList, P);
					}
					return P;
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
		return Seek(Index);
	}

}

#endif
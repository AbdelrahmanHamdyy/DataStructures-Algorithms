#include <iostream>
using namespace std;

// ================== Class Node ========================

template<typename T>
class Node
{
private :
	T item;	
	Node<T>* next;	
public :

	Node( )
	{
		next= nullptr;
	} 

	Node( T newItem) 
	{
		item = newItem;
		next= nullptr;

	}

	void setItem( T newItem)
	{
		item = newItem;
	} 

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} 

	T getItem() const
	{
		return item;
	} 

	Node<T>* getNext() const
	{
		return next;
	}
}; // end Node

// ================== Class Linked List ========================

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;

public:

	LinkedList()
	{
		Head = nullptr;
	}

	~LinkedList()
	{
		DeleteAll(); 
	}

	// Prints the linked list in the required format
	// DON'T CHANGE ANYTHING INSIDE THIS FUNCTION *********
	// BECAUSE THE AUTOMATIC JUDGE COMPARES FOR THIS FORMAT
	void PrintList()	const
	{
		Node<T> *p = Head;
		while(p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
		cout << endl;
	}

	// DO NOT CHANGE ANYTHING IN THIS FUNCTION *********
	void ReadList() 
	{
		int val;
		cin>>val;
		while(val != -1)
		{
			this->InsertEnd(val);
			cin>>val;
		}
	}

	// you should NOT change this function
	void InsertEnd(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		if (!Head)
		{
			Head = R;
			return;
		}
		Node<T> *p = Head;
		while (p->getNext())
			p = p->getNext();
		p->setNext(R);
	}

	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	int GetMin(Node<T>* head)
	{
		int min = head->getItem();
		for (Node<T>* temp = head; temp != NULL; temp = temp->getNext())
		{
			if (temp->getItem() < min)
				min = temp->getItem();
		}
		return min;
	}

	void Sort(Node<T>* ptr)
	{
		if (ptr)
		{
			while (ptr->getNext())
			{
				int min = GetMin(ptr->getNext());
				if (ptr->getItem() > min)
				{
					for (Node<int>* temp = ptr->getNext(); temp != NULL; temp = temp->getNext())
					{
						if (temp->getItem() == min)
						{
							int x = ptr->getItem();
							ptr->setItem(temp->getItem());
							temp->setItem(x);
						}
					}
				}
				ptr = ptr->getNext();
			}
		}
	}
	//////////////////////////////////////////

	/// TODO: ADD ANY REQUIRED FUNCTIONS HERE
	int countAnomalies()
	{
		if (!Head || !(Head->getNext())) // Empty list or only 2 elements
			return 0;
		int count = 0;
		Node<T>* prev2 = Head;
		Node<T>* prev1 = Head->getNext();
		Node<T>* curr = Head->getNext()->getNext();
		while (curr)
		{
			if (curr->getItem() > (prev2->getItem() + prev1->getItem()))
				count++;
			prev2 = prev2->getNext();
			prev1 = prev1->getNext();
			curr = curr->getNext();
		}
		return count;
	}

	void insertBeforePositive()
	{
		if (!Head) // Empty list
			return;
		Node<T>* prev = Head;
		Node<T>* curr = Head->getNext();
		if (prev->getItem() > 0)
		{
			int item = (-1) * prev->getItem();
			Node<T>* new_node = new Node<T>(item);
			new_node->setNext(Head);
			Head = new_node;
		}
		while (curr)
		{
			if (curr->getItem() > 0)
			{
				int item = (-1) * curr->getItem();
				Node<T>* new_node = new Node<T>(item);
				new_node->setNext(curr);
				prev->setNext(new_node);
				prev = prev->getNext();
			}
			prev = prev->getNext();
			curr = curr->getNext();
		}
	}

	void deleteSecondLargest()
	{
		if (!Head || !Head->getNext()) // Empty list
			return;
		int max = 0;
		for (Node<T>* temp = Head; temp != NULL; temp = temp->getNext())
		{
			if (temp->getItem() > max)
				max = temp->getItem();
		}
		int max2 = 0;
		for (Node<T>* temp = Head; temp != NULL; temp = temp->getNext())
		{
			if (temp->getItem() > max2 && temp->getItem() != max)
				max2 = temp->getItem();
		}
		if (max2 == 0)
			return;
		Node<T>* prev = Head;
		Node<T>* curr = Head->getNext();
		while (curr)
		{
			// If the second largest elements are at the beginning
			if (prev->getItem() == max2)
			{
				Head = Head->getNext();
				delete prev;
				prev = Head;
				curr = curr->getNext();
			}
			else if (curr->getItem() == max2)
			{
				prev->setNext(curr->getNext());
				delete curr;
				curr = prev->getNext();
			}
			else
			{
				prev = prev->getNext();
				curr = curr->getNext();
			}
		}
	}

	void reverseHalf()
	{
		if (!Head)
			return;
		int size = 0;
		Node<T>* ptr = Head;
		while (ptr)
		{
			size++;
			ptr = ptr->getNext();
		}
		if (size % 2 == 0)
			size /= 2;
		else
			size = (size / 2) + 1;
		if (size == 1)
			return;
		Node<T>* curr = Head;
		Node<T>* prev = NULL;
		Node<T>* next = NULL;

		while (size > 0) {
			next = curr->getNext();
			curr->setNext(prev);
			prev = curr;
			curr = next;
			size--;
		}
		Head->setNext(curr);
		Head = prev;
	}

	void sortedOddsAndEvens(LinkedList<T>& L)
	{
		if (!Head && !L.Head)
			return;
		Node<T>* prev1, * ptr1, * prev2, * ptr2;
		prev1 = Head;
		prev2 = L.Head;
		if (!prev1)
			ptr1 = NULL;
		else if (!(prev1->getNext()))
			ptr1 = NULL;
		else
			ptr1 = Head->getNext();
		if (!prev2)
			ptr2 = NULL;
		else if (!(prev2->getNext()))
			ptr2 = NULL;
		else
			ptr2 = L.Head->getNext();
		while (prev1 || prev2)
		{
			if (prev1)
			{
				if (prev1->getItem() % 2 == 0)
				{
					L.InsertEnd(prev1->getItem());
					Head = Head->getNext();
					delete prev1;
					prev1 = Head;
					if (prev1)
						ptr1 = prev1->getNext();
				}
				else if (ptr1 && ptr1->getItem() % 2 == 0)
				{
					L.InsertEnd(ptr1->getItem());
					prev1->setNext(ptr1->getNext());
					delete ptr1;
					ptr1 = prev1->getNext();
				}
				else
				{
					if (prev1)
						prev1 = prev1->getNext();
					if (ptr1)
						ptr1 = ptr1->getNext();
				}
			}
			if (prev2)
			{
				if (prev2->getItem() % 2 != 0)
				{
					InsertEnd(prev2->getItem());
					L.Head = L.Head->getNext();
					delete prev2;
					prev2 = L.Head;
					if (prev2)
						ptr2 = prev2->getNext();
				}
				else if (ptr2 && ptr2->getItem() % 2 != 0)
				{
					InsertEnd(ptr2->getItem());
					prev2->setNext(ptr2->getNext());
					delete ptr2;
					ptr2 = prev2->getNext();
				}
				else
				{
					if (prev2)
						prev2 = prev2->getNext();
					if (ptr2)
						ptr2 = ptr2->getNext();
				}
			}
		}
		Node<int>* ptr = Head;
		Sort(ptr);
		ptr = L.Head;
		Sort(ptr);
	}
	//////////////////////////////////////////


}; // end of class LinkedList


// ================== The Main Function ========================

/// TODO: This main is partially implemented, complete it to be exactly as specified in the requirements' document
int main()
{
	try {
		//Don’t use any cin or cout in the code 
		// (except in [“choice” equals 1] part in the main function and must be exactly the same as required). 
		// Whenever you want to read or print linked list elements, just use:
		//-	 L.PrintList ( ) when you want to print the elements of linked list L to the user.
		//-	 L.ReadList ( ) when you want to read the elements of linked list L from the user.
		// Note: you must NOT change the implementation of these functions: L.PrintList() or L.ReadList().


		int choice;
		cin >> choice;
		if (choice == 1)
		{
			/// TODO: Put the needed code here
			LinkedList<int> L1;
			L1.ReadList();
			int ca = L1.countAnomalies();
			std::cout << ca;
		}
		else if (choice == 2)
		{
			/// TODO: Put the needed code here
			LinkedList<int> L1;
			L1.ReadList();
			L1.insertBeforePositive();
			L1.PrintList();
		}
		else if (choice == 3)
		{
			/// TODO: Put the needed code here
			LinkedList<int> L1;
			L1.ReadList();
			L1.deleteSecondLargest();
			L1.PrintList();
		}
		else if (choice == 4)
		{
			/// TODO: Put the needed code here
			LinkedList<int> L1;
			L1.ReadList();
			L1.reverseHalf();
			L1.PrintList();
		}
		else if (choice == 5)
		{
			/// TODO: Put the needed code here
			LinkedList<int> L1, L2;
			L1.ReadList();
			L2.ReadList();
			L1.sortedOddsAndEvens(L2);
			L1.PrintList();
			L2.PrintList();
		}
		// Note: Do [NOT] write system("pause") or cin >> c; or anything similar to halt execution
	}
	catch (...) {
		cout << "Exception";
	}
	return 0;
}


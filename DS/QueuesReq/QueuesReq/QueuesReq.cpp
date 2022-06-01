#include <iostream>
#include "math.h"
using namespace std;

template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
public:
	Node();
	Node(const T& r_Item);
	Node(const T& r_Item, Node<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
}; // end Node

template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}


template <typename T>
class LinkedQueue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	void print() const;
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ);
};

/*
Function: Queue()
The constructor of the Queue class.

*/
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

template<typename T>
void LinkedQueue<T>::print() const
{
	Node<T>* ptr = frontPtr;
	while (ptr) 
	{
		cout << ptr->getItem() << " ";
		ptr = ptr->getNext();
	}
	cout << endl;
}

int GetSize(LinkedQueue<int> Q1)
{
	int x;
	int size = 0;
	while (!Q1.isEmpty())
	{
		Q1.dequeue(x);
		size++;
	}
	return size;
}

void Swap(LinkedQueue<int>& Q1, LinkedQueue<int>& Q2)
{
	int x;
	LinkedQueue<int> temp;
	while (!Q1.isEmpty())
	{
		Q1.dequeue(x);
		temp.enqueue(x);
	}
	while (!Q2.isEmpty())
	{
		Q2.dequeue(x);
		Q1.enqueue(x);
	}
	while (!temp.isEmpty())
	{
		temp.dequeue(x);
		Q2.enqueue(x);
	}
}
void switchHalves(LinkedQueue<int>& Q1, LinkedQueue<int>& Q2)
{
	// TODO: implement this function
	int x;
	LinkedQueue<int> HQ1;
	LinkedQueue<int> HQ2;
	LinkedQueue<int> temp;
	int size1 = GetSize(Q1);
	int size2 = GetSize(Q2);
	for (int i = 0; i < ceil(size1 / 2.0); i++)
	{
		Q1.dequeue(x);
		HQ1.enqueue(x);
	}
	for (int i = 0; i < ceil(size2 / 2.0); i++)
	{
		Q2.dequeue(x);
		HQ2.enqueue(x);
	}
	Swap(Q2, HQ2);
	while (!HQ1.isEmpty())
	{
		HQ1.dequeue(x);
		Q2.enqueue(x);
	}
	LinkedQueue<int> temp2;
	while (!HQ2.isEmpty())
	{
		HQ2.dequeue(x);
		temp2.enqueue(x);
	}
	while (!Q1.isEmpty())
	{
		Q1.dequeue(x);;
		temp2.enqueue(x);
	}
	while (!temp2.isEmpty())
	{
		temp2.dequeue(x);
		Q1.enqueue(x);
	}
}

int main()
{
	try{
		// Create the queues
		LinkedQueue<int> Q1;
		LinkedQueue<int> Q2;

		// Read first queue
		int val;
		cin >> val;
		while (val != -1)
		{
			Q1.enqueue(val);
			cin >> val;
		}
		
		// Read second queue
		cin >> val;
		while (val != -1)
		{
			Q2.enqueue(val);
			cin >> val;
		}

		// call switchHalves
		switchHalves(Q1, Q2);

		Q1.print();
		Q2.print();
		
	} catch(...){
		cout<<"Exception";
	}
	
	return 0;
}
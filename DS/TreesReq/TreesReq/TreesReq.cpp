
// PLEASE READ THE ( TODO ) COMMENTS

#include <iostream>
using namespace std;

// ================== THE NODE CLASS ======================

class Node
{
private:
	int data;
	Node *left;
	Node *right;
public:
	Node(int val);
	void setdata(int d);
	int getdata();
	void setright(Node* p);
	Node*& getright();
	void setleft(Node* p);	
	Node*& getleft();

};

Node::Node(int val)
{
	data = val;
	left = right = nullptr;
}

void Node::setdata(int d)
{
	data = d;
}
int Node::getdata()
{
	return data;
}
void Node::setleft(Node* p)
{
	left = p;
}
Node*& Node::getleft()
{
	return left;
}
void Node::setright(Node* p)
{
	right = p;
}
Node*& Node::getright()
{
	return right;
}

// ================== THE BINARY SEARCH TREE CLASS ======================

class BSTree
{
private:
	Node* root;

	// Utility Functions - Recursive Functions --------------------------

	static void rec_insertBST(Node *& subRoot, int key);
	static void rec_destroy_tree(Node *& subRoot);

	// TODO: HERE, ADD THE UTILITY FUNCTION(S) THAT YOU NEED

public:
	BSTree(void);
	~BSTree(void);

	// Public Functions --------------------------

	void insertBST(int key); 
	void destroy_tree(); 

	// HERE IS THE REQUIRED PUBLIC FUNCTION
	void leftRightSummation(); // NOTE: DON'T CHANGE THE SIGNATURE OF THIS FUNCTION

};

// Utility Functions - Recursive Functions --------------------------

void BSTree::rec_insertBST(Node *& subRoot, int key)
{
	if (subRoot == nullptr)
		subRoot = new Node(key); 
	else if (subRoot->getdata() < key)
	{
		rec_insertBST(subRoot->getright(), key);  
	}
	else
	{
		rec_insertBST(subRoot->getleft(), key); 
	}
}

void BSTree::rec_destroy_tree(Node *& subRoot)
{
	if (subRoot != nullptr)
	{
		rec_destroy_tree(subRoot->getleft());

		rec_destroy_tree(subRoot->getright());

		delete subRoot;
		subRoot = nullptr; 
	}
}

// TODO: HERE, ADD THE IMPLEMENTATION OF THE UTILITY FUNCTION(S) THAT YOU NEED


// Public Functions ---------------------------------

BSTree::BSTree()
{
	root = nullptr;
}

BSTree::~BSTree()
{
	destroy_tree();
}

void BSTree::insertBST(int key)
{
	rec_insertBST(root, key);
}

void BSTree::destroy_tree() 
{
	rec_destroy_tree(root); 
}

template < typename T>
class Node2
{
private:
	T item; // A data item
	Node2<T>* next; // Pointer to next node
public:
	Node2();
	Node2(const T& r_Item);
	Node2(const T& r_Item, Node2<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(Node2<T>* nextNodePtr);
	T getItem() const;
	Node2<T>* getNext() const;
}; // end Node

template < typename T>
Node2<T>::Node2()
{
	next = nullptr;
}

template < typename T>
Node2<T>::Node2(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
Node2<T>::Node2(const T& r_Item, Node2<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node2<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node2<T>::setNext(Node2<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node2<T>::getItem() const
{
	return item;
}

template < typename T>
Node2<T>* Node2<T>::getNext() const
{
	return next;
}

template<class T>
class QueueADT
{
public:
	/** Sees whether this queue is empty.
	 @return  True if the queue is empty, or false if not. */
	virtual bool isEmpty() const = 0;

	/** Adds a new entry to the back of this queue.
	 @post  If the operation was successful, newEntry is at the
		back of the queue.
	 @param newEntry  The object to be added as a new entry.
	 @return  True if the addition is successful or false if not. */
	virtual bool enqueue(const T& newEntry) = 0;

	/** Copies the front item of the queue to the passed parameter and removes it from queue
	 @post  If the operation was successful, the front of the queue
		would be copied to FrontEntry parameter and removed from the queue.
	 @return  True if the removal is successful or false if not. */
	virtual bool dequeue(T& FrontEntry) = 0;

	/** Copies the front item of the queue to the passed parameter without removing it from queue
	 @pre  The queue is not empty.
	 @post  The front of the queue has been copied to FrontEntry param , and the
		queue is unchanged.
	 @return  The front of the queue. */
	virtual bool peek(T& FrontEntry) const = 0;

	/** Destroys this queue and frees its memory. */
	virtual ~QueueADT() { }
}; // end QueueADT

template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:

	Node2<T>* backPtr;
	Node2<T>* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node2<T>* newNodePtr = new Node2<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue


  /////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	Node2<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////
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
	Node2<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node2<T>* ptr = new Node2<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node2<T>* ptr = new Node2<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

void printTwice(int n)
{
	cout << n << " " << n << " " << 2 * n << " ";
}

void print(Node* n)
{
	cout << n << " ";
}

void printWithSum(int n1, int n2)
{
	cout << n1 << " " << n2 << " " << n1 + n2 << " ";
}

void Print(LinkedQueue<int>& q)
{
	int size = 0;
	int x;
	LinkedQueue<int> temp;
	while (!q.isEmpty())
	{
		q.dequeue(x);
		temp.enqueue(x);
		size++;
	}
	if (size == 1)
	{
		temp.peek(x);
		printTwice(x);
		return;
	}
	int first = 0;
	int last = 0;
	temp.peek(x);
	first = x;
	while (!temp.isEmpty())
		temp.dequeue(x);
	last = x;
	printWithSum(first, last);
}

void BSTree::leftRightSummation()
{
	// TODO: ADD YOUR CODE OF THE PUBLIC FUNCTION HERE
	if (root == NULL)
	{
		cout << "NULL tree";
		return;
	}
	Node* x;
	LinkedQueue<int> Q;
	LinkedQueue<Node*> Q1;
	LinkedQueue<Node*> Q2;
	Q1.enqueue(root);
	Node* head = root;
	while (!Q1.isEmpty() || !Q2.isEmpty())
	{
		while (!Q1.isEmpty())
		{
			Q1.dequeue(x);
			head = x;
			Q.enqueue(head->getdata());
			if (head->getleft())
				Q2.enqueue(head->getleft());
			if (head->getright())
				Q2.enqueue(head->getright());
		}
		if (!Q.isEmpty())
			Print(Q);
		while (!Q2.isEmpty())
		{
			Q2.dequeue(x);
			head = x;
			Q.enqueue(head->getdata());
			if (head->getleft())
				Q1.enqueue(head->getleft());
			if (head->getright())
				Q1.enqueue(head->getright());
		}
		if (!Q.isEmpty())
			Print(Q);
	}
}

// ================== THE MAIN FUNCTION ======================

// NOTE: THE MAIN IS TOTALLY DONE FOR YOU
int main()
{
	try {

		BSTree bst;

		// Read the elements of the tree (-1 indicates end of the tree)
		int val;
		cin >> val;
		while (val != -1)
		{
			bst.insertBST(val);
			cin >> val;
		}

		// Call the required public function
		bst.leftRightSummation(); // the function should print inside it, so no needed modifications in the main function

	} catch(...){
		cout<<"Exception";
	}

	return 0;
}

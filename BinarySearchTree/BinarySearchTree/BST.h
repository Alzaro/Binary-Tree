#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////
// File :			BST.h
// Author :			Corey Feist
// Purpose :		Driver of the Binary Search Tree class
////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Type> class BST
{
private:
	struct Node
	{
		Type data;
		Node* left, *right;
		Node(Type _data, Node* _left = nullptr, Node* _right = nullptr) : left(_left), right(_right), data(_data) { }
	};

	Node* Root;

	Node* PreOrderHELPER(Node* _node)
	{
		if (_node != nullptr)
		{
			PreOrderHELPER(_node->left);
			PreOrderHELPER(_node->right);
		}
		return _node;
	}
	void PreOrderCOPY(Node* _node)
	{
		if (_node != nullptr)
		{
			insert(_node->data);
			PreOrderCOPY(_node->left);
			PreOrderCOPY(_node->right);
		}
	}
	void PostOrderCLEAR(Node* _node)
	{
		if (_node != nullptr)
		{
			PostOrderCLEAR(_node->left);
			PostOrderCLEAR(_node->right);
			delete _node;
		}
	}
	void InOrderPRINT(Node* _node) const
	{
		if (_node != nullptr)
		{
			InOrderPRINT(_node->left);
			cout << _node->data << ' ';
			InOrderPRINT(_node->right);
			
		}
	}

public :
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constuctor
	// Notes : constucts an empty BST
	/////////////////////////////////////////////////////////////////////////////
	BST() { Root = nullptr; }

	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys the BST cleaning up any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	~BST() { clear(); delete Root; }

	/////////////////////////////////////////////////////////////////////////////
	// Function : assignment operator
	/////////////////////////////////////////////////////////////////////////////
	BST& operator=(const BST& _other);

	/////////////////////////////////////////////////////////////////////////////
	// Function: copy constructor
	/////////////////////////////////////////////////////////////////////////////
	BST(const BST& that);

	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :  v - the item to insert 
	/////////////////////////////////////////////////////////////////////////////
	void insert(const Type& _data);

	/////////////////////////////////////////////////////////////////////////////
	// Function : findAndRemove
	// Parameters : v - the item to find (and remove if it is found)
	// Return : bool - true if the item was removed, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& _data);


	/////////////////////////////////////////////////////////////////////////////
	// Function : find
	// Parameters : v - the item to find
	// Return : bool - true if the item was found, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool find(const Type& _data) const;


	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the BST, cleaning up any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	void clear();

	/////////////////////////////////////////////////////////////////////////////
	// Function : printInOrder
	// Notes : prints the contents of the BST to the screen, in ascending order
	/////////////////////////////////////////////////////////////////////////////
	void printInOrder() const;

};

//assignement operator
template <typename Type>
BST<Type>& BST<Type>::operator=(const BST& _other)
{
	if (this != &_other)
	{
		clear();
		Node* newNode = _other.Root;
		PreOrderCOPY(newNode);
	}
	return *this;
}

//copy constructor
template <typename Type>
BST<Type>::BST(const BST& _other) : BST()
{
	*this = _other;
}

template <typename Type>
void BST<Type>::insert(const Type& _data)
{
	if (Root != nullptr)
	{
		Node* newNode = new Node(_data, nullptr, nullptr);
		Node* current = Root;
		Node* parent = Root;
		current = (newNode->data < current->data) ? (current->left) : (current->right);
		while (current != nullptr)
		{
			parent = current;
			if (newNode->data < current->data)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		if (newNode->data < parent->data)
		{
			parent->left = newNode;
		}
		else 
		{
			parent->right = newNode;
		}
	}
	else
	{
		Node* newNode = new Node(_data);
		Root = newNode;
	}
}
template <typename Type>
bool BST<Type>::findAndRemove(const Type& _data)
{
	if (Root != nullptr)
	{
		if (Root->data == _data)
		{
			if (Root->left == nullptr)
			{
				Node* temp = Root;
				Root = Root->right;
				delete temp;
				return true;
			}
			if (Root->left == nullptr && Root->right == nullptr)
			{
				delete Root;
				Root = nullptr;
			}
			Node* current = Root->left;
			Node* parent = Root->left;
			
			while (current->right != nullptr)
			{
				parent = current;
				current = current->right;
			}
			Root->data = current->data;
			if (current->left != nullptr)
			{
				parent->right = current->left;
			}
			else 
			{
				parent->right = nullptr;
			}
			delete current;
			return true;
		}
		Node* current = Root;
		Node* parent = Root;
		current = (current->data < _data) ? (current->right) : (current->left);
		while (current != nullptr && current->data != _data)
		{
			parent = current;
			current = (current->data < _data) ? (current->right) : (current->left);
		}
		if (current != nullptr)
		{
			if (current->data == _data)
			{
				if (parent->left == current)
				{
					if (current->left == nullptr && current->right == nullptr)
					{
						parent->left = nullptr;
						delete current;
						return true;
					}
					else if (current->left == nullptr)
					{
						parent->left = current->right;
						delete current;
						return true;
					}
					else if (current->right == nullptr)
					{
						parent->left = current->left;
						delete current;
						return true;
					}
					else
					{
						Node* minParent = current->right;
						Node* minNode = current->right;
						while (minNode->left != nullptr)
						{
							parent = minNode;
							minNode = minNode->left;
						}
						current->data = minNode->data;
						if (minNode->right != nullptr)
						{
							minParent->left = minNode->right;
						}
						else
						{
							minParent->left = nullptr;
						}
						//parent->data = minParent->data;
						delete minNode;
						return true;
					}
				}
				else if (parent->right == current)
				{
					if (current->left == nullptr && current->right == nullptr)
					{
						parent->right = nullptr;
						delete current;
						return true;
					}
					else if (current->left == nullptr)
					{
						parent->right = current->right;
						delete current;
						return true;
					}
					else if (current->right == nullptr)
					{
						parent->right = current->left;
						delete current;
						return true;
					}
					else
					{
						Node* minParent = current->right;
						Node* minNode = current->right;
						while (minNode->left != nullptr)
						{
							parent = minNode;
							minNode = minNode->left;
						}
						current->data = minNode->data;
						if (minNode->right != nullptr)
						{
							minParent->left = minNode->right;
						}
						else
						{
							minParent->left = nullptr;
						}
						//parent->data = minParent->data;
						delete minNode;
						return true;
					}
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

template <typename Type>
bool BST<Type>::find(const Type& _data) const
{
	if (Root != nullptr)
	{
		Node* current = Root;
		while (current != nullptr && current->data != _data  )
		{
			current = (current->data < _data) ? (current->right) : (current->left);
		}
		if (current != nullptr)
		{
			if (current->data == _data)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}
	return false;
	

}

template <typename Type>
void BST<Type>::clear()
{
	Node* current = Root;
	PostOrderCLEAR(current);
	Root = nullptr;
}

template <typename Type>
void BST<Type>::printInOrder() const
{
	Node* current = Root;
	InOrderPRINT(current);
	cout << '\n';
}
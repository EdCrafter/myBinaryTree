#pragma once
#include <iostream>

template <class T>
class binaryTree {
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node(T data, Node* left=nullptr, Node* right = nullptr) {
			this->data = data;
			this->left = left;
			this->right = right;
		}
	};
	Node* root = nullptr;
	void insert(Node* newNode);
	void destroyTree(Node*& deleteRoot);
public:
	typedef void* nodePtr;
	void copyTree(nodePtr& tree1, nodePtr const tree2);
	nodePtr getRoot() {
		return root;
	}
	binaryTree() = default;
	binaryTree(const binaryTree<T>& other) {
		destroyTree(root);
		copyTree((nodePtr&)root, (nodePtr)other.root);
	}
	binaryTree<T>& operator=(const binaryTree<T>& other) {
		destroyTree(root);
		copyTree((nodePtr&)root, (nodePtr)other.root);
		return *this;
	};
	void insert(T data) {
		Node* newNode = new Node(data);
		insert(newNode);
	}
	binaryTree(const std::initializer_list<T>& initList) {
		root = nullptr;
		for (auto i = initList.begin(); i != initList.end(); i++) {
			insert(*i);
		}
	}
	void print(nodePtr temp, int depth=0) const {
		Node* newNode =(Node*) temp;
		if (!temp) {
			return;
		}
		print(newNode->left, depth+1);
		for (int i = 0; i < depth; i++) {
			std::cout<< "<<< ";
		}
		std::cout << newNode->data << "\n";
		print(newNode->right, depth+1);
	}
	void remove(T data) {
		Node* temp = root;
		Node* parent = nullptr;
		while (temp &&(temp->data != data)) {
			parent = temp;
			if (temp->data > data) {
				temp = temp->left;
			}
			else{
				temp = temp->right;
			}
		}
		if (!temp) return;
		if (temp->left && temp->right) {
			if (!parent) root = temp->right;
			else if (parent->left == temp) {
				parent->left = temp->right;
			}
			else 
			{
				parent->right = temp->right;
			}
			insert(temp->left);
		}
		else if (!temp->left) {
			if (!parent) root = temp->right;
			else if (parent->left == temp) {
				parent->left = temp->right;
			}
			else 
			{
				parent->right = temp->right;
			}
		}
		else if (!temp->right) {
			if (!parent) root = temp->left;
			else if (parent->left == temp) {
				parent->left = temp->left;
			}
			else 
			{
				parent->right = temp->left;
			}
		}
		delete temp;
		
	}
	
	bool empty() {
		return (bool)(!root);
	}
	bool search(T data) {
		Node* temp = root;
		while (temp) {
			if (temp->data == data) return true;
			else if (temp->data > data) {
				temp = temp->left;
			}
			else  {
				temp = temp->right;
			}
		}
		return false;
	}
	//void inOrder(nodePtr& root, std::vector<T>& arr) = default;
	//{
		/*Node*& temp = (Node*&)root;
		if (!temp) return;
		inOrder((nodePtr&)temp->left,arr);
		arr.push_back(temp->data);
		inOrder((nodePtr&)temp->right,arr);
	}*/
	void clear() {
		destroyTree(root);
	}
	~binaryTree() {
		destroyTree(root);
	}
};

template<typename T>
void binaryTree<T>::insert(Node* newNode) {
	if (root == nullptr) {
		root = newNode;
		return;
	}
	Node* temp = root;
	Node* parent = root;
	while (temp) {
		parent = temp;
		if (temp->data == newNode->data) {
			delete newNode;
			return;
		}
		else if (temp->data > newNode->data) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	if (parent->data > newNode->data) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
}

template<typename T>
void binaryTree<T>::copyTree(nodePtr& tree1, nodePtr const tree2) {
	Node*& temp1 = (Node*&)tree1;
	Node* temp2 = (Node*)tree2;
	if (!temp2) return;
	temp1 = new Node(temp2->data);
	copyTree((nodePtr&)temp1->left, (nodePtr&)temp2->left);
	copyTree((nodePtr&)temp1->right, (nodePtr&)temp2->right);
}

template<typename T>
void binaryTree<T>::destroyTree(Node*& delRoot) {
	if (delRoot == nullptr) return;
	destroyTree(delRoot->left);
	destroyTree(delRoot->right);
	delete delRoot;
	delRoot = nullptr;
}
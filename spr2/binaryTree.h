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
	void print(Node* temp, int depth = 0) const;
	size_t subtreeSize(Node*& subRoot) ;
	template<typename Func>
	void doForNode(Node*& currNode, Func func);
public:
	typedef void* nodePtr;
	void copyTree(nodePtr& tree1, nodePtr const tree2);
	nodePtr getRoot() {
		return root;
	}
	binaryTree() = default;
	binaryTree(const binaryTree& other) {
		destroyTree(root);
		copyTree((nodePtr&)root, (nodePtr)other.root);
	}
	binaryTree(binaryTree&& other) noexcept
	{
		root = other.root;
		other.root = nullptr;
	}
	binaryTree<T>& operator=(const binaryTree<T>& other) {
		destroyTree(root);
		copyTree((nodePtr&)root, (nodePtr)other.root);
		return *this;
	};
	void insert(const T data) {
		Node* newNode = new Node(data);
		insert(newNode);
	}
	binaryTree(const std::initializer_list<T>& initList) {
		root = nullptr;
		for (auto i = initList.begin(); i != initList.end(); i++) {
			insert(*i);
		}
	}
	void show() const {
		print(root);
	}
	void remove(T data);
	bool empty() const {
		return (bool)(!root);
	}
	bool search(T data) const {
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
	void inOrder(nodePtr root, std::vector<T>& arr);
	size_t size();
	T findMin() const;
	T findMax() const;
	template<typename Func>
	binaryTree<T>& doForAll(Func func); // (function) or also for lambda ([](){})
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

template<typename T>
void binaryTree<T>::print(Node* temp, int depth) const {
	if (!temp) {
		return;
	}
	print(temp->left, depth + 1);
	for (int i = 0; i < depth; i++) {
		std::cout << "<<< ";
	}
	std::cout << temp->data << "\n";
	print(temp->right, depth + 1);
}

template<typename T>
void binaryTree<T>::remove(T data) {
	Node* temp = root;
	Node* parent = nullptr;
	while (temp && (temp->data != data)) {
		parent = temp;
		if (temp->data > data) {
			temp = temp->left;
		}
		else {
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

template<typename T>
void binaryTree<T>::inOrder(nodePtr root, std::vector<T>& arr)
{
	Node*& temp = (Node*&)root;
	if (!temp) return;
	inOrder((nodePtr&)temp->left, arr);
	arr.push_back(temp->data);
	inOrder((nodePtr&)temp->right, arr);
}

template<class T>
inline T binaryTree<T>::findMin() const
{
	Node* min = root;
	while (min->left) {
		min = min->left;
	}
	return min->data;
}

template<class T>
inline T binaryTree<T>::findMax() const
{
	Node* max = root;
	while (max->right) {
		max = max->right;
	}
	return max->data;
}

template<typename T>
size_t binaryTree<T>::subtreeSize(Node*& subRoot) {
	if (!subRoot) return 0;
	return subtreeSize(subRoot->left) + 1 + subtreeSize(subRoot->right);
}

template<class T>
template<typename Func>
inline void binaryTree<T>::doForNode(Node*& currNode, Func func)
{
	if (!currNode) return;
	doForNode(currNode->left,func);
	doForNode(currNode->right,func);
	func(currNode->data);
}

template<typename T>
size_t binaryTree<T>::size()  {
	return subtreeSize(root);
}

template<class T>
template<typename Func>
inline binaryTree<T>& binaryTree<T>::doForAll(Func func)
{
	// (function) or also for lambda ([](){})
	doForNode(root,func);
	return *this;
}

#include <iostream>
#include <random>
#include <ctime>
#include <conio.h>

//std::map<int,int> m;


#include "binaryTree.h"

using namespace std;

int decr(int& y) {
	return y--;
}

int main() {
	//int* r = nullptr;
	//delete r;

	srand(time(NULL));
		
	binaryTree<int> tree = {0,5,-1,-3, 1,2,3,4 };
	tree.doForAll(decr); 
	tree.show();
	return 0;
	binaryTree<int> tree2(move(tree));
	tree2.insert(2);
		
	//tree = tree2;
	tree.remove(2);

	//tree.getRoot() = 0;
	/*tree.show();
	tree.insert(5);
	tree = tree2;*/

	tree.show();
	//tree.clear();
	cout << tree.empty() << "\n";

	return 0;
	//cout << reinterpret_cast<int*>(tree.getRoot())[0] << "\n"; // illegal access

	for (int i = 0; i < 20; i++) {
		int a = rand() % 61 - 25;
		tree.insert(a);

	}

	tree.show();
	vector<int> ordArr;
	ordArr.reserve(25);
	//tree.inOrder(tree.getRoot(), ordArr);
	cout << "Order arr : ";
	for (int el : ordArr) {
		cout << el<<" ";
	}
	cout << "\n";
	return 0;

	int f;
	while (true) {
		tree.show();
		cout << "--------------------------\n";
		cout << "Find : ";
		cin >> f;
		cout << ((tree.search(f)) ? "find" : "not find") << "\n";
		cout << "Press esc to leave , otherwaise any other key" << "\n";
		int ch = _getch();
		if (ch == 27) {
			return 0;
		}
		system("cls");
	}
		
		
	return 0;
	int n;
	while (tree.getRoot()) {
		tree.show();
		cout << "--------------------------\n";
		cout << "Input n : ";
		cin >> n;
		tree.remove(n);
		system("cls");
	}
	cout << ((tree.empty())?"empty":"not empty") << "\n";
	return 0;
}
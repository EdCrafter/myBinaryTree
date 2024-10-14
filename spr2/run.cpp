#include <iostream>
#include <random>
#include <ctime>
#include <conio.h>
#include<map>

//std::map<int,int> m;


#include "binaryTree.h"

using namespace std;

int main() {
	try {
		
		//int* r = nullptr;
		//delete r;

		srand(time(NULL));
		
		binaryTree<int> tree = {0,5,-1,-3, 1,2,3,4 };
		binaryTree<int> tree2;
		tree2.insert(2);
		tree = tree2;
		tree.remove(2);

		//tree.getRoot() = 0;
		/*tree.print(tree.getRoot());
		tree.insert(5);
		tree = tree2;*/

		tree2.print(tree2.getRoot());
		tree.clear();
		cout << tree.empty() << "\n";

		return 0;
		//cout << reinterpret_cast<int*>(tree.getRoot())[0] << "\n"; // illegal access

		for (int i = 0; i < 20; i++) {
			int a = rand() % 61 - 25;
			tree.insert(a);

		}

		tree.print(tree.getRoot());
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
			tree.print(tree.getRoot());
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
			tree.print(tree.getRoot());
			cout << "--------------------------\n";
			cout << "Input n : ";
			cin >> n;
			tree.remove(n);
			system("cls");
		}
		cout << ((tree.empty())?"empty":"not empty") << "\n";
		
		
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	catch (std::exception e) {
		cout << e.what() << endl;
	}
	return 0;
}
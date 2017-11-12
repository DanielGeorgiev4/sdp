#include <iostream>
#include "BinTree.h"
using namespace std;

bool test(const int& x)
{
	return x >= 100;
}

void test()
{
	BinTree<int> t;
	t.add(10, "");
	t.add(5, "L");
	t.add(20, "R");
	t.add(15, "RL");
	t.add(25, "RR");
	cout << t.get_element("RLR") << endl;
}
int main()
{
	test();
}
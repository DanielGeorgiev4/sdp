#include <iostream>
#include <cassert>
#include <vector>
#include "HashMap.h"

using namespace std;

unsigned func(const string& s, int size)
{
	int result = 0;
	for (int i = 0; i < s.size(); i++) result += s[i];
	return result % size;
}

void testHash()
{
	HashMap<string, int> map(255,func);
	map["Elizabeth"] = 10;
	map["Jonh"] = 20;
	map["Jhno"] = 44;
	map["onhJ"] = 322;
	for (HashMap<string, int>::Iterator it = map.begin(); it != map.end(); ++it)
	{
		cout << (*it).key << " -> " << (*it).value << endl;
	}
}

struct Tree
{
	int value;
	vector<Tree*> next;
	void print()
	{
		print(this);
	}
	void print(Tree* curr)
	{
		cout << curr->value << ' ';
		if (curr->next.size() == 0) return;
		cout << '(';
		for (int i = 0; i < next.size(); i++) print(curr->next[i]);
		cout << ')';
	}
};

int findPath(const vector<vector<char>>& g, char* w, int vertex)
{
	if (w[0] == '\0') return 1;
	int count = 0;
	for (int i = 0; i < g.size(); i++)
	{
		count += (g[vertex][i] == w[0] ? findPath(g, w + 1, i) : 0);
	}
	return count;
}

int pathAmount(const vector<vector<char>>& g, char* w)
{
	int count = 0;
	for (int i = 0; i < g.size(); i++) count += findPath(g, w, i);
	return count;
}

void createTree(const vector<vector<bool>>& g, unsigned level, unsigned root, Tree*& t)
{
	t->value = root;
	if (level == 0) return;
	for (int i = 0; i < g.size(); i++)
	{
		if (g[root][i])
		{
			t->next.push_back(new Tree);
			createTree(g, level - 1, i, t->next[t->next.size() - 1]);
		}
	}
}	
void testGraph()
{
	vector<vector<char>> g({ {'a','a','b'},
							 {'c','b','\0'},
							 {'\0','a','c'}});
	vector<vector<bool>> t({ { 1, 1, 1 },
							 { 1, 1, 1 },
							 { 1, 1, 1 } });
	Tree* p = new Tree;
	createTree(t, 2, 0 ,p);
	p->print();
}
int main()
{
	testGraph();
}
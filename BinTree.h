#pragma once
#include <vector>
#include <string>
template <class T>
struct Node
{
	Node *left, *right;
	T value;
	Node() : left(nullptr), right(nullptr) {}
	Node(T _value) : value(_value), left(nullptr), right(nullptr) {}
};
template <class T>
class BinTree
{
	Node<T> *root;
	void add(const T&, char*, Node<T>*&);
	void basic_print(Node<T>* subroot) const;
	void del(Node<T>*&);
	unsigned count_elements(Node<T>*) const;
	unsigned count_even(Node<T>*) const;
	unsigned search_count(bool(*)(const T&), Node<T>*) const;
	unsigned height(Node<T>*) const;
	unsigned count_leaves(Node<T>*) const;
	unsigned max_leaf(Node<T>*) const;
	T& get_element(char* path, Node<T>*&);
	std::vector<T> list_leaves(Node<T>*,std::vector<T>&) const;
	std::string find_trace(Node<T>*, const T&) const;
	void pretty_print(Node<T>*,unsigned) const;
	T& get_el_helper(Node<T>*, unsigned);
	void level(Node<T>*, std::vector<T>&, unsigned) const;
	bool isBOT(Node<T>*) const;
	unsigned change_to_count(Node<T>*&);
public:
	BinTree();
	BinTree(Node<T>*);
	~BinTree();
	void add(const T&, char*);
	void basic_print() const;
	unsigned count_elements() const;
	unsigned count_even() const;
	unsigned search_count(bool(*)(const T&)) const;
	unsigned height() const;
	unsigned count_leaves() const;
	unsigned max_leaf() const;
	T& get_element(char*);
	std::vector<T> list_leaves() const;
	std::string find_trace(const T&) const;
	void pretty_print() const;
	T& operator[] (unsigned);
	std::vector<T> level(unsigned) const;
	bool has_same_levels() const;
	bool isBOT() const;
	void change_to_count();
	void balance_string();
};

template <class T>
void BinTree<T>::balance_string()
{
	;
}
template <class T>
void BinTree<T>::change_to_count()
{
	change_to_count(root);
}
template <class T>
unsigned BinTree<T>::change_to_count(Node<T>*& curr)
{
	if (curr == nullptr) return 0;
	curr->value = 1 + change_to_count(curr->left) + change_to_count(curr->right);
	return curr->value;
}
template <class T>
bool BinTree<T>::isBOT() const
{
	return isBOT(root);
}
template <class T>
bool BinTree<T>::isBOT(Node<T>* curr) const
{
	if (curr == nullptr) return true;
	if (!(isBOT(curr->left) && isBOT(curr->right))) return false;
	if (curr->left != nullptr)
		if (curr->left->value >= curr->value) return false;
	if (curr->right != nullptr)
		if (curr->right->value < curr->value) return false;
	return true;
}
template <class T>
bool BinTree<T>::has_same_levels() const
{
	unsigned height = BinTree<T>::height();
	if (height < 2) return false;
	vector<T>* arr = new vector<T>[height];
	for (unsigned i = 0; i < height; i++) arr[i] = level(i);
	for (unsigned i = 0; i < height - 1; i++)
		for (unsigned k = i + 1; k < height; k++)
			if (arr[i] == arr[k])
			{
				delete[] arr;
				return true;
			}
	delete[] arr;
	return false;
}
template <class T>
std::vector<T> BinTree<T>::level(unsigned k) const
{
	vector<T> v;
	level(root, v, k);
	return v;
}
template <class T>
void BinTree<T>::level(Node<T>* curr, std::vector<T>& v, unsigned k) const
{
	if (curr == nullptr || k < 0) return;
	if (!k)
	{
		v.push_back(curr->value);
		return;
	}
	level(curr->left, v, k - 1);
	level(curr->right, v, k - 1);
}
template <class T>
T& BinTree<T>::operator[](unsigned i)
{
	return get_el_helper(root, i);
}
template <class T>
T& BinTree<T>::get_el_helper(Node<T>* curr,unsigned i)
{
	if (!i) return curr->value;
	unsigned left_count = count_elements(curr->left);
	if ( left_count > i - 1) return get_el_helper(curr->left, i - 1);
	return get_el_helper(curr->right, i - 1 - left_count);
}
template <class T>
void BinTree<T>::pretty_print() const
{
	pretty_print(root, 0);
}
template <class T>
void BinTree<T>::pretty_print(Node<T>* curr, unsigned n) const
{
	if (curr == nullptr) return;
	pretty_print(curr->right, n + 16);
	std::cout << std::string(n,' ') << curr->value << std::endl;
	pretty_print(curr->left, n + 16);
}
template <class T>
std::string BinTree<T>::find_trace(const T& x) const
{
	return find_trace(root, x);
}
template <class T>
std::string BinTree<T>::find_trace(Node<T>* curr, const T& x) const
{
	if (curr == nullptr) return "_";
	if (curr->value == x) return "\0";
	std::string left = find_trace(curr->left, x), right = find_trace(curr->right, x);
	if (left != "_") return 'L' + left;
	if (right != "_") return 'R' + right;
	return "_";
}
template <class T>
std::vector<T> BinTree<T>::list_leaves() const
{
	std::vector<T> v;
	return list_leaves(root, v);
}
template <class T>
std::vector<T> BinTree<T>::list_leaves(Node<T>* curr,std::vector<T>& v) const
{
	if (curr == nullptr) return v;
	if (curr->left == nullptr && curr->right == nullptr)
	{
		v.push_back(curr->value);
		return v;
	}
	list_leaves(curr->left, v);
	list_leaves(curr->right, v);
	return v;
}
template <class T>
T& BinTree<T>::get_element(char* path)
{
	return get_element(path, root);
}
template <class T>
T& BinTree<T>::get_element(char* path, Node<T>*& subroot)
{
	if (subroot == nullptr) return root->value;
	if (path[0] == '\0') return subroot->value;
	if (path[0] == 'L') return get_element(path + 1, subroot->left);
	return get_element(path + 1, subroot->right);
}
template <class T>
unsigned BinTree<T>::max_leaf() const
{
	return max_leaf(root);
}
template <class T>
unsigned BinTree<T>::max_leaf(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	if (subroot->left == nullptr && subroot->right == nullptr) return subroot->value;
	unsigned left = max_leaf(subroot->left), right = max_leaf(subroot->right);
	return (left > right ? left : right);
}
template <class T>
unsigned BinTree<T>::count_leaves() const
{
	return count_leaves(root);
}
template <class T>
unsigned BinTree<T>::count_leaves(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return count_leaves(subroot->left) + count_leaves(subroot->right) + (subroot->left == nullptr && subroot->right == nullptr ? 1 : 0);
}
template <class T>
unsigned BinTree<T>::height() const
{
	return height(root);
}
template <class T>
unsigned BinTree<T>::height(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	unsigned left = height(subroot->left), right = height(subroot->right);
	return 1 + (left > right ? left : right);
}
template <class T>
unsigned BinTree<T>::search_count(bool(*pred)(const T&)) const
{
	return search_count(pred, root);
}
template <class T>
unsigned BinTree<T>::search_count(bool(*pred)(const T&), Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return search_count(pred, subroot->left) + search_count(pred, subroot->right) + (pred(subroot->value) ? 1 : 0);
}
template <class T>
unsigned BinTree<T>::count_even() const
{
	return count_even(root);
}
template <class T>
unsigned BinTree<T>::count_even(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return count_even(subroot->left) + count_even(subroot->right) + (subroot->value % 2 ? 0 : 1);
}
template <class T>
unsigned BinTree<T>::count_elements() const
{
	return count_elements(root);
}
template <class T>
unsigned BinTree<T>::count_elements(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return 1 + count_elements(subroot->left) + count_elements(subroot->right);
}
template <class T>
BinTree<T>::BinTree()
{
	root = nullptr;
}
template <class T>
BinTree<T>::BinTree(Node<T>* _root)
{
	root = _root;
}
template <class T>
BinTree<T>::~BinTree()
{
	del(root);
}
template <class T>
void BinTree<T>::del(Node<T>*& subroot)
{
	if (subroot == nullptr) return;
	del(subroot->left);
	del(subroot->right);
	delete subroot;
}
template <class T>
void BinTree<T>::add(const T& _value, char* path)
{
	add(_value, path, root);
}
template <class T>
void BinTree<T>::add(const T& _value, char* path,Node<T>*& subroot)
{
	if (subroot == nullptr)
	{
		subroot = new Node<T>(_value);
		return;
	}
	if (path[0] == 'L')
	{
		add(_value, path + 1, subroot->left);
		return;
	}
	add(_value, path + 1, subroot->right);
	return;
}
template <class T>
void BinTree<T>::basic_print() const
{
	basic_print(root);
}
template <class T>
void BinTree<T>::basic_print(Node<T>* subroot) const 
{
	if (subroot == nullptr) return;
	cout << subroot->value << ' ';
	basic_print(subroot->left);
	basic_print(subroot->right);
}
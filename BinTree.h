#pragma once
template <typename T>
struct Node
{
	Node *left, *right;
	T value;
	Node() : left(nullptr), right(nullptr) {}
	Node(T _value) : value(_value), left(nullptr), right(nullptr) {}
};
template <typename T>
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
};
template <typename T>
T& BinTree<T>::get_element(char* path)
{
	return get_element(path, root);
}
template <typename T>
T& BinTree<T>::get_element(char* path, Node<T>*& subroot)
{
	if (subroot == nullptr) return root->value;
	if (path[0] == '\0') return subroot->value;
	if (path[0] == 'L') return get_element(path + 1, subroot->left);
	return get_element(path + 1, subroot->right);
}
template <typename T>
unsigned BinTree<T>::max_leaf() const
{
	return max_leaf(root);
}
template <typename T>
unsigned BinTree<T>::max_leaf(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	if (subroot->left == nullptr && subroot->right == nullptr) return subroot->value;
	unsigned left = max_leaf(subroot->left), right = max_leaf(subroot->right);
	return (left > right ? left : right);
}
template <typename T>
unsigned BinTree<T>::count_leaves() const
{
	return count_leaves(root);
}
template <typename T>
unsigned BinTree<T>::count_leaves(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return count_leaves(subroot->left) + count_leaves(subroot->right) + (subroot->left == nullptr && subroot->right == nullptr ? 1 : 0);
}
template <typename T>
unsigned BinTree<T>::height() const
{
	return height(root);
}
template <typename T>
unsigned BinTree<T>::height(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	unsigned left = height(subroot->left), right = height(subroot->right);
	return 1 + (left > right ? left : right);
}
template <typename T>
unsigned BinTree<T>::search_count(bool(*pred)(const T&)) const
{
	return search_count(pred, root);
}
template <typename T>
unsigned BinTree<T>::search_count(bool(*pred)(const T&), Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return search_count(pred, subroot->left) + search_count(pred, subroot->right) + (pred(subroot->value) ? 1 : 0);
}
template <typename T>
unsigned BinTree<T>::count_even() const
{
	return count_even(root);
}
template <typename T>
unsigned BinTree<T>::count_even(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return count_even(subroot->left) + count_even(subroot->right) + (subroot->value % 2 ? 0 : 1);
}
template <typename T>
unsigned BinTree<T>::count_elements() const
{
	return count_elements(root);
}
template <typename T>
unsigned BinTree<T>::count_elements(Node<T>* subroot) const
{
	if (subroot == nullptr) return 0;
	return 1 + count_elements(subroot->left) + count_elements(subroot->right);
}
template <typename T>
BinTree<T>::BinTree()
{
	root = nullptr;
}
template <typename T>
BinTree<T>::BinTree(Node<T>* _root)
{
	root = _root;
}
template <typename T>
BinTree<T>::~BinTree()
{
	del(root);
}
template <typename T>
void BinTree<T>::del(Node<T>*& subroot)
{
	if (subroot == nullptr) return;
	del(subroot->left);
	del(subroot->right);
	delete subroot;
}
template <typename T>
void BinTree<T>::add(const T& _value, char* path)
{
	add(_value, path, root);
}
template <typename T>
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
template <typename T>
void BinTree<T>::basic_print() const
{
	basic_print(root);
}
template <typename T>
void BinTree<T>::basic_print(Node<T>* subroot) const 
{
	if (subroot == nullptr) return;
	cout << subroot->value << ' ';
	basic_print(subroot->left);
	basic_print(subroot->right);
}
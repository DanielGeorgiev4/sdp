#pragma once
#include <vector>
#include <string>

template <typename KeyT>
using hashf = unsigned (*)(const KeyT&, int);

template <typename KeyT, typename ValueT>
class HashMap
{
	struct Pair
	{
		KeyT key;
		ValueT value;
		Pair(KeyT _key, ValueT _value) : key(_key), value(_value) {}
	};
	unsigned size;
	std::vector<std::vector<Pair>> table;
	hashf<KeyT> f;
	int locate(const KeyT&, unsigned) const;
public:
	HashMap(unsigned,hashf<KeyT>);
	void add(const KeyT&, const ValueT&);
	ValueT& operator [](const KeyT&);
	bool hasKey(const KeyT&);
	void resize(int);
	class Iterator
	{
		unsigned idx, place;
		const std::vector<std::vector<Pair>>* _table;
	public:
		Iterator(const std::vector<std::vector<Pair>>& table, unsigned _idx)
		{
			idx = _idx;
			place = 0;
			_table = &table;
		}
		bool operator != (const Iterator& other)
		{
			return idx != other.idx || place != other.place;
		}
		Pair operator *()
		{
			return (*_table)[idx][place];
		}
		void operator ++ ()
		{
			if (place + 1 == (*_table)[idx].size())
			{
				place = 0;
				idx++;
				while ((*_table)[idx].empty() && idx < _table->size()) { idx++; }
				if (idx == _table->size()) cout << _table->size() << endl;
				return;
			}
			place++;
		}
	};
	Iterator begin()
	{
		unsigned i = 0;
		while (table[i].empty() && i < table.size()) { i++; } //?
		return Iterator(table,i);
	}
	Iterator end()
	{
		return Iterator(table,table.size());
	}
};
template <typename KeyT, typename ValueT>
void HashMap<KeyT, ValueT>::resize(int new_size)
{
	vector<vector<Pair>> new_table(new_size, {});
	for (int i = 0; i < table.size(); ++i)
	{
		for (int k = 0; k < table[i].size(); k++)
		{
			int idx = f(table[i][k].key,new_size);
			new_table[idx].push_back(Pair(table[i][k].key, table[i][k].value));
		}
	}
	size = new_size;
	table = new_table;
}
template <typename KeyT, typename ValueT>
bool HashMap<KeyT, ValueT>::hasKey(const KeyT& key)
{
	int idx = f(key, size);
	return locate(key, idx) != -1;
}
template <typename KeyT, typename ValueT>
ValueT& HashMap<KeyT, ValueT>::operator[](const KeyT& key)
{
	unsigned index = f(key, size);
	int place = locate(key, index);
	if (place == -1)
	{
		table[index].push_back(Pair(key, ValueT()));
		place = table[index].size() - 1;
	}
	return table[index][place].value;
}
template <typename KeyT, typename ValueT>
int HashMap<KeyT, ValueT>::locate(const KeyT& key, unsigned idx) const
{
	for (int i = 0; i < table[idx].size();i++)
	{
		if (table[idx][i].key == key) return i;
	}
	return -1;
}
template <typename KeyT, typename ValueT>
void HashMap<KeyT, ValueT>::add(const KeyT& key, const ValueT& value)
{
	unsigned index = f(key,size);
	table[index].push_back(Pair(key, value));
}
template <typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(unsigned _size, hashf<KeyT> _f)
{
	size = _size;
	f = _f;
	table = vector<vector<Pair>>(size, {});
}
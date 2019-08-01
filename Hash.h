#pragma once
#include <vector>

template<class K>
struct HashFunc
{
	const K& operator()(const K& key)
	{
		return key;
	}
};

template<>
struct HashFunc<string>
{
	size_t BKDRHash(const char* str)
	{
		size_t hash = 0;
		while (*str)
		{
			hash = hash * 131 + *str;
			++str;
		}

		return hash;
	}
	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};

namespace closehash
{
	enum State
	{
		EXITS,
		EMPTY,
		DELETE,
	};

	template<class T>
	struct HashStruct
	{
		T _v;			// 
		State _state;
	};

	template<class K, class T>
	class HashTable
	{
		typedef HashStruct<T> HashStruct;
	public:
		bool Insert(const T& v)
		{
			// 1.��0
			// 2.����ӳ���ϵ����
			if (_table.size() == 0 ||
				10 * _num / _table.size() >= 7)
			{
				size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
				/*	vector<HashStruct> newtable;
					newtable.resize(newsize);
					for (size_t i = 0; i < _table; i++)
					{
					if (_table[i]._state == EXITS)
					{

					}

					}*/
				HashTable<K, T> newht;
				newht._table.resize(newsize);
				for (size_t i = 0; i < newht._table.size(); ++i)
				{
					newht._table[i]._state = EMPTY;
				}

				for (size_t i = 0; i < _table.size(); ++i)
				{
					if (_table[i]._state == EXITS)
					{
						newht.Insert(_table[i]._v);
					}
				}

				_table.swap(newht._table);
			}

			//size_t index = v % _table.size();
			//// ����̽��
			//while (_table[index]._state == EXITS)
			//{
			//	if (_table[index]._v == v)
			//	{
			//		return false;
			//	}

			//	++index;
			//	if (index == _table.size())
			//		index = 0;
			//}

			// ����̽��
			size_t start = v % _table.size();
			size_t index = start;
			size_t i = 1;
			while (_table[index]._state == EXITS)
			{
				if (_table[index]._v == v)
				{
					return false;
				}

				index = start + i*i;
				index %= _table.size();
				++i;
			}

			_table[index]._v = v;
			_table[index]._state = EXITS;
			_num++;

			return true;
		}

		HashStruct* Find(const K& k)
		{
			if (_table.size() == 0)
				return nullptr;

			size_t index = k % _table.size();
			while (_table[index]._state != EMPTY)
			{
				if (_table[index]._v == k && _table[index]._state == EXITS)
				{
					return &_table[index];
				}

				++index;
				if (index == _table.size())
				{
					index = 0;
				}
			}

			return nullptr;
		}

		bool Erase(const K& k)
		{
			HashStruct* ret = Find(k);
			if (ret == nullptr)
			{
				return false;
			}
			else
			{
				ret->_state = DELETE;
				--_num;
				return true;
			}
		}

	private:
		//HashStruct* _table;
		//size_t _size;
		//size_t _capacity;
		vector<HashStruct> _table;
		size_t _num = 0;	// ӳ��洢�����ݸ���
	};

	void TestHashTable()
	{
		//HashTable<int, int> s;
		//s.Insert(5);
		//s.Insert(3);
		//s.Insert(2);
		//s.Insert(12);
		//s.Insert(22);
		//s.Insert(9);
		//s.Insert(8);
		//s.Insert(7);

		HashTable<int, int> s;
		s.Insert(2);
		s.Insert(12);
		s.Insert(22);
		s.Insert(32);
	}
}

namespace hashbucket
{
	template<class T>
	struct HashNode
	{
		HashNode<T>* _next;
		T _v;
		
		HashNode(const T& t)
			:_v(t)
			, _next(nullptr)
		{}
	};

	template<class K, class T, class KeyOfValue, class HF>
	class HashTable;

	template<class K, class T, class KeyOfValue, class HF>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, T, KeyOfValue, HF> Self;
		Node* _node;
		HashTable<K, T, KeyOfValue, HF>* _pht;

		__HTIterator(Node* node, HashTable<K, T, KeyOfValue, HF>* pht)
			:_node(node)
			, _pht(pht)
		{}

		T& operator*()
		{
			return _node->_v;
		}

		T* operator->()
		{
			return &(operator*());
		}

		// ++it
		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfValue kov;
				size_t index = _pht->HashFunc(kov(_node->_v), _pht->_table.size());
				++index;
				while (index < _pht->_table.size())
				{
					if (_pht->_table[index])
					{
						_node = _pht->_table[index];
						break;
					}
					else
					{
						++index;
					}
				}

				// ����Ͱ�����ˣ���Ϊnullptr��ʾend()��λ��
				if (index == _pht->_table.size())
				{
					_node = nullptr;
				}
			}

			return *this;
		}

		bool operator!= (const Self& s)
		{
			return _node != s._node;
		}
	};

	template<class K, class T, class KeyOfValue, class HF>
	class HashTable
	{
		typedef HashNode<T> Node;

		//friend struct __HTIterator<K, T, KeyOfValue>;
		template<class K, class T, class KeyOfValue, class HF>
		friend struct __HTIterator;
	public:
		typedef __HTIterator<K, T, KeyOfValue, HF> iterator;
		iterator begin()
		{
			if (_num == 0)
			{
				return end();
			}

			for (size_t i = 0; i < _table.size(); ++i)
			{
				if (_table[i] != nullptr)
				{
					return iterator(_table[i], this);
				}
			}

			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		pair<iterator, bool> Insert(const T& v)
		{
			KeyOfValue kov;
			// ���� load factor == 1
			if (_table.size() == _num)
			{
				size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
				vector<Node*> newtable;
				newtable.resize(newsize);

				// Ų���ɱ����ݵ��±�����µ�λ��
				for (size_t i = 0; i < _table.size(); ++i)
				{
					Node* cur = _table[i];
					while (cur)
					{
						Node* next = cur->_next;

						size_t index = HashFunc(kov(cur->_v), newtable.size());
						cur->_next = newtable[index];
						newtable[index] = cur;

						cur = next;
					}

					_table[i] = nullptr;
				}

				newtable.swap(_table);
			}

			size_t index = HashFunc(kov(v), _table.size());
			Node* cur = _table[index];
			while (cur)
			{
				if (kov(cur->_v) == kov(v))
				{
					return make_pair(iterator(cur, this), false);
				}

				cur = cur->_next;
			}

			// ͷ��
			Node* newnode = new Node(v);
			newnode->_next = _table[index];
			_table[index] = newnode;
			++_num;

			return make_pair(iterator(newnode, this), true);
		}

		iterator Find(const K& k)
		{
			KeyOfValue kov;
			size_t index = HashFunc(k, _table.size());
			Node* cur = _table[index];
			while (cur)
			{
				if (kov(cur->_v) == k)
				{
					return iterator(cur, this);
				}

				cur = cur->_next;
			}

			return end();
		}

		bool Erase(const K& k)
		{
			KeyOfValue kov;
			size_t index = HashFunc(k, _table.size());
			Node* prev = nullptr;
			Node* cur = _table[index];

			while (cur)
			{
				if (kov(cur->_v) == k)
				{
					if (prev == nullptr)
					{
						_table[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}
		}

		size_t HashFunc(const K& k, size_t n)
		{
			HF hf;
			return hf(k) % n;
		}

	private:
		vector<Node*> _table;
		size_t _num = 0;
	};
}

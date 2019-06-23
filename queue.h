#pragma once

template<class T, class Container = deque<int>>
class Queue
{
public:
	void Push(const T& x)
	{
		_con.push_back(x);
	}

	void Pop()
	{
		_con.pop_front();
	}

	size_t Size()
	{
		_con.size();
	}

	bool Empty()
	{
		return _con.empty();
	}

	const T& Front()
	{
		return _con.front();
	}

	const T& Back()
	{
		return _con.back();
	}
private:
	Container _con;
};

void TestQueue()
{
	//Queue<int, vector<int>> q; vector��֧��
	Queue<int, list<int>> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);

	while (!q.Empty())
	{
		cout << q.Front() << endl;
		q.Pop();
	}
}
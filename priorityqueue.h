#pragma once

#include<queue>

// N找最大的10个  小堆
// N找最小的10个  大堆
void test_priority_queue()
{
	std::priority_queue<int, vector<int>, std::greater<int>> pq1;
	pq1.push(4);
	pq1.push(3);
	pq1.push(1);
	pq1.push(9);
	pq1.push(7);

	while (!pq1.empty())
	{
		cout << pq1.top() << endl;
		pq1.pop();
	}
}

template<class T>
struct Less
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};


template<class T, class Container = vector<T>, class Compare = Less<T>>
class PriorityQueue
{
public:
	void AdjustUp(size_t child)
	{
		size_t parent = (child - 1) / 2;
		Compare com;
		while (child > 0)
		{
			//if (_con[child] > _con[parent])
			if (com(_con[parent], _con[child]))
			{
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustDwon(size_t parent)
	{
		size_t child = parent * 2 + 1;
		Compare com;
		while (child < _con.size())
		{
			//if (child + 1 < _con.size() 
			//	&& _con[child + 1] > _con[child])
			if (child + 1 < _con.size()
				&& com(_con[child], _con[child + 1]))
			{
				++child;
			}

			//if (_con[child] > _con[parent])
			if (com(_con[parent], _con[child]))
			{
				swap(_con[child], _con[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	void Push(const T& x)
	{
		_con.push_back(x);

		AdjustUp(_con.size() - 1);
	}

	void Pop()
	{
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();

		AdjustDwon(0);
	}

	const T& Top()
	{
		return _con[0];
	}

	size_t Size()
	{
		return _con.size();
	}

	bool Empty()
	{
		return _con.empty();
	}
private:
	Container _con;
};

// 仿函数 函数对象
//void TestPriorityQueue()
//{
//	//Less<int> less;
//	//Greater<int> greater;
//
//	//cout << less(1, 3) << endl;
//	//cout << less.operator()(1, 3) << endl;
//	//cout << Less<int>()(1, 3) << endl;
//	//cout << greater(1, 3) << endl;
//
//	//PriorityQueue<int,vector<int>, Greater<int>> pq;
//	PriorityQueue<int, vector<int>, Less<int>> pq;
//	pq.Push(1);
//	pq.Push(6);
//	pq.Push(1);
//	pq.Push(8);
//	pq.Push(0);
//
//	while (!pq.Empty())
//	{
//		cout << pq.Top() << endl;
//		pq.Pop();
//	}
//	cout << endl;
//}

//void TestPriorityQueue()
//{
//	//Less<int> less;
//	//Greater<int> greater;
//
//	//cout << less(1, 3) << endl;
//	//cout << less.operator()(1, 3) << endl;
//	//cout << Less<int>()(1, 3) << endl;
//	//cout << greater(1, 3) << endl;
//
//	//PriorityQueue<int,vector<int>, Greater<int>> pq;
//	PriorityQueue<int, vector<int>, Less<int>> pq;
//	pq.Push(1);
//	pq.Push(6);
//	pq.Push(1);
//	pq.Push(8);
//	pq.Push(0);
//
//	while (!pq.Empty())
//	{
//		cout << pq.Top() << endl;
//		pq.Pop();
//	}
//	cout << endl;
//}

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}

	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}

	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}

private:
	int _year;
	int _month;
	int _day;
};

// 商品
struct Goods
{
	int price;
	int evaluate;
};

struct GoodsPriceLess
{
	bool operator()(const Goods& l, const Goods& r)
	{
		return l.price < r.price;
	}
};

struct GoodsEvaluateLess
{
	bool operator()(const Goods& l, const Goods& r)
	{
		return l.evaluate < r.evaluate;
	}
};

void TestPriorityQueue()
{
	//// 大堆，需要用户在自定义类型中提供<的重载
	//priority_queue<Date> q1;
	//q1.push(Date(2018, 10, 29));
	//q1.push(Date(2018, 10, 28));
	//q1.push(Date(2018, 10, 30));
	//cout << q1.top() << endl;

	//// 如果要创建小堆，需要用户提供>的重载
	//priority_queue<Date, vector<Date>, greater<Date>> q2;
	//q2.push(Date(2018, 10, 29));
	//q2.push(Date(2018, 10, 28));
	//q2.push(Date(2018, 10, 30));
	//cout << q2.top() << endl;

	priority_queue<Goods> q3;
	q3.push(Goods{ 10, 8 });
	q3.push(Goods{ 8, 12 });
	Goods top = q3.top();
}
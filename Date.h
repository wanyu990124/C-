#pragma once 

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

class Date
{
public:
	inline int GetMonthDay(int year, int month) const
	{
		static int monthArry[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if ((month == 2)
			&& (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			return 29;
		}
		return monthArry[month];
	}

	//构造函数
	Date(int year, int month, int day)
	{
		if (year >= 1900
			&& month > 0 && month < 13
			&& day > 0 && day <= GetMonthDay(year, day))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期" << endl;
		}
	}

	//析构函数
	~Date()
	{}

	//拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//赋值运算符重载
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << "-" << endl;
	}

	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;

	Date& operator++();	// 前置++
	Date operator++(int);	// 后置++

	Date operator--();	// 前置--
	Date operator--(int);	// 后置--

	Date operator+(int day) const;
	Date operator-(int day) const;

	Date& operator+=(int day);
	Date& operator-=(int day);

	int operator-(const Date&d);

private:
	int _year;
	int _month;
	int _day;
};


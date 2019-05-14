#include "Date.h"

bool Date::operator>(const Date& d) const
{
	if ((_year > d._year)
		|| ((_year == d._year) && (_month > d._month))
		|| ((_year == d._year) && (_month == d._month) && (_day > d._day)))
	{
		return true;
	}
	return false;
}

bool Date::operator>=(const Date& d) const
{
	if (*this > d)
	{
		return true;
	}
	return false;
}
bool Date::operator<(const Date& d) const
{
	if ((_year < d._year)
		|| ((_year == d._year) && (_month < d._month))
		|| ((_year == d._year) && (_month == d._month) && (_day < d._day)))
	{
		return true;
	}
	return false;
}
bool Date::operator<=(const Date& d) const
{
	if (*this < d)
	{
		return true;
	}
	return false;
}
bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}
bool Date::operator!=(const Date& d) const
{
	return _year != d._year
		&& _month != d._month
		&& _day != d._day;
}

// ++d
Date& Date::operator++()	// 前置++
{
	*this += 1;
	return *this;
}

// d++
Date Date::operator++(int) // 后置++
{
	Date ret(*this);
	*this += 1;
	return ret;
}

Date Date::operator--()	// 前置--
{
	*this -= 1;
	return *this;
}
Date Date::operator--(int)	// 后置--
{
	Date ret(*this);
	*this -= 1;
	return ret;
}

Date Date::operator+(int day) const
{
	Date ret(*this);
	ret += day;
	return ret;
}

Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -(-day);
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13)
		{
			++_year;
			_month = 1;
		}
	}
	return *this;
}

Date Date::operator-(int day) const
{
	Date ret(*this);
	ret -= day;
	return ret;
}
Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this +(-day);
	}

	_day -= day;
	while (_day <= 0)
	{
		_day += GetMonthDay(_year, _month);
		_month--;
		if (_month == 0)
		{
			_year--;
			_month = 12;
		}
	}
	return *this;
}

int Date::operator-(const Date&d)
{
	Date max = *this, min = d;
	if (*this < d)
	{
		max = d;
		min = *this;
	}
	int days = 0;
	while (min < max)
	{
		++days;
	}
	return days;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
#include<string.h>
using namespace std;
class Time
{
public:
	Time()
	{
		std::cout << " Time() " << endl;
		_hour = 0;
		_minute = 0;
		_second = 9;
	}
private:
	int _hour = 0;
	int _minute = 0;
	int _second = 0;
};

/*class Date {
private:    
	// 基本类型(内置类型)    
	int _year;    
	int _month;    
	int _day;

	// 自定义类型    
	Time _t; 
};*/

typedef int DataType; 
class SeqList
{
public:    
	SeqList(int capacity = 10)
	{
		_pData = (DataType*)malloc(capacity * sizeof(DataType));
		assert(_pData);
		_size = 0;
		_capacity = capacity;
	}
	~SeqList()   
	{
		if (_pData)     
		{
			free(_pData);  
			// 释放堆上的空间     
			_pData = NULL;  
			// 将指针置为空       
			_capacity = 0;       
			_size = 0;    
		}   
	}  
private :    
	int* _pData ;  
	size_t _size;  
	size_t _capacity; 
};

class String 
{
public:   
	String(const char* str = "jack")   
	{ 
		_str = (char*)malloc(strlen(str) + 1);    
		strcpy(_str, str); 
	}
	~String()  
	{ 
		cout << "~String()" << endl;   
		free(_str);
	} 
private:  
	char* _str;
};

class Person
{ 
private:   
	String _name;  
	int    _age; 
};

class Date
{
public:    
	Date(int year = 1900, int month = 1, int day = 1)  
	{ 
		_year = year;    
		_month = month;      
		_day = day; 
	}
	Date(const Date& d)   
	{
		_year = d._year;    
		_month = d._month; 
		_day = d._day;
	} 
private:   
	int _year; 
	int _month;  
	int _day;
};

int main()
{
	//Time t;
	//Date d;
	//Person p;
	Date d1;
	Date d2(d1);

	String s1("hello");   
	String s2(s1);

	system("pause");
	return 0;
}
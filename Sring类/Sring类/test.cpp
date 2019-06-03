#include<iostream>
#include<string>
#include<assert.h>
//��ͳд����string��
class String {
public:    
	String(const char* str = "") {                
		// ����string�����ʱ���������nullptrָ�룬��Ϊ����Ƿ����˴�������        
		if(nullptr == str) {            
			assert(false);            
			return;        
		}                
		_str = new char[strlen(str) + 1];        
		strcpy(_str, str);    
	}        
	String(const String& s)        
		: _str(new char[strlen(s._str)+1]) {            
		strcpy(_str, s._str);    
	}        
	String& operator=(const String& s) {        
		if(this != &s) {            
			char* pStr = new char[strlen(s._str) + 1];            
			strcpy(pStr, s._str);            
			delete[] _str;            
			_str = pStr; 
		}                return *this;
	}        
	~String() { 
		if (_str) { 
			delete[] _str;           
			_str = nullptr; 
		} 
	}    
private:    
	char* _str;
};

//��ͳд����string��
class String {
public:    
	String(const char* str = "") { 
		if (nullptr == str)            
			str = "";                
		= new char[strlen(str) + 1];        
		strcpy(_str, str); 
	}        
	String(const String& s) 
		: _str(nullptr) { 
		String strTmp(s._str);        
		swap(_str, strTmp); 
	}           
	String& operator=(String s) {        
		swap(_str, s._str);           
		return *this;    
	}        
	/*    String& operator=(const String& s) {        
	if(this != &s) {
	String strTmp(s);           
	swap(_str, strTmp._str);        
	}                
	return *this;    
	}*/        
	~String() { 
		if (_str) { 
			delete[] _str;            
			_str = nullptr; 
		} 
	}    
private:    
	char* _str;
};

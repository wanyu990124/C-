#include<iostream>
#include<string>
using namespace std;
void TestPushBack() {
	string s; 
	size_t sz = s.capacity();    
	cout << "making s grow:\n";    
	for (int i = 0; i < 100; ++i) {
		s.push_back('c');
		if (sz != s.capacity()) {
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

void TestPushBackReserve() { 
	string s;     
	s.reserve(100);    
	size_t sz = s.capacity();       
	cout << "making s grow:\n";    
	for (int i = 0; i < 100; ++i) { 
		s.push_back('c');        
		if (sz != s.capacity()) { 
			sz = s.capacity();            
			cout << "capacity changed: " << sz << '\n'; 
		} 
	} 
}



//翻转字符串
class Solution { 
public:    
	string reverseString(string s) { 
		if (s.empty())            
			return s;                
		size_t start = 0;        
		size_t end = s.size() - 1;                
		while (start < end) { 
			swap(s[start], s[end]);            
			++start;            
			--end; 
		}                
		return s; 
	} 
};

//找字符串中第一次出现一次的字符
#include<iostream> 
#include<string> 
using namespace std;
int main() {
	string line;
	// 不要使用cin>>line,因为会它遇到空格就结束了    
	// while(cin>>line)    
	while (getline(cin, line)) {
		size_t pos = line.rfind(' ');
		cout << line.size() - pos - 1 << endl;
	}
	return 0;
}

//验证一个字符串是否是回文
class Solution {
public:    
	bool isLetterOrNumber(char ch)    {
	return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z');
	}        
	bool isPalindrome(string s) {			
		// 先小写字母转换成大写，再进行判断        
		for(auto& ch : s)  {            
			if(ch >= 'a' && ch <= 'z')                
				ch -= 32;        
		}                
		int begin = 0, end = s.size()-1;        
		while(begin < end)  {            
			while(begin < end && !isLetterOrNumber(s[begin]))                
				++begin;                        
			while(begin < end && !isLetterOrNumber(s[end]))                
				--end;                        
			if(s[begin] != s[end]) {                
				return false;            
			}            
			else {                                
				++begin;                
				--end;            
			}        
		}                
		return true;    
	} 
};

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



//��ת�ַ���
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

//���ַ����е�һ�γ���һ�ε��ַ�
#include<iostream> 
#include<string> 
using namespace std;
int main() {
	string line;
	// ��Ҫʹ��cin>>line,��Ϊ���������ո�ͽ�����    
	// while(cin>>line)    
	while (getline(cin, line)) {
		size_t pos = line.rfind(' ');
		cout << line.size() - pos - 1 << endl;
	}
	return 0;
}

//��֤һ���ַ����Ƿ��ǻ���
class Solution {
public:    
	bool isLetterOrNumber(char ch)    {
	return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z');
	}        
	bool isPalindrome(string s) {			
		// ��Сд��ĸת���ɴ�д���ٽ����ж�        
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

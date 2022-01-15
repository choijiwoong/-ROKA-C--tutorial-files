#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

namespace self_string{
	class String;
	
	//support functions
	std::ostream& operator<<(std::ostream&, const String&);
	std::istream& operator>>(std::istream&, String&);
	bool operator==(const String&, const String&);
	bool operator!=(const String&, const String&);
	char* begin(String&);
	char* end(String&);
	const char* begin(const String&);
	const char* end(const String&);
	String& operator+=(String&, const String&);
	String operator+(const String, const String&);
	String operator"" _s(const char*, size_t);
	int hash(const String&);
	void print_in_order(const String&, const std::vector<int>&);
	char* expand(const char*, int);
	
	class String{
		/*
			Simple string that concrete simple SSO(limit: short_max variable)
			size()==sz is count of element
			ptr points start of string sequence. it's end is expressed by 0 ptr[size()]==0; for considering C style
			allocation is precessing multiple 2 for effeciency
			capacity()=sz+space(not include 0 for end)
		*/
		public:
			String();//common constructor
			String(const char* p);//constructor of C style string
			String(const String&);//copy constructor
			String& operator=(const String&);//copy assign
			String(String&& x);//move constructor _For meaning of value.
			String& operator=(String&& x);//move assign
			~String(){ if(short_max<sz) delete[] ptr; }//destructor
			
			char& operator[](int n) { return ptr[n]; }
			char operator[](int n) const{ return ptr[n]; }//const version
			char& at(int n){ check(n); return ptr[n]; }
			char at(int n) const{ check(n); return ptr[n]; }//const version
			String& operator+=(char c);
			char* c_str(){ return ptr; }
			const char* c_str() const{ return ptr; }//const version
			int size() const{ return sz; }
			int capacity() const{ return (sz<=short_max)? short_max:sz+space; }
			
		private:
			static const int short_max=15;
			int sz;
			char* ptr;
			union{//annonymous union(discriminated union_sz<=short_max)
				int space;//non-use
				char ch[short_max+1];//for enough space for 0(end)
			};
			
			void check(int n) const{//range check
				if(n<0 || sz<=n)
					return;
				throw std::out_of_range("String::at()"); 
			}
			void copy_from(const String& x);
			void move_from(String& x);
	};
	//inner structure
	String::String(): sz{0}, ptr{ch}{ ch[0]=0; }
	String::String(const char* p): sz{strlen(p)}, ptr{(sz<=short_max)? ch:new char[sz+1]}, space{0}{ strcpy(ptr, p); }//if oversize, new allocation and set ptr to point start of new space
	String::String(const String& x){ copy_from(x); }
	String::String(String&& x){ move_from(x); }
	
	String& String::operator=(const String& x){
		if(this==&x)//self-assign
			return *this;
		char* p=(short_max<sz)? ptr:0;//for delete ptr if SSO is using.
		copy_from(x);//get content of x
		delete[] p;//and delete initial heap memory
		return *this;
	}
	String& String::operator=(String&& x){
		if(this==&x)
			return *this;//do not x=move(x)_ptr
		if(short_max<sz)
			delete[] ptr;//delete ptr if SSO is using direct because it's move
		move_from(x);
		return *this;
	}
	String& String::operator+=(char c){
		if(sz==short_max){
			int n=sz+sz+2;//for effeciency of space
			ptr=expand(ptr, n);
			space=n-sz-2;
		} else if(short_max<sz){
			if(space==0){//if new allocation is needed
				int n=sz+sz+2;
				char* p=expand(ptr, n);
				delete[] ptr;
				ptr=p;
				space=n-sz-2;
			} else{//if space is enough
				--space;
			}
		}//manage memory
		ptr[sz]=c;//set inputted char
		ptr[++sz]=0;//set null as c style
		return *this;
	}
	
	void String::copy_from(const String& x){
		if(x.sz<=short_max){//have to use SSO
			memcpy(this, &x, sizeof(x));
			ptr=ch;
		} else{//have to use heap
			ptr=expand(x.ptr, x.sz+1);
			sz=x.sz;
			space=0;
		}
	}
	void String::move_from(String& x){
		if(x.sz<=short_max){//have to use SSO
			memcpy(this, &x, sizeof(x));
			ptr=ch;
		} else{//have to use heap
			ptr=x.ptr;
			sz=x.sz;
			space=x.space;
			x.ptr=x.ch;//because of move. make ptr point ch that is inner char[]
			x.sz=0;
			x.ch[0]=0;//end set for c style
		}
	}
	
	//helper functions
	std::ostream& operator<<(std::ostream& os, const String& s){ return os<<s.c_str(); }//[stream operator overloading]
	std::istream& operator>>(std::istream& is, String& s){//space for get result(s)
		s="";//initial set
		is>>std::skipws;//skip space
		char ch=' ';
		while(is.get(ch)&&!isspace(ch))
			s+=ch;
		return is;//return istream
	}
	bool operator==(const String& a, const String& b){//[== != operator overloading]
		if(a.size()!=b.size())
			return false;
		for(int i=0; i!=a.size(); ++i)
			if(a[i]!=b[i])
				return false;
		return true;
	}
	bool operator!=(const String&a, const String& b){ return !(a==b); }//reuse
	char* begin(String& x){ return x.c_str(); }//[Iterator for range-based loof]
	char* end(String& x){ return x.c_str()+x.size(); }
	const char* begin(const String& x){ return x.c_str(); }//const version
	const char* end(const String& x){ return x.c_str()+x.size(); }
	String& operator+=(String& a, const String& b){//[+= + operator overloading]
		for(auto x: b)
			a+=x;
		return a;
	}
	String operator+(const String& a, const String& b){//reuse
		String res{a};
		res+=b;
		return res;
	}
	String operator"" _s(const char* p, size_t){ return String{p}; }//[Literal operator overloading]
	
	
	int hash(const String& s){//hash function by xor*operator[]
		if(s.size()==0)
			return 0;
		int h{s[0]};
		for(int i{1}; i<s.size(); ++i)
			h^=s[i]>>1;
		return h;
	}
	
	void print_in_order(const String& s, const std::vector<int>& index){
		for(auto x: index)
			std::cout<<s.at(x)<<'\n';
	}
	
	char* expand(const char* ptr, int n){//expand to heap memory(escape SSO)
		char* p=new char[n];
		strcpy(p, ptr);
		return p;
	}
}

int main(){
	using namespace self_string;
	
	String s("abcdefghij");
	std::cout<<s<<'\n';
	
	s+='k';
	s+='l';
	s+='m';
	s+='n';
	std::cout<<s<<'\n';
	
	String s2="Hell";
	s2+=" and high water";
	std::cout<<s2<<'\n';
	
	String s3="qwerty";
	s3=s3;//self assign on SSO
	String s4="the quick brown fox jumped over the lazy dog";
	s4=s4;//self assign on heap
	std::cout<<s3<<" "<<s4<<'\n';
	std::cout<<s+". "+s3+String(". ")+ "Horsefeathers\n";
	
	String buf;
	while(std::cin>>buf && buf!="quit")
		std::cout<<buf<<" "<<buf.size()<<" "<<buf.capacity()<<'\n';
	
	return 0;
}

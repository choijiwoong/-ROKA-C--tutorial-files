/*
빌드옵션이나 프로그램코드의옵션으로 수행되는 테스트들은 디버그버전시스템과 상품버전으로 나뉘는데, 상품버전 출시에서도 최소한 몇 가지 테스트를 남겨두는 것이 좋다. Assert level0규약은 항상 체크되는 것처럼.
몇가지 정상성 체크를 남겨두어야하며, 소멸자는 던지지 않아야 하므로 당연히 소멸자에서 Assert()던지기를 사용하면 안된다. 
*/

#include <iostream>

namespace Assert{
	enum class Mode{throw_, terminate_, ignore_};
	constexpr Mode current_mode=CURRENT_MODE;
	
	constexpr int current_level=CURRENT_LEVEL;
	constexpr int default_level=1;
	constexpr bool level(int n){ return n<=current_level; }
	struct Error: runtime_error{ 
		Error(const string& p): runtime_error(p){} 
	};
	//...
	
	string compose(const char* file, int line, const string& message){
		ostringstream os("(");
		os<<file<<","<<line<<"):"<<message;
		return os.str();
	}
	
	template <bool condition=level(default_level), typename Except=Error>//use this as base function
	void dynamic(bool assertion, const string& message="Assert::dynamic failed");{//default argument is always at last
		if(assertion)
			return;
		if(current_mode==Assert_mode::throw_)
			throw Except{message};
		if(current_mode==Assert_mode::terminate_)
			std::terminate();
	}
	
	template<>
	void dynamic<false, Error>(bool, const string&){}//nothing
	void dynamic(bool b, const string& s){ dynamic<true, Error>(b, s); }//default setting
	void dynamic(bool b){ dynamic<true, Error>(b); }
}

void f(int n){//examples of using
	Assert::dynamic<Assert:level(2), Assert::Error>(
		(1<=n && n<max), Assert::compose(__FILE__, __LINE__, "range problem"));
	//...
}
void f2(int n){//use default setting
	Assert::dynamic((1<=n && n<max), Assert::compose(__FILE__, __LINE__, "range problem"));
	//...
}
void f3(int n){
	dynamic(1<=n && n<max);
}

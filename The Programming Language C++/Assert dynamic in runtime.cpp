/*
����ɼ��̳� ���α׷��ڵ��ǿɼ����� ����Ǵ� �׽�Ʈ���� ����׹����ý��۰� ��ǰ�������� �����µ�, ��ǰ���� ��ÿ����� �ּ��� �� ���� �׽�Ʈ�� ���ܵδ� ���� ����. Assert level0�Ծ��� �׻� üũ�Ǵ� ��ó��.
��� ���� üũ�� ���ܵξ���ϸ�, �Ҹ��ڴ� ������ �ʾƾ� �ϹǷ� �翬�� �Ҹ��ڿ��� Assert()�����⸦ ����ϸ� �ȵȴ�. 
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

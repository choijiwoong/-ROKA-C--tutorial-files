#include <iostream>
#include <exception>

namespace{
	//exception customizing
	struct My_error: runtime_error{
		My_error(int x): runtime_error{"My_error"}, interesting_value{x}{}
		int interesting_value;
	};
	
	//structure of make_exception_ptr
	template<typename E>
	exception_ptr make_exception_ptr(E e) noexcept//current_exception을 exception_ptr에 담아 exception_ptr을 make
	try{
		throw e;
	} catch(...){
		return current_exception();
	}
	
	//nested_exception example
	struct My_error2: runtime_error{
		My_error2(const string&);
		//...
	};
	void my_code(){
		try{
			//...
		} catch(...){
			My_error2 err{"something went wrong in my_code()"};
			//...
			throw_with_nested(err);
		}
	}
	void user(){
		try{
			my_code();
		} catch(My_error2& err){
			//...solve
			try{
				rethrow_if_nested(err);//exist, rethrow
			} catch(Some_error& err2){
				//...resolve
			}
		}
	}
	
	//mapping of error_code
	enum class future_errc{//1.	define enum by error_code
		broken_promise=1;
		future_already_retrived,
		promise_already_satisfied,
		no_state
	};
	
	class future_cat: public error_category{//2. define proper category about error_code
		public:
			const char* name() const noexcept override{ return "future"; }
			string message(int ec) const override;
	};
	const error_category& future_category() noexcept{
		static future_cat obj;
		return obj;
	}
	
	string future_cat::message(int ec) const{//3. mapping int value to message string
		switch(static_cast<future_errc>(ec)){
			default:
				return "bad future_cat code";
			case future_errc::broken_promise:
				return "future_error: broken promise";
			case future_errc::future_already_retrived:
				return "future_error: future already retrieved";
			case future_errc::promise_already_satisfied:
				return "future_error: promise already satisfied";
			case future_errc::no_state:
				return "future_error: no state";
		}
	}
	
	error_code make_error_code(future_errx e) noexcept{//4. use
		return error_code(int(e), future_category());
	}
	
	//5. upgrade
	template<>
	struct is_error_code_enum<future_errc>: public true_type{};
	template<typename>
	struct is_error_code_enum: public false_type{};
	
	error_condition make_error_condition(future_errc e) noexcpet;
	
	template<>
	struct is_error_condition_enum<future_errc>: public true_type{};
	template<>
	struct is_error_condition_enum: public false_type{};
}

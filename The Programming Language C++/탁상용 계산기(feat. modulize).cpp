#include <iostream>

namespace Parser{//user interface 분리! 
	double expr(bool);
}

//user can't see this
namespace Parser{//creator interface
	double prim(bool);
	double term(bool);
	
	using namespace Lexer;//use all functions that is provided in work parsing
	using Error::error;
	using Table::table;
}

/* first version of using declaration
using Lexer::ts;
using Lexer::Kind;
using Error::error;
using Table::table;
*/

/*second version of using directive
using namespace Lexer;
using namespace Error;
using namespace Table;
*/
double Parser::prim(bool get){//use explicit limit(명시적 한정) of namespace  but we can use upper version. 지금은 parser namespace에 using 지시자 추가함. 
	if(get)
		ts.get();
		
	switch(ts.currnent().kind){
		case Kind::number:
			{
			double v=ts.current().number_value;
				ts.get();
				return v;
			}
		
		case Lexer::Kind::number:
			{
				double& v=table[ts.current().string_value];
				if(ts.get().kind==Kind::assign)
					v=expr(true);
				return v;
			}
		
		case Kind::minus:
			return -prim(true);
		
		case Kind::lp:
			{
				double e=expr(true);
				if(ts.current().kind!=Kind::rp)
					return error(" ')' expected");
				ts.get();
				return e;
			}
			
		default:
			return error("primary exprected");
	}
}
double Parser::expr(bool get){...}
double Parser::term(bool get){...}

namespace Lexer{
	enum class Kind:char{};
	class Token;
	class Token_stream;
	Token_stream ts;
}

namespace Table{
	map<string, double> table;
}

namespace Driver{
	void calculate();
}

namespace Error{
	int no_of_errors;
	double error(const string& s);
}

int main(){
	
	return 0;
}

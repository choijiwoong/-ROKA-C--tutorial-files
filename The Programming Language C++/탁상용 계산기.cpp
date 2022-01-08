//구분 분석기(parser)와 입력 함수, 기호 테이블, 드라이버로 구성할 예정이다. 

/*
	[구분 분석기] 
1.	구문 분석기에서 받아들여지는 언어 문법은 아래와 같다.
program:
	end
	expr_list end
expr_list:
	expression print
	expression print expr_list
expression:
	expression + term
	expression - term
term:
	term / primary
	term * primary
	primary
primary:
	number
	name
	name=expression
	-primary
	(expression) 
2.	직관적인 top-down기법인 recursive descent 즉 재귀적 하강 문법 분석 스타일을 사용한다. terminal symbol은 어휘분석기에 인식되고, nonterminal symbol은 expr(), term(), prim()등의 문법 해석 함수에서 인식된다.
3.	구문분석기가 문자를 읽고 그것을 Token으로 캡슐화하는 Token_stream을 이용하며 ts.get(), ts.current()등을 지원한다. Token은 {number, 123.45}처럼 {kind of token, value}로 구성된 값이다. 
4.	각각의 구문분석기 함수(자신의 표현식을 평가해 결과값을 반환)는 bool get인자를 받아 다음 토근을 얻기 위해 Token_stream::get()호출여부를 결정한다. 
5.	각 대입 연산자=는 개별적인 어휘 토큰이라는 것에 유의하자. a + = 1;은 공백때문에 문법 오류를 일으킨다(a+=1; 로 해석 X) 
6.	prim은 기본 단위 primary를 expr()및 term()과 비슷한 방식으로 처리한다. 항상 사용하는 것보다 하나 더 많은 Token을 분석을 위해 읽는 것에 유의하자.
7.	기호 테이블은 map<string, double> table로 map이다. 사용자가 예로 radius=63778.388;이라고 입력할 시 내부적으로 double& v=table["radius"]; v=6378.388을 처리한다. 

	[입력] 
1.	상위토큰을 만들어 상위 수준의 루틴을 위한 입력 단위를 만들자. 저수준 입력은 ts.get()에 의해 처리되며 Token_stream에 전체적인 정의를 우선 완성하자. 

	[저수준 입력]
1.	출력을 위한 ;, 공백을 넣어 x =7꼴로 만들어야 하는 것들은 귀찮기에 get을 발전시켜보자. 
*/
enum class Kind: char{
	name, number, end,
	plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
};
struct Token_stream{
	public:
		Token_stream(istream& s): ip{&s}, owns{false}{}
		Token_stream(istream* p): ip{p}, owns{true}{}
		
		~Token_stream(){ close(); }
		 
		Token get();
		const Token& current(){ return ct; }
		
		void set_input(istream& s){ close(); ip=&s; owns=false; }
		void set_input(istream* p){ close(); ip=p; owns=true; }
	
	private:
		void close(){ id(owns) delete ip; }
		istream* ip;
		bool owns;//ip가 &인지 *인지. 
		Token ct{Kind::end};//초기값 for 사용자 실수(current token)
};
Token Token_stream::get(){//[입력]
	char ch=0;
	//[저수준 입력]
	do{//\n을 제외한 공백을 건너뛴다. 
		if(!ip->get(ch))
			return ct={Kind::end};
	}while(ch!='\n' && isspace(ch));
	
	*ip>>ch;//read string by space(for check type)
	
	switch(ch){
		case ';':
		case '\n':
			return ct={Kind::print};
		
		case 0://read null
			return ct={Kind::end};//assign & return
		
		case ';':
		case '*':
		case '/':
		case '+':
		case '-':
		case '(':
		case ')':
		case '=':
			return ct={static_cast<Kind>(ch)};//assign & return to enum
		
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': cast '9': case '.':
			ip->putback(ch);//다시 넣기
			*ip>>ct.number_value;//숫자를 읽기
			ct.kind=Kind::number;//set ct
			return ct; 
		
		default://it must be name
			if(isalpha(ch)){
				//ip->putback(ch);//다시 넣기 
				//*ip>>ct.string_value;//문자열 읽기 
				//[저수준 입력]
				ct.string_value=ch;
				while(ip->get(ch)){
					if(isalnum(ch)){
						ct.string_value+=ch;//ch를 string_value끝에 붙여서 >>로 발생하던 기존의 문제를 근자나 숫자가 아닌 문자가 만날 때 까지 한 번에 한 문자씩 읽는 방법으로 해결한다. 
					} else{//(여기서의 문제는 v +1처럼 띄어쓰는 것을 말함) 
						ip->putback(ch);
						break;
					}
				} 
				ct.kind=Kind::name;//set ct
				return ct;
			} else{
				error("bad token");
				return ct={Kind::print};
			}
	}
}

double prim(bool get){
	if(get)
		ts.get();//다음 토큰 읽기 
	switch(ts.current(). kind){
		case Kind::number:
			{
				double v=ts.current().number_value;
				ts.get();
				return v;
			}
		case Kind::name:
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
				auto e=expr(true);
				if(ts.current().kind!=Kind::rp)//after expr
					return error("')' expected");
				ts.get();
				return e;
			}
		default:
			return error("primary exprected");
	}
}

double term(bool get){
	double left=prim(get);
	for(;;){
		switch(ts.current().kind){
			case Kind::mul:
				left*=prim(true);
				break;
			case Kind::div:
				if(auto d=prim(true)){
					left/=d;
					break;
				}
				return error("divide by 0");
			default:
				return left;
		}
	}
} 

double expr(bool get){
	double left=term(get);
	for(;;){
		switch(ts.current().kind){
			case Kind::plus:
				left+=term(true);
				break;
			case Kind::minus:
				left-=term(true);
				break;
			default:
				return left;
		}
	}
}

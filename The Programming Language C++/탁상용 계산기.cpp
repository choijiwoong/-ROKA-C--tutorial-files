//���� �м���(parser)�� �Է� �Լ�, ��ȣ ���̺�, ����̹��� ������ �����̴�. 

/*
	[���� �м���] 
1.	���� �м��⿡�� �޾Ƶ鿩���� ��� ������ �Ʒ��� ����.
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
2.	�������� top-down����� recursive descent �� ����� �ϰ� ���� �м� ��Ÿ���� ����Ѵ�. terminal symbol�� ���ֺм��⿡ �νĵǰ�, nonterminal symbol�� expr(), term(), prim()���� ���� �ؼ� �Լ����� �νĵȴ�.
3.	�����м��Ⱑ ���ڸ� �а� �װ��� Token���� ĸ��ȭ�ϴ� Token_stream�� �̿��ϸ� ts.get(), ts.current()���� �����Ѵ�. Token�� {number, 123.45}ó�� {kind of token, value}�� ������ ���̴�. 
4.	������ �����м��� �Լ�(�ڽ��� ǥ������ ���� ������� ��ȯ)�� bool get���ڸ� �޾� ���� ����� ��� ���� Token_stream::get()ȣ�⿩�θ� �����Ѵ�. 
5.	�� ���� ������=�� �������� ���� ��ū�̶�� �Ϳ� ��������. a + = 1;�� ���鶧���� ���� ������ ����Ų��(a+=1; �� �ؼ� X) 
6.	prim�� �⺻ ���� primary�� expr()�� term()�� ����� ������� ó���Ѵ�. �׻� ����ϴ� �ͺ��� �ϳ� �� ���� Token�� �м��� ���� �д� �Ϳ� ��������.
7.	��ȣ ���̺��� map<string, double> table�� map�̴�. ����ڰ� ���� radius=63778.388;�̶�� �Է��� �� ���������� double& v=table["radius"]; v=6378.388�� ó���Ѵ�. 

	[�Է�] 
1.	������ū�� ����� ���� ������ ��ƾ�� ���� �Է� ������ ������. ������ �Է��� ts.get()�� ���� ó���Ǹ� Token_stream�� ��ü���� ���Ǹ� �켱 �ϼ�����. 

	[������ �Է�]
1.	����� ���� ;, ������ �־� x =7�÷� ������ �ϴ� �͵��� �����⿡ get�� �������Ѻ���. 
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
		bool owns;//ip�� &���� *����. 
		Token ct{Kind::end};//�ʱⰪ for ����� �Ǽ�(current token)
};
Token Token_stream::get(){//[�Է�]
	char ch=0;
	//[������ �Է�]
	do{//\n�� ������ ������ �ǳʶڴ�. 
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
			ip->putback(ch);//�ٽ� �ֱ�
			*ip>>ct.number_value;//���ڸ� �б�
			ct.kind=Kind::number;//set ct
			return ct; 
		
		default://it must be name
			if(isalpha(ch)){
				//ip->putback(ch);//�ٽ� �ֱ� 
				//*ip>>ct.string_value;//���ڿ� �б� 
				//[������ �Է�]
				ct.string_value=ch;
				while(ip->get(ch)){
					if(isalnum(ch)){
						ct.string_value+=ch;//ch�� string_value���� �ٿ��� >>�� �߻��ϴ� ������ ������ ���ڳ� ���ڰ� �ƴ� ���ڰ� ���� �� ���� �� ���� �� ���ھ� �д� ������� �ذ��Ѵ�. 
					} else{//(���⼭�� ������ v +1ó�� ���� ���� ����) 
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
		ts.get();//���� ��ū �б� 
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

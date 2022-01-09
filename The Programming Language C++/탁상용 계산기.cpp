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

	[����ó��]
1.	������ ������ ����, ����Ѵ��� ����� ��ȯ�ϴ� error�Լ��� �����ߴ�. 
2.	������ ���� ó�� ��Ŀ������ ����Ž���� ���� ������ ���е�����, �츮 Ź��� ������ ���ؿ����� stream::get()�� �� ��ȣ�� ����ϰ� �ִٴ� ���� �Ͽ� ������ �߻���ġ�� ����ڿ� �˸� �� �ֱ⿡ �������� �����ϴ�. 

	[����̹�]
1.	������ ���� ����̺�� �غ�� �������� ����� main, ���� ����� ó���� calculate()�� ����Ѵ�. 

	[Ŀ�ǵ���� ����]
1.	�츮�� ���� expression�� command-line argument�� �Էµ� �� �ִٸ� ��� Ű�� �� ������ �Ǳ⿡ �������Ѻ���
2.	main�� ȣ���ϴ� �Ծ��� C�� �������̱⿡ C��Ÿ�� ���ڿ��� ���ȴ�. ��� �Է½�Ʈ������ �о���̴� �Ͱ� ���� ������� ��� ���ڿ����� �о������. Token_stream�� ������ istringstream���� �а� �ϸ� �ȴ�. 
*/

#include <iostream>//io
#include <string>
#include <map>
#include <cctype>//isalpha()

using namespace std;

//definition
double error(const string& s);//increase global variable no_of_errors and print current num of errors and return 1
enum class Kind: char{//for expression name, number, end, operators for parsing
	name, number, end,
	plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
};
struct Token{//it can get string_value or number_value by it's Kind(enum) member
	Kind kind;
	string string_value;
	double number_value;
};
struct Token_stream{//it provides get(), current(), set_input(istream& s), set_input(istream* p). we have to judge is it pointer or reference by it's member owns
	public:
		Token_stream(istream& s): ip{&s}, owns{false}{}
		Token_stream(istream* p): ip{p}, owns{true}{}
		
		~Token_stream(){ close(); }
		 
		Token get();
		const Token& current(){ return ct; }
		
		void set_input(istream& s){ close(); ip=&s; owns=false; }
		void set_input(istream* p){ close(); ip=p; owns=true; }
	
	private:
		void close(){ if(owns) delete ip; }
		istream* ip;
		bool owns;//ip�� &���� *����. 
		Token ct{Kind::end};//�ʱⰪ for ����� �Ǽ�(current token)
};
double prim(bool get);//handling primary, read and handling TokenStream by it's Token by using ts.current(). (ts is global vaiable of Token_stream)
double term(bool get);//* & /
double expr(bool get);//+ & -
void calculate();//call expr function properly.
int main(int argc, char* args[]);//use command-line argument



//global variables
int no_of_errors;//[���� ó��]error function like exception object.
Token_stream ts{cin};//use input of cin
map<string, double> table;



double error(const string& s){
	no_of_errors++;
	cerr<<"error: "<<s<<'\n';//cerr is unbuffered stream so it's used for reporting error.
	return 1;
}

//inner structure
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
			
		case '*':
		case '/':
		case '+':
		case '-':
		case '(':
		case ')':
		case '=':
			return ct={static_cast<Kind>(ch)};//assign & return to enum
		
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
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

//functions
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


double expr(bool get){//[����̹�] 
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



void calculate(){
	for(;;){
		ts.get();//user input(correctly, std input)
		if(ts.current().kind==Kind::end) break;
		if(ts.current().kind==Kind::print) continue;
		
		cout<<expr(false)<<'\n';
	}
}

int main(int argc, char* argv[]){
	switch(argc){//for using command-line argument
		case 1:
			break;
		
		case 2:
			ts.set_input(new istringstream(argv[1]));
			break;
			
		default:
			error("too many arguments");
			return 1;
	}
	
	table["pi"]=3.1415926535897932385;//rounded value
	table["e"]=2.7182818284590452354;
	
	calculate();
	
	return no_of_errors;//num of error
}

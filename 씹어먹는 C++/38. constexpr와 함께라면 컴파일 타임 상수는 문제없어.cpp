#include <iostream>
#include <type_traits>//6

/*1 use of constexpr
template <int N>
struct A{
	int operator()(){return N;}
};
int main(){
	constexpr int size=3;
	int arr[size];//Good!
	
	constexpr int N=10;
	A<N> a;//Good!
	std::cout<<a()<<std::endl;
	
	constexpr int number=3;
	enum B{x=number, y, z};
	std::cout<<B::x<<std::endl;
}*/

/*2 defference of constexpr & const
int a;
//Do something...
const int b=a;

int a_;
//Do something
constexpr int b_=a_;//error 'int a_ is not const'

const int i=3;//initialization in compile time? or runtime? Ambiguous in perception of compiler.
*/

/*3 It was impossible making compile time const object without constexpr in past.
int factorial(int N){
	int total=1;
	for(int i=1; i<=N; i++)
		total*=i;
		
	return total;
}

template <int N>
struct A{
	int operator()(){return N;}
};

int main(){
	A<factorial(5)> a;//error occur because factorial(5) isn't compile time const. 
}//so we have to use complex template meta programming for solving this problem before like this.
*/

/*3 make compile time const object by using TMP.
template <int N>
struct Factorial{
	static const int value=N*Factorial<N-1>::value;//Like recursive
};

template <>//template specialization for stop condition of Fatorial
struct Factorial<0>{
	static const int value=1;
};

template <int N>
struct A{
	int operator()(){ return N; }
};

int main(){
	A<Factorial<10>::value> a;//it can be used by template argument because it's decided in compile time thanks to template meta programming.
	
	std::cout<<a()<<std::endl;
}*/

/*3 make compile time const object by using constexpr
constexpr int Factorial(int n){//explicitly expression that return type is constexpr!
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	
	return total;
}

template <int N>
struct A{
	int operator()(){ return N; }
};

int main(){
	A<Factorial(10)> a;//so it can be used by template argument because Factorial always returns constexpr object.
	
	std::cout<<a()<<std::endl;
}*/

/*3 compile time error occur if we don't keep exception condition of constexpr function
int not_constexpr(int x){ return x++; }
constexpr int Factorial(int n){
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	
	not_constexpr(total);//error occur "call to non_constexpr function"
	return total;
}*/

/*3 constexpr with normal argument not compile time const variable
constexpr int Factorial(int n){
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	return total;
}//error my compiler,,only
int main(){
	int num;
	std::cin>>num;//num is not compile time const!
	std::cout<<Factorial(num)<<std::endl;//constexpr int function can get compile time const successfully.
}*/

/*5 using of constexpr as template argument with constexpr Constructor, function
class Vector{
	public:
		constexpr Vector(int x, int y) :x_(x), y_(y){}//it gets two int as argument that is literal. It's correct using
		
		constexpr int x() const{return x_;}//accessing member variable is set to constexpr. then, these function like x() & y() can be used in constexpr function.
		constexpr int y() const{return y_;}
	
	private:
		int x_;
		int y_;
};

constexpr Vector AddVec(const Vector& v1, const Vector& v2){
	return {v1.x()+v2.x(), v1.y()+ v2.y()};
}

template <int N>//work in compile time
struct A{
	int operator()(){return N;}
};

int main(){
	constexpr Vector v1{1,2};//constexpr Vector object
	constexpr Vector v2{2,3};
	
	//v1.x() can be used by template argument because v1 is constexpr, v1's x() is constexpr function.
	A<v1.x()> a;
	std::cout<<a()<<std::endl;//Good!
	
	//AddVec(v1, v2).x() can be used by template argument because AddVec function is constexpr and it return Vector object that's .x() is constexpr.
	A<AddVec(v1, v2).x()> b;
	std::cout<<b()<<std::endl;//Good
}*/

/*6 function changing by argument's type by using template
template <typename T>
void show_value(T t){
	std::cout<<"it's not pointer : "<<t<<std::endl;
}

template <typename T>
void show_value(T* t){
	std::cout<<"it's pointer : "<<*t<<std::endl;
}

int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}*/


/*6 function changing by argument's type by using std::is_pointer in type_traits
template <typename T>
void show_value(T t){
	if(std::is_pointer<T>::value)
		std::cout<<"It's pointer"<<*t<<std::endl;//Error occur in template instantiation, because if T is int, this code uses *t to int, so compile error is occur.
	else
		std::cout<<"It's not pointer"<<t<<std::endl;
}

int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}*/

//6 solution by using if constexpr
template <typename T>
void show_value(T t){
	if constexpr (std::is_pointer<T>::value)//error occur in my compiler...only
		std::cout<"It's pointer"<<*t<<std::endl;//can be ignore!
	else
		std::cout<<"It's not pointer"<<t<<std::endl;//can be ignore!
} 
int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}




/*
[0. ���⿡ �ռ�]
1.	C++11���� ���Ե� constexprŰ���带 �˾ƺ� ���ε�, �̴� ��ü�� �Լ� �տ� ���� �� �ִ� Ű�����, �ش� ��ü�� �Լ��� ���ϰ��� ������ Ÿ�ӿ� ���� �˼� �ִ� ��� �ǹ̸� �����ϰ� �ȴ�.
	�����Ϸ��� ������ Ÿ�ӿ� ��� ���� ���� ������ �� ���ٸ� �ش� ���� �����(Constant expression)�̶�� �ϰ�, 
	�� �߿��� ���� ������ ���� ���� �����(Integral constant expression)�̶�� �ϴµ� �̴� ���� ���ӻ��� ���´�.
	int arr[size];���� size��
	
	template <int N>
	struct A{
		int operator()(){return N;}
	};
	A<numver> a;�� number,
	
	enum A{a=number, b, c};�� number
	��� ���� ������̾�� �Ѵ�. ��ó�� C++��� �� ����������� �ſ� ���ϴ�. 
	
[1.	constexpr]
1.	Constexpr�� ��� ���� ������̶�� ������ִ� Ű�����̴�. constecpr�� ��ü���ǿ� ���ȴٸ� �� ��ü�� ��� ����Ŀ��� ���� �� �ִ�. 

[2.	constexpr VS const]
1.	const�� ���ǵ� ������� ���� ������ Ÿ�ӿ� �� ���� �� �ʿ䰡 ������, constexpr�� ��� �ݵ�� �����ʿ� �ٸ� ������� �;� �Ѵ�.
	constexpr�� �׻� const����, const�� constexpr�� �ƴϴ�. 
2.	���� const��ü�� ��������� �ʱ�ȭ�Ǿ��� �ص� �����Ϸ��� ���� �̸� ��Ÿ�ӿ� �ʱ�ȭ����, ������Ÿ�ӿ� �ʱ�ȭ���� �ٸ� �� �ֱ⿡ 
	������ Ÿ�ӿ� Ȯ���� ����� ����ϰ� �ʹٸ� constexpr Ű���带 �� ����ؾ� �Ѵ�. 

[3.	constexpr �Լ�]
1.	constexpr�� ������ Ÿ�� ����� ������ �� �ִٸ�, ������ Ÿ�� ����� ��ü���� ������ �Լ��� ������ �� ������?
2.	constexpr�������� ������ Ÿ�� ����� ��ü�� ����� �Լ��ۼ��� �Ұ����ߴ�. 
	�ٵ� ������ �� �Լ��� ����Ÿ���� constexpr�̶�� ������ָ� ��밡���ϴ�.
3.	C++14���� ��� ���������� ��ȭ�Ǿ� �Ʒ��� ���ǻ���� ��� constexpr�Լ� ���ο��� ������ �� �ִ�.
	-goto�� ���
	-����ó��(try ��; C++20���� ��������)
	-���ͷ� Ÿ���� �ƴ� ������ ����
	-�ʱ�ȭ ���� �ʴ� ������ ����
	-���� �߰��� constexpr�� �ƴ� �Լ��� ȣ���ϰ� ��
	���� ���� ���� �۾��� �ϸ� ������ Ÿ�� ������ �߻��Ѵ�. 
4.	constexpr�̶�� ������ Ÿ�� ����鸸 ���ڷ� ���� �� �ִ� ���� �ƴϰ� �Ϲ� �Լ�ó�� ������ ���� �ִ�. 
	��� constexpr�� �Լ��� ���� �� �ִٸ� �ٿ��ִ� ���� ������, constexpró�� ������ ���ϸ� �Ϲ� �Լ�ó�� ������ ���̰�, ������ Ÿ�� ����� ������ �� �ִٸ� ���� ������ �̿��� �� �ֱ� �����̴�.
	
[4.	���ͷ� Ÿ��?]
1.	constexpr�� �Լ� ���ο��� �Ұ����� �۾����� ���ͷ�(Literal)Ÿ���� �ƴ� ������ ���Ƕ�� �Ͽ��µ�, C++������ ���ͷ���
	-void��
	-��Ż�� Ÿ��(char, int, bool, long, float, double) ��
	-���۷��� Ÿ��
	-�Ʒ� ������ �����ϴ� Ÿ��
		������Ʈ �Ҹ��ڸ� ������ ���� �� �ϳ��� �����ϴ� Ÿ��
			-���� �Լ�
			-ArggregateŸ��(����� ���� ������, �Ҹ��ڰ� ������ ��� ������ ������� public) pair�� ���� �ֵ� 
			-constepxr�����ڸ� ������ ���� �� �̵� �����ڰ� ���� 
2.	���� �ֵ��� ���ͷ� Ÿ���̶�� �ǹ��ϸ�, �ش� ��ü�鸸�� constexpr�� ����Ǵ��� constexpr�Լ� ���ο��� ���� �� �ִ�. 

[5.	constexpr ������]
1.	constexpr�������� ��� constexpr�Լ��� ����Ǵ� �������ǵ��� ��� ����Ǹ�, constexpr�������� ���ڵ��� �ݵ�� ���ͷ� Ÿ���̾�߸� �ϰ�, �ش� Ŭ������ �ٸ� Ŭ������ ���� ��� ���� �� ����.
2.	constepxr��ü�� constexpr��� �Լ����� constexpr�� �ش�.

[6.	if constexpr]
1.	Ÿ�Կ� ���� ���°� �޶����� �Լ��� ¥����. like get_value function�ε� ���ڰ� �����͸� *�� �����ϰ� �ƴϸ� ������ ���ڸ� ����.
	�̷��� �Լ��� template�� �̿��Ͽ� ���� ��������, show_value�Լ��� ��Ȯ�� ��� ������ T�� �䱸�ϴ��� �� ���� �ľ��ϱ� �����,
	���� �Լ��� ��ó�� �� �� ����Ѵٴ� ������ �ִ�.
2.	�̷��� ������ �ذ��ϱ� ���� C++ǥ�� ���̺귯���� <type_traits>������ �������� ���ø� �Լ����� �����ϴµ�, �̵� �� �ش� Ÿ���� ���������� �ƴ��� Ȯ���ϴ� �Լ��� �̿��Ͽ� �����غ����� ����.
	type_traits�� std::is_pointer�� ������ ���� T�� �����Ͷ�� value�� True�� �ǰ�, �ƴϸ� false�� �Ǵ� ���ø� ��Ÿ �Լ��̴�.  
	������ Ÿ�Կ� ���� ���ø� �ν��Ͻ�ȭ �������� �ڵ� ��ü�� ������ �� �� ���� ������ �߻��ϰ� �ȴ�.
3.	�̷��� ������ �ذ��ϱ� ���� if constexpr�� ������ �� �ִ�. 
*/ 

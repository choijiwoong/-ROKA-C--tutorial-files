#include <iostream>

//���� ���� �۾����� ���� �ʴ� �̻� constexpr Ű���带 �Լ��� ���� �� �ְ� �˴ϴ�. ���� ������ �������� �ʴ� �۾��� �Լ� ������ �ϰ� �ȴٸ� ������ Ÿ�� ������ �߻��ϰ� �˴ϴ�. ���� ��

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

//3 compile time error occur if we don't keep exception condition of constexpr function



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
*/ 

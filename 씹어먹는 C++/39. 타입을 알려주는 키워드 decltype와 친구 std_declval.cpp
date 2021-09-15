#include <iostream> 

/*1 using of decltype
struct A{
	double d;
};

int main(){
	int a=3;
	decltype(a) b=2;//int
	
	int& r_a=a;
	decltype(r_a) r_b=b;//int&
	
	int&& x=3;
	decltype(x) y=2;//int&&
	
	A* aa;
	decltype(aa->d) dd=0.1;//double
}*/

/*2-2 lvalue
int i;
i;//i's address is real address value of i
int&& x=i;//impossible! not movable. cannot compile
//most objects have name are lvalue because it can get address of that object.

//2 lvalue exception of referencing member variable or function that is enum or not static.
class A{
	int f();//not static member function
	static int g();//static member function
}
	
A a;
a.f;//not lvalue. it's prvalue
a.g;//lvalue
	
//2 type category & value category
void f(int&& a){//a's type category is rvalue reference, but a's value category is lvalue because it has name.
	a;
}
f(3);


//2 it can compile too
void f(int&& a) { std::cout<<&a; }
int main() { f(3); } 
*/

/*2-3 prvalue
int f() {return 10; }
f();//we can't access it's address, but it can be put at rvalue reference. so it's prvalue

const int& r=42;
int&& rr=42;
int& rrr=2;//impossible! normal lvalue refercence
*/

/*2-4 xvalue
//definition of std::move()
template <class T>
constexpr typename std::remove_reference<T>::type&& move(T&& t) noexcept;
//move's return type is rvalue reference. so it(calls move) can use like lvalue, like prvalue

//then how about decltype?
int a, b;
decltype(a+b) c;//a+b is prvalue so it guess int. ==int c;

int a_;
decltype((a_)) b_;//(a_) can do &(a_) and not movable, so it's lvalue.
//so b's type is guessed to int& not int.???
*/


/*3 necessity of decltype
int i=4;
auto j=i;//int j=i;

int i=4;
decltype(i) j=i;//int j=1;
//it's same result but actually, auto doesn't express correct type.

//3 difference of auto & decltype_it preserve type perfectly 
const int i=4;
auto j=i;//int j=i;
decltype(i) k=i;//const int k=i;

int arr[10];
auto arr2=arr;//int* arr2=arr;
decltype(arr) arr3;//int arr3[10]; much correct!

template <typename T, typename U>
void add(T t, U u, ? result){//what type will be placed? what we have to do? 
	*result=t+u;
}
//we can use decltype like this
template <typename T, typename U>
void add(T t, U u, decltype(t+u)* result){//just use pointer. it's doesn't get any importance.
	*result=t*u;
}

//how about just make function that returns added value? more shortly like this
template <typename T, typename U>
decltype(t+u) add(T t, U u){//compile error! when compiler watch decltype(t+u), say "what's the funcking this?" because decltype(t+u) is front of definition t & u.
	return t+u;
}
//so we have to write return value of function behind of definition of arguments. like this

template <typename T, typename U>
auto add(T t, U u)->decltype(t+u){//just put auto on return value's place, and assign real return type behind of ->.
	return t+u;
}
//it's like grammer of lambda function
*/

/*4 introduce background before making std::declval
struct A{
	int f() { return 0; }
}; 
decltype(A().f()) ret_val;//int ret_val;
//expressiong in decltype() is not runnig in runtime, it just exist form as expression.
//so in upper code, object A is not created and not called function f actually. it's just expression.
//but also, it can catch wrong expression in decltype() like this

struct B{
	B(int x) {}
	int f() { return 0; }
};
int main(){
	decltype(B().f()) ret_val2;//Error! B() is wrong gramatically.
}
//so we have to code correct code that satisfys rule of B's constructor regardless of we don't make object B actually.


template <typename T>
decltype(T().f()) call_f_and_return(T& t){//call member function f by receiving object T (that is random type)
	return t.f();
}
//we can use it if we suppose every objects that will use this function defines member function f.
//but the problem is every type T cannot define default constructor T().

template <typename T>
decltype(T().f()) call_f_and_return(T& t){
	return t.f();
}
struct A{
	int f(){return 0;}
};
struct B{
	B(int x){}
	int f(){return 0;}
};
int main(){
	A a;
	B b(1);
	
	call_f_and_return(a);//Good. default constructor is called!
	call_f_and_return(b);//Bad. it doesn't have default constructor only have constructor with argument
}
//so making constructor directly can make problem when received type's constructor are not same form.
//This problem can be solved by std::declval.
*/

//4 std::declval version of upper code.
#include <utility>
template <typename T>
decltype(std::declval<T>().f()) call_f_and_return(T& t){//std::declval<T> can make effect like T() even if T's constructor is not defined.
	return t.f();
}
struct A{
	int f() {return 0;}
};
struct B{
	B(int x){}
	int f() {return 0;}
};
int main(){
	A a;
	B b(1);
	
	call_f_and_return(a);//Good
	call_f_and_return(b);//Good
}
//so it can prevent error because of differency of constructors of template argument T.

//but declval must be used in type operation, if we use it runtime, error occur.
struct B{
	B(int x){}
	int f() {return 0;}
};
int main(){B b =std::declval<B>();}//error occur. object saving by std::declval.

//compiler can guess return type of funtion at C++14
template <typename T>
auto call_f_and_return(T& t){
	return t.f();
}

/*
[0.	���⿡ �ռ� �������]
1.	C++������ �� ī�װ��� ���� �� ũ�� �ΰ��� ������ �Ѵ�.
	-��ü�� �� �� �ִ°�?_�ٸ� �İ� ���� ������ ������ �����Ѱ�?
	-�̵���ų �� �ִ°�?_�̵�������, �̵����Ի����� ����� �����Ѱ�? 

[1.	decltype]
1.	C++11�� �߰��� Ű�����, decltype��� �̸��� �Լ�ó�� ���ȴ�. like decltype(Ÿ���� �˰��� �ϴ� ��)
2.	decltype�� �Լ��ʹ� �޸�, Ÿ���� �˰��� �ϴ� ���� Ÿ������ ġȯ�Ǿ� �����ϵȴ�.
	���� �ڵ�� ���� decltype�� ���޵� ���� ���� �ѷ������� ���� �ĺ��� ǥ����(id-expression)�̶�� �ش� ���� Ÿ���� ���� �� �ִ�.
3.	�ĺ��� ǥ�����̶�, ������ �̸�, �Լ��� �̸�, enum �̸�, Ŭ���� ��� ���� �� ��� ������ ���� �ʰ� �ܼ��� ��ü �ϳ����� ����Ű�� ���̴�. 
4.	���� decltype�� �ĺ��� ǥ������ �ƴ� ���� ���޵ȴٸ�, �ش� ���� ���� ����(value category)�� ���� �޶�����.
	-xvalue��� decltype�� T&&
	-lvalue��� decltype�� T&
	-prvalue��� decltype�� T

[2.	Value Category]
1.	C++������ 5������ �� ī�װ��� �����ϴµ�, lvalue(������), rvalue(������), prvalue(���� ������), xvalue(�Ҹ��ϴ� ��), glvalue(�Ϲ�ȭ�� ������)�̴�.
	xvalue�� glvalue�� value�� �������̰�, glvalue-rvalue�� lvalue, rvalue-glvalue�� prvalue�̴�.
2.	lvalue
	-����, �Լ��� �̸�, � Ÿ���� ������ ���(std::endl, std::cin)���
	-������ ���۷����� �����ϴ� �Լ��� ȣ���(std::cout<<1, ++it)���
	-a=b, a+=b, a*=b���� ���� ���� ������ �ĵ�
	-++a, --a���� ���� ���� ������ �ĵ�
	-a.m, p->m�� ���� ����� ������ ��(m�� enum�̰ų� static�� �ƴ� ��� �Լ��� ��� ����)
	-a[n]�� ���� �迭 ���� �ĵ�
	-���ڿ� ���ͷ� "hi"
	�̷��� lvalue���� ��� lvalue���� �ּҰ� ������(&)�� ���� �ش� ���� �ּҰ��� �˾Ƴ� �� �ִ�.(&++i, &std::endl) ���� lvalue���� ������ ���۷����� �ʱ�ȭ�ϴµ��� ����� �� �ִ�.
3.	prvalue
	-���ڿ� ���ͷ��� ������ ��� ���ͷ���(42, true, nullptr)���
	-���۷����� �ƴ� ���� �����ϴ� �Լ��� ȣ���(str.substr(1, 2), str1+str2)���
	-���� ���� ������ ��(a++, a--)
	-(default not overloaded)��� ������, �� ������ �ĵ�(a+b, a&&b, a<b)���
	-�ּҰ� ������ �� &a
	-a.p, o->m�� ���� ����� ������ ��(m�� enum�̰ų� nonstatic�� ��츸)
	-this
	-enum ��
	-���ٽ� [](){return 0;};��� 
	prvalue���� ��ü�� �� �� ���⿡ �ּҰ��� ���� �� ���⿡ &a++�� &42���� �����̴�. ���� prvalue�� ���� ������ �� �� ����.
	��� prvalue�� ������ ���۷����� ��� ������ ���۷����� �ʱ�ȭ�ϴµ� ����� �� �ִ�. 
4.	xvalue
	���� �� ī�װ��� lvalue�� prvalue �ΰ��θ� ���еȴٸ�, ���������� �з��Ǵ� ���� �̵���ų ����� ������� ������ �߻��Ѵ�.
	��� �츮�� ������ ó�� ��ü�� ������ �̵��� ��ų �� �ִ� ���� �����ؾ��ϴµ� ��ǥ������ std::move(x)�� �ִ�. 
	��, move�� ȣ���� ���� lvalueó�� ������ ���۷����� �ʱ�ȭ�ϴµ� ����� �� �ְ�, prvalueó�� ������ ���۷����� ���̰ų� �̵� �����ڿ� �����Ͽ� �̵���ų �� �ִ� ��� ������ ������ ���̴�.
	 �㳪, �츰 decltype�� ���� �˰��ִ�. �� ī�װ��� ����ؼ� �����غ���, ��ȣ�� ������ �߷� Ÿ���� �ٲ� �� �ִ�.
	�ٵ� �� �𸣰��� �K
	 
[3.	decltype�� ���ӻ�]
1.	autoŰ����� ������ ���ϸ� ��Ȯ�� Ÿ���� ǥ�������ʱ⿡ Ÿ���� �״�� �����ϴ� decltype�� ����Ѵ�.
2.	���ø� �Լ����� � ��ü�� Ÿ���� ���ø� ���ڵ鿡 ���� �����Ǵ� ��찡 �ִ�. 
3.	auto add(T t, U u)->decltype(t+u){ó�� ���ϰ��ڸ��� auto�� ���� ->�ڿ� ���� �Լ��� ���� Ÿ���� �������־ �ȴ�.
	����Ÿ���� ���ø� ���ڿ� ���� ������ ��쿡 �̷��� ������� �ذ��Ѵ�. 
	
[4.	std::declval]
1.	declval�� decltype�� �޸� Ű���尡 �ƴ϶� <utilty>�� ���ǵ� �Լ��� decltype�� ���� C++11�� �߰��� std::declval�Լ��̴�.
2.	������ decltype�� ��ȣ()�ȿ� ���� ���� ������ ��Ÿ�ӿ� ����Ǵ� ���� �ƴ� �ܼ��� ���� ����������, �츮�� ������ ��Ģ���� �������Ѿ� ����� �����ߴ�.
	��� decltype()�ȿ� �����ڸ� ���� ȣ���ع�����, ��Ģ�� �����ʾ�(����� ���� constructor�� default constructor�� ���ٰų�)�� ������ �߻��� �� �ִ�.
3.	std::declval�� Ÿ�� T�� �����ϸ�, T�� �����ڸ� ���� ȣ������ �ʰ� T�� ������ ��ü�� ��Ÿ�� �� �ִ�. ��, �����ڰ� �������� �ʴ��� ��ġ T()�� ���� ȿ���� ���� �������� ���°� �޶� �߻��ϴ� ������ ���� �� �ִ�. 
4.	C++14���� �˾Ƽ� �����Ϸ��� �Լ��� ����Ÿ���� �������ִ� ����� �߰��Ǿ� �� auto�� ��� ����� ���������� �����滧��
5.	declval�� �ʿ伺�� auto�� ���� �������µ�������, �ڿ� type_traits���̺귯���� �ٷ�� ������ TMP������� ����� �� �ִ�. 
*/

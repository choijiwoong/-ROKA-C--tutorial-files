#include <iostream>

/*common code without decltype keyword
template <typename T, typename U>
void add(T t, U u, (???type) result){
	*result=t+u;
} 

//solution by decltype
template <typename T, typename U>
void add(T t, U u, decltype(t+u)* result){
	*result=t+u;
}

//how about just return added value without result variable?
template <typename T, typename U>
decltype(t+u) add(T t, U u){//compile error! compiler doesn't know what's t and u
	return t+u;
}

//solution by C++14's rule
template <typename T, typename U>
auto add(T t, U u)->decltype(t+u){//explicit auto as return type. like lambda
	return t+u;
}*/

#include <utility>
//need of std::declval not only decltype
template <typename T>
decltype(std::declval<T>().f()) call_f_and_return(T& t){
	return t.f();
}
struct A{
	int f(){ return 0;}
};
struct B{
	B(int x){}
	int f(){ return 0; }
};

int main(){
	A a;
	B b(1);
	
	call_f_and_return(a);
	call_f_and_return(b);
}

/*
1.	decltypeŰ����� Ÿ���� �˰��� �ϴ� ���� Ÿ������ ġȯ�ǰ� �ȴ�. ��ȣ�� �ѷ������� ���� �ĺ��� ǥ����(id-expression);
	��� ������ ���� �ʰ� �ܼ��� ��ü �ϳ����� ����Ű�� ���̸� �� �����ϴ�.
2.	decltype�� �ĺ��� ǥ������ �ƴ� ���� �����ϸ� ���� ����(value category)�� ���� �޶�����. 
	xvalue�� T&&, lvalue�� T&, prvalue�� T�� �ȴ�.
3.	C++�� ��� ��(expression)�� Ÿ�԰� �� ī�װ� �� �ΰ��� ������ �׻� ����ٴѴ�.
	�� ī�װ��� �����ϴ� ������ ��ü�� �� �� �ִ°�(�ּҰ��� ���� �� �ִ���)�� �̵������Ѱ�(T&& x=i ����?)�̴�.
	 xvalue�� ��üO�̵�O, lvalue�� ��üO�̵�X, prvalue�� ��üX�̵�O�̴�. �̶� �̵�O�� rvalue, ��üO�� glvalue��� �Ѵ�.
4.	decltype�� ��ȣ�� ������ ���� �� ī�װ��� �ٲ�� �߷еǴ� Ÿ���� �ٸ� �� �ִ�. 
	int a; decltype((a)) b;���� b�� int&�� �߷еȴ�. ��üO�̵�X�̱⿡ lvalue�� �߷еǱ� �����̴�.
5.	decltype�� auto�� �ٸ��� ��Ȯ�� Ÿ���� ���� �� �ִ�. ��, �迭�� ��� auto�� �����ͷ� ��ȯ������ decltype�� �迭 Ÿ�� �״�θ� �����Ѵ�.
6.	C++14���� �ϴ� �Լ��� �������� auto�� ��ΰ� �Լ� �������Ǻ� �ڿ� ->�� ���� ���� Ÿ���� �������ִ� ���� �����ϴ�.
7.	decltype�� class�� default constructor�� ȣ���Ͽ� �Լ��� �����ϴ� decltype(A().f()) ret_val;�� �Ѵٰ� �ص� ������ Ÿ�ӿ� ���� ���·θ� ������ ��
	��Ÿ�� �ÿ� ����Ǵ� ���� �ƴϴ�. 
8.	decltype�� ������ template���� ��ü�� �Լ��� ȣ���� ���, �ش� ���ø� ���ڷ� ���� (��ü��)Ÿ�Կ� �ش� �Լ��� �������� �ʴٸ� ������ �߻��Ѵٴ� ���̴�.
	�̸� std::declval�� �ذ��� �����ϴ�. 
	declval�� T�� �����ڸ� ���� ȣ������ �ʴ��� T�� ������ ��ü�� ��Ÿ�� �� �ִ�. �̴� �������� ���°� ��� �޶� �߻��ϴ� ������ �ذ����ش�.
	 ���� dtd::declval�� ��Ÿ�ӿ� ����ϸ� ������ �߻��Ѵ�.
	������ decltype(std::decltype<T>())�� �ϸ� ������ ����ȣ����� ��üǥ���� �����ϴ� ����Լ��� �������� .���� ��Ÿ���� decltype Ÿ���� �˾Ƴ� �� �ִ�. 
9.	p.s�� C++14���ʹ� �Լ��� ����Ÿ���� �����Ϸ��� �˾Ƽ� �������ִ� �׳� �Լ� ����Ÿ���� auto�� ����Ͽ� ����ص� �ȴ�. 
 
*/

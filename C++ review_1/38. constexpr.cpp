#include <iostream>

/*make compile time function by constexpr not TMP
constexpr int Factorial(int n){
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	return total;
}

template <int N>
struct A{//template argument return class
	int operator()(){ return N; }
};

int main(){
	A<Factorial(10)> a;
	std::cout<<a()<<std::endl;
}*/

//coding by template argument case without compile error by using if constexpr
template <typename T>
void  show_value(T t){
	if constexpr(std::is_pointer<T>::value)
		std::cout<<"pointer: "<<*t<<std::endl;
	else
		std::cout<<"not pointer: "<<t<<std::endl;
}

int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}


/*
1.	constexpr;������ Ÿ�� ���. ���� ������ Ÿ�ӿ� �� �� �ִ�, �� ������̶�� ������ִ� Ű�����̴�. (like array's size)
2.	const�� ���� ������ �ָ� �ٲܼ� ���� ���� �翬������, ������ Ÿ�ӿ� ���� �� ���� �� �ʿ䰡 ����. ���� ������Ÿ���̳� ��Ÿ�ӿ� �ʱ�ȭ�ȴ�. 
	�ݸ鿡 constexpr�� �ݵ�� �����ʿ� �ٸ� ������� �;� �Ѵ�. ���int a;  constexpr int b=a;�� ������ ������ �߻���Ų��. 
3.	TMP�� ����Ͽ� ������ Ÿ�� �Լ��� ����� ������� �ݸ�, 
	������ �´´ٸ� constexpr�� ����Ͽ� �Լ��� ���ϰ��� ������ Ÿ�� ���constexpr�� ���� �� �ִ�.(ex. �Լ� ���ο��� constexpr�� �ƴ� �Լ� ȣ��) 
4.	�����ϸ� �Լ��� constexpr�� ���̴°� ������, ������ Ÿ�� ����� ������ �� ���ٸ� �Ϲ� �Լ�ó�� �۵��ϱ� �����̴�. 
5.	constexpr��ü�� constexpr��� �Լ����� constexpr�� �ش�!(constexpr�� ���� �� �ִ�)
	<type_traits>���� ���� ���ø� �Լ����� �����ϴµ�, �� �߿� std::is_pointer<T>::value��� ���������� �ƴ����� Ȯ���ϴ� �Լ��� �ִ�.
	�츰 �̸� if�� ó�������ν� �������϶��� �����Ͱ� �ƴ� ���� �����Ͽ� �ڵ��� �� �ִµ�, ������ TMP�� ���� template argument�� ����
	������ ��ü�� �Ұ����� �����ڵ尡 �ν��Ͻ�ȭ�� ���� �ִ�. 
	 �׷��� if constexpr���� ����Ͽ� ó���ϸ�, �ش��ϴ� �κ� �� if constexpr�� else�߿��� ���� �κи� �����ϵǰ� ������ �κ��� �ƿ� ���õǾ� ������ ������ �߻����� �ʴ´�.
	  
*/

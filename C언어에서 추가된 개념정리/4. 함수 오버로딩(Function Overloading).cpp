#include <iostream>

using namespace std;

void func(int a){
	cout <<"void func(int a)�� ȣ���!"<<endl;
}

void func(int a, int b){
	cout<<"void func(int a, int b)�� ȣ���!"<<endl;
}

int main()
{
	func(4);
	func(5,6);
	return 0;
}

//warning-> int add(int a, int b){...} �� double add(int a, int b){...}�� ���� 

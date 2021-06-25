#include <iostream>

using namespace std;

void func(int a){
	cout <<"void func(int a)이 호출됨!"<<endl;
}

void func(int a, int b){
	cout<<"void func(int a, int b)이 호출됨!"<<endl;
}

int main()
{
	func(4);
	func(5,6);
	return 0;
}

//warning-> int add(int a, int b){...} 과 double add(int a, int b){...}는 오류 

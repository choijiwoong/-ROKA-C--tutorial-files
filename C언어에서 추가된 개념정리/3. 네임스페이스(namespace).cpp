#include <iostream>

namespace A{
	void Add(){
		printf("A의 Add() 호출!\n");
	}
	
	void Minus(){
		printf("A의 Minus() 호출!\n");
	}
	
	int variable;
}

namespace B{
	void Add(){
		printf("B의 Add() 호출!\n");
	}
	//A::variable=20; error occur
}

int main()
{
	A::variable=10;
	A::Add();
	B::Add();
	return 0;
}

using namespace A;
int main2()
{
	Add();
	Minus();
	return 0;
}

using namespace A::Add;
int main3()
{
	Add();
	A:Minus();
	return 0;
}

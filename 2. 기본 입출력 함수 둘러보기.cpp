#include <iostream>

int main()
{
	//cout(console out)
	//기본 출력형 
	std::cout << "hello, world!" << std::endl;
	
	//변수출력형 
	char name[10]="최지웅";
	std::cout<<"저의 이름은"<< name << "입니다."<<std::endl;
	
	//개행
	std::cout<<"Hello, World!";
	std::cout<<"Hello, World!"<<std::endl; 
	
	//cin(console input)
	char myname[10];
	int age; 
	
	std::cin>>name>>age;//shift연산자의 방향이 cout의 반대 
	std::cout<<"당신의 이름은 "<<name<<"입니다. 나이는 "<<age<<std::endl;//****printf, scanf와의 차이점은 형식지정무필요 
	
	return 0;
}

#include <iostream>

int main()
{
	//cout(console out)
	//�⺻ ����� 
	std::cout << "hello, world!" << std::endl;
	
	//��������� 
	char name[10]="������";
	std::cout<<"���� �̸���"<< name << "�Դϴ�."<<std::endl;
	
	//����
	std::cout<<"Hello, World!";
	std::cout<<"Hello, World!"<<std::endl; 
	
	//cin(console input)
	char myname[10];
	int age; 
	
	std::cin>>name>>age;//shift�������� ������ cout�� �ݴ� 
	std::cout<<"����� �̸��� "<<name<<"�Դϴ�. ���̴� "<<age<<std::endl;//****printf, scanf���� �������� �����������ʿ� 
	
	return 0;
}

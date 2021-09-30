#include <iostream>
#include <exception>

//exception logic error on class interitance
class Parent: public std::exception{
	public:
		virtual const char* what() const noexcept override{ return "Parent!\n";}
};
class Child: public Parent{
	public:
		const char* what() const noexcept override{ return "Child!\n"; }
};

int func(int c){
	if(c==1)
		throw Parent();
	else if(c==2)
		throw Child();
	return 0;
}

int main(){
	int c;
	std::cin>>c;
	
	try{
		func(c);
	} catch (Parent& p){//Parent must be afte Child's catch! throw find catch in near, so if Parent& p=c is possible, compiler get child object to Parent's catch.
		std::cout<<"Parent Catch!"<<std::endl;
		std::cout<<p.what();
	} catch (Child& c){
		std::cout<<"Child Catch!"<<std::endl;
		std::cout<<c.what();
	}
}
 

/*
1.	throw�� ���ܷ� �����ϰ� ���� ��ü�� ���ָ� �ȴ�. ����ó���ϸ鼭 stack�� �����Ǿ��� ��ü���� �������� �Ҹ�����ش�(�Ҹ��ڸ� ����� �ۼ��Ѵٸ�. ��� �Ҹ��ڿ��� throw����) 
2.	try���� ���ܰ� �߻����� �ʾҴٸ� try..catch�� ���� �� ó�� ����ȴ�. 
3.	�����ڿ��� ���� �߻��ÿ� �Ҹ��ڸ� ȣ���Ű�� �ʱ⿡ catch���� ���� ó���ؾ� �Ѵ�.
4.	�׳� �߻��ϴ� ��� ���ܿ� ���� ó���Ϸ��� catch(....)ó�� ���� �ȴ� like parameter pack �ַ� �ν��Ͻ�ȭ�Ǳ����� ����� �𸣴� template �Լ����� ��� 
5.	noexceptŰ���带 ���̴� ���� ���� �����Ϸ����� �ִ� ��Ʈ�̴�. ����ȭ�� ����. ���� �߻��Ѵٸ� ó���� ����� ���� �ʰ� ����� �� 
*/

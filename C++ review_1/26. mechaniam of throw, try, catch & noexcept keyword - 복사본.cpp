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
1.	throw로 예외로 전달하고 싶은 객체를 써주면 된다. 예외처리하면서 stack에 생성되었던 객체들을 빠짐없이 소멸시켜준다(소멸자만 제대로 작성한다면. 고로 소멸자에선 throw금지) 
2.	try에서 예외가 발생하지 않았다면 try..catch가 없는 것 처럼 실행된다. 
3.	생성자에서 예외 발생시엔 소멸자를 호출시키지 않기에 catch에서 따로 처리해야 한다.
4.	그냥 발생하는 모든 예외에 대해 처리하려면 catch(....)처럼 쓰면 된다 like parameter pack 주로 인스턴스화되기전에 결과를 모르는 template 함수에서 사용 
5.	noexcept키워드를 붙이는 것은 단지 컴파일러에게 주는 힌트이다. 최적화를 위해. 예외 발생한다면 처리가 제대로 되지 않고 종료될 뿐 
*/

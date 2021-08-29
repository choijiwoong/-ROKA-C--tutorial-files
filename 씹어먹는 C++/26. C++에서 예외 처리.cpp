#include <iostream>
#include <vector>
#include <string> 
#include <stdexcept>

/*1
int main(){
	//exceptions.
	//out of range
	std::vector<int> v(3);
	std::cout<<v.at(4);//not problem on grammer. but it's out of range.
	//too much allocation
	std::vector<int> V(1000000000000000);
	
	return 0;
}*/

/*2
//for show unconvenience of exception that we check result not process in C language.
#include <stdio.h>

bool func2(int *addr);
bool func3(int *addr);

bool func1(int *addr){
	if(func2(addr)){
		//do something
	}
	return false;
}
bool func2(int *addr){
	if(func3(addr)){
		//do something
	}
	return false;
}
bool func3(int *addr){
	addr=(int *)malloc(100000000000);
	if(addr==NULL)
		return false;
	return true;
}

int main(){
	char *c=(char *)malloc(100000000000);
	if(c==NULL){//if allocation is failed, save NULL to c.
		printf("memory allocation error!\n");//so we can check exception!
		return 0;
	}//but this way is unconvenient if we code long code. like this.
	
	//difficult of check error point.
	int *addr;
	if(func1(addr)){
		//well done
	} else{
		//error occur
	}
	//in perceptin of main function, all result of functions have to be returned for catch error.
	//and even not only func3 but also func2 make error?
	//The solution of this problem is in C++.
	
	return 0;
}*/

/*34
//mcdonald set of throw!
template <typename T>
class Vector{
	public:
		Vector(size_t size):size_(size){
			data_=new T[size_];
			for(int i=0; i<size_; i++)
				data_[i]=3;
		}
		//when we use T&, we can't return value that we can know 'error occur!' because it's const. but thanks to throw, we can handle that.
		const T& at(size_t index) const{//[] can change value, T.at() can't change value. it's const.
			if(index>=size_)
				throw std::out_of_range("vector's index range is over.");
			return data_[index];
		}
		~Vector(){
			delete[] data_;
		}
	
	private:
		T* data_;
		size_t size_;
};
//mcdonald set of try & catch!
int main(){
	Vector<int> vec(3);
	
	int index, data=0;
	std::cin>>index;
	
	try{
		data=vec.at(index);
	} catch(std::out_of_range& e){//throw's object has to be same to this argument!
		std::cout<<"exception occur! "<<e.what()<<std::endl;
	}//if there's no exception, compiler passes this parts like that is not exist at first time.
	std::cout<<"read data : "<<data<<std::endl;//if there's not error, print 3. if there's error, print 0 that is in data.
	
	return 0;
}*/

/*5 김승호 상병님의 방구냄새는 언제나 독하다ㄷ 소리없는 암살자 긴장을 놓칠 수 없는 야간 연등시간. 2초이내로 kf-80이상의 마스크를 쓰지 않으면 모두가 죽을 것이다. 살아라!  
//correct example of object's destructor work 
class Resource{
	public:
		Resource(int id): id_(id){}
		~Resource(){
			std::cout<<"unset resource : "<<id_<<std::endl;
		}
		
	private:
		int id_;
};

int func3(){
	Resource r(3);
	throw std::runtime_error("Exception from 3!\n");//fuck up all process! doby will go to catch!! I'm free~~ worker of ROKA. shxt..
	//return 0;//if work well
}
int func2(){
	Resource r(2);
	func3();
	std::cout<<"not execute!"<<std::endl;
	//std::cout<<"execute!"<<std::endl;
	return 0;
}
int func1(){
	Resource r(1);
	func2();
	std::cout<<"not execute!"<<std::endl;
	//std::cout<<"execute!"<<std::endl;
	return 0;
}

int main(){
	try{
		func1();
	} catch(std::exception& e){
		std::cout<<"Exception : "<<e.what();
	}
	
	return 0;
}//if work well, print execute!
*/

//6
/*many exception handling.
int func(int c){
	if(c==1)
		throw 10;
	else if(c==2)
		throw std::string("hi!");
	else if(c==3)
		throw 'a';
	else if(c==4)
		throw "hello!";
	return 0;
} 

int main(){
	int c;
	std::cin>>c;
	
	try{//for catch many exception, just write catch sequentially! like switch. 
		func(c);
	} catch(char x){
		std::cout<<"Char : "<<x<<std::endl;
	} catch(int x){
		std::cout<<"Int : "<<x<<std::endl;
	} catch(std::string& s){
		std::cout<<"String : "<<s<<std::endl;
	} catch(const char* s){
		std::cout<<"String Literal : "<<s<<std::endl;
	}
	return 0;
}*/

/*exception handling in Parent & Child class
class Parent:public std::exception{
	public:
		virtual const char* what() const noexcept override {//override on std::exception's function! 
			return "Parent!\n";
		}
};
class Child: public Parent{
	public:
		const char* what() const noexcept override{
			return "Child!\n";
		}
};

int func(int c){
	if(c==1){
		throw Parent();//return object directly.
	} else if(c==2){
		throw Child();
	}
	return 0;
}

int main(){
	int c;
	std::cin>>c;
	
	try{
		func(c);
	} catch(Parent& p){//Even throw Child(), this catch execute because compiler find close catch and Child c can convert to Parent p.
		std::cout<<"Parent Catch!"<<std::endl;
		std::cout<<p.what();
	} catch(Child& c){//so it's better we write catch of child first than Parent class for correct catch execution.
		std::cout<<"Child Catch!"<<std::endl;
		std::cout<<c.what();
	}
	
	return 0;
}*/

//7
/*uncatched_different argument of catch
int func(){
	throw std::runtime_error("error");
} 
int main(){
	try{
		func();
	} catch(int i){//not std::runtime_error& e! no catch for std::runtime_error!
		std::cout<<"Catch int : "<<i;//error! uncommon end of program.
	}
	
	return 0;
}*/

/*default catch
int func(int c){
	if(c==1){
		throw 1;
	} else if(c==2){
		throw "hi";
	} else if(c==3){
		throw std::runtime_error("error");
	}
	return 0;
}
int main(){
	int c;
	std::cin>>c;
	
	try{
		func(c);
	} catch(int e){
		std::cout<<"Catch int : "<<e<<std::endl;
	} catch(...){//... as argument for default catch! get all exception in try.
		std::cout<<"Defaul Catch!"<<std::endl;
	}
	
	return 0;
}*/

//8
int foo() noexcept {}
int bar() noexcept{throw 1;}
int main(){
	foo();
	try{
		bar();
	} catch(int x){
		std::cout<<"Error : "<<x<<std::endl;
	}
	
	return 0;
} 



/*
[1.	예외란?]
1.	정상적인 상황에서 벗어난 모든 예외적인 상황들

[2.	기존의 예외 처리 방식]
1.	C에서는 예외 처리 방식이라는 것이 따로 존재하지 않고, 작업 실행 후 결과값을 확인하는 방식으로 처리하였다.  

[3.	예외 발생시키기-throw]
1.	C++에서는 throw문을 통해 예외가 발생하였다는 사실을 명시적으로 나타낼 수 있다. 
2.	C++에서는 예외를 던지고 싶다면, 예외로 전달하고 싶은 객체를 써주면 된다. 아무 객체나 던져도 상관없지만, C++표준 라이브러리에 이미 여러 예외들이 있어 활용해도 좋다.
	C++표준에는 out_of_range외에도 overflow_error, length_error, runtime_error 등등 여러가지가 정의되어 있고, 표준 라이브러리에서 활용되고 있다. 
	이렇게 throw를 하게 되면, 그 위치에서 함수는 즉시 종료되고, 예외처리 하는 부분까지 점프하게 된다. 즉, throw 밑에 있는 모든 문장은 실행되지 않는다.
	 놀라운 점은 이렇게 예외처리부까지 빠져나가면서 stack에 생성되었던 객체들을 빠짐없이 소명시켜 준다는 점이다. 즉, 소멸자만 제대로 작성하였다면 모든 자원들을 제대로 소멸시킬 수 있다.

[4.	예외 처리하기-try와 catch]
1.	out_of_range 클래스는 간단하게 문자열 필드 하나 있고 .what()으로 내용을 보는게 끝이다.

[5.	스택 풀기(stack unwinding)]
1.	앞서 throw를 하면, 가장 가까운 catch로 점프한다고 했는데, 그 말의 뜻을 예제로 알아보자.
2.	catch로 점프하면서 스택 상에서 정의된 객체들을 소멸시키는 과정을 스택 풀기(stack unwinding)이라고 부른다. 
3.	*주의사항*으로, 생성자에서는 에러발생시에 소멸자가 호출되지 않는다는 점이다(전부 패스해버리니)! 고로 생성자에서는 예외를 던지기 이전에 획득한 자원이 있다면 (exception이전에 모든 메모리를 해제해야한다)catch에서 잘 타일러주어야 한다.(해제) 

[6.	여러 종류의 예외 받기]
1.	catch 주렁주렁 스킬 발동!
2.	만약 기반 클래스와 파생 클래스의 경우는? 
3.	일반적으로 예외 객체는 std::exception을 상속받는 것이 좋다. 그래야 표준 라이브러리의 유용한 함수들(ensted_exception 등)을 사용할 수 있기 때문이다. 

[7.	모든 예외 받기]
1.	throw가 있는데 그 throw를 받는 특정한 catch가 없다면? 
2.	예외 객체 하나하나 catch할 필요없이 그냥 전부라고 말하고 싶다면? 
3.	템플릿으로 정의되는 클래스의 경우 인스턴스화에 따라서 던지는 예외의 종류가 다를 수 있다. 그렇기에 해당 객체의 catch에서는 모든 예외(객체)를 고려해야 한다. 

[8.	예외를 발생시키지 않는 함수-noexcept]
1.	noexcept를 붙였다고 함수가 절대로 예외를 던지지 않는 것은 아니다.
2.	컴파일러는 int bar(int x) noexcept {throw 1;}이어도 noexcept를 곧이곧대로 믿고 그대로 컴파일하게 된다(경고는 뜸).
	대신, noexcept로 명시된 함수가 예외를 발생시키게 된다면 예외가 제대로 처리되지 않고 그대로 종료된다.
3.	noexcept는 단지 프로그래머가 컴파일러에게 주는 힌트에 불과하다. 컴파일러가 어떤 함수가 절대로 예외를 발생시키지 않는 사실을 알게 된다면,
	자체적으로 여러가지 추가적인 최적화를 수행할 수 있기 때문이다. 
 
*/

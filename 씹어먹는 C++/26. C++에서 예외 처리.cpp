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

/*5 ���ȣ �󺴴��� �汸������ ������ ���ϴ٤� �Ҹ����� �ϻ��� ������ ��ĥ �� ���� �߰� ����ð�. 2���̳��� kf-80�̻��� ����ũ�� ���� ������ ��ΰ� ���� ���̴�. ��ƶ�!  
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
[1.	���ܶ�?]
1.	�������� ��Ȳ���� ��� ��� �������� ��Ȳ��

[2.	������ ���� ó�� ���]
1.	C������ ���� ó�� ����̶�� ���� ���� �������� �ʰ�, �۾� ���� �� ������� Ȯ���ϴ� ������� ó���Ͽ���.  

[3.	���� �߻���Ű��-throw]
1.	C++������ throw���� ���� ���ܰ� �߻��Ͽ��ٴ� ����� ��������� ��Ÿ�� �� �ִ�. 
2.	C++������ ���ܸ� ������ �ʹٸ�, ���ܷ� �����ϰ� ���� ��ü�� ���ָ� �ȴ�. �ƹ� ��ü�� ������ ���������, C++ǥ�� ���̺귯���� �̹� ���� ���ܵ��� �־� Ȱ���ص� ����.
	C++ǥ�ؿ��� out_of_range�ܿ��� overflow_error, length_error, runtime_error ��� ���������� ���ǵǾ� �ְ�, ǥ�� ���̺귯������ Ȱ��ǰ� �ִ�. 
	�̷��� throw�� �ϰ� �Ǹ�, �� ��ġ���� �Լ��� ��� ����ǰ�, ����ó�� �ϴ� �κб��� �����ϰ� �ȴ�. ��, throw �ؿ� �ִ� ��� ������ ������� �ʴ´�.
	 ���� ���� �̷��� ����ó���α��� ���������鼭 stack�� �����Ǿ��� ��ü���� �������� �Ҹ���� �شٴ� ���̴�. ��, �Ҹ��ڸ� ����� �ۼ��Ͽ��ٸ� ��� �ڿ����� ����� �Ҹ��ų �� �ִ�.

[4.	���� ó���ϱ�-try�� catch]
1.	out_of_range Ŭ������ �����ϰ� ���ڿ� �ʵ� �ϳ� �ְ� .what()���� ������ ���°� ���̴�.

[5.	���� Ǯ��(stack unwinding)]
1.	�ռ� throw�� �ϸ�, ���� ����� catch�� �����Ѵٰ� �ߴµ�, �� ���� ���� ������ �˾ƺ���.
2.	catch�� �����ϸ鼭 ���� �󿡼� ���ǵ� ��ü���� �Ҹ��Ű�� ������ ���� Ǯ��(stack unwinding)�̶�� �θ���. 
3.	*���ǻ���*����, �����ڿ����� �����߻��ÿ� �Ҹ��ڰ� ȣ����� �ʴ´ٴ� ���̴�(���� �н��ع�����)! ��� �����ڿ����� ���ܸ� ������ ������ ȹ���� �ڿ��� �ִٸ� (exception������ ��� �޸𸮸� �����ؾ��Ѵ�)catch���� �� Ÿ�Ϸ��־�� �Ѵ�.(����) 

[6.	���� ������ ���� �ޱ�]
1.	catch �ַ��ַ� ��ų �ߵ�!
2.	���� ��� Ŭ������ �Ļ� Ŭ������ ����? 
3.	�Ϲ������� ���� ��ü�� std::exception�� ��ӹ޴� ���� ����. �׷��� ǥ�� ���̺귯���� ������ �Լ���(ensted_exception ��)�� ����� �� �ֱ� �����̴�. 

[7.	��� ���� �ޱ�]
1.	throw�� �ִµ� �� throw�� �޴� Ư���� catch�� ���ٸ�? 
2.	���� ��ü �ϳ��ϳ� catch�� �ʿ���� �׳� ���ζ�� ���ϰ� �ʹٸ�? 
3.	���ø����� ���ǵǴ� Ŭ������ ��� �ν��Ͻ�ȭ�� ���� ������ ������ ������ �ٸ� �� �ִ�. �׷��⿡ �ش� ��ü�� catch������ ��� ����(��ü)�� ����ؾ� �Ѵ�. 

[8.	���ܸ� �߻���Ű�� �ʴ� �Լ�-noexcept]
1.	noexcept�� �ٿ��ٰ� �Լ��� ����� ���ܸ� ������ �ʴ� ���� �ƴϴ�.
2.	�����Ϸ��� int bar(int x) noexcept {throw 1;}�̾ noexcept�� ���̰��� �ϰ� �״�� �������ϰ� �ȴ�(���� ��).
	���, noexcept�� ��õ� �Լ��� ���ܸ� �߻���Ű�� �ȴٸ� ���ܰ� ����� ó������ �ʰ� �״�� ����ȴ�.
3.	noexcept�� ���� ���α׷��Ӱ� �����Ϸ����� �ִ� ��Ʈ�� �Ұ��ϴ�. �����Ϸ��� � �Լ��� ����� ���ܸ� �߻���Ű�� �ʴ� ����� �˰� �ȴٸ�,
	��ü������ �������� �߰����� ����ȭ�� ������ �� �ֱ� �����̴�. 
 
*/

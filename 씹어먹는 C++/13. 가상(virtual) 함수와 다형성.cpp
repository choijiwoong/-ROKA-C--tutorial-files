#include <iostream>
#include <string>

/*1
class Car{
	private:
		Engin e;//has -a relation
		Brake b;
		//....
}; 

class EmployeeList{
	int alloc_employee;//has -a relation
	int current_employee;
	Employee **employee_list;
};*/

/*2,3
class Base{
	std::string s;
	
	public:
		Base():s("기반") {  std::cout<<"기반 클래스"<<std::endl;  }//constructor with initializer list
		void what(){
			std::cout<<s<<std::endl;
		}  
};
class Derived:public Base{
	std::string s;
	
	public:
		Derived():s("파생"),Base(){
			std::cout<<"파생 클래스"<<std::endl;
		}
		void what(){
			std::cout<<s<<std::endl;
		}
};
int main(){
	/*normal main
	std::cout<<" ===기반 클래스 생성 ==="<<std::endl;
	Base p;
	p.what();
	std::cout<<" === 파생 클래스 생성 === "<<std::endl;
	Derived c;
	c.what();*/
	
	/*up casting main
	Base p;
	Derived c;
	
	std::cout<<"===포인터 버전==="<<std::endl;
	Base p_c=&c;//assign Derived to Base!!!
	p_c->what();*/
	
	/*try down casting main 
	Base p;
	Derived c;
	
	std::cout<<"===포인터 버전==="<<std::endl;
	Derived* p_p=&p;//assign Base to Derived->Error occur!!!
	p_p->what();;*/
	
	/*down casting of Base class that points Derived class actually.
	Base p;
	Derived c;
	
	std::cout<<"===포인터 버전==="<<std::endl;
	Base* p_p=&c;
	
	//Derived* p_c=p_p;//p_p actually points Derived, but p_p's type is Base so it occur error too. but it's logical to work. so for doing it, we will cast forcely.
	Derived* p_c=static_cast<Derived*>(p_p);//thanks to p_p is pointing Derived actually.
	p_c->what();*/
	
	/*down casting that is not the same way with upper case.
	Base p;
	Derived c;
	
	std::cout<<"===포인터 버전==="<<std::endl;
	Base* p_p=&p;
	
	Derived* p_c=static_cast<Derived*>(p_p);
	p_c->what();//runtime error occur.*//*
	
	//dynamic casting
	Base p;
	Derived c;
	
	std::cout<<"===포인터 버전==="<<std::endl;
	Base* p_p=&p;
	
	Derived* p_c=dynamic_cast<Derived*>(p_p);//error occur. for find error easily.....just? no special function...?TT
	p_c->what();
	
	
	
	return 0;
}*/

/*4
class EmployeeList{
	int alloc_employee;
	
	int current_employee;
	int current_manager;
	
	Employee **employee_list;
	Manager **manager_list;
	//problem of this structure is we have to save data seperately by each class. then, if we have to add class, it's so complex to fix.
	//but we know upcasting is free. So, Employee* can point Manager object. so just remove manager_list, Can it be solved by make employee_list point both?
	//then, another problem is occur.
	public:
		void print_employee_info(){
			int total_pay=0;
			for(int i=0;i<current_employee;i++){
				employee_list[i]->print_info();//it must call Employee class's print_info not Manager class's print_info. because employee_list[i] is pointer that points Employee object.
				total_pay+=employee_list[i]->calculate_pay();//this problem will occur at calculae_pay() too.
			}
			//...
		}
	//so pointing Manager and Employee at Employee* is not suitable.
	//In addition, calculate_pay() function will always work as Employee's calculate_pay() regardless of Manager.
	//So sum of pay is calculated lower value than real value. because every manager is calculated by normal employee.
};*/

/*5
class Base {

 public:
  Base() { std::cout << "기반 클래스" << std::endl; }

  virtual void what() { std::cout << "기반 클래스의 what()" << std::endl; }//because of this!
};
class Derived : public Base {

 public:
  Derived() : Base() { std::cout << "파생 클래스" << std::endl; }

  void what() { std::cout << "파생 클래스의 what()" << std::endl; }
};
int main() {
  Base p;
  Derived c;

  Base* p_c = &c;//up casting
  Base* p_p = &p;

  std::cout << " == 실제 객체는 Base == " << std::endl;
  p_p->what();

  std::cout << " == 실제 객체는 Derived == " << std::endl;
  p_c->what();//ddyong! true value print! not Base's what! because of^
  //in upper code, compiler's interpret
  //1. Let's do Base's what() because p_c is Base pointer!
  //2. Wait, Base's what is virtual!
  //3. Let's check is it real Base object! no! It's Derived object!
  //4. Let's do Derived what!
  //Mechanism is same when p_p->what().

  return 0;
}*/

class Base {
  std::string s;

 public:
  Base() : s("기반") { std::cout << "기반 클래스" << std::endl; }

  virtual void incorrect() { std::cout << "기반 클래스 " << std::endl; }
};
class Derived : public Base {
  std::string s;

 public:
  Derived() : Base(), s("파생") {}

  void incorrect() override { std::cout << "파생 클래스 " << std::endl; }//explicit override expression of Base class's virtual function. to privent this situation.
};//actually it's different to Base's incorrect(). so add override keyword and delete const keyword
int main() {
  Base p;
  Derived c;

  Base* p_c = &c;
  Base* p_p = &p;

  std::cout << " == 실제 객체는 Base == " << std::endl;
  p_p->incorrect();

  std::cout << " == 실제 객체는 Derived == " << std::endl;
  p_c->incorrect();
  return 0;
}
  
  


/*
[1.	is '-a'와 'has -s']
1.	C++에서는 단순히 Ctrl+C, Ctrl+V를 방지하기 위해 상속을 만든것이 아니다. 기존의 C에서는 구조체 사이의 관계를 나타낸 방법이 없었지만, 
	상속의 개념을 도입하며, 클래스 사이의 관계를 표현함으로써, 객체지향프로그래밍에서 추구하는 실제 객체의 추상화를 좀 더 효과적으로 할 수 있게 되었다.
2.	class Manager:public Employee의 의미는 
	-Manager class는 Employee의 모든 기능을 포함한다.
	-Manager class는 Employee의 기능을 모두 수행할 수 있기 때문에 Manager를 Employee라고 칭해도 무방하다.
	-즉, 모든 Manager는 Employee이다.
	-Manager is a Employee!
	따라서, 모든 상속 관계는 is a의 관계이다. 당연하게도 이를 뒤바꾸면 성립되지 않는다. Manager는 Employee이지만, Employee는 Manager가 아니다.
	 프로그램 설계 시에 클래스 간의 상속 관계를 도표로 나타내는 경우가 종종 있는데, 많은 경우 파생 클래스가 기반 클래스를 화살표로 가리키게 그린다. Manager->Employee
	Ex)A programmer is a human, CheckingAccount and SavingAccount are BankAccount.
	 위와같은 예시에서 알 수 있는 상속의 중요한 특징은, 클래스가 파생될 수록 좀 더 특수화(구체화:specialize)된다는 의미이다. 즉, Employee클래스가 일반적인 사원을 위한 클래스 였다면, Manager클래스 들은
	일반적인 사원들 중에서도 좀 더 특수한 부류의 사원들을 의미하게 된다. 또한 BankAccount도 일반적인 은행 계좌를 위한 클래스 였다면, 이를 상속받는 CheckingAccount, SavingAccount들을 좀 더 구체적인 클래스가 된다.
	반대로 기반클래스로 거슬러 올라가면 올라갈 수록 점점 일반화(generalize)된다고 한다. 
3.	하지만 모든 클래스의 관계를 is-a로만 표현할 수 없다. ex) 자동차 클래스를 구성하는데 사용되는 엔진 클래스, 브레이크 클래스, 오디오 클래스...이들이 자동차 is 엔진, 자동차 is 브레이크는 아니기 때문에 has-a관계로 표현한다.
	 즉, 자동차는 엔진을 가진다(자동차 has a 엔진), 자동차는 브레이크를 가진다(자동차 has a 브레이크). 
	 
[2. (다시보는) 오버라이딩]
1.	Derived를 Base로 대입해도 되는데, Derived가 Base를 상속받고 있기 때문이다. 즉, Derived is a Base. Derived에 해당하는 부분에 대한 정보만 가지는 Base객체가 만들어진다.
	 이렇게 파생클래스에서 기반클래스로 캐스팅 하는 것을 업캐스팅(Up casting)이라고 한다. 
	그렇다면 다운캐스팅은? 만약 Derived* pointer가 Base object를 가리킨다면, p_p->what()에서 Derived의 what()을 call해야 하는데, p_p가 가리키는 객체는 Base객체이므로 Derived에 대한 정보가 없어 불가능하다.
	고로 컴파일러상에서 함부로 다운 캐스팅 하는 것을 금지하고 있다. 
2.	강제적으로 다움캐스팅을 하는 경우, 컴ㄴ파일 타임에서 오류를 찾아내기 매우 힘들기 때문에 작동이 보장되지 않는 한 매우매우 권장하지 않는 방법이다. 

[3. dynamic_cast]
1.	위와 같은 캐스팅의 오류를 미연에 방지하기 위하며, C++에서는 상속 관계에 있는 두 포인터들 간에 캐스팅을 해주는 dynamic_cast라는 것을 지원한다.
	사용법은 static_cast와 같다. 
	
[4. EmployeeList다시 보기]
1.	Employee **employee_list에 Manager, employee를 몽땅 넣어버리자 by 업 캐스팅.->문제 발생. calculate를 Employee함수로 쓴다. 

[5. virtual 키워드]	
1.	EmployeeList 문제를 해결하기 이전에 간단한 예시로 살펴보자. 
2.	virtual 키워드로 인하여 컴파일러가 실제 객체인지 확인을 한다. 이처럼 컴파일 시에 어떤 함수가 실행될 지 정해지지 않고, 런터임 시에 정해지는 것을 동적 바인딩(dynamic binding)이라고 한다.
3.	동적 바인딩의 반대말로 정적 바인딩(static binding)이라는 말도 있지만, 이는 컴파일 타임에 어떤 함수가 호출될 지 정해지는 것으로 지금까지 사용해온 함수에 해당한다.
4.	virtual키워드가 붙은 함수를 가상 함수(virtual function)이라고 한다.
5.	파생 클래스의 함수가 기반 클래스의 함수를 오버라이드(override)하기 위해서는 두 함수의 꼴이 정확히 같아야 한다!

[6.	override 키워드]
1.	override 키워드를 사용하여 명시적으로 오버리아드를 알려주게되면, 실수로 오버라이드를 하지 않는 경우를 막을 수 있다. 

[7. 그렇다면 Employee 문제를 어떻게 해결할까]
1.	단순히 Employee 클래스의 calculate_pay함수와 print_info함수 앞에 virtual을 붙여서 컴파일러가 실제로 가리키는 형식이 어떤건지를 확인하게 하여 Employee와 Manager를 구분하게 한다. 
2.	수정한 코드에서 이 부분을 보면, 
    for (int i = 0; i < current_employee; i++) {
      employee_list[i]->print_info();//이 부분은 employee_list가 manager나 employee냐에 따라서 다르게 동작하게 된다. 
      total_pay += employee_list[i]->calculate_pay();
    }
	 즉, 같은 print_info함수를 호출했음에도 불구하고 경우에 따라 다른 것이 호출되는 일;
	정리해서! 하나의 메소드를 호출했음에도 불구하고 여러가지 다른 작업들을 하는 것을 바로 다형성(polumorphism)이라고 부른다. 

[8. 생각해보기]
1.	virtual키워드의 처리과점. 이 포인터가 어떻게 객체를 가리키는지 어떻게 알 수 있을까 
*/


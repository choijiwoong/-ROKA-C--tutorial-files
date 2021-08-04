#include <iostream>
#include <string>
//what 함수는 Base 에 정의가 되어 있기 때문에 Derived 의 s 가 아니라 Base 의 s 가 출력되어 "기반" 라고 나오게 되는 것입니다.
/*1
int main(){
	//because of standard, it's defined in std._std::string(but it isn't only std::string depending on which library we use)
	std::string s="abc";
	std::cout<<s<<std::endl;//"abc" is recognized as string in C in compiler. so it's means calls constructor that has argument 'const char *' in std::string clss.
	
	std::string t="def";//new string variable
	std::string s2=s;//asssign s in s2
	
	std::cout<<s<<"의 길이: "<<s.length()<<std::endl;
	std::cout<<s<<" 뒤에 "<<t<<"를 붙이면 : "<<s+t<<std::endl;
	
	if(s==s2)//condition operator to std::string. it will be expressed as strcmp in C lang. because in C, it's comparing pointer.
		std::cout<<s<<" 와 "<<s2<<" 는 같다. "<<std::endl;//but std::string, == and != can be operated by overloading of operator function.
	if(s!=t)//std::string has not only length(), but also insert(), erase(), replace()...etc, many useful function is exist.
		std::cout<<s<<" 와 "<<t<<"는 다르다 "<<std::endl;
	
	return 0;
} */

/*2
class Employee{
	std::string name;//name ex) Jimo
	int age;//age ex) 17
	std::string position;//opsition name ex) director
	int rank;//high value == high position ex)5
	
	public:
		Employee(std::string name, int age, std::string position, int rank)
			:name(name), age(age), position(position), rank(rank){}//Constructor with initializer list
		Employee(const Employee& employee){//Copy Constructor
			name=employee.name;
			age=employee.age;
			position=employee.position;
			rank=employee.rank;
		}
		Employee(){}//default constructor
		
		void print_info(){  std::cout<<name<<" ("<<position<<" , "<<age<<") ==> "<<calculate_pay()<<"만원"<<std::endl;  }
		int calculate_pay(){  return 200+rank*50;  }
};

class Manager{
	std::string name;
	int age;
	std::string position;
	int rank;
	int year_of_service;
	
	public:
		Manager(std::string name, int age, std::string position, int rank, int year_of_service)
			:year_of_service(year_of_service), name(name), age(age), position(position), rank(rank) {}
		Manager(const Manager& manager){
			name=manager.name;
			age=manager.age;
			position=manager.position;
			rank=manager.rank;
			year_of_service=manager.year_of_service;
		}
		Manager(){}
		int calculate_pay() { return 200+rank*50+5*year_of_service; }
		void print_info(){
			std::cout << name << " (" << position << " , " << age << ", "<< year_of_service 
			<< "년차) ==> " << calculate_pay() << "만원"<< std::endl;
		}
};

class EmployeeList{
	int alloc_employee;//allocated staff number
	int current_employee;//now staff number
	 int current_manager;//now manager number
	Employee** employee_list;//staff data for Employee* list
	 Manager **manager_list;//manager data for manager* list
	
	public:
		EmployeeList(int alloc_employee):alloc_employee(alloc_employee){//constructor with alloc_employee for allocation.
			employee_list=new Employee*[alloc_employee];//Employee* list allocation. 
			 manager_list=new Manager*[alloc_employee];
			current_employee=0;//set default value to 0
			 current_manager=0;
		}
		
		void add_employee(Employee* employee){//add employee to employee_list.
			//current_employee++;//first, current employee++ for judgement of whether we need more allocation for adding.
			//if(alloc_employee<current_employee){//have we to allocate?
			//	Employee** buffer=employee_list;//data save
			//	delete[] employee_list;//delete employee_list for reallocation
				
			//	employee_list=new Employee*[current_employee];//reallocation
			//	employee_list=buffer;//backup data to copy constructor
				
			//	delete[] buffer;//delete buffer
			//	alloc_employee++;//after allocation, add alloc_employee
				
			//	employee_list[current_employee]=employee;//new data save in new space
			//}//***error*** because of there are no copy constructor at Employee** employee_list. it can solve by making copy constructor of EmployeeList and use .employee_list or making another class for Employee**. later,,check logical mechanism of upper code..
			employee_list[current_employee]=employee;//suppose alloc_employee>current_employee always
			current_employee++;
		}
		 void add_manager(Manager* manager){
			 manager_list[current_manager]=manager;
			 current_manager++;
		 }
		int current_employee_num() { return current_employee+ current_manager; }//int type return of current_employee member variable.
		
		void print_employee_info(){//all information of employee
			int total_pay=0;
			for(int i=0; i<current_employee;i++){//each info print and calculate total pay.
				employee_list[i]->print_info();//access by -> because it's Employee*.
				total_pay+=employee_list[i]->calculate_pay();//jonna convenient...
			}
			 for (int i = 0; i < current_manager; i++) {
     			 manager_list[i]->print_info();
      			 total_pay += manager_list[i]->calculate_pay();
    		 }
			std::cout<<"총 비용: "<<total_pay<<"만원 "<<std::endl;//print total pay
		}
		~EmployeeList(){//Destructor
			for(int i=0;i<current_employee;i++)//current_employee. not alloc_employee because it's erasing of each data.(Employee*)
				delete employee_list[i];//each employee data delete
			 for(int i=0;i<current_manager;i++)
				 delete manager_list[i];
			delete[] employee_list;//database delete
			 delete[] manager_list;
		}
};

int main() {
  EmployeeList emp_list(10);
  emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
  emp_list.add_employee(new Employee("하하", 34, "평사원", 1));

  emp_list.add_manager(new Manager("유재석", 41, "부장", 7, 12));
  emp_list.add_manager(new Manager("정준하", 43, "과장", 4, 15));
  emp_list.add_manager(new Manager("박명수", 43, "차장", 5, 13));
  emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
  emp_list.add_employee(new Employee("길", 36, "인턴", -2));
  emp_list.print_employee_info();
  return 0;
}*/

class Base{//base class
	std::string s;
	
	public:
		Base():s("기반"){  std::cout<<"기반 클래스"<<std::endl;  }//Constructor with initializer list. print message when constructor activate.
		void what() {  std::cout<<s<<std::endl;  }//print s function in Base
}; 
//derived class
class Derived:public Base{//derive will be inherited with Base by public type
	std::string s;
	
	public:
		Derived():Base(), s("파생"){//constructor. by Base(), it call Base()'s constructor and set initialize Derived's s.
			std::cout<<"파생 클래스"<<std::endl;//if we don't define constructor, compiler call default constructor.
			what();//there are no what() function in Derive so it call Base's what()function.
		}
};

int main() {
   std::cout << " === 기반 클래스 생성 ===" <<  std::endl;
  Base p;//Base's Constructor

   std::cout << " === 파생 클래스 생성 ===" <<  std::endl;
  Derived c;//Base's Constructor in Derived's Constructor and call what() in Base class

  return 0;
}

/*
[1.	표준 'string'클래스]
1.	C언어의 문자열을 문자열의 길이를 한번에 알 수 없고, NULL문자까지 읽어야 한다든지 많은 불편함이 있었기에, 지난시간에 MyString클래스를 만들어서 그러한 문제들을 해결해 보았다.
	하지만, 속도가 매우 중요한 환경에서 그대로 쓰기에는 부족한 점이 많기에, C++에서는 string이라는 빠르고 안전하고 사용하기 매우 간편한 문자열 클래스를 표준으로 사용하고 있다.
	 몇가지 기술의 예시로는, 짧은 문자열의 경우 동적할당이 아닌 지역변수로 보관을 하고, 복사할때는 문자열의 내용이 바뀌지 않는 한 원래 문자열을 가리키기만 하는 등 속도를 향상시키기 위한 많은 기술이 접목되어있다.

[2.	사원 관리 프로그램]
1.	목적은 회사의 사원들의 월급을 계산해서 한달에 총 얼마나 되는 돈을 월급으로 지출해야 하는지 알려주는 프로그램이다. 
2.	Employee클래스를 단순한 배열로써 관리할 수도 있지만, EmployeeList클래스를 만들어서 간단하게 처리해보자. 
3.	사원관리 프로그램을 잘 만들어서 제출해달라는 찰나, 무한 상사로 부터 차장 이상 급들은 관리데이커에 근속 년수를 포함시켜서 월급에 추가해달라고 말한다. 그리하여 Manager클래스를 추가한다. 짜증나게도 EmployeeList에서도 달리 처리해야한다. 

[3. 상속(Inheritance)]_...드디어 
1.	Manager의 코드 자체가 Employee의 대부분을 포함하고 있는데, C++에서는 다른 클래스의 내용을 그대로 포함할 수 있게하는 작업을 가능케 하는데 이를 상속이라고 한다.
2.	C++ 상속이 어떻게 사용될까? 
*/

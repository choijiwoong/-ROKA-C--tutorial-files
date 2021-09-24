#include <iostream>
#include <string>

class Employee{
	protected:
		std::string name;
		int age;
		
		std::string position;//CEO, CTO like etc..
		int rank;
		
	public:
		Employee(std::string name, int age, std::string position, int rank): name(name), age(age), position(position), rank(rank){}
		Employee(const Employee& employee){//cannot use initializer list!
			name=employee.name;
			age=employee.age;
			position=employee.position;
			rank=employee.rank;
		}
		Employee()=default;
		
		void print_info(){ std::cout<<name<<" ("<<position<<" , "<<age<<") ==> "<<calculate_pay()<<" $"<<std::endl; }
		int calculate_pay(){ return 200+rank*50; }
};

class Manager: public Employee{//inheritance as public
	int year_of_service;
	
	public:
		Manager(std::string name, int age, std::string position, int rank, int year_of_service): Employee(name, age, position, rank), year_of_service(year_of_service){}//call Base constructor and set year_of_service
		Manager(const Manager& manager): Employee(manager.name, manager.age, manager.position, manager.rank){
			year_of_service=manager.year_of_service;
		}
		//Manager()=default;//NO! we have to call constructor of Based class
		Manager(): Employee(){}
		
		int calculate_pay(){ return 200+rank*50+5*year_of_service; }
		void print_info(){ std::cout<<name<<" ("<<position<<" , "<<age<<", "<<year_of_service<<"years)==> "<<calculate_pay()<<"$"<<std::endl; }
};

class EmployeeList{
	int alloc_employee;
	
	int current_employee;
	int current_manager;
	
	Employee** employee_list;
	Manager** manager_list;
	
	public:
		EmployeeList(int alloc_employee): alloc_employee(alloc_employee){
			employee_list=new Employee*[alloc_employee];//allocation
			manager_list=new Manager*[alloc_employee];
			
			current_employee=0;
			current_manager=0;
		}
		void add_employee(Employee* employee){//get argument by pointer(*) because we will add employee like add_employee(new Manager(~)). no reference
			employee_list[current_employee]=employee;
			current_employee++;
		}
		void add_manager(Manager* manager){
			manager_list[current_manager]=manager;
			current_manager++;
		}
		int current_employee_num(){ return current_employee+current_manager; }
		
		void print_employee_info(){
			int total_pay=0;
			for(int i=0; i<current_employee; i++){//employee print and + pay
				employee_list[i]->print_info();
				total_pay+=employee_list[i]->calculate_pay();
			}
			for(int i=0; i<current_manager; i++){
				manager_list[i]->print_info();
				total_pay+=manager_list[i]->calculate_pay();
			}
			std::cout<<"total cost: "<<total_pay<<"$"<<std::endl;
		}
		
		~EmployeeList(){
			for(int i=0; i<current_employee; i++)
				delete employee_list[i];
			for(int i=0; i<current_manager; i++)
				delete manager_list[i];
				
			delete[] employee_list;
			delete[] manager_list;
		}
};

int main(){
	EmployeeList emp_list(10);
	
	emp_list.add_manager(new Manager("john calson", 24, "CEO", 1,1));
	emp_list.add_manager(new Manager("isac kerson", 32, "CTO", 2,4));
	emp_list.add_manager(new Manager("johnson", 22, "CMO", 3, 3));
	emp_list.add_employee(new Employee("choi ji", 24, "Tech", 1));
	emp_list.add_employee(new Employee("troll", 1, "ss", -10));
	
	emp_list.print_employee_info();
	
	return 0;
}


/*
1.	Derived생성자는 초기화자리스트에서 Based 생성자를 호출하여 먼저 처리한 다음, 생성을 시키자. 만약 Based 생성자를 명식적으로 호출하지 않을 경우 기반 클래스의 default생성자가 호출된다.
2.	Derived에 what함수가 이미 정의되어 있다면, 솔직히 다른 클래스에 정의된 다른 함수기에 굳이 Based클래스를 보지 않고 Derived클래스의 what함수를 호출한다. 이를 오버라이딩(overrriding)이라고 한다. 
3.	Derived클래스에서 Base클래스의 private를 수정하고자 할때, protected를 사용한다. 
4.	또한 상속할때, class Derived : public Base{의 키워드는 최대 오픈도?를 의미한다. public이면 모든 status가 유지되고, protected면 public이 protected키워드로 바뀐다. 
	약간 여기까지만 허용할게!느낌
protected, overrride, Derived constructor 
*/

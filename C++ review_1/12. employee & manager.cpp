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
1.	Derived�����ڴ� �ʱ�ȭ�ڸ���Ʈ���� Based �����ڸ� ȣ���Ͽ� ���� ó���� ����, ������ ��Ű��. ���� Based �����ڸ� ��������� ȣ������ ���� ��� ��� Ŭ������ default�����ڰ� ȣ��ȴ�.
2.	Derived�� what�Լ��� �̹� ���ǵǾ� �ִٸ�, ������ �ٸ� Ŭ������ ���ǵ� �ٸ� �Լ��⿡ ���� BasedŬ������ ���� �ʰ� DerivedŬ������ what�Լ��� ȣ���Ѵ�. �̸� �������̵�(overrriding)�̶�� �Ѵ�. 
3.	DerivedŬ�������� BaseŬ������ private�� �����ϰ��� �Ҷ�, protected�� ����Ѵ�. 
4.	���� ����Ҷ�, class Derived : public Base{�� Ű����� �ִ� ���µ�?�� �ǹ��Ѵ�. public�̸� ��� status�� �����ǰ�, protected�� public�� protectedŰ����� �ٲ��. 
	�ణ ��������� ����Ұ�!����
protected, overrride, Derived constructor 
*/

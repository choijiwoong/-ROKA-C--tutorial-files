#include <iostream>
#include <string>

class Employee{
	protected:
		std::string name;
		int age;
		
		std::string position;
		int rank;
		
	public:
		Employee(std::string name, int age, std::string position, int rank):name(name), age(age), position(position), rank(rank){}
		Employee(const Employee& employee): name(employee.name), age(employee.age), position(employee.position), rank(employee.rank){}
		Employee() {}
		//virtual! Let compiler check when this function is worked.
		virtual void print_info(){ std::cout<<name<<" ("<<position<<" , "<<age<<") ==> "<<calculate_pay()<<"$"<<std::endl; }
		virtual int calculate_pay(){ return 200+ rank*50; }
};

class Manager: public Employee{
	private:
		int year_of_service;
	
	public:
		Manager(std::string name, int age, std::string position, int rank, int year_of_service):year_of_service(year_of_service), Employee(name, age, position, rank){}
		//override! Let compiler use this rather than Employee.function.
		int calculate_pay() override{ return 200+ rank*50+ 5*year_of_service; }
		void print_info() override{ std::cout<<name<<" ("<<position<<" , "<<age<<", "<<year_of_service<<"years)==> "<<calculate_pay()<<"$"<<std::endl; }
};

class EmployeeList{
	private:
		int alloc_employee;
		int current_employee;
		Employee** employee_list;//save Manager too. pointer is container of object. real object is Manager or Employee class.
	
	public:
		EmployeeList(int alloc_employee): alloc_employee(alloc_employee){
			employee_list=new Employee*[alloc_employee];
			current_employee=0;
		}
		void add_employee(Employee* employee){
			//alloc>current
			employee_list[current_employee]=employee;
			current_employee++;
		}
		int current_employee_num(){ return current_employee; }
		void print_employee_info(){
			int total_pay=0;
			for(int i=0; i<current_employee; i++){
				employee_list[i]->print_info();
				total_pay+=employee_list[i]->calculate_pay();
			}
			std::cout<<"total cost: "<<total_pay<<"$ "<<std::endl;
		}
		~EmployeeList(){
			for(int i=0; i<current_employee; i++)
				delete employee_list[i];
			delete[] employee_list;
		}
};

int main(){
	EmployeeList emp_list(10);
	
	emp_list.add_employee(new Manager("john calson", 24, "CEO", 1,1));
	emp_list.add_employee(new Manager("isac kerson", 32, "CTO", 2,4));
	emp_list.add_employee(new Manager("johnson", 22, "CMO", 3, 3));
	emp_list.add_employee(new Employee("choi ji", 24, "Tech", 1));
	emp_list.add_employee(new Employee("troll", 1, "ss", -10));
	
	emp_list.print_employee_info();
	
	return 0;
}

/*
1.	is-a(inheritance relation. Manager is as Employee. Employee<-Manager), has-a ����(Manager.year)
2.	�Ļ��ɼ��� Ư��ȭ(��üȭ; specialize)�ǰ�, �ö󰥼��� �Ϲ�ȭ(generalize)�ȴ�. 
3.	���ɽ���, �ٿ�ĳ����(����)�� ������ ���� ���� �����Ϸ��󿡼� �����Ǳ⿡, �ƿ� C++���� ��Ӱ����� �� �����͸� ĳ�����ϴ� dynamic_cast�� ó���Ѵ�.
4.	virtualŰ���带 ����Ͽ� ���� ��ü�� ����Ű�� �ִ� ���� �´��� Ȯ���� �� �ִµ�, �̷��� ���� ��, ������ �ÿ� � �Լ��� ����� �� �������� �ʰ� ��Ÿ�� �ÿ� �������� ���� ���� ���ε�(dynamic binding)�̶�� �Ѵ�. �̿� �ݴ�Ǵ� �Ϲ����� �Լ� �� ���� ���ε��̶�� �Ѵ�. 
	�Ļ� Ŭ������ �Լ��� ��� Ŭ������ �Լ��� �������̵� �ϱ� ���ؼ��� �� �Լ��� ���� ��Ȯ�� ���ƾ� �Ѵ�. 
5.	overrideŰ����� �Ļ� Ŭ������ �Լ��� ������ ��� Ŭ���� �Լ����� �켱�ǰ� �� �� �ִ�.
6.	�ϳ��� �޼ҵ带 ȣ���������� �ұ��ϰ� ���� ���� �۾����� �ϴ� ���� �ٷ� ������(polymorphism)���ϰ� �Ѵ�. 

is-a, upcasting, virtual, override, polymorphism
*/

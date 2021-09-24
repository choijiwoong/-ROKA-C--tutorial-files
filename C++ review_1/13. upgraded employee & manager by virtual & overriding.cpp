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
1.	is-a(inheritance relation. Manager is as Employee. Employee<-Manager), has-a 관계(Manager.year)
2.	파생될수록 특수화(구체화; specialize)되고, 올라갈수록 일반화(generalize)된다. 
3.	업케스팅, 다운캐스팅(위험)은 오류가 존나 많아 컴파일러상에서 금지되기에, 아예 C++에서 상속관게의 두 포인터를 캐스팅하는 dynamic_cast로 처리한다.
4.	virtual키워드를 사용하여 실제 객체를 가리키고 있는 것이 맞는지 확인할 수 있는데, 이러한 행위 즉, 컴파일 시에 어떤 함수가 실행될 지 정해지지 않고 런타임 시에 정해지는 일을 동적 바인딩(dynamic binding)이라고 한다. 이에 반대되는 일반적인 함수 즉 정적 바인딩이라고 한다. 
	파생 클래스의 함수가 기반 클래스의 함수를 오버라이드 하기 위해서는 두 함수의 꼴이 정확히 같아야 한다. 
5.	override키워드로 파생 클래스의 함수가 무조건 기반 클래스 함수보다 우선되게 할 수 있다.
6.	하나의 메소드를 호출했음에도 불구하고 여러 가지 작업들을 하는 것을 바로 다형성(polymorphism)이하고 한다. 

is-a, upcasting, virtual, override, polymorphism
*/

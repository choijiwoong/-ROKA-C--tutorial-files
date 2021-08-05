#include <iostream>
#include <string>

/*1
int main(){
	//because of standard, it's defined in std._std::string(but it isn't only std::string depending on which library we use)
	std::string s="abc";
	std::cout<<s<<std::endl;//"abc" is recognized as string in C in compiler. so it's means calls constructor that has argument 'const char *' in std::string clss.
	
	std::string t="def";//new string variable
	std::string s2=s;//asssign s in s2
	
	std::cout<<s<<"�� ����: "<<s.length()<<std::endl;
	std::cout<<s<<" �ڿ� "<<t<<"�� ���̸� : "<<s+t<<std::endl;
	
	if(s==s2)//condition operator to std::string. it will be expressed as strcmp in C lang. because in C, it's comparing pointer.
		std::cout<<s<<" �� "<<s2<<" �� ����. "<<std::endl;//but std::string, == and != can be operated by overloading of operator function.
	if(s!=t)//std::string has not only length(), but also insert(), erase(), replace()...etc, many useful function is exist.
		std::cout<<s<<" �� "<<t<<"�� �ٸ��� "<<std::endl;
	
	return 0;
} */

//*2
class Employee{
	protected://public in derived.
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
		
		void print_info(){  std::cout<<name<<" ("<<position<<" , "<<age<<") ==> "<<calculate_pay()<<"����"<<std::endl;  }
		int calculate_pay(){  return 200+rank*50;  }
};

/*class Manager{
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
			<< "����) ==> " << calculate_pay() << "����"<< std::endl;
		}
};*/
class Manager:public Employee{
	int year_of_service;
	
	public:
		Manager(std::string name, int age, std::string position, int rank, int year_of_service)//constructor with input as argument
			:year_of_service(year_of_service), Employee(name, age, position, rank){}//and call Constructor of parent class with input argument
		
		Manager(const Manager& manager)//copy constructor
			:Employee(manager.name, manager.age, manager.position, manager.rank){//it's function of inserting values at variables.
		  year_of_service=manager.year_of_service;
		}
		
		Manager():Employee(){}//default constructor
		
		int calculate_pay(){  return 200+rank*50+5*year_of_service;  }
		void print_info(){
			std::cout<<name<<" ("<<position<<" , "<<age<<", "<<year_of_service<<"����) ==> "<<calculate_pay()<<"����"<<std::endl;
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
			std::cout<<"�� ���: "<<total_pay<<"���� "<<std::endl;//print total pay
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
  emp_list.add_employee(new Employee("��ȫö", 34, "����", 1));
  emp_list.add_employee(new Employee("����", 34, "����", 1));

  emp_list.add_manager(new Manager("���缮", 41, "����", 7, 12));
  emp_list.add_manager(new Manager("������", 43, "����", 4, 15));
  emp_list.add_manager(new Manager("�ڸ��", 43, "����", 5, 13));
  emp_list.add_employee(new Employee("������", 36, "�븮", 2));
  emp_list.add_employee(new Employee("��", 36, "����", -2));
  emp_list.print_employee_info();
  return 0;
}//*/

/*3,4
class Base{//base class
	public:
		std::string parent_string;
	
	public:
		Base():parent_string("���"){  std::cout<<"��� Ŭ����"<<std::endl;  }//Constructor with initializer list. print message when constructor activate.
		void what() {  std::cout<<parent_string<<std::endl;  }//print s function in Base
}; 
//derived class
class Derived:private Base{//derive will be inherited with Base by public type
	std::string child_string;
	
	public:
		Derived():Base(), child_string("�Ļ�"){//constructor. by Base(), it call Base()'s constructor and set initialize Derived's s.
			std::cout<<"�Ļ� Ŭ����"<<std::endl;//if we don't define constructor, compiler call default constructor.
			what();//there are no what() function in Derive so it call Base's what()function.
			
			//if can we access parent_string in Base with private?
			parent_string="�ٲٱ�";//error occur. so change Base's private to protected.->error solved.
		}
		void what(){  std::cout<<child_string<<std::endl;  }//if make what() in Derived too?
};

int main() {
   std::cout << " === ��� Ŭ���� ���� ===" <<  std::endl;
  Base p;//Base's Constructor
	std::cout << p.parent_string << std::endl;//of course, parent_string can be access because of public.
	
   std::cout << " === �Ļ� Ŭ���� ���� ===" <<  std::endl;
  Derived c;//Base's Constructor in Derived's Constructor and call what() in Base class
   std::cout << c.parent_string << std::endl;//error occur because inheritance type is private.

  return 0;
}*/

/*
[1.	ǥ�� 'string'Ŭ����]
1.	C����� ���ڿ��� ���ڿ��� ���̸� �ѹ��� �� �� ����, NULL���ڱ��� �о�� �Ѵٵ��� ���� �������� �־��⿡, �����ð��� MyStringŬ������ ���� �׷��� �������� �ذ��� ���Ҵ�.
	������, �ӵ��� �ſ� �߿��� ȯ�濡�� �״�� ���⿡�� ������ ���� ���⿡, C++������ string�̶�� ������ �����ϰ� ����ϱ� �ſ� ������ ���ڿ� Ŭ������ ǥ������ ����ϰ� �ִ�.
	 ��� ����� ���÷δ�, ª�� ���ڿ��� ��� �����Ҵ��� �ƴ� ���������� ������ �ϰ�, �����Ҷ��� ���ڿ��� ������ �ٲ��� �ʴ� �� ���� ���ڿ��� ����Ű�⸸ �ϴ� �� �ӵ��� ����Ű�� ���� ���� ����� ����Ǿ��ִ�.

[2.	��� ���� ���α׷�]
1.	������ ȸ���� ������� ������ ����ؼ� �Ѵ޿� �� �󸶳� �Ǵ� ���� �������� �����ؾ� �ϴ��� �˷��ִ� ���α׷��̴�. 
2.	EmployeeŬ������ �ܼ��� �迭�ν� ������ ���� ������, EmployeeListŬ������ ���� �����ϰ� ó���غ���. 
3.	������� ���α׷��� �� ���� �����ش޶�� ����, ���� ���� ���� ���� �̻� �޵��� ��������Ŀ�� �ټ� ����� ���Խ��Ѽ� ���޿� �߰��ش޶�� ���Ѵ�. �׸��Ͽ� ManagerŬ������ �߰��Ѵ�. ¥�����Ե� EmployeeList������ �޸� ó���ؾ��Ѵ�. 

[3. ���(Inheritance)]_...���� 
1.	Manager�� �ڵ� ��ü�� Employee�� ��κ��� �����ϰ� �ִµ�, C++������ �ٸ� Ŭ������ ������ �״�� ������ �� �ְ��ϴ� �۾��� ������ �ϴµ� �̸� ����̶�� �Ѵ�.
2.	���� ���� �̸��� �Լ��� �Ļ�, ���Ŭ������ �ִٰ� �ϴ���, ���������� �ٸ� Ŭ������ ���ǵǾ� �ִ� ���̱� ������ �ٸ� �Լ��� ��޵ȴ�.
	��, �켱 DerivedŬ������ What�Լ��� ���ǵǾ� �ֱ� ������ ���� �ָ� Base�Լ����� ������ �ʰ�, DerivedŬ������ what()�Լ��� ȣ���Ѵ�.
	�̰��� �������̵�(Overriding)�̶�� �Ѵ�. ��, Derived�� what�Լ��� Base�� what�Լ��� �������̵� �� �� �̴�.
	!=�����ε�. 
	
[4. ���ο� ģ�� protected]
1.	����� �޾Ƶ� private ��� �������� ��� ��쿡�� �ڱ� Ŭ���� ����� ������ �� ����. ���⼭ �߻��ϴ� ������, EmployeeŬ������ ������� ����Ͽ� Managee�� ����ٰ� �ϸ�,
	�̶� name�̳� age�� Employee�� private��������� ������ ������ ���ϰ� �Ǵ� ������ �߻��Ѵ�. 
	 �̸� �ذ��ϱ� ���� C++������ protected��� public�� private�� �߰� ��ġ�� ���� �����ڸ� �����Ѵ�. ��, ��ӹ޴� Ŭ������ �����ϰ� ��� ���� �Ұ����� ������ ��� �ִ�.
	������ģ����_private: ����й�ȣ protected: ������������й�ȣ public: ���ּ� 
2.	class Derived : public Base�� �ǹ�.
	Ű���尡 public�� ��, ��� Ŭ������ ���� �����ڵ鿡 ���� ���� �״�� �۵��Ѵ�. ��, public�� public����, protected�� protected��, private�� private�� �״�� �۵��Ѵ�.
	Ű���尡 protected���, public�� protected�� �ٲ�� �������� �����ȴ�.
	���� private���, ��� private�� �ȴ�. 
	
[5. ��� ���� ���α׷��� �����غ���.]
*/

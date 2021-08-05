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
		Base():s("���") {  std::cout<<"��� Ŭ����"<<std::endl;  }//constructor with initializer list
		void what(){
			std::cout<<s<<std::endl;
		}  
};
class Derived:public Base{
	std::string s;
	
	public:
		Derived():s("�Ļ�"),Base(){
			std::cout<<"�Ļ� Ŭ����"<<std::endl;
		}
		void what(){
			std::cout<<s<<std::endl;
		}
};
int main(){
	/*normal main
	std::cout<<" ===��� Ŭ���� ���� ==="<<std::endl;
	Base p;
	p.what();
	std::cout<<" === �Ļ� Ŭ���� ���� === "<<std::endl;
	Derived c;
	c.what();*/
	
	/*up casting main
	Base p;
	Derived c;
	
	std::cout<<"===������ ����==="<<std::endl;
	Base p_c=&c;//assign Derived to Base!!!
	p_c->what();*/
	
	/*try down casting main 
	Base p;
	Derived c;
	
	std::cout<<"===������ ����==="<<std::endl;
	Derived* p_p=&p;//assign Base to Derived->Error occur!!!
	p_p->what();;*/
	
	/*down casting of Base class that points Derived class actually.
	Base p;
	Derived c;
	
	std::cout<<"===������ ����==="<<std::endl;
	Base* p_p=&c;
	
	//Derived* p_c=p_p;//p_p actually points Derived, but p_p's type is Base so it occur error too. but it's logical to work. so for doing it, we will cast forcely.
	Derived* p_c=static_cast<Derived*>(p_p);//thanks to p_p is pointing Derived actually.
	p_c->what();*/
	
	/*down casting that is not the same way with upper case.
	Base p;
	Derived c;
	
	std::cout<<"===������ ����==="<<std::endl;
	Base* p_p=&p;
	
	Derived* p_c=static_cast<Derived*>(p_p);
	p_c->what();//runtime error occur.*//*
	
	//dynamic casting
	Base p;
	Derived c;
	
	std::cout<<"===������ ����==="<<std::endl;
	Base* p_p=&p;
	
	Derived* p_c=dynamic_cast<Derived*>(p_p);//error occur. for find error easily.....just? no special function...?TT
	p_c->what();
	
	
	
	return 0;
}*/

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
};

/*
[1.	is '-a'�� 'has -s']
1.	C++������ �ܼ��� Ctrl+C, Ctrl+V�� �����ϱ� ���� ����� ������� �ƴϴ�. ������ C������ ����ü ������ ���踦 ��Ÿ�� ����� ��������, 
	����� ������ �����ϸ�, Ŭ���� ������ ���踦 ǥ�������ν�, ��ü�������α׷��ֿ��� �߱��ϴ� ���� ��ü�� �߻�ȭ�� �� �� ȿ�������� �� �� �ְ� �Ǿ���.
2.	class Manager:public Employee�� �ǹ̴� 
	-Manager class�� Employee�� ��� ����� �����Ѵ�.
	-Manager class�� Employee�� ����� ��� ������ �� �ֱ� ������ Manager�� Employee��� Ī�ص� �����ϴ�.
	-��, ��� Manager�� Employee�̴�.
	-Manager is a Employee!
	����, ��� ��� ����� is a�� �����̴�. �翬�ϰԵ� �̸� �ڹٲٸ� �������� �ʴ´�. Manager�� Employee������, Employee�� Manager�� �ƴϴ�.
	 ���α׷� ���� �ÿ� Ŭ���� ���� ��� ���踦 ��ǥ�� ��Ÿ���� ��찡 ���� �ִµ�, ���� ��� �Ļ� Ŭ������ ��� Ŭ������ ȭ��ǥ�� ����Ű�� �׸���. Manager->Employee
	Ex)A programmer is a human, CheckingAccount and SavingAccount are BankAccount.
	 ���Ͱ��� ���ÿ��� �� �� �ִ� ����� �߿��� Ư¡��, Ŭ������ �Ļ��� ���� �� �� Ư��ȭ(��üȭ:specialize)�ȴٴ� �ǹ��̴�. ��, EmployeeŬ������ �Ϲ����� ����� ���� Ŭ���� ���ٸ�, ManagerŬ���� ����
	�Ϲ����� ����� �߿����� �� �� Ư���� �η��� ������� �ǹ��ϰ� �ȴ�. ���� BankAccount�� �Ϲ����� ���� ���¸� ���� Ŭ���� ���ٸ�, �̸� ��ӹ޴� CheckingAccount, SavingAccount���� �� �� ��ü���� Ŭ������ �ȴ�.
	�ݴ�� ���Ŭ������ �Ž��� �ö󰡸� �ö� ���� ���� �Ϲ�ȭ(generalize)�ȴٰ� �Ѵ�. 
3.	������ ��� Ŭ������ ���踦 is-a�θ� ǥ���� �� ����. ex) �ڵ��� Ŭ������ �����ϴµ� ���Ǵ� ���� Ŭ����, �극��ũ Ŭ����, ����� Ŭ����...�̵��� �ڵ��� is ����, �ڵ��� is �극��ũ�� �ƴϱ� ������ has-a����� ǥ���Ѵ�.
	 ��, �ڵ����� ������ ������(�ڵ��� has a ����), �ڵ����� �극��ũ�� ������(�ڵ��� has a �극��ũ). 
	 
[2. (�ٽú���) �������̵�]
1.	Derived�� Base�� �����ص� �Ǵµ�, Derived�� Base�� ��ӹް� �ֱ� �����̴�. ��, Derived is a Base. Derived�� �ش��ϴ� �κп� ���� ������ ������ Base��ü�� ���������.
	 �̷��� �Ļ�Ŭ�������� ���Ŭ������ ĳ���� �ϴ� ���� ��ĳ����(Up casting)�̶�� �Ѵ�. 
	�׷��ٸ� �ٿ�ĳ������? ���� Derived* pointer�� Base object�� ����Ų�ٸ�, p_p->what()���� Derived�� what()�� call�ؾ� �ϴµ�, p_p�� ����Ű�� ��ü�� Base��ü�̹Ƿ� Derived�� ���� ������ ���� �Ұ����ϴ�.
	��� �����Ϸ��󿡼� �Ժη� �ٿ� ĳ���� �ϴ� ���� �����ϰ� �ִ�. 
2.	���������� �ٿ�ĳ������ �ϴ� ���, �Ĥ����� Ÿ�ӿ��� ������ ã�Ƴ��� �ſ� ����� ������ �۵��� ������� �ʴ� �� �ſ�ſ� �������� �ʴ� ����̴�. 

[3. dynamic_cast]
1.	���� ���� ĳ������ ������ �̿��� �����ϱ� ���ϸ�, C++������ ��� ���迡 �ִ� �� �����͵� ���� ĳ������ ���ִ� dynamic_cast��� ���� �����Ѵ�.
	������ static_cast�� ����. 
	
[4. EmployeeList�ٽ� ����]
1.	Employee **employee_list�� Manager, employee�� ���� �־������ by �� ĳ����.->���� �߻�. calculate�� Employee�Լ��� ����. 

[5. virtual Ű����]	
*/

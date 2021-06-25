#include <iostream>

using namespace std;

/*[INHERITANCE OVERRIDING]
class A{
	public:
		void over() {
			cout << "A Ŭ������ over �Լ� ȣ��!" << endl;
		}
};

class B: public A{
	public:
		void over(){
			cout<<"B Ŭ������ over �Լ� ȣ��!"<<endl;
		}
};

int main()
{
	B b;
	b.over();//�θ��� ��� �Լ��� ������ ������ ���ƾ� �� 
	//�������̵� �� �θ��� Ŭ���� �Լ��� ��� ������. 
	
	//�ٵ� �׷��ٰ� �� �θ��Լ��� Ŭ���� �Լ��� �� ȣ���ϴ� ���� �ƴ�.
	b.A::over();
	 
	return 0;
}//�����ε��� �̸������Լ� �ٸ��� ���°� �������̵�� �������°�
*/ 

/*[VIRTUAL FUNCTION]
class Parent {
	public:
		//void func() { cout << "�θ� Ŭ������ func �Լ� ȣ��!" << endl; }
		virtual void func() { cout << "�θ� Ŭ������ func �Լ� ȣ��!" << endl; } 
};

class Child : public Parent {
	public:
		//void func() { cout << "�ڽ� Ŭ������ func �Լ� ȣ��!" << endl; }
		virtual void func() { cout << "�ڽ� Ŭ������ func �Լ� ȣ��!" << endl; }
};//virtual �Լ��� ����ϸ� �����Ϸ��� �����ͺ����� �ڷ����� ����ϴ� ���� �ƴ� ���� ����Ű�� ���� ���� 

int main()
{
	Parent P, *pP;
	Child C;
	
	pP=&P;
	pP->func();
	pP=&C;//���⿡�� �ڽ��Լ��� �ּҸ� ��� �� ������, �����ͺ����� �ڷ����� �����Ϸ��� ����ϱ� ������
	//�θ��Լ��� �ν���. 
	pP->func();//�ڽ��Լ��� �ƴ� �θ� ȣ��! 
	
	return 0;
}
*/

/*[PURE VIRTUAL FUNCTION] 
class Parent{
	public:
		virtual void func()=0;
};

class Child: public Parent{
	public:
		virtual void func(){ cout << "�ڽ� Ŭ������ func �Լ� ȣ��"<<endl;}//���� �����Լ��� �ڽ�Ŭ�������� �ݵ�� ������. 
};//�������̵� 

int main()
{
	//Parent P; //error! ���������Լ��� ��ü�� ���� ���� �Ұ�.  
	Parent *P;//�����ʹ� ���� 
	
	P=new Child;
	P->func();
	
	return 0;
}
*/

//[MULTIPLE INHERITANCE]
class ParentOne {
 	public:
		void funcone() { cout << "ParentOne Ŭ�������� funcone() ȣ��!" << endl; }
};

class ParentTwo {
	public:
		void functwo() { cout << "ParentTwo Ŭ�������� functwo() ȣ��!" << endl; }
};

class Child : public ParentOne, public ParentTwo {
	public:
	void func() { funcone(); functwo(); }
};

int main()
{
	Child child;
	child.func();
	
	return 0;
}

//���߻���� ���� ����. �� Ŭ�������� ���� �̸��� �Լ��� �ִٸ� ��� �Լ��� ȣ���� �� �𸣴� �����߻�.
// ���̾Ƹ������ ����Ͽ� abcd �� d-b-a, d-c-a���� ���� �̸��� �Լ��� ȣ���ϴ� this�� �ٸ��� �ϴ� �ذ�å 
//�ٵ� �� ��� ���� 

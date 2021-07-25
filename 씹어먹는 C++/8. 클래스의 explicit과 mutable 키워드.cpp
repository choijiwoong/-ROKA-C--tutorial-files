//explicit_�Ͻ��� ��ȯ ��Ȱ��ȭ. �������� �̰� �Ͻ��� ��ȯ �� ������� ��! 
/*#include <iostream>

class MyString {
  char* string_content;  // ���ڿ� �����͸� ����Ű�� ������
  int string_length;     // ���ڿ� ����

  int memory_capacity;

 public:
  // capacity ��ŭ �̸� �Ҵ���.
  explicit MyString(int capacity);//�Ͻ��� ��ȯ ��Ȱ��ȭ!!!! 

  // ���ڿ��� ���� ����
  MyString(const char* str);

  // ���� ������
  MyString(const MyString& str);

  ~MyString();

  int length() const;
};

MyString::MyString(int capacity) {//�̸� ũ�⸦ �Ҵ�޴� ���ο� ������ �߰�. 
  string_content = new char[capacity];
  string_length = 0;
  memory_capacity = capacity;
  std::cout << "Capacity : " << capacity << std::endl;
}

MyString::MyString(const char* str) {
  string_length = 0;
  while (str[string_length++]) {
  }

  string_content = new char[string_length];
  memory_capacity = string_length;

  for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
  string_length = str.string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++)
    string_content[i] = str.string_content[i];
}
MyString::~MyString() { delete[] string_content; }
int MyString::length() const { return string_length; }

void DoSomethingWithString(MyString s) {
  // Do something...
}

int main() {
  DoSomethingWithString(3);  // ????
  
  MyString s = "abc";  // MyString s("abc") well work 
  MyString s3 = 5;      // MyString s(5) occur error
  //���Խ� ��������ڰ� ȣ��Ǵµ�, �̰��� ��쿡�� �˾Ƽ� ������ �����ڸ� �����Ϸ��� ����ִµ�, explicit�� �ֱ⿡ ������ �߻�. 
}*/

/*
[1. explicit]_����� 
1.	void DoSomethingWithString(MyString s) { Do something... } ��ó�� MyString�� ���ڷ� �޴� �Լ�����
	DoSomethingWithString("abc") ��ó�� ���������ex. MyString("abc")ǥ������ ���� ��쿡�� 
	C++�����Ϸ��� "abc"�� ��� MyString���� �ٲ� �� �ִ����� �����մϴ�. ������, �������߿�
	MyString(const char* str);�� �ֱ⿡ �˾Ƽ� DoSomethingWithString(MyString("abc"))�� ��ȯ�Ǿ� �����ϵȴ�.
	�̿� ���� ��ȯ�� �Ͻ��� ��ȯ(implicit conversion)�̶�� �θ��ϴ�.
	 ������  DoSomethingWithString(3)�̷��� �Ǽ��� ���� ��쿣, MyString(int capacity);������ �� �Լ���
	�Ͻ��� ��ȯ�� ����  DoSomethingWithString(MyString(3))���� �ǵ�ġ�ʰ� ��ȯ�Ǿ� �����ϵȴ�. 
	 �̷��� �ǵ����� ���� �Ͻ��� ��ȯ�� �����ϱ� ���� �Ͻ��� ��ȯ�� �� �� ���� ����� ���� explicitŰ�����̴�.

[2. mutable]_���� ������ 
1.	const �Լ� ���ο����� ��� �������� ���� �ٲٴ� ���� �Ұ���������, ��� ������ mutable�� �����Ѵٸ�
	const�Լ� �������� �̵��� ���� �ٲ� �� �ִ�. 
2.	mutable�� ���ٿ� ���� const()�� �������� ���� �ʴ���?
	const �Լ��� �ǹ̴� '�� �Լ��� ��ü ������ ���¿� ������ ���� �ʽ��ϴ�.' ex) �б��۾� ���� �Լ�.
	class Server {
  	// .... (����) ....

 	 // �� �Լ��� �����ͺ��̽����� user_id �� �ش��ϴ� ���� ������ �о ��ȯ�Ѵ�.
  	User GetUserInfo(const int user_id) const {
  	  // 1. �����ͺ��̽��� user_id �� �˻�
  	  Data user_data = Database.find(user_id);
	
  	  // 2. ���ϵ� ������ User ��ü ����
  	  return User(user_data);
 	 }
	}; 
	�� ������ �׳� DB���� ������ ��ȸ�ؼ�, �� ������ ������ �����ϴ� �Լ��̴�. �翬�� ������Ʈ�� �����۾���
	���� ������ const�Լ��� ����Ǿ� �ִ�.
	 ������ ��� �ѹ� ��û�� ������ ����ؼ� ��û�� Ȯ���� ���⿡ ĳ���� ����ǰ�, ĳ�� ũ��� �������̱⿡
	������ ĳ������ ����� �ȴ�.
	 class Server {
 	 // .... (����) ....

 	 mutable Cache cache; // ĳ��! Mutable!!!!!!!

 	 // �� �Լ��� �����ͺ��̽����� user_id �� �ش��ϴ� ���� ������ �о ��ȯ�Ѵ�.
  	User GetUserInfo(const int user_id) const {
  	  // 1. ĳ������ user_id �� �˻�
  	  Data user_data = cache.find(user_id);

 	   // 2. ������ ĳ���� �����Ͱ� ���ٸ� �����ͺ��̽��� ��û
 	   if (!user_data) {
  	    user_data = Database.find(user_id);

  	    // �� �� ĳ���� user_data ���
  	    cache.update(user_id, user_data); // <-- �Ұ���
  	  }

   	 // 3. ���ϵ� ������ User ��ü ����
  	  return User(user_data);
 	 }
	};
	�ٵ� GetUserInfo�� const�Լ���� ���� ������ �߻��Ѵ�.
	cache�� update�ϴ� ��������,  cache�� ���� data�� �ٲ�� �ϱ⿡ ������ �� ����.
	���� �翬�� update�Լ��� const�Լ��� �ƴ� ���̴�.
	 ���⼭ �������� �߻��ϴµ�, �׷��ٰ� GetUserInfo�Լ��� const�� ���ڴ� �̰� ����� ���忡��
	�翬�� const�� ���ǵǾ�� �ϴ� �Լ��̱� �����̴�. �׷��� �̷��� ���, Cache�� mutable�� �����ع�����
	�������� �ذ�ȴ�. 
*/
//mutable
#include <iostream>

class A {
  //int data_;
  mutable int data_;

 public:
  A(int data) : data_(data) {}
  void DoSomething(int x) const {
    data_ = x;  // �Ұ���!
  }

  void PrintData() const { std::cout << "data: " << data_ << std::endl; }
};

int main() {
  A a(10);
  a.DoSomething(3);
  a.PrintData();
}

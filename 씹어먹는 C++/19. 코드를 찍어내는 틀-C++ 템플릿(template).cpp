#include <iostream>
#include <string>
//�׷��� �� bubble_sort �Լ������� �� ���� ������ ���� �ֽ��ϴ�. ���࿡, ���� ������ �������� �ϰ�
//1~3, 4
template <typename T>
class Vector{
	T* data;
	int capacity;
	int length;
	
	public:
		typedef T value_type;//which type will be saved
		
		Vector(int n=1): data(new T[n]), capacity(n), length(0) {}//constructor
		void push_back(T s){//push
			if(capacity<=length){
				T* temp=new T[capacity*2];
				for(int i=0; i<length; i++)
					temp[i]=data[i];
				delete[] data;
				data=temp;
				capacity*=2;
			}
			data[length]=s;
			length++;
		}
		T operator[](int i) {	return data[i];}//random access by using [] operator
		void remove(int x){//remove data that is in random location
			for(int i=x+1;i<length;i++)
				data[i-1]=data[i];
			length--;
		}
		int size(){return length;}//get vector's size
		void swap(int i, int j){//change location with i and j
			T temp=data[i];
			data[i]=data[j];
			data[j]=temp;
		}
		~Vector(){//destructor
			if(data)
				delete[] data;
		}
}; 

//template specialization part
template <>//no exsist other typename work just specializing of bool argument. must exist template<> code! 
class Vector<bool>{//when Vector class used with bool argument.
	unsigned int* data;//for prevent problem when we use shift operate using int.
	int capacity;//data array's size
	int length;//real bool's size. 1 capacity->32 bools.
	
	public:
		typedef bool value_type;//which type will be saved
		
		Vector(int n=1): data(new unsigned int[n/32+1]), capacity(n/32+1), length(0){//constructor. int is 4 byte so int is 32bit. so int can save 32 bool data.
			for(int i=0; i<capacity; i++)
				data[i]=0;//initializing
		}
		void push_back(bool s){//push
			if(capacity*32<=length){
				unsigned int* temp=new unsigned int[capacity*2];
				for(int i=0; i<capacity; i++)
					temp[i]=data[i];//data save
				for(int i=capacity; i<2*capacity;i++)
					temp[i]=0;//initializing
					
				delete[] data;
				data=temp;
				capacity*=2;
			}
			if(s)
				data[length/32]|=(1<<(length%32));//if true is added, change that bit to true. some bit or 1 is absolutely 1. with protection of around bit's value.
			
			length++;
		}
		bool operator[](int i){ return (data[i/32]&(1<<(i%32)))!=0; }//access for random location...???
		void remove(int x){//remove element in random location
			for(int i=x+1; i<length; i++){//not just overcopy because just reading of left or right element is complex.
				int prev=i-1;
				int curr=i;
				
				if(data[curr/32]&(1<<(curr%32)))//if curr's bit is 1, make prev to 1
					data[prev/32]|=(1<(prev%32));
				else{//else, make prev to 0
					unsigned int all_ones_except_prev=0xFFFFFFF;
					all_ones_except_prev^=(1<<(prev%32));
					data[prev/32]&=all_ones_except_prev;
				}
			}
			length--;
		}
		int size(){return length;}//get vector's size
		~Vector(){
			if(data)
				delete[] data;
		}
}; 

template <typename Cont>//function template!
void bubble_sort(Cont& cont){//use reference
	for(int i=0; i<cont.size(); i++)//if Cont doesn't have these function like .size() then, compiler split errors
		for(int j=i+1; j<cont.size(); j++)
			if(cont[i]>cont[j])
				cont.swap(i, j);
}

int main(){
	Vector<int> int_vec;
	int_vec.push_back(3);
	int_vec.push_back(1);
	int_vec.push_back(2);
	int_vec.push_back(8);
	int_vec.push_back(5);
	int_vec.push_back(3);
	
	std::cout<<"���� ���� ---- "<<std::endl;
	for(int i=0; i<int_vec.size(); i++)
		std::cout<<int_vec[i]<<" ";
	
	std::cout<<std::endl<<"���� ���� ---- "<<std::endl;
	bubble_sort(int_vec);//Vector<int> will be sent to Cont typename in template function. runtime error!
	for(int i=0; i<int_vec.size(); i++)
		std::cout<<int_vec[i]<<" ";
	std::cout<<std::endl;
	
	Vector<std::string> str_vec;
	str_vec.push_back("hello");
	str_vec.push_back("world");
	std::cout<<"-------std::string vector------"<<std::endl;
	std::cout<<"first element : "<<str_vec[0]<<std::endl;
	std::cout<<"second element : "<<str_vec[1]<<std::endl;
	
	Vector<bool> bool_vec;
 	bool_vec.push_back(true);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(false);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);

	std::cout << "-------- bool vector ---------" << std::endl;
	for (int i = 0; i < bool_vec.size(); i++) {
  		std::cout << bool_vec[i];
	}
	std::cout << std::endl;
}

/*4
template <typename T>
T max(T& a, T& b){
	return a>b?a:b;
}//no convert to code before instantiation while compiling!

int main(){
	int a=1, b=2;
	std::cout<<"Max ("<<a<<", "<<b<<") ? : "<<max(a,b)<<std::endl;//class template instantiation! convert code to int! (we can also use <int> but compiler do instantiation with a, b type sutomatically)
	
	std::string s="hello", t="world";
	std::cout<<"Max ("<<s<<", "<<t<<") ? : "<<max(s,t)<<std::endl;
}*/

/*
[0.	���⿡ �ռ�]
1.	����(vector)�� ���� ���� �迭��, ����ڰ� �迭ó�� ����ϴµ� ũ�⸦ ������� ���̰� ���� �� �ִ� ���� �ڷ����̴�.
2.	����(stack)�� ���, ���߿� �� ���� ���� ���´�(LIFO-last in first out)������ �ڷ������� pop�� push�� ���Ͽ� �������� �۾����� �� �� �ִ�.
3.	���, �������� ������ Ÿ���� �ٲ� ������ �ٸ� ���͸� ������־�� �Ѵٴ� ���̴�. ���ݱ����� string�����͸� ó���ϵ��� �Ͽ���. 
	����, ������Ÿ���� �ٸ� ���͸� ����� ���� ���� ���̴�. �׳� �ڵ��� type�κи� �ٲ��ָ� �Ǳ� �����̴�. ��ġ ��� Ʋ�� Ÿ���� ��������� ���ϴ� �ڵ氡 ���� Ƣ����� Ʋ ����.

[1.	C++ ���ø�(template)]
1.	���Ͱ��� �۾��� C++������ template�̶�� �̸����� �����ϰ� �ִ�. ���������� ���ڷ� Ư���� '��' Ȥ�� '��ü'�� �����ؿ�����, 'Ÿ��'�� ��ü�� ������ ���� ������.
2.	���ǹ�� template <typename T> �̴� �Ʒ��� ���ǵǴ� Ŭ������ ���� ���ø��� �����ϰ�, ���ø� ���ڷ� T�� �ް� �Ǹ�, T�� �ݵ�� ��� Ÿ���� �̸����� ����ϰ� �ִ�.
3.	���� ���, ���ø� ���� �Ʒ� ���� ���� class Vector�̹Ƿ� �� VectorŬ������ ���� ���ø����� ����ϴµ�, ���࿡ �ؿ� ���� ���� �Լ��� ��� �Լ��� ���� ���ø��� �ȴ�.
4.	���� template <class T>��� ǥ���ϴµ�, template <typename T>�� ������ ǥ���̴�. �׷��⿡ ǥ�ø� class T��� �ؼ� T�ڸ��� Ŭ������ �;� �ϴ� ���� �ƴϴ�.
	(p.s �� ���� ��Ȯ�� ���� �ǹ̸� ��Ÿ������, �ǵ��� typename T�� ����ϴ� ���� �����Ѵ�. C++�� ó�� ���� Bjarne Stroustrup�� ó���� template�� ���ڷ� ���ο� Ű���带 ����� ���� �ʾ� class��� �̸��� ����Ͽ���. 
	������ �ð��� �귯 C++����ȸ���� �̷����� ȥ���� ���� ����_'class T�ڸ��� ������ class!' typename�̶�� �̸��� ����ϱ� �����߰�, ���� �ڵ���� ȣȯ�� ���ؼ� class T�� �״�� ���ܵξ���.) 
5.	�̷��� ������ ���ø��� ���ڿ� ���� �����ϱ� ���ؼ��� Vector<int> int_vec;�� ���� <>�ȿ� �����Ϸ��� ���� ������ָ� �ȴ�.  
7.	�����Ϸ��� Vector<int> int_vec;�̶�� �ڵ带 ���� Vector�� T�� int�� ġȯ�Ͽ� ���ο� �ڵ带 �ۼ��ϰ� �ȴ�. 
8.	���� ���� Ŭ���� ���ø��� ���ڸ� �����Ͽ� ���� �ڵ带 �����ϴ� ���� Ŭ���� ���ø� �ν��Ͻ�ȭ(class template instantiation)�̶�� �Ѵ�.
	��, ���ø��� �ν��Ͻ�ȭ ���� �ʰ�, ���׷��� �ִٸ� ������ �ÿ� �ƹ��� �ڵ�� ��ȯ���� �ʴ´�. ���ø��� �ݵ�� �ν��Ͻ�ȭ�Ǿ�߸� ��μ� �����Ϸ��� ���� �ڵ带 �����ϰ� �ȴ�. 
9.	����������, �Ϻ� Ÿ�Կ� ���ؼ��� �ٸ� ������� ó���ؾ� �ϴ� ��찡 �ִµ�, �ٷ� bool�����͸� �����ϴ� ���͸� �����غ� ���̴�.
	Vector<bool> bool_vec; �̿�󿡴� ������ ������, C++���� �⺻������ ����ϴ� ó�� ������ 1byte��� ���� ����ؾ� �Ѵ�.
	��, bool���������� 1bit������ ����� ������ �� ������ 8bit�� ����Ͽ� 1�� bool���� �����Ѵٴ� ���� ��û�� �޸� ���񰡾ƴҼ� ����. ���� Vector<bool>�� ���ؼ��� Ư���� ���� ó�����־�� �Ѵ�.

[3. ���ø� Ư��ȭ(template specializationi)] 
1.	�̿� ���� �Ϻ� ��쿡 ���Ͽ� ���� ó���ϴ� ���� ���ø� Ư��ȭ��� �Ѵ�. 
2.	���� template <typename A, typename B, typename C>���� A�� int��, C�� double�϶��� ���� ó���ϰ� �ʹٸ� template <typename B> class test<int, B, double>{}ó�� ó���� �� �ִ�.
 	���� B������ Ư��ȭ �ϰ� �ʹٸ�, template<> class test<int, int, couble>{}; ó�� �����ϴ� ���ø� ���ڰ� ������ Ư��ȭ�ϰ�ʹٸ� template,.�� ������� �Ѵ�. 
3.	�׷��ٸ� bool������ ���, template<> class Vector<bool>{}�� ���� ���� ó�����ָ� �ȴ�. ���⼭ int�迭�� �̿��� ���ε�, int�� ��� 32bit�̹Ƿ�, 1���� int�� 32���� bool�����͸� ������ �� �ְ�, ���� N��° bool�����ʹ� N/32��° int�ȿ� ����ǰ� �ȴ�.
4.	������� �м�

[4.	�Լ� ���ø�(Function template)]
1.	���� �Լ� ���ø����� ����� �Լ��� ������ ���ڰ� �������� ���� ��쿡 ������ �վ��. �̴� ��Ÿ�� �� �߻��ϴµ�, �����Ϸ��� type�� argument�� ���� �� �ڵ带 �ϼ��Ͽ� ����ϱ� �����̴�.
2.	�̷��� ������ �ÿ� ������ø� ���� �ν��Ͻ�ȭ�ȴٴ� ����� ������ ���ø� ��Ÿ���α׷���(template metaprogramming)�̶�� �ϴ� ������� �ڵ鸣 © �� �ִ�.
 
*/

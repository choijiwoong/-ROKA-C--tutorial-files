#include <iostream>
#include <string>

template <typename T>//=template <class T>
class Vector{
	T* data;
	int capacity;
	int length;
	
	public:
		typedef T value_type;//which type will be saved
		
		Vector(int n=1): data(new T[n]), capacity(n), length(0){}//CONSTRUCTOR
		void push_back(T s){//PUSH_BACK
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
		T operator[](int i){ return data[i]; }//ACCESS BY []
		void remove(int x){//REMOVE
			for(int i=x+1;i<length;i++)
				data[i-1]=data[i];
			length--;
		}
		int size(){ return length; }//LENGTH
		void swap(int i, int j){//SWAP
			T temp=data[i];
			data[i]=data[j];
			data[j]=temp;
		}
		~Vector(){//DESTRUCTOR
			if(data)
				delete[] data;
		}
}; 

template <>//template specialization
class Vector<bool>{//use int type
	unsigned int* data;//for prevention of problem in shift
	int capacity;//size of created data
	int length;//real bool data
	
	public:
		typedef bool value_type;
		
		Vector(int n=1): data(new unsigned int[n/32+1]), capacity(n/32+1), length(0){//CONSTRUCTOR
			for(int i=0; i<capacity; i++)
				data[i]=0;//initialization to ZERO
		}
		void push_back(bool s){//PUSH_BACK
			if(capacity*32<=length){
				unsigned int* temp=new unsigned int[capacity*2];
				for(int i=0; i<capacity; i++)//it's ok because 32 bool data is save in one int data. so if we move one int data normally, automatically 32 bool data will be moved
					temp[i]=data[i];
				for(int i=capacity; i<2*capacity; i++)//initialization to ZERO
					temp[i]=0;
				
				delete[] data;
				data=temp;
				capacity*=2;
			}
			
			if(s)//if push data is true
				data[length/32]|=(1<<(length%32));//make it to true. or operation is useful because it can protect initial value. ???
			
			length++;
		}
		bool operator[](int i){ return (data[i/32] & (1<<(i%32)))!=0; }//ACCESS BY []
		void remove(int x){//REMOVE
			for(int i=x+1; i<length; i++){
				int prev=i-1;
				int curr=i;
				
				if(data[curr/32]&(1<<(curr%32))){//curr is 1
					data[prev/32]|=(1<<(prev%32));//prev to 1
				} else{//curr is 0
					unsigned int all_ones_except_prev=0xFFFFFFFF;//value that is true except of location(we will delete) to false
					all_ones_except_prev^=(1<<(prev%32));//^ is XOR.  
					data[prev/32]&=all_ones_except_prev;//remove prev by 0
				}
			}
			length--;
		}
		int size(){ return length; }//GET SIZE
		~Vector(){//DESTRUCTOR
			if(data)
				delete[] data;
		}
};

template <typename Cont>//template function
void bubble_sort(Cont& cont){
	for(int i=0; i<cont.size(); i++)
		for(int j=i+1; j<cont.size(); j++)
			if(cont[i]>cont[j])
				cont.swap(i, j);
}

template <typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp){
	for(int i=0; i<cont.size(); i++)
		for(int j=i+1; j<cont.size(); j++)
			if(!comp(cont[i], cont[j]))//use Functor
				cont.swap(i, j);
}

struct Comp1{//Functor
	bool operator()(int a, int b){ return a>b; }
};
struct Comp2{
	bool operator()(int a, int b){ return a<b; }
};

int main(){
	Vector<int> int_vec;
	int_vec.push_back(3);
	int_vec.push_back(2);
	
	bubble_sort(int_vec);
	std::cout<<"[normal sort]"<<std::endl;
	std::cout<<"-------- int vector --------"<<std::endl;
	std::cout<<"first element: "<<int_vec[0]<<std::endl;
	std::cout<<"second element: "<<int_vec[1]<<std::endl<<std::endl;
	
	Comp1 comp1;
	bubble_sort(int_vec, comp1);
	std::cout<<"[comp1 sort]"<<std::endl;
	std::cout<<"-------- int vector --------"<<std::endl;
	std::cout<<"first element: "<<int_vec[0]<<std::endl;
	std::cout<<"second element: "<<int_vec[1]<<std::endl<<std::endl;
	
	Vector<std::string> str_vec;
	str_vec.push_back("hello");
	str_vec.push_back("world");
	std::cout<<"-------- std::string vector --------"<<std::endl;
	std::cout<<"first element: "<<str_vec[0]<<std::endl;
	std::cout<<"second element: "<<str_vec[1]<<std::endl<<std::endl;
	
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
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	
	std::cout<<"-------- bool vector --------"<<std::endl;
	for(int i=0; i<bool_vec.size(); i++)
		std::cout<<bool_vec[i];
	std::cout<<std::endl;
}

//power of template default argument
template <typename T>
struct Compare{//FUNCTOR FOR COMPARE
	bool operator()(const T& a, const T& b) const{ return a<b; }
};

template <typename T, typename Comp=Compare<T>>
T Min(T a, T b){
	Comp comp;
	if(comp(a, b))
		return a;
	return b;
}

int main(){
	int a=3, b=5;
	std::cout<<"Min "<<a<<", "<<b<<" :: "<<Min(a, b)<<std::endl;//we don't have to Compare<int> comp1; Min<comp1>(a,b);
	
	std::string s1="abc", s2="def";
	std::cout<<"Min "<<s1<<", "<<s2<<" :: "<<Min(s1, s2)<<std::endl;
}

/*
1.	template <class T>�� template <typename T>�� �����ϴ�. �ٸ� class T�� ���� ������ ȣȯ�� ���� �����Ѵ�. 
2.	Ŭ���� ���ø��� ���ڸ� �����ؼ� ���� �ڵ带 �����ϴ� ��; Ŭ���� ���ø� �ν��Ͻ�ȭ(class template instantiation)
3.	��Ʈ ����� 0�� or�ϰų� 1�� and�ϸ� ������ ���� �����ϸ� ���� ������ �� �ִ�. 
4.	Functor�� ��ü���� �Լ��� ô �ϴ� �Լ��� ���Ѵ�. �̸� �Լ� ��ü(function object)��� �Ѵ�. Functor���� Có�� �Լ� �����͸� �ѱ�� �ͺ��� Functor�� �����Ϸ��� inlineȭ �� �� �ֱ⿡ �۾��� �� ��������. 
5.	���ø� ���ڸ� �Ϲ� ����ó�� <int num>����� ���� �ִ�. �ٸ� Ÿ���� �������̴�. �ַ� ������Ÿ�ӿ� ���� �������� �ϴ� �迭�� ũ�� ���� ���ø� ���ڷ� ����Ѵ�. �� ���� default���� ������ �� �ִ�. 
6.	���ø��� ����Ѵٴ� ���� ������ Ÿ�ӿ� �ν��Ͻ�ȭ �ȴٴ� ���̰� �̴� ��, ���ÿ����� �Ҵ���� �ǹ��Ѵ�. 
7.	���ø��� ����Ʈ ���ڸ� ����� �� �ִٴ� ����, Comp�� ���� Functor�� �⺻���� ���������ν� ���ʿ��� ���������� ������ �� �ִ�. 
*/

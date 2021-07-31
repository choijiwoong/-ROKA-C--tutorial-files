#include <iostream>
//���� ���������, ����Ʈ ���ڵ��� �Լ��Ǹ� ������ ���� ���� '����������'�� ����� �� �ֽ��ϴ�. �ֳ��ϸ� ���� �츮�� ����Ʈ ���ڸ�
class Array;
class Int;

class Array{
	friend Int;
	
	const int dim;//tensor size. how deep? level.
	int* size; //size[0]*size[1]*...*size[dim-1] array.(array[3][2][3]'s 323 save this array. size information.
	
	struct Address{//private struct. class in class. struct is class all element is public.
		int level;//how deep
		void* next;//next array(low tensor) address by type. pointer for access next element by +1 to next.
	};
	Address* top;//start point
	
	public:
		Array(int dim, int* array_size);
		Array(const Array &arr);
		~Array();
		
		void initialize_address(Address *current);//recursive function that's same 'deep first search'.
		void delete_address(Address *current);
		void copy_address(Address *dst, Address*src);
		
		Int operator[](const int index);
};
Array::Array(const Array &arr):dim(arr.dim){//copy constructure.
	size=new int[dim];
	for(int i=0;i<dim;i++) size[i]=arr.size[i];
	
	top=new Address;//same process regardless of copy constructure. top is same. always.
	top->level=0;//top set
	
	initialize_address(top);//make spaces processs till here.
	
	copy_address(top, arr.top);//content copy
}
Array::Array(int dim, int* array_size):dim(dim){//Constructor of Array class with initializer list.
			size=new int[dim];//allocate size to dim.
			for(int i=0;i<dim;i++) size[i]=array_size[i];//size saves how many tensors we make.
			
			top=new Address;//top set
			top->level=0;
			
			initialize_address(top);//initialize start.
		}
void Array::initialize_address(Address *current){//argument type is pointer of Address structure. up to down.
	if(!current) return;//exception empty
	if(current->level==dim-1){//stop condition. rule2 in recursive function.
		current->next=new int[size[current->level]];//current's next is allocated by Address structure 
		return;//current->next is pointer.
	}
	current->next=new Address[size[current->level]];//size is member array that has user's input how many tensor we make.
	for(int i=0;i!=size[current->level];i++){//added element(same dim, different poket) to pass same process.
		(static_cast<Address *>(current->next)+i)->level=current->level+1;//current->next to Address(casting) and 
		//new allocated address for Address can be accessed by +1 at initial memory location, and set level.
		initialize_address(static_cast<Address *>(current->next)+i);//current->next is allocated by list as Address.
	}//so +1 means next element of current->next. same dim, different element. amount of its is in size[]
}
void Array::delete_address(Address *current){
	if(!current) return;//exception empty
	for (int i=0; current->level<dim-1&&i<size[current->level];i++){//all
		delete_address(static_cast<Address *>(current->next)+1);//Recursive function. 
	}
	if(current->level==dim-1){//is current is last level
		delete[] static_cast<int *>(current->next);//int data is in last level. current->next has Address type. so we have to cast to int*
	}
	delete[] static_cast<Address *>(current->next);//until last level, Address deallocation.
}
void Array::copy_address(Address *dst, Address *src){
	if(dst->level==dim-1){
		for(int i=0;i<size[dst->level];i++)
			static_cast<int *>(dst->next)[i]=static_cast<int *>(src->next)[i];//if we not use [i] and use just pointer, delete error.
		return;
	}
	for(int i=0;i!=size[dst->level];i++){//for all element in same level.
		Address *new_dst=static_cast<Address *>(dst->next)+1;//next's default set is void. so we has to cast to specific type before use.
		Address *new_src=static_cast<Address *>(src->next)+1;//next location save
		copy_address(new_dst, new_src);//and recursive. for all data copy, use new Address.
	}
}
Array::~Array(){//main process is work in Address, so we have to delete just left variables.
	delete_address(top);//delete top that is root memory.
	delete[] size;//delete size that is allocated list in member variable.
}
Int Array::operator[](const int index){//???
	return Int(index, 1, static_cast<void *>(top), this);
}

class Int{
		void* data;//content is same. for data
		
		int level;//for level
		Array* array;//Array object
		
		public:
			Int(int index, int _level=0, void *_data=NULL, Array *_array=NULL);//Wrapper
			Int operator[](const int index);
			operator int();
};

Int::Int(int index, int _level=0, void *_data=NULL, Array *_array=NULL)
		:level(_level), data(_data), array(_array){//def default argument(it can use sequencly when its group at back)
	if(_level<1||index>=array->size[_level-1]){//exception(top level, over index)
		data=NULL;
		return;
	}
	if(level==array->dim){//Int's level==array's dim
		data=static_cast<void *>(//save our int tupe to data
		static_cast<int *>  (static_cast<Array::Address *>(data)->next)  +index);
	} else{//or save address to data
		data=static_cast<void *>(//?????
		static_cast<Array::Address *>  (static_cast<Array::Address *>(data)->next)  +index);
	}
};
Int Int::operator[](const int index){
	if(!data) return 0;
	return Int(index, level+1, data, array);
}
Int::operator int(){
}

int main(){
	return 0;
} 

/*
[1.	C++��Ÿ���� ĳ����]
1.	������ C������ 2������ ĳ���� ��� ��, �����Ϸ��� �˾Ƽ��ϴ� �Ͻ���(implicit)ĳ���ð�, �츮�� ���� �����ϴ� �����(explicit)ĳ������ �־�����.
	ex)�Ͻ���ĳ����: int+double->double+double, �����ĳ����: void*->int* or double*, ptr=(something *)other_ptr; int_variable=(int)flocat_variable;
	 �̴� ���� �ȵǴ� ĳ���ÿ� ���Ͽ� �����Ϸ��� ������ �߻���Ű�� �ʱ⿡ �Ǽ��� ����ϸ�, �ڵ��� �������� �������ϴ�.(function((int)variable);
2.	C++������ 4������ ĳ������ �����ϰ� �ִ�.
	1) static_cast: �Ϲ����� Ÿ�� ��ȯ 
	2) const_cast: ��ü�� �����(const)�� ���ִ� Ÿ�� ��ȯ. �� const int -> int
	3) dynamic_cast: �Ļ� Ŭ���� ���̿����� �ٿ� ĳ����(to be continue...)
	4) reinterpret_cast: ������ �����ϰ� ���� ������ ���� �����͵� ������ ĳ����
	 �̷��� ĳ������ ����ϴ� ����� (���ϴ� ĳ���� ����)<�ٲٷ��� Ÿ��>(������ �ٲܰ��ΰ�?)�̴�.
	��, static_cast�� floatŸ���� float_variable������ intŸ���� ������ Ÿ�� ��ȯ�ϱ� ���ؼ���
	static_cast<int>(float_variable);�̶�� �ϸ� �ȴ�. �̴� C�� (int)(float_variable)�� ����. 
[2. N���� �迭 �����]
1.	N������ �迭�� �����ϴ� ����� ũ�� 2���� �ε�, ù��°�� array[x1][x2]...[xn]�� ���Ѵٸ�, x1*x2*...*xn�� ũ���� ������ �迭�� �Ҵ��� ��, ��Ȯ�� ��ġ�� ã���ָ� �ȴ�.
	�ι�°��, ���� �����͸� ������ �ڿ�, int* Ÿ���� x1 ũ���� 1 ���� �迭�� �Ҵ��ϰ�, �� int* �迭�� �� ���ҿ� ���ؼ� �� x2 ũ���� 1 ���� �迭�� ��� �Ҵ��� ��
	int** arr;
	arr = new int*[x1];
	for (int i = 0; i < x1; i++) arr[i] = new int[x2];
	 �ٸ� �ι�° ����� �������� ù��° ����� ��� ��Ȯ�� x1*x2��ŭ�� �޸𸮸� ��Ƹ�����, �ι�°�� �������� ��ü ũ�⶧����
	x1*x2+x1+1��ŭ�� �޸𸮸� ��ƸԴ´�.
	 ��� ù��° ����� ��� ��ü ���Ҽ��� int�� ũ�⸦ �Ѿ�ٸ� ū���� ���� lib�� ����ؾ� ������,
	�ι�° ����� �������� ���� int�� �Ѿ�� �ʴ� �̻�, �޸𸮰� �ſ�ſ�ū �迭�� ������ �� �ִٴ� ���̴�.  
	 n�����̶�� arr***...*�� �� �� ������ ���Ḯ��Ʈ���� ������ �����ͺ���.
	struct Address{
		int level;
		void* next;
	} 
2.	N������ �����ϴ� ���� �ַ� for���� ���������, ���� for���� ���� �𸣱⿡ ��� �Լ��� ����ϵ��� �Ѵ�.
	-�Լ�ü�� ó���ϴ� ��, �� ���� �ܰ迡�� ���� �ܰ�� �Ѿ�� ������ �����ΰ�?_next�� ���� ������ Adress�迭�� �������ְ�, ó��. 
	-��� ȣ���� ����Ǵ� ������ �����ΰ�?_Address�迭�� ������ dim-1�� ��. 
[3. operator[] ����]
1.	N���� �迭�� ������ ������ ���ҿ� ������ �� ������? []�� ���ϴ� �����ڴ� �־ N���� []���� ���ϴ� �����ڴ� ����.
	 arr[1][2][3]; ���� arr[1]�� ó���ϰ�, ��ü T�� �����ϰ� (T)[2]�� ó���Ǵ� ������� �ذ��غ���. 
2.	���ο� ��ü�� �ʿ��ϴ�. arr[1][2]���� arr[1]�� �Ϲ� Array�� ó���Ѵٸ� arr[1]=2;���� ����� ����� �����̴�.
	����, 1���������� int��, �������̸�  �ٸ����� �����ϰ� �ؾ��ϴµ�, �̴� �����ε� ��Ģ �� �Ѱ��� ���ڿ� �Ѱ��� ���ϸ��� �����ϴ�.
	 �̶�, intó�� �۵������� int�� �ƴ� Ŭ����. int�� Wrapper������ ���ȴ�. 
	�뷫
	class Int{
		void* data;
		
		int level;
		Array* array;
	};

*/

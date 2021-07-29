#include <iostream>

class Array{
	const int dim;//tensor size. how deep? level.
	int* size; //size[0]*size[1]*...*size[dim-1] array.(array[3][2][3]'s 323 save this array. size information.
	
	struct Address{//private struct. class in class. struct is class all element is public.
		int level;//how deep
		void* next;//next array(low tensor) address by type.
	};
	Address* top;//start point
	
	public:
		Array(int dim, int* array_size):dim(dim){//Constructor with initializer list.
			size=new int[dim];//allocate size to dim.
			for(int i=0;i<dim;i++) size[i]=array_size[i];//size saves how many tensors we make.
		}
};

void initialize_address(Address *current){//argument type is pointer of Address structure.
	if(!current) return;//exception empty
	if(current->level==dim-1){//stop condition. rule2 in recursive function.
		current->next=new int[size[current->level]];
		return;
	}
	//���� ����. ���� �� ������ �����ϸ� ������ ���� �ڵ带 © �� �ֽ��ϴ�. �˻� ���� 
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
	
*/

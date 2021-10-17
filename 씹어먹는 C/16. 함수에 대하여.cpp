#include <stdio.h> 

/*1. pointer swap by using double pointer
int pswap(int **pa, int **pb);

int main(){
	int a, b;
	int *pa, *pb;
	
	pa=&a;
	pb=&b;
	
	printf("%p %p\n", pa, pb);
	pswap(&pa, &pb);
	printf("%p %p\n", pa, pb);
	
	return 0;
}
int pswap(int **ppa, int **ppb){
	int *temp=*ppa;
	*ppa=*ppb;
	*ppb=temp;
	
	return 0;
}*/

/*2. access to array by using array pointer
int INC_element(int (*arr)[2], int row);//int arr[][2] is possible on argument of function

int main(){
	int arr[3][2]={1,2,3,4,5,6};
	INC_element(arr, 3);
	for(int i=0; i<3; i++)
		for(int j=0; j<2; j++)
			printf("%d\n", arr[i][j]);
	
	return 0;
} 
int INC_element(int (*arr)[2], int row){
	for(int i=0; i<row; i++)
		for(int j=0; j<2; j++)
			arr[i][j]++;
	return 0;
}*/

//3. function pointer 
int max(int a, int b);

int main(){
	int a=3465, b=8906;
	int (*pmax)(int, int);
	pmax=max;//pass address by name
	
	printf("%d", pmax(a,b));
	
	return 0;
}
int max(int a, int b){
	return a>b?a:b;
}

/*18
1.	main�� ���ϰ��� �ü���� �޴´�. ���� �Լ��� main�Ʒ��� ������ ��, ��ܿ� �Լ��� ����(prototype)�� �̿��Ѵ�. 
2.	double pointer�� �̿��Ͽ� ������ �ּҰ��� swap�Լ��� ���� �� �ִ�. 
3.	�迭�� ����Ű�� �����͸� �Լ��� �����Ͽ� �̿��� �� �ִ�. 
4.	�Լ��� ������ ���Ǵ� �Լ��� ������ Ÿ�Ը� �����ָ� �ȴ�. ������ *�̸� (����, ����, ...) 
	����� INC_element�� ù ���ڰ��� ��� �̸��� ������ int(*)[2]�� ����ϸ� �ȴ�. 
*/

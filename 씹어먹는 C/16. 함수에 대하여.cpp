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
1.	main의 리턴값은 운영체제가 받는다. 또한 함수를 main아래에 정의할 때, 상단에 함수의 원형(prototype)을 이용한다. 
2.	double pointer을 이용하여 포인터 주소값의 swap함수를 만들 수 있다. 
3.	배열을 가리키는 포인터를 함수에 전달하여 이용할 수 있다. 
4.	함수의 포인터 정의는 함수의 인자의 타입만 정해주면 된다. 리턴형 *이름 (인자, 인자, ...) 
	참고로 INC_element의 첫 인자같은 경우 이름만 제거한 int(*)[2]를 사용하면 된다. 
*/

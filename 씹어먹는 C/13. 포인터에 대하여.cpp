#include <stdio.h>

/*double pointer 
int main(){
	int m=3;
	int *l=&m;
	int **p=&l;//not l! because it's pointer points pointer's address.
	**p=4;
	
	printf("%d %d %d",m ,*l, **p);
		
	return 0;
} */

/*
int main(){
	//1. const type pointer
	int a;
	int b;
	const int* pa=&a;//cannot change value! compiler think a is const int because we set int* pa to const.
	
	//*pa=3;//bad!
	pa=&b;//good!
	
	int* const pb=&b;//cannot change variable!
	
	*pb=3;//good!
	//pb=&a;//bad!
	
	//2. subtract of pointer is possible.
	printf("%p", pb-pa); 
	
	int data[10]={100,21,21,64,75,23,67,45,75,47};
	
	int* dp=data;
	int sum=0;
	
	while(dp-data<=9){
		sum+=(*dp);
		dp++;
	}
	
	printf("sum of data: %d\n", sum);
	
	//3. [] is operator 
	int arr[5]={1,2,3,4,5};
	
	printf("%d, %d\n", 3[arr], *(arr+3));//because [] is operator, compiler change 3[arr] to *(3+arr) like arr[3] to *(arr+3)
	
	//4. pointer array
	int* array[3];//save information of many pointer
	
	return 0;
}*/

int main(){
	//1. pointer of array with full access admition
	int arr[3]={1,2,3};
	int (*parr)[3]=&arr;//pointer for location of array! make pointer that has enough space for accessing to array.
	int *parr2[3];//pointer array!
	
	printf("%p, %p\n\n", arr, parr); 
	
	//2. calculate num of col, row by array's rule
	int array[2][3]={{1,2,3}, {4,5,6}};
	
	printf("All size: %d\n", sizeof(array));
	printf("All row size: %d\n", sizeof(array[0]) / sizeof(array[0][0]));
	printf("All column size: %d\n\n", sizeof(array)/sizeof(array[0]));
	
	//3. pointer of 2nd array
	int ar[2][3]={{1,2,3}, {4,5,6}};
	int (*par)[3];
	
	par=ar;
	
	printf("%d\n\n", par[1][2]);
	
	//4. if we express 2nd array by double pointer
	int **p;//pointer of int*(that's size is 8bytes) 
	//p=ar;//my compiler makes error... int to int* 
	
	//printf("%d\n\n", p[1][1]);//*(*(p+1)+1)_  +1 means +8bytes because (p+1) is int*. so it locate ar[3]. and, because result of *(p+1) is int*, +1means +4bytes. so it locate ar[7]; out of range
	
	//5. casting on pointer is possible?
	long long nn=3465464565;
	int * pp= (int*)nn;
	char* cc=(char*)pp;
	*cc=1;
	
	printf("%d %p %p",cc, pp,cc);
	
	return 0;
}

/*
1.	이중 포인터(double-pointer)에 대하여 생각해보자. 

2.	pointer끼리의 덧셈은 의미없는 메모리 공간을 가리키는 것이기에 오류를 발생시키지만, 뺄셈에 한하여 가능하다.(ex. 배열의 주소값 사이의 연산으로 위치를 판별하기도 함) 
3.	배열의 이름과, 첫 원소를 가리키는 포인터는 엄연히 다르다. 다만 (sizeof나 &이 없이)배열의 이름을 사용시 암묵적으로 첫 번째 원소를 가리키는 포인터로 타입 변환될 뿐이다.
	실제로 sizeof연산을 배열의 이름 자체에 그대로 쓰면 배열의 실제 크기가 출력된다. 
4.	[]는 연산자기 때문에 3[arr]과 같이 사용할 수 있다. 
5.	포인터의 선언을 int* p나 int *p로 할 수 있지만, 주로 후자를 선택하는 이유는 여러 포인터를 동시에 선언할 때 햇갈리기 때문이다. 

6.	array의 이름을 그냥 사용하면 첫 번째 원소를 가리키는 포인터가 되지만, 그 이름에 &을 붙이면 첫 번째 원소를 가리키며 배열 사이즈를 담을 수 있는 포인터로 변경된다. 
	고로 배열 전체를 받을 경우 사용되는데, 이를 받을 때는 포인터 역시 그만한 크기를 할당해야 하기에 int (*parr)[3]처럼 int 3크기를 가지는 포인터로 선언한다. 
7.	2차원 배열에서도 마찬가지로 arr[0]이 arr[0][0]을 가리키는 포인터로 암묵적으로 타입변환될 뿐, 다른 값이다.
	이를 이용하여 2차원 배열의 행과 열의 개수를 계산할 수 있다.
8.	2차원 배열을 가리키는 포인터롤 원소들을 정확히 접근하기 위해서는 가리키는 원소의 크기(타입), arr[a][b]에서 b의 값이 필요하다.
	arr[x][y]의 시작 주소값은 arr+4bx+4y가 되기 때문이다. 고로 n차원 배열을 포인터로 담으려면 pointer[]..[] n-1개로 가능하다. 
9.	배열을 포인터로 받으면, 다음 주소들을 +나 []를 사용하여 접근이 가능하다. 2차원배열을 포인터로 받을때 역시
	+를 사용하여 접근이 가능한데, 배열의 이름을 포인터로 받으면 첫 번째 행의 주소를 리턴한다. 허나 그 크기가 [3]이기 때문에 크기3을 가지는 포인터로써 2차원 배열의 표현이 가능하다. 
10.	포인터의 크기는 운영체제의 bit수에 따라 달라지는데, 64비트에서 주소값을 나타내기 위해선 64비트(8바이트)가 필요하고, 32비트라면 4바이트(32비트)가 필요하다. 
	이는 더블포인터에서 조싱해야 하는데, 일반 int*는 int의 타입에 따라 4바이트지만, int*의 주소값을 가리키는 (int)포인터는 8바이트이다. 
	
*/ 

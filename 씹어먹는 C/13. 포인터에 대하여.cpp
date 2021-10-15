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
1.	���� ������(double-pointer)�� ���Ͽ� �����غ���. 

2.	pointer������ ������ �ǹ̾��� �޸� ������ ����Ű�� ���̱⿡ ������ �߻���Ű����, ������ ���Ͽ� �����ϴ�.(ex. �迭�� �ּҰ� ������ �������� ��ġ�� �Ǻ��ϱ⵵ ��) 
3.	�迭�� �̸���, ù ���Ҹ� ����Ű�� �����ʹ� ������ �ٸ���. �ٸ� (sizeof�� &�� ����)�迭�� �̸��� ���� �Ϲ������� ù ��° ���Ҹ� ����Ű�� �����ͷ� Ÿ�� ��ȯ�� ���̴�.
	������ sizeof������ �迭�� �̸� ��ü�� �״�� ���� �迭�� ���� ũ�Ⱑ ��µȴ�. 
4.	[]�� �����ڱ� ������ 3[arr]�� ���� ����� �� �ִ�. 
5.	�������� ������ int* p�� int *p�� �� �� ������, �ַ� ���ڸ� �����ϴ� ������ ���� �����͸� ���ÿ� ������ �� �ް����� �����̴�. 

6.	array�� �̸��� �׳� ����ϸ� ù ��° ���Ҹ� ����Ű�� �����Ͱ� ������, �� �̸��� &�� ���̸� ù ��° ���Ҹ� ����Ű�� �迭 ����� ���� �� �ִ� �����ͷ� ����ȴ�. 
	��� �迭 ��ü�� ���� ��� ���Ǵµ�, �̸� ���� ���� ������ ���� �׸��� ũ�⸦ �Ҵ��ؾ� �ϱ⿡ int (*parr)[3]ó�� int 3ũ�⸦ ������ �����ͷ� �����Ѵ�. 
7.	2���� �迭������ ���������� arr[0]�� arr[0][0]�� ����Ű�� �����ͷ� �Ϲ������� Ÿ�Ժ�ȯ�� ��, �ٸ� ���̴�.
	�̸� �̿��Ͽ� 2���� �迭�� ��� ���� ������ ����� �� �ִ�.
8.	2���� �迭�� ����Ű�� �����ͷ� ���ҵ��� ��Ȯ�� �����ϱ� ���ؼ��� ����Ű�� ������ ũ��(Ÿ��), arr[a][b]���� b�� ���� �ʿ��ϴ�.
	arr[x][y]�� ���� �ּҰ��� arr+4bx+4y�� �Ǳ� �����̴�. ��� n���� �迭�� �����ͷ� �������� pointer[]..[] n-1���� �����ϴ�. 
9.	�迭�� �����ͷ� ������, ���� �ּҵ��� +�� []�� ����Ͽ� ������ �����ϴ�. 2�����迭�� �����ͷ� ������ ����
	+�� ����Ͽ� ������ �����ѵ�, �迭�� �̸��� �����ͷ� ������ ù ��° ���� �ּҸ� �����Ѵ�. �㳪 �� ũ�Ⱑ [3]�̱� ������ ũ��3�� ������ �����ͷν� 2���� �迭�� ǥ���� �����ϴ�. 
10.	�������� ũ��� �ü���� bit���� ���� �޶����µ�, 64��Ʈ���� �ּҰ��� ��Ÿ���� ���ؼ� 64��Ʈ(8����Ʈ)�� �ʿ��ϰ�, 32��Ʈ��� 4����Ʈ(32��Ʈ)�� �ʿ��ϴ�. 
	�̴� ���������Ϳ��� �����ؾ� �ϴµ�, �Ϲ� int*�� int�� Ÿ�Կ� ���� 4����Ʈ����, int*�� �ּҰ��� ����Ű�� (int)�����ʹ� 8����Ʈ�̴�. 
	
*/ 

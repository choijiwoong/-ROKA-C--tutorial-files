#include <stdio.h>
#include <stdlib.h>//malloc

/*1. Malloc
int main(int argc, char **argv) {
	int SizeOfArray;
	int *arr;
	
	printf("num of elements: ");
	scanf("%d", &SizeOfArray);
	
	arr=(int *)malloc(sizeof(int)*SizeOfArray);//return type is void*
	
	free(arr);//for prevention of memory leak
	
	return 0;
}*/

/*2. 2nd array malloc by pointer array by using version.1 that's int* pointer
void get_sum(int **arr, int x, int y); 

int main(int argc, char **argv){
	int i,j;
	int x, y;
	
	printf("arr[x][y] will be made.\n");
	scanf("%d %d", &x, &y);
	
	//1. way
	int **arr;
	arr=(int **)malloc(sizeof(int *)*x);//make 1st array that's element is (int *) type
	for(i=0; i<x; i++)
		arr[i]=(int *)malloc(sizeof(int)*y);
	printf("complete!\n");
	
	for(i=0; i<x; i++){
		for(j=0; j<y; j++){
			arr[i][j]=i+j+i*j;
		}
	}
	
	get_sum(arr, x, y);
	
	for(i=0; i<x; i++)
		free(arr[i]);
	free(arr);
	
	return 0;
}

void get_sum(int **arr, int x, int y){//Because it's int* array, we don't have to express size of 1st size like int (*arr)[2] 
	int i, j, sum=0;
	for(i=0; i<x; i++){
		for(j=0; j<y; j++){
			sum+=arr[i][j];
		}
	}
	
	printf("sum: %d\n", sum);
}*/

//3. concept of 2nd malloc
int main(){
	int width, height;
	printf("width: ");
	scanf("%d", &width);
	printf("height: ");
	scanf("%d", &height);
	
	int(*arr)[width]=(int(*)[width])malloc(height*width*sizeof(int));
	/*
	int(*arr2)[width]=(int(*)[width])malloc(height*width*sizeof(int));
	arr=arr2;
	printf("%p %p\n", arr, arr2); 
	free(arr);
	free(arr2);
	*/
	printf("complete!\n");
	
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			arr[i][j]=i+j+i*j;

	free(arr);
	
	return 0;
}//

/*4. 2nd array malloc by 2nd array by using version.2 that's real 2nd array
void get_sum(int x, int y, int (*arr)[y]);
int main(int argc, char **argv){
	int x, y;
	
	printf("x: ");
	scanf("%d", &x);
	printf("y: ");
	scanf("%d", &y);
	
	int (*arr)[y]=(int(*)[y])malloc(sizeof(int)*x*y);
	
	for(int i=0; i<x; i++)
		for(int j=0; j<y; j++)
			arr[i][j]=i+j+i*j;
	
	get_sum(arr, x, y);
	free(arr);
	
	return 0;
}

void get_sum(int x, int y, int (*arr)[y]){
	int sum=0, i, j;
	
	for(i=0; i<x; i++)
		for(j=0; j<y; j++)
			sum+=arr[i][j];
	
	printf("sum: %d\n", sum);
}*/


/*
1.	배열의 크기는 언제나 컴파일 시간에 확정되어야 하는데, 공간을 낭낭하게 잡아버리면 비효율적인 프로그램을 의미하게 된다. 
2.	2차원 배열의 동적할당은크게 2가지 방법을 생각할 수 있다. 
	-포인터 배열을 사용하여 2차원 배열처럼 동작하는 배열을 만들기
	-실제로 2차원 배열 크기의 메모리를 할당한 뒤 2차원 배열 포인터로 참조하기 
	 첫번째 방법은 엄밀하게 따지자면 메모리가 연속적이지 않아 2차원 배열이라고 하긴 힘들지만, 포인터의 포인터이기에 함수의 인자로 손쉽게 넘길 수 있다. 
	심지어 일반 2차원 배열의 성질 arr[3][4]처럼 접근이 가능하기에 편리하다. 
	 두번째 방법은 VLA를 지원하는 컴파일러에서만 실행이 가능한데, 이는 메모리에 연속적으로 존재하는 진짜 2차원 배열을 만들어야 하기에 이러한 사실을 컴파일러에게 전달해야 한다. 
	고로 늘 그렇듯이 행 길이를 넣어주어 2차원 배열 포인터 arr을 정의하면 된다. 다만, arr을 정의할 때 행 길이는 실제 배열의 넓이값이 들어간 뒤 정의해야 한다. 
3.	되도록이면 연속된 공간에 2차원 배열을 할당하는 두번쨰 방법을 사용하는 것이 좋다.
	malloc함수는 느린 함수이기 때문에 호출 횟수를 최소화해야되고, 첫번째 방법은 메모리의 원소에 접근하기 위해 먼저 arr[3]을 읽고 해당 주소에서 [2]연산 즉, 두단계의 메모리 접근이 필요한 반면,
	두번째 방법은 arr[3][2]에 다이렉트로 접근이 가능하기 때문이다. 또한 기본적으로 메모리가 연속적으로 있으면 접근이 빠르다. 
4.	prob.2 동적할당 된 배열을 대입했을때, 이동연산인지 복사연산인지(double free의 가능성 여부): double free 가능! 메모리의 복사.
 	free하려면 치환하기 전에 미리 free후 malloc 혹은 ralloc! 
*/

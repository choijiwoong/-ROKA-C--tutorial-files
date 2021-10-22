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
1.	�迭�� ũ��� ������ ������ �ð��� Ȯ���Ǿ�� �ϴµ�, ������ �����ϰ� ��ƹ����� ��ȿ������ ���α׷��� �ǹ��ϰ� �ȴ�. 
2.	2���� �迭�� �����Ҵ���ũ�� 2���� ����� ������ �� �ִ�. 
	-������ �迭�� ����Ͽ� 2���� �迭ó�� �����ϴ� �迭�� �����
	-������ 2���� �迭 ũ���� �޸𸮸� �Ҵ��� �� 2���� �迭 �����ͷ� �����ϱ� 
	 ù��° ����� �����ϰ� �����ڸ� �޸𸮰� ���������� �ʾ� 2���� �迭�̶�� �ϱ� ��������, �������� �������̱⿡ �Լ��� ���ڷ� �ս��� �ѱ� �� �ִ�. 
	������ �Ϲ� 2���� �迭�� ���� arr[3][4]ó�� ������ �����ϱ⿡ ���ϴ�. 
	 �ι�° ����� VLA�� �����ϴ� �����Ϸ������� ������ �����ѵ�, �̴� �޸𸮿� ���������� �����ϴ� ��¥ 2���� �迭�� ������ �ϱ⿡ �̷��� ����� �����Ϸ����� �����ؾ� �Ѵ�. 
	��� �� �׷����� �� ���̸� �־��־� 2���� �迭 ������ arr�� �����ϸ� �ȴ�. �ٸ�, arr�� ������ �� �� ���̴� ���� �迭�� ���̰��� �� �� �����ؾ� �Ѵ�. 
3.	�ǵ����̸� ���ӵ� ������ 2���� �迭�� �Ҵ��ϴ� �ι��� ����� ����ϴ� ���� ����.
	malloc�Լ��� ���� �Լ��̱� ������ ȣ�� Ƚ���� �ּ�ȭ�ؾߵǰ�, ù��° ����� �޸��� ���ҿ� �����ϱ� ���� ���� arr[3]�� �а� �ش� �ּҿ��� [2]���� ��, �δܰ��� �޸� ������ �ʿ��� �ݸ�,
	�ι�° ����� arr[3][2]�� ���̷�Ʈ�� ������ �����ϱ� �����̴�. ���� �⺻������ �޸𸮰� ���������� ������ ������ ������. 
4.	prob.2 �����Ҵ� �� �迭�� ����������, �̵��������� ���翬������(double free�� ���ɼ� ����): double free ����! �޸��� ����.
 	free�Ϸ��� ġȯ�ϱ� ���� �̸� free�� malloc Ȥ�� ralloc! 
*/

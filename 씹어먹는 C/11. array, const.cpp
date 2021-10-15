#include <stdio.h>
#define DATASET_NUM 8
#define PRIMESET_NUM 100

int main(){
	const int array[DATASET_NUM]={5,1234,2,211,142,24,124,958751};
	int prime[PRIMESET_NUM]={0,};
	prime[0]=2;
	int p_size=1;
	int done_by_prime;
	int is_prime;
	
	for(int data=0; data<DATASET_NUM; data++){//each data 
		done_by_prime=0;
		for(int pri=0; pri<p_size; pri++){//compare by prime
			if(prime[pri]<array[data] && array[data]%prime[pri]==0){
				printf("array[%d]: %d not prime!\n", data, array[data]);
				done_by_prime=1;
				break;
			}
		}
		if(done_by_prime)
			continue;
		//finish by prime
		
		for(int i=prime[p_size-1]+1; i<=array[data]; i++){
			//check i is prime
			is_prime=1;
			for(int j=2; j<i; j++){
				if(i%j==0){
					is_prime=0;
					break;
				}
			}
			
			if(is_prime){
				prime[p_size]=i;
				p_size++;
			}
		}
		//finish add new prime
		for(int pri=0; pri<p_size; pri++){
			is_prime=1;
			if(prime[pri]<array[data] && array[data]%prime[pri]==0){
				printf("array[%d]: %d not prime!\n", data, array[data]);
				is_prime=0;
				break;
			}
		}
		if(!is_prime)
			continue;
			
		printf("array[%d]: %d prime!\n", data, array[data]);//why array[7] is 593?
	}
}

/*
1.	배열 접근 시 out of range가 된다면, 다르게 사용되고 있는 데이터를 덮어쓰기 할 수 있기에 참조하는 원소의 위치가 배열의 크기보다 작은지 항상 확인해야 한다.
2.	다중 for문에서 continue시 가장 하위의 반복문이 continue된다는 것을 유의하자. 
3.	운영체제에서는 초기화되지 않은 변수에 대한 접근을 금지하고 있다. 

1.	배열은 차원에 상관없이 모두 메모리 상에서 연속적으로 존재한다.(메모리는 항상 1차원이다)
2.	배열의 크기는 임의로 정해지지 않는다. 
3.	C에서는 다차원 배열의 경우, 맨 앞의 크기를 제외한 나머지 크기들을 정확히 지정해줘야 오류가 발생하지 않는다.
	int arr[][2]={{1,2}, {3,4}, {5,6}, {7}};가능,  int arr[2][]={{4,5,6}, {7,8,9}};불가능 
*/

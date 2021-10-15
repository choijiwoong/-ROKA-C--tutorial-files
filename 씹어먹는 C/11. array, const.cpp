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
1.	�迭 ���� �� out of range�� �ȴٸ�, �ٸ��� ���ǰ� �ִ� �����͸� ����� �� �� �ֱ⿡ �����ϴ� ������ ��ġ�� �迭�� ũ�⺸�� ������ �׻� Ȯ���ؾ� �Ѵ�.
2.	���� for������ continue�� ���� ������ �ݺ����� continue�ȴٴ� ���� ��������. 
3.	�ü�������� �ʱ�ȭ���� ���� ������ ���� ������ �����ϰ� �ִ�. 

1.	�迭�� ������ ������� ��� �޸� �󿡼� ���������� �����Ѵ�.(�޸𸮴� �׻� 1�����̴�)
2.	�迭�� ũ��� ���Ƿ� �������� �ʴ´�. 
3.	C������ ������ �迭�� ���, �� ���� ũ�⸦ ������ ������ ũ����� ��Ȯ�� ��������� ������ �߻����� �ʴ´�.
	int arr[][2]={{1,2}, {3,4}, {5,6}, {7}};����,  int arr[2][]={{4,5,6}, {7,8,9}};�Ұ��� 
*/

#include <stdio.h>

int main(){
	int N;
	printf("���μ� ������ ���� �Է����ּ���: ");
	scanf("%d", &N);
	
	//check is prime(Mersenne) fastly by Lucas-Lehmer
	int M_N=N*N-1;
	int s=4;
	for(int i=0; i<N-2; i++)
		s=(s*s-1)%M_N;
	if(s==0){
		printf("%d�� ���μ����� ����� %d %d�Դϴ�!\n", N, 1, N);
		return 0;
	} 
	
	//check is 1
	if(N==1){
		printf("%d�� ���μ����� ����� 1�Դϴ�!\n", N);
		return 0;
	}
	
	printf("%d�� ���μ����� ����� ", N);
	for(int i=2; i<=N; i++){//1 doesn't make any effect!
		//check i is prime
		int is_prime=1;
		for(int j=2; j<i; j++){
			if(i%j==0){
				is_prime=0;
				break;
			}
		}
		if(is_prime==0)//if it's not prime, i++
			continue;
			
		while(N%i==0){//loop until not divide.
			printf("%d ", i);
			N=N/i;
		}
	}
	
	return 0;
}

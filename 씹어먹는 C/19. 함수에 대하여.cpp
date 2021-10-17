#include <stdio.h>

/*prob.2
int GCD(int x, int y);

int main(){
	int a=124, b=837;
	printf("%d", GCD(a, b));
	
	return 0;
} 

int GCD(int x, int y){
	if(y==0)
		return x;
	return GCD(y, x%y);
}*/

/*prob.6
int main(){
	int prime[100];
	int array[100]={0,};
	int i, k;
	int p_size=0;
	
	for(i=0; i<100; i++){
		array[i]=i+2;	
	}
		
	for(i=0; i<100; i++){
		if(array[i]==-1)
			continue;
		prime[p_size]=array[i];
		p_size++;
		for(k=i+1; k<100; k++){
			if(array[k]%array[i]==0)
				array[k]=-1;
		}
	}
	
	for(i=0; i<p_size; i++)
		printf("%d ",prime[i]);
	
	return 0;
}*/

//prob.7
#define MAX 5

void print(int *num){
	for(int i=0; i<MAX; i++)
		printf("%d",num[i]);
	printf("\n");
}
int plus(int *num1, int *num2, int *result);
int minus(int *num1, int *num2, int *result);
int multiple(int *num1, int *num2, int *result);
int divide(int *num1, int *num2, int *result);
int main(){
	char oper;
	int num1[MAX]={0, }, num2[MAX]={0, }, result[MAX+1]={0, };//sorted right 
	
	printf("input first num!\n");
	for(int i=0; i<MAX; i++){
		scanf("%c", &num1[i]);
		num1[i]-=48;//ASCII 0
	}
	fflush(stdin);//\n
	
	printf("input operator!\n");
	scanf("%c",&oper);
	fflush(stdin);//\n
	
	printf("input second num!\n");
	for(int j=0; j<MAX; j++){
		scanf("%c", &num2[j]);
		num2[j]-=48;
	}
	fflush(stdin);//\n
	
	switch(oper){
		case '+':
			plus(num1, num2, result);
			break;
		case '-':
			minus(num1, num2, result);
			break;
		case '*':
			multiple(num1, num2, result);
			break;
		case '/':
			divide(num1, num2, result);
			break;
		default:
			return 0;
			break;
	}
	
	printf("result: ");
	for(int i=0; i<=MAX; i++)
		printf("%d", result[i]);
	
	
	return 0;
}

int plus(int *num1, int *num2, int *result){
	int carry=0;
	int sum;
	for(int i=MAX-1; i>=0; i--){
		sum=num1[i]+num2[i]+carry;
		carry=sum>=10?1:0;
		sum%=10;
		
		result[i+1]=sum;
	}
	if(carry)
		result[0]=1;
	return 0;
}
int minus(int *num1, int *num2, int *result){
	int carry=0;
	int sum;
	for(int i=MAX-1; i>=0; i--){
		sum=num1[i]-num2[i]+carry;
		carry=sum<0?-1:0;
		sum=sum<0?-sum:sum;
		
		result[i+1]=sum;
	}
	if(carry){
		for(int i=0; i<MAX+1; i++)
			result[i]=0;
	}
	return 0;
}
int multiple(int *num1, int *num2, int *result){
	int carry=0;
	int sum=0;
	int buffer1[MAX+1]={0, }, buffer2[MAX+1]={0,};
	
	for(int j=MAX-1; j>=0; j--){
		buffer1={0,};
		for(int i=MAX-1; i>=0; i--){
			sum=num1[i]*num2[j]+carry;
			carry=sum>=10?sum/10:0;
			sum%=10;
			buffer1[i+1]=sum;
		}
		
	}
	
	return 0;
}
int divide(int *num1, int *num2, int *result){
	return 0;
}

/*
1.	에라토스테네스의 체는 1부터 N까지 소수를 구할 때, 소수가 발견되면 그 배수들을 검색 목록에서 제외시키는 것이다. 
	그럼 검색하면서 안지워 져있는 것들은 소수이다. prob.6
*/

#include <stdio.h> 

/*1. shift operation than divide
int main(){
	int i=120;
	
	printf("32로 나누면%d\n5칸 쉬프트하면%d\n", i/32, i>>5);
} */

/*2. use bit operation
struct HUMAN{//192 bits for 6 information!!!!
	int is_Alive;
	int is_Walking;
	int is_Running;
	int is_Jumping;
	int is_Sleeping;
	int is_Eating;
};

#define ALIVE 0x1 		//1
#define WALKING 0x2		//10
#define RUNNING 0x4		//100
#define JUMPING 0x8		//1000
#define SLEEPING 0x10	//10000
#define EATING 0x20		//100000

int main(){
	int my_status=ALIVE | WALKING | EATING;
	
	if(my_status & ALIVE)
		printf("ALIVE!\n");
	if(my_status & WALKING)
		printf("WALKING!\n");
	if(my_status & RUNNING)
		printf("RUNNING!\n");
	if(my_status & JUMPING)
		printf("JUMPING!\n");
	if(my_status & SLEEPING)
		printf("SLEEPING!\n");
	if(my_status & EATING)
		printf("EATING!\n");
		
	return 0;
}*/

/*3. judge odd even by bit operation(we heva to check just last num)
int main(){
	int i=127841;
	
	if(i&1)
		printf("odd!\n");
	else
		printf("even\n");
	
	return 0;
}*/

/*4. do many work in one loop
//use this 
while(n!=0){
	if(n&1)
		one_bit++;
	if(n&2)
		one_bit++;
	if(n&4)
		one_bit++;
	if(n&8)
		one_bit++;
	n>>=4;
}

// than
while(n!=0){//count how many 1 have
	if(n&1)
		one_bit++;
	n>>=1;
}*/



/*
1.	현대의 컴파일러는 우리의 최적화보다 훨씬 더 좋게 최적화 하기에 그냥 놔두는게 더 빠른 경우가 많다.
	또한 최적화를 했다고 해도 여러 변수들이 속도에 영향을 주어 실제로 성능이 향상되지는 않는다. 고로 항상 테스트를 해보는게 중요한데 이를 프로파일링(profiling)이라고 한다. 
2.	[산술 연산 관련]	
	-구조가 복잡한 부동 소수점(float, double)을 지양하자.
	-나눗셈을 피하자(나눗셈 속도는 덧셈의 속도/10). 만약 값의 범위가 지정되어 있다면, %보다 if문으로 최댓값에 도달했을 때 최솟값으로 만들어주는 방식을 택하자.
	 다만 분기문(if)이 때로 프로그램 속도를 저하시킬 수 있는데, 다음 명령어를 미리 실행하는 파이프라이닝중에 분기문 다음 명령어를 모르기 때문이다.
	 고로 이전의 추세를 보아서 대충 참과 거짓을 예측하여 다음 명령어를 실행하는데, 이를 분기 예측(branch prediction)이라고 한다. 
	 (근데 사실 대부분 현대 컴파일러들은 나눗셈을 알아서 최적화 잘 함)
	-나눗셈 대신 쉬프트 연산을 사용할 수 있다. 
	-비트 연산은 컴퓨터에서 가장 빠르게 실행되는 연산들이다. 어떠한 특정 자리를 1로 만드려면 1로 or, 1인지 보려면 1로 and
3.	[루프(loop) 관련]
	-알고있는 일반적인 계산 결과(공식)을 이용하라. (sum+=i보단 (n+1)*n/2)
	-끝낼 수 있다면 바로 끝내라. (break)
	-하나의 루프에서 최대한 많은 작업을 하자. 
	-루프에서는 다른 수와 비교하는 것 보다 0과 비교하는게 빠르다. 0과의 비교 연산은 CPU에 따로 만들어져 있다.
	-루프를 굳이 쓰지 않아도 되는 것은 직접 노가다로 써라 
4.	[if 및 switch문 관련]
	-if문을 2의 배수로 쪼개라; Binary Breakdown (like 2진탐색) 그리고 연속적이면 switch쓰고..
	-룩업 테이블(look 'up table, 'LUT)를 사용할 수 있으면 사용하자. 미리 계산된 데이터를 사용(ex. sin포를 어레이로) 
5.	[함수 관련]
	-함수호출에도 시간이 걸린다. 함수를 반복적으로 호출하기 보단 그 함수 내에서 반복적인 작업을 처리하자.
	-인라인(inline)함수를 사용하자. 
	-인자를 전달하는 경우 포인터를 이용하라.
	 stuct big{
    	 int arr[1000];
		 char str[1000];
	 };
6.	완전한 최적화는 불가능하다. 최적화의 여지가 항상 남아있기 때문에 최적화에 너무 많은 노력을 기울이는 것은 무의미하다.
 
*/

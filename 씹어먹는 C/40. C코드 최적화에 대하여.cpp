#include <stdio.h> 

/*1. shift operation than divide
int main(){
	int i=120;
	
	printf("32�� ������%d\n5ĭ ����Ʈ�ϸ�%d\n", i/32, i>>5);
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
1.	������ �����Ϸ��� �츮�� ����ȭ���� �ξ� �� ���� ����ȭ �ϱ⿡ �׳� ���δ°� �� ���� ��찡 ����.
	���� ����ȭ�� �ߴٰ� �ص� ���� �������� �ӵ��� ������ �־� ������ ������ �������� �ʴ´�. ��� �׻� �׽�Ʈ�� �غ��°� �߿��ѵ� �̸� �������ϸ�(profiling)�̶�� �Ѵ�. 
2.	[��� ���� ����]	
	-������ ������ �ε� �Ҽ���(float, double)�� ��������.
	-�������� ������(������ �ӵ��� ������ �ӵ�/10). ���� ���� ������ �����Ǿ� �ִٸ�, %���� if������ �ִ񰪿� �������� �� �ּڰ����� ������ִ� ����� ������.
	 �ٸ� �б⹮(if)�� ���� ���α׷� �ӵ��� ���Ͻ�ų �� �ִµ�, ���� ��ɾ �̸� �����ϴ� ���������̴��߿� �б⹮ ���� ��ɾ �𸣱� �����̴�.
	 ��� ������ �߼��� ���Ƽ� ���� ���� ������ �����Ͽ� ���� ��ɾ �����ϴµ�, �̸� �б� ����(branch prediction)�̶�� �Ѵ�. 
	 (�ٵ� ��� ��κ� ���� �����Ϸ����� �������� �˾Ƽ� ����ȭ �� ��)
	-������ ��� ����Ʈ ������ ����� �� �ִ�. 
	-��Ʈ ������ ��ǻ�Ϳ��� ���� ������ ����Ǵ� ������̴�. ��� Ư�� �ڸ��� 1�� ������� 1�� or, 1���� ������ 1�� and
3.	[����(loop) ����]
	-�˰��ִ� �Ϲ����� ��� ���(����)�� �̿��϶�. (sum+=i���� (n+1)*n/2)
	-���� �� �ִٸ� �ٷ� ������. (break)
	-�ϳ��� �������� �ִ��� ���� �۾��� ����. 
	-���������� �ٸ� ���� ���ϴ� �� ���� 0�� ���ϴ°� ������. 0���� �� ������ CPU�� ���� ������� �ִ�.
	-������ ���� ���� �ʾƵ� �Ǵ� ���� ���� �밡�ٷ� ��� 
4.	[if �� switch�� ����]
	-if���� 2�� ����� �ɰ���; Binary Breakdown (like 2��Ž��) �׸��� �������̸� switch����..
	-��� ���̺�(look 'up table, 'LUT)�� ����� �� ������ �������. �̸� ���� �����͸� ���(ex. sin���� ��̷�) 
5.	[�Լ� ����]
	-�Լ�ȣ�⿡�� �ð��� �ɸ���. �Լ��� �ݺ������� ȣ���ϱ� ���� �� �Լ� ������ �ݺ����� �۾��� ó������.
	-�ζ���(inline)�Լ��� �������. 
	-���ڸ� �����ϴ� ��� �����͸� �̿��϶�.
	 stuct big{
    	 int arr[1000];
		 char str[1000];
	 };
6.	������ ����ȭ�� �Ұ����ϴ�. ����ȭ�� ������ �׻� �����ֱ� ������ ����ȭ�� �ʹ� ���� ����� ����̴� ���� ���ǹ��ϴ�.
 
*/

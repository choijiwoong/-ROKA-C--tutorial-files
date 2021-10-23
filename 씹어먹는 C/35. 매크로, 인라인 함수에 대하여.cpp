#include <stdio.h>

/*1. mecro function 
#define square(x) x*x
#define RADTODEG(x) (x)*57.295
#define PrintVariableName(var) printf(#var"\n");
#define AddName(x, y) x##y 

int main(int argc, char **argv){
	//1. square mecro function 
	printf("1. square(3): %d\n", square(3+1));//7! it's just changed to 3+1*3+1 . we have to type #define square(x) (x)*(x)
	//2. radian to degree mec function
	printf("2. 5 rad: %f degree\n", 1/RADTODEG(5));//0! it's just change to 1/(5)*57.295. we have to type #define RADTODEG(x) ((x)*57.295)
	//3. print mec function
	printf("3. ");
	int a;
	PrintVariableName(a);//printf("a" "\n");
	//4. name add mec function
	int AddName(a,b);//int ab; before compile
	ab=3;
	printf("4. %d\n", ab);
	
	return 0;
} */

//2. inline function
__inline int square(int a){ return a*a; }
__inline int max(int a, int b){//inline function check argument's type! unlike mecro function
	if(a>b)
		return a;
	else
		return b;
} 

int main(int argc, char **argv){
	printf("%d", square(3+1));//16! welldone! 
	printf("max of 3 & 2: %d\n", max(3,2));//it's changed to like 3>x?3:2
	
	return 0;
}

/*
1.	��ũ�� �Լ��� �Ϲ����� define ġȯ�� ���� square(x)�κ��� ������ �Ǳ� ���� x*x�� ġȯ�Ѵ�.
	 �ٸ� ������ ���� ġȯ�� ���̱⿡ ���� �������� �����ϱ� ���� ��ü ������ �Ұ�ȣ�� ���� �� �ִ�. 
2.	��� ���� �տ� #�� ���̸� �� ���ڸ� ���ڿ��� �ٲپ� ������. C���� ������ �� ���� ���ڿ��� �ϳ��� ���� ����Ѵ�.
3.	##�� �Էµ� ���� �ϳ��� �����ش�. (����� #�� ##�� ��� ��ó���������� ������ �����̴�.)

4.	�Ϲ����� �Լ��� ȣ���ϸ�, main���� ���ڸ� ���� �ش� �Լ��� ����, ���ϰ��� ������ �ٽ� main�Լ��� ���� ���̱⿡ �ð��� �ɸ��� �ȴ�.
	�Լ��� inline���� ����� �Ǹ� ��ũ�� �Լ�ó�� ġȯ�� �ϰ� �ȴ�. �� �ܼ��� �Լ�ó�� ���̴� ���� ���̴�. 
	 �ٸ� ��ũ�� �Լ�ó�� �����ϰ� ġȯ�Ͽ� ������ �켱������ ���̴� ���� �ƴ϶� �����Ϸ��� �˾Ƽ� �����ϰ� ���� ����ϴ� �Լ�ó�� �ٲ��ش�. 
5.	�����Ϸ��� �ζ����Լ��� ȣ���� ���� �̸� �ζ��� �Լ� ������ �ڵ�� ��ü�� �� �ִ����� ������ ��, ���� ���� ġȯ�Ͽ� �۾��ϴ� �� ����
	�Ϲ����� ������� �Լ��� ȣ���ϰ� ���Ϲ޴� ����� �� ũ�ٸ� inlineŰ���带 �����ϰ� �ȴ�. 
*/

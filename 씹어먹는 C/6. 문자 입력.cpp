#include <stdio.h>

int main(){
	double celsius;
	
	printf("input celsius temperature: ");
	scanf("%lf", &celsius);
	
	printf("converted value is %f\n",9/5*celsius+32);//logic error! because of arthimetic convertion
	
	/*summary of io format
	char ch;
	
	short sh;
	int i;
	long lo;
	
	float fl;
	double du;
	
	printf("input char type variable: ");
	scanf("%c", &ch);
	
	printf("input short type variable: ");
	scanf("%hd", &sh);
	printf("input int type variable: ");
	scanf("%d", &i);
	printf("input long type variable: ");
	scanf("%ld", &lo);
	
	printf("input float type variable: ");
	scanf("%f", &fl);
	printf("input double type variable: ");
	scanf("%lf", &du);
	
	printf("char: %c, short: %d, int: %d\n", ch, sh, i);
	printf("long: %ld, float: %f, double: %f\n",lo, fl, du);*/
	
	return 0;
} 

/*
1.	출력시 double과 float을 %f로 출력했지만, scanf입력 시 float은 무조건 %f로 받아야 한다. 
*/

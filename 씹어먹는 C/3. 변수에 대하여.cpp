#include <stdio.h>

int main(){
	//computer believe our definition! 
	float a=3.141592f;
	double b=3.141592;
	
	printf("a: %d\n b: %d\n",a,b);//logic error; not %f!
	printf("%f\n\n",1);//logic error; not 1.0! 
	
	//formats of printf
	int c=123;
	
	printf("a: %.20f\n", a);
	printf("c: %5d\n", c);
	printf("b: %6.3f\n", b);
	
	return 0;
} 

/*
1.	%d_10진법, %o_8진법, %x_16진법 
2.	double이나 float처럼 선언을 한 것을 %d식으로 출력하게 되면 쓰레기 값이 출력되는데, 그 이유는 우리가 a와 b를 선언한 순간 
	컴퓨터는 a와 b를 절대 정수로 보지 않기 때문이다. 
	 또한 printf에서 %f를 사용하여 수를 출력할 때, 소수점을 붙이지 않으면 이상한 값(0)이 출력된다. 
3.	%.2f는 소수점 2자리까지 무조건 출력하라, %5d는 5자리를 맞추어라는 것을 의미하지만 수가 오바되면 다 표기한다. 
	이 둘을 섞어 %6.3f는 6자리를 맞추되, 소수는 3째자리까지 표기하라는 것이다. 
4.	오래된 C언어(C89)는 변수의 선언을 반드시 최상단에 해야했다. 
5.	대소문자를 구분한다는 것을 영어로 case sensitive라고 한다.
*/

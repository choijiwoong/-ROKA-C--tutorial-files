#include <stdio.h>

int main(){
	int a, b;
	printf("%f\n", a/b);//logic error; (int) (operator) (int) pop only int!
	
	//we have to solve it by arithmetic conversion (double b;)
	
	return 0;
} 

/*
1.	+, -, *, /, %는 산술 연산자(Arithmetic Operator), =는 대입 연산자(Assignment Operator) 
2.	%를 출력하고 싶으면 %%를 사용하면 된다. 
3.	어떠한 자료형이 다른 두 변수를 연산할 때, 숫자의 범위가 큰 자료형으로 자료형이 바뀌는데, 이를 산술 변환이라 한다.
4.	복합대입연산*=, 증감 연산자(prefix, postfix; ++c, c++). 이중 속도가 가장 빠른 연산을 증감 연산이다(INC a than ADD a 1) 
5.	shift연산에서 <<은 오른쪽으로 shift하면 무조건 0이 채워지지만, >>는 앞부분에 맨 왼쪽의 수로 채워지게 된다.
	11100010>>3=11111100, 00011001>>3=00000011 
*/

#include <stdio.h>

int main(){
	int a, b;
	printf("%f\n", a/b);//logic error; (int) (operator) (int) pop only int!
	
	//we have to solve it by arithmetic conversion (double b;)
	
	return 0;
} 

/*
1.	+, -, *, /, %�� ��� ������(Arithmetic Operator), =�� ���� ������(Assignment Operator) 
2.	%�� ����ϰ� ������ %%�� ����ϸ� �ȴ�. 
3.	��� �ڷ����� �ٸ� �� ������ ������ ��, ������ ������ ū �ڷ������� �ڷ����� �ٲ�µ�, �̸� ��� ��ȯ�̶� �Ѵ�.
4.	���մ��Կ���*=, ���� ������(prefix, postfix; ++c, c++). ���� �ӵ��� ���� ���� ������ ���� �����̴�(INC a than ADD a 1) 
5.	shift���꿡�� <<�� ���������� shift�ϸ� ������ 0�� ä��������, >>�� �պκп� �� ������ ���� ä������ �ȴ�.
	11100010>>3=11111100, 00011001>>3=00000011 
*/

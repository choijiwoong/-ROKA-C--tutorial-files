#include <stdio.h>
#include <string.h>

/*1. library
int main(){
	char str1[20]={"hi"};
	char str2[20]={"hello every!"};
	
	strcpy(str1, str2);
	printf("str1: %s\n", str1);
	
	return 0;
} */

//2. calculator program that uses float and double
#define CACULATOR_MODEL_1

#ifdef CALCULATOR_MODEL_1
float var1, var2;
#endif

#ifdef CALCULATOR_MODEL_2
double var1, var2;
#endif

/*
1.	������Ͽ��� �Լ��� ���� �Ӹ� �ƴ϶� ��������, ����ü&����ü&������, �Ϻ� Ư���� �Լ�(ex. �ζ���), ��ũ�� ���� ����. 
2.	�ٸ� ����� ���� �Լ����� ����ϱ⿡ ���ϰ� �� ���� ���̺귯���̴�. 
3.	define ��ũ���̸� �� ����, �̴� �� �״�� ��ó�����̱⶧���� ������ ���� ġȯ�ȴ�. 
	#ifdef ��ũ���̸�(�� ���ǵǾ��ִٸ� �� �κ��� �ڵ忡 ���Եȴ�) 
	#endif 
	 #ifndef�� �ִ�. 
*/ 

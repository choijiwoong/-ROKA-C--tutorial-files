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
1.	헤더파일에는 함수의 원형 뿐만 아니라 전역변수, 구조체&공용체&열거형, 일부 특정한 함수(ex. 인라인), 매크로 등이 들어간다. 
2.	다른 사람이 만든 함수들을 사용하기에 편리하게 한 것이 라이브러리이다. 
3.	define 매크로이름 값 으로, 이는 말 그대로 전처리기이기때문에 컴파일 전에 치환된다. 
	#ifdef 매크로이름(이 정의되어있다면 이 부분이 코드에 포함된다) 
	#endif 
	 #ifndef도 있다. 
*/ 

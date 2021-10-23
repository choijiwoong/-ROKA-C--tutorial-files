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
1.	매크로 함수는 일반적인 define 치환과 같이 square(x)부분을 컴파일 되기 전에 x*x로 치환한다.
	 다만 주의할 점은 치환일 뿐이기에 연산 오류들을 방지하기 위해 전체 수식을 소괄호로 묶을 수 있다. 
2.	어떠한 인자 앞에 #을 붙이면 이 인자를 문자열로 바꾸어 버린다. C언어에선 연속한 두 개의 문자열을 하나로 합쳐 출력한다.
3.	##는 입력된 것을 하나로 합쳐준다. (참고로 #과 ##는 모두 전처리문에서만 가능한 문법이다.)

4.	일반적인 함수를 호출하면, main에서 인자를 갖고 해당 함수로 가서, 리턴값을 가지고 다시 main함수로 오는 것이기에 시간이 걸리게 된다.
	함수를 inline으로 만들게 되면 매크로 함수처럼 치환을 하게 된다. 즉 단순히 함수처럼 보이는 것인 것이다. 
	 다만 매크로 함수처럼 무식하게 치환하여 연산자 우선순위가 꼬이는 것이 아니라 컴파일러가 알아서 적절하게 보통 사용하는 함수처럼 바꿔준다. 
5.	컴파일러는 인라인함수의 호출을 보고 이를 인라인 함수 내부의 코드로 대체할 수 있는지를 생각한 뒤, 만약 직접 치환하여 작업하는 것 보다
	일반적인 방법으로 함수를 호출하고 리턴받는 비용이 더 크다면 inline키워드를 무시하게 된다. 
*/

#include <stdio.h>

/*1. static variable
int* function(){
	static int a=2;
	return &a;
}

int main(){
	int *pa=function();
	printf("%d \n", *pa);
	
	return 0;
}*/

int global=3;

int main(){
	int i;
	char *str="Hello, Baby";//RO
	char arr[20]="WHATTHEHECK";
	
	printf("global: %p\n", &global);//2
	printf("i: %p\n", &i);//4
	printf("str: %p\n", str);//1
	printf("arr: %p\n", arr);//3
	
	return 0;
} 

/*
1.	지역변수(local variable)와 달리 전역 변수(global variable)는 메모리의 데이터 영역(Data segment)에 할당된다.
	전역변수들을 정의 시 자동으로 0으로 초기화된다. 전역변수는 모든 함수에서 접근이 가능하기에, 사용 시 굉장히 주의하여 사용해야 한다. like private to public
2.	일반적으로 정의된 변수들을 자신이 정의된 지역을 빠져나갈 때 파괴된다. 이와 반대로, 지역을 빠져나가도 파괴되지 않는 변수는 정적 변수(static variable)이라고 한다. 
	이때 function이 실행되지 않더라도 이미 정적 변수가 정의되어 있는 상태이며, static a는 딱 한번 실행이되기에 function함수를 여러번 호출해도 초기화되지 않는다. 
	 static variable도 전역 변수와 같이 데이터영역에 저장되고, 프로그램이 종료될 때 파괴된다. 얘도 default0값을 갖는다. 
3.	C언어 자체적으로는 스택과 힙을 구분하지 않지만, 대부분의 운영체제에서 프로그램을 실행하면 힙과 스택영역을 구분하여 만들게 된다. 
	 프로그램 실행 시 프로그램에 RAM에 올라오게 되는데, 이때 RAM위로 올라오는 프로그램의 내용을 크게 나누어 코드 세그먼트(Code Segment)와 데이터 세그먼트(Data Segment)로 나눌 수 있다. 
	스택은 지역변수가 거처하는 곳으로, 지역 변수가 늘어나면 크기가 아래로(메모리 주소 낮아짐)증가하다가 지역변수가 파괴되면 다시 스택의 크기는 위로 줄어들게 된다.
	즉, 스택이 늘어나는 방향은 메모리 주소가 낮아지는 방향(아래)이다. 
4.	데이터 세그먼트의 구조는 사진을 참고하는 것이 좋으나, 간단하게 순서를 표시해보았다.
	[Stack(ex. local variable)-> <-Heap] -> Data section(ex. global variable, static variable)->Read-Only Data->Code segment
	방향은 메모리 주소가 낮아짐 
5.	다른 scope에서 같은 이름의 static variable이 있어 같이 Data segment에 들어간다고 하더라도 컴파일러 입장에서는 다른 scope에 정의되었기에 다른 변수라고 생각한다. 
*/

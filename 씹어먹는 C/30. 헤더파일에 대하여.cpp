#include <stdio.h>
#include "30. header.h" 

int main(){
	char str1[20];
	char str2[20];
	
	scanf("%s %s", str1, str2);
	
	if(compare(str1, str2))
		printf("same!\n");
	else
		printf("different!\n");
		
	return 0;
} 

/*
1.	실행파일을 만들기 위해 코드를 어셈블리로 바꿔주는 컴파일을 진행한다.(목적코드 생성)  
	다른파일에 위치한 소스 코드들을 한데 엮어서 하나의 실행파일로 만드는 링킹을 진행한다. 
2.	어떤 함수를 다른 파일에서도 사용하려고 할때, 매번 원형을 써주면 귀찮아지니 헤더파일로서 귀찮음을 해결하였다. 
3.	#include같은 명령들을 전처리기(Preprocessor)라고 부르는데, 이는 컴파일 이전에 싱행된다. 컴파일에 앞서서 지칭하는 파일의 내용을 복사하여 붙여넣는다. 
	<>는 컴파일러가 기본으로 지원하는 헤더이고, ""는 사용자 지정 헤더이다. 
4.	도서관리 프로그램을 분할해보자. main함수를 가지는 test.c, 도서관리 함수들을 가지는 book_function.c, 문자열 관리 함수를 가지는 str.c로 나누어보자.
	당연히 book_function.h와 str.h헤더파일도 가질 것이다. 
	 book_function.cpp는 add_book의 printf와 scanf가 있기에 stdio.h을 include해야하고, search_book의 경우 compare함수를 호출하기에 str.h를 include해야한다. 
	반면에 main이 있는 test.cpp는 compare함수는 사용하지 않으므로 다른 헤더만 추가해준다.
5.	prob.1 구조체 버전도 쪼개보기 
*/ 

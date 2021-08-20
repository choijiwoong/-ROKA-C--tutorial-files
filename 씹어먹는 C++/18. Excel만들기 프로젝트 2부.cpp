#include <iostream>
#include "utils.h"

int main(){
	std::cout<<"테이블 (타입) (최대 행 크기) (최대 열 크기) 를 순서대로 입력해주세요"<<std::endl;
	std::cout<<"* 참고 *"<<std::endl;
	std::cout<<"1: 텍스트 테이블, 2. CSV 테이블, 3: HTML 테이블"<<std::endl;
	
	int type, max_row, max_col;
	std::cin>>type>>max_row>>max_col;
	MyExcel::Excel m(max_row, max_col, type-1);
	m.command_line();//wait input and reprint when update of content
}

/*
[0.	들어가기에 앞서]
1.	실제 엑셀에 비해 낳짜데이터, 수식을 넣어 연산 등 여러 기능이 부족했다.

[1.	Cell 클래스 확장]
1.	Cell클래스는 string데이터만 저장할 수 있기 때문에 상속 받는 클래스들을 만들어서 셀에 다양한 데이터들을 보관할 수 있다.
	고로, Cell클래스에서 문자열 데이터를 보관했던 것과는 달리, 이를 빼버리고 상속받는 클래스에서 데이터를 보관하게 끔 하자.
	또한 stringify와 to_numeric을 순수 가상함수로 지정하여 상속 받는 클래스에서 반드시 구현토록 수정하다. 
	
[2.	수식 계산하기 '-'중위 표기법(infix notation)과 후위 표기법(postfix notation)]
1.	중위 표기법(infix notation): 3 + 4 * 5 + 4 * (7 - 2) 우리야 어떤 순서로 계산해야하는 지 알 수 있지만, 컴퓨터는 어렵기에 후위 표기법을 사용
2.	후위 표기법(postfix notation):  3 4 5 * + 4 7 2 - * + 연산자들이 피연산자 뒤쪽에 위치해있고, 괄호가 사라졌다.
3.	컴퓨터는 피연산자를 만나면 스택에 push를 한다.
	반대로 연산자를 만나면 스택에서 두 개를 pop한 뒤에 그 둘에 해당 연산을 한 후, 그 결과를 다시 스택에 push한다. 
	더 이상 입력받을 것이 없다면 스택에서 pop을 한다. 그 결과가 바로 연산결과 이다. 
4.	후위 표기법으로 된 수식을 계산하게끔 is_numeric함수를 구현해보자! 

[3.	중위 표기법을 후위 표기법으로 변환하기(parse_expression function)]
1.	중위 표기법을 후위 표기법으로 변환하는 것은 다음의 방식을 따른다.
	-피연산자(셀 이름이나 숫자)일 경우 그냥 exp_vec에 넣는다.
	-여는 괄호( (, [, { 와 같은 것들)을 만날 경우 스택에 push한다.
	-닫는 괄호( ), ], } 와 같은 것들)을 만날 경우 여는 괄호가 pop될 때 까지 pop되는 연산자들을 exp_vec에 넣는다.
	-연산자일 경우 자기보다 우선순위가 낮은 연산자가 스택 최상단에 올 때 까지(혹은 스택이 빌 때까지)스택을 pop하고(낮은 것은 pop하지 않는다), 
	 pop된 연산자들을 exp_vec에 넣는다. 그리고 마지막에 자식을 스택에 push한다. 

[4.	엑셀 프로그램]
1.	실제로 사용자의 입력을 받아서비록 마우스는 쓸 수 없더라도 키보드로 명령을 처리하는 엑셀 프로그램을 만들어보자. 
*/

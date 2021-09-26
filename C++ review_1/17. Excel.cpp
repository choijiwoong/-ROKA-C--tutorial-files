#include <iostream>
#include <string>
#include "utils.h"

int main(){
	std::cout<<"type like Table(type) (max_row_size) (max_col_size)"<<std::endl;
	std::cout<<"* reference *"<<std::endl;
	std::cout<<"1. Text Table, 2: CSV Table, 3: HTML Table"<<std::endl;
	
	int type, max_row, max_col;
	std::cin>>type>>max_row>>max_col;
	MyExcel::Excel m(max_row, max_col, type-1);
	m.command_line();
}

/*
1.	postfix-notation calculation
	-피연산자를 만나면 스택에 push
	-연산자를 만나면 스택에서 두개를 pop하고 연산뒤 다시 스택에 push
	-더이상 입력이 없으면 스택에서 pop하여 연산결과를 얻는다. 
2.  infix-notation -> postfix-notation
	-피연산자일 경우 그냥 후위저장소에 넣음
	-여는 괄호는 스텍에 넣음
	-닫는 괄호는 여는 괄호가 pop될때 까지 pop되는 연산자들을 exp_vec에 넣음
	-연산자면 자기보다 우선순위가 낮은 연산자가 스택 최상단에 올때 까지 pop하고 pop된건 exp_vec에 넣음 
*/

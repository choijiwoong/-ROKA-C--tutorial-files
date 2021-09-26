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
	-�ǿ����ڸ� ������ ���ÿ� push
	-�����ڸ� ������ ���ÿ��� �ΰ��� pop�ϰ� ����� �ٽ� ���ÿ� push
	-���̻� �Է��� ������ ���ÿ��� pop�Ͽ� �������� ��´�. 
2.  infix-notation -> postfix-notation
	-�ǿ������� ��� �׳� ��������ҿ� ����
	-���� ��ȣ�� ���ؿ� ����
	-�ݴ� ��ȣ�� ���� ��ȣ�� pop�ɶ� ���� pop�Ǵ� �����ڵ��� exp_vec�� ����
	-�����ڸ� �ڱ⺸�� �켱������ ���� �����ڰ� ���� �ֻ�ܿ� �ö� ���� pop�ϰ� pop�Ȱ� exp_vec�� ���� 
*/

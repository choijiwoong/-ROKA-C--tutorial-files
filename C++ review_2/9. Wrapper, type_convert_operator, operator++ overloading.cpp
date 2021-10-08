#include <iostream>

//1. Wrapper Class with type convert operator 
class Int{
	int data;
	
	public:
		Int(int data):data(data){}
		Int(const Int& i):data(i.data){}
		
		operator int(){ return data; }//type convert operator
};
int main(){
	Int x=3;
	int a=x+4;
	
	x=a+2+x*4;//default assign operator is well working! 
	std::cout<<x<<std::endl;
}//

/*
0.	mutable in const function, explicit in constructor 
1.	WrapperŬ����-Ÿ�� ��ȯ ������_ (operator (type)() ����Ÿ�� ���)
2.	������ �����ε� �� ���� ���� ������(++x, --x)�� operator++(), operator--(). ���� ���� ������(x++, x--)�� operator++(int), operator--(int) 
	���� ������ ���� �ٲ� �ڽ��� �����ϰ�, ���������� ���� �ٲ�� ���� ��ü�� �����Ѵ�. 
	<���� ����> 
	Test& operator++() {
	    x++;
    	std::cout << "���� ���� ������" << std::endl;
    	return *this;//�ٲ�� �� 
  	}
	<���� ����>
	Test operator++(int) {
    	Test temp(*this);
    	x++;
    	std::cout << "���� ���� ������" << std::endl;
    	return temp;//������ �ٲ������ �ʰ� ���纻�� �ְ� ���� �ٲ�� 
  	}
*/

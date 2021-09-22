#include <iostream>

/*1. Wrapper Class with type convert operator 
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
}*/

/*
1.	Wrapper클래스-타입 변환 연산자 
	Int와 똑같이 작동하는 Int객체를 만들면 연산자 존나 오버로딩 해야하니 타입 변환 연산자가 도입된다. (operator (type)() 리턴타입 노노)
	이 객체는 operator연산시 int가 될 수 있는데 이때 data를 리턴한다. 대입 처리는 디폴트가 알아서 
2.	연산자 오버로딩 시 전위 증감 연산자(++x, --x)는 operator++(), operator--(). 후위 증감 연산자(x++, x--)는 operator++(int), operator--(int) 
	전위 증감은 값이 바뀐 자신을 리턴하고, 후위증감은 값이 바뀌기 전의 객체를 리턴한다. 
	<전위 증감> 
	Test& operator++() {
	    x++;
    	std::cout << "전위 증감 연산자" << std::endl;
    	return *this;//바뀐게 들어감 
  	}
	<후위 증감>
	Test operator++(int) {
    	Test temp(*this);
    	x++;
    	std::cout << "후위 증감 연산자" << std::endl;
    	return temp;//들어갔을때 바뀌어있지 않게 복사본을 넣고 값은 바꿔둠 
  	}
*/

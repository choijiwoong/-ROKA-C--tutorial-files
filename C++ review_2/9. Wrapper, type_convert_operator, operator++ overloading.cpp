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
1.	Wrapper클래스-타입 변환 연산자_ (operator (type)() 리턴타입 노노)
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

#include <iostream>
#include <cstring>

using namespace std;

/*[FUNCTION TEMPLATE]_함수를 만드는데 사용되는 템플릿 
template<typename T>//=<class T>, T는 그저 이름 
void Swap(T& num1, T& num2){//자료형 상관없이 다 수행 함. 
	T temp=num1;
	num1=num2;
	num2=temp;
}

int main(){
	int num1=10, num2=40;
	cout<<"before, num1: "<<num1<<", num2: "<<num2<<endl;
	Swap(num1, num2);//물론 명시적으로 표시해도 됨. Swap<int>(num1, num2); 
	cout<<"after, num1: "<<num1<<", num2: "<<num2<<endl;
	
	double num3=15.6, num4=14.44;
	cout<<"before, num3: "<<num3<<", num4: "<<num4<<endl;
	Swap(num1, num2);
	cout<<"after, num3: "<<num3<<", num4: "<<num4<<endl;
	
	return 0;
}
*/

//[CLASS TEMPLATE]_템플릿을 기반으로 만들어진 함수 
template <class Y>//typename 상관 ㄴ 
class Data{
	private:
		Y data;
	public:
		Data(Y data):data(data) {}
		void ShowInfo(){
			cout<<data<<endl;
		}
};

int main(){
	Data<int> data1(50);//TEMPLATE CLASS에서는 자료형 생략 불가. 
	data1.ShowInfo();
	
	Data<char> data2('A');
	data2.ShowInfo();
	
	Data<double> data3(24.337);
	data3.ShowInfo();
	
	return 0;
}

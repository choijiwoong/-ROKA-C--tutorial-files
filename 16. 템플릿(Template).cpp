#include <iostream>
#include <cstring>

using namespace std;

/*[FUNCTION TEMPLATE]_�Լ��� ����µ� ���Ǵ� ���ø� 
template<typename T>//=<class T>, T�� ���� �̸� 
void Swap(T& num1, T& num2){//�ڷ��� ������� �� ���� ��. 
	T temp=num1;
	num1=num2;
	num2=temp;
}

int main(){
	int num1=10, num2=40;
	cout<<"before, num1: "<<num1<<", num2: "<<num2<<endl;
	Swap(num1, num2);//���� ��������� ǥ���ص� ��. Swap<int>(num1, num2); 
	cout<<"after, num1: "<<num1<<", num2: "<<num2<<endl;
	
	double num3=15.6, num4=14.44;
	cout<<"before, num3: "<<num3<<", num4: "<<num4<<endl;
	Swap(num1, num2);
	cout<<"after, num3: "<<num3<<", num4: "<<num4<<endl;
	
	return 0;
}
*/

//[CLASS TEMPLATE]_���ø��� ������� ������� �Լ� 
template <class Y>//typename ��� �� 
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
	Data<int> data1(50);//TEMPLATE CLASS������ �ڷ��� ���� �Ұ�. 
	data1.ShowInfo();
	
	Data<char> data2('A');
	data2.ShowInfo();
	
	Data<double> data3(24.337);
	data3.ShowInfo();
	
	return 0;
}

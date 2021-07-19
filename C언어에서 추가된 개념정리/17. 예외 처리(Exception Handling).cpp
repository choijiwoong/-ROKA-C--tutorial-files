#include <iostream>
#include <cstring>

using namespace std;

/*[EXCEPTION HANDLING]
int main()
{
	int a, b;
	cout << "두 개의 정수를 입력하세요: ";
	cin >> a >> b;
	if (b == 0) // 나누는 수가 0이라면,
		cout << "나누는 수가 0이 될 수 없습니다." << endl;
	else
		cout << a << "를 " << b << "로 나눈 몫은 " << a/b << "입니다." << endl;
	return 0;
}//예외사항을 그냥 따로 뺴주기. div/0 error 단, 이러면 예외가 발생할 때마다 처리를 해야하는 단점
*/ 

/*[TRY~CATCH, THROW]
int main()
{
	int a, b;
	cout << "두 개의 정수를 입력하세요: ";
	cin >> a >> b;
	
	try {
		if (b == 0) throw b;
		cout << a << "를 " << b << "로 나눈 몫은 " << a/b << "입니다." << endl;
	} 
	catch (int exception) {
		cout << "예외 발생, 나누는 수는 " << exception << "가 될 수 없습니다." << endl;
	}
	
	return 0;
}
*/

/*[FUNCTION EXCEPTION HANDLING]
void func(int a, int b)
{
	if (b == 0) throw b;//func내부에 catch가 없으면 호출된 곳으로 
	cout << a << "를 " << b << "로 나눈 몫은 " << a/b << "입니다." << endl;
}

int main()
{
	int a, b;
	cout << "두 개의 정수를 입력하세요: ";
	cin >> a >> b;
	try {
		func(a, b);//뿅 가서 아래 catch에 전달 
	} catch (int exception) {
		cout << "예외 발생, 나누는 수는 " << b << "가 될 수 없습니다." << endl;
	}
	
	return 0;
}

*/

//[STACK UNWINDING]_위와 같이 예외가 호출된 영역을 타고 계속 전달되는 현상 
	void func1() { throw 0; }
	void func2() { func1(); }
	void func3() { func2(); }
	void func4() { func3(); }

int main()
{
	try {
		func4();
	} catch (int exception) {
		cout << "예외 발생, " << exception << "!" << endl;
	}
	
	return 0;
}



#include <iostream>
#include <cstring>

using namespace std;

/*[EXCEPTION HANDLING]
int main()
{
	int a, b;
	cout << "�� ���� ������ �Է��ϼ���: ";
	cin >> a >> b;
	if (b == 0) // ������ ���� 0�̶��,
		cout << "������ ���� 0�� �� �� �����ϴ�." << endl;
	else
		cout << a << "�� " << b << "�� ���� ���� " << a/b << "�Դϴ�." << endl;
	return 0;
}//���ܻ����� �׳� ���� ���ֱ�. div/0 error ��, �̷��� ���ܰ� �߻��� ������ ó���� �ؾ��ϴ� ����
*/ 

/*[TRY~CATCH, THROW]
int main()
{
	int a, b;
	cout << "�� ���� ������ �Է��ϼ���: ";
	cin >> a >> b;
	
	try {
		if (b == 0) throw b;
		cout << a << "�� " << b << "�� ���� ���� " << a/b << "�Դϴ�." << endl;
	} 
	catch (int exception) {
		cout << "���� �߻�, ������ ���� " << exception << "�� �� �� �����ϴ�." << endl;
	}
	
	return 0;
}
*/

/*[FUNCTION EXCEPTION HANDLING]
void func(int a, int b)
{
	if (b == 0) throw b;//func���ο� catch�� ������ ȣ��� ������ 
	cout << a << "�� " << b << "�� ���� ���� " << a/b << "�Դϴ�." << endl;
}

int main()
{
	int a, b;
	cout << "�� ���� ������ �Է��ϼ���: ";
	cin >> a >> b;
	try {
		func(a, b);//�� ���� �Ʒ� catch�� ���� 
	} catch (int exception) {
		cout << "���� �߻�, ������ ���� " << b << "�� �� �� �����ϴ�." << endl;
	}
	
	return 0;
}

*/

//[STACK UNWINDING]_���� ���� ���ܰ� ȣ��� ������ Ÿ�� ��� ���޵Ǵ� ���� 
	void func1() { throw 0; }
	void func2() { func1(); }
	void func3() { func2(); }
	void func4() { func3(); }

int main()
{
	try {
		func4();
	} catch (int exception) {
		cout << "���� �߻�, " << exception << "!" << endl;
	}
	
	return 0;
}



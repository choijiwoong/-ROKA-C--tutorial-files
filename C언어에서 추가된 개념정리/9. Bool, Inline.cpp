/*[BOOL]
#include <iostream>

using namespace std;

int main(){
	//bool �� ����� Ȯ�� 
	cout<<true<<endl<<false<<endl;
	
	//bool�� size Ȯ��
	cout<<"sizeof true: "<<sizeof true<<endl;
	cout<<"sizeof false: "<<sizeof false<<endl; 
	
	//bool�� Ȱ��
	int a, b;
	bool isMax;
	
	cin >>a>>b;
	
	if (a>b) isMax=true;
	else isMax=false;
	
	cout<<"isMax: "<<isMax<<endl; 
	
	return 0;
}
*/

//[INLINE]_������ �Լ� ���ǰ���, �ӵ� ����, �ڷ����� ���� X 
#include <iostream>
#define PI 3.141592
//#define CU(X) ((X)*(X)*(X))

using namespace std;

inline int CU(int x){//�ζ��� �Լ� ����Ͽ� ó��. but �ڷ��������� �Ҽ� �� ����. 
	return x*x*x;
}

int main(){
	cout<<PI<<endl;
	cout<<CU(7.1)<<endl;
	
	return 0;
}

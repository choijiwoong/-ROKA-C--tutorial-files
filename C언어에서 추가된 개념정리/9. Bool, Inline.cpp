/*[BOOL]
#include <iostream>

using namespace std;

int main(){
	//bool 의 출력형 확인 
	cout<<true<<endl<<false<<endl;
	
	//bool의 size 확인
	cout<<"sizeof true: "<<sizeof true<<endl;
	cout<<"sizeof false: "<<sizeof false<<endl; 
	
	//bool의 활용
	int a, b;
	bool isMax;
	
	cin >>a>>b;
	
	if (a>b) isMax=true;
	else isMax=false;
	
	cout<<"isMax: "<<isMax<<endl; 
	
	return 0;
}
*/

//[INLINE]_간단한 함수 정의가능, 속도 빠름, 자료형에 영향 X 
#include <iostream>
#define PI 3.141592
//#define CU(X) ((X)*(X)*(X))

using namespace std;

inline int CU(int x){//인라인 함수 사용하여 처리. but 자료형때문에 소수 값 버림. 
	return x*x*x;
}

int main(){
	cout<<PI<<endl;
	cout<<CU(7.1)<<endl;
	
	return 0;
}

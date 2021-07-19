/*[REFERENCE]
#include <iostream>

using namespace std;

int main()
{
	int num=50;
	int &num1=num;
	int &num2=num;
	int &num3=num2;
	
	cout<<"num: "<<&num<<endl;
	cout<<"num1: "<<&num1<<endl;
	cout<<"num2: "<<&num2<<endl;
	cout<<"num3: "<<&num3<<endl;
	
	return 0;
}
*/

//[CALL BY REFERENCE WITH REFERENCE]
#include <iostream>

using namespace std;

void Swap(int &ref1, int &ref2){
	int temp=ref1;
	ref1=ref2;
	ref2=temp;
}

int main(){
	int a=50, b=40;
	
	cout<<"swap before, a: "<<a<<"b: "<<b<<endl;
	Swap(a,b);
	cout<<"swap after, a: "<<a<<"b: "<<b<<endl;
	
	return 0;
}

//[FRIEND]
#include <iostream>

using namespace std;

class B;

class A{
	private:
		int adata;
	public:
		A(int _data){
			adata=_data;
		}
		void ShowData(B b);
		friend class B;//A->B직접 접근 가능 
};

class B{
	private:
		int bdata;
	public:
		B(int _data){
			bdata=_data;
		}
		void ShowData(A a){
			cout<<"a.data: "<<a.adata<<endl;
		}
		friend class A;//B->A직접 접근 가능 
};

void A::ShowData(B b) {
cout<<"b.data: "<<b.bdata<<endl;
}

int main(){
	A a(10);
	B b(20);
	
	a.ShowData(b);//A a의 showdata함수로 b를 봄 
	b.ShowData(a);//이하동문 
	
	return 0;
}//friend를 쓰면 함수 간 private, public의 정보은닉이 깨져 많은 사용은 문제를 불러온다. 자제할 것. 

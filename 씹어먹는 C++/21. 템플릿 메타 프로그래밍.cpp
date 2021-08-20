#include <iostream>
#include <typeinfo>
//�������� ������� ��� ��Ģ������� �������ڸ� �Ʒ��� �����ϴ�.
/*0
template <typename T, unsigned int N>//get type, uint by template argument.
class Array{
	T data[N];//database
	
	public:
		Array(T (&arr)[N]){//array constructor. &arr get array, define size as N(unsigned int) and type is T in template argument.
			for(int i=0; i<N; i++)//for all data in array,
				data[i]=arr[i];//copy to data.
		}
		
		T* get_array(){//return data pointer
			return data;
		}
		
		unsigned int size(){//return size
			return N;
		}
		
		void print_all(){
			for(int i=0; i<N-1; i++)
				std::cout<<data[i]<<", ";
			std::cout<<data[N-1]<<std::endl;
		}
};

int main(){
	int arr[3]={1,2,3};
	
	Array<int, 3> arr_w(arr);
	arr_w.print_all();
	
	//is Array<int, 5> is same class? of coursely, different because template instansiate by different template argument. we can check it by #include <typeinfo>
	std::cout<<(typeid(Array<int, 3>)==typeid(Array<int, 5>))<<std::endl; 
}*/

/*0
template <int N>
struct Int{
	static const int num=N;
};

template <typename T, typename U>
struct add{//add part
	typedef Int<T::num+U::num> result;//two type's argument's num + and make new Int object that has typename result.
};

int main(){
	typedef Int<1> one;
	typedef Int<2> two;
	
	typedef add<one, two>::result three;
	
	std::cout<<"Addition result : "<<three::num<<std::endl;//* add work is in compile time. In runtime, just show that result.
}*/

/*1
//factorial calculation in compile time
template <int N>
struct Factorial{
	static const int result=N*Factorial<N-1>::result;//not finish define 'static const int result'! it's stil defining in compile time.
}; 

template<>//like n==1 exception of recursive function
struct Factorial<1>{//n=1 in template. template specialization.
	static const int result=1;
};

int main(){
	std::cout<<"6! = 1*2*3*4*5*5 = "<<Factorial<6>::result<<std::endl;//there are no object that has value'720'! 720 value is just point type 'Factorial<6>'
}*/

int gcd(int a, int b){//normal way
	if(b==0)
		return a;
	return gcd(b, a%b);
} 

template <int X, int Y>//TMP way
struct GCD{
	static const int value=GCD<Y, X%Y>::value;
};
template <int X>
struct GCD<X, 0>{
	static const int value=X;
};
/*previoud Ratio & add
template <int N, int D=1>
struct Ratio{//Ratio means rational number
	typedef Ratio<N, D> type;//point self (like 'this' keyword in class)
	static const int num=N;//numerator of fraction
	static const int den=D;//denominator of fraction
};

template <class R1, class R2>
struct _Ratio_add{//radio add part
	typedef Ratio<R1::num*R2::den + R2::num*R1::den, R1::den*R2::den> type;
};
template <class R1, class R2>
struct Ratio_add:_Ratio_add<R1, R2>::type {};//just make type that is already added. ???
*/
template <int N, int D=1>
struct Ratio{
	private:
		const static int _gcd=GCD<N, D>::value;
		
	public:
		typedef Ratio<N/_gcd, D/_gcd> type;
		static const int num=N/_gcd;
		static const int den=D/_gcd;
};
template <class R1, class R2>
struct _Ratio_add{
	using type=Ratio<R1::num*R2::den+R2::num*R1::den, R1::den*R2::den>;
};

template <class R1, class R2>
struct Ratio_add:_Ratio_add<R1, R2>::type {};//���� 


int main(){
	std::cout<<"gcd (36, 24) :: "<<GCD<26, 24>::value<<std::endl;
	
	using rat=Ratio<2, 3>;//typedef Ratio<2, 3> rat;
	using rat2=Ratio<3, 2>;//typedef Ratio<3, 2> rat2;
	using rat3=Ratio_add<rat, rat2>;//typedef Ratio_add<rat, rat2> rat3;
	std::cout<<rat3::num<<" / "<<rat3::den<<std::endl;//not making Ratio class's object! just compiler makes new types.
	
	return 0;
}


/*
[0.	���⿡ �ռ�]
1.	���� ����ó�� ���ø��� ���Ͽ� Ÿ���� ��ġ ���� �ΰ� ó�� ����ϴ� ���� �Ϲ�ȭ ���α׷���(generic programming)Ȥ�� �׳� ���ʸ� ���α׷����̶�� �θ���.
2.	���ø� ���ڷδ� Ÿ�� �Ӹ� �ƴ϶� Ư���� ������ �����ϴ� ���鵵 �� �� �ִµ�, ������ std::array�� ��� �����Ǿ������� ���� ������. 
3.	�� �ڵ�ó�� �迭�� ���δ� wrapper Ŭ������ ���� ��ġ �迭ó�� ����Ѵٸ�, �迭�� ����ϸ� �߻��ϴ� ���� �������� ���� �ذ��� �� �ְ� �ȴ�.
	�������, �Ϲ� �迭�� ��� �迭 ������ �Ѿ�� �� �� ������, �� ArrayŬ������ index ������ �Ѿ���� ���� �˷��� �� �ֱ� �����̴�.
4.	�ٽø���, ������ ����Ǵ� �ñ�� ������Ÿ���̰�, ��Ÿ�� �ÿ��� �ܼ��� �� ����� �����ش�.

[1.	���ø� ��Ÿ ���α׷���(Template Meta Programming-TMP)]
1.	���ø� ������, ������ �˰��ִ� Ÿ���� ��� ���� ������ �ʾ�����, �ٷ� �� �������� ���ؼ� ���ø��� ����Ͽ� Ÿ�Կ� ��� ���� �ο��ϰ�, �� ������ ������ �� �� �ִٴ� ���� ���Ҵ�.
	����, Ÿ���� �ݵ�� ������ Ÿ�ӿ� Ȯ���Ǿ�� �ϹǷ�, ������ Ÿ�ӿ� ��� ������� ������ �Ǵµ� 
	 �̷��� Ÿ���� ������ ������ Ÿ�ӿ� �����Ǵ� �ڵ�� ���α׷����� �ϴ� ���� ��Ÿ ���α׷���(meta programming)�̶�� �ϰ�, 
	C++�� ��� ���ø��� ������ �̷��� �۾��� �ϱ� ������ ���ø� ��Ÿ ���α׷���, �ٿ��� TMP��� �θ���.
2.	���ø����δ� for���� �� �� ���⿡ ����� ������ ����Ѵ�. ������ �ݴ��, for������ ������ �� �ִ� ��� �ڵ�� �Ȱ��� ���ø� ��Ÿ ���α׷����� �̿��Ͽ� ������ �� �ְ�, 
	if�� ���� ���� ���ø� Ư��ȭ�� ���� TMP�� ������ �� �ִ�. 
	
[2. TMP�� �� ���°�?]
1.	��� ��� C++�ڵ�� ���ø� ��Ÿ ���α׷��� �ڵ�� ��ȯ�� �� �ִ�. �̴� ������ Ÿ�ӿ� ��� ������ ������ ������ ������ �ð��� ��û �þ������, ���α׷� ���� �ӵ��� ��� ��ų �� �ִٴ� ������ �ִ�.
	 ��, ���ø� ��Ÿ ���α׷����� �ſ� �����ϱ⿡ ���α׷� ��ü�� �����ϴ� ���� ����. ����, ������ Ÿ�ӿ� �����ϴ� ���̱⿡ ������� �Ұ����ϰ�, C++�����Ϸ� Ư�� �� ���ø� ���� �ÿ� ��û�� ������ ������ ���ձ⿡ TMP�� �ۼ��� �ڵ��� ���׸� ã�� ���� �ſ� �����.
2.	�׷��⿡ TMP�� �̿��ϴ� ���� �ϳ� ������������, Boost ���̺귯���� ������ ���� C++���̺귯�� ���� TMP�� �̿��Ͽ� �����Ǿ���, �̸� ���Ͽ� ������ Ÿ�ӿ� ���� �������� ��Ƴ� ���� �ְ�(������ ��ȭ ��ġ ���� ���),  
	�ӵ��� �ſ� �߿��� ���α׷��� ��� TMP�� ���Ͽ� ��Ÿ�� �ӵ��� ����ų �� �ִ�. 
3.	C++11���� typedef ��ſ� using�̶�� Ű���带 ����� �� �ִ�.
	typedef Ratio_add<rat, rat2> rat3; == using rat2=Ratio_add<rat, rat2>;
4.	Ư�� �Լ� �������� ��� typedef void (*func)(int, int);ó�� ����ؾ� ������, using���δ� using func=void (*)(int int);ó�� ���������� ��Ÿ�� �� �ִ�. 
*/

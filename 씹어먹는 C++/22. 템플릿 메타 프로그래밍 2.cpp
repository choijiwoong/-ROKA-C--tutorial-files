#include <iostream>

/*1
bool is_prime(int N){//normal function
	if(N==2) return true;
	if(N==3) return true;
	
	for(int i=2; i<=N/2; i++)
		if(N%i==0) return false;
		
	return true;
}//transfer this to TMP!

template <>//template specialization of 2
struct is_prime<2>{
	static const bool result=true;
};

template<>
struct is_prime<3>{//template specialization of 3
	static const bool result=true;
};

template <int N>//get bool value bu check_div
struct is_prime{
	static const bool result=!check_div<n, 2>::result;
};

template <int N, int d>
struct check_div{
	static const bool result=(N%d==0)||check_div<N, d+1>::result;//recursive structure
};

template <int N>//At this, error occur. template specialization must use template <> but, if then, we can't express <N, N/2> without template <int N>. So make N to type!
struct check_div<N, N/2>{//stop condition
	static const bool result=(N%(N/2)==0);
};*/



/*1
template <int N>
struct INT{
	static const int num=N;
};
template <typename a, typename b>
struct add{
	typedef INT<a::num+b::num> result;
};

template <typename a, typename b>
struct divide{
	typedef INT<a::num / b::num> result;
};

using one=INT<1>;
using two=INT<2>;
using three=INT<3>;

template <typename N, typename d>
struct check_div{
	static const bool result=(N::num%d::num==0)||check_div<N, typename add<d, one>::result>::result;//recursive structure with add<d, one>
};

template <typename N>//use like is_prime<INT<11>>::result but for convenience, change to use like is_prime<11>::result
struct _is_prime{
	static const bool result=!check_div<N, two>::result;//judge by check_div. 
};

template <>
struct _is_prime<two>{//template specialization
	static const bool result=true;
};
template<>
struct _is_prime<three>{
	static const bool result=true;
};

temaplate <typename N>//depending on N!
struct check_div<N, typename divide<N, two>::result>{//error occur! we think result as type ofcoursely. But in compiler aspect, it must decide that this result is type or value.
	static const bool result=(N::num%(N::num/2)==0);//So, for completely read upper command we show "result must be type" by adding 'typename' keyword 
};//check_div's result is static const bool(value), so it doesn't need typename. 

template <int N>
struct is_prime{
	static const bool result=_is_prime<INT<N>>::result;
};

int main(){
	std::cout<<std::boolalpha;
	std::cout<<"Is 2 prime? :: "<<is_prime<2>::result<<std::endl;//true
	std::cout<<"Is 10 prime? :: "<<is_prime<10>::result<<std::endl;//false
	std::cout<<"Is 11 prime? :: "<<is_prime<11>::result<<std::endl;//true
	std::cout<<"Is 61 prime? :: "<<is_prime<61>::result<<std::endl;//true
}*/



//GCD define
template <int X, int Y>
struct GCD{
	static const int value=GCD<Y, X%Y>::value;
};
template <int X>
struct GCD<X, 0>{//escape
	static const int value=X;
};
//Ratio define
template <int N, int D=1>//N/D structure for expression of denominator and numerator of fraction.
struct Ratio{
	const static int _gcd=GCD<N, D>::value;//tool for abbreviation
	
	public:
		typedef Ratio<N/_gcd, D/_gcd> type;
		static const int num=N/_gcd;
		static const int den=D/_gcd;
};
//calculation part of Ratio
template <class R1, class R2>//add define
struct _Ratio_add{
	using type=Ratio<R1::num*R2::den+R2::num*R1::den, R1::den*R2::den;
};
template <class R1, class R2>//for simplization of add
struct Ratio_add:_Ratio_add<R1, R2>::type{};

template <class R1, class R2>//subtract define
struct _Ratio_subtract{
	using type=Ratio<R1::num*R2::den-R2::num*R1::den. R1::den*R2::den;
};
template <class R1, class R2>//for simplization of subtract
struct Ratio_subtract: _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>//multiply define
struct _Ratio_multiply{
	using type=Ratio<R1::num*R2::num, R1::den*R2::den>;
};
template <class R1, class R2>//for simplization of multiply
struct Ratio_multiply:_Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>//divide define
struct _Ratio_divide{
	using type=Ratio<R1::num*R2::den, R1::den*R2::num>;
};
template <class R1, class R2>//for simplization of divide
struct Ratio_divide:_Ratio_divide<R1, R2>::type {};

//Dim define
template <typename U, typename V, typename W>//for express unit. get type by argument. so not Dim<1, 1, -2>, Dim<Ratio<1,1>, Ratio<1,1>, Ratio<-2,1>>
struct Dim{//for simplization just 3 element(normal 8 elements are needed)
	using M=U;//Mass(kg)
	using L=V;//Length(meter)
	using T=W;//Time(second)
	
	using type=Dim<M, L, T>;//like point self
};
//calculation part of Dim
template <typename U, typename V>//+ & - calculation
struct add_dim_{//Dim add define
	typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,//dependent type.
			    typename Ratio_add<typename U::L, typename V::L>::type,
			    typename Ratio_add<typename U::T, typename V::T>::type>
			type;//simplization of add of Dim
};
template <typename U, typename V>
struct subtract_dim_{//Dim subtract define
	typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
			    typename Ratio_subtract<typename U::L, typename V::L>::type,
			    typename Ratio_subtract<typename U::T, typename V::T>::type>
			type;//simplizatino of subtract of Dim
};

//quantity define for data+unit
template <typename T, typename D>//data, dim
struct quantity{//class that save real data.
	T q;//data is q that has t type.
	using dim_type=D;//dimention information
	
	//for operator overload
	quantity operator+(quantity<T, D> quant) {//input data with quantity<T,D> type in operator+()function define name to quant 
		return quantity<T, D>(q+quant.q);//q and quant's q add operation. return quantity object that has q+quant.q. than constructor get that key and set q+quant.q as new q value.
	}//quantity's data type must be same Dim type for instantiation.
	quantity operator-(quantity<T, D> quant) {	
		return quantity<T, D>(q-quant.q);	
	}//if types are different, compiler make error that can't find operator+ because of no instantiation.
	//if D is different in operator+ & - overloading work, compiler makes error in return part because quantity<T, D1> is different type of quantity<T, D2>. cannot save data regardless of q+quant.t
	
	//operator overload of * & / is mush hard than overload of + & - because it can calculate regardless of Dim! just new Dim data occur.(ex. for acceleration just do meter/(second*second)
	//so * and / can work ragardless of Dim!
	template <typename D2>//for * operation of quantity
	quantity<T, typename add_dim_<D, D1>::type> operator*(quantity<T, D2> quant){//* operation with quantity<T, D2> as quant object
		return quantity<T, typename add_dim_<D, D2>::type(q*quant.q);//(both type is same to T! if not error)add dim and set data to q*quant.q by using Constructor
	}//and return type copy to infront of operator* keyword as return type.
	template <typename D2>//for / operation of quantity
	quantity<T, typename subtract_dim_<D, D2>::type> operator/(quantity<T, D2> quant){//algorithm is same to operator*
		return quantity<T, typename subtract_dim_<D, D2>::type>(q/quant.q);
	}
	//for exception scalar input like '3*kg' that is no demention normally.
	quantity<T, D> operator*(T scalar){	return quantity<T,D>(q*scalar);}
	quantity<T, D> operator/(T scalar){	return quantity<T,D>(q/scalar);}
	}
	
	//constructor
	quantity(T q):q(q){}
};

//print quantity to ostream for convenience
template <typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q){
	out<<q.q<<"kg^"<<D::M::num/D::M::den<<"m^"<<D::L::num/D::L::den<<"s^"<<D::T::num/D::T::den;
	return out;
}


int main(){
	using one=Ratio<1, 1>;
	using zero=Ratio<0, 1>;
	
	quantity<double, Dim<one, xero, xero>> kg(1);//data: double 1, dim_type Mass(kg)
	quantity<double, Dim<zero, one, zero>> meter(1);
	quantity<double, Dim<zero, zero, one>> second(1);
	
	//good
	//kg+kg;
	
	//bad
	//kg+meter;
	//error occur
	//no opertor "+" matches these operands
	//binary '+': no operator founs which takes a right-hand operand of type
	//'quantity<double, Dim<zero, one, zero>>' (or there is no acceptable conversion)
	
	auto F=kg*meter/(second*second); //what type will be get F? F's dim is <Ratio<1, 1>, Ratio<1, 1>, Ratio<-2,1>>.
	//So, F get 'quantity<double, Dim<one, one, Ratio<-1,1>>> F=kg*meter/(second*second);
	//it's so annoying when we define variables. and compiler already know what type pop of F.
	//So actually, we don't have to write that dirty type. so make compiler smart to think that type by self.
	std::cout<<"2 kg ��ü�� 3m/s^2�� ���ӵ��� �б� ���� ���� ũ���? "<<F<<std::endl;
}

/*for understanding of auto keyword
#include <typeinfo>

int sum(int a, int b){
	return a+b;
} 

class SomeClass{
	int data;
	
	public:
		SomeClass(int d):data(d){}
		SomeClass(const SomeClass& s):data(s.data){}
};

int main(){
	auto c=sum(1,2);//compiler can guess int by return type of function.
	auto num=1.0+2.0;//can guess double
	
	SomeClass some(10);
	auto some2=some;
	
	auto some3(10);//whether compiler makes SomeClass object? Compiler guess very simply, just make int variable.
	//auto's guessing way is same to template type's guessing way.
	//but like 'auto F=kg*meter/(second*second), compiler can guess type completely, we can use auto keyword.
	
	std::cout<<"C's type :: "<<typeid(c).name()<<std::endl;
	std::cout<<"num's type :: "<<typeid(num).name()<<std::endl;
	std::cout<<"some2's type :: "<<typeid(some2).name()<<std::endl;
	std::cout<<"some3's type :: "<<typeid(some3).name()<<std::endl;
}*/


/*
�����Ϸ� Tools->compiler option->add��¼��->-std=c++14 �̰ɸ����ٴ�!!!������!! 

[1.	���� ���� �����غ��� ����(TMP�� ����Ͽ� � ���� �Ҽ����� �ƴ����� �Ǻ��ϴ� ���α׷��� ������)]
1.	�����Ϸ��� ������ ��� �ĺ���(���� �̸��̵� �Լ� �̸��̵� �ڵ� ���� �̸���)�� ������ �� �� �ĺ��ڰ� '��'���� 'Ÿ��'������ �����ؾ� �Ѵ�.
	������� Ŭ������ ���� func�Լ��� Ư��ȭ �Ѵٸ�, T::t* p;�� Ŭ������ t�� p�� ���ϴ� ������ �ؼ��� ������,
	� �Լ��� Ŭ���������� Ư��ȭ �Ѵٸ� T::t* p;�� ������ p�� �����ϴ� ���� �Ǳ� �����̴�.
	��� �� �λ�Ȳ�� �����Ϸ��� ��Ȯ�ϰ� �����ϰ��ϱ� ���� T::t�� Ÿ������ �������� ��Ȯ�ϰ� �˷���߸� �Ѵ�.
	 ���� result���� 'Ÿ��'���� '��'������ �����ؾ��ϴµ�, ����
	template <>
	struct divide<int a, int b>{
		const static int result=a+b;
	};
	�̷� ���ø��� ���ǵ��ְ� ���� N�� two�� �׳� int���̶�� result�� static const intŸ���� '��'�� �ȴ�.
	 ��ó�� ���ø� ���ڿ� ���� ��� Ÿ���� �޶��� �� �ִ� ���� ���� Ÿ��(dependent type)�̶�� ������.
	���� ��� result�� N�� �����ϱ� ������ ����Ÿ���̴�. 
	 ������ Ÿ���̶�� �����ϴ� ����� �տ� typenameŰ���带 �ٿ��ָ� �ȴ�. ���� ���� �����Ϸ��� � �ĺ��ڸ� ���� �� default�� ���̶�� �����ϱ⿡ �׳� �Ⱥٿ��ָ� �ȴ�. 
2.	����� �����Ϸ��� ���� ��������� �� �� ��� �������� ���̰� �������ֱ� ������, �� ū ���� �ִ´ٸ� ������ ������ �߻��� ���� �ִ�. 
3.	���������� ���� ���¿��� RatioŬ������ �� ���� TMP�� ��������� �˾ư�����. TMP�� ��¥ �Ŀ�

[2.	����(Unit) ���̺귯��]
1.	C++ �ڵ带 �ۼ��ϴ� ���� �� �ϳ��� �ΰ������� �˵��� ����Ѵٴ���, ������ ��� ����Ѵٴ��� � �ʿ��� ���� ��ġ ����� �ִ�.  
	�̷��� ������ ��ġ ��꿡 �ʿ��� ���� kg, m, s���� �����ε�, �̷��� �͵��� ����ϴ� ���α׷����� ���, double�̳� float������ ���� ������ '����'�� �پ �� ���̴�.
	float v;//�ӵ�  m/s
	float a;//���ӵ� m/s^2
	std::cout<<v+a;
	�� ���, v+a�� �и��� �Ұ����� ����������, C++�����Ϸ� ���忡���� �׳� �� ���� float������ ���� ���̱⿡ �������� ������ �ȴ�.
2.	�̷��� �Ǽ��� ���� ���ؼ� 1�������� ������ Ŭ������ ���� ������ ���� �����ϴ� ���̴�. operator������ �����ڵ��� �����ε��ϰ�, �����ڰ� �ٸ����� ������ ó���ϸ� �ȴ�.
	������, ���� Ʋ�� ������ ������ �ڵ尡 �ſ� �幰�� ��Ÿ���ٸ�, �� ��Ÿ�ӿ��� �� ������ �߰����� ���� ä �Ѿ �� �ִٴ� ������ �ִ�.
	 ���, �ƿ� ������ �ٸ��� �����Ͻÿ� ������ �߻����ѹ����� ���� �̻����̴�. 

[3. Ÿ���� �˾Ƽ� �����ض�! '-auto' Ű����]
1.	��ü�� ������ ��, ���� ��� ���� Ÿ���� ���� �ʾƵ��˾Ƽ� ������ �� �ִ� ������ ���� �ִ�.
	(??) a=3;
	some_class a;
	(??) b=a;
	��ü�� ��������� �� �� ���� �����ϴ� ����� Ÿ���� Ȯ���� �� �� �ִٸ�, ���� ������� �ʾƵ� �����Ϸ��� �� ���ִ�.
	���� ���ܻ����� �ִµ�, ���� �����ڵ忡���� ����
	quantity<double, Dim<one, zero, zero>> kg(1);
	���� ���� Ÿ���� ������ (??) kg(1);�� ��� �����Ϸ� ���忡���� �׳� 1�� �ʱ�ȭ�ϴ� �����̹Ƿ� int�� ������ ���̴�. �ݸ鿡,
	(??) F=kg*meter/(second*second)������ ���� Ÿ���� ���� �ʾƵ� �����Ϸ��� �������� ������ ���ؼ� F�� Ÿ���� ��Ȯ�ϰ� �˾Ƴ� �� �ִ�.
	 ��ó�� �����Ϸ��� Ÿ���� ��Ȯ�� �˾Ƴ� �� �ִ� ��� ���� �� ��� �� Ÿ���� �����ʰ� auto�� ǥ���� �� �ִ�. 
2.	ª�� �̸��� Ÿ���� ��� �׳� ���� ���� ���������鿡�� ������, ��ó�� ������ Ÿ���� �̸��� ���, �� Ÿ���� ���� ������ �� �ִٸ� autoŰ���带 Ȱ���ϴ� �͵� ����.
3.	��� ���ø� ��Ÿ���α׷����� ��� TMPƯ���� �����ϰ�, �Ӹ��� ���� ��ߵǰ�, ������� ����⿡ �������� ����ϴ� ���� �״��� ���� �ʴ�.
	������ UnitŬ���� ó�� TMP�� ������ Ȱ���ϸ� ��Ÿ�ӿ��� ã�ƾ� �ϴ� ������ ������ Ÿ�ӿ��� �̸� ���� �� �ְ�, ��Ÿ�� �� �����ϴ� ����鵵 �Ϻ� ������ Ÿ������ �ű� �� �ִ�.
	���� TMP�� �ۼ��� ���� ���� �� ���� ���� �����ϱ� ���� boost::MPL���̺귯���� �־� ���� ���� © �� ���� ���̴�. 
*/

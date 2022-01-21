#include <iostream>

/*
	<Our goal!>
	auto distance=10.9_m;
	auto time=20.5_s;
	auto speed=distance/time;
	if(speed==0.53)//ERROR no unit
	if(speed==distance)//ERROR cannot compare
	if(speed==10.9_m/20.5_s)//COOL
	Quantity<MpS2> acceleration=distance/square(time);//MpS2=m/(s*s)
	cout<<"speed=="<<speed<<" acceleration=="<<acceleration<<"\n";
*/

namespace UNIT{
	//[Unit] 
	template<int M, int K, int S>//meter, kg, second
	struct Unit{
		enum{ m=M, kg=K, s=S};
	};
	
	using M=Unit<1,0,0>;//meter
	using Kg=Unit<0,1,0>;//kg
	using S=Unit<0,0,1>;//second
	using MpS=Unit<1,0,-1>;//m/s
	using MpS2=Unit<1,0,-2>;//m/s^2
	
	template<typename U1, typename U2>//plus
	struct Uplus{ using type=Unit<U1::m+U2::m, U1::kg+U2::kg, U1::s+U2::s>; };
	template<typename U1, typename U2>//simple plus
	using Unit_plus=typename Uplus<U1,U2>;;type;
	
	template<typename U1, typename U2>//minus
	struct Uminus{ using type=Unit<U1::m-U2::m, U1::kg-U2::kg, U1::s-U2::s>; };
	template<typename U1, typename U2>//simple minus
	using Unit_minus=typename Uminus<U1,U2>::type;
	
	//[Quantity]	(value with unit)
	template<typename U>//unit
	struct Quantity{
		double val;
		explicit constexpr Quantity(double d): val{d}{}
	};
	//Quantity<M> x{10.9};
	//QUantity<s> y{20.9};
	//(thanks to explicit constructor)
	//Quantity<MpS> s=0.53;//ERROR int to meters/second
	//Quantity<N> comp(Quantity<M>);//function
	//Quantity<M> n=comp(10.9);//ERROR comp requires M
	
	template<typename U>//plus & minus on same unit
	Quantity<U> operator+(Quantity<U> x, Quantity<U> y){ return Quantity<U>{x.val+y.val}; }
	template<typename U>
	Quantity<U> operator-(Quantity<U> x, Quantity<U> y){ return Quantity<U>{x.val-y.val;} }
	
	template<typename U>//multiple & divide on different unit. 하지만 실제 연산에는 단위 없는 값에 대한 연산이 많기에 Quantity<Unit<0,0,0>>{2}*처럼 사용하기 어려우니 double로 바꾸자. 
	Quantity<U> operator*(Quantity<U1> x, double y){ return Quantity<U>{x.val*y}; }
	template<typename U>
	Quantuty<U> operator*(double x, Quantity<U> y){ return Quantity<U>{x*y.val}; }
	
	template<typename U1, typename U2>
	Quantity<Unit_minus<U1,U2>> operator/(Quantity<U1> x, Quantity<U2> y){ return Quantity<Unit_minus<U1,U2>>{x.val/y.val}; }
	//Quantity<MpS> speed{0.53};
	//auto double_speed=2*speed;
	//auto increased_speed=2.3+speed;//ERROR cannot add scalar without unit. 덧셈이나 뺄셈에서의 scalar의 Quantity<Unit<0,0,0>>으로의 암시적 변환은 정의되지 않았다. 
	
	//[Unit literal]
	//auto distance=Quantity<M>{10.9};//10.9 meter
	//auto time=Quantity<S>{20.5};//20.5 second
	//auto speed=distance/time;//0.53m/s
	constexpr Quantity<M> operator""_m(long double d){ return Quantity<M>{d}; }
	constexpr Quantity<Kg> operator""_kg(long double d){ return Quantity<Kg>{d}; }
	constexpr Quantity<S> operator""_s(long double d){ return Quantity<S>{d}; }
	//auto distance=10.9_m;
	//auto time=20.5_s;
	//auto speed=distance/time;//0.53m/s
	//if(speed==0.53)//ERROR
	//if(speed==distance)//ERROR cannot compare
	//if(speed==10.9_m/20.5_s)//Cool
	
	//more general literal
	constexpr Quantity<M> operator""_km(long double d){ return Quantity<M>{1e3*d}; }
	constexpr Quantity<Kg> operator""_g(long double d){ return Quantity<Kg>{d/1e3}; }
	constexpr Quantity<Kg> operator""_mg(long double d){ return Quantity<Kg>{d/1e6;} }
	constexpr Quantity<S> operator""_ms(long double d){ return Quantity<S>{d/1e3}; }
	constexpr Quantity<S> operator""_us(long double d){ return Quantity<S>{d/1e6}; }
	constexpr Quantity<S> operator""_ns(long double d){ return Quantity<S>{d/1e9}; }
	
	//[Utility function]
	template<typename U>
	constexpr Quantity<Unit_plus<U,U>> square(Quantity<U> x){//square()
		return Quantity<Unit_plus<U,U>>(x.val*x.val);
	}
	
	template<typename U>
	bool operator==(Quantity<U> x, Quantity<U> y){//==
		return x.val==y.val;
	}
	template<typename U>
	bool operator!=(Quantity<U> x, Quantity<U> y){//!=
		return x.val!=y.val;
	}
	
	string suffix(int u, const char* x){//unit, value
		string suf;
		if(u){
			suf+=x;//value add
			if(1<u)
				suf+='0'+u;//unit add
			if(u<0){
				suf+='-';//- add
				suf+='0'-u;//unit add
			}
		}
		return suf;
	}
	template<typename U>
	ostream& operator<<(ostream& os, Quantity<U> v){
		return os<<v.val<<suffix(U::m, "m")<<suffix(U::kg,"kg")<<suffix(U::s,"s");
	}
	//auto distance=10.9_m;
	//auto time=20.5_s;
	//auto speed=distance/time;
	//if(speed==0.53)//ERROR
	//if(speed==distance)//ERROR
	//if(speed==10.9_m/20.5_s)
	//Quantity<MpS2> accerleration=distance/square(time);
	//cout<<"speed=="<<speed<<" acceleration=="<<acceleration<<"\n";

}

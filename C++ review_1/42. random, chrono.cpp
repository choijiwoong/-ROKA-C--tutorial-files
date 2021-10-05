#include <iostream>
#include <random>
#include <chrono>

/*random
int main(){
	std::random_device rd;//create random_device for seed value
	std::mt19937 gen(rd());//initialization of random engine by random_device(Mersenne twister) minstd_rand like rand in C
	std::uniform_int_distribution<int> dis(0, 99);//definition of uniform distribution for distribution
	
	for(int i=0; i<5; i++)
		std::cout<<"random: "<<dis(gen)<<std::endl;
} */

#include <iomanip>
#include <vector> 
/*check times by using chrono, when we make random number to vector
namespace ch=std::chrono;
int main(){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1000);
	
	for(int total=1; total<=1000000; total*=10){
		std::vector<int> random_numbers;
		random_numbers.reserve(total);
		
		ch::time_point<ch::high_resolution_clock> start=ch::high_resolution_clock::now();//save start time by high_
		for(int i=0; i<total; i++)
			random_numbers.push_back(dist(gen));
		ch::time_point<ch::high_resolution_clock> end=ch::high_resolution_clock::now();//save end time by high_
		
		std::chrono::duration diff=end-start;//getduration
		std::cout<<std::setw(7)<<"time for create random("<<total<<"): "<<ch::duration_cast<ch::microseconds>(diff).count()<<"us"<<std::endl;
	}
}*/

#include <ctime>//no class in C++17. so use C's function
//make time to data
int main(){
	auto now=std::chrono::system_clock::now();//get now time_point
	std::time_t t=std::chrono::system_clock::to_time_t(now);//convert time_t object
	
	std::cout<<std::put_time(std::localtime(&t), "%F %T %z")<<std::endl;//pass by local_time for convet std::tm ojbect
}


/*
1.	C의 srand(time(NULL))은 pseudo random number(의사 난수)이다. 시드값 변화속도도 느리고, 범위 내에 균등하지도 않을 뿐더러 rand()가 선형 합동 생성기(Linear congruential generator)로 만들어져 난수열들의 상관 관계도 높다. 
2.	시드값을 얻은 장치를 만들고(like 장치 드라이버들의 noise등을 이용한 운영체제기반의 진짜 난수), 장치로 난수 엔진에 시드값 전달, 
	균등 분포로 범위를 정한 다음, 분포에 시드값이 전달된 엔진을 넣어 호출. 
3.	uniform distribition말고도 normal distribution같은 여러 분포를 제공한다. 

4.	chrono는 현재 시간을 알려주는 시계_system_clock, 특정 시간을 나타내는 time_stamp, 시간의 간격을 나타내는 duration으로 구성되어 있다.
5.	일반적인 system_clock과 정밀한 high_resolution_clock이 있는데, 이들은 time_stamp객체를 리턴한다.(Unix time; 1970/01/01부터 몇번의 틱) 
	time_stamp객체는 clock의 시작점과 현재 시간의 duration을 보관하는 객체이다. 
6.	duration_cast로 duration객체를 받아 우리가 원하는 단위의 duration객체로 캐스팅이 가능하다. 
*/ 

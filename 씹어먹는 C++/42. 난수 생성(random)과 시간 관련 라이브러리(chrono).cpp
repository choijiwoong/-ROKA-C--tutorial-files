/*1. C style random
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	srand(time(NULL));
	for(int i=0; i<5; i++)
		printf("random : %d\n", rand()%100);//recollections..
	return 0;
	//In fact, it creates psudo random number that looks like real random number.
	//In computer, making perfect random number is some hard. so instead of it, computer make only first number randomly, and left numbers by many mathmetical ways.
	//We call that first value to Seed, we can set Seed value by srand in C language.
	//In upper example, time that we execute program is set by time(NULL).
	//So compiler makes sequence that looks like random number when we call rand().
}*/

/*2 random
#include <iostream>
#include <random>
int main(){
	std::random_device rd;//for get seed value
	std::mt19937 gen(rd());//initialize random creating engine by random_device. it can be put any value we want
	std::uniform_int_distribution<int> dis(0,99);//definition of uniform distribution for uniform random sequence
	
	for (int i=0; i<5; i++)
		std::cout<<"random : "<<dis(gen)<<std::endl;//pass random engin to uniform distribution
}*/

/*3 <random> produce many distribution like uniform_int_distribution. Let's see one more example of Normal distribution.
#include <iomanip>
#include <iostream>
#include <map>
#include <random>

int main(){
	std::random_device rd;//for use random value in operating system
	std::mt19937 gen(rd());//pass seed to engin
	std::normal_distribution<double> dist(0, 1);//average, standard deviation to normal_distribution
	
	std::map<int, int> hist{};//like dictionary in python
	
	for(int n=0; n<10000; ++n)//extract 10000 samples
		++hist[std::round(dist(gen))];
	for(auto p:hist)//it looks like normal_distribution graph
		std::cout<<std::setw(2)<<p.first<<' '<<std::string(p.second/100, '*')<<" "<<p.second<<'\n';
	//i don't know this code perfectly..
}*/

/*5 Let's check time creating random number
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

int main(){
	std::random_device rd;//for use random function of system operation
	std::mt19937 gen(rd());//initialization of engine by rd.
	std::uniform_int_distribution<> dist(0, 1000);//set distribution with range of random number we want
	
	for(int total=1; total<=1000000; total*=10){//6 times
		std::vector<int> random_numbers;//storage for random number
		random_numbers.reserve(total);//reserve memory with total
		std::chrono::time_point<std::chrono::high_resolution_clock> start=std::chrono::high_resolution_clock::now();//set start that's time of now.
		
		for(int i=0; i<total; i++)
			random_numbers.push_back(dist(gen));//make random number as total value & save
			
		std::chrono::time_point<std::chrono::high_resolution_clock> end=std::chrono::high_resolution_clock::now();//set end that's time of now.
		//clock's now return time_point with clock (by template argument)
		
		//Before C++17, we have to use std::chrono::duration<std::chrono::high_resolution_clock>. so we used auto keyword simplely.
		auto diff=end-start;//calculation of duration
		//time_stamp-time_stamp returns duration object.
		
		//After C++17
		//std::chrono::duration diff=end-start;
		
		std::cout<<std::setw(7)<<"tick count creating "<<total<<" random number"<<diff.count()<<std::endl;
	}
	//std::setw(n) set field that we use for print.
	//duration object's count(member function) allow how many tick is occured during that time difference
	//but we need how many time not how many tick. so we can use duration_cast
	//Let's recode upper code by using duration_cast and namespace ch!
} */

/*5 Let's use duration_cast
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

namespace ch=std::chrono;

int main(){
	std::random_device rd;//system operation
	std::mt19937 gen(rd());//mersenne twister
	std::uniform_int_distribution<> dist(0, 1000);//sidtribution with range
	
	for(int total=1; total<=1000000; total*=10){//6 times
		std::vector<int> random_numbers;//storage
		random_numbers.reserve(total);//reserve memory
		
		ch::time_point<ch::high_resolution_clock> start = ch::high_resolution_clock::now();//time before execution
		
		//execution
		for(int i=0; i<total; i++)
			random_numbers.push_back(dist(gen));//make
		
		ch::time_point<ch::high_resolution_clock> end = ch::high_resolution_clock::now();//time after execution
		
		auto diff=end-start;//duration
		
		std::cout<<std::setw(7)<<"spended time for making "<<total<<"'s random number: "<<ch::duration_cast<ch::microseconds>(diff).count()<<"us"<<std::endl;
		//duration_cast can cast random duration to duration that we want to change.
		//ch::microseconds is duration object that tick 10^6 time in 1 second.
		//so return value( of count after casting) means how many microseconds duration is.
	}
}*/

//6 we have to use C function for print time now.
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

int main(){
	auto now=std::chrono::system_clock::now();//get current tick
	std::time_t t=std::chrono::system_clock::to_time_t(now);//convert now to 'time_t' type for print
	std::cout<<"current time: "<<std::put_time(std::localtime(&t), "%F %T %z")<<'\n';//C++17...
	//we pass t to std::localtime for converting to std::tm object, finally it can be consisted to string that we want by std::put_time.
}


/*
[0.	들어가기에 앞서]
1.	some people use time.h or stdlib.h for using function about time in C++. But we have to use time library of C++.

[1.	C스타일의 난수 생성의 문제점]
1.	시드값이 너무 천천히 변핝다. 즉, 프로그램이 같은 시간대에 모두 같은 의사 난수 수열을 생성하게 된다
2.	0부터 99까지 균등하게 난수를 생성하지 않는다. 
	compiler는 0부터 RAND_MAX까지의 값을 난수로 생성하는거지 그 값을 나눈 값이 완벽한 난수가 되지 않는다. 즉, 1의 경우 rand()가 리턴한 값이 1이거나 101이거나..이지만, 50의 경우 50일때 만 생성된다. 즉 1의 확률이 50의 2배인 것이다(RAND_MAX가 128이라 가정)
3.	rand()자체도 별로 뛰어나지 않다.
	C의 rand()함수는 선형 합동 생성기(Linear congruential generator)알고리즘을 바탕으로 구현되었는데, 이는 생성되는 난수열들의 상관 관계가 높아 일부 시뮬레이션에 사용하기에 적합하지 않다.
4.	C의 srand와 rand를 버리자

[3.	<random>]
1.	C는 time(NULL)로 시드값을 얻었지만, C++은 양질의 시드값을 위해 random_device를 사용한다.
2.	대부분의 운영체제에는 진짜 난수 값들을 얻어낼 수 있는 여러가지 방식들을 제공하고 있다. (ex. 리눅스의 /dev/random or /dev/urandom)
	이는 수학적 알고리즘에서 비롯된 것이 아닌, 실제 컴퓨터가 실행하면서 마주치는 무작위적인 요소들(ex. 장치 드라이버의 noise)를 기반으로 한 진정한 난수를 제공한다.
	random_device는 운영체제 단에서 제공하는 진짜 난수를 사용할 수 있게 해준다. 다만 진짜 난수는 컴퓨터가 무작위적 환경과 상호작용하며 만들어지므로 의사 난수보다 난수의 새엉 속도가 매우 느리다.
	고로, 난수 엔진을 초기화하는 시드값으로 사용하고, 그 이후는 난수 엔진이 만든다.
3.	std::mt19937은 C++의 random에서 제공하는 난수 생성 엔진 중 하나로, 메르센 트위스터 알고리즘을 사용하는데, 이는 rand의 선형 합동 방식보다 양질의 난수열을 생성한다. 또한 생성되는 난수들간의 상관관게가 매우 적어 여러 시뮬레이션에 사용된다.
	mt19937은 객체크기가 2KB이상으로 크기가 커서 메모리가 부족한 프로그램에서는 rand와 같은 minstd_rand등의 여러 엔진을 사용하기도 한다.(mt19937은 생성 이후 사용 속도가 매우 빠음) 
4.	그 다음 C++의 경우, 어디에서 수들을 뽑아낼 지 알려주는 분포(distribution)을 정의해야 한다. 그를 위해서는 귱등 분포(Uniform distribution)객체를 정의해야 한다.
	 
[4.	chrono 소개]
1.	chrono는 크게 3가지 요소로 구성되어 있다.
	-현재 시간을 알혀주는 시계_(ex. system_clock)
	-특정 시간을 나타내는 time_stamp
	-시간의 간격을 나타내는 duration

[5.	chrono에서 지원하는 clock들]
1.	chrono에서는 여러 시계들을 지원하고 있는데, 일반적인 상황에서 컴퓨터상 시간을 얻으려면 std::system_clock을, 정밀한 시간 계산을 하려면(ex. 프로그램 성능 측정) std::high_resolution_clock을 사용할 수 있다.
2.	이 시계들은 지정된 시점으로 부터 몇 번의 틱(tick)이 발생했는지 알려주는 time_stamp객체를 리턴한다. 예로 std::system_clock은 1970.01.01부터 현재까지의 틱의 횟수를 리턴한다.(이를 흔히 유닉스 타임(Unix time)이라고 부른다.)
	다시말해 time_stamp객체는 clock의 시작점과 현재 시간의 duration을 보관하는 객체이다. 
3.	각 시계마다 정밀도가 다르기에 clock에서 얻어지는 tick값 자체는 조금 다르다. (system_clock은 1초에 1tick이지만, high_resolution_clock은 0.00000001초마다 1tick이다.) 
4.	chrono 라이브러리의 경우 다른 표준 라이브러리와 다르게 객체들이 std::chrono namespace안에 정의되어 있어 std::higj_resolution_clock이 아닌 std::chrono::high_resolution_clock처럼 사용해야 한다.
	(귀찮으면 namespace ch=std::chrono;로 별명지어주고 사용하삼.) 
5.	clock에는 현재의 time_point를 리턴하는 static함수인 now가 정의되어 있다. 이 now()를 호출하면 해당 clock에 맞는 time_point객체를 리턴한다.
	즉, 우리는 high_resolution_clock::now()를 호출하였으므로, std::chrono::time_point<std::chrono::high_resolution_clock>을 리턴한다. 
	time_point에 clock인자로 들어가는 이유는 5-1처럼 clock마다 1초에 발생하는 틱 횟수가 모두 다르기 때문이다. 즉, 실제 시간으로 변환 시 clock정보가 필요하기 때문이다.(실제초(시간)=틱/클록이 사용하는 초당 틱) 
6.	두 time_stamp를 빼면 duration객체를 리턴한다.	 
7.	duration_cast는 우리가 원하는 duration으로 캐스팅이 가능하다. 
8.	chrono에는 std::chrono::microseconds외에도 nanoseonds, milliseconds, seconds, minutes, hours가 정의되어 있다.

[6.	현재 시간을 날짜로]
1.	아쉽게도 C++17에는 chrono라이브러리에 날짜를 간단하게 다룰 수 있도록 도와주는 클래스가 없다. 고로 현재 시간을 출력하고 싶다면 C의 함수들에 의존해야 한다.
2.	연재 시간을 std::tm객체로 변환하기 위하여 std::tm 객체로 변환하여 std::localtime에 t를 전달하고, std::put_time을 통해 우리가 원하는 문자열로 변환할 수 있다.
	put_time에 전달된 인자는 strftime에서 사용되는 인자와 동일하다.
3.	C++17 현재 C의 함수를 사용하지 않으면 날짜를 다룰 수 없다. 하지만 C++20에 추가될 예정이다.

[7.	마무리하며]
1.	srand와 rand말고 std::mt19937을 사용하자. 
2.	random라이브러리에선 원하는 확률 분포에서 샘플링이 가능하다.
3.	현재시간은 system_clock, 정밀한 측정은 high_resolution_clock이다
4.	duration_cast로 원하는 시간 스케일로 변경이 가능하다. 
*/

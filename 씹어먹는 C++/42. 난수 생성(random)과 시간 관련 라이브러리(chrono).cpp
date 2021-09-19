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
[0.	���⿡ �ռ�]
1.	some people use time.h or stdlib.h for using function about time in C++. But we have to use time library of C++.

[1.	C��Ÿ���� ���� ������ ������]
1.	�õ尪�� �ʹ� õõ�� ������. ��, ���α׷��� ���� �ð��뿡 ��� ���� �ǻ� ���� ������ �����ϰ� �ȴ�
2.	0���� 99���� �յ��ϰ� ������ �������� �ʴ´�. 
	compiler�� 0���� RAND_MAX������ ���� ������ �����ϴ°��� �� ���� ���� ���� �Ϻ��� ������ ���� �ʴ´�. ��, 1�� ��� rand()�� ������ ���� 1�̰ų� 101�̰ų�..������, 50�� ��� 50�϶� �� �����ȴ�. �� 1�� Ȯ���� 50�� 2���� ���̴�(RAND_MAX�� 128�̶� ����)
3.	rand()��ü�� ���� �پ�� �ʴ�.
	C�� rand()�Լ��� ���� �յ� ������(Linear congruential generator)�˰����� �������� �����Ǿ��µ�, �̴� �����Ǵ� ���������� ��� ���谡 ���� �Ϻ� �ùķ��̼ǿ� ����ϱ⿡ �������� �ʴ�.
4.	C�� srand�� rand�� ������

[3.	<random>]
1.	C�� time(NULL)�� �õ尪�� �������, C++�� ������ �õ尪�� ���� random_device�� ����Ѵ�.
2.	��κ��� �ü������ ��¥ ���� ������ �� �� �ִ� �������� ��ĵ��� �����ϰ� �ִ�. (ex. �������� /dev/random or /dev/urandom)
	�̴� ������ �˰��򿡼� ��Ե� ���� �ƴ�, ���� ��ǻ�Ͱ� �����ϸ鼭 ����ġ�� ���������� ��ҵ�(ex. ��ġ ����̹��� noise)�� ������� �� ������ ������ �����Ѵ�.
	random_device�� �ü�� �ܿ��� �����ϴ� ��¥ ������ ����� �� �ְ� ���ش�. �ٸ� ��¥ ������ ��ǻ�Ͱ� �������� ȯ��� ��ȣ�ۿ��ϸ� ��������Ƿ� �ǻ� �������� ������ ���� �ӵ��� �ſ� ������.
	���, ���� ������ �ʱ�ȭ�ϴ� �õ尪���� ����ϰ�, �� ���Ĵ� ���� ������ �����.
3.	std::mt19937�� C++�� random���� �����ϴ� ���� ���� ���� �� �ϳ���, �޸��� Ʈ������ �˰����� ����ϴµ�, �̴� rand�� ���� �յ� ��ĺ��� ������ �������� �����Ѵ�. ���� �����Ǵ� �����鰣�� ������԰� �ſ� ���� ���� �ùķ��̼ǿ� ���ȴ�.
	mt19937�� ��üũ�Ⱑ 2KB�̻����� ũ�Ⱑ Ŀ�� �޸𸮰� ������ ���α׷������� rand�� ���� minstd_rand���� ���� ������ ����ϱ⵵ �Ѵ�.(mt19937�� ���� ���� ��� �ӵ��� �ſ� ����) 
4.	�� ���� C++�� ���, ��𿡼� ������ �̾Ƴ� �� �˷��ִ� ����(distribution)�� �����ؾ� �Ѵ�. �׸� ���ؼ��� ���� ����(Uniform distribution)��ü�� �����ؾ� �Ѵ�.
	 
[4.	chrono �Ұ�]
1.	chrono�� ũ�� 3���� ��ҷ� �����Ǿ� �ִ�.
	-���� �ð��� �����ִ� �ð�_(ex. system_clock)
	-Ư�� �ð��� ��Ÿ���� time_stamp
	-�ð��� ������ ��Ÿ���� duration

[5.	chrono���� �����ϴ� clock��]
1.	chrono������ ���� �ð���� �����ϰ� �ִµ�, �Ϲ����� ��Ȳ���� ��ǻ�ͻ� �ð��� �������� std::system_clock��, ������ �ð� ����� �Ϸ���(ex. ���α׷� ���� ����) std::high_resolution_clock�� ����� �� �ִ�.
2.	�� �ð���� ������ �������� ���� �� ���� ƽ(tick)�� �߻��ߴ��� �˷��ִ� time_stamp��ü�� �����Ѵ�. ���� std::system_clock�� 1970.01.01���� ��������� ƽ�� Ƚ���� �����Ѵ�.(�̸� ���� ���н� Ÿ��(Unix time)�̶�� �θ���.)
	�ٽø��� time_stamp��ü�� clock�� �������� ���� �ð��� duration�� �����ϴ� ��ü�̴�. 
3.	�� �ð踶�� ���е��� �ٸ��⿡ clock���� ������� tick�� ��ü�� ���� �ٸ���. (system_clock�� 1�ʿ� 1tick������, high_resolution_clock�� 0.00000001�ʸ��� 1tick�̴�.) 
4.	chrono ���̺귯���� ��� �ٸ� ǥ�� ���̺귯���� �ٸ��� ��ü���� std::chrono namespace�ȿ� ���ǵǾ� �־� std::higj_resolution_clock�� �ƴ� std::chrono::high_resolution_clockó�� ����ؾ� �Ѵ�.
	(�������� namespace ch=std::chrono;�� ���������ְ� ����ϻ�.) 
5.	clock���� ������ time_point�� �����ϴ� static�Լ��� now�� ���ǵǾ� �ִ�. �� now()�� ȣ���ϸ� �ش� clock�� �´� time_point��ü�� �����Ѵ�.
	��, �츮�� high_resolution_clock::now()�� ȣ���Ͽ����Ƿ�, std::chrono::time_point<std::chrono::high_resolution_clock>�� �����Ѵ�. 
	time_point�� clock���ڷ� ���� ������ 5-1ó�� clock���� 1�ʿ� �߻��ϴ� ƽ Ƚ���� ��� �ٸ��� �����̴�. ��, ���� �ð����� ��ȯ �� clock������ �ʿ��ϱ� �����̴�.(������(�ð�)=ƽ/Ŭ���� ����ϴ� �ʴ� ƽ) 
6.	�� time_stamp�� ���� duration��ü�� �����Ѵ�.	 
7.	duration_cast�� �츮�� ���ϴ� duration���� ĳ������ �����ϴ�. 
8.	chrono���� std::chrono::microseconds�ܿ��� nanoseonds, milliseconds, seconds, minutes, hours�� ���ǵǾ� �ִ�.

[6.	���� �ð��� ��¥��]
1.	�ƽ��Ե� C++17���� chrono���̺귯���� ��¥�� �����ϰ� �ٷ� �� �ֵ��� �����ִ� Ŭ������ ����. ��� ���� �ð��� ����ϰ� �ʹٸ� C�� �Լ��鿡 �����ؾ� �Ѵ�.
2.	���� �ð��� std::tm��ü�� ��ȯ�ϱ� ���Ͽ� std::tm ��ü�� ��ȯ�Ͽ� std::localtime�� t�� �����ϰ�, std::put_time�� ���� �츮�� ���ϴ� ���ڿ��� ��ȯ�� �� �ִ�.
	put_time�� ���޵� ���ڴ� strftime���� ���Ǵ� ���ڿ� �����ϴ�.
3.	C++17 ���� C�� �Լ��� ������� ������ ��¥�� �ٷ� �� ����. ������ C++20�� �߰��� �����̴�.

[7.	�������ϸ�]
1.	srand�� rand���� std::mt19937�� �������. 
2.	random���̺귯������ ���ϴ� Ȯ�� �������� ���ø��� �����ϴ�.
3.	����ð��� system_clock, ������ ������ high_resolution_clock�̴�
4.	duration_cast�� ���ϴ� �ð� �����Ϸ� ������ �����ϴ�. 
*/

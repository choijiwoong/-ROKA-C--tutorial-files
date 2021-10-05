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
1.	C�� srand(time(NULL))�� pseudo random number(�ǻ� ����)�̴�. �õ尪 ��ȭ�ӵ��� ������, ���� ���� �յ������� ���� �Ӵ��� rand()�� ���� �յ� ������(Linear congruential generator)�� ������� ���������� ��� ���赵 ����. 
2.	�õ尪�� ���� ��ġ�� �����(like ��ġ ����̹����� noise���� �̿��� �ü������� ��¥ ����), ��ġ�� ���� ������ �õ尪 ����, 
	�յ� ������ ������ ���� ����, ������ �õ尪�� ���޵� ������ �־� ȣ��. 
3.	uniform distribition���� normal distribution���� ���� ������ �����Ѵ�. 

4.	chrono�� ���� �ð��� �˷��ִ� �ð�_system_clock, Ư�� �ð��� ��Ÿ���� time_stamp, �ð��� ������ ��Ÿ���� duration���� �����Ǿ� �ִ�.
5.	�Ϲ����� system_clock�� ������ high_resolution_clock�� �ִµ�, �̵��� time_stamp��ü�� �����Ѵ�.(Unix time; 1970/01/01���� ����� ƽ) 
	time_stamp��ü�� clock�� �������� ���� �ð��� duration�� �����ϴ� ��ü�̴�. 
6.	duration_cast�� duration��ü�� �޾� �츮�� ���ϴ� ������ duration��ü�� ĳ������ �����ϴ�. 
*/ 

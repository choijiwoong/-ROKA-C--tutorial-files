#include <iostream>
#include <thread>//CreateTread in Window, pthread_create in Linux
#include <vector>

//Logical error if threads access to same memory.
void worker(int& counter){
	for(int i=0; i<10000; i++)
		counter+=1;
} 

int main(){
	int counter=0;
	
	std::vector<std::thread> workers;
	for(int i=0; i<4; i++)
		workers.push_back(std::thread(worker, std::ref(counter)));
	
	for(int i=0; i<4; i++)
		workers[i].join();
		
	std::cout<<"Resault of Counter: "<<counter<<std::endl;
}

/*
1.	Context switching; CPU에서 작업을 스위칭하여 여러작업을 수행하는 것
2.	운영체제의 Scheduler; CPU에게 어떤 프로그램을 실행시킬지, 얼마동안 실행시킬지, 다음에 어느 프로그램으로 switching할지를 결정
3.	Thread; CPU코어에서 돌아가는 프로그램의 단위. 한 프로세스 안의 쓰레드는 메모리를 공유한다.
4.	dependent하지 않은 parallelize작업을 MultiThread로 처리한다. 
5.	C++은 join되거나 detach(백그라운드화하고 잊어버리기)되지 않은 쓰레드들의 소멸자가 호출되면 예외를 발생시킨다. 
6.	thread::id this_id=std::this_thread::get로 쓰레드의 아이디를 알 수 있다. 
7.	printf는 내용출력을 보장해주기에 cout대신 사용한다.
8.	같은 메모리를 참조하여 여러 쓰레드를 돌리면, mutex로 lock을 하지 않는 이상 컴파일러나 운영체제가 코드를 어셈블단위에서 재배치하기에 손실이 일어난다. 
*/

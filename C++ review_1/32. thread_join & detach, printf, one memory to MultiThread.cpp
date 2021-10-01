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
1.	Context switching; CPU���� �۾��� ����Ī�Ͽ� �����۾��� �����ϴ� ��
2.	�ü���� Scheduler; CPU���� � ���α׷��� �����ų��, �󸶵��� �����ų��, ������ ��� ���α׷����� switching������ ����
3.	Thread; CPU�ھ�� ���ư��� ���α׷��� ����. �� ���μ��� ���� ������� �޸𸮸� �����Ѵ�.
4.	dependent���� ���� parallelize�۾��� MultiThread�� ó���Ѵ�. 
5.	C++�� join�ǰų� detach(��׶���ȭ�ϰ� �ؾ������)���� ���� ��������� �Ҹ��ڰ� ȣ��Ǹ� ���ܸ� �߻���Ų��. 
6.	thread::id this_id=std::this_thread::get�� �������� ���̵� �� �� �ִ�. 
7.	printf�� ��������� �������ֱ⿡ cout��� ����Ѵ�.
8.	���� �޸𸮸� �����Ͽ� ���� �����带 ������, mutex�� lock�� ���� �ʴ� �̻� �����Ϸ��� �ü���� �ڵ带 ������������ ���ġ�ϱ⿡ �ս��� �Ͼ��. 
*/

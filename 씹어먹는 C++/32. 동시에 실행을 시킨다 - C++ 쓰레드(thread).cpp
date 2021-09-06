#include <iostream>

/*3 example crawling website
int main(){
	map<string, string> url_and_content;
	for(auto itr=url_and_content.begin(); itr!=url_and_content.end(); ++itr){
		const string& url=itr->first;
		itr->second=download(url);//download and return of site.
	}
}*/

#include <thread>
/*4
using std::thread;
void func1(){
	for(int i=0; i<10; i++)
		std::cout<<"working thread 1!"<<std::endl;
}
void func2(){
	for(int i=0; i<10; i++)
		std::cout<<"working thread 2!"<<std::endl;
}
void func3(){
	for(int i=0; i<10; i++)
		std::cout<<"working thread 3!"<<std::endl;
}

int main(){
	thread t1(func1);//make thread object! 
	thread t2(func2);
	thread t3(func3);
	
	//t1.join();//return when thread done their work.
	//t2.join();
	//t3.join();
	
	t1.detach();
	t2.detach();
	t3.detach();
	
	std::cout<<"exit main \n";
}*/

#include <cstdio>
#include <vector> 
/*5
using std::thread;
using std::vector;
void worker(vector<int>::iterator start, vector<int>::iterator end, int* result){
	int sum=0;
	for(auto itr=start; itr<end; ++itr)
		sum+=*itr;
	*result=sum;
	
	//get id of thread
	thread::id this_id=std::this_thread::get_id();
	printf("calculated result of %d to %d of thread %x : %d \n", *start, *(end-1), sum);//not std::cout!! 
}

int main(){
	vector<int> data(10000);
	for(int i=0; i<10000; i++)
		data[i]=i;
	
	vector<int> partial_sums(4);
	//vector that saves partual sums in each thread
	
	vector<thread> workers;
	for(int i=0; i<4; i++)
		workers.push_back(thread(worker, data.begin()+i*2500, data.begin()+(i+1)*2500, &partial_sums[i]));
		
	for(int i=0; i<4; i++)
		workers[i].join();
		
	int total=0;
	for(int i=0; i<4; i++)
		total+=partial_sums[i];
	
	std::cout<<"total sum : "<<total<<std::endl;
}*/

//6
using std::thread;
using std::vector;

void worker(int& counter){
	for(int i=0; i<10000; i++)
		counter++;
}
int main(){
	int counter=0;
	
	vector<thread> workers;
	for(int i=0; i<4; i++)
		workers.push_back(thread(worker, std::ref(counter)));
	for(int i=0; i<4; i++)
		workers[i].join();
		
	std::cout<<"Final result of Counter : "<<counter<<std::endl;//diffenent value!
}



/*
[1.	��Ƽ ������ ���α׷�]
1.	�۾������ڸ� ������ ������ ������ ���μ����� �� �� �ִ�. �츮�� ���� 1���� ���α׷��� ����ų �� 1���� ���μ����� �ǹ��Ѵ�.
	�̷��� ���μ����� CPU �ھ�� ����Ǵµ�, CPU�� �ѹ��� �Ѱ��� ����ۿ� ���ϱ⿡ ���ؽ�Ʈ ����Ī(Context switching)�� �̿��Ͽ� ���α׷��� ����Ī �ϸ� ���ݾ� ���������� ������� ó���Ѵ�.
	��, CPU�� �ü���� ��Ű�� ��ɾ ������ ��, ���α׷��� ���࿩��, �ð�, �������� ����ġ�� ���α׷� ���� �ü���� �����췯(scheduler)�� �����ϰ� �ȴ�.
	 �� CPU�ھ�� ���ư��� ���α׷� ������ ������(thread)��� �ϴµ�, �� CPU�ھ��ϳ����� �ѹ��� �� ���� �������� ����� �����ϰ� �ȴ�.
	�� ���� ���μ����� �ּ� �� ���� ������� �����Ǹ�, �������� ������� ������ ���α׷��� ��Ƽ ������(multithread) ���α׷��̶�� �Ѵ�.
	������� ���μ����� ���� ū �������� �� ���μ��� �ȿ� �����尡 �������� ���� ���� �޸𸮸� �����ϴ� �ݸ�, ���μ������� ���� �޸𸮸� �������� �ʴ´ٴ� ���̴�. 

[2.	CPU�� �ھ�� �� ���� �ƴϴ�]
1.	�ٷ��� CPU���������� �ھ� �ϳ��� ���ۼӵ��� ���̱� ���ٴ�, CPU�� ������ �ھ� ������ �ø��� ������ �����ؿԴ�.
	���� �̱��ھ� CPU���� �ƹ��� ��Ƽ ������ ���α׷��̶� �ϴ��� �ᱹ �ѹ��� �� �����常 ������ �� �־�����, ��Ƽ�ھ� CPU������ �������� ��������� ȿ�������� ������ �� �ְԵǾ���.
	(p.s SMT(Simultaneous Multithreading)����� ���� �������� �ھ�ó�� �� �� ����) 

[3.	�׷��� �� ��Ƽ ������ �ε�?]
1.	���� ������(Parallelizable)�۾����� �л��Ͽ� �Ի��ϴµ��� ȿ�����̴�. 
	�ٸ� �Ǻ���ġ ���Ͱ��� ���� ���, Fn�� ���Ϸ��� Fn-1 Fn-2�� �˾ƾ��ϱ⿡ parallelize(����ȭ)�� �ӵ��� ���̰� ���� �ȴ�.
	��� �Ǻ���ġ ������ ����ϴ� ���α׷��� ����ȭ�ϴ°��� �ſ� ��ƴ�. ��� ����(A)�� �����ϱ� ���� �ٸ� ����(B)�� ����� �ʿ��ϱ� �����ε�, �츮�� �̸� A�� B�� �����Ѵ� ��� ǥ���Ѵ�.
	��, ���α׷� ������ �󿡼� ����鰣�� �������谡 ������ ����ȭ�� ���������, ���������� ������ ����ȭ�� �ſ� ��������.
2.	���ð��� �� �۾����� ó���ϴµ� ȿ�����̴�.
	���ͳ��� CPUó���ӵ��� ���� �ſ� ������. ping�ӵ��� ��û�� ������ �ٽ� ���ƿ��� �ð��� �ǹ��ϴµ�, ������ CPU�� 1�ʿ� 10^9�� ������ �� �� �ֱ⿡, CPU�� ��ȿ�������� ����ϴ� ���� �ȴ�.
	��� �ٿ�ε� �Լ��� ���� �����忡�� �θ��� ���ؽ�Ʈ ����Ī�� ���� ��ٸ��� �ð� ���� CPU�� �ִ������� ����� �� �ְ� �ȴ�.
	
[4.	C++���� ������ �����ϱ�]
1.	C++ 11���� ǥ�ؿ� �����尡 �߰��Ǿ� ������ �÷������� ��������� �޶����Ͱ��� �޸� ������ ����� �ſ� ��������.
2.	#include <thread>�ϰ� thread t1(func2) thread��ü�� �����ϸ� ���̴�.  t1�� ���ڷ� ���޹��� �Լ��� ���ο� �����忡�� �����ϰ� �ȴ�.(�׳� �� �ھ ������ 3���� ���ؽ�Ʈ ����Ī�� �ϸ鼭 ���ư� ���� ����. �װ� �ü���� ����) 
	join()�� �����尡 ������ �����ϸ� �����ϴ� �Լ��̴�. 
	 ���� t2�� t1���� ���� ����Ǿ t1.join()�� ������ t2.join()���� �ٷ� ���ϵȴ�. 
3.	���� join�� ���� �ʰ� �Ǹ� �������� ������ ä ����Ǳ⵵ ���� main�Լ��� ����Ǿ� thread ��ü�� �Ҹ��ڰ� ȣ��ȴ�. �ٵ� �� �� �ǳ� �m 
	C++ǥ�ؿ� ������ join�ǰų� detach���� �ʴ� ��������� �Ҹ��ڰ� ȣ��Ǹ� ���ܸ� �߻���Ű�� �Ǿ��ִ�.(���� ���)
4.	detach�� �ش� �����带 ���� ��Ų ��, �ؾ������ ���̴�. �� ��׶��忡�� ���ư��� ���̴�. 
	�⺻������ ���μ����� ����� ��, �ش� ���μ��� ���� ��� ��������� ���� ���ο� ������� �ڵ����� ����ȴ�. ��, main function���� exit main�� print�Ѵٸ� work thread ~�� ����� �� ���� �ȴ�.
	 �����带 detach�ϰ� �Ǹ� main�Լ������� ��������� ����� �� ���� ��ٸ��� �ʴ´�. ��� ���ڿ��� ǥ���ϱ⵵ ���� ���μ����� ����ǰų� ������� ����ǰ� ����� �� �ִ�. 

[5.	�����忡 ���� �����ϱ�]
1.	thread::id this_id=std::this_thread::get_id();�� � �����忡�� �۾��������� �� �� �ִ�.
	std::cout<<A<<B�� ��� A�� ��µǴ� ������ �ٸ� �����尡 ������ ����� �� ���� ������ ������, A�� ����� ������ B�� ��µǱ� ������ �ٸ� �������� ������ ��½�ų �� �ֱ⿡
	printf�� ����ߴ�. printf�� ""�ȿ� �ִ� ���ڿ��� ����� ��, �ٸ� ��������� �� ���̿� �޼����� ������� ���ϰ� ���� ���ع��� �ʰ� ����� �����ϴ�. 

[6.	�ٸ� �����忡�� �޸𸮸� ���� �����Ѵٸ�?]
1.	�������¿��� �˾ƺ��� 

*/

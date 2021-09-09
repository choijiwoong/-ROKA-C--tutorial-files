#include <iostream>

/*1 for showing unefficiency of this code.
string txt=read("a.txt");//5ms
string resault=do_something_with_txt(txt);//5ms
do_other_computation();//5ms
//read function waits while files are read in hard disk.

//1 solution for eficiency by using thread we have learned.
void file_read(string* result){
	string txt=read("a.txt");//0ms thanks to thread
	//Now, CPU can move to main thread and execute do_other_computation
	*result=do_something_with_txt(txt);//5ms
}
int main(){
	string result;
	thread t(file_read, &result);
	do_other_computation();//5ms
	t.join();//do work by thread. CPU don't rest once.
}*/



/*
[0.	들어가기에 앞서]
-	이번 강좌에서는 멀티 쓰레딩의 강력함을 더 쉽게 활용할 수 있게 해주는 몇 가지 도구들을 살펴보자. 

[1.	동기(sunchronous)와 비동기(asynchronous) 실행]
1.	한 번에 하나씩 순차적으로 실행되는 작업을 동기적(synchronous)으로 실행된다고 한다. 한 작업이 끝날 때 까지 다음 작업으로 이동하지 않기 때문이다.
	하지만, read가 하드 디스크에서 데이터를 읽어오는 동안 CPU는 아무런 작업을 하지 않기에 그 시간에 CPU에게 do_other_computation과 같은 작업을 실행시키는 것이 더 효율적이고 바람직하다.
	 그렇기에 C++은 thread로 빼어 do_other_computaion을 하는 동안 read를 하도록 하여 기다리는 시간을 단축하였다.
	이처럼 프로그램의 실행이, 한 갈래가 아니라 여러 갈래로 갈라져서 동시에 진행되는 것을 비동기적(asynchronous) 실행이라고 부른다. 
2.	자바스크립트와 같은 언어들은 언어 차원에서 비동기적 실행을 지원하지만, C++의 경우 명시적으로 쓰레드를 생성해서 적절히 수행해야 했다.
	이를 돕기 위해 C++11 표준 라이브러리에는 매우 간단히 비동기적 실행을 할 수 있게 해주는 도구들을 제공하고 있다.
	
[2.	std::promise와 std::future]
1.	 
*/ 

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
[0.	���⿡ �ռ�]
-	�̹� ���¿����� ��Ƽ �������� �������� �� ���� Ȱ���� �� �ְ� ���ִ� �� ���� �������� ���캸��. 

[1.	����(sunchronous)�� �񵿱�(asynchronous) ����]
1.	�� ���� �ϳ��� ���������� ����Ǵ� �۾��� ������(synchronous)���� ����ȴٰ� �Ѵ�. �� �۾��� ���� �� ���� ���� �۾����� �̵����� �ʱ� �����̴�.
	������, read�� �ϵ� ��ũ���� �����͸� �о���� ���� CPU�� �ƹ��� �۾��� ���� �ʱ⿡ �� �ð��� CPU���� do_other_computation�� ���� �۾��� �����Ű�� ���� �� ȿ�����̰� �ٶ����ϴ�.
	 �׷��⿡ C++�� thread�� ���� do_other_computaion�� �ϴ� ���� read�� �ϵ��� �Ͽ� ��ٸ��� �ð��� �����Ͽ���.
	��ó�� ���α׷��� ������, �� ������ �ƴ϶� ���� ������ �������� ���ÿ� ����Ǵ� ���� �񵿱���(asynchronous) �����̶�� �θ���. 
2.	�ڹٽ�ũ��Ʈ�� ���� ������ ��� �������� �񵿱��� ������ ����������, C++�� ��� ��������� �����带 �����ؼ� ������ �����ؾ� �ߴ�.
	�̸� ���� ���� C++11 ǥ�� ���̺귯������ �ſ� ������ �񵿱��� ������ �� �� �ְ� ���ִ� �������� �����ϰ� �ִ�.
	
[2.	std::promise�� std::future]
1.	 
*/ 

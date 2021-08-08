#include <iostream>
#include <string>
#include <fstream> 

int main(){
	//1
	std::ifstream in("test.txt");//ready for read file.
	std::string s;/*
	
	if(in.is_open()){//TIC
		in>>s;//content save to s. of coursely, read until space.
		std::cout<<"�Է� ���� ���ڿ� :: "<<s<<std::endl;//print
	} else{
		std::cout<<"������ ã�� �� �����ϴ�!"<<std::endl;
	}
	//2
	in.close();//situation that we have to close ifstream directly. 
	in.open("other.txt");//for use other file with same variable.
	
	if(in.is_open()){
		in>>s;
		std::cout<<"�Է� ���� ���ڿ� :: "<<s<<std::endl;
	} else{
		std::cout<<"������ ã�� �� �����ϴ�!"<<std::endl;
	} */
	//3
	in.close();
	in.open("test.txt", std::ios::binary);//std::ifstream in("test.txt", std::ios::binary);_p.s std::ios::binary is just number.
	//we will receive test.txt to binary type. that means receving binary value directly not string data. 
	int x;//read by binary number
	if(in.is_open()){
		in.read((char*)(&x),4);//read 4 bites content. first argument means buffer.so we send data with int varuable that works as char array has 4 bites.
		std::cout<<std::hex<<x<<std::endl;
	} else{
		std::cout<<"������ ã�� �� �����ϴ�!"<<std::endl;
	}
	
	return 0;
} 


/*
[1. fstream]
1.	���� ��Ʈ���� �⺻���� istream�̳� ostream���� �����ϴ� ����� �� ���⿡ �̸� ��ӹ޾Ƽ� �ۼ��Ǿ�����, ������ ��ӹ��� ���� ifstream�� ofstream�̴�. ���� �̵��� ��� �����ϴ� ���̺귯���� fstream�� ����Ѵ�.
2.	������ cout�� cin�� �� ����, �̹� ǥ�� ����¿� ������ �Ǿ� �ִ� ��Ȳ�̾�����, ������ ��� ��� ���Ͽ� ������� �ؾ������� �����ؾ��ϱ⿡ �̸� ifstream��ü�� �����ڿ� �����ϰ��� �Ѵ� ������ ��θ� �����ϸ� �ȴ�.
3.	C�� �ٸ��� fclose�� �ִ��� ifstream�� �Ҹ��ڿ��� �ڵ������� close�� �ϱ⿡ ���ص� �ȴ�. �ٸ� ���� �ؾ��ϴ� ��찡 �ִµ�, �ѹ� �� ������ �����ϰ� �ٸ� ������ ���� �� in.close()�� �� ���� in.open("other.txt")������ �ҷ��� ����̴�. ��, ���ο� ���Ͽ��� ���� ��ü�� �Է��� �ޱ� ���ؼ��� ���� ���� ��Ʈ������ ������ �����ϰ�, ���ο� ���ϰ� ��������ָ� �ȴ�. 
	���� open�Լ��� �ֱ⿡ ifstream��ü �����ڿ��� ���ϰ�θ� �ٷ� �������� �ʿ�� ����, ���߿� open���� ���ϴ� ������ ��� �ȴ�.
4.	hex�����ͷ� test.txt�� ������ ���캸��, ù �κ��� ��ġ�ϴ� ���� �� �� �ִ�.(3) 
	����� �츮�� ���� CPU�� ��� ��Ʋ �����(���� �ּҰ��� ���� �ڸ�����)������ �Ųٷ� int������ ��ϵ� ���� �� �� �ִ�. 
	������ �ٸ��� ���� ��, binary���� �������� �ɼ��� ���� ����Ϸ��� or ���������� �ȴ�. 
	 ������ ������ ���� �ڵ�ó�� int�� 4����Ʈ char �迭ó�� ����ϴ� ���� ���� ����, �׳� char �迭�� ũ�⸦ �����ؼ� ������ �ȴ�.
	 char x[10];
	 in.read(x, 10);
5.	p.s cout���� ����� std::hex������ ������ std::cout<<std::hex<<x<<std::endl;�� hex�� ����� �η��� 16������ ���� �����͸� ǥ�����ش�.

[2. ���� ��ü �б�]
1.	  
*/

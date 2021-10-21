#include <stdio.h>

/*1. define struct with initialization 
struct obj{
	char name[20];
	int x, y;
} Ball;

int main(){
	Ball.x=3;
	
	return 0;
}*/

/*2. union with Little&Big Endian
union A{
	int i;
	char j;
};
union B{
	int i;
	short j;
};

int main(){
	//union A a;
	//a.i=0x12345678;
	//printf("%x", a.j);//78 not 12! 
	
	//union B b;
	//b.i=0x12345678;
	//printf("%x", b.j);//5678 not 8765!
	
	return 0;
}*/

//3. enum
enum {RED=3, BLUE, WHITE=3, BLACK};//3 4 3 4

int main(){
	int palette=RED;
	
	switch(palette){
		case RED:
			printf("RED");
			break;
		case BLUE:
			printf("BLUE");
			break;
		case WHITE:
			printf("WHITE");
			break;
		case BLACK:
			printf("BLACK");
			break;
	}
	
	return 0;
}

/*
1.	����ü ���� ����ü�� ���ǰ� ������ ������ ����ü�� ����� ������ �Ǵٸ� Ÿ��(��)�̱⿡ int�� charó�� ����� �����ϱ� �����̴�.
2.	����ü�� �����ϴ� ���ÿ� ����ü ������ ������ �� �ִ�. 
3.	����ü(union)�� ����ü�� �޸� �޸𸮸� ���� �Ѵ�. 
4.	��ǻ�Ϳ��� �޸𸮿� ���� ������ ��, ���� �ּҰ��� ���� ��Ʈ�� ���� ����� �򿣵��(Big Endian)�̶�� �ϰ�,
	�ݴ�� ���� �ּҰ��� ���� ��Ʈ�� ���� ����� ��Ʋ �����(Little Endian)�̶�� �Ѵ�. ��κ��� x86���μ����� ��Ʋ ����� ����� ����Ѵ�.
	 ��ǻ�ʹ� �ڽ��� �޸𸮿� ���� �����ϴ� ����� ��Ʋ ���������, �� ��������� �˰� ������ ��ȯ�Ͽ� ǥ���Ѵ�. 
5.	�������� ���� ������� �����ϴ� �迭�� ����ѵ�, �����Ϸ��� ������ ������� ���� �Ҵ���� �ؼ��Ѵ�. 
	enum color{}�� ����ó�� ����� ���� �ִ�. color palette=RED;
6.	����ü(union)�� ��� �������ݿ��� �ַ� ����ϴµ�, �޸��� ���鿡���� ���⵵ �ϰ�, �Ʒ��� �ڵ�� ���� ���� ���� buffer�� �ѹ��� ������
	���� ���� struct�� ������� ���� ���� �� �ִ�.
	typedef union comm{
		char buffer[4];
		struct{
			char version;
			char header;
			char length;
			char address;
		}segment;
	}comm;
	
	int main(){
		MessageSend(comm.buffer[0]);
		MessageReceive(comm.segment.version, comm.segment.header, comm.segment.length, comm.segment.address);
		
		return 0;
	}
*/

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
1.	구조체 안의 구조체의 정의가 가능한 이유는 구조체는 사용자 정의의 또다른 타입(형)이기에 int와 char처럼 사용이 가능하기 때문이다.
2.	구조체를 선언하는 동시에 구조체 변수를 생성할 수 있다. 
3.	공용체(union)은 구조체와 달리 메모리를 공유 한다. 
4.	컴퓨터에서 메모리에 수를 저장할 때, 낮은 주소값에 상위 비트를 적는 방식을 빅엔디안(Big Endian)이라고 하고,
	반대로 높은 주소값에 상위 비트를 적는 방식을 리틀 엔디안(Little Endian)이라고 한다. 대부분의 x86프로세서는 리틀 엔디안 방식을 사용한다.
	 컴퓨터는 자신이 메모리에 수를 저장하는 방식이 리틀 엔디안인지, 빅 엔디안인지 알고 적절히 변환하여 표기한다. 
5.	열거형은 여러 상수들을 보관하는 배열과 비슷한데, 컴파일러는 열거형 순서대로 수를 할당시켜 해석한다. 
	enum color{}로 변수처럼 사용할 수도 있다. color palette=RED;
6.	공용체(union)은 통신 프로토콜에서 주로 사용하는데, 메모리적 측면에서도 좋기도 하고, 아래의 코드와 같이 보낼 때는 buffer로 한번에 보내고
	받을 때는 struct의 변수들로 각각 받을 수 있다.
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

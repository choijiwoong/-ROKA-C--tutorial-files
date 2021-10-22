#include <stdio.h>

/*1. concept of void pointer
int main(){
	void *a;
	double b=123.3;
	
	a=&b;
	
	printf("%lf\n", *(double *)a);//casting 
	
	return 0;
}*/

/*2. void pointer (feat. Little Endian)
int read_char(void *p, int byte);

int main(){
	int arr[1]={0x12345678};
	
	printf("%x \n", arr[0]);
	read_char(arr, 4);
}

int read_char(void *p, int byte){
	do{
		printf("%x\n", *(char *)p);
		byte--;
		
		p=(char *)p+1;
	}while(p&&byte);
	
	return 0;
}*/

//3. argument of main function
int main(int argc, char **argv){//not 2nd array pointer. (char *)'s array.
	printf("num of argument: %d\n", argc);
	printf("address of this program: %s\n", argv[0]);//if we put another argument, it's saved to argv sequensely.
	
	return 0;
}

/*
1.	void 형 변수의 선언이 안되는 이유는, 컴파일 때 모든 변수들의 메모리상의 위치가 결정되어야 하기 때문이다. 
	대신 주소값은 8바이트(64 bit)로 정해져있으니 void형 포인터로 타 자료형의 주소값 저장이 가능하다.
	 이때, 그냥 void의 값을 참조하게 되면 자료형이 정해져있지 않아 얼만큼 메모리를 읽어야하는지 모르기 때문에, 자료형을 캐스팅을 통해 정할 수 있다. 
2.	순전히 주소값 만을 받기 위해서는 어떠한 형태의 포인터 주소값도 가능하다는 의미를 가진 void형 포인터를 사용하는 것이 바람직하다. 
3.	Little Endian에서 87, 65, 43, 21순이 아닌 78, 56, 34, 12순인 이유는  저장의 단위가 바이트이므로 한 바이트 내에선 우리가 생각하는 순서대로 저장되기 때문이다. 
4.	main함수의 위와같은 인자를 운영체제가 넣어주고 있다. 프로그램을 실행시키는 순간, 이 프로그램의 main함수 첫번 째 인자가 "void; main's argument.exe"인 것이다.
	단순히 cmd에서 프로그램 이름 뒤에 다른 문자를 써줌으로써 여러 다른 인자를 넣을 수 있다. 
*/

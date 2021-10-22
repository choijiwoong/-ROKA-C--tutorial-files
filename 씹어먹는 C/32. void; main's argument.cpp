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
1.	void �� ������ ������ �ȵǴ� ������, ������ �� ��� �������� �޸𸮻��� ��ġ�� �����Ǿ�� �ϱ� �����̴�. 
	��� �ּҰ��� 8����Ʈ(64 bit)�� ������������ void�� �����ͷ� Ÿ �ڷ����� �ּҰ� ������ �����ϴ�.
	 �̶�, �׳� void�� ���� �����ϰ� �Ǹ� �ڷ����� ���������� �ʾ� ��ŭ �޸𸮸� �о���ϴ��� �𸣱� ������, �ڷ����� ĳ������ ���� ���� �� �ִ�. 
2.	������ �ּҰ� ���� �ޱ� ���ؼ��� ��� ������ ������ �ּҰ��� �����ϴٴ� �ǹ̸� ���� void�� �����͸� ����ϴ� ���� �ٶ����ϴ�. 
3.	Little Endian���� 87, 65, 43, 21���� �ƴ� 78, 56, 34, 12���� ������  ������ ������ ����Ʈ�̹Ƿ� �� ����Ʈ ������ �츮�� �����ϴ� ������� ����Ǳ� �����̴�. 
4.	main�Լ��� ���Ͱ��� ���ڸ� �ü���� �־��ְ� �ִ�. ���α׷��� �����Ű�� ����, �� ���α׷��� main�Լ� ù�� ° ���ڰ� "void; main's argument.exe"�� ���̴�.
	�ܼ��� cmd���� ���α׷� �̸� �ڿ� �ٸ� ���ڸ� �������ν� ���� �ٸ� ���ڸ� ���� �� �ִ�. 
*/

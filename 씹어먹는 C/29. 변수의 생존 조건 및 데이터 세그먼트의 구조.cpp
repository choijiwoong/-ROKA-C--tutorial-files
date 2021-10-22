#include <stdio.h>

/*1. static variable
int* function(){
	static int a=2;
	return &a;
}

int main(){
	int *pa=function();
	printf("%d \n", *pa);
	
	return 0;
}*/

int global=3;

int main(){
	int i;
	char *str="Hello, Baby";//RO
	char arr[20]="WHATTHEHECK";
	
	printf("global: %p\n", &global);//2
	printf("i: %p\n", &i);//4
	printf("str: %p\n", str);//1
	printf("arr: %p\n", arr);//3
	
	return 0;
} 

/*
1.	��������(local variable)�� �޸� ���� ����(global variable)�� �޸��� ������ ����(Data segment)�� �Ҵ�ȴ�.
	������������ ���� �� �ڵ����� 0���� �ʱ�ȭ�ȴ�. ���������� ��� �Լ����� ������ �����ϱ⿡, ��� �� ������ �����Ͽ� ����ؾ� �Ѵ�. like private to public
2.	�Ϲ������� ���ǵ� �������� �ڽ��� ���ǵ� ������ �������� �� �ı��ȴ�. �̿� �ݴ��, ������ ���������� �ı����� �ʴ� ������ ���� ����(static variable)�̶�� �Ѵ�. 
	�̶� function�� ������� �ʴ��� �̹� ���� ������ ���ǵǾ� �ִ� �����̸�, static a�� �� �ѹ� �����̵Ǳ⿡ function�Լ��� ������ ȣ���ص� �ʱ�ȭ���� �ʴ´�. 
	 static variable�� ���� ������ ���� �����Ϳ����� ����ǰ�, ���α׷��� ����� �� �ı��ȴ�. �굵 default0���� ���´�. 
3.	C��� ��ü�����δ� ���ð� ���� �������� ������, ��κ��� �ü������ ���α׷��� �����ϸ� ���� ���ÿ����� �����Ͽ� ����� �ȴ�. 
	 ���α׷� ���� �� ���α׷��� RAM�� �ö���� �Ǵµ�, �̶� RAM���� �ö���� ���α׷��� ������ ũ�� ������ �ڵ� ���׸�Ʈ(Code Segment)�� ������ ���׸�Ʈ(Data Segment)�� ���� �� �ִ�. 
	������ ���������� ��ó�ϴ� ������, ���� ������ �þ�� ũ�Ⱑ �Ʒ���(�޸� �ּ� ������)�����ϴٰ� ���������� �ı��Ǹ� �ٽ� ������ ũ��� ���� �پ��� �ȴ�.
	��, ������ �þ�� ������ �޸� �ּҰ� �������� ����(�Ʒ�)�̴�. 
4.	������ ���׸�Ʈ�� ������ ������ �����ϴ� ���� ������, �����ϰ� ������ ǥ���غ��Ҵ�.
	[Stack(ex. local variable)-> <-Heap] -> Data section(ex. global variable, static variable)->Read-Only Data->Code segment
	������ �޸� �ּҰ� ������ 
5.	�ٸ� scope���� ���� �̸��� static variable�� �־� ���� Data segment�� ���ٰ� �ϴ��� �����Ϸ� ���忡���� �ٸ� scope�� ���ǵǾ��⿡ �ٸ� ������� �����Ѵ�. 
*/

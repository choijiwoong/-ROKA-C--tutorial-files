#include <stdio.h>

/*1. concept of typedef
struct HUMAN{
	int age;
	int height;
	int weight;
	int gender;
};
typedef struct HUMAN Human;

typedef int CAL_TYPE;

int main(){
	CAL_TYPE input, a, b;
	
	while(1){
		printf("calculator\n1. add\n2. subtract\n3. exit\n");
		scanf("%d", &input);
		if(input==1){
			printf("num: ");
			scanf("%d%d", &a, &b);
			printf("sum: %d\n", a+b);
		} else if (input ==2){
			printf("num: ");
			scanf("%d%d", &a, &b);
			printf("sum: %d\n", a-b);
		}else{
			break;
		}
	}
	return 0;
}*/

/*2. application of typedef
int add(int a, int b){return a+b;}

typedef int CAL_TYPE;
typedef int (*Padd)(int, int);//function pointer to name Padd
typedef int Arrays[10];

int main(){
	CAL_TYPE a=10;
	Arrays arr={1,2,3,4,5,6,7,8,9,0};//int arr[10];
	Padd ptr=add;//int (*ptr)(int, int)=add;
	
	printf("a: %d\n", a);
	printf("arr[3]: %d\n", arr[3]);
	printf("add(3, 5): %d\n", ptr(3, 5));
	
	return 0;
}*/

/*3. volatile keyword for no optimization like protocol
typedef struct SENSOR{
	int sensor_flag;//sence=1, null=0
	int data;
} SENSOR; 

int main(){
	volatile SENSOR *sensor;
	
	while(!(sensor->sensor_flag)){}//compiler is too smart, changes like that
	//if(!(sensor->sensor_flag)){ while(1){}}
	
	printf("Data: %d\n", sensor->data);
	
	return 0;
}*/

//4. #pragma
#pragma pack(1)

struct Weird{
	char arr[2];
	int i;
}; 

int main(){
	struct Weird a;
	printf("size: %d\n", sizeof(a));//8! not 6 because of double word boundary
	
	return 0;
}

/*header*/
#pragma once
struct Weird{
	char arr[2];
	int i;
};

/*
1.	typedef�� �̿��Ͽ� Ÿ���� �̸��� �ٲ� ���ִµ�, �̴� �ַ� ����ü�� ������ �� Ȥ��, ���α׷����� �ڵ��� ����Ÿ���� ��Ȳ�� ����
	�ٲپ� ���� �� ���ȴ�. �Լ��� �����ͳ� ũ�Ⱑ ������ �迭 ���� �����ӵ� �� �� �ִ�.
2.	volatile�� ��κ� �ܺ� �ϵ����� ����� �� ����ϴ� Ű�����̴�. �Ϲ������� �ܺ� ��ſ��� ���� ���Դ����� loop�� Ȯ���ϴµ�,
	�����Ϸ��� ���ϰ� �ȶ��Ͽ� �� �ڵ带 ���� �������� loop�� �ϰ� �ٲٴµ�, �̷��� ������ �ذ��ϱ� ���� ����ȭ �ɼ��� �������� 
	�ٸ� �ڵ�鵵 ����ȭ�� �ȵǱ⿡ �ս��� Ŀ����. 
	 volatile Ű���带 �ٿ��ְԵǸ�, �����Ϸ��� sensor�� ���� �ƹ��� ����ȭ�� �������� �ʰ� �ȴ�. 
3.	#pragma�� �����Ϸ����� �����ϴ� ��ó���� ����̴�(�����Ϸ� ����) 
	 double word boundary�� �ϵ���� �� ��� �����ε�, ���� SCSI�������̽�(PC���� �ϵ�� �ֺ���� ���� ��� ���)�� �б����� ������ ���� 6����Ʈ�� ��ɾ �����Ѵ�.
	�� 6����Ʈ�� ��ɾ ������ ������ �����Ͽ� ����ü�� ���� ����ϴµ�, ���Ͱ��� ����ϸ� ũ�Ⱑ 8����Ʈ�� �����Ǿ� � ������ ���� �� ������ �Ұ���������.
	 ��� �̷��� ��Ȳ�� ���� ���� �����Ϸ��� �Ͽ��� ����ü�� ���� ���� ��迡 ���� ����� �ϰ� ���� �� pragmaŰ���带 �̿��Ѵ�. 
	pack(1)�� 1����Ʈ ������ �����϶�� ������, ����ü�� ũ�Ⱑ 1�� ����� �ǰ� �϶�� ���̴�. 1�ܿ� 2, 4, 8, 16���� �� �� �ִµ�, �⺻�� �� ���� ���� ���� pack(4)�� �ϸ� �ȴ�. 
4.	���Ϻ��ҿ��� ��������Ǹ� ���� ���� C�� �⺻ ��ó���� ����� #indef���� ���� ����Ҽ��� ������, pragma�� ����ϸ� �� ���� �� �� �ִ�. 
	�ֽô��� ������Ͽ� #pragma once�� �ְԵǸ�, �����Ϸ��� �Ͽ��� �� ������ �� �ѹ��� include�ȴٴ°� �����ش�. ������ �ð��� ����ȴ�! 
*/

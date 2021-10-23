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
1.	typedef를 이용하여 타입의 이름을 바꿀 수있는데, 이는 주로 구조체를 정의할 때 혹은, 프로그램에서 코드의 변수타입을 상황에 따라
	바꾸어 심을 때 사용된다. 함수의 포인터나 크기가 지정된 배열 역시 리네임드 할 수 있다.
2.	volatile은 대부분 외부 하드웨어와 통신할 때 사용하는 키워드이다. 일반적으로 외부 통신에서 값이 들어왔는지를 loop로 확인하는데,
	컴파일러는 과하게 똑똑하여 위 코드를 값이 있을때만 loop를 하게 바꾸는데, 이러한 문제를 해결하기 위해 최적화 옵션을 꺼버리면 
	다른 코드들도 최적화가 안되기에 손실히 커진다. 
	 volatile 키워드를 붙여주게되면, 컴파일러는 sensor에 대해 아무런 최적화를 수행하지 않게 된다. 
3.	#pragma는 컴파일러에게 전달하는 전처리기 명령이다(컴파일러 종속) 
	 double word boundary는 하드웨어 간 통신 때문인데, 예로 SCSI인터페이스(PC에서 하드와 주변기기 연결 통신 방식)는 읽기명령을 내리기 위해 6바이트의 명령어를 전송한다.
	이 6바이트의 명령어를 내리는 구조가 복잡하여 구조체를 흔히 사용하는데, 위와같이 사용하면 크기가 8바이트로 설정되어 어떤 문제가 생길 지 예측이 불가능해진다.
	 고로 이러한 상황을 막기 위해 컴파일러로 하여금 구조체를 더블 워드 경계에 놓지 말라고 하고 싶을 때 pragma키워드를 이용한다. 
	pack(1)은 1바이트 단위로 정렬하라는 뜻으로, 구조체의 크기가 1의 배수가 되게 하라는 것이다. 1외에 2, 4, 8, 16등이 올 수 있는데, 기본값 즉 더블 워드 경계는 pack(4)로 하면 된다. 
4.	파일분할에서 헤더재정의를 막기 위해 C의 기본 전처리기 명령인 #indef같은 것을 사용할수도 있지만, pragma를 사용하면 더 쉽게 할 수 있다. 
	애시당초 헤더파일에 #pragma once를 넣게되면, 컴파일러로 하여금 이 파일이 딱 한번만 include된다는걸 말해준다. 컴파일 시간도 절약된다! 
*/

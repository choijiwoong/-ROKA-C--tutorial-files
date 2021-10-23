#include <stdio.h>

//fscanf부터 마저 

/*1. concept of file location indicator
int main(){
	FILE *fp=fopen("some_data.txt", "r");//There is some data in this FILE!!!!
	char data[10];
	char c;
	
	if(hp==NULL){
		printf("file open error!\n");
		return 0;
	}
	
	fgets(data, 5, fp);
	printf("input data: %s\n", data);//Ther
	
	c=fgetc(fp);
	printf("next char: %c\n", c);//e
	
	fseek(fp, -1, SEEK_CUR);
	c=fgetc(fp);
	printf("what char will be printed?: %c\n", c);//e
	
	fclose(fp);
	
	return 0;
} */

/*2. necessity of initialization of file location indicator when change write to read by fseek or fflush
int main(){
	FILE *fp=fopen("some_data.txt", "r+");//There is some data in this FILE!!!!
	char c;
	
	if(fp==NULL){
		printf("fail!\n");
		return 0;
	}
	
	while((c=fgetc(fp)!=EOF)){
		if(65<=c&&c<=90){//A
			fseek(fp, -1, SEEK_CUR);//back one space
			fputc(c+32, fp);//print
			
			fseek(fp, 0, SEEK_CUR);
		} else if(97<=c&&c<=122){//a
			fseek(fp, -1, SEEK_CUR);
			fputc(c-32, fp);
			
			fseek(fp, 0, SEEK_CUR);//or fflush(fp);
		}
	}
	
	fclose(fp);
	
	return 0;
}*/

//3. 

/*
1.	스트림의 기본 모토는 '순차적으로 입력을 받는다'이다. fgetc이 실행될 떄마다 다음 문자를 입력받을 수 있는 이유는 파일 위치 지시자가
	다음에 입력 받을 위치를 기억해놓기 때문이다. 
	 파일 위치 지시자의 위치를 사용자 마음대로 바꿀 수있는 여러 함수들 중 fseek함수가 있는데, int fseek(FILE* stream, long int offset, int origin);처럼 생겼다.
	stream에는 파일 위치 지시자를 옮기고 싶은 스트림의 포인터, origin은 어디서부터 옮길지, offset은 얼만큼 옮길지에 대한 정보를 넣는다.
2.	파일의 맨 마지막 데이터를 갖고 올 떄는 fseek(fp, -1, SEEK_END);와 같이 되어야 하는데, 그냥 SEEK_END에는 EOF가 있기 때문에 우리가 원하는 정보는 SEEK_END에서 -1인 곳에 있다.
3.	읽기 및 쓰기 방식으로 r+와 w+가 있는데, r+는 파일이 존재하지 않는다면 열지 않고, 존재한다면 파일의 내용을 유지한다.
	다만 w+는 파일이 존재하지 않으면 새로 만들고, 파일이 존재한다면 내용을 지워버린다. 
	 이 외에도 append기능("a")으로 파일 뒤에 내용을 덧붙일 수 있다.  a+는 읽기&덧붙이기를 번갈아 할 수 있다. 
	append는 파일을 소중하게 보호할 때 적절하다. 
4.	스트림 작업에서 쓰기->읽기로 작업을 변환할 때는 반드시 fflush함수를 호출하거나 fseek나 rewind같은 함수를 호출하여 파일 위치 지정자를 다시 설정해주어야하기 때문이다. like iterator in C++
	 
*/ 

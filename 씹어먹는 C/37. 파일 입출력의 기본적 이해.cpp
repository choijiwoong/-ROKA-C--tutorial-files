#include <stdio.h>

int main(){
	FILE *fp;//FILE struct define! 
	fp=fopen("a.txt", "r");//return pointer that points stream that is made by fopen
	char buf[20];
	
	if(fp==NULL){//must!!
		printf("read error\n");
		return 0;
	}
	
	//fputs("Start Of 군생활!!!\n", fp); "w"
	fgets(buf, 20, fp);
	printf("content: %s\n", buf);
	
	fclose(fp);//if not, stream stil alive with "w" status!
	
	//close standard stream by using fclose
	fclose(stdout);
	printf("aaa");
	
	return 0;
}

/*
1.	fopen은 우리가 지정한 파일과 소통할 수 있는 스트림을 만들어 준다. 
2.	우리가 printf함수만 생각하더라도 모니터마다 출력하는 방식이 다르지만 출력이 되었는데, 그 이유는 스트림에 있다.
	스트림은 두 개의 완전한 다른 장치들을 이어주는 파이프로, 운영체제가 구현하고 처리해준다. 
3.	모니터와 키보드에 대한 스트림은 포준 스트림(standard stream)으로 프로그랭이 싱행될 때 자동으로 생성된다.
	여기서 모니터에 대한 스트림은 stdout, 키보드의 스트림은 stdin, 오류에 대한 스트림은 stderr이 있는데 이는 stdout과 거의 동일하다(단지 오류메시지 출력) 
4.	fopen에서 파일의 경로를 작성할 때 \가 아닌 \\를 쓰는 이유는 \하나만 쓰면 escape character에 따라 이상한 문자가 되기에 \\로 표시한다.
5.	fclose로 표준 스트림들도 닫을 수 있다. 
6.	fgets로 파일의 내용을 읽어올 수 있다. 
	fgetc로 문자하나를 읽어올 수 있는데, 읽은 것이 EOF인지를 비교하여 파일의 크기를 알 수도 있다. 
7.	파일위치지정자(Position Indicator)를 옮기려면 fseek(fp, 0, SEEK_SET);  fp안의 위치지정자를 SEEK_SET으로부터 0칸뒤로 옮긴다. 
*/

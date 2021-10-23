#include <stdio.h>

int main(){
	FILE *fp;//FILE struct define! 
	fp=fopen("a.txt", "r");//return pointer that points stream that is made by fopen
	char buf[20];
	
	if(fp==NULL){//must!!
		printf("read error\n");
		return 0;
	}
	
	//fputs("Start Of ����Ȱ!!!\n", fp); "w"
	fgets(buf, 20, fp);
	printf("content: %s\n", buf);
	
	fclose(fp);//if not, stream stil alive with "w" status!
	
	//close standard stream by using fclose
	fclose(stdout);
	printf("aaa");
	
	return 0;
}

/*
1.	fopen�� �츮�� ������ ���ϰ� ������ �� �ִ� ��Ʈ���� ����� �ش�. 
2.	�츮�� printf�Լ��� �����ϴ��� ����͸��� ����ϴ� ����� �ٸ����� ����� �Ǿ��µ�, �� ������ ��Ʈ���� �ִ�.
	��Ʈ���� �� ���� ������ �ٸ� ��ġ���� �̾��ִ� ��������, �ü���� �����ϰ� ó�����ش�. 
3.	����Ϳ� Ű���忡 ���� ��Ʈ���� ���� ��Ʈ��(standard stream)���� ���α׷��� ����� �� �ڵ����� �����ȴ�.
	���⼭ ����Ϳ� ���� ��Ʈ���� stdout, Ű������ ��Ʈ���� stdin, ������ ���� ��Ʈ���� stderr�� �ִµ� �̴� stdout�� ���� �����ϴ�(���� �����޽��� ���) 
4.	fopen���� ������ ��θ� �ۼ��� �� \�� �ƴ� \\�� ���� ������ \�ϳ��� ���� escape character�� ���� �̻��� ���ڰ� �Ǳ⿡ \\�� ǥ���Ѵ�.
5.	fclose�� ǥ�� ��Ʈ���鵵 ���� �� �ִ�. 
6.	fgets�� ������ ������ �о�� �� �ִ�. 
	fgetc�� �����ϳ��� �о�� �� �ִµ�, ���� ���� EOF������ ���Ͽ� ������ ũ�⸦ �� ���� �ִ�. 
7.	������ġ������(Position Indicator)�� �ű���� fseek(fp, 0, SEEK_SET);  fp���� ��ġ�����ڸ� SEEK_SET���κ��� 0ĭ�ڷ� �ű��. 
*/

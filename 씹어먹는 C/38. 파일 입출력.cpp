#include <stdio.h>

//fscanf���� ���� 

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
1.	��Ʈ���� �⺻ ����� '���������� �Է��� �޴´�'�̴�. fgetc�� ����� ������ ���� ���ڸ� �Է¹��� �� �ִ� ������ ���� ��ġ �����ڰ�
	������ �Է� ���� ��ġ�� ����س��� �����̴�. 
	 ���� ��ġ �������� ��ġ�� ����� ������� �ٲ� ���ִ� ���� �Լ��� �� fseek�Լ��� �ִµ�, int fseek(FILE* stream, long int offset, int origin);ó�� �����.
	stream���� ���� ��ġ �����ڸ� �ű�� ���� ��Ʈ���� ������, origin�� ��𼭺��� �ű���, offset�� ��ŭ �ű����� ���� ������ �ִ´�.
2.	������ �� ������ �����͸� ���� �� ���� fseek(fp, -1, SEEK_END);�� ���� �Ǿ�� �ϴµ�, �׳� SEEK_END���� EOF�� �ֱ� ������ �츮�� ���ϴ� ������ SEEK_END���� -1�� ���� �ִ�.
3.	�б� �� ���� ������� r+�� w+�� �ִµ�, r+�� ������ �������� �ʴ´ٸ� ���� �ʰ�, �����Ѵٸ� ������ ������ �����Ѵ�.
	�ٸ� w+�� ������ �������� ������ ���� �����, ������ �����Ѵٸ� ������ ����������. 
	 �� �ܿ��� append���("a")���� ���� �ڿ� ������ ������ �� �ִ�.  a+�� �б�&�����̱⸦ ������ �� �� �ִ�. 
	append�� ������ �����ϰ� ��ȣ�� �� �����ϴ�. 
4.	��Ʈ�� �۾����� ����->�б�� �۾��� ��ȯ�� ���� �ݵ�� fflush�Լ��� ȣ���ϰų� fseek�� rewind���� �Լ��� ȣ���Ͽ� ���� ��ġ �����ڸ� �ٽ� �������־���ϱ� �����̴�. like iterator in C++
	 
*/ 

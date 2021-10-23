#include <stdio.h>

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

/*3. fscanf
int main(){
	FILE *fp=fopen("some_data.txt", "r");//There is some data in this FILE!!!!
	char data[100];
	
	if(fp=NULL){
		printf("file open error!\n");
		return 0;
	}
	
	printf("---words---\n");
	
	while(fscanf(fp, "%s", data)!=EOF)//for read each words
		printf("%s\n", data);
	
	fclose(fp);
	
	return 0;
}*/

/*4. change special word in file
#include <string.h>

int main(){
	FILE *fp=fopen("some_data.txt", "r+");
	char data[100];
	
	if(fp==NULL){
		printf("file open error\n");
		return 0;
	}
	
	while(fscanf(fp, "%s", data)!=EOF){
		if(strcmp(data, "this")==0){
			fseek(fp, -(long)strlen("this"), SEEK_CUR);
			fputs("that", fp);//cover
			
			fflush(fp);//for change write to read
		}
	}
	
	fclose(fp);
	
	return 0;
}*/

//5. upgraded library manage program
#include <stdlib.h>

struct BOOK{
	char book_name[30];
	char auth_name[30];
	char publ_name[30];
	int borrowed;
};
typedef struct BOOK BOOK;

char compare(char *str1, char *str2);
int register_book(BOOK *book_list, int *nth);
int search_book(BOOK *book_list, int total_num_book);
int borrow_book(BOOK *book_list);
int return_book(BOOK *book_list);

int main(){
	int user_choice;
	int num_total_book=0;
	BOOK *book_list;
	
	printf("Set max size of library: ");
	scanf("%d", &user_choice);
	book_list=(BOOK *)malloc(sizeof(BOOK)*user_choice);
	
	while(true){
		printf("[Library manage program]\n");
		printf("choice menu\n");
		printf("1. add new book\n");
		printf("2. search book\n");
		printf("3. borrow book\n");
		printf("4. return book\n");
		printf("5. save list as txt file\n");
		printf("6. exit program\n");
		scanf("%d", &user_choice);
		
		if(user_choice==1){
			register_book(book_list, &num_total_book);
		} else if(user_choice==2){
			search_book(book_list, num_total_book);
		} else if(user_choice==3){
			borrow_book(book_list);
		} else if(user_choice==4){
			return_book(book_list);
		} else if(user_choice==5){
			
		} else if(user_choice==6){//The reason we use if not switch. for escape loop
			break;
		}
	}
	
	free(book_list);
	return 0;
}

int register_book(BOOK *book_list, int *nth){
	printf("title: ");
	scanf("%s", book_list[*nth].book_name);
	
	printf("author: ");
	scanf("%s", book_list[*nth].auth_name);
	
	printf("publisher: ");
	scanf("%s", book_list[*nth].publ_name);
	
	book_list[*nth].borrowed=0;
	
	(*nth)++;
	
	return 0;
}
int search_book(BOOK *book_list, int total_num_book){
	int user_input;
	int i;
	char user_search[30];
	
	printf("search element choice\n");
	printf("1. title\n");
	printf("2. author\n");
	printf("3. publisher\n");
	scanf("%d", &user_input);
	
	printf("type word for search: ");
	scanf("%s", user_search);
	
	if(user_input==1){
		for(i=0; i<total_num_book; i++)
			if(compare(book_list[i].book_name, user_search))
				printf("id: %d // title: %s // author: %s // publisher: %s\n", i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
	} else if(user_input==2){
		for(i=0; i<total_num_book; i++)
			if(compare(book_list[i].auth_name, user_search))
				printf("id: %d // title: %s // author: %s // publisher: %s\n", i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
	} else if(user_input==3){
		for(i=0; i<total_num_book; i++)
			if(compare(book_list[i].publ_name, user_search))
				printf("id: %d // title: %s // author: %s // publisher: %s\n", i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
	}
	
	return 0;
}
char compare(char *str1, char *str2){
	while(*str1){
		if(*str1!=*str2){
			return 0;
		}
		str1++;
		str2++;
	}
	if(*str2=='\0')
		return 1;
	return 0;
}
int borrow_book(BOOK *book_list){
	int book_num;
	
	printf("type book id: ");
	scanf("%d", &book_num);
	
	if(book_list[book_num].borrowed==1){
		printf("it's already borrowed!\n");
	} else{
		book_list[book_num].borrowed=1;
		printf("borrowed!\n");
	}
	
	return 0;
}
int return_book(BOOK *book_list){
	int num_book;
	
	printf("type book id:");
	scanf("%d", &num_book);
	
	if(book_list[num_book].borrowed==0){
		printf("it's already returned!\n");
	} else{
		book_list[num_book].borrowed=0;
		printf("returned!\n");
	}
	
	return 0;
}

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
5.	fscanf�� scanf�� ���� �����ѵ�, ���̴� ������ ��Ʈ�������� �Է��� ���� ���ִ� �Ϲ�ȭ�� �Լ���� �� ���̴�.
	��, fscanf(stdin, "%s", data);�� scanf("%s", data);�� ��Ȯ�� ��ġ�Ѵ�. 
6.	register������ ������ �� �ִ�. 
*/ 

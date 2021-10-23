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
5.	fscanf는 scanf와 아주 유사한데, 차이는 임의의 스트림에서도 입력을 받을 수있는 일반화된 함수라는 것 뿐이다.
	즉, fscanf(stdin, "%s", data);는 scanf("%s", data);와 정확히 일치한다. 
6.	register변수를 선언할 수 있다. 
*/ 

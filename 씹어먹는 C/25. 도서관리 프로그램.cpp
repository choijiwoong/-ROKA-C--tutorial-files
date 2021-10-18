#include <stdio.h>

//psi version
int add_book(char (*book_name)[30], char (*auth_name)[30], char (*publ_name)[30], int *borrowed, int *num_total_book);
int search_book(char (*book_name)[30], char (*auth_name)[30], char (*publ_name)[30], int num_total_book);
int compare(char *str1, char *str2);
int borrow_book(int *borrowed);
int return_book(int *borrowed);

int main(){
	int user_choice;//menu user choose
	int num_total_book=0;//current number of books
	
	char book_name[100][30], auth_name[100][30], publ_name[100][30];
	int borrowed[100];
	
	while(true){
		printf("[library manage program]\n");
		printf("choose menu you want to do\n");
		printf("1. Add new book\n");
		printf("2. Search book\n");
		printf("3. Borrow book\n");
		printf("4. Return book\n");
		printf("5. exit\n");
		
		printf("show your choice: ");
		scanf("%d", &user_choice);
		
		if(user_choice==1)
			add_book(book_name, auth_name, publ_name, borrowed, &num_total_book);
		else if(user_choice==2)
			search_book(book_name, auth_name, publ_name, num_total_book);
		else if(user_choice==3)
			borrow_book(borrowed);
		else if(user_choice==4)
			return_book(borrowed);
		else if(user_choice==5)
			break;
	}
	
	return 0;
} 
//Func add book
int add_book(char (*book_name)[30], char (*auth_name)[30], char (*publ_name)[30], int *borrowed, int *num_total_book){
	printf("title of book you want to add: ");
	scanf("%s", book_name[*num_total_book]);
	
	printf("author of book you want to add: ");
	scanf("%s", auth_name[*num_total_book]);
	
	printf("publisher of book you want to add: ");
	scanf("%s", publ_name[*num_total_book]);
	
	borrowed[*num_total_book]=0;//not borrow
	printf("book is added successfully!\n");
	(*num_total_book)++;
	
	return 0;
}

//Func search book
int search_book(char (*book_name)[30], char (*auth_name)[30], char (*publ_name)[30], int num_total_book){
	int user_input;
	int i;
	char user_search[30];
	
	printf("which thing you will search with?\n");
	printf("1. search by title\n");
	printf("2. search by author\n");
	printf("3. search by publisher\n");
	scanf("%d", &user_input);
	
	printf("type word will be searched: ");
	scanf("%s", user_search);
	
	printf("result of search\n");
	if(user_input==1){
		for(i=0; i<num_total_book; i++){
			if(compare(book_name[i], user_search)){
				printf("id: %d // title of book: %s // author: %s // publisher: %s\n", i, book_name[i], auth_name[i], publ_name[i]);
			}
		}
	} else if(user_input==2){
		for(i=0; i<num_total_book; i++){
			if(compare(auth_name[i], user_search)){
				printf("id: %d // title of book: %s // author: %s // publisher: %s\n", i, book_name[i], auth_name[i], publ_name[i]);
			}
		}
	} else if(user_input==3){
		for(i=0; i<num_total_book; i++){
			if(compare(publ_name[i], user_search)){
				printf("id: %d // title of book: %s // author: %s // publisher: %s\n", i, book_name[i], auth_name[i], publ_name[i]);
			}
		}
	}
	
	return 0;
}
//compare tool for search book
int compare(char *str1, char *str2){
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
//Func borrow book
int borrow_book(int *borrowed){
	int book_num;
	
	printf("type number of book you want to borrow\n");
	printf("number of book: ");
	scanf("%d", &book_num);
	
	if(borrowed[book_num]==1){
		printf("it's already borrowed!\n");
	} else{
		borrowed[book_num=1];
		printf("borrowed!\n");
	}
	
	return 0;
}
//Func return book
int return_book(int *borrowed){
	int num_book;
	
	printf("type number of book you want to return\n");
	printf("number of book: ");
	scanf("%d", &num_book);
	
	if(borrowed[num_book]==0){
		printf("it's already returned\n");
	} else{
		borrowed[num_book]=0;
		printf("it's returned!\n");
	}
	
	return 0;
}

/*
1.	프로그램을 작성하기에 앞서서 생각해 보아야 하는 것들
	-이 프로그램은 무슨 작업을 하는가
	-과연 이 작업이 꼭 필요한 것인가
	-어떠한 환경에서 프로그램이 작동되는가
	-무슨 언어로 개발할 것인가
2.	저자의 경우 3차원 배열을 사용하지 않고, book_name, auth_name, publ_name, borrowed를 사용하였다. 공간 효율적 측면에서 나보다 효율적으로 보인다. 
	또한 add_book함수에서 borrowed를 0으로 초기화해주면서 명확히 정의해주었다. 
3.	prob4. search_book함수를 개략하여 특정한 검색어를 입력했을 때, 그 검색어를 포함하는 문자열도 검색되게 하자. 문자열 탐색 
*/

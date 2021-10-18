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
1.	���α׷��� �ۼ��ϱ⿡ �ռ��� ������ ���ƾ� �ϴ� �͵�
	-�� ���α׷��� ���� �۾��� �ϴ°�
	-���� �� �۾��� �� �ʿ��� ���ΰ�
	-��� ȯ�濡�� ���α׷��� �۵��Ǵ°�
	-���� ���� ������ ���ΰ�
2.	������ ��� 3���� �迭�� ������� �ʰ�, book_name, auth_name, publ_name, borrowed�� ����Ͽ���. ���� ȿ���� ���鿡�� ������ ȿ�������� ���δ�. 
	���� add_book�Լ����� borrowed�� 0���� �ʱ�ȭ���ָ鼭 ��Ȯ�� �������־���. 
3.	prob4. search_book�Լ��� �����Ͽ� Ư���� �˻�� �Է����� ��, �� �˻�� �����ϴ� ���ڿ��� �˻��ǰ� ����. ���ڿ� Ž�� 
*/

#include <stdio.h>
#include <string.h>
#define MAX 30

struct Book{
	char name[MAX];
	char author[MAX];
	char publisher[MAX];
	int borrowed;
}typedef Book;

int register_book(Book *temp, int *num_library);
int compare_str(char *left, char *right);
int search_book(Book *temp, int *num_library);

int main(){
	Book library[100];
	int num_library=0;
	
	int user_choice;
	
	while(true){
		printf("\n[Welcome to library manage program!]\n");
		printf("choose work what you want\n");
		printf("1. Add book\n");
		printf("2. Search book\n");
		printf("3. Borrow book\n");
		printf("4. Return book\n");
		printf("5. Show all list of library\n");
		printf("6. exit\n");
		printf("work number: ");
		scanf("%d", &user_choice);
		printf("\n");
		
		switch(user_choice){
			case 1:
				register_book(&library[num_library], &num_library);
				break;
			case 2:
				search_book(library, &num_library);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				return 0;
				break;
			default:
				break;
		}
		
		printf("\n\n");
	}
	
	
	return 0;
}

int register_book(Book *temp, int *num_library){
	printf("---register book---\n");
	//default setting
	printf("type title of book that you want to register: ");
	scanf("%s",temp->name);
	printf("type author of book that you want to register: ");
	scanf("%s", temp->author);
	printf("type publisher of book that you want to register: ");
	scanf("%s", temp->author);
	temp->borrowed=0;
	//INC num of books
	(*num_library)++;
	printf("Book register success!\n");
	
	return 1;
}
int compare_str(char *left, char *right){//tool of search_book function
	while(*left){
		if(*left!=*right)
			return 0;
		left++;
		right++;
	}
	
	if(*right=='\0')
		return 1;
	else
		return 0;
}

int search_book(Book *temp, int *num_library){
	int user_choice;
	char buffer[MAX]={0,}, user_input[MAX];
	int length_book_str, length_input;
	printf("---search book---\n");
	
	printf("choose search way you want\n");
	printf("1. search by title\n");
	printf("2. search by author\n");
	printf("3. search by publisher\n");
	scanf("%d", &user_choice);
	
	printf("type word: ");
	scanf("%s", user_input);
	length_input=strlen(user_input);
	
	switch(user_choice){
		case 1:
			for(int i=0; i<*num_library; i++){
				length_book_str=strlen(temp[i]->name);
				for(int j=0; j<length_book_str-length_input+1; j++){//for get first char address that we will compare
					for(int k=j+0; k<j+length_input; k++){//save part of temp->name to buffer for using compare_str function
						buffer[k-j]=temp[i]->name[k];
					}
					if(compare_str(buffer, user_input)){
						printf("[book information]\n");
						printf("1. id: %d\n2. title: %s\n3. author: %s\n4. publisher: %s\n5. borrow: ", i, temp[i]->name, temp[i]->author, temp[i]->publisher);
						if(temp[i]->borrowed)
							printf("possible\n");
						else
							printf("impossible\n");
						return 1;
					}
				}
			}
			printf("no book in library!\n");
			break;
			
		case 2:
			for(int i=0; i<*num_library; i++){
				length_book_str=strlen(temp[i]->author);
				for(int j=0; j<length_book_str-length_input+1; j++){//for get first char address that we will compare
					for(int k=j+0; k<j+length_input; k++){//save part of temp->name to buffer for using compare_str function
						buffer[k-j]=temp[i]->name[k];
					}
					if(compare_str(buffer, user_input)){
						printf("[book information]\n");
						printf("1. id: %d\n2. title: %s\n3. author: %s\n4. publisher: %s\n5. borrow: ", i, temp[i]->name, temp[i]->author, temp[i]->publisher);
						if(temp[i]->borrowed)
							printf("possible\n");
						else
							printf("impossible\n");
						return 1;
					}
				}
			}
			printf("no book in library!\n");
			break;
			
		case 3:
			for(int i=0; i<*num_library; i++){
				length_book_str=strlen(temp[i]->publisher);
				for(int j=0; j<length_book_str-length_input+1; j++){//for get first char address that we will compare
					for(int k=j+0; k<j+length_input; k++){//save part of temp->name to buffer for using compare_str function
						buffer[k-j]=temp[i]->name[k];
					}
					if(compare_str(buffer, user_input)){
						printf("[book information]\n");
						printf("1. id: %d\n2. title: %s\n3. author: %s\n4. publisher: %s\n5. borrow: ", i, temp[i]->name, temp[i]->author, temp[i]->publisher);
						if(temp[i]->borrowed)
							printf("possible\n");
						else
							printf("impossible\n");
						return 1;
					}
				}
			}
			printf("no book in library!\n");
			break;
			
		default:
			printf("wrong input\n");
			break;
	}
	
	return 1;
}

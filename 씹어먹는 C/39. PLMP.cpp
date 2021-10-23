//final upgrade version of library manage program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "39. PLMP.h"

int main(){
	int user_choice;
	int num_total_book=0;
	BOOK *book_list;
	int i;
	
	printf("set maximum size of library: ");
	scanf("%d", &user_choice);
	book_list=(BOOK *)malloc(sizeof(BOOK)*user_choice);//make BOOK array
	
	while(true){
		printf("[library manage program]\nchoose menu\n1. add book\n2. search book\n3. borrow book\n4. return book\n5. make txt file\n6. get data to txt file\n7. print book list\n8. exit\n");
		printf("choice: ");
		scanf("%d", &user_choice);
		
		if(user_choice==1)
			register_book(book_list, &num_total_book);
		else if(user_choice==2)
			search_book(book_list, num_total_book);
		else if(user_choice==3)
			borrow_book(book_list);
		else if(user_choice==4)
			return_book(book_list);
		else if(user_choice==5)
			textize_book_list(book_list, num_total_book);
		else if(user_choice==6)
			retrieve_book_info(&book_list, &num_total_book);
		else if(user_choice==7){
			for(i=0; i<num_total_book; i++){
				printf("%20s//%20s//%20s//", book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
				printf("%20s\n",book_list[i].borrowed==0?"NO":"YES");
			}
		} else if(user_choice==8)
			break;
	}
	
	free(book_list);
	return 0;
}

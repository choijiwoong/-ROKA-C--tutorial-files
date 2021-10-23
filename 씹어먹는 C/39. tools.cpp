#include <stdio.h>
#include "39. PLMP.cpp"

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
int textize_book_list(BOOK *book_list, int total_num_book){
	FILE *fp=fopen("book_list.txt", "w");
	int i;
	
	if(fp==NULL){
		printf("fprint error!\n");
		return -1;
	}
	
	fprintf(fp, "%d\n", total_num_book);//for convenience of retrieve_book_info
	for(i=0; i<total_num_book; i++){
		fprintf(fp, "%s\n%s\n%s\n%s\n", book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name, book_list[i].borrowed==0?"NO":"YES");
	}
	
	printf("complete!\n");
	fclose(fp);
	
	return 0;
}
int retrieve_book_info(BOOK **book_list, int *total_num_book){
	FILE *fp=fopen("book_list.txt", "r");
	int total_book;
	int i;
	char str[10];
	
	if(fp==NULL){
		printf("file open error!\n");
		return -1;
	}
	
	fscanf(fp, "%d", &total_book);
	(*total_num_book=total_book);
	
	free(*book_list);
	(*book_list)=(BOOK *)malloc(sizeof(BOOK)*total_book);//realloc
	
	if(*book_list=NULL){
		printf("\nERROR\n");
		return -1;
	}
	
	for(i=0; i<total_book; i++){
		fscanf(fp, "%s", (*book_list)[i].book_name);//no book_list[i]->book_name! book_list in this function, pointer of BOOK*; BOOK **
		fscanf(fp, "%s", (*book_list)[i].auth_name);
		fscanf(fp, "%s", (*book_list)[i].publ_name);
		fscanf(fp, "%s", str);
		
		if(compare(str, "YES"))
			(*book_list)[i].borrowed=1;
		else if(compare(str, "NO"))
			(*book_list)[i].borrowed=0;
	}
	
	fclose(fp);
	return 0;
}
char compare(char *str1, char *str2){
	while(*str1){
		if(*str1!=*str2)
			return 0;
		str1++;
		str2++;
	}
	if(*str2=='\0')
		return 1;
	return 0;
}

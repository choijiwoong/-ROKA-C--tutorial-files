typedef struct BOOK{
	char book_name[30];
	char auth_name[30];
	char publ_name[30];
	int borrowed;
} BOOK;

int register_book(BOOK *book_list, int *nth);
int search_book(BOOK *book_list, int total_num_book);
int borrow_book(BOOK *book_list);
int return_book(BOOK *book_list);
int textize_book_list(BOOK *book_list, int total_num_book);
int retrieve_book_info(BOOK **book_list, int *total_num_book);
char compare(char *str1, char *str2);

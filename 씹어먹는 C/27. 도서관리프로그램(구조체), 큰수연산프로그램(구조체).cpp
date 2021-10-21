#include <stdio.h>
#include <string.h>

/*prob.1 library manage program
struct Book{
	char name[MAX];
	char author[MAX];
	char publisher[MAX];
	int borrowed;
}typedef Book;

int register_book(Book *temp, int *num_library);
int compare_str(char *left, char *right);
int search_book(Book *temp, int *num_library);
int borrow_book(Book *temp, int *num_library);
int return_book(Book *temp, int *num_library);
int show_all(Book *temp, int *num_library);

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
				register_book(&library[num_library], &num_library);//pass one element
				break;
			case 2:
				search_book(library, &num_library);//pass whole array 
				break;
			case 3:
				borrow_book(library, &num_library);
				break;
			case 4:
				return_book(library, &num_library);
				break;
			case 5:
				show_all(library, &num_library);
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
	scanf("%s", temp->publisher);
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
				length_book_str=strlen(temp[i].name);
				for(int j=0; j<length_book_str-length_input+1; j++){//for get first char address that we will compare
					for(int k=j+0; k<j+length_input; k++){//save part of temp->name to buffer for using compare_str function
						buffer[k-j]=temp[i].name[k];
					}
					if(compare_str(buffer, user_input)){
						printf("[book information]\n");
						printf("1. id: %d // 2. title: %s // 3. author: %s // 4. publisher: %s // 5. borrow: ", i, temp[i].name, temp[i].author, temp[i].publisher);						
						if(temp[i].borrowed)
							printf("impossible\n");
						else
							printf("possible\n");
						return 1;
					}
				}
			}
			printf("no book in library!\n");
			break;
			
		case 2:
			for(int i=0; i<*num_library; i++){
				length_book_str=strlen(temp[i].author);
				for(int j=0; j<length_book_str-length_input+1; j++){//for get first char address that we will compare
					for(int k=j+0; k<j+length_input; k++){//save part of temp->name to buffer for using compare_str function
						buffer[k-j]=temp[i].author[k];
					}
					if(compare_str(buffer, user_input)){
						printf("[book information]\n");
						printf("1. id: %d // 2. title: %s // 3. author: %s // 4. publisher: %s // 5. borrow: ", i, temp[i].name, temp[i].author, temp[i].publisher);						
						if(temp[i].borrowed)
							printf("impossible\n");
						else
							printf("possible\n");
						return 1;
					}
				}
			}
			printf("no book in library!\n");
			break;
			
		case 3:
			for(int i=0; i<*num_library; i++){
				length_book_str=strlen(temp[i].publisher);
				for(int j=0; j<length_book_str-length_input+1; j++){//for get first char address that we will compare
					for(int k=j+0; k<j+length_input; k++){//save part of temp->name to buffer for using compare_str function
						buffer[k-j]=temp[i].publisher[k];
					}
					if(compare_str(buffer, user_input)){
						printf("[book information]\n");
						printf("1. id: %d // 2. title: %s // 3. author: %s // 4. publisher: %s // 5. borrow: ", i, temp[i].name, temp[i].author, temp[i].publisher);
						if(temp[i].borrowed)
							printf("impossible\n");
						else
							printf("possible\n");
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

int borrow_book(Book *temp, int *num_library){
	int input_id;
	
	printf("type book id you want to borrow: ");
	scanf("%d", &input_id);
	
	if(temp[input_id].borrowed==1){
		printf("it's already borrowed! you can't borrow it\n");
	}else{
		temp[input_id].borrowed=1;
		printf("borrowed!\n");
	}
	
	return 1;
}

int return_book(Book *temp, int *num_library){
	int input_id;
	
	printf("type book id you want to return: ");
	scanf("%d", &input_id);
	
	if(temp[input_id].borrowed==0){
		printf("wrong number! it's not borrowed\n");
	}else{
		temp[input_id].borrowed=0;
		printf("returned!\n");
	}
	
	return 1;
}

int show_all(Book *temp, int *num_library){
	printf("[Library list]\n");
	for(int i=0; i<*num_library; i++){
		printf("1. id: %d // 2. title: %s // 3. author: %s // 4. publisher: %s // 5. borrow: ", i, temp[i].name, temp[i].author, temp[i].publisher);
		if(temp[i].borrowed)
			printf("impossible\n");
		else
			printf("possible\n");
	}
	
	return 1;
}*/

//prob.2 big num: overflow
struct BigNum{
	int i_digit[100];//integer part
	int d_digit[100];//decimal part
	int i_total_digit;//num of i_digit
	int d_total_digit;//num of d_digit
	char sign;//+: 1, -: 0
}typedef BigNum;

BigNum set_BigNum(char *temp);
int show_BigNum(const BigNum *temp);

int main(){
	char number1[]="-2394465465116516124.7116516511918919283124";
	BigNum bn1=set_BigNum(number1);
	show_BigNum(&bn1);
	
	char number2[]="1251321165417375.53116519191919185919851915165132484634343415";
	BigNum bn2=set_BigNum(number2);
	show_BigNum(&bn2);
	
	return 0;
}

BigNum set_BigNum(char *temp){//make char array to BigNum struct
	BigNum result;//define BigNum struct for return
	if(temp[0]=='-'){
		result.sign=0;
		temp++;//good idea!
	} else if(temp[0]=='+'){
		result.sign=1;
		temp++;
	} else{
		result.sign=1;
	}

	int length=strlen(temp);//get array's length
	int dot_location;//for distinguishing digit part, decimal part
	int i;//variable for loop
	
	//get dot location
	for(dot_location=0; dot_location<length; dot_location++){
		if(temp[dot_location]=='.'){
			break;
		}
	}
	if(dot_location==length){//no dot
		dot_location=-1;
	}
	
	//get i_digit
	for(i=0; i<dot_location; i++){
		result.i_digit[i]=temp[i]-48;//char to num
	}
	if(dot_location==-1)//if no dot
		result.i_total_digit=length;
	else
		result.i_total_digit=dot_location;//(count not index)
	
	//get d_digit
	if(dot_location==-1){//if no dot
		result.d_total_digit=0;
	} else{
		for(i=dot_location+1; i<length; i++){
			result.d_digit[i-(dot_location+1)]=temp[i]-48;//char to num
		}
		result.d_total_digit=length-(dot_location+1);//real length- index
	}
	
	//return BigNum
	return result;
}

int show_BigNum(const BigNum *temp){
	int i;
	if(temp->sign)
		printf("+");
	else
		printf("-");
	
	for(i=0; i<temp->i_total_digit; i++){
		printf("%d",temp->i_digit[i]);
	}
	
	printf(".");
	
	for(i=0; i<temp->d_total_digit; i++){
		printf("%d", temp->d_digit[i]);
	}
	
	printf("\n");
	
	return 1;
}

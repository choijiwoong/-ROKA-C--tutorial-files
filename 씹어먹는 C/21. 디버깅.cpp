#include <stdio.h>

/*1. debugging by using search expression 
int main(){
	int arr[10];
	int i;
	
	for(i=0; i<10; i++)
		scanf("%d", &arr[i]);
	for(i=0; i<=10; i++)
		printf("%d\n", arr[i]);
		
	return 0;
}*/

/*2. text segment
int main(){
	char str[]="hello";//it's defined in stack that can modify memory.
	char *pstr="GLASSY";//GOOD! it's defined in text segment
	
	str[1]='a';
	str[1]='a';//BAD! it's possible only read because it's in text segment
	
	printf("%s",*pstr);
	
	return 0;
} */

/*3. string
int copy_str(char *dest, char *src);
int add_str(char *dest, char *src);
int compare(char *str1, char *str2);

int main(){
	char str1[]="hello";
	char str2[]="hi";
	
	printf("before copy: %s\n", str1);
	copy_str(str1, str2);
	printf("after copy: %s\n", str1);
	
	
	char str3[100]="the";
	char str4[]=" sentence";
	
	printf("before add: %s\n", str3);
	add_str(str3, str4);
	printf("after add: %s\n", str3);
	
	
	char str5[100]="Hello!";
	char str6[100]="Good Bye!";
	
	if(compare(str5, str6)){
		printf("same!\n");
	} else{
		printf("different!\n");
	}
	
	return 0;
}

int copy_str(char *dest, char *src){//copy src to dest
	while(*src){
		*dest=*src;
		src++;
		dest++;
	}
	*dest=NULL;//important! if it's not NULL, it will print "hillo"
	
	return 1;
}
int add_str_MYVERSION(char *dest, char *src){
	int i, j;
	for(i=0; dest[i]!='\0'; i++){}//get length of dest
	
	for(j=0; src[j]!='\0'; j++){
		dest[i]=src[j];
		i++;
	}
	dest[i+j]='\0';
	
	return 1;
}
int add_str(char *dest, char *src){//we get pointer!
	while(*dest)
		dest++;
	
	while(*src){
		*dest=*src;
		src++;
		dest++;
	}
	
	*dest='\0';
	
	return 1;
}
int compare(char *str1, char *str2){
	while(*str1){
		if(*str1!=*str2)
			return 0;
		
		str1++;
		str2++;
	}
	
	if(*str2=='\0')
		return 1;
		
	return 0;
}*/

//prob.5 library

int ADD_BOOK(char (*DB)[4][30], int *book_count);
int search_book(char (*DB)[4][30], int *book_count);
int search_author(char (*DB)[4][30], int *book_count);
int search_publisher(char (*DB)[4][30], int *book_count);
int borrow_book(char (*DB)[4][30], int *book_count);
int return_book(char (*DB)[4][30], int *book_count);

int compare_str(char *str1, char *str2){//1 same 0 different
	while(*str1){
		if(*str1!=*str2){
			return 0;
		} else{
			str1++;
			str2++;
		}
	}
	
	if(*str2=='\0')
		return 1;
	return 0;
}

int main(){
	char DB[100][4][30]={0,};
	int book_count=0;
	printf("Welcome to library!\n");
	while(1){
		int work;
		printf("\nChoose work you want[book: %d]\n", book_count);
		printf("1. search book\n2. search author\n3. search publisher\n4. borrow book\n5. return book\n6. exit\n");
		scanf("%d", &work);
		
		switch(work){
			case -1:
				printf("\n[BOOK LIST]\n");
				for(int i=0; i<book_count; i++)
						printf("%d: %s %s %s\n", i, DB[i][0], DB[i][1], DB[i][2], DB[i][3]);
				break;
			case 0:
				ADD_BOOK(DB, &book_count);
				break;
			case 1:
				search_book(DB, &book_count);
				break;
			case 2:
				search_author(DB, &book_count);
				break;
			case 3:
				search_publisher(DB, &book_count);
				break;
			case 4:
				borrow_book(DB, &book_count);
				break;
			case 5:
				return_book(DB, &book_count);
				break;
			case 6:
				return 0;
				break;
			default:
				printf("you type wrong number!\n");
				break;
		}
		printf("\n\n");
	}
	
	return 0;
}

int ADD_BOOK(char (*DB)[4][30], int *book_count){
	/*
	const int password=1234;
	int input_password;
	printf("input password: ");
	scanf("%d", &input_password);
	if(input_password!=password){
		printf("wrong access!\n");
		return 1;
	}*/
	
	printf("input New Book's title, author, publisher information!\n");
	scanf("%s %s %s", DB[*book_count][0], DB[*book_count][1], DB[*book_count][2]);
	(*book_count)++;//not *book_count++ because of priority of operator
	
	printf("%d Add book success!\n",*book_count);
	return 0;
}
int search_book(char (*DB)[4][30], int *book_count){//****problem is DB[*book_count][0] is empty
	char input[100];
	printf("input title of book you want to search: ");
	scanf("%s", input);
	
	for(int i=0; i<*book_count; i++){
		if(compare_str(DB[i][0], input)){
			printf("<%s's information>\n1. title: %s\n2. author: %s\n3. publisher: %s\n4. borrow: %s", input, DB[i][0], DB[i][1], DB[i][2]);
			return 0;
		}
	}
	printf("book: %s is not in library!\n", input);
	
	return 0;
}
int search_author(char (*DB)[4][30], int *book_count){
	char input[100];
	printf("input author of book you want to search: ");
	scanf("%s", input);
	
	for(int i=0; i<*book_count; i++){
		if(compare_str(DB[i][1], input)){
			printf("<%s's information>\n1. title: %s\n2. author: %s\n3. publisher: %s\n4. borrow: %s", input, DB[i][0], DB[i][1], DB[i][2]);
			return 0;
		}
	}
	printf("author: %s is not in library!\n", input);
	
	return 0;
}
int search_publisher(char (*DB)[4][30], int *book_count){
	char input[100];
	printf("input publisher of book you want to search: %d");
	scanf("%s", input);
	
	for(int i=0; i<*book_count; i++){
		if(compare_str(DB[i][2], input)){
			printf("<%s's information>\n1. title: %s\n2. author: %s\n3. publisher: %s\n4. borrow: %s", input, DB[i][0], DB[i][1], DB[i][2]);
			return 0;
		}
	}
	printf("publisher: %s is not in library!\n", input);
	
	return 0;
}
int borrow_book(char (*DB)[4][30], int *book_count){
	char input[100];
	printf("input title of book you want to borrow: ");
	scanf("%s", input);
	
	for(int i=0; i<*book_count; i++){
		if(compare_str(DB[i][0], input) && DB[*book_count][3][0]==0){
			DB[*book_count][3][0]=1;
			printf("borow success!\n", input, DB[i][0], DB[i][1], DB[i][2]);
			return 0;
		}
	}
	printf("book: %s cannot be borrow!\n", input);
	
	return 0;
}
int return_book(char (*DB)[4][30], int *book_count){
	char input[100];
	printf("input title of book you want to return: ");
	scanf("%s", input);
	
	for(int i=0; i<*book_count; i++){
		if(compare_str(DB[i][0], input) && DB[*book_count][3][0]==1){
			DB[*book_count][3][0]=0;
			printf("return success!\n", input, DB[i][0], DB[i][1], DB[i][2]);
			return 0;
		}
	}
	printf("book: %s cannot be returned!\n", input);
	
	return 0;
}


/*24
1.	VS���� ������� ���������� ������� �̿��Ͽ� �� ������ ���� Ȯ���� �� �ִ�. 
2.	���ڿ��� ���� ��Ÿ���� NULL���ڴ� '\0', 0, (char)NULL�� ǥ���� �� �ִ�. 
3.	���ڿ��� ==�� �ϸ� �ȵǴ� ������ ���ڿ��� �̸��� �����ͷ� �Ͻ��� ��ȯ�� �Ǳ⿡ �ش� ==�񱳴� �޸� �ּҰ��� ������ ���� �񱳰� �ƴϴ�. 
4.	fflush(stdin);�� ���� stdin���۸� ��� �� ������, gcc�� ��� �̷��� �۾��� ���� ���� ���ɼ��� ũ�⿡ vs�� 2015���� fflush�� ��ó�� �۵����� �ʴ´�.
	��� getchar();�� ����Ѵ�. getchar�� �ѹ��ڸ� stdin���� �о���°��ε�, �������Ǵ� stdin�� \n�� ���� �� �ֱ⿡ ���ȴ�. 
5.	���ڸ� �Է��ϴ� scanf���� 123abc���� ���� �Է��ϸ�, sacnf�� ���ڰ� �ƴ� ���� ���� �� �Է��� ���߱� ������ getchar()�� �ص�
	���ۿ� bc���� �͵��� �����ְ� �Ǳ⿡ ���� ������ ����Ų��. ��� scanf������ �ǵ��� %c�� ������� �ʴ°��� ����.
	 �� ���� �ϳ��� �Է¹޴´ٸ� %s���ڿ��� �Է¹ް� �� ���� ���� �ϳ��� ���ϴ� ������ ����� ���� ����. 

6.	���ͷ�(literal)�̶� �ҽ� �ڵ�󿡼� ������ ���� ������ ������, Ư�� C���� ""�� ���� �͵��� ���ڿ� ���ͷ�(string literal)�̶�� �θ���.
7.	�ü���� �����Ϸ� ������ ���� �ٸ�����, ��� ���α׷��� ����Ǿ� �޸𸮿� �ε�Ǹ� text segment, data segment, bss segment, heap, stack�� 5���� ������ �����ϰ� �ȴ�.
	�̶�, text segment���� ���α׷� �ڵ�� ���, ���ͷ����� ���ǵȴ�. (�б⸸ ����) 
8.	�Լ��� ����⿡ �ʼ������� �Լ��� � �۾��� �ϴ����� ���� �ڼ��� ����, ������, ���ڰ� �ִ�. 
9.	char str[100];
	str="abcdefg";�� �ȵǴ� ������ �迭�� �̸��� ù��° ���Ҹ� ����Ű�� �����ͷ� ����ε�, �� ������� ���ͷ������͸� �־� �����Ϸ��ϰ� �ֱ� �����̴�. 
	 �ٸ� C���� ������� ���Ǹ� ���� char str[100]="abcdefg";�� �����ϰ� �صξ���. �̴� �迭�� ������ ���� ����� �����ϴ�.
10.	 
*/

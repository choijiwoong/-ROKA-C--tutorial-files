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
1.	VS에는 디버깅의 인터프리터 조사식을 이용하여 매 변수의 값을 확인할 수 있다. 
2.	문자열의 끝을 나타내는 NULL문자는 '\0', 0, (char)NULL로 표시할 수 있다. 
3.	문자열에 ==를 하면 안되는 이유는 문자열의 이름은 포인터로 암시적 변환이 되기에 해당 ==비교는 메모리 주소값의 비교이지 값의 비교가 아니다. 
4.	fflush(stdin);을 통해 stdin버퍼를 비울 수 있지만, gcc의 경우 이러한 작업을 하지 않을 가능성이 크기에 vs도 2015부터 fflush가 위처럼 작동하지 않는다.
	고로 getchar();을 사용한다. getchar는 한문자만 stdin에서 읽어오는것인데, 문제가되는 stdin의 \n을 빼낼 수 있기에 사용된다. 
5.	숫자를 입력하는 scanf에서 123abc같은 것을 입력하면, sacnf는 숫자가 아닌 것을 읽을 때 입력을 멈추기 때문에 getchar()을 해도
	버퍼에 bc같은 것들이 남아있게 되기에 많은 문제를 일으킨다. 고로 scanf에서는 되도록 %c를 사용하지 않는것이 좋다.
	 정 문자 하나를 입력받는다면 %s문자열로 입력받고 맨 앞의 문자 하나만 취하는 식으로 만드는 것이 좋다. 

6.	리터럴(literal)이란 소스 코드상에서 고정된 값을 가지는 것으로, 특히 C언어에서 ""로 묶인 것들을 문자열 리터럴(string literal)이라고 부른다.
7.	운영체제나 컴파일러 구성에 따라 다르지만, 대게 프로그램이 실행되어 메모리에 로드되면 text segment, data segment, bss segment, heap, stack의 5가지 영역이 존재하게 된다.
	이때, text segment에서 프로그램 코드와 상수, 리터럴등이 정의된다. (읽기만 가능) 
8.	함수를 만들기에 필수조건은 함수가 어떤 작업을 하는지에 대한 자세한 설명, 리턴형, 인자가 있다. 
9.	char str[100];
	str="abcdefg";가 안되는 이유는 배열의 이름은 첫번째 원소를 가리키는 포인터로 상수인데, 그 상수값에 리터럴데이터를 넣어 변경하려하고 있기 때문이다. 
	 다만 C언어에서 사용자의 편의를 위해 char str[100]="abcdefg";는 가능하게 해두었다. 이는 배열을 정의할 때만 사용이 가능하다.
10.	 
*/

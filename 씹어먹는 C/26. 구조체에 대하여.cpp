#include <stdio.h>

/*1. normal use of struct
struct Books{
	char name[30];
	char auth[30];
	char publ[30];
	int borrowed;//not initialization in definition of struct!
}; 

int main(){
	struct Books book_list[3];
	int i;
	
	for(i=0; i<3; i++){
		printf("type information of %d's book: ", i);
		scanf("%s%s%s", book_list[i].name, book_list[i].auth, book_list[i].publ);
		book_list[i].borrowed=0;
	}
	
	for(i=0; i<3; i++){
		printf("----------------------\n");
		printf("information of %s\n", book_list[i].name);
		printf("author: %s\n", book_list[i].auth);
		printf("publisher: %s\n", book_list[i].publ);
		
		if(book_list[i].borrowed==0)
			printf("not borrowed!\n");
		else
			printf("borrowed!\n");
	}
	
	return 0;
}*/

/*2. importance of operator priority
int add_one(int *a);
struct TEST{
	int c;
	int *pointer;
};

int main(){
	struct TEST t;
	printf("t.c: %d\n", t.c);//get initial value
	struct TEST *pt=&t;
	int i=0;
	
	t.pointer=&i;
	*t.pointer=3;
	printf("i: %d\n", i);
	
	*pt->pointer=4;//priority of -> is higher than *, & (ex. add_one(&pt->c);)
	add_one(&pt->c);//add 1
	
	printf("i: %d, c: %d\n", i, t.c);
	
	
	return 0;
}
int add_one(int *a){
	(*a)++;//be careful!
	return 0;
}*/

/*3. assign operator = on struct
char copy_str(char *dest, char *src);
struct TEST{
	int i;
	char str[20];
};

int main(){
	struct TEST a, b;
	
	b.i=3;
	copy_str(b.str, "hello, world");
	
	a=b;//assign
	
	b.str[2]='F';//for check memory copy
	
	printf("a.str: %s\na.i: %d\n", a.str, a.i);//well copied!
	
	return 0;
}
char copy_str(char *dest, char *src){
	while(*src){
		*dest=*src;
		src++;
		dest++;
	}
	
	*dest='\0';
	
	return 1;
}*/

//4. struct int argument of function
struct TEST{
	int age;
	int gender;
	char name[20];
};
int set_human(struct TEST *a, int age, int gender, cosnt char *name);
char copy_str(char *dest, const char *src);

int main(){
	struct TEST human;
	set_human(&human, 10, 1, "Lee");
	printf("AGE: %d // Gender: %s // Name: %s\n", human.age, human.gender, human.name);
	
	return 0;
}

int set_human(struct TEST *a, int age, int gender, const char *name){
	a->age=age;
	a->gender=gender;
	copy_str(a->name, name);
	
	return 0;
}
char copy_str(char *dest, const char *src){
	while(*src){
		*dest=*src;
		src++;
		dest++;
	}
	*dest='\0';
	
	return 1;
}


/*
1.	배열로 모든 정보를 표현하기에는 같은 타입의 데이터만 담아야 하기에 많은 정보를 담으려면 여러 배열이 필요하고, 
	그러면 코드가 지저분해지는 문제점이 필연적이기에 구조체가 도입된다. 
2.	구조체 포인터로 멤버에 접근할 때, (*ptr).a=1이 아닌 *ptr.a=1를 하게 되면 연산자 우선순위를 따라서 ptr.a를 먼저 실행 후 그 값에 *를 한것에 1을 대합하게 된다.
	이러한 복잡함을 없애기 위해 ptr->a=1;이 등장하였다. 
3.	대입연산자=을 이용하여 같은 구조체 타입을 대입할 수 있다.
4.	구조체가 등장하면서 &와 *, ->등과의 연산자 우선순위가 더욱 중요해 졌다. 
	중요한 것만 다시 잡고 가면 ->가 1순위, &와 *가 2순위이다. 
*/

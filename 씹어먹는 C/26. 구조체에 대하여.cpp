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
1.	�迭�� ��� ������ ǥ���ϱ⿡�� ���� Ÿ���� �����͸� ��ƾ� �ϱ⿡ ���� ������ �������� ���� �迭�� �ʿ��ϰ�, 
	�׷��� �ڵ尡 ������������ �������� �ʿ����̱⿡ ����ü�� ���Եȴ�. 
2.	����ü �����ͷ� ����� ������ ��, (*ptr).a=1�� �ƴ� *ptr.a=1�� �ϰ� �Ǹ� ������ �켱������ ���� ptr.a�� ���� ���� �� �� ���� *�� �ѰͿ� 1�� �����ϰ� �ȴ�.
	�̷��� �������� ���ֱ� ���� ptr->a=1;�� �����Ͽ���. 
3.	���Կ�����=�� �̿��Ͽ� ���� ����ü Ÿ���� ������ �� �ִ�.
4.	����ü�� �����ϸ鼭 &�� *, ->����� ������ �켱������ ���� �߿��� ����. 
	�߿��� �͸� �ٽ� ��� ���� ->�� 1����, &�� *�� 2�����̴�. 
*/

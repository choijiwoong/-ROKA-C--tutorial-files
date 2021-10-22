#include <stdio.h>
#include <stdlib.h>

/*1. struct allocation
struct SomeThing{
	int a;
	int b;
};

int main(){
	struct SomeThing *arr;
	int size, i;
	
	printf("size: ");
	scanf("%d", &size);
	
	arr=(struct SomeThing*)malloc(sizeof(struct SomeThing)*size);//we must use sizeof operator to struct!
	//for prevention of error that's caused by double word boundary
	
	for(i=0; i<size; i++){
		arr[i].a=i;
		arr[i].b=i-1;
	}
	
	free(arr);
}*/

/*2. Node
struct Node* InsertNode(struct Node* current, int data);
void DestroyNode(struct Node* destroy, struct Node* head);
struct Node* CreateNode(int data);
void PrintNodeFrom(struct Node* from);

struct Node{
	int data;
	//struct Node* prevNode;
	struct Node* nextNode;
};

int main(){
	struct Node* Node1=CreateNode(100);
	struct Node* Node2=InsertNode(Node1, 200);
	struct Node* Node3=InsertNode(Node2, 300);
	struct Node* Node4=InsertNode(Node2, 400);
	
	PrintNodeFrom(Node1);
	
	return 0;
}
//PRINT
void PrintNodeFrom(struct Node* from){
	while(from){//if anything is in from
		printf("data of Node: %d\n", from->data);//data print
		from=from->nextNode;//++
	}
}
//INSERT
struct Node* InsertNode(struct Node* current, int data){
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));//make new node that will be inserted
	
	newNode->data=data;//set data to data of argument
	newNode->nextNode=current->nextNode;//set next pointer to current->nextNode
	
	current->nextNode=newNode;//it's also Node pointer; Node*
	
	return newNode;
}
//DELETE
void DestroyNode(struct Node* destroy, struct Node* head){//delete destroy at head
	struct Node* next=head;
	
	if(destroy==head){//if you want to delete head
		free(destroy);
		return;
	}
	while(next){
		if(next->nextNode==destroy)//find!
			next->nextNode=destroy->nextNode;//change nextNode to destroy's nextNode for skip(delete)
		next=next->nextNode;//++ for keep searching. (if find destroy, now next->nextNode is destroy->nextNode->nextNode)
	}
	
	free(destroy);//anyway, we want to delete destroy!
}
//CREATE
struct Node* CreateNode(int data){
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	
	newNode->data=data;
	newNode->nextNode=NULL;
	
	return newNode;
}*/

//3. mem func 
#include <string.h>

int main(){
	/* 1. memcpy
	char str[50]="I love chicken";
	char str2[50];
	char str3[50];
	
	memcpy(str2, str, strlen(str)+1);//null
	memcpy(str3, "hello", 6);
	
	printf("%s\n", str);
	printf("%s\n", str2);
	printf("%s\n", str3);
	*/
	
	/*2. memmove
	char str[50]="I love chicken";
	
	printf("%s\n", str);
	memmove(str+12, str+2, 4);
	printf("%s", str);*/
	
	//3. memcmp
	int arr[10]={1,2,3,4,5};
	int arr2[10]={1,2,3,4,5};
	
	//if same, return 0 else, other value not 0
	if(memcmp(arr, arr2, 5)==0)//it compares 5 bytes NOT 5 elements!
		printf("same!\n");
	else
		printf("different!\n");
	
	return 0;
}

/*
1.	����ü ���� �Ϲ����� ������� �����Ҵ��� �����ϴ�. �̶� ������ ���� sizeof(struct Something)*size�� �ƴ� ���� ũ�⸦ ����Ͽ� ���� ���
	��� �׷��� ���� ���� �ֱ� ������ ���� �߻� ���ɼ��� �ִ�.
	 �� ������ ������� ���(double word boundary)�� Ȱ��(application)�����ε�, ��ǻ�Ͱ� �ӵ� ����� �������� ����ü�� ũ�⸦ word�� ���� ������ �� �ֱ� �����̴�.
	��� �׳� sizeof�� �������.
2.	�����Ҵ��� ���, 1000���� �����Ϳ��� 1���� �߰������͸� ���� 1001���� ���ο� malloc�� ��ȿ�����̱⿡ ��尡 ���������.
	���� �߰�/����/������ ������ �������� ���� ������ �Ϸ��� ������ ã�ư��� �ϱ⿡ ���Ҹ� ã�� ��쿣 �迭�� ������ ����.
	 ���� ����� ��� �����Ͱ��� �ܿ� ���� ��带 ����Ű�� ����(nextNode)�� �ʿ��ϱ� ������ ���������ε� �ణ �����̴�.
	��, �߰�/����/������ ���� �Ͼ�� ��� ��尡 ���Ǹ�, ���� Ž���� ���� �Ͽ� �迭�� ���ȴ�.
	 ��� �ܿ��� ����, ť, Ʈ�� �� ���� �ڷᱸ������ �ִ�. 
3.	Cǥ�� ���̺귯������ �����Ǵ� �޸� ���� �Լ��δ� memmove, memcpy, memcmp, memset���� �ִ�. 
	memcpy�� �޸��� Ư���� �κ����κ��� �󸶱����� �κ��� �ٸ� �޸� �������� �������ִ� �Լ��̴�.
	memmove�� �޸��� Ư���� �κ��� ������ �ٸ� �κ����� �Ű��ִ� ��Ȱ�� �ϴµ�, ���� ������ �����Ͱ� ������� ���� �ƴϴ�. 
	 memcpy�� ���������, memmove�� memcpy�� �޸� �޸� ������ ���ĵ� �ȴ�. 
	memcmp�� �� ���� �޸� ������ ���� ���ϴ� �Լ��̴�. 
	 ������ ���� ������ ������ ���ڷ� �����ϴ� ���� �ƴ�, ���� �޸��� ���� ���ڷ� �����ϱ⿡, ��ü �迭�� ���ϰ� �ʹٸ�
	sizeof(int)*5�÷� �־��־���Ѵ�. 
*/

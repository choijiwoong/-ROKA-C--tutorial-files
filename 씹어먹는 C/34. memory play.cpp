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
1.	구조체 역시 일반적인 방법으로 동적할당이 가능하다. 이때 주의할 점은 sizeof(struct Something)*size가 아닌 실제 크기를 계산하여 더할 경우
	사실 그렇지 않을 수도 있기 때문에 오류 발생 가능성이 있다.
	 그 이유는 더블워드 경계(double word boundary)의 활용(application)때문인데, 컴퓨터가 속도 향상을 목적으로 구조체의 크기를 word와 같게 설정할 수 있기 때문이다.
	고로 그냥 sizeof를 사용하자.
2.	동적할당의 경우, 1000개의 데이터에서 1개의 추가데이터를 위해 1001개의 새로운 malloc은 비효율적이기에 노드가 만들어졌다.
	노드는 추가/삭제/삽입이 월등히 편리하지만 원소 접근을 하려면 일일히 찾아가야 하기에 원소를 찾을 경우엔 배열이 월등히 좋다.
	 또한 노드의 경우 데이터공간 외에 다음 노드를 가리키는 공간(nextNode)이 필요하기 때문에 공간적으로도 약간 손해이다.
	즉, 추가/삭제/삽입이 자주 일어나는 경우 노드가 사용되며, 원소 탐색이 잦은 일엔 배열이 사용된다.
	 노드 외에도 스택, 큐, 트리 등 여러 자료구조들이 있다. 
3.	C표준 라이브러리에서 지원되는 메모리 관련 함수로는 memmove, memcpy, memcmp, memset등이 있다. 
	memcpy는 메모리의 특정한 부분으로부터 얼마까지의 부분을 다른 메모리 영역으로 복사해주는 함수이다.
	memmove는 메모리의 특정한 부분의 내용을 다른 부분으로 옮겨주는 역활은 하는데, 이전 공간의 데이터가 사라지는 것은 아니다. 
	 memcpy와 비슷하지만, memmove는 memcpy와 달리 메모리 공간이 겹쳐도 된다. 
	memcmp는 두 개의 메모리 공간을 서로 비교하는 함수이다. 
	 주의할 점은 원소의 개수를 인자로 전달하는 것이 아닌, 비교할 메모리의 수를 인자로 전달하기에, 전체 배열을 비교하고 싶다면
	sizeof(int)*5꼴로 넣어주어야한다. 
*/

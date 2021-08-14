#include "utils.h"

namespace MyExcel{
//***Vector***
//Constructor define
Vector::Vector(int n): data(new string[n]), capacity(n), length(0) {}//be careful of default argument
//push_back define
void Vector::push_back(string s){//add element to last of array. 
	if(capacity<=length){//if size over
		string* temp=new string[capacity*2];//*2 allocation for efficiency of time and space
		for(int i=0;i<length;i++)
			temp[i]=data[i];//data copy to string* temp
		delete[] data;//erase data's address
		data=temp;//data locate temp's address
		capacity*=2;
	}
	
	data[length]=s;
	length++;
}
//operator[] overloading for access random location define
string Vector::operator[](int i){	return data[i];		}
//remove random element define
void Vector::remove(int x){
	for(int i=x+1;i<length;i++)
		data[i-1]=data[i];//overwrite data[i]
	length--;
}	
//return size define
int Vector::size(){	return length;	}
//Destructor of Vector define
Vector::~Vector(){
	if(data){//Is data existing.
		delete[] data;
	}
}
//***Vector End***

//***Stack***
//Constructor define
Stack::Stack():start(NULL, "") {//initialize Node start with initializer list
	current=&start;//initialize current to start
}
//push define
void Stack::push(string s){
	Node* n=new Node(current, s);//make new node with prev node to current
	current=n;//set current new Node* n.
}
//pop define
string Stack::pop(){
	if(current==&start) return "";//exception
	
	string s=current->s;//current s data save for return
	Node* prev=current;//For delete, prev get current's address.
	current=current->prev;//set current to variable current->prev
	
	delete prev;//delete prev that is past current.
	return s;//return data pop
}
//just return without delete define
string Stack::peek(){
	return current->s;
}
//is it empty? define
bool Stack::is_empty(){
	if(current==&start) return true;//if current is bottom.
	return false;//return bool type
}
//Destructor define
Stack::~Stack(){
	while(current!=&start){//if current is not bottom.
		Node* prev=current;
		current=current->prev;
		delete prev;//inifinitly delete.(like pop loof)
	}
}
//***Stack End***

//***NumStack***
NumStack::NumStack():start(NULL, 0){	current=&start;	}
void NumStack::push(double s){
	Node* n=new Node(current, s);
	current=n;
}
double NumStack::pop(){
	if(current==&start)
		return 0;
	
	double s=current->s;
	Node* prev=current;
	current=current->prev;
	
	delete prev;
	return s;
}
double NumStack::peek(){
	return current->s;
}
bool NumStack::is_empty(){
	if(current==&start)
		return true;
	return false;
}
NumStack::~NumStack()
{
	while(current != &start){
		Node* prev=current;
		current=current->prev;
		delete prev;
	}
}
//***NumStack End***
}//MyExcel end

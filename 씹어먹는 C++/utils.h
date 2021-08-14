#ifndef UTILS_H
#define UTHLS_H

#include <iostream>
#include <string>
using std::string;

namespace MyExcel{
//Vector class 
class Vector{
	string* data;//for save data. we will make data by string array.
	int capacity;//allocated size
	int length;//real capacity.
	
	public:
		//Constructor with default argument
		Vector(int i=1);
		//Add new element to back
		void push_back(string s);
		//approach random element
		string operator[](int i);
		//remove element that is located x
		void remove(int x);
		//return vector's size
		int size();
		//Destructor
		~Vector();
};
//Vector class end

//Stack class
class Stack{
	struct Node{
		Node* prev;
		string s;
		
		Node(Node* prev, string s):prev(prev), s(s) {}//Constructor of Node structure.
	};
	Node* current;//for point upper node.
	Node start;//for point lower node. for checking "Is it last node?" with comparing Node* current.
	
	public:
		//Constructor
		Stack();
		//add new element to upper
		void push(string s);
		//return and remove element of upper
		string pop();
		//return element of upper without remove
		string peek();
		//is it empty?
		bool is_empty();
		//Destructor
		~Stack();
};

//NumStack
class NumStack{
	struct Node{
		Node* prev;
		double s;
		
		Node(Node* prev, double s):prev(prev), s(s){}
	};
	Node* current;
	Node start;
	
	public:
		NumStack();
		void push(double s);
		double pop();
		double peek();
		bool is_empty();
		~NumStack();
};
//NumStack end 

}//MyExcel
#endif

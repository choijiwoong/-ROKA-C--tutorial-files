#ifndef UTILS_H
#define UTHLS_H
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

//Cell
class Table;
class Cell{//one space in big table.
	protected:
		int x, y;//cell location
		Table* table;//which table in?
		
		//string data;//for save content in one space.[deleted]
	public:
		//convert data to string
		virtual string stringify()=0;//purize
		//convert data to num(for inheritance to NumberCell, etc.. so virtual!)
		virtual int to_numeric()=0;//purize
		//Constructor
		Cell(int x, int y, Table* table);//no string data
}; 

class StringCell:public Cell{
	string data;
	
	public:
		string stringify();
		int to_numeric();
		
		StringCell(string data, int x, int y, Table* t);
};
class NumberCell:public Cell{
	int data;
	
	public:
		string stringify();
		int to_numeric();
		
		NumberCell(int data, int x, int y, Table* t);
};
class DateCell:public Cell{//for convenience, yyy-mm-dd format defined
	time_t data;
	
	public:
		string stringify();
		int to_numeric();
		
		DateCell(string s, int x, int y, Table* t);
};
class ExprCell:public Cell{
	string data;
	string* parsed_expr;
	
	Vector exp_vec;
	
	int precedence(char c);//return priority of operator
	void parse_expression();//research mathematical expression
	
	public:
		ExprCell(string data, int x, int y, Table* t);
		
		string stringify();
		int to_numeric();
};


//Cell end

//Table
class Table{
	protected:
		int max_row_size, max_col_size;//maximum size of row and column
		Cell*** data_table;//2 tensor array that save Cell* data.
		
	public:
		//Constructor
		Table(int man_row_size, int max_col_size);
		//Destructor
		~Table();
		//register new cell to row, col
		void reg_cell(Cell* c, int row, int col);
		//return numeric value that cell
		int to_numeric(const string& s);//s is name of cell(ex. A3, E7)
		//call cell with row and col
		int to_numeric(int row, int col);
		//return string in that cell
		string stringify(const string& s);
		string stringify(int row, int col);
		//print table.
		virtual string print_table()=0;//pure virtual function **Table object can't be made!** it must inherit
};
//Table end

//TxtTable
class TxtTable:public Table{//order, print Table's content
	string repeat_char(int n, char c);
	//column number to A~Z
	string col_num_to_str(int n);
	
	public:
		TxtTable(int row, int col);
		//print table with text
		string print_table();
};
//TxtTable end

//HtmlTable
class HtmlTable:public Table{
	public:
		HtmlTable(int row, int col);
		
		string print_table();
};
//HtmlTable end

//CSVTable
class CSVTable:public Table{
	public:
		CSVTable(int row, int col);
		
		string print_table();
};
//CSVTable end

//Excel
class Excel{
	Table* current_table;
	
	public:
		Excel(int max_row, int max_col, int choice);
		
		int parse_user_input(string s);
		void command_line();
};
//Excel end 

}//MyExcel
#endif

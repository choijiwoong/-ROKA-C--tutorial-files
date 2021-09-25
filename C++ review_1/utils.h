#ifdef UTILS_H
#define UTILS_H

#include <string>

namespace MyExcel{//tools: Vector, Stack, NumStack
	class Vector{
		private:
			std::string* data;
			int capacity;
			int length;
	
		public:
			Vector(int n=1);
			void Push_back(string s);
			std::string operator[](int i);
			void remove(int x);
			int size();
			~Vector();
	};

	class Stack{//for string
		private:
			struct Node{//for linked list
				Node* prev;
				std::string s;
			
				Node(Node* prev, std::string s): prev(prev), s(s){}
			};
			
			Node* current;
			Node start;
		
		public:
			Stack();
			void push(std::string s);
			std::string pop();
			std::string peek();
			bool is_empty();
			~Stack();
	};
	
	class NumStack{//for number
		private:
			struct Node{
				Node* prev;
				double s;
			
				Node(Node* prev, double s): prev(prev), s(s){}
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
}

namespace MyExcel{
	class Cell{
		protected:
			int x, y;//location information of cell
			Table* table;//Cell information in which table?
			
			string data;//storage
		
		public:
			virtual std::string stringify();
			virtual int to_numeric();
			
			Cell(std::string data, int x, int y, Table* table);
	};
	
	class Table{//abstract class
		protected:
			int max_row_size, max_col_size;//maximum size
			Cell*** data_table;//dememtion 2 array that saves Cell*
			
		public:
			Table(int max_row_size, int max_col_size);
			~Table();
			void reg_cell(Cell* c, int row, int col);
			int to_numeric(const string& s);//s is cell name like B6, A3
			int to_numeric(int row, int col);
			std::string stringify(const string& s);//cell name too
			std::string stringify(int row, int col);
			virtual std::string print_table()=0;//pure virtual function
	};
	
	class TxtTable: public Table{//specialization of Table class by inheritance in case text type.
		private:
			std::string repeat_char(int n, char c);
			std::string col_num_to_str(int n);//A, B...etc
			
		public:
			TxtTable(int row, int col);
			std::string print_table();//print as table
	};
}
#endif

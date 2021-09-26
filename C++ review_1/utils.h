#ifdef UTILS_H
#define UTILS_H


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
	
	
	
	class Cell{
		protected:
			int x, y;//location information of cell
			Table* table;//Cell information in which table?
		
		public:
			virtual std::string stringify()=0;
			virtual int to_numeric()=0;
			
			Cell(int x, int y, Table* table);
	};
	class StringCell: public Cell{
		private:
			std::string data;
		
		public:
			std::string stringify();
			int to_numeric();
			StringCell(std::string data, int x, int y, Table* t);
	};
	class NumberCell: public Cell{
		private:
			int data;
		
		public:
			std::string stringify();
			int to_numeric();
			NumberCell(int data, int x, int y, Table* t);
	};
	class DateCell: public Cell{//only yyyy-mm-dd
		private:
			time_t data;
		public:
			std::string stringify();
			int to_numeric();
			DateCell(std::string s, int x, int y, Table* t);
	};
	class ExprCell: public Cell{
		private:
			std::string data;
			std::string* parsed_expr;
			Vector exp_vec;//for save postfix-notation expression after parse_expression()
		
			//tools for to_numeric(infix notation->postfix notation)
			int precedence(char c);//convert precedence of operator
			void parse_expression();//infix-notation to postfix-notation in exp_vec
		
		public:
			ExprCell(std::string data, int x, int y, Table* t);
			std::string stringify();
			int to_numeric();//calculate postfix-notation
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
	
	
	class HtmlTable : public Table {
 		public:
  			HtmlTable(int row, int col);
  			string print_table();
	};

	class CSVTable : public Table {
 		public:	
  			CSVTable(int row, int col);
  			string print_table();
	};
	
	
	
	
	class Excel{//TUI
		private:
			Table* current_table;//for which table now
		
		public:
			Excel(int max_row, int max_col, int choice);
			
			int parse_user_input(std::string s);//work
			void command_line();
	};
}//END NAMESPACE
#endif

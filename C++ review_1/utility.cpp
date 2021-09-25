#include "utils.h"

namespace MyExcel{//tools: Vector, Stack, NumStack
	//START VECTOR
	Vector::Vector(int n=1): data(new std::string[n], capacity(n), length(0)){}//CONSTRUCTOR
	void Vector::Push_back(std::string s){//PUSH_BACK
		if(capacity<=length){//If allocation is needed
			std::string* temp=new std::string[capacity*2];//type is pointer
			for(int i=0; i<length; i++)
				temp[i]=data[i];
			delete[] data;
			data=temp;//pass by pointer
			capacity*=2;
		}
		data[length]=s;
		length++;
	}
	std::string Vector::operator[](int i){ return data[i]; }//ACESS BY []
	void Vector::remove(int x){//remove element
		for(int i=x+1; i<length; i++)//delete by overwrite
			data[i-1]=data[i];
		length--;
	}
	Vector::~Vector(){//DESTRUCTOR
		if(data)
			delete[] data;
	}
	//END VECTOR
	
	//START STACK
	Stack::Stack(): start(NULL, ""){ current=&start; }//CONSTRUCTOR
	void Stack::push(std::string s){//PUSH
		Node* n=new Node(current, s);//(prev, data)
		current=n;
	}
	std::string Stack::pop(){//POP
		if(current==&start)//no element for pop
			return "";
		
		std::string s=current->s;//for return poped value
		Node* prev=current;//for delete memory(poped Node)
		current=current->prev;//back to prev 
		
		delete prev;
		return s;
	}
	std::string Stack::peek(){ return current->s; }//PEEK
	bool Stack::is_empty(){//IS_EMPTY
		if(current==&start) 
			return true;
		return false;
	}
	Stack::~Stack(){//DESTRUCTOR
		while(current!=&start){//no need for return poped value.
			Node* prev=current;
			current=current->prev;//future to the past!
			delete prev;//just delete memory
		}
	}
	//END STACK
	
	//START NUMSTACK
	NumStack::NumStack(): start(NULL, 0){ current=&start; }
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
	double NumStack::peek(){ return current->s; }
	bool NumStack::is_empty(){
		if(current==&start)
			return true;
		return false;
	}
	NumStack::~NumStack(){
		while(current!=&start){
			Node* prev=current;
			current=current->prev;
			delete prev;
		}
	}
	//END NUMSTACK
}

namespace MyExcel{
	//START CELL
	Cell::Cell(std::string data, int x, int y, Table* table): data(data), x(x), y(y), table(table){}//CONSTRUCTOR
	std::string Cell::stringify(){ return data; }//STRINGIFY
	int Cell::to_numeric(){ return 0; }//NUMERIC
	//END CELL
	
	//START TABLE
	Table::Table(int max_row_size, int max_col_size): max_row_size(max_row_size), max_col_size(max_col_size){//just Let's think as dimention 2 array that has element's type as Cell*
		data_table=new Cell**[max_row_size];//make Cell** as much as max_row_size. one element is Cell*
		for(int i=0; i<max_row_size; i++){//to every row,
			data_table[i]=new Cell*[max_col_size];//make coloum as much ad max_col_size for storage of Cell* that is one element
			for(int j=0; j<max_col_size; j++)
				data_table[i][j]=NULL;//initialization
		}
	}
	Table::~Table(){//DESTRUCTOR
		for(int i=0; i<max_row_size; i++)
			for(int j=0; j<max_col_size; j++)
				if(data_table[i][j])
					delete data_table[i][j];//erase all element
		for(int i=0; i<max_row_size; i++)
			delete[] data_table[i];//erase area of row
		delete[] data_table;//erase area of column
	}
	void Table::reg_cell(Cell* c, int row, int col){//Assign cell*
		if(!(row<max_row_size && col<max_col_size))//exception(out of range) handling
			return;
			
		if(data_table[row][col])//if data exist
			delete data_table[row][col];//erase for saving
			
		data_table[row][col]=c;//assign Cell*
	}
	int Table::to_numeric(const std::string& s){//numeric by Cell name like B6, C1
		int col=s[0]='A';
		int row=atoi(s.c_str()+1)-1;//?????????????????????????
		
		if (row<max_row_size && col<max_col_size)//in range,
			if(data[row][col])//data is exist,
				return data_table[row][col]->to_numeric();//call numeric function
		return 0;
	}
	int Table::to_numeric(int row, int col){//numeric by row, col
		if(row<max_row_size && col<max_col_size && data_table[row][col])
			return data_table[row][col]->to_numeric();
		return 0;
	}
	std::string Table::stringify(const std::string& s){
		int col=s[0]-'A';
		int row=atoi(s.c_str()+1)-1;
		
		if(row<max_row_size && col<max_col_size)
			if(data_table[row][col])
				return data_table[row][dol]->stringify();
		return 0;
	}
	std::string Table::stringify(int row, int col){
		if(row<max_row_size && col<max_col_size && data_table[row][col])
			return data_table[row][col]->stringify();
		return "";
	}
	std::ostream& operator<<(std::ostream& o, Table& table){
		o<<table.print_table();
		return o;
	}
	//END TABLE
	
	//START TXTTABLE
	TxtTable::TxtTable(int row, int col): Table(row, col){}//CONSTRUCTOR
	std::string TxtTable::print_table(){//PRINT CLEAN AS TABLE
		std::string total_table;
		
		int* col_max_wide=new int[max_col_size];
		for(int i=0; i<max_col_size; i++){
			unsigned int max_wide=2;
			for(int j=0; j<max_row_size; j++)
				if(data_table[j][i] && data_table[j][i]->stringify().length()>max_wide)
					max_wide=data_table[j][i]->stringify().length();
			col_max_wide[i]=max_wide;
		}
		
		total_table+="		";
		int total_wide=4;
		for(int i=0; i<max_col_size; i++){
			if(col_max_wide[i]){
				int max_len=max(2, max_col_wide[i]);
				total_table+=" | "+col_num_to_str(i);
				total_table+=repeat_char(max_len-col_num_to_str(i).length(), ' ');
				
				total_wide+=(max_len+3);
			}
		}
		
		total_table+="\n";
		for(int i=0; i<max_row_size; i++){
			total_table+=repeat_char(total_wide, '-');
			total_table+="\n"+to_string(i+1);
			total_table+=repeat_char(4-to_string(i+1).length(), ' ');
			
			for(int j=0; j<max_col_size; j++){
				if(col_max_wide[j]){
					int max_len=max(2, col_max_wide[j]);
					
					std::string s="";
					if(data_table[i][j])
						s=data_table[i][j]->stringify();
					
					total_table+=" | "+s;
					total_table+=repeat_char(max_len- s.length(), ' ');
				}
			}
			total_table+="\n";
		}
		return total_table;
	}
	std::string TxtTable::repeat_char(int n, char c){//REPEAT CHAR
		std::string s="";
		for(int i=0; i<n; i++)
			s.push_back(c);
		return s;
	}
	std::string TxtTable::col_num_to_str(int n){
		std::string s="";
		if(n<26){
			s.push_back('A'+n);
		} else{
			char first='A'+n/26-1;
			char second='A'+n%26;
			
			s.push_back(first);
			s.push_back(second);
		}
		
		return s;
	}
	//END TXTTABLE
}

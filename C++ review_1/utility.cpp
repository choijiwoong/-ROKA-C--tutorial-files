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
	
	
	
	//START CELL
	Cell::Cell(int x, int y, Table* table): x(x), y(y), table(table){}//CONSTRUCTOR
	
	StringCell::StringCell(std::string data, int x, int y, Table* t): data(data), Cell(x, y, t){}
	std::string StringCell::stringify(){ return data; }
	int StringCell::to_numeric(){ return 0; }
	
	NumberCell::NumberCell(int data, int x, int y, Table* t): data(data), Cell(x, y, t){}
	std::string NumberCell::stringify(){ return to_string(data); }
	int NumberCell::to_numeric(){ return data; }//하나씩 쌓아올려 만들어지는 공든 탑. 노력에 배신은 없다
	
	DateCell::DateCell(std::string s, int x, int y, Table* t): Cell(x, y, t){//yyyy-mm-dd
		int year=atoi(s.c_str());
		int month=atoi(s.c_str()+5);
		int day=atoi(s.c_str()+8);
		
		tm timeinfo;//class
		
		//convert input data to tm form for using mktime()
		timeinfo.tm_year=year-1900;
		timeinfo.tm_mon=month-1;
		timeinfo.tm_mday=day;
		timeinfo.tm_hour=0;
		timeinfo.tm_min=0;
		timeinfo.tm_sec=0;
		
		data=mktime(&timeinfo);//naje tm to time_t form
	} 
	std::string DateCell::stringify(){
		char buf[50];
		tm temp;//make tm variable
		localtime_s(&temp, &data);//convert data to tm
		strtime(buf, 50, "%F", &temp);//make it strtime
		
		return std::string(buf);//return as string
	}
	int DateCell::to_numeric(){ return static_cast<int>(data); }//casting
	
	ExprCell::ExprCell(std::string data, int x, int y, Table* t): data(data), Cell(x, y, t){}
	int ExprCell::precedence(char c){
		switch(c){
			case '(':
			case '[':
			case '{':
				return 0;
			case '+':
			case '-':
				return 1;
			case '*':
			case '/':
				return 2;
		}
		return 0;
	}
	void ExprCell::parse_expression(){//to postfix-notation based on rule
		Stack stack;
		//cover input expression(data) to () for prevention of remaining operator in data.
		data.insert(0, "()");
		data.push_back(')');
		
		for(int i=0; i<data.length(); i++){//for all element of data
			if(isalpha(data[i])){//Cell(Number)
				exp_vec.push_back(data.substr(i,2));
				i++;//one more space because of A3
			} else if(isdigit(data[i])){//Number
				exp_vec.push_back(data.substr(i,1));
			} else if(data[i]=='(' || data[i]=='[' || data[i]=='{'){//open parenthesis
				stack.push(data.substr(i, 1));
			} else if(data[i]==')' || data[i]==']' || data[i]=='}'){//closed parenthesis
				string t=stack.pop();//pop until meeting open parenthesis
				while(t!="(" && t!="[" && t!="{"){
					exp_vec.push_back(t);
					t=stack.pop();
				}
			} else if(data[i]=='+' || data[i]=='*' || data[i]=='+' || data[i]=='/'){//operators
				while(!stack.is_empty() && precedence(stack.peek()[0])>=precedence(data[i]))//precedence of stack[0] is higher or same than data[i]
					exp_vec.push_back(stack.pop());//stack pop and exp_vec push
				stack.push(data.substr(i, 1));//just push operator(data[i]) to stack
			}
		}
	}
	int ExprCell::to_numeric(){
		NumStack stack;//for postfixization
		
		for(int i=0; i<exp_vec.size(); i++){//for all element of vector
			std::string s=exp_vec[i];//get one element
			
			if(isalpha(s[0])){//Cell(Number)
				stack.push(table->to_numeric(s));
			} else if(isdigit(s[0])){//Number
				stack.push(atoi(s.c_str()));
			} else{//operator
				double y=stack.pop();
				double x=stack.pop();
				switch(s[0]){
					case '+':
						stack.push(x+y);
						break;
					case '-':
						stack.push(x-y);
						break;
					case '+':
						stack.push(x+y);
						break;
					case '/':
						stack.push(x/y);
						break;
				}
			}
		}//for loop end
		return stack.pop();//result
	}
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
		
		int* col_max_wide=new int[max_col_size];//get column's max_wide
		for(int i=0; i<max_col_size; i++){
			unsigned int max_wide=2;//default value of wide
			for(int j=0; j<max_row_size; j++)
				if(data_table[j][i] && data_table[j][i]->stringify().length()>max_wide)//if stringify_length is bigger than max_wide
					max_wide=data_table[j][i]->stringify().length();//refresh max_wide
			col_max_wide[i]=max_wide;//and save that wide
		}
		
		//information of column upper space.
		total_table+="    ";//space 4
		int total_wide=4;
		for(int i=0; i<max_col_size; i++){//to all column
			if(col_max_wide[i]){//if max_wide is exist
				int max_len=max(2, max_col_wide[i]);//get max_len minimun 2
				total_table+=" | "+col_num_to_str(i);//i to char.
				total_table+=repeat_char(max_len-col_num_to_str(i).length(), ' ');//remain space to ' '
				
				total_wide+=(max_len+3);//max_len + length(" | ")
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
	
	
	HtmlTable::HtmlTable(int row, int col) : Table(row, col) {}

	string HtmlTable::print_table() {
  		string s = "<table border='1' cellpadding='10'>";
  		for (int i = 0; i < max_row_size; i++) {
		    s += "<tr>";
		    for (int j = 0; j < max_col_size; j++) {
	      	s += "<td>";
	      	if (data_table[i][j]) s += data_table[i][j]->stringify();
	      	s += "</td>";
	    	}
	    	s += "</tr>";
  		}
  		s += "</table>";
  		return s;
	}	

	CSVTable::CSVTable(int row, int col) : Table(row, col) {}

	string CSVTable::print_table() {
  		string s = "";
  		for (int i = 0; i < max_row_size; i++) {
		    for (int j = 0; j < max_col_size; j++) {
		        if (j >= 1) s += ",";
    		    string temp;
		        if (data_table[i][j]) temp = data_table[i][j]->stringify();
		
				for (int k = 0; k < temp.length(); k++) {
		        if (temp[k] == '"') {
    	      	temp.insert(k, 1, '"');
		          k++;
	    	    }
	      	}
	      	temp = '"' + temp + '"';
	      	s += temp;
	    	}
	    	s += '\n';
	  	}
	  	return s;
	}
	
	
	
	
	Excel::Excel(int max_row, int max_col, int choice=0){//choice Table type by argument of constructor
		switch(choice){
			case 0:
				current_table=new TxtTable(max_row, max_col);
				break;
			
			case 1:
				current_table=new CSVTable(max_row, max_col);
				break;
			
			default:
				current_table=new HtmlTable(max_row, max_col);
		}
	}
	
	int Excel::parse_user_input(std::string s){
		int next=0;
		std::string command="";
		for(int i=0; i<s.length(); i++){
			if(s[i]==' '){//space
				command=s.substr(0, i);//-1. cut command
				next=i+1;
				break;
			} else if(i==s.length()-1){//well done
				command=s.substr(0, i+1);
				next=i+1;
				break;
			}
		}
		
		std::string to="";
		for(int i=next; i<s.length(); i++){
			if(s[i]==' ' || i==s.length()-1){//space or done
				to=s.substr(next, i-next);//get command
				next=i+1;//set next
				break;
			} else if(i==s.length()-1){//well done
				to=s.substr(0, i+1);//get command
				next=i+1;
				break;
			}
		}
		
		int col=to[0]-'A';
		int row=atoi(to.c_str()+1)-1;
		
		std::string rest=s.substr(next);//get rest(garbage..?)
		
		if(command=="sets"){
			current->table->reg_cell(new StringCell(rest, row, col, current_table), row, col);
		} else if(command=="setn"){
			current_table->reg_cell(new NumberCell(atoi(rest.c_str()), row, col, current_table), row, col);
		} else if(command=="setd"){
			current_table->reg_cell(new DateCell(rest, row, col, current_table), row, col);
		} else if(command=="sete"){
			current_table->reg_cell(new ExprCell(rest, row, col, current_table), row, col);
		} else if(commanc=="out"){
			ofstream out(to);
			out<<*current_table;
			std::cout<<to<<"is saved by content"<<std::endl;
		} else if(command=="exit"){
			return 0;
		}
		
		return 1;
	}
	void Excel::command_line(){
		std::string s;
		std::getline(cin, s);
		
		while(parse_user_input(s)){
			std::cout<<*current_table<<std::endl<<">> ";
			getline(cin, s);
		}
	}
	
}//END NAMESPACE

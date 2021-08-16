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

//***Cell***
Cell::Cell(string data, int x, int y, Table* table): data(data), x(x), y(y), table(table) {}
string Cell::stringify(){	return data;	}
int Cell::to_numeric() {	return 0;	}//string to num return 0
//***Cell End***

//***Table***
Table::Table(int max_row_size, int max_col_size): max_row_size(max_row_size), max_col_size(max_col_size){
	data_table=new Cell**[max_row_size];//Cell*'s array 
	for(int i=0; i<max_row_size; i++){
		data_table[i]=new Cell*[max_col_size];//allocation with column
		for(int j=0; j<max_col_size; j++){
			data_table[i][j]=NULL;//set data to NULL
		}
	}
}
Table::~Table(){
	for(int i=0; i<max_row_size; i++){//with all data location
		for(int j=0; j<max_col_size; j++){
			if(data_table[i][j])//if data exist
				delete data_table[i][j];//delete_1. cell object erase.
		}
	}
	for(int i=0; i<max_row_size; i++){
		delete[] data_table[i];//delete data_table[i] that is used for making col Cells_2. Cell array erase.
	}
	delete data_table;//delete data_table._3. 2 tensor table erase.
}
void Table::reg_cell(Cell* c, int row, int col){
	if(!(row<max_row_size&&col<max_col_size)) return;//exception out range.
	
	if(data_table[row][col]){
		delete data_table[row][col];//erase initial cell's address
	}
	data_table[row][col]=c;//change to new cell's address
}
int Table::to_numeric(const string& s){//ex. B4
	int col=s[0]-'A';
	int row=atoi(s.c_str()+1)-1;//change to c string
	
	if(row<max_row_size&&col<max_col_size){
		if(data_table[row][col]){
			return data_table[row][col]->to_numeric();//function in Cell class
		}
		return 0;
	}
}
string Table::stringify(const string& s){
	int col=s[0]-'A';
	int row=atoi(s.c_str()+1)-1;
	
	if(row<max_row_size&&col<max_col_size){//correct range
		if(data_table[row][col]){//is data
			return data_table[row][col]->stringify();
		}
	}
	return 0;
}
string Table::stringify(int row, int col){
	if(row<max_row_size&&col<max_col_size&&data_table[row][col]){//correct range, is data
		return data_table[row][col]->stringify();
	}
	return "";
}
std::ostream& operator<<(std::ostream& o, Table& table){//ostream operator overloading.
	o<<table.print_table();
	return o;
}
//***Table End***

//***TxtTable***
TxtTable::TxtTable(int row, int col):Table(row, col){}//Constructor call Table's constructor with initializer list
string TxtTable::print_table(){
	string total_table;
	
	int* col_max_wide=new int[max_col_size];
	for(int i=0; i<max_col_size; i++){
		unsigned int max_wide=2;
		for(int j=0; j<max_row_size; j++){
			if(data_table[j][i]&&data_table[j][i]->stringify().length()>max_wide){
				max_wide=data_table[j][i]->stringify().length();
			}
		}
		col_max_wide[i]=max_wide;//save max_wide at each column. it is needed for printing cleanly. 
	}//find maximum length of cell in whole area.
	total_table+="    ";//4blank
	int total_wide=4;
	for(int i=0; i<max_col_size; i++){
		if(col_max_wide[i]){
			int max_len=std::max(2, col_max_wide[i]);
			total_table+=" | "+col_num_to_str(i);
			total_table+=repeat_char(max_len-col_num_to_str(i).length(), ' ');//will be defined
			
			total_wide+=(max_len+3);//?
		}
	}//upside, column information print
	
	total_table+="\n";
	//suppose maximum size is 9999column
	for(int i=0; i<max_row_size; i++){
		total_table+=repeat_char(total_wide, '-');
		total_table+="\n"+to_string(i+1);
		total_table+=repeat_char(4-to_string(i+1).length(),' ');
		
		for(int j=0; j<max_col_size; j++){
			if(col_max_wide[j]){
				int max_len=std::max(2, col_max_wide[j]);
				
				string s="";
				if(data_table[i][j]){
					s=data_table[i][j]->stringify();
				}
				total_table+=" | "+s;
				total_table+=repeat_char(max_len-s.length(), ' ');
			}
		}
		total_table+="\n";
	}
	return total_table;
}

string TxtTable::repeat_char(int n, char c){
	string s="";
	for(int i=0; i<n; i++)
		s.push_back(c);//
		
	return s;
}
string TxtTable::col_num_to_str(int n){//column number to Alphabet ex. AB AC 
	string s="";
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
//***TxtTable End***

//***HtmlTable***
HtmlTable::HtmlTable(int row, int col):Table(row, col){}

string HtmlTable::print_table(){
	string s="<Table border='1' cellpadding='10'>";
	for(int i=0; i<max_row_size; i++){
		s+="<tr>";
		for(int j=0; j<max_col_size; j++){
			s+="<td>";
			if(data_table[i][j])
				s+=data_table[i][j]->stringify();
			s+="</td>";
		}
		s+="</tr>";
	}
	s+="</table>";
	return s;
}
//***HtmlTable End***

//***CSVTable***
CSVTable::CSVTable(int row, int col):Table(row, col){}

string CSVTable::print_table(){
	string s="";
	for(int i=0; i<max_row_size; i++){
		for(int j=0; j<max_col_size; j++){
			if(j>=1)
				s+=",";
				//by CSV rule, if " in string, change to "
			
			string temp;
			if(data_table[i][j])
				temp=data_table[i][j]->stringify();
			for(int k=0; k<temp.length(); k++){
				if(temp[k]=='"'){
					temp;insert(k,1,'"');
					//k move because " is already added so it don't need check
					k++;
				}
			}
			temp='"'+temp+'"';
			s+=temp;
		}
		s+='\n';
	}
	return s;
}
//***CSVTable End***
}//MyExcel end

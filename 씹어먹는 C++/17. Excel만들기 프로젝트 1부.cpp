#include <iostream>
#include <string>

class Cell{//one space in big table.
	protected:
		int x, y;//cell location
		Table* table;//which table in?
		
		string data;//for save content in one space.
	public:
		//convert data to string
		virtual string stringify();
		//convert data to num(for inheritance to NumberCell, etc.. so virtual!)
		virtual int to_numeric();
		//Constructor
		Cell(string data, int x, int y, Table* table);
}; 
Cell::Cell(string data, int x, int y, Table* table): data(data), x(x), y(y), table(table) {}
string Cell::stringify(){	return data;	}
int Cell::to_numeric() {	return 0;	}//string to num return 0

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

class TxtTable:public Table{//order, print Table's content
	string repeat_char(int n, char c);
	//column number to A~Z
	string col_num_to_str(int n);
	
	public:
		TxtTable(int row, int col);
		//print table with text
		string print_table();
};
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
		col_max_wide[i]=max_wide;
	}//find maximum length of cell in whole area.
	total_table+="		";
	int total_wide=4;
	for(int i=0; i<max_col_size; i++){
		if(col_max_wide[i]){
			int max_len=max(2, col_max_wide[i]);
			total_table+=" | "+col_num_to_str(i);
			total_table+=repeat_char(max_len-col_num_to_str(i).length(), ' ');
			
			total_wide+=(max_len+3);
		}
	}
	//
	
}

/*
[0. 들어가기에 앞서서]
1.	Excel프로그램에서 사용할 자료구조는 크게 Vector와 Stack인데, 이들은 수식을 분석하기 위해, 즉 ExprCell객체의 to_numeric함수 내에서 사용될 예정이다.
2.	Vector는 수학의 벡터와는 다른느낌으로, 배열의 크기를 맘대로 조절할 수 있는 가변길이 배열이라고 보면 된다. 즉, 배열처럼 []연산자로 임의의 위치에 있는 원소에 마음대로 접근할 수 있고, 임의의 위치에 원솔르 추가하거나 뺄 수 있다. 
	또한, 벡터를 만드는 방법은 이전에 문자열 클래스를 만들 때와 거의 비슷하다. 문자열 역시 char데이터를 담는 가변 길이 배열이라고 볼 수 있기 때문이다.
3.	Stack은 벡터와는 다르게 임의의 위치에 있는 원소에 접근할 수 없고 항상 최상단에 있는 데이터만 접근할 수 있다. 그리고 새로운 데이터를 추가하면 항상 최상단에 오게 된다. 즉, 설거지용으로 쌓는 접시들의 모형이다. 
	새로운 설거지가 오면 맨 위에 오게되고(push), 설거지를 위해 접시를 뺄 땐 맨 위의 접시부터(push)빠진다.
4.	Vector를 활용하여 Stack을 만들 수 도 있지만, 약간 과하다. 보통 스택의 경우 링크드 리스트(Linked List)를 이용하여 구현을 한다.
	스택은 임의의 위치에 접근할 필요가 없고, 단순히 최상단에 뭐가 있는지, 그리고 새로운것을 추가하거나 빼는것만 하면 된다. 

[1. 벡터 클래스(Vector)]
1.	디폴트 인자는 C++규칙이기도 한데, 클래스 내부 함수 선언에서 디폴트 인자를 명시하였다면, 함수 본체에서 명시하면 안되고, 반대로 함수 본체에서 명시하였다면 클래스 내부 함수 선언에 명시하면 안된다. 즉, 둘 중 한 곳에만 표시해야 한다. 
2.	간단히 excel프로젝트안에서 사용할 목적으로 만든 것. 보통의 일반적인 Vector클래스는 중간에 원소를 추가하는 insert나 검색하는 find함수들도 세트로 다닌다. 

[2.	스택 클래스(Stack)]
1.	앞서 말한 것 처럼 링크드 리스트를 사용하기에 데이터를 보관하기 위해서 하나의 노드를 만들어서 노드들을 체인처럼 엮을 것이다. 
2.	문자열을 받는 것 외에도, 숫자 데이터를 보관하기 위해 NumStack을 기존의 Stack의 string을 int로 바꾸어 동일하게 처리 하였다. 
3.	NumStack클래스까지 만들어, utils.h 헤더파일과 그 하위 함수들이 정의된 utility.cpp파일로 나뉘어 MyExcel이라는 namespace에 담아두었다.

[3.	본격적인 'Cell'과 'Table'클래스]
1.	 
*/

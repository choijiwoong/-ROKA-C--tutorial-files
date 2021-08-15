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
[0. ���⿡ �ռ���]
1.	Excel���α׷����� ����� �ڷᱸ���� ũ�� Vector�� Stack�ε�, �̵��� ������ �м��ϱ� ����, �� ExprCell��ü�� to_numeric�Լ� ������ ���� �����̴�.
2.	Vector�� ������ ���Ϳʹ� �ٸ���������, �迭�� ũ�⸦ ����� ������ �� �ִ� �������� �迭�̶�� ���� �ȴ�. ��, �迭ó�� []�����ڷ� ������ ��ġ�� �ִ� ���ҿ� ������� ������ �� �ְ�, ������ ��ġ�� ���ָ� �߰��ϰų� �� �� �ִ�. 
	����, ���͸� ����� ����� ������ ���ڿ� Ŭ������ ���� ���� ���� ����ϴ�. ���ڿ� ���� char�����͸� ��� ���� ���� �迭�̶�� �� �� �ֱ� �����̴�.
3.	Stack�� ���Ϳʹ� �ٸ��� ������ ��ġ�� �ִ� ���ҿ� ������ �� ���� �׻� �ֻ�ܿ� �ִ� �����͸� ������ �� �ִ�. �׸��� ���ο� �����͸� �߰��ϸ� �׻� �ֻ�ܿ� ���� �ȴ�. ��, ������������ �״� ���õ��� �����̴�. 
	���ο� �������� ���� �� ���� ���Եǰ�(push), �������� ���� ���ø� �� �� �� ���� ���ú���(push)������.
4.	Vector�� Ȱ���Ͽ� Stack�� ���� �� �� ������, �ణ ���ϴ�. ���� ������ ��� ��ũ�� ����Ʈ(Linked List)�� �̿��Ͽ� ������ �Ѵ�.
	������ ������ ��ġ�� ������ �ʿ䰡 ����, �ܼ��� �ֻ�ܿ� ���� �ִ���, �׸��� ���ο���� �߰��ϰų� ���°͸� �ϸ� �ȴ�. 

[1. ���� Ŭ����(Vector)]
1.	����Ʈ ���ڴ� C++��Ģ�̱⵵ �ѵ�, Ŭ���� ���� �Լ� ���𿡼� ����Ʈ ���ڸ� ����Ͽ��ٸ�, �Լ� ��ü���� ����ϸ� �ȵǰ�, �ݴ�� �Լ� ��ü���� ����Ͽ��ٸ� Ŭ���� ���� �Լ� ���� ����ϸ� �ȵȴ�. ��, �� �� �� ������ ǥ���ؾ� �Ѵ�. 
2.	������ excel������Ʈ�ȿ��� ����� �������� ���� ��. ������ �Ϲ����� VectorŬ������ �߰��� ���Ҹ� �߰��ϴ� insert�� �˻��ϴ� find�Լ��鵵 ��Ʈ�� �ٴѴ�. 

[2.	���� Ŭ����(Stack)]
1.	�ռ� ���� �� ó�� ��ũ�� ����Ʈ�� ����ϱ⿡ �����͸� �����ϱ� ���ؼ� �ϳ��� ��带 ���� ������ ü��ó�� ���� ���̴�. 
2.	���ڿ��� �޴� �� �ܿ���, ���� �����͸� �����ϱ� ���� NumStack�� ������ Stack�� string�� int�� �ٲپ� �����ϰ� ó�� �Ͽ���. 
3.	NumStackŬ�������� �����, utils.h ������ϰ� �� ���� �Լ����� ���ǵ� utility.cpp���Ϸ� ������ MyExcel�̶�� namespace�� ��Ƶξ���.

[3.	�������� 'Cell'�� 'Table'Ŭ����]
1.	 
*/

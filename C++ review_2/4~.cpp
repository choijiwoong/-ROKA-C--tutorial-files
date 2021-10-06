#include <iostream>

//Geometry************************************************
#include <cmath>//for sqrt & pow
#include <vector>
class Point{
	int x,y;
	
	public:
		Point(const int& pos_x, const int& pos_y):x(pos_x), y(pos_y){};
		int Get_x(){ return x; }
		int Get_y(){ return y; }
		~Point()=default;
};
class Geometry{
	Point* point_array[100];
	int num_points;
	
	public:
		Geometry(){ num_points=0; }
		void AddPoint(Point point){ point_array[num_points++]=new Point(point.Get_x(), point.Get_y()); }
		void PrintDistance();
		void PrintNumMeets();
		void PrintPoints();
		~Geometry()=default;
};
void Geometry::PrintPoints(){
	for(int i=0; i<num_points; i++)
		std::cout<<"point_array["<<i<<"] : "<<point_array[i]->Get_x()<<", "<<point_array[i]->Get_y()<<std::endl;
}

double GetDistance(Point& sample1, Point& sample2){
	return sqrt(pow((sample1.Get_x()-sample2.Get_x()),2)+pow(sample1.Get_y()-sample2.Get_y(), 2));
}
void Geometry::PrintDistance(){
	for(int i=0; i<num_points; i++)
		for(int j=i+1; j<num_points; j++)
			std::cout<<"distance of "<<i<<" & "<<j<<" : "<<GetDistance(*point_array[i], *point_array[j])<<std::endl;//input as value of pointer not pointer type
}

void Geometry::PrintNumMeets(){//�����Ѱ� ������ ����, ������ ����, �����ɷ� �߸� 
	struct double_pair{//tool for PrintNumMeets
		double first;
		double second;
	};
	std::vector<double_pair> line_array;
	line_array.reserve(num_points*(num_points-1));//not suppose same dot.
	
	double_pair par;//first is degree of straight, second is point that meets with y
	for(int i=0; i<num_points; i++){
		for(int j=i+1; j<num_points; j++){
			par.first=(point_array[i]->Get_y()-point_array[j]->Get_y()) / (point_array[i]->Get_x()-point_array[j]->Get_x());
			par.second=point_array[i]->Get_y()-point_array[i]->Get_x()*par.first;
			line_array.push_back(par);
		}
	}
	//save all line to vector
	
	
	for(int i=0; i<line_array.size(); i++){
		for(int j=i+1; j<line_array.size(); j++){
			if(line_array[i].first==line_array[j].first && line_array[i].second==line_array[j].second){//same
				std::cout<<"infinite!"<<std::endl;
				return;
			}
			else if(line_array[i].first==line_array[j].first){//same degree
				line_array.erase(line_array.begin()+j);//delete
			}
		}
	}
	
	
	if(line_array.size()==2)
		std::cout<<"NumMeets: 1!"<<std::endl;
	else 
		std::cout<<"NumMeets: "<<line_array.size()<<"!"<<std::endl;
}

int main(){
	Geometry geo;
	geo.AddPoint(Point(1,2));
	geo.AddPoint(Point(2,3));
	geo.AddPoint(Point(2,3));
	geo.PrintPoints();
	geo.PrintDistance();
	geo.PrintNumMeets();
}

/*
1.	C++�����Ϸ��� �Լ� �����ε� ����
	1) �ڽŰ� Ÿ���� ��Ȯ�� ��ġ�ϴ� �Լ��� ã�´�.
	2) ��Ȯ�� ��ġ�ϴ� Ÿ���� ���� ��� �Ʒ��� ���� ����ȯ�� ���Ͽ� ��ġ�ϴ� �Լ��� ã�ƺ���.
		-char, unsigned char, short�� int
		-unsigned short�� int�� ũ�⿡ ���� intȤ�� unsigned int��
		-float�� double��
		-enum�� int��
	3) �Ʒ��� �� �� �������� ����ȯ�� ���Ͽ� ��ġ�ϴ� �Լ��� ã�ƺ���.
		-numeric(������ ����)Ÿ���� �ٸ� ���� Ÿ������ ��ȯ�ȴ�.
		-enum�� ������ ���� Ÿ������ ��ȯ�ȴ�
		-0�� ������ Ÿ���̳� ����Ÿ������ ��ȯ�ȴ�.
		-�����ʹ� void�����ͷ� ��ȯ�ȴ�.
	4) ���� ���ǵ� Ÿ�� ��ȯ���� ��ġ�ϴ� ���� ã�´�
	 �� 4������ ���ؿ� �ش����� ������ ��ȣ�ϴ�(ambigous)��� �Ǵ��Ͽ� ������ �߻���Ų��. 
	���� �ڵ忡���� 3�ܰ���� ���������� double�� char�̳� int�� �� ��ȯ�� �����ϱ⿡ ambiguous������ �߻���Ų��. 

2.	Date day(2011, 3, 1);�� �Ͻ���(implicit) ���, Date day=Date(2012, 3, 1);�� �����(explicit) ������� �����ڸ� ȣ���� ���̴�.

3.	making(all variable by const keyword) maybe occur error or false return value if we enter const number to it 
*/

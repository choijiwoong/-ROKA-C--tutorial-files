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

void Geometry::PrintNumMeets(){//������ ������ ����, �����Ѱ� ����, �����ɷ� �߸�
	if(num_points<=2){//no point
		printf("NumMeets: 0!");
		return;
	}
	
	//calculate possible graph line & save
	std::vector<std::pair<double, double>> line;
	line.reserve(num_points*(num_points-1));
	double x1, y1, x2, y2, a, b;
	for(int i=0; i<num_points-1; i++){//default value of num_points is ZERO
		for(int j=i+1; j<num_points-1; j++){
			x1=point_array[i]->Get_x();
			y1=point_array[i]->Get_y();
			x2=point_array[j]->Get_x();
			y2=point_array[j]->Get_y();
			a=(y2-y1)/(x2-x1);
			b=y1-x1*a;
			
			line.push_back(std::make_pair(a, b));
			std::cout<<"graph [y="<<a<<"x+"<<b<<"] is added by ("<<x1<<", "<<y1<<"), ("<<x2<<", "<<y2<<")"<<std::endl;
		}
	}

	//if same graph is exist, it makes many dot & remove parallel
	for(std::vector<std::pair<double, double>>::iterator itr=line.begin(); itr!=line.end(); itr++){
		for(std::vector<std::pair<double, double>>::iterator itr2=itr+1; itr2!=line.end(); itr2++){
			if(itr->first==itr2->first && itr->second==itr2->second){//same graph
				std::cout<<"NumMeets: infinite!"<<std::endl;
				return;
			} else if(itr->first==itr2->first && itr->second!=itr2->second){//parallel
				line.erase(itr2);//not iterator error?
				itr=line.begin();//solve!
				itr2=line.begin()+1;
			}
		}
	}
	
	std::cout<<"NumMeets: "<<line.size()<<"!"<<std::endl;
	return;
}

int main(){
	Geometry geo;
	geo.AddPoint(Point(1,2));
	geo.AddPoint(Point(2,4));
	geo.AddPoint(Point(25,3));
	geo.AddPoint(Point(22,3));
	geo.AddPoint(Point(-1,2));
	geo.AddPoint(Point(-2,4));
	geo.AddPoint(Point(-25,3));
	geo.AddPoint(Point(-22,3));
	
	geo.PrintPoints();
	std::cout<<std::endl;
	
	geo.PrintDistance();
	std::cout<<std::endl;
	
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

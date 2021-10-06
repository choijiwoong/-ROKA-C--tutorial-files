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

void Geometry::PrintNumMeets(){//평행한거 있으면 무한, 같은거 제거, 남은걸로 추리 
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
1.	C++컴파일러의 함수 오버로딩 과정
	1) 자신과 타입이 정확히 일치하는 함수를 찾는다.
	2) 정확히 일치하는 타입이 없는 경우 아래와 같은 형변환을 통하여 일치하는 함수를 찾아본다.
		-char, unsigned char, short는 int
		-unsigned short는 int의 크기에 따라 int혹은 unsigned int로
		-float은 double로
		-enum은 int로
	3) 아래의 좀 더 포괄적인 형변환을 통하여 일치하는 함수를 찾아본다.
		-numeric(임의의 숫자)타입은 다른 숫자 타입으로 변환된다.
		-enum도 임의의 숫자 타입으로 변환된다
		-0은 포인터 타입이나 숫자타입으로 변환된다.
		-포인터는 void포인터로 변환된다.
	4) 유저 정의된 타입 변환으로 일치하는 것을 찾는다
	 위 4가지의 기준에 해당하지 않으면 모호하다(ambigous)라고 판단하여 오류를 발생시킨다. 
	위의 코드에서는 3단계까지 내려간다음 double이 char이나 int둘 다 변환이 가능하기에 ambiguous오류를 발생시킨다. 

2.	Date day(2011, 3, 1);은 암시적(implicit) 방법, Date day=Date(2012, 3, 1);은 명시적(explicit) 방법으로 생성자를 호출한 것이다.

3.	making(all variable by const keyword) maybe occur error or false return value if we enter const number to it 
*/

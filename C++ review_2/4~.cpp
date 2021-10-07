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

void Geometry::PrintNumMeets(){//같은거 있으면 무한, 평행한거 제거, 남은걸로 추리
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

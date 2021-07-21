/*1. ��ü��?
������ Animal ����ü�� ��������  
typedef struct Animal {
  char name[30];  // �̸�
  int age;        // ����

  int health;  // ü��
  int food;    // ��θ� ����
  int clean;   // ������ ����
} Animal;
�̰�, �̸� �ʿ�� �ϴ� �Լ��鿡�� play(list[play_with]);�� ���� ����ü�� �μ��� ������ ��.
�ٵ� play�� animal�� �ϴ� �� ���� �� �ڵ�� ��� animal��ü�� play�� �ϴ� ����.
�� �̸� �����־� ���� �ڵ��ϰ� �Ǹ�,

Animal animal;

// �������� �ʱ�ȭ (����)

animal.play();   // �� ���� (animal ��) Play �� �Ѵ�!
animal.sleep();  // ���� sleep �� �Ѵ�! 
�̷��� �ٱ� �� ����. �̷��ٸ� play�Լ��� �̹� �� ��� ������ �� �� �ֱ⿡ ������ ó���� ����.
��. animal�� �ڽ��� ���¸� �˷��ִ� ����(variable)��, �ڽ��� �ϴ� �ൿ��(play, sleep)�� �����ϴ�
�Լ�(method)��� �̷����.
 ��������� "��ü��, ������� ���� �ڷ��� �̷���� ����Ʈ���� ����̴�." 
�̶� ��ü�� ���Ǽ����� �����ϴ� ���� ��Ÿ�������� �߻�ȭ(abstraction)�̶�� ������ ��ġ�µ�,
�ڵ����� ��� ��ȭ�� ���ڸ� �ڵ����� �ϴ� ������, ���͸��� �ܷ����� ���� ������. 
��. �����ϰ� ��ǻ�Ϳ��� ó���� �� �ֵ��� �ٲٴ� ������ �ǹ��Ѵ�. 
 �� ��ü���� �������� �Լ����� �ѷ��ΰ� �ִ� �����ε�, �̸� �ν���Ʈ ����(instance variable)��
�ν���Ʈ �޼ҵ�(instance method)��� �θ���. (�� ���� �ν���Ʈ �޼ҵ�� ��ü���� �Լ���.)
 �̶�, �������� �Լ����� �ѷ��Ѵٴ� ���� ������ ��ȣ�� �޴� ���� �ǹ���. �ν���Ʈ ������
���� �����Ͽ� ���� �ٲٱ� ���� �Լ��� ���� �����ϴµ�, ��ó�� �ܺο��� ���� �ν���Ʈ ������ ����
�ٲ� �� ����, �׻� �ν��Ͻ� �޼ҵ带 ���Ͽ� ���������� �����ϴ� ���� ķ��ȭ(Encapsulation)�̶�� �Ѵ�.
  �̶� ĸ��ȭ�� ����, �� ������ "��ü�� ���������� ��� �۵��ϴ��� ���� ����� �� �ִ�."�̴�.
���� ���� animal���� animal.increase_food(100);�� �ϸ� ���������� weight�� �����ϰ�, happiness�� �ö󰡴�
��, ���� �۾��� �Ͼ�µ�, ĸ��ȭ�� ���� �ʾҴٸ� ��ü ������ �������� � ���� �Ҵ�Ǿ� �ִ����� Ȯ���ϰ�
�̿����� ������ �������� ��������� �Ѵ�. �� ���α׷��Ӱ� food�� 100�Դ� �������� � �ϵ��� �Ͼ����
�˾ƾ߸� ������ �����ϴٴ� ��. ���� �̸� ĸ��ȭ �ߴٸ� �ٸ� ���α׷��Ӱ� ������ �̷��� �ϵ��� ������ 
���� �ܼ��� animal.increase_food(100);�� ���� ���θ� ���� ����� �����ϴ�. 
�̿� ���� �ǹ��� ǰ�´ٸ� ������ Ű���带 my_domputer.keyboard_hit('a');�޼ҵ��� ȣ��� ����ϱ� �ٶ�. 
 */
 
/*2. (�ʿ� ����?)Ŭ���� 
C++������ �̷��� ��ü�� ���� �� �ִ� ��ġ�� Ŭ����(class)�̴�. Ŭ������ �̿��Ͽ� ������� ��ü�� �ν��Ͻ�(instance)��� �θ���.
#include <iostream>

class Animal {//AnimalŬ������ ���Ͽ� ������ ������ ��ü�� ���� ���赵 
 private://�̸� ���� ������ ��� ��. �ܺο��� ����鿡 ���Ͽ� ������ �� �� �ֳ� ���ĸ� �������ִ� ���̴�.
  int food;//Ŭ���� �󿡼� ��Ī�Ҷ� �ɹ� ����(member variable) 
  int weight;//private�Ǵ� ��� ���� �ڱ� ��ü �ȿ����� ������ �� ����, ��ü �ܺο����� ������ �� ���� �ȴ�. 
  //�� main���� Animal animal;�Ҵ� �� animal.food=100;�� �Ұ����ϴٴ� ��.
  //������ private, public��ø� ���� �ʴ´ٸ� private�� default����. �� private���� �ɹ� ������
  //������ �����ֵ� ���� �۵� ��. (�˾Ƽ� privateȭ) 
   
 public://public�� ��� �ܺο��� ������ �̿��� �� ����. �� main���� animal.set_animal(100,50);ó�� ����� �����ϴ�. 
  void set_animal(int _food, int _weight) {//�ɹ� �Լ�(member function)�̶�� �θ�. �� �����ϴ°� �ƴϴ�. 
    food = _food;//��ü�� ��������� �����ϸ� �ν��Ͻ� ����, �ν��Ͻ� �Լ�! 
    weight = _weight;
  }//���� voit set_animal()�Լ��� private�� �Ű�ٸ�, ������ �Ұ����ϴٴ� ������ 3������ �����Ѵ�. 
  //���� ����ϰ� ���� ��������� public���� �ű�� main���� animal.food=100;ó�� ����� �����ϴ�. 
  
  void increase_food(int inc) {
    food += inc;
    weight += (inc / 3);
  }
  void view_stat() {
    std::cout << "�� ������ food   : " << food << std::endl;
    std::cout << "�� ������ weight : " << weight << std::endl;
  }
};  // �����ݷ� ���� ����!

int main() {
  Animal animal;//Ŭ������ ���� struct�� ������� �ʰ� �Ϲ����� �ڷ��� ó�� ���. 
  animal.set_animal(100, 50);
  animal.increase_food(30);

  animal.view_stat();
  return 0;
}
*/

//3. ���� �غ� ����
#include <iostream>

class Date{
	int year_;
	int month_;//1 to 12
	int day_;//1 to 31
	
	public:
		int return_day_by_month(int i){//�O��,,,�̰Ž� ���̽��� �ƴѰŽÿ�!!!!! 
			if (i==2){
				return 28;
			}
			
			//int *array=new int[7]; �� �� �ȵǴ�  
			int array[7]={1,3,5,7,8,10,12};
			
			for(int m=0;m<7;m++){//�˰ھ�??? :�� �ƴ϶� {}�������������� ���̴� 
				if(array[m]==i){
					//delete[] array;
					return 31;
				}
			}
			
			//delete[] array;
			return 30;
		}
		
		void SetDate(int year, int month, int day){
			year_=year;
			month_=month;
			day_=day;
		}
		
		void AddDay(int inc){
			//�ʰ��ϴ� ��� 
			if (return_day_by_month(month_)<day_+inc){
				month_+=1;
				day_=day_+inc-return_day_by_month(month_);
			}
			//�Ϲ����� ��� 
			else{
				day_+=inc;
			}
		}
				
		void AddMonth(int inc){
			//�ʰ��ϴ� ���
			if (month_+inc>12){
				year_+=1;
				month_=month_+inc-12;
			}
			else
				month_=month_+inc;
		}
		
		void AddYear(int inc){
			year_+=inc;
		}
		
		void ShowDate(){
			std::cout<<year_<<"�� "<<month_<<"�� "<<day_<<"�� �Դϴ�."<<std::endl;
		}
			
};

int main(){
	Date test;
	test.SetDate(2021,7,21);
	test.ShowDate();
	test.AddDay(11);
	test.ShowDate();
	test.AddMonth(6);
	test.AddYear(3);
	test.ShowDate();
}
 

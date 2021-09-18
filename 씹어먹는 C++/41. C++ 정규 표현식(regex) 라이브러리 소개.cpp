#include <iostream>
#include <regex>
#include <vector>
//1 Let's code by regular expression 'db-\d*-log\.txt'
int main(){
	//names of files
	std::vector<std::string> file_names={"db-123-log.txt", "db-124-log.txt", "not-db-log.txt", "db-12-log.txt", "db-12-log.jpg"};
	
	std::regex re("db-\\d*-log\\.txt");
	for (const auto &file_name: file_names)
		std::cout<<file_name<<": "<<std::boolalpha<<std::regex_match(file_name, re)<<'\n';
		
	std::regex re1("db-\\d*-log\\.txt", std::regex::grep);//we can choose engine of regular expression by adding argument.
	//our default engine is std::regex::ECMAScript
	//we can pass characteristic by argument with '|' not only engine like that
	std::regex re2("db-\\d*-log\\.txt", std::regex::grep | std::regex::icase);//that doesn't look different A and a.
	//And we can pass std::regex::opimize if we need performance of regular expression. it's more time to create object, but less time to use object.
	
	//std::regex_match return true if first argument(fiel_name) is matched to second argument(re).
}

/*
[0.	���⿡ �ռ�]
1.	C++11���� ǥ�ؿ� ���Ե� ���� ǥ����(regular expression)���̺귯���� ���ؼ� ������ �˾ƺ���
2.	���� ǥ������ ���ڿ����� ������ ã�µ� ����ϴµ�, �̸� ����
	-�־��� ���ڿ��� �־��� ��Ģ�� �´��� Ȯ���� ��
	-�־��� ���ڿ����� ���ϴ� ������ ���ڿ��� �˻��� ��
	-�־��� ���ڿ����� ���ϴ� ������ ���ڿ��� ġȯ�� ��
	�� ���� ��쿡 �ſ� �����ϰ� ���ȴ�. 

[1.	��ü ���ڿ� ��Ī�ϱ�]
1.	�������� �� �ð����� �α������� �����ϴµ�, db-(�ð�)-log.txt�� ���� ���·� �����ɶ�, ���� ���ϵ��� �����ִ� �������� �츮�� ���ϴ� �α� ���ϵ鸸 ������ �������� ��� �ؾ��� ��?
	����ǥ������ ����� �� �ִٸ� db-\d*-log\.txt�� ���� ���� ǥ������ ���÷��� ���̴�.
	\d*�� ������ ������ ���ڸ� �ǹ��ϰ�, .���� \�� .�� ������ ���ڷ� �ؼ��Ǵ� ���� ���´�. 
2.	C++���� ���� ǥ������ ����ϱ� ���ؼ��� ���� ���� ǥ���� ��ü�� �����ؾ� �Ѵ�. ����� ���� ǥ���� ������ ������, ���� ǥ������ ó���ϴ¿��� ���� ���� ������ �ִµ�, �̷��� ������ �� �����ڿ� �߰����� ���ڷ� ������ �� �ִ�.
3.	����ǥ������ ������ �ɼ����� ���� �� ������, |���� Ư���� ���� �� �ִ�. �׸��� std::regex::optimize�� �����ϸ� �� �� ����ȭ�� regex�� ����� �� �ִ�.
4.	std::regex_match�� ù������ ���ڿ��� �ι�° ������ ����ǥ���İ�ü�� ������ ��Ī(���� ǥ������ ���Ͽ� ����)�Ѵٸ� true�� �����Ѵ�.

[2.	�κ� ��Ī �̾Ƴ���]
1.	 
*/ 

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
[0.	들어가기에 앞서]
1.	C++11부터 표준에 포함된 정규 표현식(regular expression)라이브러리에 대해서 간단히 알아보자
2.	정규 표현식은 문자열에서 패턴을 찾는데 사용하는데, 이를 통해
	-주어진 문자열이 주어진 규칙에 맞는지 확인할 때
	-주어진 문자열에서 원하는 패턴의 문자열을 검색할 때
	-주어진 문자열에서 원하는 패턴의 문자열로 치환할 때
	와 같은 경우에 매우 유용하게 사용된다. 

[1.	전체 문자열 매칭하기]
1.	서버에서 매 시간마다 로그파일을 생성하는데, db-(시간)-log.txt와 같은 형태로 생성될때, 여러 파일들이 섞여있는 폴더에서 우리가 원하는 로그 파일들만 간단히 읽으려면 어떻게 해야할 까?
	정규표현식을 사용할 수 있다면 db-\d*-log\.txt와 같은 정규 표현식을 떠올렸을 것이다.
	\d*는 임의의 개수의 숫자를 의미하고, .앞의 \은 .이 임의의 문자로 해석되는 것을 막는다. 
2.	C++에서 정규 표현식을 사용하기 위해서는 먼저 정규 표현식 객체를 정의해야 한다. 참고로 정규 표현식 문법의 종류와, 정규 표현식을 처리하는엔진 역시 여러 종류가 있는데, 이러한 엔진을 위 생성자에 추가적인 인자로 전달할 수 있다.
3.	정규표현식의 엔진을 옵션으로 넣을 수 있으며, |으로 특성도 넣을 수 있다. 그리고 std::regex::optimize를 전달하면 좀 더 최적화된 regex를 사용할 수 있다.
4.	std::regex_match는 첫인자의 문자열과 두번째 인자의 정규표현식객체와 완전히 매칭(정규 표현식의 패턴에 부합)한다면 true를 리턴한다.

[2.	부분 매칭 뽑아내기]
1.	 
*/ 

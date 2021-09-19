#include <iostream>
#include <regex>
#include <vector>
/*1 Let's code by regular expression 'db-\d*-log\.txt'
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
	
	//std::regex_match return true if first argument(file_name) is matched to second argument(re).
}*/

/*2 regular expression of cell-phone
int main(){
	std::vector<std::string> phone_numbers={"010-1234-5678", "010-123-4567", "011-1234-5567", "010-12345-6789", "123-4567-8901", "010-1234-567"};
	
	std::regex re("[01]{3}-\\d{3,4}-\\d{4}");//first parts can be placed 3 number of 1,2 & second parts can be placed 3 or 4 number of integral & third parts can be placed 4 number of integral
	for(const auto &number:phone_numbers)//range-based for loop
		std::cout<<number<<": "<<std::boolalpha<<std::regex_match(number, re)<<'\n';
	//well working like part 1.
	//then how about if we want to get middle number of phone_numbers?
	//we can use capture group
} */

/*2 using of capture group in regular expression for extracting of middle number of phone_numbers
int main(){
	std::vector<std::string> phone_numbers={"010-1234-5678", "010-123-4567", "011-1234-5567", "010-12345-6789", "123-4567-8901", "010-1234-567"};
	
	std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");//regular expression with capture group()
	std::smatch match;//save result of matching as string. it return matched string to std::string. cmatch is exsist that returns const char* type.
	for (const auto &number: phone_numbers){
		if (std::regex_match(number, match, re)){//element, storage for passed element, regular expression
			for (size_t i=0; i<match.size(); i++)
				std::cout<<"Match : "<<match[i].str()<<std::endl;//because match's type is smatch, so match[i].str() is std::string type.
			std::cout<<"-----------------------\n";
		}
	}
	//regex_match is matching all string, so return all string at first result.
	//and then, print string in ()
}*/

/*3 read tag in HTML like <div class="sk...">...</div>
int main(){
	std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";
  
  std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
  std::smatch match;
  while(std::regex_search(html, match, re)){//searching pattern in string can use regex_search. if pattern is exist, regex_search returns true
  	std::cout<<match.str()<<'\n';//we can approach matched pattern by match.str()
  	//if we just execute condtion of while 'std::regex_search(html, match, re)', then it returns same pattern that is already gotten.
  	html=match.suffix();//so we have to updata html.
  	//match.suffix() returns std::sub_match object. it's getting two Iterator that points start & end.
  	//suffix returns sub_match object that has match.prefix(), match.str(), match.suffix(). such like "My name"_match.prefix(), "is "_match.str(), "Jaebum Lee"_match.suffix()
  	//sub_match class has casting operator to convert string. so if we substitute sub_match to html, it's automatically converted.
  	//so we can make new search after pattern we found.
  }
}*/

/*4 use regex_itertor for convenience to upper code
int main(){//what's literal operator R? r is char*...
	std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";
  
  std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");//regular expression for partly extracting
  std::smatch match;//storage for matched element
  
  auto start=std::sregex_iterator(html.begin(), html.end(), re);//definition of string iterator of html that points start with regular expression
  auto end=std::sregex_iterator();//definition of string iterator of html that points end
  //these iterators only gets element that satisfies regular expression.
  //std::sregex_iterator is iterator that uses string in regex_iterator.
  
  while(start!=end){//iterator is pointer, so we can approach str() function by ->
  	std::cout<<start->str()<<std::endl;//already checked regular expression thanks to start's argument with re.
  	++start;//operator++() is already defined in std::sregex_iterator 
  }
}*/

/*5 replace by std::regex_replace 
int main(){//! maybe literal operator R means sentence contains special char in past chapter.
	std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";
  
  std::regex re(R"r(sk-circle(\d))r");//regular expression of part that we will change
  std::smatch match;//storage
  
  std::string modified_html=std::regex_replace(html, re, "$1-sk-circle");//html, regular expression, target format. std::regex_replace returns changed html by re to "$1-sk-circle". $1 means second capture group(first capture group is all sentence in re)
  std::cout<<modified_html<<std::endl<<std::endl;
  
  //std::regex_replace has many overloading format, but in this case, creats modified string and returns
  //if we want to just print not creating replaced string, we can write like this.
  std::regex_replace(std::ostreambuf_iterator<char>(std::cout), html.begin(), html.end(), re, "$1-sk-circle");
  //std::regex_replace's another overloading version!
  //if we pass iterator(that points start point of location that will be printed) that will print to first argument.
}*/

//5 two capture group
int main(){
	std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";
  
  std::regex re(R"r((sk-circle(\d) sk-circle))r");//that can contain all string that we will change like "sk-circle1 sk-circle"
  std::smatch match;//why? for saving later?
  //literal r is raw-string literal that can express original string that doesn't use escape sequence
  
  std::string modified_html=std::regex_replace(html, re, "$2-sk-circle");//like index of array
  std::cout<<modified_html;
	
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
1.	regex_match를 이용하여 전체 문자열이 주어진 정규 표현식 패턴을 만족하는지를 알아낼 수 있다면, 해당 조건을 만족하는 문자열에서 패턴 일부분을 뽑아내고 싶다면?
	전화번호를 받는 정규 표현식을 생각해보자.
	-(숫자)-(숫자)-(숫자)꼴
	-맨앞자리는 반드시 3자리며 0이나 1로 이루어짐
	-가운데자리는 3자리나 4자리임
	-마지막자리는 4자리임
	010-1234-5678
	010-123-4566
	011-1234-5678
	[01]{3}-\d{3,4}-\d{4} 라는 regular expression로 나타낼 수 있다.
	[01]은 0혹은 1이라는 뜻이고, {3}은 해당 종류의 문자가 3번 나타날 수 있다는 뜻이다. 
2.	만약 가운데 번호만 추출하고 싶다면 캡쳐 그룹(capture group)을 사용할 수 있다. 
	regular expression에서 원하는 부분을 ()로 감싸게 된다면 해당 부분에 매칭된 문자열을 얻을 수 있다.
3.	smatch는 매칭된 문자열을 std::string으로 돌려준다. const char*로 돌려주는 cmatch도 있다. 
4.	regex_match는 전체 문자열이 매칭된 것이기에 첫 번째 결과에 전체 문자열을 저장하고, 그 다음으로 ()안에 들어있던 문자열이 나타나게 된다.
	만약 정규 표현식 안에 ()가 여러개 있다면 마찬가지로 for문을 통해 순차적으로 접근이 가능하다.

[3.	원하는 패턴 검색하기]
1.	regex_match를 통해 문자열 전체가 패턴에 부합하는지 여부를 확인하였다. 만약 전체 말고 패턴을 만족하는 문자열 일부를 검색하고 싶다면?
	HTML에서 <div class="sk...">...</div>와 같은 형태의 태그만 읽고 싶다면 정규표현식은
	
	<div class="sk[\w-]*">\w*</div>로 나타낼 수 있다. 
2.	std::smatch로 검색된 패턴을 저장하는 공간을 만들 수 있고, std::regex_search나 std::regex_match에 인자로 넣음으로써 저장공간을 지정해줄 수 있다.
	다만 HTML안에서와 같이 vector와 같이 원소가 구분되지 않은 곳에서 패턴을 찾을때 이는 iterator같은 것이 아니기에, while을 사용할 수 있는데 그 속에 std::cout<<match.str()과 같이 처리를 한뒤에
	다시 while's condition을 확인하면 처음부터 다시 탐색하는 것과 같아 이미 출력한 패턴을 재탐색하게 된다. 고로 html을 업데이트해주어야 하는데,
	std::smatch match객체에 match.suffix()는 이미 탐색된 뒷부분을 리턴함과 동시에 string타입의 operator가 있어 단순히 기존에 html string에 대입해주면
	탐색된 부분을 배제하여 html을 업데이트 할 수 있다.
	
[4.	std::regex_iterator]
1.	사실 regex_iterator가 존재하여 이를 이용하면 더 편리하게 검색을 수행할 수 있다.
2.	sregex_iterator는 string을 사용하는 regex_iterator이고, 생성자에 html.start()와 html.end()그리고 regular expression을 호출하여 생성이 가능하다.
	이는 처음 생성될 때와, ++연산자로 증감될 때마다 regex_search를 통해 패턴을 만족하는 문자열을 검색한다. 
3.	또한 *연산자를 통해 역참조한다면 현재 검색된 패턴에 대한 match_results 객체를 얻을 수 있다.
	고로 std::cout<<start->str();처럼 간단하게 패턴과 매칭되는 문자열들을 뽑아낼 수 있다.
	
[5.	원하는 패턴 치환하기]
1.	정규 표현식을 통하여 원하는 패턴의 문자열을 다른 문자열로 치환(replace)을 std::regex_replace를 통하여 구현할 수 있다.
	html에서 sk-circle1과 같은 문자열을 1-sk-circle로 바꾸어보는 정규 표현식을 생각해보자.
	 우선 우리는 sk-circle1을 어떤 regex로 매칠시킬지 생각해야하는데 이는 sk-circle\d로 생각할 수 있다.
	또한 치환하고 싶은 형태는 숫자-sk-circle꼴인데, 문제는 숫자에 해당하는 부분이 매칭된 패턴의 \d에 해당하는 부분이라는 데에 있다.(쉽게 못옮긴다)
	하지만, 캡쳐 그룹을 이용하여 이를 간단히 해결할 수 있다.
	 먼저, sk-circle(\d)을 통하여 해당 부분을 첫번째 캡쳐그룹으로 만들고,
	치환을 할 때, 첫 번째 캡쳐 그룹을 표현하기 위해 $1로 명시할 수 있다.(이와 같은 요소를 back reference라고 부름) 
	따라서 $1-sk-circle로 표현이 가능하다.
	 이를 코드로 옮겨보자. 
2.	std::regex_replace(html, re, "$1-sk-circl");처럼 html, regular expression, 치환format을 넣어 std::string객체에 대입하면, string으로 overloading된다.
3.	만약 객체를 저장하지 않고 그냥 stdout에 출력하고 싶으면
	std::regex(std::ostreambuf_iterator<char>(std::out), html.begin(), html.end(), re, "$1-sk-circle");처럼 
	std::regex_replace의 첫번째 인자로 출력할 위치의 시작점을 가리키는 반복자를 넣어주면 된다.
4.	중복된 캡쳐 그룹
	나아가 <div class="sk-circle1 sk-circle">a</dic>에서
	<div class="1-sk-circle">a</div>처럼 치환과 동시에 뒷부분을 날려버리고 싶다고 해보자.
	 이를 위해 두개의 캡쳐그룹이 필요하다. (sk-circle(\d) sk-circle)로 전체와 숫자부를 뽑을 수 있다.
	이처럼 괄호가 중첩되었을때, 괄호가 열리는 순서대로 $1, $2..로 진행하기에 위의 경우엔 전체가 $1이고 \d가 $2이다.
	 치환된 패턴은 $2-sk-circle이니 코드를 작성해보자. 
	 
[6.	마무리하며]
1.	std::regex를 통하여 정규 표현식 객체생성이 가능하다
2.	std::regex_match로 전체 문자열이 패턴을 만족하는지 확인이 가능하다
3.	std::regex_search로 패턴에 맞는 문자열검색이 가능하다
4.	std::regex_replace로 원하는 패턴의 문자열을 다른 문자열로 치환이 가능하다. 
*/ 

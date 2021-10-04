#include <iostream>
#include <regex>
#include <vector>
#include <string>

int main(){
	//1. find name by using regex object & regex_match 
	std::vector<std::string> file_names={"db-123-log.txt", "db-124-log.txt", "not-db-log.txt", "db-12-log.jpg", "db-12-log.txt"};
	
	std::regex re("db-\\d*-log\\.txt");//make regular expression object with engin as argument(out default regex engine is ECMAScript) 
	//we can pass additional option(like std::regex::icase_A==a, std::optmize) to | .
	for(const auto &file_name: file_names)
		std::cout<<file_name<<": "<<std::boolalpha<<std::regex_match(file_name, re)<<std::endl;
	std::cout<<std::endl<<std::endl;
	
	//2. extract some area by capture group
	std::vector<std::string> phone_numbers={"010-1234-5678", "010-123-4567", "011-1234-5567", "010-12345-6789", "123-4567-8901", "010-1234-567"};
	std::regex rere("[01]{3}-(\\d{3,4})-\\d{4}");//01로 이루어진거 3개, int로 이루어진거 3개나 4개, int 4개
	std::smatch match;//for saving result
	for(const auto &number: phone_numbers)
		if(std::regex_match(number, match, rere))//save matched all number and matched part
			for(size_t i=0; i<match.size(); i++)
				std::cout<< "Match : " << match[i].str() << std::endl;
	std::cout<<std::endl<<std::endl;
	
	//3. search part string in whole string
	std::string html=R"(
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
    
    std::regex rerere(R"(<div class="sk[\w -]*">\w*</div>)");//search: <div class="sk...">...</div>
    std::smatch matchmatch;
    while(std::regex_search(html, matchmatch, rerere)){
    	std::cout<<matchmatch.str()<<std::endl;
    	html=matchmatch.suffix();//if not, regex_search will make same result(that we already found). so we have to updata html.
	}
	std::cout<<std::endl<<std::endl;
	
	//4. search part string in whole string *by using iterator!*
	html=R"(
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
	
	std::regex rei(R"(<div class="sk[\w -]*">\w*</div>)");
	std::smatch storage;
	auto start=std::sregex_iterator(html.begin(), html.end(), rei);
	auto end=std::sregex_iterator();
	
	while(start!=end){
		std::cout<<start->str()<<std::endl;
		start++;
	}
	std::cout<<std::endl<<std::endl;
	
	//5. replace by back reference
	html=R"(
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
    
    std::regex reho(R"r(sk-circle(\d))r");
    std::string modified_html=std::regex_replace(html, reho, "$1-sk-circle");
    //std::regex_replace(std::ostreambuf_iterator<char>(std::cout), html.begin(), html.end(), reho, "$1-sk-circle");//for just print
    std::cout<<modified_html;
}

/*
1.	패턴에 일치하는거 찾아내기
2.	패턴에 맞는 문자열에서 일부분 뽑아내기 
3.	패턴을 만족하는 문자열 일부 검색하기
	정규 표현식이 탐지된 부분을 match.str()로 얻을 수 있고, 그 전을 match.prefix(), 그 후를 match.suffix()라고 표현한다. 
4.	std::regex_iterator을 사용한 탐색 
5.	원하는 패턴 치환하기 back reference $1
6.	특정한 패턴을 날려보내고 싶다면 괄호가 열리는 순서대로 $1, $2...가 되기에 날릴부분을 캡쳐하고, 살릴부분을 캡쳐하여 $1을 사용하지 않고 $2를 사용하여 치환하면 된다. 
 
*/

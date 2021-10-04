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
	std::regex rere("[01]{3}-(\\d{3,4})-\\d{4}");//01�� �̷������ 3��, int�� �̷������ 3���� 4��, int 4��
	std::smatch match;//for saving result
	for(const auto &number: phone_numbers)
		if(std::regex_match(number, match, rere))//save matched all number and matched part
			for(size_t i=0; i<match.size(); i++)
				std::cout<< "Match : " << match[i].str() << std::endl;
	std::cout<<std::endl<<std::endl;
	
	//3. search part string in whole string
	std::string html=R"(
        <div class="social-login">
          <div class="small-comment">�������� �α��� </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            �Ǵ� ���� �Է��ϼ��� (��� ������ ��й�ȣ�� �ʿ��մϴ�)
          </div>
          <input name="name" id="name" placeholder="�̸�">
          <input name="password" id="password" type="password" placeholder="��й�ȣ">
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
          <div class="small-comment">�������� �α��� </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            �Ǵ� ���� �Է��ϼ��� (��� ������ ��й�ȣ�� �ʿ��մϴ�)
          </div>
          <input name="name" id="name" placeholder="�̸�">
          <input name="password" id="password" type="password" placeholder="��й�ȣ">
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
          <div class="small-comment">�������� �α��� </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            �Ǵ� ���� �Է��ϼ��� (��� ������ ��й�ȣ�� �ʿ��մϴ�)
          </div>
          <input name="name" id="name" placeholder="�̸�">
          <input name="password" id="password" type="password" placeholder="��й�ȣ">
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
1.	���Ͽ� ��ġ�ϴ°� ã�Ƴ���
2.	���Ͽ� �´� ���ڿ����� �Ϻκ� �̾Ƴ��� 
3.	������ �����ϴ� ���ڿ� �Ϻ� �˻��ϱ�
	���� ǥ������ Ž���� �κ��� match.str()�� ���� �� �ְ�, �� ���� match.prefix(), �� �ĸ� match.suffix()��� ǥ���Ѵ�. 
4.	std::regex_iterator�� ����� Ž�� 
5.	���ϴ� ���� ġȯ�ϱ� back reference $1
6.	Ư���� ������ ���������� �ʹٸ� ��ȣ�� ������ ������� $1, $2...�� �Ǳ⿡ �����κ��� ĸ���ϰ�, �츱�κ��� ĸ���Ͽ� $1�� ������� �ʰ� $2�� ����Ͽ� ġȯ�ϸ� �ȴ�. 
 
*/

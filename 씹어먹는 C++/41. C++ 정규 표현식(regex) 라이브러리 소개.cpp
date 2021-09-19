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
  
  std::regex re(R"r((sk-circle(\d) sk-circle))r");//that can contain all string that we will change like "sk-circle1 sk-circle"
  std::smatch match;//why? for saving later?
  //literal r is raw-string literal that can express original string that doesn't use escape sequence
  
  std::string modified_html=std::regex_replace(html, re, "$2-sk-circle");//like index of array
  std::cout<<modified_html;
	
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
1.	regex_match�� �̿��Ͽ� ��ü ���ڿ��� �־��� ���� ǥ���� ������ �����ϴ����� �˾Ƴ� �� �ִٸ�, �ش� ������ �����ϴ� ���ڿ����� ���� �Ϻκ��� �̾Ƴ��� �ʹٸ�?
	��ȭ��ȣ�� �޴� ���� ǥ������ �����غ���.
	-(����)-(����)-(����)��
	-�Ǿ��ڸ��� �ݵ�� 3�ڸ��� 0�̳� 1�� �̷����
	-����ڸ��� 3�ڸ��� 4�ڸ���
	-�������ڸ��� 4�ڸ���
	010-1234-5678
	010-123-4566
	011-1234-5678
	[01]{3}-\d{3,4}-\d{4} ��� regular expression�� ��Ÿ�� �� �ִ�.
	[01]�� 0Ȥ�� 1�̶�� ���̰�, {3}�� �ش� ������ ���ڰ� 3�� ��Ÿ�� �� �ִٴ� ���̴�. 
2.	���� ��� ��ȣ�� �����ϰ� �ʹٸ� ĸ�� �׷�(capture group)�� ����� �� �ִ�. 
	regular expression���� ���ϴ� �κ��� ()�� ���ΰ� �ȴٸ� �ش� �κп� ��Ī�� ���ڿ��� ���� �� �ִ�.
3.	smatch�� ��Ī�� ���ڿ��� std::string���� �����ش�. const char*�� �����ִ� cmatch�� �ִ�. 
4.	regex_match�� ��ü ���ڿ��� ��Ī�� ���̱⿡ ù ��° ����� ��ü ���ڿ��� �����ϰ�, �� �������� ()�ȿ� ����ִ� ���ڿ��� ��Ÿ���� �ȴ�.
	���� ���� ǥ���� �ȿ� ()�� ������ �ִٸ� ���������� for���� ���� ���������� ������ �����ϴ�.

[3.	���ϴ� ���� �˻��ϱ�]
1.	regex_match�� ���� ���ڿ� ��ü�� ���Ͽ� �����ϴ��� ���θ� Ȯ���Ͽ���. ���� ��ü ���� ������ �����ϴ� ���ڿ� �Ϻθ� �˻��ϰ� �ʹٸ�?
	HTML���� <div class="sk...">...</div>�� ���� ������ �±׸� �а� �ʹٸ� ����ǥ������
	
	<div class="sk[\w-]*">\w*</div>�� ��Ÿ�� �� �ִ�. 
2.	std::smatch�� �˻��� ������ �����ϴ� ������ ���� �� �ְ�, std::regex_search�� std::regex_match�� ���ڷ� �������ν� ��������� �������� �� �ִ�.
	�ٸ� HTML�ȿ����� ���� vector�� ���� ���Ұ� ���е��� ���� ������ ������ ã���� �̴� iterator���� ���� �ƴϱ⿡, while�� ����� �� �ִµ� �� �ӿ� std::cout<<match.str()�� ���� ó���� �ѵڿ�
	�ٽ� while's condition�� Ȯ���ϸ� ó������ �ٽ� Ž���ϴ� �Ͱ� ���� �̹� ����� ������ ��Ž���ϰ� �ȴ�. ��� html�� ������Ʈ���־�� �ϴµ�,
	std::smatch match��ü�� match.suffix()�� �̹� Ž���� �޺κ��� �����԰� ���ÿ� stringŸ���� operator�� �־� �ܼ��� ������ html string�� �������ָ�
	Ž���� �κ��� �����Ͽ� html�� ������Ʈ �� �� �ִ�.
	
[4.	std::regex_iterator]
1.	��� regex_iterator�� �����Ͽ� �̸� �̿��ϸ� �� ���ϰ� �˻��� ������ �� �ִ�.
2.	sregex_iterator�� string�� ����ϴ� regex_iterator�̰�, �����ڿ� html.start()�� html.end()�׸��� regular expression�� ȣ���Ͽ� ������ �����ϴ�.
	�̴� ó�� ������ ����, ++�����ڷ� ������ ������ regex_search�� ���� ������ �����ϴ� ���ڿ��� �˻��Ѵ�. 
3.	���� *�����ڸ� ���� �������Ѵٸ� ���� �˻��� ���Ͽ� ���� match_results ��ü�� ���� �� �ִ�.
	��� std::cout<<start->str();ó�� �����ϰ� ���ϰ� ��Ī�Ǵ� ���ڿ����� �̾Ƴ� �� �ִ�.
	
[5.	���ϴ� ���� ġȯ�ϱ�]
1.	���� ǥ������ ���Ͽ� ���ϴ� ������ ���ڿ��� �ٸ� ���ڿ��� ġȯ(replace)�� std::regex_replace�� ���Ͽ� ������ �� �ִ�.
	html���� sk-circle1�� ���� ���ڿ��� 1-sk-circle�� �ٲپ�� ���� ǥ������ �����غ���.
	 �켱 �츮�� sk-circle1�� � regex�� ��ĥ��ų�� �����ؾ��ϴµ� �̴� sk-circle\d�� ������ �� �ִ�.
	���� ġȯ�ϰ� ���� ���´� ����-sk-circle���ε�, ������ ���ڿ� �ش��ϴ� �κ��� ��Ī�� ������ \d�� �ش��ϴ� �κ��̶�� ���� �ִ�.(���� ���ű��)
	������, ĸ�� �׷��� �̿��Ͽ� �̸� ������ �ذ��� �� �ִ�.
	 ����, sk-circle(\d)�� ���Ͽ� �ش� �κ��� ù��° ĸ�ı׷����� �����,
	ġȯ�� �� ��, ù ��° ĸ�� �׷��� ǥ���ϱ� ���� $1�� ����� �� �ִ�.(�̿� ���� ��Ҹ� back reference��� �θ�) 
	���� $1-sk-circle�� ǥ���� �����ϴ�.
	 �̸� �ڵ�� �Űܺ���. 
2.	std::regex_replace(html, re, "$1-sk-circl");ó�� html, regular expression, ġȯformat�� �־� std::string��ü�� �����ϸ�, string���� overloading�ȴ�.
3.	���� ��ü�� �������� �ʰ� �׳� stdout�� ����ϰ� ������
	std::regex(std::ostreambuf_iterator<char>(std::out), html.begin(), html.end(), re, "$1-sk-circle");ó�� 
	std::regex_replace�� ù��° ���ڷ� ����� ��ġ�� �������� ����Ű�� �ݺ��ڸ� �־��ָ� �ȴ�.
4.	�ߺ��� ĸ�� �׷�
	���ư� <div class="sk-circle1 sk-circle">a</dic>����
	<div class="1-sk-circle">a</div>ó�� ġȯ�� ���ÿ� �޺κ��� ���������� �ʹٰ� �غ���.
	 �̸� ���� �ΰ��� ĸ�ı׷��� �ʿ��ϴ�. (sk-circle(\d) sk-circle)�� ��ü�� ���ںθ� ���� �� �ִ�.
	��ó�� ��ȣ�� ��ø�Ǿ�����, ��ȣ�� ������ ������� $1, $2..�� �����ϱ⿡ ���� ��쿣 ��ü�� $1�̰� \d�� $2�̴�.
	 ġȯ�� ������ $2-sk-circle�̴� �ڵ带 �ۼ��غ���. 
	 
[6.	�������ϸ�]
1.	std::regex�� ���Ͽ� ���� ǥ���� ��ü������ �����ϴ�
2.	std::regex_match�� ��ü ���ڿ��� ������ �����ϴ��� Ȯ���� �����ϴ�
3.	std::regex_search�� ���Ͽ� �´� ���ڿ��˻��� �����ϴ�
4.	std::regex_replace�� ���ϴ� ������ ���ڿ��� �ٸ� ���ڿ��� ġȯ�� �����ϴ�. 
*/ 

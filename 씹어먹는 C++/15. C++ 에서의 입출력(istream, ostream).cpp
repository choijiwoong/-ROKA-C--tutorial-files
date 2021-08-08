#include <iostream>
#include <string> 

/*1,2
int main(){
	std::string s;//cin can't handle space at one time.
	while (false){
		std::cin>>s;
		std::cout<<"word: "<<s<<std::endl;//input with seperation by space..etc
	}
	
	int t;//type error
	while(false){
		std::cin>>t;
		std::cout<<"�Է�:: "<<t<<std::endl;//if input is sentence, error.
		if(t==0)
			break;
	}
	
	//int T;
	//while(std::cin>>T){//input at while()
	//	std::cout<<"�Է� :: "<<T<<std::endl;//no roof error!! 
	//	if(T==0)
	//		break;
	//}
	
	//int y;
  	//std::cin >> y;  //if we type char deliberately, then failbit will be turned on.
  	//std::cout << "fail ��Ʈ�� ���� �����̹Ƿ�, �Է¹��� �ʴ´�" << std::endl;
  	//std::string S;
  	//std::cin >> S;//no input. return.
	
	int T;//solution
	while(true){
		std::cin>>T;
		std::cout<<"�Է� :: "<<T<<std::endl;
		if(std::cin.fail()){//if fail function(not fail flag!!) is on(fail func is defined at ios class that will return when failbit is true or badbit is true)
			std::cout<<"����� �Է����ּ���"<<std::endl;
			std::cin.clear();//initialization of flags(clear function is defined in ios class too, if no argument, it initialize flag to goodbit. it means deleting of fail status)
			std::cin.ignore(100,'\n');//ignore before \n(ignore function is defined at istream class. buffer ignore until read '\n' in maximum 100 length.
		}//so if we input char that has length over 100, ignore function will be called until deleting buffer's char.
		if(T==1)
			break;
	}
	
	return 0;
}*/

/*3
int main(){	
	int t;
	while(false){//basefield saves what notation we use. so initialization of basefield by locate 2nd argument. and set hex.
		std::cin.setf(std::ios_base::hex, std::ios_base::basefield);//setf function can change setting of stream by argument's <format flag>.
		std::cin>>t;//ex) 0xFF
		std::cout<<"�Է� :: "<<t<<std::endl;//ex) 255
		if(std::cin.fail()){
			std::cout<<"����� �Է����ּ���"<<std::endl;
			std::cin.clear();
		}
		if(t==0) 
			break;
	}
	while(true){//other way
		std::cin>>std::hex>>t;//hex change the way of getting num at cin. it calls <Manipulator>(hex is function but this std::hex is different of std::ios_base::hex explicitly.)
		std::cout<<"�Է� :: "<<t<<std::endl;
		if(std::cin.fail()){
			std::cout<<"����� �Է����ּ���"<<std::endl;
			std::cin.clear();
			std::cin.ignore(100,'\n');
		}
		if(t==0)
			break;
	}
	
	return 0;
}*/

int main(){
	std::string s;
	std::cin>>s;//content: hello world\n
	
	//move once placeholder, and peek next char.(not move) status of stram location holder after cin>>s is hello^world\n. Then, snextc() make stream location holder move once and return w. then!!! no touch stream location holder, reread, print world\n not orld\n!
	char peek=std::cin.rdbuf()->snextc();//cin.rdbuf() return pointer that point stremabuf object that cin object work. then, cin object is istream object, so streambuf object only has get area.
	if(std::cin.fail()) std::cout<<"Failed";
	std::cout<<"�� ��° �ܾ� �� �� ����: "<<peek<<std::endl;
	std::cin>>s;
	std::cout<<"�ٽ� ������ : "<<s<<std::endl;
	
	return 0;
} 

/*
[1.	C++ ����� ���̺귯��]
1.	C++�� ��� ����� Ŭ������ ios_base�� ��� Ŭ������ �ϰ� �ȴ�. �� Ŭ������ ���� ���� ���� �ʰ�, ��Ʈ���� ����� ���� ���� �����͸� ó���Ѵ�.ex) �Ǽ����� ����� ��, û�е��� ��� ����, �������� �������, 10������ ���� 16������ ���� etc..
	 �� �������� ios Ŭ������ ������ ��Ʈ�� ����(������ �ӽ� �����)�� �ʱ�ȭ �Ѵ�. ex)����ڰ� 1bite�� �д´ٰ� ������ �����δ� �� ���ͱ�(ex.513bite)�� �ѹ��� �о� ��Ʈ�� ���ۿ� �����ѵڿ� ����ڰ� ��û�� ������ 1bite�� ����.
	�̷��� ��Ʈ�����۸� ����ϴ� ������ �ϵ��ũ���� �о���� �۾��� �ſ� �����⿡ �ѹ� ���� �� 1bite�� ������ ��û�� �����̰� �߻��ϱ� �����̴�. ���⵵ ���������̴�.
	iosŬ������ ��Ʈ�� ���� �ܿ���, ���� ����� �۾��� ���¸� ó���Ѵ�. ex)������ �дٰ� ���� �����ߴ°�? eof�Լ�, ���� ������� �� ������ �� �ִ°�?good�Լ�.

[2. iostream Ŭ����]
1.	ios_base�� ios Ŭ�������� ����� �۾��� ���� ������ ����־��ٸ�, iostream�� ������ �Է��� �����ϴ� Ŭ�����̴�.ex)operator>>�� istreamŬ������ ���ǵǾ��ִ� ������, cin�� istreamŬ������ ��ü �� �ϳ�.
	std::cin>>a;�� �� �� �ְԲ� ��� �⺻ Ÿ�Ե鿡 ���� ���ǰ� operator>>�� �Ǿ� �ִ�. �׷��ٰ� string���� istream�� ��� �Լ��� ���� ���� �Է¸��ϴ� ���� �ƴϰ�,
	�ܺ� �Լ��� ������ �����ε��� �Ͽ� ����� �� �ִ�.
	istream& operator>>(istram& in, std::string&s){
		//make
	} 
2.	operator>>�� �Ǵٸ� Ư¡���δ�, ��� ���鹮��(���� ���� �� ��)�� �Է½�Ű�� �����ع�����. ��� cin�� ���Ͽ� ������ �Է¹޴´ٸ�, ù �ܾ �Է¹ް� �������� ���� �� ����. 
	int�� ������ 'c'�� ���� �ٸ� Ÿ���� �Է��ϸ� ������ �߻��Ǵµ� �� ������ �ռ���, ios Ŭ������ ��Ʈ���� ���¸� �����Ѵٰ� �ռ��� ���ߴ�.
	�̶� ��Ʈ���� ���¸� �����ϴ� �÷���(flag; ��Ʈ 1�� ������)�� 4���� ���ǵǾ� �ְ�, �� 4���� �÷��׵��� ��Ʈ���� ���� ��� ���������� ���Ͽ� ������ �����Ѵ�.
	4���� Ŭ���״� goodbit, badbit, eofbit, failbit��, ����� �۾��� ������ ��, ���� �Ұ��� ���� �߻� ��, �Է� �۾� �� EOF���޽�, ���� ������ ���� �߻��ø� ��Ÿ����.
	���� ���� �ڵ�ó�� Ÿ���� �޶� ���ڸ� �Է��� ���, �׳� ���� ��Ʈ�� ���ۿ� ���ִ� 'c\n'�� �����ع����� �Ǳ⿡ badbit�� �ƴϰ�, failbit�� ������ �ȴ�. �׸��� �Է°��� ���� �ʰ� �׳� �����ع�����.
	���⼭�� ������ �׳� �����ϸ鼭 ���ۿ� �����ִ� 'c\n'�̴�. �׷��⿡ ���ѹݺ��ϸ� �����Ⱚ�� ��µǴ� ���̴�. 
3.	std::cin���� Ÿ�Կ����� ���ѷ����� �������� while(std::cin>>t)�� ���� �ذ��� �� �ִµ�, ios���� operator void*() const; �Լ��� ���ǵǾ� �ִ�.
	�̴� ios��ü�� void*�� ��ȯ�� �ִµ�, �� ��, NULL�����Ͱ� �ƴ� ���� �����ϴ� ������, failbit, badbit�� ��� off�� ���̴�.(������డ���Ҷ�)
	�ٵ� 's'�� �츮�� �Է��ϸ� operator>>�� cin�� failbit�� �ѰԵǰ�, std::cin>>t�� cin�� ���ϵǴµ�, ���ϰ��� while�� ���ǽ����� ���� ������ �����Ϸ��� ������ Ÿ�� ��ȯ�� ã�� �ǰ�,
	�ᱹ, ios��ü->void*->bool�� ���� 2�� ��ȯ�� ���ؼ� while���� ���������� �ȴ�.(NULL�� bool�� false) 
	 ����, ������ failbit�� �����ֱ⿡ flag�� �ʱ�ȭ ���� �ʴ� �� cin�� �̿��Ͽ� �Է��� ���� �� ���� �� �����ϴ�. �ٸ� ������ �ذ�Ǿ��� ��.

[3.	���� �÷���(format 'flag')�� ������(Manipulator)]
1.	ios_base Ŭ��������, ��Ʈ���� ����� ������ �ٲ� �� �ִٰ� �ߴ�. �Է� �� ���ݱ����� 10������ ó���Ǿ�����, 16������ ó���� ���� �ְ� �� �� �ִ�. 
2.	setf function's version has two. �ϳ��� ���� 1���� �޾� ���ڷ� �� ���� �÷��׸� �����ϴ� ���̰�, ���ڸ� 2�� ���ϴ� ���� �� ��° ����(������ basefield)�� ������ �ʱ�ȭ �ϰ�, ù ��° ����(hex)�� �����ϴ� ����̴�.
3.	����, 16������ ó���ϴ� �Լ��� �׳� ���� �ȴ�. ���ڿ��� �Է¹޾� ó���ص� ������, 0x�� ���ڿ� �տ� ������ �Ⱥ�����(16����������Ÿ��), a123���� A123���� ���� ��찡 �ֱ⿡
	�׳� IO���̺귯������ �����ϴ� ����� ����ϴ� ���� ����.
	 ù ��°�� std::cin::setf(format flag, initialization)������� format flag ���� �÷��׸� ����Ͽ� �����ϰų�, std::cin>>std::hex>>t;�� ���� Manipulator �����ڸ� ����Ͽ� ������ �� �ִ�.
	�̶� std::hex�� function�̰�, format flag's hex�� ���� ��� '��'����, �̸��� ���� �� �ٸ� ���̴�.(std::ios_base::hex) 
	 ���� �÷��� hex that is manipulator�� ios_base object�� reference�� �ް�, �ٽ� �� ��ü�� �����ϰ� ���ǵǾ� �ִ�.
	std::ios_base& hex(std::ios_base& str); 
	�׷��ٸ� ���� operator>>�� �� �Լ��� ���ڷ� ������ ��쵵 �ִ�.
	istream& operator>>(ios_base& (*pf)(ios_base&));
	�׳� operator>>���� �����ڸ� �޴´ٸ� �ܼ��� pf(*this)�� ȣ���ϴ� ���̴�. �׸��� ȣ��� hex�Լ��� �ܼ���
	str.setf(std::ios_base::hex, std::ios_base::basefield)�� �����ϰ� �ȴ�. 
	 ��, setf�� ���� ������� �ʰ�, manipulator�� ����Ͽ� �����ϰ� �Է� ������ �ٲ� �� �ִ�. ���� �������� ���� ���� hex���� �پ��ѵ�, true�� false�� 1�� 0�� �ƴ� ���ڿ��� ó���ϴ� boolalpha�� �ְ�,
	��� �������� ���� Ȥ�� ���������� ���� ��Ű�� left�� right������ �� ���������� �ִ�.(std::endl�� �������� �ϳ��ε�, ����� �����ϴ� ostream�� ���ǵǾ��ִ� �����ڷ�, ���� ���๮�ڸ� ����ϴ� �� ����, ��� ���۸� ��� ��������(flush)��Ȱ�� �����Ѵ�!
	�̷��� flush��Ȱ�� �Ϲ������� ���۸� �̿��Ͽ� ������� ���ڰ� ���δ��� �������� ��İ� �ٸ��� ������ �ð��� ���� ���缭 ȭ�鿡 ����ؾ��ؼ� �ٷιٷ� ���������ϴ� ��쿡 ���ȴ�.
	flush�� ���ۿ� �����Ͱ� �󸶳� �׿��ֵ��� ���� �ٷ� ����� ���ִ� �Լ��̴�. ���� �ٽ� �������� ���ư��ڸ� std::endl �����ڴ� ��Ʈ���� '\n'�� ����ϴ� �Ͱ� ���Ҿ� flush�� �������ش�.

[4.	��Ʈ�� ���ۿ� ����] 
1.	��� ����� ��ü���� �̿� �����Ǵ� ��Ʈ�� ��ü�� ������. �� C++�� ����� ���̺귯���� �����Ǵ� ��Ʈ�� ���� Ŭ������ streambufŬ����(�� �״�� ���ڵ��� ���������� �޸��� ������ ��)�� �����Ѵ�. 
	�̴� �츮�� ȭ�鿡 �Է��ϴ� ���ڵ� ��� ��Ʈ���� ���Ͽ� ���α׷��� ���޵ȴٴ� ���̰�, �ϵ��ũ���� ������ �д� ��, �ٸ���ǻ�Ϳ� TCP/IP��ſ��� ��� ��Ʈ���� ���� �̷�����ٴ� ���� �ǹ��Ѵ�.
	���� C++������ std::stringstream�� ���Ͽ� ����� ���ڿ��� ��ġ ��Ʈ���ΰ� ó�� ����� �� �ְԵ� ���ش�.
	 ��ư �ٽ� ��������, streambuf�� ��Ʈ���� ���� ���� �⺻���� ��� ����Ѵ�. 
	streambufŬ������ ��Ʈ���� ���¸� ��Ÿ���� ���ؼ� �� ���� �����͸� �����ϰ� �ִµ�, ������ ���� �κ��� ����Ű�� ���� ������, �������� ���� ���ڸ� ����Ű�� �ִ� ������(��Ʈ�� ��ġ ������), ������ ���� ����Ű�� �� �����Ͱ� �ִ�.
	���� streamvufŬ������ �Է� ���ۿ� ��� ���۸� �����ϱ� ���� get area�� put area�� �����Ͽ� �θ��µ�, �̿� ���� ������ ����Ű�� �����͵� g�� p�� �ٿ��� ǥ���ϰ� �ȴ�. 
2.	of coursely, streambuf�� snextc�Լ� ���� �پ��� �Լ����� ���ǵǾ� �ִ�. �� ����� �ʿ�� ������, ���� C++ ����� ���̺귯���� ��Ʈ�� ���۸����� �߻�ȭ�Ͽ� Ŭ������ ������ٴ� ���� �˰� ������ ����.
	����, C++���� streambuf�� ������ ������ 1bite���� ���� �ƴ϶� wchar_t, �� ���� ����Ʈ ���ڵ�(ex. UTF-8)�� ���� ó���� �����ϰ� �ϱ� �����̴�.
	��, ���� ����Ʈ ������ ���, ����ڰ� ���� �� ���� �䱸�ص� ��ũ�������z 1����Ʈ�� ���� �� �ְԵ����� 2����Ʈ, ������ 4����Ʈ���� �ʿ��� ��찡 �ִ�. �׸��Ͽ� �̷��� �͵��� 
	��Ʈ�� ���� ��ü ��ü���� �����ϵ��� �Ͽ� ����ڰ� ����� ó���� �̿��ϴµ� �����ϰ� �Ͽ���. 
*/

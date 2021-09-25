#include <iostream>
#include <string>

//solution of input error
int main(){
	int t;
	while(1){
		//std::cin.setf(std::ios_base::hex, std::ios_base::basefield);//change format of istream to hex. //VALUE!
		std::cin>>std::hex>>t;//manipulator that changes io format by manipulating io stream. FUNCTION! like bool alpha, std::endl
		std::cout<<"input "<<t<<std::endl;//input normally
		if(std::cin.fail()){//if failbit is on
			std::cout<<"type right"<<std::endl;
			std::cin.clear();//clear flags
			std::cin.ignore(100, '\n');//ignore until '\n'
		}
		if(t==1) break;
	}
} 

//streambuf
int main(){
	std::string s;
	std::cin>>s;//hello world! but cin get one word by space or \n. So only hello is inputted to S, and ' world!' stay in input buffer.
	//manipulate streambuf! 
	char peek=std::cin.rdbuf()->snextc();//readbuffer's location pointer move one space(' |world!'), and spy next char without moving(' |world!')
	if(std::cin.fail()) std::cout<<"Failed";
	std::cout<<"first char of second word: "<<peek<<std::endl;
	std::cin>>s;
	std::cout<<"read! : "<<s<<std::endl;
} 

/*
1.	ios_base(��Ʈ�� ����� ����), ios(��Ʈ�� ���� �ʱ�ȭ&����� �۾� ����), istream&ostream(���� �����), ifstream. ofstream, iostream, fstream
2.	cin�� ���⳪ ���鹮�ڸ� �и��ؼ� �Է¹޴´�. 
3.	ios���� goodbit, badbit, eofbit, failbit�� ����ϴµ�, ���� cin�� �߸��� ���� ���� �� failbit�� Ű�� ���۸� ���� ���� ������ ������. flag�� �̿��Ͽ� ���������� ó���� �� �ִ�. 
4.	std::ios_base�� �̿��Ͽ� ����� ���ĺ����� �����ѵ�, �̴� ������(manipulator)_�Լ��ε� �����ϴ�.
5.	std::streambuf�� �Ϲ����� ���ڿ��� ��Ʈ��ó�� ����� �����ϴ�. 
6.	streambufŬ������ ������ ���ۺκ�_���������Ϳ�, ���� ����_��Ʈ�� ��ġ �����ڿ�, �� �κ�_�� �����Ͱ� �ִ�. �̶� �Է¹��۸� get area, ��� ���۸� put area��� ǥ���Ѵ�. 
7.	streambuf�� ���� ������ ���� ����Ʈ ���ڵ鿡 ���� ����ڰ� ����� ó���� �̿��ϱ� �����ϰ� �ϴµ��� ������ �ִ�. 
*/

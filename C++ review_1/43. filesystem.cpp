#include <iostream>
#include <filesystem> 

namespace fs=std::filesystem;
//file is exist?
int main(){
	std::filesystem::path p("./some_file");
	
	//is file & is regular file not soket or device & is firectory
	std::cout<<"Does "<<p<<" exist? ["<<std::boolalpha<<fs::exists(p)<<"]"<<std::endl;
	std::cout<<"Is "<<p<<" exist? ["<<fs::is_regular_file(p)<<"]"<<std::endl;//for linux(linux judge device & socket to file)
	std::cout<<"Is "<<p<<" directory? ["<<fs::is_directory(p)<<"]"<<std::endl;
	std::cout<<std::endl;
	
	//get path
	std::cout<<"current path: "<<fs::current_path()<<std::endl;
	std::cout<<"relative path: "<<p.relative_path()<<std::endl;
	std::cout<<"absolute path: "<<fs::absolute(p)<<std::endl;
	std::cout<<"canonical path: "<<fs::canonical(p)<<std::endl;
	std::cout<<std::endl;
	
	//search all files in directory
	for(const fs::directory_entry& entry: fs::directory_iterator(fs::current_path()/"a"))//entry has each file's meta data like name, size, etc..
		std::cout<<entry.path()<<std::endl;//(operator/ is overloaded for add path)
		
	//initialization of directory_iterator must be needed if we change structure of directory like remove, make_dir like this.
	//example of removing file by using directory_iterator with initialization of iterator when strucutre of directory is changed
	fs::path P("./a");//In this directory, we will remove txt file
	while(true){
		bool is_modified=false;
		
		for(const auto& entry: fs::directory_iterator("./a")){//initialization of directory_iterator by using it in for's condition
			const std::string ext=entry.path().extension();
			
			if(ext==".txt"){
				fs::remove(entry.path());
				is_modified=true;
				break;
			}
		}
		
		if(!is_modified){
			break;
		}
	}	
}

/*
1.	파일 데이터의 입출력을 담당하는 fstream과는 달리, filesystem은 파일 자체를 읽지 않고 파일 메타 데이터에 접근을 도와준다. 
2.	filesystem은 모든 클래스와 함수들이 std::filesystem안에 정의되어 있어 주로 namespace fs=std::filesystem;을 정의하여 사용한다.
3.	get_path와 같은 모든 함수는 입력 경로에 파일이 존재하지 않으면 모두 throw하기에 exist를 통해 먼저 확인해야 한다.
	만약 예외를 처리하고 싶지 않다면 마지막 인자로 발생한 오류를 받는 std::error_code객체를 전달하면 throw대신 error_code에 발생한 오류를 설정한다.
	filesystem에서 예외를 던지는 함수들은 모두 error_code를 받는 오버로딩이 제공된다.
4.	디렉토리를 순회하고 싶다면 directory_iterator를 사용할 수 있다. 만약 서브 디렉토리까지 순회하고 싶다면 recursive_directory_iterator를 사용하면 된다.
5.	path객체를 create_directory함수에 넣어 디렉토리를 생성할 수 있다. 다만 생성하는 디렉토리의 부모 디렉토리는 반드시 존재해야 한다.
	만약 부모 디렉토리까지 다 만들고 싶다면 create_directories함수를 사용하자.
	fs::path p("./c/d/e/f");
	fs::create_directories(p); 
6.	파일을 복사하고 싶다면 path객체를 두개(대상과 목표) 만들어 fs::copy(from, to, fs::copy_options::recursive)에 넣으면 가능하다.
	이때, 이미 대상이 존재하면 throw하게 되는데, copy_options::skip_existing(무시)& overwrite_existing(덮어쓰기)& updata_existing(오래된거면 덮어쓰기)옵션으로 해결이 가능하다.
	fs::path from("./a/a.txt");
	fs::path to("./c");
	fs::copy(from, to, fs::copy_options::overwrite_existing);
7.	제거는 제거하고자 하는 것의 path객체를 fs::remove에 넣으면 된다. 다만 빈 디렉토리만 제거가 가능한데,
	비어있지 않은 디렉토리를 제거하고 싶으면 remove_all을 사용하면 된다. 
8.	directory_iterator 사용 시 디렉토리의 구조가 바뀔 때 마다 무효화되기에 매번 새로이 반복자를 초기화해줘야 한다. 
 
*/

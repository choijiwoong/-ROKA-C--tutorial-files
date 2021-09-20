#include <iostream>
#include <filesystem>

/*1 example of filesystem
int main(){
	std::filesystem::path p("./some_file");
	
	std::cout<<"Does"<<p<<" exist? ["<<std::boolalpha<<std::filesystem::exists(p)<<"]"<<std::endl;
	std::cout<<"Is"<<p<<" file? ["<<std::filesystem::is_regular_file(p)<<"]"<<std::endl;//common file (like is_file..?) linux deals with socket & device to file.- Everything is a File!
	std::cout<<"Is"<<p<" directory? ["<<std::filesystem::is_directory(p)<<"]"<<std::endl;
	
	//Does "./some_file" exist? [true]
	//Is "./some_file" file? [true]
	//Is "./some_file" directory? [false]
} */

namespace fs=std::filesystem;
/*2 some function related to path
int main(){
	fs::path p("./some_file.txt");
	
	std::cout<<"my current path : "<<fs::current_path()<<std::endl;//path executing program
	std::cout<<"relative path : "<<p.relative_path()<<std::endl;
	std::cout<<"absolute path : "<<fs::absolute(p)<<std::endl;//disadvantage of sbsolute is it can include needless element like . or ..
	std::cout<<"official sbsolute path : "<<fs::canonical(p)<<std::endl;//develooped absolute
	
	//my current path : "/Users/jblee/Test"
	//relative path : "./some_file.txt"
	//absolute path : "/Users/jblee/Test/./some_file.txt"
	//official sbsolute path : "/Users/jblee/Test/some_file.txt"
}*/

/*3 itinerate all files in directory
int main(){
	fs::directory_iterator itr(fs::current_path()/"a");//operator/ to pass path that we will search. it defines iterator itself unlike vector.begin().
	while(itr!=fs::end(itr)){//we can get end of iterator by std::filesystem::end(iterator)
		const fs::directory_entry& entry=*itr;//each iterator points directory_entry that indicates each files defined in directory. directory_entry has many information like name, size..etc
		std::cout<<entry.path()<<std::endl;
		itr++;
	}
	
	//"/Users/jblee/Test/a/3.txt"
	//"/Users/jblee/Test/a/2.txt"
	//"/Users/jblee/Test/a/1.txt"
	//"/Users/jblee/Test/a/b"
	
	//we can use it by range for
	for(const fs:directory_entry& entry: fs:directory_iterator(fs::current_path()/"a"))
		std::cout<<entry.path()<<std::endl;
		
	//but one disadventage of directory_iterator is it doesn't lool inside of directoty in that directory.
	//if we want to itinerate directory+subdirectory, we can use recursive_directory_iterator
	for(const fs::directory_entry& entry: fs::recursive_directory_iterator(fs::current_path()/"a"))
		std::cout<<entry.path()<<std::endl;
}*/

/*5 mkdir
int main(){
	fs::path p("./a/c");
	std::cout<<"Does "<<p<<" exist? ["<<std::boolalpha<<fs::exists(p)<<"]"<<std::endl;
	
	fs::create_directory(p);//parent directory(a) must be existing. if we do like "./c/d/f/e" without rule, it throw exception.
	std::cout<<"Does "<<p<<" exist? ["<<fs::exists(p)<<"]"<<std::endl;
	std::cout<<"Is "<<p<<" director? ["<<fs::is_directory(p)<<"]"<<std::endl;
	
	//Does "./a/c" exist? [false]
	//Does "./a/c" exist? [true]
	//Is "./a/c" directory? [true]
	
	//if we want to make directory with parent directory at once, can use create_directories()
	fs::path p("./c/d/e/f");
	std::cout<<"Does "<<p<<" exists? ["<<std::boolalpha<<fs::exists(p)<<"]"<<std::endl;
	
	fs::create_directories(p);
	std::cout<<"Does "<<p<<" exist? ["<<fs::exists(p)<<"]"<<std::endl;
	std::cout<<"Is "<<p<<" directory? ["<<fs::is_directory(p)<<"]"<<std::endl;
	//we can check it by tree command
}*/

/*6 In a->(a.txt, b->c.txt) ,c, copy a to c
int main(){
	├── a
	│   ├── a.txt
	│   └── b
	│       └── c.txt
	├── c
	
	fs::path from("./a");
	fs::path to("/c");
	fs::copy(from, to, fs::copy_options::recursive);//way of copy. recursive copy all files and directories. default option copy only files in a(a.txt)
	
	├── a
	│   ├── a.txt
	│   └── b
	│       └── c.txt
	├── c
	│   ├── a.txt
	│   └── b
	│       └── c.txt
	
	//if target to copy is already exist, throw exception
	fs::path from("./a/a.txt");
	fs::path to("./c");
	//fs::copy(from, to);//throw exception!
	fs::copy(from, to, fs::copy_options::overwrite_existing);
	
	//we can choice 3 options: skip_existing, overwrite_existing->update_existing
} */

/*6 delete directory by remove
int main(){
	fs::path p("./a/b.txt");
	std::cout<<"Does "<<p<<" exist? ["<<std::boolalpha<<std::filesystem::exists(p)<<"]"<<std::endl;
	
	fs::remove(p);
	std::cout<<"Does "<<p<<" exist? ["<<std::bolalpha<<std::filesyetem::exists(p)<<"]"<<std::endl;
	
	//Does "./a/b.txt" exist? [true]
	//Does "./a/b.txt" exist? [false]
}*/

/*6 remove can remove derectory that is empty, if not use remove_all
int main(){
	fs::path p("./c/b");
	std::error_code err;
	
	fs:remove(p, err);//fail
	std::cout<<err.message()<<std::endl;//print "Directory not empty"
	
	fs::remove_all(p);//success!
}*/

/*7 point to note in using directory_iterator
//program that remove all files that's txt
int main(){
	fs::path p("./a");
	
	for(const auto& entry: fs::directory_iterator("./a")){
		const std::string ext=entry.path().extension();//get extension for comparing with ".txt"
		
		if(ext==".txt")
			fs::remove(entry.path());//logic error! structure of directory is changed, so entry become useledd iterator.
	}
}*/

//7 solution of upper logical error
int main(){
	fs::path p("./a");
	
	while(1){
		bool is_modified=false;
		
		for(const auto& entry: fs::directory_iterator("./a")){
			const std::string ext=entry.path().extension();
			
			if(ext==".txt"){
				fs::remove(entry.path());
				if_mofidied=true;
				
				break;
			}
		}
		if(!is_modified)
			break;//no continue. iterator is already invalidated. initialization of iterator is needed
	}
}


/*
[0.	들어가기에 앞서]
1.	C++17에 도입된 파일 시스템 라이브러리는 파일 데이터의 입출력을 담당하는 파일 입출력 라이브러리<fstream>과는 다르다.
	<fstream>은 파일 하나가 주어지면 해당 파일의 데이터를 읽어내는 역활을 한다. 그 외의 데이터(이름, 위치 등등)를 수정할 수 없다. 반면에
	파일시스템라이브러리는 파일에 대한 정보(파일 메타데이타)에 접근을 도와주며 파일 자체를 읽는 일은 수정하지 않는다.
2.	하드디드스 어딘가 있는 a.txt를 filesystem라이브러리를 이용해 찾고, fstream을 통해 읽는다.

[1.	파일을 찾아보자]
1.	파일 시스템 라이브러리에는 모든 클래스와 함수들이 std::filesystem namespace안에 정의되어 있다. 예를 들어 path클래스를 사용하려면 std::filesystem::path를 사용해야 한다.like chrono

[2.	경로(path)]
1.	파일의 주소가 아닌 경로(path)라 하는 이유는 컴퓨터에서 해당 파일을 참조할 때 가장 첫 번째 디렉토리부터 순차적으로 찾아가기 때문이다.(/a/b/c는 /a->b->c) 
2.	가장 최상의 디렉토리에서 원하는 파일까지의 경로인 절대 경로(absolute path)와 프로그램 실행 위치에서 해당 파일을 찾는 상대 경로(relative path)중ㅇ에 위 코드의 ./some_file은 .이 현재 디렉토리를 의미하므로 상대경로이다.
3.	filesystem 라이브러리에서 파일이나 디렉토리를 다루는 모든 함수들은 path객체를 인자로 받는데, 원하는 경로의 파일/디렉토리의 path를 정의->해당 path로 파일/디렉토리 정보 수집의 순서롤 작업을 진행한다.
	다만 path객체만으로 exist여부를 모르기에 exists()함수를 사용하여 확인한다.

[3.	여러 경로 관련 함수들]
1.	만약 경로에 파일이 존재하지 않으면 throw해야한다. 고로 호출하기 전에 exists로 존재유무를 보자
2.	예외로 처리하고 싶지 않다면 마지막 인자로 발생한 오류를 받는 std::error_code객체를 전달하자. 이는 error_code객체에 발생한 오류를 설정한다. 
	filesystem에서 예외를 던지는 함수들의 경우 이처럼 마지막 인자로 error_code를 받는 오버로딩이 제공된다. 
	
[4.	디렉토리 관련 작업들]
1.	파일 시스템 라이브러리를 통하여 디렉안의 파일/폴더 보기, 디렉안에 폴더 생성, 디렉안에 파일/폴터 복사, 디렉안에 파일/폴더 삭제 등의 작업을 할 수 있다.
2.	디렉토리 안에 모든 파일들 순회하기_directory_iterator 다만 단점은 디렉안에 다른 디렉이 있으면 그 안까지 안본다. 그럴땐 recursive_director_iterator사용하면 된다. 

[5.	디렉토리 생성하기]
1.	이전에 std::ofstream out("a.txt"); out<<"hi";처럼 파일을 간단하게 생성했었지만, ofstream을 통해서 directory를 생성할 수는 없었다.
	std::ofstream out("./b/a.txt");
	out<<"HI";에서 폴더b가 없다면 a.txt도 생성되지 않고 out<<은 실패한다.
2.	골 filesystem의 create_directory함수를 사용하자. 다만 생성하는 디렉토리의 부모 디렉토리는 반드시 존재해야 한다. 
	만약 부모도 다 만들고싶으면 create_directories함수를 사용할 수 있다. 
	
[6.	파일과 폴더 복사/삭제하기]
1.	기존의 ofstream으로 read->print느낌으로 복사가 가능했지만, 디렉토리를 복사하거나 디렉토리 안의 모든 파일들을 복사하는 등의 작업은 불가능하였지만, filesystem의 copy를 사용할 수 있다.
2.	복사옵션으로 recursive는 모든 걸 복사하는거고 defualt는 파일만 복사한다. 만약 복사대상이 이미 존재한다면 예외를 던지는데,
	이때 skip_existing(무시) overwrite_existing(덮어쓰기) updata_existing(이미 존재하는 파일이 더 오래되면 덮어쓰기)를 옵션으로 사용할 수 있다.
3.	파일/디렉토리 삭제하기_remove
	remove로 디렉을 삭제하려면 반드시 디렉토리여야 하고 차있는 디렉을 지우려면 remove_all을 사용하자. 
4.	directory_iterator사용시 주의할 점
	directory_iterator는 디렉토리의 구조가 바뀔 때마다 무효화 되기에 fs::remove후 entry는 사용할 수 없는 반복자가 되기에 ++entry후 다음 디렉토리 포인팅을 보장할 수 없다.
	고로 삭제시마다 반복자를 초기화를 해주어야 한다. 
	
[7.	마무리하며]
1.	 
	 
*/

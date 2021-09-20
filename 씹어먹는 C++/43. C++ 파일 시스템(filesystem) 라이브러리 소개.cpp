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
	������ a
	��   ������ a.txt
	��   ������ b
	��       ������ c.txt
	������ c
	
	fs::path from("./a");
	fs::path to("/c");
	fs::copy(from, to, fs::copy_options::recursive);//way of copy. recursive copy all files and directories. default option copy only files in a(a.txt)
	
	������ a
	��   ������ a.txt
	��   ������ b
	��       ������ c.txt
	������ c
	��   ������ a.txt
	��   ������ b
	��       ������ c.txt
	
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
[0.	���⿡ �ռ�]
1.	C++17�� ���Ե� ���� �ý��� ���̺귯���� ���� �������� ������� ����ϴ� ���� ����� ���̺귯��<fstream>���� �ٸ���.
	<fstream>�� ���� �ϳ��� �־����� �ش� ������ �����͸� �о�� ��Ȱ�� �Ѵ�. �� ���� ������(�̸�, ��ġ ���)�� ������ �� ����. �ݸ鿡
	���Ͻý��۶��̺귯���� ���Ͽ� ���� ����(���� ��Ÿ����Ÿ)�� ������ �����ָ� ���� ��ü�� �д� ���� �������� �ʴ´�.
2.	�ϵ��彺 ��� �ִ� a.txt�� filesystem���̺귯���� �̿��� ã��, fstream�� ���� �д´�.

[1.	������ ã�ƺ���]
1.	���� �ý��� ���̺귯������ ��� Ŭ������ �Լ����� std::filesystem namespace�ȿ� ���ǵǾ� �ִ�. ���� ��� pathŬ������ ����Ϸ��� std::filesystem::path�� ����ؾ� �Ѵ�.like chrono

[2.	���(path)]
1.	������ �ּҰ� �ƴ� ���(path)�� �ϴ� ������ ��ǻ�Ϳ��� �ش� ������ ������ �� ���� ù ��° ���丮���� ���������� ã�ư��� �����̴�.(/a/b/c�� /a->b->c) 
2.	���� �ֻ��� ���丮���� ���ϴ� ���ϱ����� ����� ���� ���(absolute path)�� ���α׷� ���� ��ġ���� �ش� ������ ã�� ��� ���(relative path)�ߤ��� �� �ڵ��� ./some_file�� .�� ���� ���丮�� �ǹ��ϹǷ� ������̴�.
3.	filesystem ���̺귯������ �����̳� ���丮�� �ٷ�� ��� �Լ����� path��ü�� ���ڷ� �޴µ�, ���ϴ� ����� ����/���丮�� path�� ����->�ش� path�� ����/���丮 ���� ������ ������ �۾��� �����Ѵ�.
	�ٸ� path��ü������ exist���θ� �𸣱⿡ exists()�Լ��� ����Ͽ� Ȯ���Ѵ�.

[3.	���� ��� ���� �Լ���]
1.	���� ��ο� ������ �������� ������ throw�ؾ��Ѵ�. ��� ȣ���ϱ� ���� exists�� ���������� ����
2.	���ܷ� ó���ϰ� ���� �ʴٸ� ������ ���ڷ� �߻��� ������ �޴� std::error_code��ü�� ��������. �̴� error_code��ü�� �߻��� ������ �����Ѵ�. 
	filesystem���� ���ܸ� ������ �Լ����� ��� ��ó�� ������ ���ڷ� error_code�� �޴� �����ε��� �����ȴ�. 
	
[4.	���丮 ���� �۾���]
1.	���� �ý��� ���̺귯���� ���Ͽ� �𷺾��� ����/���� ����, �𷺾ȿ� ���� ����, �𷺾ȿ� ����/���� ����, �𷺾ȿ� ����/���� ���� ���� �۾��� �� �� �ִ�.
2.	���丮 �ȿ� ��� ���ϵ� ��ȸ�ϱ�_directory_iterator �ٸ� ������ �𷺾ȿ� �ٸ� ���� ������ �� �ȱ��� �Ⱥ���. �׷��� recursive_director_iterator����ϸ� �ȴ�. 

[5.	���丮 �����ϱ�]
1.	������ std::ofstream out("a.txt"); out<<"hi";ó�� ������ �����ϰ� �����߾�����, ofstream�� ���ؼ� directory�� ������ ���� ������.
	std::ofstream out("./b/a.txt");
	out<<"HI";���� ����b�� ���ٸ� a.txt�� �������� �ʰ� out<<�� �����Ѵ�.
2.	�� filesystem�� create_directory�Լ��� �������. �ٸ� �����ϴ� ���丮�� �θ� ���丮�� �ݵ�� �����ؾ� �Ѵ�. 
	���� �θ� �� ���������� create_directories�Լ��� ����� �� �ִ�. 
	
[6.	���ϰ� ���� ����/�����ϱ�]
1.	������ ofstream���� read->print�������� ���簡 ����������, ���丮�� �����ϰų� ���丮 ���� ��� ���ϵ��� �����ϴ� ���� �۾��� �Ұ����Ͽ�����, filesystem�� copy�� ����� �� �ִ�.
2.	����ɼ����� recursive�� ��� �� �����ϴ°Ű� defualt�� ���ϸ� �����Ѵ�. ���� �������� �̹� �����Ѵٸ� ���ܸ� �����µ�,
	�̶� skip_existing(����) overwrite_existing(�����) updata_existing(�̹� �����ϴ� ������ �� �����Ǹ� �����)�� �ɼ����� ����� �� �ִ�.
3.	����/���丮 �����ϱ�_remove
	remove�� ���� �����Ϸ��� �ݵ�� ���丮���� �ϰ� ���ִ� ���� ������� remove_all�� �������. 
4.	directory_iterator���� ������ ��
	directory_iterator�� ���丮�� ������ �ٲ� ������ ��ȿȭ �Ǳ⿡ fs::remove�� entry�� ����� �� ���� �ݺ��ڰ� �Ǳ⿡ ++entry�� ���� ���丮 �������� ������ �� ����.
	��� �����ø��� �ݺ��ڸ� �ʱ�ȭ�� ���־�� �Ѵ�. 
	
[7.	�������ϸ�]
1.	 
	 
*/

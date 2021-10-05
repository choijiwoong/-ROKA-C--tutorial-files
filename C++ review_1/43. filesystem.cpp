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
1.	���� �������� ������� ����ϴ� fstream���� �޸�, filesystem�� ���� ��ü�� ���� �ʰ� ���� ��Ÿ �����Ϳ� ������ �����ش�. 
2.	filesystem�� ��� Ŭ������ �Լ����� std::filesystem�ȿ� ���ǵǾ� �־� �ַ� namespace fs=std::filesystem;�� �����Ͽ� ����Ѵ�.
3.	get_path�� ���� ��� �Լ��� �Է� ��ο� ������ �������� ������ ��� throw�ϱ⿡ exist�� ���� ���� Ȯ���ؾ� �Ѵ�.
	���� ���ܸ� ó���ϰ� ���� �ʴٸ� ������ ���ڷ� �߻��� ������ �޴� std::error_code��ü�� �����ϸ� throw��� error_code�� �߻��� ������ �����Ѵ�.
	filesystem���� ���ܸ� ������ �Լ����� ��� error_code�� �޴� �����ε��� �����ȴ�.
4.	���丮�� ��ȸ�ϰ� �ʹٸ� directory_iterator�� ����� �� �ִ�. ���� ���� ���丮���� ��ȸ�ϰ� �ʹٸ� recursive_directory_iterator�� ����ϸ� �ȴ�.
5.	path��ü�� create_directory�Լ��� �־� ���丮�� ������ �� �ִ�. �ٸ� �����ϴ� ���丮�� �θ� ���丮�� �ݵ�� �����ؾ� �Ѵ�.
	���� �θ� ���丮���� �� ����� �ʹٸ� create_directories�Լ��� �������.
	fs::path p("./c/d/e/f");
	fs::create_directories(p); 
6.	������ �����ϰ� �ʹٸ� path��ü�� �ΰ�(���� ��ǥ) ����� fs::copy(from, to, fs::copy_options::recursive)�� ������ �����ϴ�.
	�̶�, �̹� ����� �����ϸ� throw�ϰ� �Ǵµ�, copy_options::skip_existing(����)& overwrite_existing(�����)& updata_existing(�����ȰŸ� �����)�ɼ����� �ذ��� �����ϴ�.
	fs::path from("./a/a.txt");
	fs::path to("./c");
	fs::copy(from, to, fs::copy_options::overwrite_existing);
7.	���Ŵ� �����ϰ��� �ϴ� ���� path��ü�� fs::remove�� ������ �ȴ�. �ٸ� �� ���丮�� ���Ű� �����ѵ�,
	������� ���� ���丮�� �����ϰ� ������ remove_all�� ����ϸ� �ȴ�. 
8.	directory_iterator ��� �� ���丮�� ������ �ٲ� �� ���� ��ȿȭ�Ǳ⿡ �Ź� ������ �ݺ��ڸ� �ʱ�ȭ����� �Ѵ�. 
 
*/

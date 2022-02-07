#include <iostream>

namespace C_std_library{
	//1. bug �����Ҵ� �������� ���� �ߴµ� �������� �����ϳ�. �ƴѰ�  realloc
	int max=1024;
	char* p=static_cast<char*>(malloc(max));
	char* current_word=nullptr;
	bool in_word=false;
	int i=0;
	while(cin.get(&p[i])){
		if(isletter(p[i])){
			if(!in_word)
				current_word=p;
			in_word=true;
		} else{
			in_word=false;
		}
		if(++i==max)
			p=static_cast<char*>(realloc(p, max*=2));//double allocation! WHY? realloc with non-primitive memory?
		//...
	}
}

namespace compatibility{
	//1. struct scope; difference with c & c++
	int x[99];
	void f(){
		struct x{ int a; };
		sizeof(x);//C������ �迭�� ũ��, C++������ ����ü�� ũ�� 
		sizeof(struct x);
	}
}

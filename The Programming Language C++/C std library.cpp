#include <iostream>

namespace C_std_library{
	//1. bug 더블할당 에러레서 뭐지 했는데 생각보다 간단하네. 아닌가  realloc
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
		sizeof(x);//C에서는 배열의 크기, C++에서는 구조체의 크기 
		sizeof(struct x);
	}
}

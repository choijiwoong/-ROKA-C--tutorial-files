#include <iostream>

/*
1.	C++은 Garbage Collector가 없어 직접 해제해주는게 중요하다. 하지만, 일반적인 객체를 throw시 소멸자를 호출하지만(stack unwindgin)
	포인터는 아무리 delete를 잘 해주었다고 해도 소멸자가 호출되지 않기에 memory leak을 피할 수 없다.
2.	RAII(Resource Acquisition Is Initialization) 자원관리를 스택에 할당한 객체를 통해 수행한다는 의미이다.
	즉, 소멸자가 호출되지 않는 포인터 형식 자체를 포인터 객체로 만들어서 이 소멸자에 자원을 해제하는 루틴을 넣는것이다.
	다른말로 RAII. 메모리 관리를 포인터 객체를 통해 수행하는 것이다. 이러한 것을 스마트 포인터라고 부른다. 
3.	C++에는 unique_ptr과 shared_ptr 두 가지의 스마트 포인터를 제공하여 메모리 누수를 막았다.
	그리고 double free버그는 포인터객체에 유일한 소유권을 보유하여 애초에 이 포인터 말고는 객체소멸이 불가하다 라고 하는 unique_ptr
	 unique_ptr복사 시 그 뭐시냐 생성자 인자에 unique_ptr꼴이 들어오면 =delete로 되는 오버로딩을 만들어 둬서 삭제된 함수를 사용할 수 없다는 오류 발생
	정상적으로 소유권을 이전하려면 std::move로 =assign해야 한다. 또한 소유권이 이전된 댕글링 포인터는 절대 참조하면 안된다. 
4.	.get()으로 포인터주소를 쌔빌 수 있는데, 함수 인자로 넣는다거나 할 때 이용하자.
5.	C++14부터
	std::unique_ptr<Foo> ptr(new Foo(3, 5)); 대신에
	auto ptr=std::make_unique<Foo>(3, 5);를 사용할 수 있다. 이를 사용하는 것이 더 좋은게 어쩌다보니 나오는 다중소유문제를 탐지할 수 있다. 
6.	unique_ptr는 복사 생성자가 없다 라는 특성으로 vector와 같은 컨테이너에 push_back으로 넣을 때 오류가 존나게 발생하는데,  
	vec.push_back(std::move(pa));처럼 명시적으로 이동시켜주거나, emplace_back을 이용하여 vector안에 직접 생성하는 경우도 있다.
	 emplace_back은 인자를 완벽한 전달(perfect forwarding)을 통해 불필요한 이동 연산을 없앤다. 
	다만 어떤 생성자가 호출되는지는 조심해야 한다. push_back과는 다소 차이가 있어 원치않는 생성자가 호출될 위험이 있다.
	 
	 
*/

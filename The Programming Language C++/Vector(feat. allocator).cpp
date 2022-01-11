#include <iostream>

template<typename For, typename T>
void uninitialized_fill(For beg, For end, const T& x){//for simplizing constructor
	For p;
	try{
		for(p=beg; p!=end; ++p)
			::new(static_cast<void*>(&*p)) T(x);//&*p manage itertor not element of pointer.
	} catch(...){//totally success ot totally fail! prevent half completed state.
		for(For q=beg; q!=p; ++q)//but this don't destroy element reversely with constructing.
			(&*q)->~T();
		throw;
	}
}

template <typename T, typename A=allocator<T>>
class vector{
	private:
		T* elem;//start of allocation(elements)
		T* space;//end of sequence of elements, start of new allocation(end of elements)
		T* last;//end of allocated space.(end of space)
		A alloc;//allocator of T
	
	public:
		using size_type=typename A::size_type;
		
		explicit vector(size_type n, const T& val=T(), const A&=A());//constructor with default arguments(to last)
		
		vector(const vector& a);//copy constructor
		vector& operator=(const vector& a);//copy assign
		
		vector(vector&& a);//move constructor
		vector& operatoe=(vector&& a);//move assign
		
		~vector();
		
		size_type size() const { return space-elem; }//pointer's diff?¤§¤§ 
		size_type capacity() const { return last-elem; }
		void reserve(size_type n);
		
		void resize(size_type n, const T&={});
		void push_back(const T&);
		//...
};

template<typename T, typename A>//not good version. allocate can throw memory exception, copy exception on val.
vector<T,A>::vector(size_type n, const T& val, const A& a):alloc{a}{
	elem=alloc.allocate(n);
	space=last=elem+n;
	
	for(T* p=elem; p!=last; ++p)
		a.construct(p, val);//make copy of val to *p
}

template<typename T, typename A>//safe version of previous version
vector<T, A>::vector(size_type n, const T& val, const A& a):alloc{a}{
	elem=alloc.allocate(n);
	iterator p;//***IMPORTANT*** for access iterator on catch not only try. prevention of auto destruct by scope.
	try{//same way
		iterator end=elem+n;
		for(p=elem; p!=end; ++p)
			alloc.construct(p, val);
		last=space=p;
		
		/* simple version by unitialized_fill()
		unitialized_fill(elem, elem+n, val);
		space=last=elem+n;
		*/
	} catch(...){//catch all exception
		for(iterator q=elem; q!=p; ++q)
			alloc.destroy(q);//destruct all elements.
		alloc.deallocate(elem, n);//deallocate all allocated elements
		throw;//rethrow current exception.
	}
}

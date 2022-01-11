#include <iostream>

//vector_base class that support vector class.
template<typename T, typename=A=allocator<T>>
struct vector_base{//RAII!
	A alloc;
	T* elem;
	T* space;
	T* last;
	
	vector_base(const A& a, typename A::size_type n, typename A::size_type m=0): alloc{a}, elem{alloc.allocate(n+m)}, space{elem+n}, last{elem+n+m}{}//element, allocate_size, last_location
	~vector_base(){ alloc.deallocate(elem, last-elem); }
	
	vector_base(const vector_base&)=delete;//no copy
	vector_base& operator=(const vector_base&)=delete;
	
	vector_base(vector_base&&);
	vector_base& operatoe=(vector_base&&);
};

template<typename T, typename A>
vector_base<T,A>::vector_base(vector_base&& a): alloc(a.alloc), elem{a.alloc}, space{a.space}, last{a.last}{
	a.elem=a.space=a.last=nullptr;
}

template<typename T, typename A>
vector_base<T,A>& vector_base<T,A>::operator=(vector_base&& a){
	swap(*this, a);
	return *this;
}

//vector class by using vector_base
template<typename T, typename A=allocator<T>>
class vector{
	private:
		vector_base<T,A> vb;//manage memory only!
		void destroy_elements();
	
	public:
		using size_type=typename A::size_type;
		
		explicit vector(size_type n, const T& val=T{}, const A& a=A{});
		
		vector(const vector& a);
		vector& operator=(const vector& a);
		
		vector(vector&& a);
		vector& operator=(vector&& a);
		~vector(){ destroy_elements(); }
		
		size_type size() const{ return vb.space-vb.elem; }
		size_type capacity() const{ return vb.last-vb.elem; }
		
		void reserve(size_type); 
		
		void resize(size_type, const T&={});
		void clear(){ resize(0); }
		void push_back(const T&);
		//...
};

template<typename T, typename A>
void vector<T,A>::destroy_elements(){//for destructor of vector
	for(T* p=vb.elem; p!=vb.space; ++p)
		p->~T();//explicitly calling destructor. IT MEANS IF EXCEPTION OCCUR IN DESTRUCTOR, WE FAIL TO REMOVE VECTOR. if then, terminate() will be called. 
	vb.space=sb.elem;
}

template<typename T, typename A>
vector<T,A>::vector(const vector<T,A>& a): vb{a.vb.alloc, a.size()}{//simple constructor
	//uninitialized_copy(a.begin(), a.end(), vb.elem);
	uninitialized_copy(a.begin(), a.end(), vb.elem);
	//we can use this style of constructor thanks to basic language rule that 'complete derived object can be removed properly'
}

template<typename T, typename A>
vector<T,A>::vector(vector&& a):vb{move(a.vb)}{}//simple move constructor

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(vector&& a){//simple move operation
	clear;
	swap(vb, a.vb);
	return *this;
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a){//not good version
	vector_base<T,A> b{a.vb.alloc, a.size()};//get memory
	unitilized_copy(a.begin(), a.end(), b.elem);//copy element
	destroy_elements();//remove previous element
	swap(vb, b);//move ownership
	return *this;//remove previous value implicitly (b, vb's swap. previous data is in b now, but b is local variable so it will be removed by escaping scope.)
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a){//simple version
	vector temp{a};
	swap(*this, temp);
	return *this;//implicitly remove previous data.
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a){//optimizing version_enough space_no allocation & assign than constructing after destructing
	if(capacity()<a.size()){
		vector temp{a};
		swap(*this, temp);
		return *this;
	}
	
	if(this==&a)//self assign
		return *this;
	
	size_type sz=size();
	size_type asz=a.size();
	vb.alloc=a.vb.alloc;//copy allocator
	if(asz<=sz){//remove remain elemets(allocate size <= size)
		copy(a.begin(), a.begin()+asz, vb.elem);
		for(T* p=vb.elem+asz; p!=vb.space; ++p)
			p->~T();
	} else{//make new elements(allocate size > size)
		copy(a.begin(), a.begin()+sz, vb.elem);//copy initialized data
		uninitialized_copy(a.begin()+sz, a.end(), vb.space);//copy uninitialized data
	}
	vb.space=vb.elem+asz;//set
	return *this;
}

template<typename T, typename A>
void safe_assign(vector<T,A>& a, vector<T,A> b){//assign by pointer
	vector<T,A> temp{b};
	swap(a, temp);//for pointer
}
template <typename T, typename A>
void safe_assign(vector<T,A>&a, vector<T,A> b){ //assign by value
	swap(a,b); 
}

template<typename T, typename A>
void vector<T,A>::reverse(size_type newalloc){//not good! has flaw; no default value on all elements, it initializes space for additional space
	if(newalloc<=capacity())
		return;
	vector<T,A> v(newalloc);//make new vector
	copy(vb.elem, vb.elem+size(), v.begin());//copy initial data without initialization of left data
	vb.space=size();
	swap(*this, v);
}

template<typename T, typanem A>
void vector<T,A>::reserve(size_type newalloc){//optimized version of reserve();
	if(newalloc<=capacity())
		return;
	vector_base<T,A> b{vb.alloc, size(), newalloc-size()};//partly allocation by vector_base
	uninitialized_move(vb.elem, vb.elem+size(), b.elem);//move to initial on b.elem. add vb's elements to b.
	swap(vb, b);//나중에 보면 이 부분이 이해가 안될거같아서 한글로쓰면 vector_base로 예약된 공간을 가지는 객체생성, uninitialized_move로 해당 공간에 기존 요소 이동 후 swap. uninitialized_move를 쓰는이유는 단순히 b가 초기화되지 않은 메모리기에. 
}//remove previous value implicitly

template<typename In, typename Out>
Out uninitialized_move(In b, In e, Out oo){
	using T=Value_type<Out>;
	for(; b!=e; ++b,++oo){
		new(static_cast<void*>(&*oo)) T{move(*b)};//&* means iterator. allocate on oo's iterator by b's type
		b->~T();//destroy for preventing memory leak
	}
	return oo;
}


template<typename In>
void destroy(In b, In e){
	for(; b!=e; ++b)//[b:e)
		b->~Value_type<In>();//suppose destructor.. Every standard iterator has value_type
}
template<typename T, typename A>
void vector<T,A>::resize(size_type newsize, cosnt T& val){
	reserve(newsize);//if small than newsize, it doesn't do any work(just return;). so it's safe
	if(size()<newsize)
		uninitialized_fill(vb.elem+size(), vb.elem+newsize, val);
	else//if new size is smaller than initial size
		destroy(vb.elem+newsize, vb.elem+size());//destroy over element partly
	vb.space=vb.elem+newsize;//setting
}

template<class T, typename A>
void vector<T,A>::push_back(const T& val){
	if(capacity()==size())
		reserve(size()?2*size():8);//for efficiency. (1.618 is best rate on enough allocation mathmetically proved)
	vb.alloc.construct(&vb.elem[size()], val);//add to last
	++vb.space;//setting
}

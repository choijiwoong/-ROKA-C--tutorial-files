#include <iostream>

namespace Unique_ptr{
	//1. define make_unique self
	template<typename T, typename... Args>
	unique_ptr<T> make_unique(Args&&... args){
		return unique_ptr<T>{new T(args...)};
	}//use: auto unique=make_unique(variable)
}


namespace Allocator{
	//1. unusual constructor & destructor that handle memory directly; allocator
	template<typename T>
	struct Simple_alloc{
		using value_type=T;
		Simple_alloc(){}
		T* allocate(size_t n){ return reinterpret_cast<T*>(new char[n*sizeof(T)]); }//return allocated memory
		void deallocate(T* p, size_t n){ delete[] reinterpret_cast<char*>(p); }//delete after casting memory
		//...
	};
	
	//2. default allocator_by new & delete in std
	template<typename T>
	class allocator{
		public:
			using size_type=size_t;
			using difference_type=ptrdiff_t;
			using pointer=T*;
			using const_pointer=const T*;
			using reference=T&;
			using const_reference=const T&;
			using value_type=T;
			
			template<typename U>
				struct rebind{ using other=allocator<U>; };
			//template<typename T>
			//using other=allocator<U>;
			
			allocator() noexcept;
			allocator(const allocator&) noexcept;
			template<typename U>
				allocator(const allocator<U>&) noexcept;
			~allocator();
			
			pointer address(reference x) const noexcept;
			const_pointer address(const_reference x) const noexcept;
			pointer allocate(size_type n, allocator<void>::const_pointer hint=0);//n x T
			void deallocate(pointer p, size_type n);//n X T
			
			size_type max_size() const noexcept;
			template<typename U, typename... Args>
				void construct(U* p, Args&&... args);//new(p) U{args}
			template<typename U>
				void destroy(U* p);//p->~U()
	};
	template<>//specialization for void
	class allocator<void>{
		public:
			using pointer=void*;
			using const_pointer=const void*;
			using value_type=void;
			template<typename U> struct rebind{
				using other=allocator<U>;
			};
	};
	
	//3. allocator_traits
	template<typename A>
	struct allocator_traits{
		using allocator_type=A;
		using value_type=typename A::value_type;
		using pointer=value_type*;//use default value all.
		using const_pointer=Pointer_traits<pointer>::rebind<const value_type>;//
		using void_pointer=Pointer_traits<pointer>::rebind<void>;//
		using const_void_pointer=Pointer_traits<pointer>::rebind<const void>;//
		using difference_type=Pointer_traits<pointer>::difference_type;//
		using size_type=Make_unsigned<difference_type>;//
		using propagate_on_container_copy_assignment=false_type;//
		using propagate_on_container_move_assignment=false_type;//
		using propagate_on_container_swap=false_type;//
		
		template<typename T> using rebind_alloc=A<T, Args>;//
		template<typename T> using rebind_traits=Allocatoe_traits<rebind_alloc<T>>;//
		static pointer allocate(A& a, size_type n){ return a.allocate(n); }//
		static pointer allocate(A& a, size_type n, const_void_pointer hint){ return a.allocate(n, hint); }//
		static void deallocate(A& a, pointer p, size_type n){ a.deallocate(p,n); }//
		template<typename T, typename... Args>
			static void construct(A& a, T* p, Args&&... args){
				::new (static_cast<void*>(p) T(std::forward<Args>(args)...); )//
			}
		template<typename T>
			static void destroy(A& a, T* p){ p->~T(); }//
		static size_type max_size(const A& a){ return numeric_limits<size_type>::max() }//
		static A select_on_container_copy_construction(cosnt A& rhs){ return a; }//
	};
	
	template<typename P>//proxy
	struct Pointer_traits{
		using pointer=P;
		using element_type=T;
		using diference_type=ptrdiff_t;
		template<typename U>
			using rebind=T*;
		static pointer pointer_to(a);
	};
	template<typename T>//real
	struct pointer_traits<T*>{
		using pointer=T*;
		using element_type=T;
		using difference_type=ptrdiff_t;
		template<typename U>
			using rebind=U*;
		static pointer pointer_to(x) noexcept{ return addressof(x); }
	};
	
	//4. scoped_allocator_adapter class for use one more allocator on container(container's allocator, element's allcator)
	template<typename OuterA, typename... InnerA>
	class scoped_allocator_adaptor: public OuterA{//inherite Outer Allocator
		private:
			using Tr=allocator_traits<OuterA>
		public:
			using outer_allocator_type=OuterA;
			using inner_allocator_type=;//manage seperatly
			using value_type=typename Tr::value_type;
			using size_type=typename Tr::size_type;
			using difference_type=typename Tr::difference_type;
			using pointer=typename Tr::pointer;
			using const_pointer=typename Tr::const_pointer;
			using void_pointer=typename Tr::void_pointer;
			using const_void_pointer=typename Tr::const_void_pointer;
			using propagate_on_container_copy_assignment=;//manage seperatly
			using propagate_on_container_move_assignment=;//manage seperatly
			using propagate_on_container_swap;//manage seperatly
	};
	void case_4_example_of_vector_by_string(){
		using Svec0=vector<string>;
		Svec0 v0;//both use each default allocator
		
		using Svec1=vector<string, My_alloc<string>>;
		Svec1 v2{My_alloc<string>{my_arena1}};//vector use My_alloc, string use defualt allocator
		
		using Xstring=basic_string<char, char_traits<char>, My_alloc<char>>;
		using Svec2=vector<Xstring, scoped_allocator_adaptor<My_alloc<Xstring>>;
		Svec2 v2{scoped_allocator_adaptor<My_alloc<Xstring>>{my_arena1}};//both use My_alloc
		
		using Xstring2=basic_string<char, char_traits<char>, My_alloc<char>>;
		using Svec3=vector<xstring2, scoped_allocator_adaptor<My_alloc<xstring>, My_alloc<char>>>;
		Svec3 v3{scoped_allocator_adaptor<My_alloc<xstring2>, My_alloc<char>>{my_arena1}};//vector use default allocator, string use My_alloc
	}
}

namespace GC{
	//1. example of disguised pointer
	struct Link{ int value; Link* link; };
	Link* xor2(Link* pre, Link* suc){
		static_assert(sizeof(Link*)<=sizeof(long), "a long is smaller than a pointer");
		return reinterpret_cast<Link*>(reinterpret_cast<long>(pre)^reinterpret_cast<long>(suc));//xor for zip
	}
	void insert_between(Value val, Link* pre, Link* suc){
		Link* p=new Link{val, xor2(pre, suc)};
		pre->link=xor2(xor2(pre->link, suc), p);
		suc->link=xor2(p, xor2(suc->link, pre));
	}
	
	//2. GC ABI
	void declare_reachable(void* p);//object that p is pointing doesn't collected
	template<typename T>
		T* undeclare_reachable(T* p);//cancel execution of declare_reachable()
	
	void declare_no_pointers(char* p, size_t n);//p[0:n) don't save pointer
	void undeclare_no_pointers(char* p, size_t n);//cancel execution of declare_no_pointers()
	
	enum classs pointer_safety{relaces, preferred, strict};//collect all without safe pointer & traceable, as detector of leak, ignore unsafety pointers
	pointer_safety get_pointer_safety();
	
	//3. uninitialized memory for using it on std container(that supposes member is already initializd)
	template<typename T>
		pair<T* ptrdiff_t> get_temporary_buffer(ptrdiff_t);
	template<typename T>
		void return_temporary_buffer(T*);
	
	template<typename Out, typename T>
	class raw_storage_iterator: public iterator<output_iterator_tag, void, void, void, void>{//just for initialization not assign & copy
		Out p;
		
		public:
			explicit raw_storage_iterator(Out pp): p{pp}{}
			raw_storage_iterator& operator*(){ return *this; }
			raw_storage_iterator& operator=(const T& val){
				new(&*p) T{val};
				return *this;
			}
			raw_storage_iterator& operator++(){ ++p; return *this; }
			raw_storage_iterator operator++(int){
				auto t=*this;
				++p;
				return t;
			}
			//we don't have != or == operation! warning.
	};
	void user(){
		auto pp=get_temporary_buffer<string>(1000);//get uninitialized space
		if(pp.second<1000){
			//...handle fail
		}
		
		auto p=raw_storage_iterator<string*, string>(pp.first);//make temporary buffer's iterator
		generate_n(p, pp.second, [&]{next_permutation(seed, seed+sizeof(seed)-1); return seed; });
		//...
		return_temporary_buffer(pp.first);
	}
}

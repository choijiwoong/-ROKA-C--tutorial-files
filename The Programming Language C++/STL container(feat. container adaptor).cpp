#include <iostream>

//All container define set of member type
namespace member_example{
	template<typename Key, typename T, typename Compare=less<Key>, typename Allocatoe=allocator<pair<const Key, T>>>
	class map{
		public:
			using key_type=Key;
			using mapped_type=T;
			using value_type=pair<const Key, T>
			using key_compare=Compare;
			using allocator_type=Allocator;
			using reference=value_type&;
			using const_reference=const value_type&;
			using iterator=;//Definition by implementation
			using const_iterator=;//Definition by implementation
			using size_type=;//Definition by implementation
			using difference_type=;//Definition by implementation
			using pointer=typename allocator_traits<Allocator>::pointer;
			using const_pointer=typename allocator_traits<Allocator>::const_pointer;
			using reverse_iterator=std::reverse_iterator<iterator>;
			class value_compare{};//operator()(k1,k2) works key_comare()(k1,k2)
			//...
	};
	
	template<typename Key, typename T, typename Hash=hash<Key>, typename Hash=hash<Key>, typename Pred=equal_to<Key>, typename Allocator=allocator<pair<const Key, T>>>
	class unordered_map{
		public:
			using key_type=Key;
			using value_type=pair<const Key, T>
			using mapped_type=T;
			using hasher=Hash;
			using key_equal=Pred;
			using allocator_type=Allocator;
			using pointer=typename allocator_traits<Allocator>::pointer;
			using const_pointer=typename alocator_traits<Allocator>::const_pointer;
			using reference=value_type&;
			using const_reference=const value_type&;
			using size_type=;//Definition by implementation
			using difference_type=;//Definition by implementation
			using iterator=;//Definition by implementation
			using const_iterator=;//Definition by implementation
			using local_iterator=;//Definition by implementation
			using const_local_iterator=;//Definition by implementation
			//...
	};
	
}

namespace container_adaptor{
	template<typename T, typename C=deque<T>>
	class stack{
		public:
			using value_type=typename C::value_type;
			using reference=typename C::reference;
			using const_reference=typename C::const_reference;
			using size_type=typename C::size_type;
			using container_type=C;
			
		public:
			explicit stack(const C&);//copy
			explicit stack(C&&=C{});//move
			
			template<typename A>
				explicit stack(const A& a);
			template<typename A>
				stack(const C& c, const A& a);
			template<typename A>
				stack(C&&, const A&);
			template<typename A>
				stack(const stack&, const A&);
			template<typename A>
				stack(stack&&, const A&);
				
			bool empty() const{ return c.empty(); }
			size_type size() const{ return c.size(); }
			reference top(){ return c.back(); }
			const_reference top() const{ return c.back(); }
			 void push(const value_type& x){ c.push_back(x); }//additional operatrions. and remove needless operations
			 void push(value_type&& x){ c.push_back(std::move(x)); }
			 void pop(){ c.pop_back(); }
			template<typename... Args>
			void emplace(Args&&... args){
				c.emplace_back(std::forward<Args>(args)...);
			}
			void swap(stack& s) noexcept(noexcept(swap(c,s.c))){
				using std::swap;
				swap(c, s.c);
			}
			
		protected:
			C c;
	};
}

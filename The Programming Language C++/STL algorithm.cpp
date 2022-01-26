#include <iostream>

#include <algorithm>
#include <type_traits>

#include <iterator>

namespace STL_algorithm{
	using namespace std;
	//structure of mismatch that is used in standard STL algorithm commonly. example) pair(p1,p2)=mismatch(b,e,b2)	or	pair(p1,p2)=mismatch(b,e,b2,f)
	template<typename In, typename In2, typename Pred=equal_to<Value_type<In>>>
	pair<In, In2> mismatch(In first, In last, In2 first2, Pred p={}){
		while(first!=last && p(*first,*first2)){
			++first;
			++first2;
		}
		return {first, first2};
	}
	
	//remove's mechanism. move removed element to end of that container
	string s{"*CamelCase*IsUgly*"};
	cout<<s<<'\n';//*CamelCass*IsUgly*
	auto p=remove(s.begin(), s.end(), '*');
	copy(s.begin(), p, ostream_iterator<char>{cout});//CamelCaseIsUgly
	cout<<s<<'\n';//CamelCaseIsUglyly*
	
	//example of permutation
	vector<char> v{'a','b', 'c'};
	while(next_permutation(v.begin(), v.end()))
		cout<<v[0]<<v[1]<<v[2]<<' ';
	cout<<'\n';
	
	//example of fill, generate
	int v1[900];
	array<int, 900> v2;
	vector<int> v3;
	void f(){
		fill(begin(v1), end(v1), 99);
		generate(begin(v2), end(v2), Rand_int{500,1500});
		generate_n(ostream_iterator<int>{cout,'\n'}, 200, Rand_int{0,100});
		fill_n(back_inserter(v3), 20, 99);
	}
	
	//structure of lexicographical_compare(). tule for dictionaric sort
	template<typename In, typename In2>
	bool lexicographical_compare(In first, In last, In2 first2, In2 last2){
		for(; first!=last&&first2!=last2; ++first, ++first2){
			if(*first<*first2)
				return true;
			if(*first2<*first)
				return false;
		}
		return first==last && first2!=last2;
	}
}

namespace STL_iterator{
	//0. How to use iterator_tag one of iteator_traits
	template<typename Iter>
	void advance_helper(Iter& p, int n, random_iterator_tag){ p+=n; }//get property of random-iterator
	template<typename Iter>
	void advance_helper(Iter& p, int n, bidirectional_iteator_tag){
		if(0<n)
			while(n--) ++p;
		else if(n<0)
			while(n++) --p;
	}
	template<typename Iter>
	void advance(Iter& p, int n){
		advance_helper(p, n, typename iterator_traits<Iter>::iterator_category());//input category of template argument's iterator for using overloading per tag; iterator_traits
	}//Its will be inlined by tag dispatch technique.
	
	//1. Structure of iterator_traits
	template<typename Iter>
	struct iterator_traits{
		using valye_type=typename Iter::value_type;
		using difference_type=typename Iter::difference_type;
		using pointer=typename Iter::pointer;
		using reference=typename Iter::reference;
		using iterator_category=typename Iter::iterator_category;
	};
	template<typename T>
	struct iterator_traits<T*>{//specialization about pointer
		using difference_type=ptrdiff_t;
		using value_type=T;
		using pointer=T*;
		using reference=T&;
		using iterator_category=random_access_iteator_tag;
	};
	
	//2. Structure of iterator template
	template<typename Cat, typename T, typename Dist=ptrdiff_t, typename Ptr=T*, typename Ref=T&>
	struct iterator{
		using value_type=T;
		using difference_type=Dist;
		using pointer=Ptr;
		using reference=Ref;
		using iterator_category=Cat;
	};
	
	//3. structure of reverse_iterator that is one of example of iterator adaptors. WE HAVE TO CONSIDER IT'S REVERSE!!!!
	template<typename Iter>
	class reverse_iterator: public iterator<Iterator_category<Iter>, 
											Value_type<Iter>,
											Difference_type<Iter>,
											Pointer<Iter>,
											Reference<Iter>>{
		public:
			using iterator_type=Iter;
			
			reverse_iterator(): current{}{}//constrtuctor
			explicit reverse_iterator(Iter p): current{p}{}
			template<typename Iter2>
				reverse_iterator(const reverse_iterator<Iter2>& p): current(p.base()){}
			
			Iter base() const { return current; }
			
			reference operator*() const { tmp=current; return *--tmp; }
			pointer operator->() const;
			reference operator[] (difference_type n) const;
			
			reverse_iterator& operator++() { --current; return *this; }
			reverse_iterator operator++(int){ reverse_iterator t=current; --current; return t; }
			reverse_iterator& operator--(){ ++current; return *this; }
			reverse_iterator operator--(int){ reverse_iterator t=current; ++current; return t; }
			
			reverse_iterator operator+(difference_type n) const;
			reverse_iterator& operator+=(difference_type n);
			reverse_iterator operator-(difference_type n) const;
			reverse_iterator& operator-=(difference_type n);
			//...
		
		protected:
			Iter current;
		
		private:
			//...
			iter tmp;
	}
	template<typename C, typename Val>
	auto find_last(C& c, Val v)->decltype(c.begin()){
		for(auto p=c.end(); p!=v.begin();)
			if(*--p==v)
				return p;
		return c.end();
	}
}

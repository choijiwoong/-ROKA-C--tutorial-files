#include <iostream>

namespace {
	//1. structure of char_traits<char>
	template<>
	struct char_traits<char>{
		using char_tpe=char;
		using int_type=int;
		using off_type=streamoff;
		using pos_type=streampos;
		using state_type=mbstate_t;
		//...
	};
	
	//2. structure of basic_string
	template<typename C, typename Tr=char_traits<C>, typename A=allocator<C>>
	class basic_string{
		public:
			using traits_type=Tr;
			using value_type=typename Tr::char_type;
			using allocator_type=A;
			using size_type=typename allocator_traits<A>::size_type;
			using difference_type=typename allocator_traits<A>::difference_type;
			using reference=value_type&;
			using const_reference=const value_type&;
			using pointer=typename allocator_traits<A>::pointer;
			using const_pointer=typename allocator_traits<A>::const_pointer;
			using iterator=;//seperatly defined
			using const_iterator=;
			using reverse_iterator=;
			using const_reverse_iterator=;
			static const size_type npos=-1;//end of string
			//...
	};
	
	//3. getline() of string
	vector<string> lines;
	for(string s; getline(cin,s);)
		lines.push_back(s);
		
	//4. replace() return reference for using sequencely
	string s="but I have heard it works even if you don't believe in it";
	s.replace(0,4,"").replace(s.find("even"),4,"only").replace(s.find(" don't"), 6, "");//use replace sequencely!
	assert(s=="I have heard it works only if you believe in it");
}

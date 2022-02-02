#include <iostream>
#include <regex>

namespace {
	//1. simple example of regex
	void sue(){
		ifstream in("file.txt");//file open
		 if(!in) cerr<<"no file\n";
		regex pat{R"(\w{2}\s*\d{5}(-\d{4})?)"};//make regex(american address pattern)
		int lineno=0;
		
		for(string line; getline(in,line);){//get line by file input stream
			++lineno;
			smatch matches;//for saving matched string
			if(regex_search(line, matches, pat)){
				cout<<lineno<<": "<<matches[0]<<'\n';//all pattern(complete match)
				if(1<matches.size() && matches[1].matched)//print \t for convenience_ sub match(partitial match)
					cout<<"\t: "<<matches[1]<<'\n';
			}
		}
	}
	
	//2. regex char class short
	[[:alpha:]_][[:alnum:]_]*//_ on char class OK
	[_[:alpha:]][_[:alnum:]]*//OK
	[_[:alpha:]]\w*//\w is same with [_[:alnum:]]
	
	bool is_identifier(const string& s){
		regex pat{"[_[:alpha:]]\\w*"};
		return regex_match(s, pat);
	}
	
	//3. we can parse XML by <(.*?)>(.*?)</\1>
	Always look on the <b>bright</b> side of <b>life</b>
	//하짐나 이 경우엔 첫 부분패턴에 대해서 greedy match는 잘 동작하지만, 두 번째 기준으로는 bright~life까지를 parsing할것이기에 주의하자. 
	
	//4. regex structure
	template<typename C, typename Tr=regex_traits<C>>//string, pointer...etc
	class basic_regex{
		public:
			using value_type=C;
			using traits_type=Tr;
			using string_type=typename Tr::string_type;
			using flag_type=regex_constants::syntax_option_type;
			using locale_type=typename Tr::locale_type;
			~basic_regex();
			//...
	};
	
	//5. match result save one more sub_match object.
	template<typename Bi>//Bidirectional Iterator
	class sub_match: public pair<Bi, Bi>{
		public:
			using value_type=typename iterator_traits<Bi>::value_type;
			using difference_type=typename iterator_traits<Bi>::difference_type;
			using iterator=Bi;
			using string_type=basic_string<value_type>;
			bool matched;
			//...
	};
	
	template<typename Bi, typename A=allocator<sub_match<Bi>>>
	class match_results{
		public:
			using value_type=sub_match<Bi>;
			using const_reference=const value_type&;
			using reference=const_reference;
			using const_iterator=;//seperately defined
			using iterator=const_iterator;
			using difference_type=typename iterator_traits<Bi>::difference_type;
			using size_type=typename allocator_tarits<A>::size_type;
			using allocator_type=A;
			using char_type=typename iterator_traits<Bi>::value_type;
			using string_type=basic_string<char_type>;
			~match_results();//non-virtual
			//...
	};
	
	//6. complex example of regex by match()
	ifstream in ("table.txt");
	 if(!in) cerr<<"no file\n";
	
	string line;
	int lineno=0;
	
	regex header{R"(^[\w]+(\t[\w]+)*$)"};//header's pattern
	regex row{R"(^([\w]+)(\t\d+)(\t\d+)(\t\d+)$)"};
	
	if(getline(in,line)){
		smatch matches;
		if(!regex_match(line, matches, header))//regex_match to header first
			cerr<"no header\n";
	}
	
	int boys=0;
	int girls=0;
	while(getline(in,line)){
		++lineno;
		smatch matches;
		
		if(!regex_match(line, matches, row))//check row
			cerr<<"bad line: "<<lineno<<'\n';
		
		int curr_boy=stoi(matches[2]);
		int curr_girl1=stoi(matches[3]);
		int curr_total=stoi(matches[4]);
		if(curr_boy+curr_girl!=curr_total) cerr<<"bad row sum\n";
		
		if(matches[1]=="Total"){
			if(curr_boy!=boys) cerr<<"boys do not add up\n";
			else if(curr_girl!=girls) cerr<<"girls do not add up\n";
			else cout<<"all is well\n";
			return 0;
		}
		boys+=curr_boy;
		girls+=curr_girl;
	}
	cerr<<"didn't find total line\n";
	return 1;
	
	//7. structure of regex_iterator
	template<typename Bi, class C=typename iterator_traits<Bi>::value_type, class Tr=typename regex_traits<C>::type>//Bi, Bi's value_type, regex_type
	class regex_iterator{
		public:
			using regex_type=basic_regex<C,Tr>;
			using value_type=match_results<Bi>;
			using difference_type=ptrdiff_t;
			using pointer=const value_type*;
			using reference=const value_type&;
			using iterator_category=forward_iterator_tag;
			//...
	};
	//regex_token_iterator; adaptor of regex_iterator
	template<typename Bi, class C=typename iterator_traits<Bi>::value_type, class Tr=typename regex_traits<C>::type>
	class regex_token_iterator{
		public:
			using regex_type=basic_regex<C, Tr>;
			using value_type=sub_match<Bi>;
			using difference_type=ptrdiff_t;
			using pointer=const value_type*;
			using reference=const value_type&;
			using iterator_category=forward_iterator_tag;
			//...
	};
	//use
	void use(){
		string input{"aa::bb cc::dd ee::ff"};
		regex pat{R"((\w+)([[:punct:]]+)(\w+)\s*)"};
		sregex_token_iterator end{};
		for(sregex_token_iterator p{input.begin(), input.end(), pat, {1,3}}; p!=end; ++p)//iterator for 1,2,3 group
			cout<<*p<<'\n';
	}
	//regex_traits
	template<typename C>
	struct regex_traits{
		public:
			using char_type=C;
			using string_type=basic_string<char_type>;
			using lcoal_type=locale;
			using char_class_type=;//bitmask type seperatly defined
			//...
	};
}

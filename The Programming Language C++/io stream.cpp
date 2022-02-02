#include <iostream>

namespace io{
	//1. structure of basic_iostream
	template<typename C, typename Tr=char_traits<C>>
	class basic_iostream: public basic_istream<C,Tr>, public basic_ostream<C,Tr>{
		public:
			using char_type=C;
			using int_type=typename Tr::int_type;
			using pos_type=typename Tr::pos_type;
			using off_type=typename Tr::off_type;
			using traits_type=Tr;
			explicit basic_iostream(basic_streambuf<C,Tr>* sb);
			virtual ~basic_iostream();
		protected:
			basic_iostream(const basic_iostream& rhs)=delete;
			basic_iostream(basic_iostream&& rhs);
			basic_iostream& operator=(const basic_iostream& rhs)=delete;
			basic_iostream& operator=(basic_iostream&& rhs);
			void swap(basic_iostream& rhs);
	};
	
	//2. file stream
	template<typename C, typename Tr=char_traits<C>>
	class basic_fstream: public basic_iostream<C,Tr>{
		public:
			using char_type=C;
			using int_type=typename Tr::int_type;
			using pos_type=typename Tr::pos_type;//location in file
			using off_type=typename Tr::off_type;//offset
			using traits_type=Tr;
			//...
	};
	
	//3. string stream
	template<typename C, typename Tr=char_traits<C>, typename A=allocator<C>>
	class basic_stringstream: public basic_iostream<C, Tr>{
		public:
			using char_type=C;
			using int_type=typename Tr::int_type;
			using pos_type=typename Tr::pos_type;
			using off_type=typename Tr::off_type;
			using traits_type=Tr;
			using allocator_type=A;
			//...
	};
	
	//4. exception with exceptions() as stream state(good, eof, fail, bad)
	struct Io_guard{
		iostream& s;
		auto old_e=s.exceptions();
		Io_guard(iostream& ss, ios_base::iostate e): s{ss}{
			s.exceptions(s.exceptions()|e);
		}
		~Io_guard(){ s.exceptions(old_e); }
	};
	void use(istream& is){
		Io_guard guard(is.ios_base::badbit);
		//use is(if badbit, throw!)
	} catch(ios_base::badbit){
		//escape
	}
	
	//5. input operation
	template<typename C, typename Tr=char_traits<C>>
	class basic_istream: virtual public basic_ios<C,Tr>{
		public:
			using char_type=C;
			using int_type=typename Tr::int_type;
			using pos_type=typename Tr::pos_type;
			using off_type=typename Tr::off_type;
			using traits_type=Tr;
			explicit basic_istream(basic_streambuf<C,Tr>* sb);
			virtual ~basic_istream();//deallocate all resource
			class sentry;
			//...
		protected:
			//move only without copy because basic_ios doesn't provide copy operation also.
			basic_istream(const basic_istream& rhs)=delete;
			basic_istream(basic_istream&& rhs);
			basic_istream& operator=(const basic_istream& rhs)=delete;
			basic_istream& operator=(basic_istream&& rhs);
			//...
	};
	//example of using sentry
	template<typename C, typename Tr=char_traits<C>>
	basic_ostream<C,Tr>& basic_ostream<C,Tr>::operator<<(int i){
		sentry s{*this};
		if(!s){
			setstate(failbit);
			return *this;
		}
		//print int
		return *this;
	}//sentry delete! flush!
	
	//6. output operation_output stream
	template<typename C, typename Tr=char_traits<C>>
	class basic_ostream: virtual public basic_ios<C, Tr>{
		public:
			using char_type=C;
			using int_type=typaname Tr::int_type;
			using pos_type=typename Tr::pos_type;
			using off_type=typename Tr::off_type;
			using traits_type=Tr;
			explicit basic_ostream(basic_streambuf<char_type, Tr>* sb);
			virtual _basic_ostream();
			class sentry;
			//...
			
		protected:
			//move only not copy also
			basic_ostream(const basic_ostream& rhs)=delete;
			basic_ostream(basic_ostream&& rhs);
			basic_ostream& operator=(const basic_ostream& rhs)=delete;
			basic_ostream& operator=(basic_ostream& rhs);
			//...
	};
	
	//7. virtual print function by double dispatch; overcome limit of ostream!
	class My_base{
		public:
			//...
			virtual ostream& put(ostream& s) cosnt=0;
	};
	ostream& operator<<(ostream& s, const My_base& r){//when we use this
		return r.put(s);//use proper put()
	}
	//double dispatch
	class Sometype: public My_base{
		public:
			//...
			ostream& put(ostream& s) const override;//real print function
	};
	void f(const My_base& r, Sometype& s){//use << that call proper put(). choose put() in runtime by second argument.
		cout<<r<<s;
	}
	
	//8. ios_base (that defines almost interface of stream class. it saves information that is independent on template argument)
	template<typename C, typename Tr=char_traits<C>>
	class basic_ios: public ios_base{
		public:
			using char_type=C;
			using int_type=typename Tr::int_type;
			using pos_type=typename Tr::pos_type;
			using off_type=typename Tr::off_type;
			using traits_type=Tr;
			//...
	};
	
	class ios_base{
		public:
			using fmtflags=;//seperately defined_bitmask type!
			using iostate=;//seperately defined
			using openmode=;//seperately defined
			using seekdir=;//seperately defined
			
			class failure;//예제 클래스 
			class Init;//표준 iostream을 초기화 라고 하네.. 뭔소리지 
	};
	
	//9. example of modify ios_base's iostate member by openmode member
	template<typename T>
	char* as_bytes(T& i){
		return static_cast<char*>(&i);
	}
	void test(){
		ifstream ifs("source", ios_base::binary);//use as binary
		ofstream ofs("target", ios_base::binary);
		vector<int> v;
		
		for(int i; ifs.read(as_bytes(i), sizeof(i)); )//read storage of i and save to vector?
			v.push_back(i);
		//do something by v
		for(auto i: v)
			ofs.write(as_bytes(i), sizeof(i));
	}
	
	//10. necessity of tie() of basic_ios
	cout<<"Please enter a number: ";
	int num;
	cin>>num;
	//tie()없이는 우리가 cout에 명시적으로 flush하지 않았기에 cout이 cin과 연결되어있지 않다면 사용자는 입력요청을 보지 못하게 된다. 

	//11. event & event_callback type in ios_base; use it with register_callback() that is used for notifying something to user when stream's state is changed.
	enum event{
		erase_event,
		imbue_event,
		copyfmt_event
	};
	using event_callback=void (*)(event, ios_base&, int index);
	
	//12. user designed manupulator
	
}

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
	
	//12. user designed manupulator_something for printing double number as defined format without effect to stream
	class Form;
	struct Bound_form{
		const Form& f;
		double val;
	};
	
	class Form{
		friend ostream& operator<<(ostream&, const Bound_form&);
		int prc, wdt, fmt;
		
		public:
			explicit Form(int p=6, ios_base::fmtflags f=0, int w=0): prc{p}, fmt{f}, wdt{w}{}//precision, fotmat, width
			Bound_form Form::operator()(double d) const{
				return Bound_form{*this, d};
			}
			Form& scientific(){//setting formats
				fmt=ios_base::scientific; 
				return *this;
			}
			Form& fixed(){
				fmt=ios_base::fixed;
				return *this;
			}
			Form& general(){
				fmt=0;
				return *this;
			}
			Form& uppercase();
			Form& lowercase();
			Form& precision(int p){//setting private
				prc=p;
				return *this;
			}
			Form& width(int w){
				wdt=w;
				return *this;
			}
			Form& fill(char);
			Form& plus(bool b=true);
			Form& trailing_zeros(bool b=true);
			//...
	};
	
	ostream& operator<<(ostream& os, const Bound_form& bf){
		ostringstream s;
		s.precision(bf.f.prc);//access private member thanks to friend
		s.setf(bf.f.fmt, ios_base::floatfield);
		s<<bf.val;
		//set output string stream by bf
		return os<<s.str();//return str to os
	}
	
	//13. stream iterator
	template<typename T, typename C=char, typename Tr=char_traits<C>, typename Distance=ptrdiff_t>
	class istream_iterator: public iterator<input_iterator_tag, T, Distance const T*, const T&>{
		using char_type=C;
		using traits_type=Tr;
		using istream_type=basic_istream<C,Tr>;
		//...
	};
	
	template<typename T, typename C=char, typename Tr=char_traits<C>>
	class ostream_iterator: public iterator<output_iterator_tag, void, void, void, void>{
		using char_type=C;
		using traits_type=Tr;
		using ostream_type=basic_ostream<C,Tr>;
		//...
	};
	//use
	copy(istream_iterator<double>{cin}, istream_iterator<double, char>{}, ostream_iterator<double>{cout,";\n"});//1; 2; 3;
	
	//14. bufferring <streambuf>
	template<typename C, typename Tr=char_traits<C>>
	class basic_streambuf{
		public:
			using char_type=C;
			using int_type=typename Tr::int_type;//char->int
			using pos_type=typename Tr::pos_type;//position type on buffer
			using off_type=typename Tr::off_type;//offset type...
			using traits_type=Tr;
			//...
			virtual ~basic_streambuf();
	};
	
	//15. input & output stream, buffer
	template<typename C, typename Tr=char_traits<C>>
	class basic_ostream: virtual public basic_ios<C, Tr>{
		public:
			//...
			explicit basic_ostream(basic_streambuf<C,Tr>& b);
			pos_type tellp();//get current position
			basic_ostream& seekp(pos_type);
			basic_ostream& seekp(off_type, ios_base::seekdir);
			basic_ostream& flush();//extract content to real target with erase
		
			basic_ostream& operator<<(basic_streambuf<C,Tr>* b);
	};
	
	template<typename C, typename Tr=char_tratis<C>>
	class basic_istream: virtual public basic_ios<C,Tr>>{//provide operations that handle it's streambuf directly
		public:
			//...
			explicit basic_istream(basic_streambuf<C,Tr>* b);
			pos_type tellg();
			basic_istream& seekg(pos_type);
			basic_istream& seekg(off_type, ios_base::seekdir);
			
			basic_istream& putback(C c);
			basic_istream& unget();
			int_type peek();
			int sync();
			basic_istream& operator>>(basic_streambuf<C,Tr>* b);
			basic_istream& get(basic_streambuf<C,Tr>& b, C t=Tr::newline());
			streamsize readsome(C* p, streamsize n);
	};
	
	//16. istreambuf_iterator & ostreambuf_iterator
	template<typename C, typename Tr=char_traits<C>>
	class istreambuf_iterator: public iterator<input_iterator_tag, C, typename Tr::offtype, /*undefined*/, C>{
		public:
			using char_type=C;
			using traits_type=Tr;
			using int_type=typename Tr::int_type;
			using streambuf_type=basic_streambuf<C,Tr>;
			using istream_type=basic_istream<C,Tr>;
			//...
	};
	
	template<typename C, typename Tr=char_traits<C>>
	class ostreambuf_iterator: public iterator<output_iterator_tag, void, void, void, void>{
		public:
			using char_type=C;
			using traits_type=Tr;
			using streambuf_type=basic_streambuf<C,Tr>;
			using ostream_type=basic_ostream<C,Tr>;
			//...
	};
}

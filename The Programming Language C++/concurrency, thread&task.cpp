#include <iostream>

namespace concurrency_basic_concept{
	//1. concept of memory location: one of sequences that has near bit field (not 0)
	struct S{
		char a;
		int b:5;
		unsigned c:11;
		unsigned:0;//special case
		unsigned d:8;
		struct {int ee: 8} e;
	};
	
	//2. synchronizing operation
	enum memory_order{
		memory_order_relaxed,//정렬X 
		memory_order_comsume,//C++에서 수정중이기에 사용 지양 
		memory_order_acquire,//이후의 명령이 이 앞으로 배치되는 것을 금지. 
		memory_order_release,//이전의 명령이 이 뒤로 배치되는 것을 금지. 
		memory_order_acq_rel,
		memory_order_seq_cst
	}; 
	
	//3. send memory order dependency on calling of function
	[[carries_dependency]] struct foo* f(int i){
		//호출자가 결과에 memory_order_consume을 사용하게 한다.
		return foo_head[i].load(memory_order_consume); 
	}
	
	//4. Double-checked locking for solution of ABA problem(in CAS)
	X x;
	mutex lx;
	atomic<bool> x_init{false};
	
	void some_code(){
		if(!x_init){//check 1
			lx.lock();
			if(!x_init){//check 2 because of memory resort command
				//...initialize z
				x_init=true;
			}
			lx.unlock();
		}
		//use x
	}
}

namespace task_thread1{//~1300
	//1. connect tasks by making functor
	template<typename T>
	class Sync_queue<T>{
		//... 데이터 경합 없이 put()과 get()을 제공하는 큐 
	};
	
	struct Consumer{//consume queue's work
		Sync_queue<Message>& head;
		Consumer(Sync_queue<Message>& q): head(q){}
		void operator()();
	};
	
	Sync_queue<Message> mq;//make task, connect
	Consumer c{mq};
	Producer p{mq};
	
	thread pro{p};
	thread con{c};
	//...
	
	//2. constructor of thread is variadic, so we have to use reference wrapper when we want to use reference
	void my_task(vector<double>& args);
	void test(vector<double>& v){
		thread my_thread1{my_task, v};//no! not reference
		thread my_thread2{my_task, ref(v)};//ok
		thread my_thread3{[&v]{my_task(v);}};//ok by capture list
		//...이는 호출규약의 예시이지 데이터 경합을 일으키기에 좋진 않다. 
	}
	
	//3. thread call terminate() for preventing long-alive system thread than it's thread
	void heartbeat(){
		while(true){
			output(steady_clock::now());
			this_thread::sleep_for(second{1});
		}
	}
	void run(){
		thread t{hearbeat};
	}//heartbeat()가 t의 유효범위를 넘어서도 실행이 되고 있기 때문에 terminate()를 자동으로 실행하여 종료시킨다.
	
	//4. RAII to thread if thread is also resource
	struct guard_thread: thread{
		using thread::thread;
		~guarded_thread(){
			if(joinable())
				join();
		}
	}; 
}

namespace task_thread2{
	//1. thread_local
	Map<string, int>::set_default("Heraclides", 1);
	Map<string, int>::set_default("Zeno", 1);//old problem occur on concurrency
	//solution by adding thread_local
	template<typename K, typename V>
	class Map{
		//...
		private:
			static thread_local pair<const K, V> default_value;//현재 thread가 객체를 소유해버리기때문에 데이터 경합자체가 사라짐. 
	};
	
	//2. try_lock() 's algorithm not standard
	template<typename M1, typename... Mx>
	int try_lock(M1& mtx, Mx& tail...){//by reference! mutex cannot be copied or moved
		if(mtx.try_lock()){
			int n=try_lock(tail...);
			if(n==-1)
				return -1;
			mtx.unlock();
			return n+1;
		}
		return 1;
	}
	template<typename M1>
	int try_lock(M1& mtx){
		return (mtx.try_lock())? -1: 0;
	}
	//use
	void task(mutex& m1, mutex& m2){
		unique_lock<mutex> lck1{m1, defer_lock};
		unique_lock<mutex> lck2{m2, defer_lock};
		lock(lck1, lck2);
		//use resource... if we use lock(m1,m2) without unique_lock, we have to unlock explicitly also because we use lock() to m1, m2 directly.
	}
	
	//3. call_once() with once_flag
	class X{
		public:
			X();
			//...
		private:
			//...
			static once_flag static_flag;
			static Y static_data_for_class_x;
			static void init();
	}; 
	X::X(){
		call_once(static_flag, init());
	}
	//use2
	Color& default_color(){//before use call once
		static Color def{ read_form_environment("background color") };
	}
	Color& default_color(){
		static Color def;
		static_flag __def;//컴파일러 생성 코드를 강조하기 위해 __  플래그 for call_once의 인자 
		call_once(__def, read_form_environment, "background color");//__def가 false면 read_form_environment("background color")호출 
		return def;
	}
	
	//4. Sync_queue
	template<typename T>
	class Sync_queue{
		public:
			void put(const T& val);
			void put(T&& val);
			void put(T val, steady_clock::duration d, int n);
			
			void get(T& val);
			void get(T& val, steady_clock::duration d);
		private:
			mutex mtx;
			condition_variable cond;
			list<T> q;
	}; 
	
	template<typename T>
	void Sync_queue:put(const T& val){
		lock_guard<mutex> lck(mtx);//unlock implicitly
		q.push_back(val);
		cond.notify_one();
	}
	
	template<typename T>
	void Sync_queue::get(T& val){
		unique_lock<mutex> lck(mtx);//for relock at upper code(wait) if we have to wait
		cond.wait(lck, [this]{return !q.empty(); });
		val=q.front();
		q.pop_front();
	}
	
	template<typename T>
	void Sync_queue::get(T& val, steady_clock::duration d){
		unique_lock<mutex> lck(mtx);
		bool not_empty=cond.wait_for(lck, d, [this]{ return !q.empty(); });
		if(not_empty){
			val=q.front();
			q.pop_front();
		} else{
			throw system_error{"Sync_queue: get() timeout"};
		}
	}
	
	template<typename T>
	void Sync_queue::put(T val, steady_clock::duration d, int n){
		unique_lock<mutex> lck(mtx);
		bool not_full=cond.wait_for(lck, d, [this]{ return q.size()<n; });
		if(not_full){
			q.push_back(val);
			cond.notify_one();
		} else{
			cond.notify_all();
			throw system_error{"Sync_queue: put() timeout"};
		}
	}
	
	//5. simple example of packaged_task
	int ff(int i){
		if(i)
			return i;
		throw runtime_error("ff(0)");
	}
	packaged_task<int(int)> pt{ff};
	packaged_task<int(int)> pt2{ff};
	pt1(1);
	pt2(0);
	
	//later..
	auto v1=pt.get_future();
	auto v2=pt2.get_future();
	try{
		cout<<v1.get()<<'\n';
		cout<<v2.get()<<'\n';
		//cout<<ff(1);_same result will be printed. 통상적 함수 호출과 정확히 똑같이 동작한다. 
		//cout<<ff(0);
	} catch(exception& e){
		cout<<"exception: "<<e.what()<<'\n';
	}
	
	//6. inner struct of wait_for_all(args) & wait_for_any(args)
	template<typename T>
	vector<T> wait_for_all(vector<future<T>>& vf){
		vector<T> res;
		for(auto& fu: vf)
			res.push_back(fu.get());
		return res;
	}
	
	template<typename T>
	int wait_for_any(vector<future<T>>& vf, steady_clock::duration d){
		while(true){
			for(int i=0; i!=vf.size(); ++i){
				if(!vf[i].valid())
					continue;
				switch(vf[i].wait_for(seconds{0})){//wait_for은 왜 재시작 되었는지를 알려줄 것이고, 기다리기 전에 준비 여부를 검사한다 
					case future_status::ready:
						return i;
					case future_status::timeout:
						break;
					case future_status::deferred:
						throw runtime_error("wait_for_all(): deferred future");
				}
			}
			this_thread::sleep_for(d);
		}
	}
	
	//7. useful example of async()_사용자 입력 취합 
	auto handle=async([](){ return input_interaction_manager(); });
	//...
	auto input=handle.get();
	//...
}

namespace task_thread_parallel_find{
	//8. example & inner concrete parallel find
	extern vector<Record> goods
	
	template<typename Pred>
	Record* find_rec(vector<Record>& vr, int first, int last, Pred pr){//record sequencely
		vector<Record>::iterator p=std::find_if(vr.begin()+first, vr.begin()+last, pr);//find sequencely
		if(p==vr.begin()+last)//compare end
			return nullptr;
		return &*p;//발견 시 p가 iterator이기에 원소를 가리키는 포인터 반환 
	} 
	
	const int grain=50000;
	template<typename Pred>
	Record* pfind(vector<Record>& vr, Pred pr){
		//grain은 병렬처리의 입자이다. 즉 순차적으로 처리될 레코드의 개수 
		assert(vr.size()%grain==0);//짝 맞는지 ck 
		vector<future<Record*>> res;
		for(int i=0; i!=vr.size(); i+=grain)
			res.push_back(async(find_rec<Pred>, ref(vr), i, i+grain, pr));
		for(int i=0; i!=res.size(); ++i)
			if(auto p=res[i].get())
				return p;
				
		return nullptr;
	}
	
	void find_cheap_red(){//use example
		assert(goods.size()%grain==0);
		Record* p=pfind(goods, [](Record& r){ return r.price<200 && r.color==Color::red; });
	}
	
	template<typename Pred>
	Record* pfind_any(vector<Record>& vr, Pred pr){
		vector<future<Record*>> res;
		for(int i=0; i!=vr.size(); i+=grain)
			res.push_back(async(find_rec<Pred>, ref(vr), i, i+grain, pr));
		for(int count=res.size(); count; --count){
			int i=wait_for_any(res, microseconds{10});
			if(auto p=res[i].get())//완료된 것에 대해서 가져온 뒤 반환 
				return p;
		}
		return nullptr;
	}
	template<typename Pred>
	vector<Record*> find_all_rec(vector<Record>& vr, int first, int last, Pred pr){
		vector<Record*> res;
		for(int i=first; i!=last; ++i)
			if(pr(vr[i]))
				res.push_bask(&vr[i]);
		return res;
	}
	
	template<typename Pred>
	vector<Record*> pfind_all(vector<Record>& vr, Pred pr){
		vector<future<vector<Record*>>> res;//for parallel as much as grain
		for(int i=0; i!=vr.size(); i+=grain)
			res.push_back(async(find_all_rec<Pred>, ref(vr), i, i+grain, pr));//find_all_rec return vector<Record*>
		
		vector<vector<Record*>> r2=wait_for_all(res);
		vector<Record*> r;
		for(auto& x: r2)
			for(auto p: x)
				r.push_back(p);
		return r;
	}
	//use
	void find_all_cheap_red(){
		assert(goods.size()%grain==0);
		
		auto vp=pfind_all(goods, [](Record& v){ return r.price<200 && r.color==Color::red; });
		for(auto p: vp)
			cout<<"record "<<*p<<'\n';
	}
	//test
	void just_find_cheap_red(){
		auto p=find_if(goods.begin(), goods.end(), [](Record& r){ return r.price<200 && r.color==Color::red; });
		if(p!=goods.end())
			cout<<"record"<<*p<<'\n';
		else
			cout<<"not found\n";
	}
	void just_find_all_cheap_red(){
		auto vp=find_all_rec(goods, 0, goods.size(), [](Record& r){ return r.price<200 && r.color==Color::red; });
		for(auto p: vp)
			cout<<"record"<<*p<<'\n';
	}
}

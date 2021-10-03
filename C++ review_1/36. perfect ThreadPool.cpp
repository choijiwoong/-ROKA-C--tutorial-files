#include <iostream>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <future>

namespace ThreadPool{
	class ThreadPool{
		public:
			ThreadPool(size_t num_threads);
			~ThreadPool();
			
			//void EnqueueJob(std::function<void()> job);
			template <class F, class... Args>
			std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F f, Args... args);
			
		private:
			size_t num_threads_;
			std::vector<std::thread> worker_threads_;//std::thread type
			std::queue<std::function<void()>> jobs_;
			std::condition_variable cv_job_q_;
			std::mutex m_job_q_;
			
			bool stop_all;
			void WorkerThread();
	};

//CONSTRUCTOR
ThreadPool::ThreadPool(size_t num_threads): num_threads_(num_threads), stop_all(false){
	worker_threads_.reserve(num_threads_);
	for(size_t i=0; i<num_threads_; ++i)
		worker_threads_.emplace_back([this](){ this->WorkerThread(); });//to std::thread
}
//WORKERTHREAD
void ThreadPool::WorkerThread(){
	while(true){
		std::unique_lock<std::mutex> lock(m_job_q_);
		cv_job_q_.wait(lock, [this](){ return !this->jobs_.empty() || stop_all; });
		if(stop_all && this->jobs_.empty())
			return;
		
		std::function<void()> job=std::move(jobs_.front());
		jobs_.pop();
		lock.unlock();
		
		job();
	}
}
//DESTRUCTOR
ThreadPool::~ThreadPool(){
	stop_all=true;
	cv_job_q_.notify_all();
	
	for(auto& t: worker_threads_)
		t.join();
}
//ENQUEUE JOB
template <class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueJob(F&& f, Args&&... args){
	if(stop_all)
		throw std::runtime_error("ThreadPool is stopped");
	
	using return_type=typename std::result_of<F(Args...)>::type;
	//std::packaged_task<return_type()> job(std::bind(f, args...));//job is local function 
	auto job=std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	
	std::future<return_type> job_result_future=job->get_future();//so that object will be destroied after return. we can use shared_ptr
	{
		std::lock_guard<std::mutex> lock(m_job_q_);
		jobs_.push([job](){(*job)(); });
	}
	cv_job_q_.notify_one();
	
	return job_result_future;
}

}//namespace ThreadPool

int work(int t, int id){
	printf("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));
	printf("%d end after %ds\n", id, t);
	return t+id;
}

int main(){
	ThreadPool::ThreadPool pool(3);
	
	std::vector<std::future<int>> futures;
	for(int i=0; i<10; i++)
		futures.emplace_back(pool.EnqueueJob(work, i%3+1, i));
	for(auto& f: futures)
		printf("result: %d \n", f.get());
}


/*
1.	stack FILO queue FIFO dequeue 양쪽다 pop insert 가능
2.	초기 버전을 쓰레드를 작동시키기만 초점을 맞추어 쓰레드풀이 받는 함수의 형태가 리턴타입이 void고 인자를 받지 않았지만,  
	인자를 받게 된다면 void()형태의 lambda함수로 전달하면 인자를 받을 수 있는 두번째 버전을 만들 수있었다.
	 하지만, 리턴값이 있다면 더이상은 lambda로 해결이 불가능하기 때문에 아예 EnqueueJob홤수가 그 리턴값을 보관하는 future을 리턴하게 끔 세번째 버전을 꾸려보자.
3.	std::result_of<Function(~)>::type으로 함수의 리턴 타입을 알 수 있다. 
4.	오늘의 명언: 5중대원이 내 아들들이지 걔내들은 아니다. 근무지원온 애들로부터 우리 애들이 고통받는다면 차라리 그 지원 안받고 간부들이 근무 들어가겠다.
5.	지역 변수_job을 리턴할 때 shared_ptr을 사용하면 알아서 소멸시켜주기에 편하다. 즉 하나의 job을 해당 EnqueueJob과 그걸 사용하는 곳에 shared하는 것
	또한 EnqueueJob함수에서 인자들의 복사본이 아닌 완벽한 전달을 위해 우측값 레퍼런스로 인자를 받은 후 bind안에 인자를 forward를 이용하여 넣어주자. 
*/ 

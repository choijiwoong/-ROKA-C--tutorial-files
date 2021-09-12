//ThreadPool restudy with writing remark
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace ThreadPool{
	class ThreadPool{
		public:
			//Constructor with how many thread we make?
			ThreadPool(size_t num_threads);
			//Destructor for add notify_all() to all "Works are done!"
			~ThreadPool();
			
			//EnqueueJob that can return
			template <class F, class... Args>
			std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F&& f, Args&&... args);
			
		private:
			//All number of Worker Threads
			size_t num_threads_;
			//Vector that saves Worker Thread
			std::vector<std::thread> worker_threads_;
			//Queue that saves jobs we have to do
			std::queue<std::function<void()>> jobs_;//void for passing by lambda with arguments
			
			std::condition_variable cv_job_q_;
			std::mutex m_job_q_;
			
			//For allowing thread's End
			bool stop_all;
			//Worker Thread that will be placed to worker_threads_
			void WorkerThread();
	};
	
	//Constructor
	ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false){//normal setting by initializer list
		worker_threads_.reserve(num_threads_);//reserve memory for threads
		for(size_t i=0; i<num_threads_; ++i)
			worker_threads_.emplace_back([this](){ this->WorkerThread(); });//this object(ThreadPool)'s WorkerThread function is saved to worker_threads_
	}
	//WorkerThread function's definition
	void ThreadPool::WorkerThread(){
		while(true){
			std::unique_lock<std::mutex> lock(m_job_q_);//make lock by mutex for protection of memory replace in multi threading.
			cv_job_q_.wait(lock, [this](){ return !this->jobs_.empty() || stop_all;});//make this thread sleep (if jobs are empty or stop_all is true)
			
			if (stop_all && this->jobs_.empty())//for awake & remove (if jobs are empty & stop_all is true; destructor is called)
				return;//return this thread(function) for off
			
			std::function<void()> job=std::move(jobs_.front());//make each job by move job's front(FIFO)
			jobs_.pop();//remove job in queue
			lock.unlock();//end of critical section
			
			job();//do work in this WorkerThread
		}
	}
	//Destructor with notify_all to all threads
	ThreadPool::~ThreadPool(){
		stop_all=true;//make condition for end
		cv_job_q_.notify_all();//make condition for end
		
		for (auto& t: worker_threads_)
			t.join();//make all threads join for checking end condition of each threads
	}
	//EnqueueJob with return. Input job & make future object (that will be saved return value of that job in future)
	template <class F, class... Args>//for setting return type
	std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueJob(F&& f, Args&&... args){//return future object that gets the result type of F(Args...)
		//get argument by rvalue for reducing useless copy
		if (stop_all)//if ThreadPool end while enqueuing job, throw runtime_error
			throw std::runtime_error("ThreadPool is stopped");
		
		using return_type = typename std::result_of<F(Args...)>::type;//for expressing return_type conveniently
		auto job=std::make_shared<std::packaged_task<return_type()>> (std::bind(f, std::forward<Args>(args)...));
		//auto for get any return type, packaged_task(that return future object) for promise-future model easily
		//packaged_task gets only fuction so use bind for passing 'function f' with argument, make job to make_shared because we will use this in lambda function for prevention of Broken promise error
		std::future<return_type> job_result_future=job->get_future();//set result value by promise object's get_future() function
		
		{//for automatical work of lock's destructor escaping this scope
			std::lock_guard<std::mutex> lock(m_job_q_);//make critical section with lock_guard by our mutex 'm_job_q_'
			jobs_.push([job](){ (*job)(); });//enqueue job to queue(jobs_)
		}
		cv_job_q_.notify_one();//notify this news to all threads
		
		return job_result_future;//return future object that will be returned in future
	}
	
} //namespace END


int work(int t, int id){
	printf("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));
	printf("%d end after %ds\n", id, t);
	
	return t+id;
}

int main(){
	ThreadPool::ThreadPool pool(3);//make 3 threads in ThreadPool
	std::vector<std::future<int>> futures;//for getting returned result
	
	for(int i=0; i<10; i++)
		futures.emplace_back(pool.EnqueueJob(work, i%3+1, i));//get return value to vector(futures) enqueuing job to pool
	
	for(auto& f: futures)//range-based for loop
		printf("result : %d \n", f.get());//get value with waiting
}

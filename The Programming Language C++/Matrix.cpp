#include <iostream>
#include <vector>
#include <array>
#include <type_traits>

using namespace std;

namespace MATRIX{
	//Default using of Matrix: Matrix<type, dimention> m0{~}
	//Matrix's operation is different common operation of scalar. in addition, we do not allow empty element on matrix
	//We will provide useful tools like .order(return dimention) .extent()(extent dimention) .size()(return size), (x,y)&[x,y](refer) and overloading << ...etc
	//We will use class, parameterization, move constructor & assign, RAII, variadic template, initialzier_list, operator overloading, functor, TMP, implementation inheritance
	//Writer of this book supposes Matrix is 1~2 dimention of preventiong of changing to enginerring code
	//Matrix, Matrix_ref, Matrix_slice is used. and inner function is in Matrix_impl. Matrix_ref cannot survive more than it's Matrix
	//we use std::inner_product, std::swap, std::enable_if
	
	template<typename T, size_t N>
		class Matrix_ref;
	template<size_t N>
		struct Matrix_slice;
	template<typename T, size_t N>
		class Matrix;
		
	
	//[Matrix list initialization]
	template<typename T, size_t N>
	using Matrix_initializer=typename Matrix_impl::Matrix_init<T,N>::type;//just initializer that's type is Matrix_init
	
	template<typename T, size_T N>
	struct Matrix_init{
		using type=initializer_list<typename Matrix_init<T,N-1>::type;
	};
	template<typename T>
	struct Matrix_init<T,1>{
		using type=initializer_list<T>;
	};
	template<typename T>
	struct Matrix_init<T,0>;//define as error!
	
	//[Matrix_ref]
	template<typename T, size_t N>
	class Matrix_ref{
		public:
			Matrix_ref(const Matrix_slice<N>& s, T* p): desc{s}, ptr{p}{}
			//...
		private:
			Matrix_slice<N> desc;//shape of matrix
			T* ptr;//first element of matrix
	};

	//[Matrix_slice]
	template<size_t N>
	struct Matrix_slice{
		Matrix_slice()=default;
		Matrix_slice(size_t offset, initializer_list<size_t> exts);
		Matrix_slice(size_t offset, initializer_list<size_t> exts, initializer_list<size_t> strs);//stride
		
		template<typename... Dims>
			Matrix_slice(Dims... dims);
		template<typename... Dims, typename=enable_if<All(is_convertible<Dims, size_t>()...)>>
			size_t operator()(Dims... dims) const;
		
		size_t size;
		size_t start;
		array<size_t, N> extents;
		array<size_t, N> strides;
		
		template<typename... Dims>
			size_t operator()(Dims... dims)const;
	};
	//implementation
	template<size_t N>
		template<typename... Dims>
		size_t Matrix_slice<N>::operator()(Dims... dims) const{//**************************************
			static_assert(sizeof...(Dims)==N, "Matrix_slice<N>::operator(): dimemsion mismatch");
			size_t args[N]{ size_t(dims)... };//save size of elements to array
			return start+inner_product(args, args+N, strides.begin(), size_t{0});
		}
	
	template<>
	struct Matrix_slice<1>{
		//...
		size_t operator()(size_t i) const{ return i; }
	};
	template<>
	struct Matrix_slice<2>{
		//...
		size_t operator()(size_t i, size_t j) const{ return start+i*strides[0]+j; }
	};
	
	//[Matrix]
	template<typename T, size_t N>
	class Matrix{
		public:
			static constexpr size_t order=N;//basic tools
			using value_type=T;
			using iterator=typename std::vector<T>::iterator;//we use vector innerly
			using const_iterator=typename std::vector<T>::iterator;
			
			Matrix()=default;//default
			Matrix(Matrix&&)=default;
			Matrix& operator=(Matrix&&)=default;
			Matrix(const Matrix&)=default;
			Matrix& operator=(const Matrix&)=default;
			~Matrix()=default;
			
			template<typename U>//about reference
				Matrix(const Matrix_ref<U,N>&);
			template<typename U>
				Matrix& operator=(const Matrix_ref<U,N>*);
				
			template<typename... Exts>//assign range
				explicit Matrix(Exts... exts);
				
			Matrix(Matrix_initializer<T,N>);//about initializer_list
			Matrix& operator=(Matrix_initializer<T,N>);
			
			template<typename U>//no {} without elements(we will use Matrix_initializer<T,N> only)
				Matrix(initializer_list<U>)=delete;//Matrix<Piece,2> board2{3,3};//ERROR! only (2,3)
			template<typename U>
				Matrix& operator=(initializer_list<U>)=delete;
				
			size_t extent(size_t n) const{ return desc.extents[n]; }
			size_t size() const { return elems.size(); }
			const Matrix_slice<N>& descriptor() const{ return desc; }
			
			T* data(){ return elems.data(); }
			const T* data() const{ return elems.data(); }
			
			
			//access
			template<typename... Args>//by integral m(i,j,k). return as value
				Enable_if<Matrix_impl::Requesting_element<Args...>(), T&> operator()(Args... args);
			template<typename... Args>
				Enable_if<Matrix_impl::Requesting_element<Args...>(), const T&> operator()(Args... args) const;
			template<typename... Args>//by slicing m(s1,s2,s3). m2(slice{1,2}, slice{0,3})//information of index for slicing. return as ref
				Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T,N>> operator()(const Args&... args);
			template<typename... Args>
				Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T, N> operator()(const Args&... args) const;
			/*Matrix<int, 2>m3{
			  	{01,02,03},
			  	{11,12,13},
			  	{21,22,23}
			  };
			  auto m31(slice{1,2}, 1);//{{12},{22}}
			  auto x=m3(1,2);//x==13
			*/
			
			Matrix_ref<T,N-1> operator[](size_t i){ return row(i); }//m[i]
			Matrix_ref<const T, N-1> operator[](size_t i) const { return row(i); }
			Matrix_ref<T,N-1> row(size_t n);//row
			Matrix_ref<const T, N-1> row(size_t n) const;
			Matrix_ref<T,N-1> col(size_t n);//column
			Matrix_ref<const T, N-1> col(size_t n) const;
			
			
			//mathmetic operations
			template<typename F>
				Matrix& apply(F f);//f(elements) for all element to current Matrix
			template<typename M, typename F>
				Enable_if<Matrix_type<M>(), Matrix&> apply(const M& m, F f);//f(x, mx) to argument's Matrix
			Matrix& operator=(const T& value);//scalar
			Matrix& operator+=(const T& value);
			Matrix& operator-=(const T& value);
			Matrix& operator*=(const T& value);
			Matrix& operator/=(const T& value);
			Matrix& operator%=(const T& value);
			template<typename M>
				Enable_if<Matrix_type<M>(), Matrix&> operator+=(const M& x);//to Matrix
			template<typename M>
				Enable_if<Matrix_type<M>(), Matrix&> operator-=(const M& x);
			//(binary operations are provided by non-member functions)
		
		private:
			Matrix_slice<N> desc;//save size for accessing element on Matrix(N dimention)
			std::vector<T> elems;//manage memory&elements by using vector innerly.
	};
	template<typename T>//specialization of Matrix<T,0> because of many N-1 in code.
	class Matrix<T,0>{
		public:
			static constexpr size_t order=0;
			using value_type=T;
			
			Matrix(const T& x): elem(x){}
			Matrix& operator=(const T& value){ elem=value; return *this; }
			
			T& operator()(){ return elem; }
			const T& operator()() const { return elem; }
			
			operatorT&(){ return elem; }
			operator const T&(){ return elem; }
		private:
			T elem;
	};
	template<>
	class Matrix<double,1>{//for sol example p.922. thanks to this, U=M*V+W will extent automatically to U.operator=(MVmulVadd(MVmul(M,V),W))
		public:
			Matrix(const MVmulVadd& m){
				//...
				mul_add_and_assign(this, &m.m, &m.v, &m.v2);
			}
			Matrix& operator=(const MVmulVadd& m){
				mul_add_and_assign(this, &m.m, &m.v, &m.v2);
				return *this;
			}
			//...
	};
	
	//implementations
	template<typename T, size_t N>//(for Matrix class)
		template<typename... Exts>
		Matrix<T,N>::Matrix(Exts... exts): desc{exts...}, elems(desc.size){}//copy range & allocate space with default initializer(elems is vector)
	
	template<typename T, size_t N>
	Matrix<T,N>::Matrix(Matrix_initializer<T,N> init){//****************************************
		desc.extents=Matrix_impl::derive_extents(init);//discuss range of initializer_list
		
		Matrix_impl::compute_strides(desc);//compute stride&size
		elems.reserve(desc.size);//make space for slice
		Matrix_impl::insert_flat(init, elems);//initialize initializer_list
		assert(elems.size()==desc.size);
	}
	
	template<typename T, size_t N>
		template<typename U>
		Matrix<T,N>::matrix(const Matrix_ref<U,N>& x): desc{x.desc}, elems{x.begin(), x.end()}{//constructor
			static_assert(Convertible<U,T>(), "Matrix constructor: incompatible element types");//type check(loss)
		}
		
	template<typename T, size_t N>
		template<typename U>
		Matrix<T,N>& Matrix<T,N>::operator=(const Matrix_ref<U,N>& x){//operator= overloading. so use = innerly.
			static_assert(Convertible<U,T>(), "Matrix =: incompatible element types");
			
			desc=x.desc;
			elemes.assign(x.begin(), x.end());
			return *this;
		}
	//
	template<typename T, size_t N>
	Matrix_ref<T,N-1> Matrix<T,N>::operator[](size_t n){
		return row(n);
	}
	//
	template<typename T, size_t N>
	Matrix<T,N>& Matrix<T,N>::operator+=(const T& val){
		return apply([&](T& a){ a+=val; });
	}
	
	template<typename T, size_t N>
		template<typename T, size_t N>
		Matrix<T,N>& Matrix<T,N>::apply(F f){
			for(auto& x: elems)//use reference for modify value directly
				f(x);
			return *this;//for sequential operation lik m.apply([](double& x){a=abs(x);}).apply([](double& x){a=sqrt(x);});
		}
	
	template<typename T, size_t N>
	Matrix<T,N> operator+(const Matrix<T,N>& m, const T& val){
		Matrix<T,N> res=m;//for use made function
		res+=val;//use Matrix<T,N>::operator+=(const T& val)
		return res;
	}
	
	template<typename T, size_t N>
		template<typename M>
		Enable_if<Matrix_type<M>(), Matrix<T,N>&> Matrix<T,N>::operator+=(const M& m){//this Matrix + argument Matrix
			static_assert(m.order==N, "+=: mismatched Matrix dimensions");//check type
			assert(same_extents(desc, m.descriptor()));//check size
			return apply(m, [](T& a, const Value_type<M>& b){ a+=b; });
		}
	
	template<typename T, size_t N>
		template<typename M, typename F>
		Enable_if<Matrix_type<M>(), Matrix<T,N>&> Matrix<T,N>::apply(const M& m, F f){//binary argument function. save result of f(m's elements,this elements) to this.
			assert(same_extents(desc, m.descriptor()));
			for(auto i=begin(), j=m.begin(); i!=end(); ++i, ++j)
				f(*i,*j);
			return *this;
		}
	
	//template<typename T, size_t N>
	//Matrix<T,N> operator+(const Matrix<T,N>& a, const Matrix<T,N>& b){
	//	Matrix<T,N> res=a;
	//	res+=b;
	//	return res;
	//}
	//make more general version of upper code!
	template<typename T, typename T2, size_t N, typename RT=Matrix<Common_type<Value_type<T>, Value_type<T2>>,N>>//choose more common type of two Matrix type.
	Matrix<RT,N> operator+(const Matrix<T,N>& a, const Matrix<T2,N>& b){
		Matrix<RT,N> res=a;//and make vector by using previous got type
		res+=b;
		return res;
	}//We can also define undefined type on Common_type like under example
	//template<>
	//struct Common_type<Quad, long double>{ using type=Quad; }//user designed! 
	
	//
	template<typename T, size_t N>
	Matrix<T,N> operator+(cosnt Matrix_ref<T,N>& x, const T& n){//operator for Matrix_ref
		Matrix<T,N> res=x;
		res+=n;
		return res;
	}
	
	//
	template<typename T>//multiple on Matrix(NxM & MxP=NxP)
	Matrix<T,2> operator*(const Matrix<T,1>& u, const Matrix<T,1>& v){//Nx1 * 1xM
		const size_t n=u.extent(0);
		const size_t m=v.extent(0);
		Matrix<T,2> res(n,m);//NxM
		for(size_t i=0; i!=n; ++i)
			for(size_t j=0; j!=m; ++j)
				res(i,j)=u[i]*v[j];
		return res;
	}
	
	template<typename T>
	Matrix<T,1> operator*(const Matrix<T,2>& m, const Matrix<T,1>& v){//NxM * Mx1
		assert(m.extent(1)==v.extent(0));
		const size_t nr=m.extent(0);
		const size_t nc=m.extent(1);
		Matrix<T,1> res(n);
		for(size_t i=0; i!=nr; ++i)
			for(size_t j=0; j!=nc; ++j)
				res(i)+=m(i,j)*v(j);
		return res;
	}
	
	template<typename T>
	Matrix<T,2> operator+(cosnt Matrix<T,2>& m1, const Matrix<T,2>& m2){//NxM * MxP
		const size_t nr=m1.extent(0);
		const size_t nc=m1.extent(1);
		assert(nc==m2.extent(0));
		const size_t p=m2.extent(1);
		Matrix<T,2> res(nr,p);
		for(size_t i=0; i!=nr; ++i)
			for(size_t j=0; j!=p; ++j)
				res(i,j)=dot_product(m1[i], m2.column(j));//use dot_protuct and optimize inner loop under!
				//for(size_t k=0; k!=nc; ++k)
					//res(i,j)+=m1(i,k)*m2(k,j);
		return res;
	}
	template<typename T>
	T dot_product(const Matrix_ref<T,1>& a, const Matrix_ref<T,1>& b){
		return inner_product(a.begin(), a.end(), b.begin(), 0.0);
	}
	
	//
	template<size_t N, typename List>
	array<size_t N> derived_extents(const List& list){
		array<size_t N> a;
		auto f=a.begin();
		add_extents<N>(f, list);//add range to a
		return a;
	}
	
	template<size_t N, typename I, typename List>
	enable_if<(N>1), void> add_extents(I& first, const List& list){//recursive by iterator
		assert(check_non_jagged<N>(list));
		*first++ =list.size();
		add_extents<N-1>(first, *list.begin());
	}
	template<size_t N, typename I, typename List>
	enable_if<(N==1), void> add_extents(I& first, const List& list){//stop condition
		*first++=list.size();
	}
	
	template<size_t N, typename List>
	bool check_non_jagged(const List& list){
		auto i=list.begin();
		for(auto j=i+1; j!=list.end(); ++j)
			if(derive_extents<N-1>(*i)!=derive_extents<N-1>(*j))
				return false;
		return true;
	}
	
	template<int N>
	void compute_strides(Matrix_slice<N>& ms){//**********************
		size_t st=1;
		for(int i=N-1; i>=0; --i){
			ms.strides[i]=st;
			st*=ms.extents[i];
		}
		ms.size=st;
	}
	
	template<typename T, typename Vec>
	void insert_flat(initialize_list<T> list, Vec& vec){
		add_list(list.begin(), list.end(), vec);
	}
	
	template<typename T, typename Vec>
	void add_list(const initializer_list<T>* first, const initializer_list<T>* last, Vec& vec){
		for(;first!=last; ++first)
			add_list(first->begin(), first->end(), vec);
	}
	template<typename T, typename Vec>
	void add_list(const T* first, const T* last, Vec& vec){
		vec.insert(vec.end(), first, last);//to vector(like push_back)
	}
	
	//여기부터 조금 많이 이해가 어려움.. 
	template<typename T, size_t N>
	Matrix_ref<T, N-1> Matrix<T,N>::row(size_t n){//********
		assert(n<rows());
		Matrix_slice<N-1> row;
		Matrix_impl::slice_dim<0>(n,desc,row);
		return {row,data()};
	}
	
	template<typename T>
	T& Matrix<T,1>::row(size_t i){
		return elems[i];
	}
	template<typename T>
	T& Matrix<T,0>::row(size_t n)=delete;
	
	template<typename T, size_t N>
	Matrix_ref<T,N-1> Matrix<T,N>::column(size_t n){//********
		assert(n<cols());
		Matrix_slice<N-1> col;
		Matrix_impl::slice_dim<1>(n,desc,col);
		return {col,data()};
	}
	
	template<typename T, size_t N>
		template<typename... Args>
		enable_if<Matrix_impl::Requesting_element<Args...>(), T&> Matrix<T,N>::operator()(Args... args){
			assert(Matrix_impl::check_bounds(desc, args...));
			return *(data()+desc(args...));
		}
	template<size_t N, typename... Dims>
	bool check_bounds(const Matrix_slice<N>& slice, Dims... dims){
		size_t indexes[N]{ size_t(dims)... };
		return equal(indexes, indexes+N, slice.extents.begin(), less<size_t>{});
	}
	
	template<typename... Args>
	constexpr bool Requesting_element(){
		return All(is_convertible<Args, size_t>()...);//just apply predicate to all elements
	}
	constexpr bool All(){ return true; }
	template<typename... Args>
	constexpr bool All(bool b, Args... args){
		return b&&All(args...);
	}
	
	template<typename... Args>
	constexpr bool Requesting_slice(){
		return All((is_convertible<Args, size_t>() || Same<Args,slice>())...);
	}
	
	template<typename T, size_t N>
		template<typename... Args>
		enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T,N>> Matrix<T,N>::operator()(const Args&... args){
			Matrix_slice<N> d;
			d.start=Matrix_impl::doslice(desc, d, args...);
			return {d, data()};
		}
		
	template<size_t N, typename T, typename... Args>
	size_t do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns, const T& s, const Args&... args){
		size_t m=do_slice_dim<sizeof..(Args)+1>(os,ns,s);
		size_t n=do_slice(os,ns,args...);
		return m+n;
	}
	template<size_t N>
	size_t do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns){
		return 0;
	}
}

namespace USER{
	using Mat2d=MATRIX::Matrix<double, 2>;
	using Vec=MATRIX::Matrix<double, 1>;
	
	void classical_elimination(Mat2d& A, Vec& b){
		const size_t n=A.dim1();
		for(size_t j=0; j!=n-1; ++j){
			const double pivot=A(j,j);
			if(pivot==0)
				throw Elim_failure(j);
			for(size_t i=j+1; i!=n; ++i){
				const double mult=A(i,j)/pivot;
				A[i](slice(j))=scale_and_add(A[j](slice(j)), -mult, A[i](slice(j)));
				b(i)-=mult*b(j);
			}
		}
	}
	
	void back_substitution(const Mat2d& A, const Vec& b){
		const size_t n=A.dim1();
		Vec x(n);
		for(size_t i=n-1; i<=0; --i){
			double s=b(i)-dot_product(A[i](slice(i+1)), x(slice(i+1)));
			if(double m=A(i,i))
				x(i)=s/m;
			else
				throw Back_subet_failure(i);
		}
		return x;
	}
	
	Vec classical_gaussian_elimination(Mat2d A, vec b){
		classical_elimination(A, b);
		return back_substitution(A, b);
	}
	
	void elim_with_partial_pivot(Mat2d& A, Vec& b){
		const size_t n=A.diml();
		for(size_t j=0; j!=n; ++j){
			size_t pivot_row=j;
			//find pivot
			for(size_t k=j+1; k!=n; ++k)
				if(abs(A(k,j))>abs(A(pivot_row,j)))
					pivot_rpw=k;
			if(pivot_row!=j){//if find proper pivot, swap
				A.swap_rows(j,pivot_row);
				swap(b(j),b(pivot_row));
			}
			//delete
			for(size_t i=j+1; i!=n; ++i){
				const double pivot=A(j,i);
				if(pivot==0)
					error("can't solve: pivot==0");
				const double mult=A(i,j)/pivot;
				A[i](slice(j))=scale_and_acc(A[j](slice(j)), -mult, A[i](slice(j)));
				b(i)-=mult*b(j);
			}
		}
	}
	
	//test for error on code, wrong input of classical_elimination(), loss of rounding.
	void solve_random_system(size_t n){
		Mat2d A=random_matrix(n);
		Vec b=random_vector(n);
		cout<<"A="<<A<<'\n';
		cout<<"b="<<b<<'\n';
		try{
			Vec x=classical_gaussian_elimination(A,b);
			cout<<"classical elim solution is X="<<x<<'\n';
			cout<<"A*x="<<v<<'\n';
		} catch(const exception& e){
			cerr<<e.what()<<'\n';
		}
	}//loop fusion problem.
}

namespace USER2{
	using Mat2d=Matrix<double,2>
	using Vec& v;
	
	struct MVmul{//Matrix x Vector
		const Mat2d& m;
		const Vec& v;
		MVmul(const Mat2d& mm, const Vec& vv):m{mm}, v{vv}{}
		operator Vec();//evaluate & return
	};
	inline MVmul operator*(const Mat2d& mm, const Vec& vv){
		return MVmul(mm,vv);
	}
	
	struct MVmulVadd{
		const Mat2d& m;
		const Vec& v;
		const Vec& v2;
		MVmulVadd(const MVmul& mv, const Vec& vv):m(mv.m), v(mv.v), v2(vv){}
		operator Vec();
	};
	inline MVmulVadd operator+(const MVmul& mv, const Vec& vv){
		return MVmulVadd(mv,vv);//return object when operator+ is used. and when we want to know evaluated value, call operator Vec(). delay evaluation!
	}
}

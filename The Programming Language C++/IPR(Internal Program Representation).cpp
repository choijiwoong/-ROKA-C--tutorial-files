#include <iostream>

//linearize diamond hierarchy. we want impl::Var->impl::Decl<ipr::Var>->impl::Stmt<ipr::Var>->impl::Expr<ipr::Var>->impl::Node<ipr::Var>->ipr::Var->ipr::Decl->ipr::Stmt->ipr::Expr->ipr::Node
//we will use visitor pattern for operations. this hierarchy is linear hierarchy structure without pure based class. this interface is just set of classes that contain pure virtual functions.

namespace Linearize_hierarchy_IPR{
	//IPR_interface_class_START
	struct ipr::Node{
		const int node_id;
		const Category_code category;
		virtual void accept(Visitor&) const=0;//for user
		
		protected://Node will be used as based class only
			Node(Category_code);
	};
	
	struct ipr::Expr: Node{//Node with type
		virtual const Type& type() const=0;
		
		protected:
			Expr(Category_code c): Node(c){}
	};
	
	struct ipr::Stmt: Expr{//Expr with location of source file
		virtual const Unit_location& unit_location() const=0;//low of file
		virtual const Source_location& source_location() const=0;//file
		virtual const Sequence<Annotation>& annotation() const=0;
		
		protected:
			Stmt(Category_code c): Expr(c){}
	};
	
	struct ipr::Decl: Stmt{//Stmt with name. centor of concept for making C++ code
		enum Specifier{};//classes, virtual, access modifier...etc
		virtual Specifier specifiers() const=0;
		virtual const Linkage& lang_linkage() const=0;
		virtual const Name& name() const=0;
		virtual const Region& home_region() const=0;
		virtual const Region& lexical_region() const=0;
		virtual bool has_initializer() const=0;
		virtual const Expr& initializer() const=0;
		//...
		
		protected:
			Decl(Category_code c): Stmt(c){}
	};
	
	
	template<Category_code Cat, typename T=Expr>
	struct ipr::Category: T{//support class that provides Category_code for optimization
		protected:
			Category(): T(Cat){}
	};
	struct ipr::Var: Category<var_cat, Decl>{};//for expression of Variable
	//IPR_interface_class_END
	
	
	//implementation by tamplate argument T
	template<typename T>
	struct impl::Node: T{
		using Interface=T;//user can use template arguemnt's type
		void accept(ipr::Visitor& v) const override { v.visit(*this); }//override abstract virtual function for making correspondence of ipr node & impl node
	};
	
	template<typename Interface>//부터 
	struct impl::Expr: impl::Node<Interface>{
		const ipr::Type* constraint;
		Expr(): constraint(0){}
		const ipr::Type& type() const override{ return *utill::check(constraint); }//override ipr::Expr's type() 
	};
	
	template<typename S>
	struct impl::Stmt: S{
		ipr::Unit_location unit_locus;
		ipr::Source_location src_locus;
		ref_sequence<ipr::Annotation> notes;
		const ipr::Unit_location& unit_location() const override{ return unit_locus; }
		const ipr::Source_location& source_location() const override{ return src_locus; }
		const ipt::Sequence<ipr::Annotation>& annotation() const override{ return notes; }
	};
	
	template<typename D>
	struct impl::Decl: impl::Stmt<impl::Expr<D>>{
		basic_decl_data<D> decl_data;
		ipr::Named_map* pat;
		val_sequence<ipr::Substitution> args;
		Decl(): decl_data(0), pat(0){}
		const ipr::Sequence<ipr::Category::Substitution>& substitutions() const { return args; }
		const ipr::Named_map& generating_map() const override{ return *util::check(pat); }
		const ipr::Linkage lang_linkage() const override;
		const ipr::Region& home_region() const override;
	};//성호
	
	struct Val: impl::Decl<ipr::Var>{
		const ipr::Expr* init;
		const ipr::Region* lexreg;
		Var();
		bool has_initializer() const override;
		const ipr::Expr& initializer() const override;
		const ipr::Region& lexical_region() const override;
	}; 
	
}

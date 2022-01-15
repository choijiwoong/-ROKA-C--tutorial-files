#include <iostream>

namespace implementation_box{
	class BBwidget;
	
	class Ival_box: public BBwidget{//we have to consider 'Imperial Bananas', 'LiBerated Software', 'Compiler Whizzed'. then, we have to make 4 version of Ival_box by BBwidget, CWwidget, LBwidget, LSwindow
		/*
			other version of Ival_box is made by inheritance.
			BBwidget is base class that defines common properties of graphic object.
				¤¤we can use BBwidget's functions but if we change BBwidget, we have to recompile or recode for restoring changing. so we can solve this problem by using interface of Ival_box.
		*/
		protected:
			int val;//value
			int low, high;//range
			bool changed{false};//is changed
			
		public:
			Ival_box(int ll, int hh): val{ll}, low{ll}, high{hh}{}
			virtual int get_value(){ changed=false; return val; }
			virtual void set_value(int i){ changed=true; return val; }
			virtual void reset_value(int i){ changed=true; val=i; }
			virtual void prompt(){}
			virtual bool was_changed() const{ return changed; }
			virtual ~Ival_box(){}
	};
	
	void interact(IVal_box* pb){
		int old_val=pb->get_value();
		pb->prompt();
		int i=pb->get_value();
		if(i!=old_val){
			//...
		} else{
			//...
		}
	}
	void some_fct(){
		unique_ptr<Ival_box> p1{new Ival_slider{0,5}};//use by smart pointer!
		interact(p1.get());
		unique_ptr<Ival_box> p2{new Ival_dial{1, 12}};
		interact(p2.get());
	}
	
	
	class Ival_slider: public Ival_box{
		private:
			//...
		public:
			Ival_slider(int, int);
			int get_value() override;
			void prompt() override;
	};
	Ival_dial:public Ival_box{};
	class Flashing_ival_slider: public Ival_slider{};
	class Popup_ival_slider: public Ival_slider{};
}


namespace interface_box{
	class BBwidget;
	
	class Ival_box{//interface
		/*
			this way is cool on maintainning, clean than old code that uses implementation by using interface_inheritance.
			but this way has also problem on managing version. 
			
				class Ival_slider: public Ival_box, protected BBwidget{};
				class Ival_slider: public Ival_box, protected CWwidget();
				class Ival_slider: ...
		*/
		public:
			virtual int get_value()=0;
			virtual void set_value(int i)=0;
			virtual void reset_value(int i)=0;
			virtual void prompt()=0;
			virtual bool was_changed const=0;
			virtual ~Ival_box(){}
	};
	 
	class Ival_slider: public Ival_box, protected BBwidget{//interface & implementation inheritance_class hierachy. public because of interface, protected because of supporter. MULTI INHERITANCE!
		public:
			Ival_slider(int, int);
			~Ival_slider() override;
			int get_value() override;
			void set_value(int i) override;
			
		protected:
			//... BBwidget::draw()...
		
		private:
			//... data for slider...
	};
	
	class Ival_dial: public Ival_box, protected BBwidget{};
	class Flashing_ival_slider: public Ival_slider{};
	class Popup_ival_slider: public Ival_slider{};
}

//how can we manage version?
namespace version_how{
	//[1] define many Ival_slider
	class Ival_box{};
	class BB_ival_slider: public Ival_box, protected BBwidget{};
	class CW_ival_slider: public Ival_box, protected CWwidget{};
	//...
	
	
	//[2] more seperate Ival_box
	class Ival_box{};
	class Ival_slider: public Ival_box{};
	class BB_ival_slider: public Ival_slider, protected BBwidget{};
	class CW_ival_slider: public Ival_slider, protected CWwidget{};
	//...
	
	
	//[3] more use class in structure of class hierachy
	class BB_ival_slider: public Ival_slider, protected BBslider{};
	class CW_ival_slider: public Ival_slider, protected CWslider{}; 
}


namespace final_version{
	class Ival_box{};//conceptfull class hierachy
	class Ival_slider: public Ival_box{};
	class Ival_dial: public Ival_box{};
	class Flashing_ival_slider: public Ival_slider{};
	class Popup_ival_slider: public Ival_slider{};//step by step Ival_box->Ival_slider->Popup_ival_slider
	
	class BB_ival_slider: public Ival_slider, protected BBslider{};//derived class by many graphic interface
	class BB_flashing_ival_slider: public Flashing_ival_slider, protected BBWidget_with_bells_ans_whistles{};
	class BB_popup_ival_slider: public Popip_ival_slider, protected BBslider{};
	class CW_ival_slider: public Ival_slider, protected CWslider{};
} 


namespace localize_object_maker{
	class Ival_maker{
		public:
			virtual Ival_dial* dial(int, int)=0;
			virtual Popup_ival_slider* popup_slider(int, int)=0;
			//...
	};
	
	class BB_maker: public Ival_maker{
		public:
			Ival_dial* dial(int, int) override;
			Popup_ival_slider* popup_slider(int, int) override;
			//...
	};
	Ival_dial* BB_maker::dial(int a, int b){
		return new BB_ival_dial(a,b);
	}
	Ival_dial* LS_maker::dial(int a, int b){
		return new LS_ival_dial(a,b);
	}
}

{
	using namespace localize_object;
	
	void user(Ival_maker& im){
		unique_ptr<Ival_box> pb{im.dial(0, 99)};
		//...
	}
	BB_maker BB_impl;//BB user's
	LS_maker LS_impl;//LS user's
	void driver(){//integral all version by Ival_maker! 
		user(BB_impl);//use BB
		user(LS_impl);//use LS
	}
}


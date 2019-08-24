#ifndef LOGIN_H
#define LOGIN_H

#include<gtkmm.h>
#include<string>


using namespace std;

class allUsers{
		string firstname;
		string lastname;
		string email;
		string username;
		string password;
		string zipcode;
	public:
		allUsers(string first, string last, string mail, string user, string pass, string zip);

		string get_username();
		string get_password();
		string get_email();
		string get_firstname();
		string get_lastname();
		string get_zipcode();
};

class readFromFile{
	
	
	public:
	
		vector<allUsers> data;
		vector<allUsers> readFile();
		void get_index_user(string username);
		
	
};


class Home:public Gtk::Window{

	public:
		Gtk::Image bk;
		Home();
		virtual ~Home();

		void on_login_clicked();
		void on_signup_clicked();
	
	protected:
		Gtk::Label label;
		Gtk::Button btn, btn1,exit;
		Gtk::VBox box;

};

class Login:public Gtk::Window, public readFromFile {

	public:
		Login();
	virtual ~Login();
	
	void on_login();
	void on_signup();
	

	protected:
		string user1;
		string pass1;
		int status;

		bool isValid;
		Gtk::Label label1, label2;
		Gtk::Button bt1, bt2;
		Gtk::Entry entry1, entry2;
		Gtk::VBox layout;
		Gtk::Image log;

};



class Signup:public Gtk::Window, public readFromFile{

	public:
		Signup();
		virtual ~Signup();
		
		void saveUser();
		int checkUser();
		void on_signedup();
		void on_same();
		void on_home();

	protected:
		string firstname;
		string lastname;
		string email;
		string username;
		string password;
		string zipcode;
		int status;

		Gtk::Entry entry1,entry2,entry3,entry4,entry5,entry6;
		Gtk::Label label1,label2,label3,label4,label5,label6;
		Gtk::Button signup, home;
		Gtk::VBox layout;
		
};

class display:public Gtk::Window, public readFromFile{

	public: 
		display();
		virtual ~display();
		void on_logout();
		void on_mov();
		void on_theat();
		void on_job();
		void on_rent();
		vector<allUsers> val;
		int i;
		
		
	protected:
		Gtk::Label forname, l1,l2,l3,l4;
		Gtk::Button logout, mov, theat, job, rent;
		Gtk::Label lab, lab1,lab2, lab3, lab4;
		Gtk::Label ulab, ulab1, ulab2, ulab3, ulab4, ulab5;
		Gtk::Label offer, offer1,offer2,offer3;
		Gtk::VBox layout;
		Gtk::HBox allmid;
		Gtk::VBox middle;
		Gtk::Image left;
		Gtk::Image right;

};

class Employment:public Gtk::Window, public readFromFile{
	
	
	public:
		Employment();
		virtual ~Employment();
		void on_submit();
		void on_back();
		int answe;
		vector<allUsers> val;

	protected:
		string position, years, ans, references;
		Gtk::VBox lay;
		Gtk::Label label, l1,l2,l3,l4,l5;
		Gtk::Button submit, back;
		Gtk::Entry entry1,entry2,entry3,entry4;
		Gtk::Label label1,label2,label3,label4;
		
};




class displayT:public Gtk::Window{
	
	public:
		displayT();
		virtual ~displayT();
		void on_click1();
		void on_click2();	
		void on_click3();
		void on_click4();
		void on_click5();
		void on_click6();
		void on_click7();
		void on_back();
	protected:
		Gtk::Button b1,b2,b3,b4,b5,b6,b7, back;
		Gtk::Label label;
		Gtk::VBox layout;


};

class Movie{

	string moviename;
	string runtime;
	string showTime1, showTime2, showTime3;
	vector<allUsers> val;

	public:
		Movie(string name, string runtime, string showTime1,string showTime2,string showTime3);
		string get_moviename();
		string get_runtime();
		string get_showTime1();
		string get_showTime2();
		string get_showTime3();

};

class MovieFromFile{

	public:
		int movindex = 0;
		vector<Movie> movData;
		vector<Movie> readformovie();
		void get_index_movie(string movie);

};

class displayM: public Gtk::Window{
	
	public:
		displayM();
		virtual ~displayM();
		void on_click1();
		void on_click2();
		void on_click3();
		void on_click4();
		void on_click5();
		void on_click6();
		void on_click7();
		void on_click8();
		void on_click9();
		void on_click10();
		void on_click11();
		void on_click12();		
		void on_click13();
		void on_click14();
		void on_click15();
				
		void on_back();
	protected:
		Gtk::Button back;
		Gtk::Grid g1,g3,g4,g5,g6,g7;
		Gtk::Grid g2;
		Gtk::Button a1, a2,a3,a4,a5,a6,e2,a7,a8,a9,c1,c2,c8,c9,d1;
		Gtk::Label b3,b4,b5,b6,b9;
		Gtk::VBox layout;
		
};


class RentMovie: public Gtk::Window, public readFromFile{

	string rentmoviename;
	string address;
	string city;
	string state;
	string zipcode;
	int valid;
	public:
		RentMovie();
		virtual ~RentMovie();
		void on_submit();
		void on_back();
		vector<allUsers> val;

	protected:
		Gtk::VBox lay;
		Gtk::Label label, l1,l2,l3,l4,l5;
		Gtk::Button submit, back;
		Gtk::Entry entry1,entry2,entry3,entry4, entry5;
		Gtk::Label label1,label2,label3,label4, label5;
	
	
};


//For the Seat now.


class Seatwindow:public Gtk::Window{
public:
    Seatwindow();
    virtual ~Seatwindow();
	void on_confirm();
	void on_cancel();
    	void on_button_clicked();
	void close_button();
	string send_value();

protected:
	

    Gtk::Box space1, space2, space3, space4, space5, top_box;
    Gtk::HBox space;


    //top info bar
    Gtk::Frame detail;
    Gtk::Box seat_box;
    Gtk::Label available, unavailable, selection;

    //screen indication
    Gtk::Frame bscreen;
    Gtk::Label screen;

    //seat grid map with check box
	Gtk::Frame seat;
	Gtk::Grid grid;

	Gtk::CheckButton a1,a2,a3,a4,a5,b1,b2,b3,b4,b5,c1,c2,c3,c4,c5,d1,d2,d3,d4,d5;//check box


    //Check box lable
    Gtk::Box x;
    Gtk::Label a,b,c,d,one,two,three,four,five;

	//end close button
	Gtk::HBox last;
	Gtk::Button confirm,cancel,close;

	Gtk::Button buttonlb;
	Gtk::Button buttonkg;
	Gtk::Entry value;
	Gtk::Entry name;


};


//Make a payment

class Billing
{
public:
    std::string billname;
    signed long cardnum;
    int billsc;
    int billmonth;
    int billyear;

    Billing()
    {

    }

};

class Billwindow:public Gtk::Window,public Billing
{
public:
	Billwindow();
	virtual ~Billwindow();
protected:
    Gtk::VBox mainbox;
	Gtk::HBox mbox;

	Gtk::Label payment;
	Gtk::Frame fpayment;

    Gtk::VBox bcnum;
	Gtk::Label cnum;
	Gtk::Entry ecnum;

    Gtk::VBox bscode;
	Gtk::Label scode;
	Gtk::Entry escode;

    Glib::RefPtr<Gtk::Adjustment> amonth,ayear;
	Gtk::VBox bmonth;
	Gtk::Label month;
	Gtk::SpinButton smonth;

	Gtk::VBox byear;
	Gtk::Label year;
	Gtk::SpinButton syear;



	Gtk::VBox bname;
	Gtk::Label name;
	Gtk::Entry ename;

	Gtk::HBox endbox;
	Gtk::Button submit;
    void on_submit();

	Gtk::Button exit;
    void on_exit();

};


class Coupn:public Gtk::Window{
	
	
	public:
		Coupn();
		virtual ~Coupn();
		void on_click1();
		void on_click2();
		void on_click3();
		void on_click4();
	
	
	protected:
		Gtk::VBox layout;
		Gtk::Button c1,c2,c3,c4;
		Gtk::Label label;

};

class Confirm: public Gtk::Window, public readFromFile{
	
	public:	
		Confirm(int seat);
		virtual ~Confirm();

		void on_confirm();
		void on_cancel();
		void set_allvalue();

	protected:
		string fir, emai, moviename, time, theaterinfo;
		float total;
		int seat;
		vector<allUsers> val;
		
		Gtk::Button confirm, cancel;
		Gtk::Label label1, l2, l3, l4;
		Gtk::VBox layout;


};


#endif




#include"movie.h"

#include<iostream>
#include<string>
#include<fstream>
#include<thread>
#include<chrono>

int num = 0;
int Allindex = 0;
float cup = 0;
int whichMov = 0;
float price = 0;
int theat = 0;



using namespace std;

/*To read and for to save the users*/

allUsers::allUsers(string first, string last, string mail, string user, string pass, string zip ){

	this->firstname = first;
	this->lastname = last;
	this->email = mail;
	this->username = user;
	this->password = pass;
	this->zipcode = zip;

}

string allUsers::get_username(){
	return username;

}

string allUsers::get_password(){
	return password;
}

string allUsers::get_email(){
	return email;
}

string allUsers::get_firstname(){
	return firstname;
}

string allUsers::get_lastname(){
	return lastname;
}

string allUsers::get_zipcode(){
	return zipcode;
}

void readFromFile::get_index_user(string username){

	data =  readFile();
	for(int i = 1; i<data.size(); i++){
		if(username.compare(data[i].get_username())==0){
			Allindex = i;
			break;
		}
	}

}


vector<allUsers> readFromFile::readFile(){

	vector<allUsers> all;

	string first1,last1,email1,user1,pw1,zip1;

	fstream infile;
	infile.open("users.txt");

	if(!infile.is_open()){
		cout<<"error to open the file"<<endl;
		exit(1);
	}

	while(!infile.eof()){
		infile>>first1>>last1>>email1>>user1>>pw1>>zip1;
		all.push_back(allUsers(first1,last1, email1, user1,pw1, zip1));
	}

	infile.close();
	return all;
}

/*Home page for login and Sign up */

Home::Home(){
	resize(600,600);
	set_title("Home");
	set_border_width(30);

	set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	bk.set("hi.gif");
	box.add(bk);
	label.set_markup("<big><big><big><b>Welcome to Uncle Wang's Theater</b></big></big></big>");

	box.pack_start(label,Gtk::PACK_EXPAND_WIDGET,100);
	btn.add_label("Login");
	btn.signal_clicked().connect(sigc::mem_fun(*this, &Home::on_login_clicked));
	box.pack_start(btn);

	btn1.add_label("Signup");
	btn1.signal_clicked().connect(sigc::mem_fun(*this, &Home::on_signup_clicked));
	box.pack_start(btn1);

	exit.add_label("Exit");
	exit.signal_clicked().connect(sigc::mem_fun(*this, &Home::close));
	box.pack_start(exit);

	box.show_all();
	add(box);
}

void Home::on_login_clicked(){

	Login l;
	hide();
	Gtk::Main::run(l);

}

void Home::on_signup_clicked(){

	Signup s;
	hide();
	Gtk::Main::run(s);

}

Home::~Home(){}

/*Login page for to authenciate for users */

Login::Login(){

	resize(500, 400);
	set_title("Login");
	set_border_width(30);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	log.set("log.gif");
	layout.pack_start(log);
	label1.set_markup("<big>Enter your username</big>");
	layout.pack_start(label1);
	entry1.set_placeholder_text("Username");
	layout.pack_start(entry1);
	label2.set_markup("<big>Enter your password</big>");
	layout.pack_start(label2);
	entry2.set_visibility(FALSE);
	entry2.set_placeholder_text("Password");
	layout.pack_start(entry2);


	bt1.signal_clicked().connect(sigc::mem_fun(*this, &Login::on_login));
	bt1.add_label("Login");
	layout.pack_start(bt1);

	bt2.signal_clicked().connect(sigc::mem_fun(*this, &Login::on_signup));
	bt2.add_label("Sign up");
	layout.pack_start(bt2);

	layout.show_all();
	add(layout);

}

Login::~Login(){}


void Login::on_signup(){
	Signup s;
	hide();
	Gtk::Main::run(s);
}

void Login::on_login(){

	string user1 = entry1.get_text();
	string pass1 = entry2.get_text();

	status = 0;
	if(!(user1.empty() && pass1.empty())){
		status = 1;
	}


	readFromFile::get_index_user(user1);


	if((user1.compare(data[Allindex].get_username())==0) &&(pass1.compare(data[Allindex].get_password())==0) ){
			display d;
			hide();
			Gtk::Main::run(d);

		}else{
			Gtk::MessageDialog dialog(*this, "Error", true, Gtk::MESSAGE_ERROR);
	if(status == 0){
		dialog.set_secondary_text("Please fill all the box.");
	}
	else{
		dialog.set_secondary_text("Username and password doesnot match");
	}
	dialog.run();
	dialog.close();
		}


}

/*Sign up page, if username doesnot exits, store in file or let the user know about it */

Signup::Signup(){

	resize(500,500);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	set_title("Registration");
	set_border_width(30);
	label1.set_markup("<big>Enter your first name</big>");
	layout.pack_start(label1);
	entry1.set_max_length(20);
	layout.pack_start(entry1);

	label2.set_markup("<big>Enter your last name</big>");
	layout.pack_start(label2);
	entry2.set_max_length(20);
	layout.pack_start(entry2);

	label3.set_markup("<big>Enter your email id</big>");
	layout.pack_start(label3);
	entry3.set_max_length(50);
	layout.pack_start(entry3);

	label4.set_markup("<big>Enter username</big>");
	layout.pack_start(label4);
	entry4.set_max_length(20);
	layout.pack_start(entry4);

	label5.set_markup("<big>Enter password</big>");
	layout.pack_start(label5);
	entry5.set_max_length(20);
	entry5.set_visibility(FALSE);
	layout.pack_start(entry5);

	label6.set_markup("<big>Enter zipcode</big>");
	layout.pack_start(label6);
	entry6.set_max_length(10);
	layout.pack_start(entry6);

	signup.signal_clicked().connect(sigc::mem_fun(*this, &Signup::saveUser));
	signup.add_label("Sign up");
	layout.pack_start(signup);

	home.signal_clicked().connect(sigc::mem_fun(*this, &Signup::on_home));
	home.add_label("Home");
	layout.pack_start(home);

	layout.show_all();
	add(layout);

}

Signup::~Signup(){}

int Signup::checkUser(){
	vector<allUsers> data = readFile();

	int status = 0;
	for(int i = 1; i<data.size(); i++){
		if(username.compare(data[i].get_username()) == 0){
			status = 1;
			break;
		}
	}

	return status;

}

void Signup::saveUser(){

	status = 0;

	firstname = entry1.get_text();
	lastname = entry2.get_text();
	email=entry3.get_text();
	username= entry4.get_text();
	password=entry5.get_text();
	zipcode=entry6.get_text();

	if(!(firstname.empty() && lastname.empty() && email.empty() && username.empty() && password.empty() && zipcode.empty())){
		status = 1;
	}

	ofstream outfile("users.txt", ios::app);

	if(checkUser()==0 && status == 1){
		outfile<<firstname<<" "<<lastname<<" "<<email<<" "<<username<<" "<<password<<" "<<zipcode<<endl;
		Signup::on_signedup();

	}
	else{
		Signup::on_same();
		}

	outfile.close();

}

void Signup::on_same(){

	Gtk::MessageDialog dialog(*this, "Error", true, Gtk::MESSAGE_ERROR);
	if(status == 0){
		dialog.set_secondary_text("Please fill all the box.");
	}
	else{
		dialog.set_secondary_text("Username already exits.");
	}
	dialog.run();
	dialog.close();

}

void Signup::on_home(){

	Home a;
	hide();
	Gtk::Main::run(a);

}


void Signup::on_signedup(){

	Gtk::MessageDialog dialog(*this, "Signed up successfully", true, Gtk::MESSAGE_INFO);
	dialog.set_secondary_text("Registration Successfull");
	dialog.run();
	dialog.close();
	if(Gtk::RESPONSE_YES){
		Login a;
		hide();
		Gtk::Main::run(a);
	}


}

//The main display page to show all the movie

display::display(){

	resize(900,900);
	set_title("Home of the Movies");
	set_border_width(10);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	val = readFromFile::readFile();

	ostringstream line;
	line<<"Welcome "<<val[Allindex].get_firstname()<<", select from the menus.";
	string word = line.str();

	forname.set_markup("<big><big><b>"+word+"</b></big></big>");
	//label1.set_markup(Enter your username);
	layout.pack_start(forname,Gtk::PACK_EXPAND_WIDGET, 5);

	mov.add_label("Choose Movie");
	mov.signal_clicked().connect(sigc::mem_fun(*this, &display::on_mov));
	layout.pack_start(mov);

	theat.add_label("Choose Theater");
	theat.signal_clicked().connect(sigc::mem_fun(*this, &display::on_theat));
	layout.pack_start(theat);

	job.add_label("Apply for Theater's job");
	job.signal_clicked().connect(sigc::mem_fun(*this, &display::on_job));
	layout.pack_start(job);

	rent.add_label("Rent Movies");
	rent.signal_clicked().connect(sigc::mem_fun(*this, &display::on_rent));
	layout.pack_start(rent);

	l1.set_text("~~**----------------------**~~");
	middle.pack_start(l1);

	lab.set_markup("<big><u><i>Latest Movies</i></u></big>");
	middle.pack_start(lab);
	lab1.set_text("Hobbs and Shaw");
	middle.pack_start(lab1);
	lab2.set_text("Toy Story 4");
	middle.pack_start(lab2);
	lab3.set_text("Crawl");
	middle.pack_start(lab3);
	lab4.set_text("Spider man: Far From Home");
	middle.pack_start(lab4);

	l2.set_text("~~**----------------------**~~");
	middle.pack_start(l2);

	ulab.set_markup("<big><u><i>Upcoming Movies</i></u></big>");
	middle.pack_start(ulab);
	ulab1.set_text("Joker");
	middle.pack_start(ulab1);
	ulab2.set_text("Rambo V");
	middle.pack_start(ulab2);
	ulab3.set_text("Gemini Man");
	middle.pack_start(ulab3);
	ulab4.set_text("Angel has Fallen");
	middle.pack_start(ulab4);

	l3.set_text("~~**----------------------**~~");
	middle.pack_start(l3);

	offer.set_markup("<big><u><i>Available offer</i></u></big>");
	middle.pack_start(offer);
	offer1.set_text("Free popcorn special");
	middle.pack_start(offer1);
	offer2.set_text("$20 off in purchase of 3 tickets");
	middle.pack_start(offer2);
	offer3.set_text("$5 off in 1 ticket");
	middle.pack_start(offer3);

	l4.set_text("~~**----------------------**~~");
	middle.pack_start(l4);
	left.set("left.jpg");
	allmid.pack_start(left);
	allmid.pack_start(middle);
	right.set("right.jpg");
	allmid.pack_start(right);
	layout.pack_start(allmid);


	logout.add_label("Log out");
	logout.signal_clicked().connect(sigc::mem_fun(*this, &display::on_logout));
	layout.pack_start(logout);

	layout.show_all();
	add(layout);

}

display::~display(){}

void display::on_logout(){
	Allindex = 0;
	Home s;
	hide();
	Gtk::Main::run(s);

}

void display::on_mov(){
	displayM m;
	hide();
	Gtk::Main::run(m);
}

void display::on_theat(){
	displayT t;
	hide();
	Gtk::Main::run(t);
}

void display::on_job(){
	Employment e;
	hide();
	Gtk::Main::run(e);
}

void display::on_rent(){
	RentMovie r;
	hide();
	Gtk::Main::run(r);
}

/*For Job*/

Employment::Employment(){

	resize(800,800);
	set_title("Apply for the Job");
	set_border_width(20);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	label.set_markup("<big><big><u><i><b>~~~Hello, here are the currently avaiable Jobs.~~~</b></i></u></big></big>");
	lay.pack_start(label);
	l1.set_markup("<i>Bartender</i>");
	lay.pack_start(l1);
	l2.set_markup("<i>Kitchen Manager</i>");
	lay.pack_start(l2);
	l3.set_markup("<i>Supervisor</i>");
	lay.pack_start(l3);
	l4.set_markup("<i>Cashier</i>");
	lay.pack_start(l4);
	l5.set_markup("<i>Concessionist</i>");
	lay.pack_start(l5);
	l5.set_markup("<i>Janitor</i>");
	lay.pack_start(l5);


	label1.set_text("Enter the position:");
	lay.pack_start(label1);
	entry1.set_max_length(20);
	lay.pack_start(entry1);

	label2.set_text("Experience in years (if not enter N/A)");
	lay.pack_start(label2);
	entry2.set_max_length(20);
	lay.pack_start(entry2);

	label3.set_text("Why would you like to choose this posititon? (in 100 words)");
	lay.pack_start(label3);
	entry3.set_max_length(100);
	lay.pack_start(entry3);

	label4.set_text("References (if not, N/A)");
	lay.pack_start(label4);
	entry4.set_max_length(20);
	lay.pack_start(entry4);

	submit.signal_clicked().connect(sigc::mem_fun(*this, &Employment::on_submit));
	submit.add_label("Submit");
	lay.pack_start(submit);

	back.signal_clicked().connect(sigc::mem_fun(*this, &Employment::on_back));
	back.add_label("Cancel");
	lay.pack_start(back);

	lay.show_all();
	add(lay);

};

Employment::~Employment(){}

void Employment::on_back(){
	Gtk::MessageDialog dialog(*this, "Do you want to cancel your job application?", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
	int Answer = dialog.run();
	dialog.close();
	switch(Answer){
	case(Gtk::RESPONSE_YES):{
		display d;
		hide();
		Gtk::Main::run(d);
		break;
	}
	case (Gtk::RESPONSE_NO):{
		cout<<"I want to stay here"<<endl;
		break;
	}
	default:
		break;

	}

}

void Employment::on_submit(){

	answe = 0;

	position = entry1.get_text();
	years = entry2.get_text();
	ans = entry3.get_text();
	references = entry4.get_text();

	if(!(position.empty() && years.empty() && ans.empty() && references.empty())){
		answe = 1;
	}
	ofstream outfile("job_application.txt", ios::app);
	if(answe == 1){

		outfile<<position<<" "<<years<<" "<<ans<<" "<<references;

		Gtk::MessageDialog dialog(*this, "Application Submission Successful", false, Gtk::MESSAGE_INFO);
		dialog.run();
		dialog.close();
		Employment::on_back();
	}
	else{
		Gtk::MessageDialog dialog(*this, "Please fill in all the box", true, Gtk::MESSAGE_ERROR);
		dialog.run();
		dialog.close();
	}
	outfile.close();

}


RentMovie::RentMovie(){

	resize(800,800);
	set_title("Movie Rental Market");
	set_border_width(20);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	val = readFromFile::readFile();

	ostringstream line;
	line<<"Hello " + val[Allindex].get_firstname() + ", currently avaiable movie are";
	string word = line.str();

	label.set_markup("<big><big><u><i><b>"+word+"</b></i></u></big></big>");
	lay.pack_start(label);
	l1.set_markup("<i>Spiderman</i>");
	lay.pack_start(l1);
	l2.set_markup("<i>Now you see</i>");
	lay.pack_start(l2);
	l3.set_markup("<i>Fast and Furious collection</i>");
	lay.pack_start(l3);
	l4.set_markup("<i>Project Mike</i>");
	lay.pack_start(l4);
	l5.set_markup("<i>Strangers</i>");
	lay.pack_start(l5);
	l5.set_markup("<i>Breaking Bad</i>");
	lay.pack_start(l5);


	label1.set_text("Enter the name of the movie. (If not show, you can request)");
	lay.pack_start(label1);
	entry1.set_max_length(20);
	lay.pack_start(entry1);

	label2.set_text("Address");
	lay.pack_start(label2);
	entry2.set_max_length(20);
	lay.pack_start(entry2);

	label3.set_text("City");
	lay.pack_start(label3);
	entry3.set_max_length(100);
	lay.pack_start(entry3);

	label4.set_text("State");
	lay.pack_start(label4);
	entry4.set_max_length(20);
	lay.pack_start(entry4);

	label5.set_text("Zip code");
	lay.pack_start(label5);
	entry5.set_max_length(20);
	lay.pack_start(entry5);


	submit.signal_clicked().connect(sigc::mem_fun(*this, &RentMovie::on_submit));
	submit.add_label("Submit");
	lay.pack_start(submit);

	back.signal_clicked().connect(sigc::mem_fun(*this, &RentMovie::on_back));
	back.add_label("Cancel");
	lay.pack_start(back);

	lay.show_all();
	add(lay);

};

RentMovie::~RentMovie(){};

void RentMovie::on_back(){
	Gtk::MessageDialog dialog(*this, "You are about to leave", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
	int Answer = dialog.run();
	dialog.close();
	switch(Answer){
	case(Gtk::RESPONSE_YES):{
		display d;
		hide();
		Gtk::Main::run(d);
		break;
	}
	case (Gtk::RESPONSE_NO):{
		break;
	}

	}
}

void RentMovie::on_submit(){
	rentmoviename = entry1.get_text();
	address = entry2.get_text();
	city = entry3.get_text();
	state = entry4.get_text();
	zipcode = entry5.get_text();

	valid = 0;

	if(!(rentmoviename.empty() && address.empty() && city.empty() && state.empty() && zipcode.empty())){
		valid = 1;
	}

	ofstream outfile("rent_movie.txt", ios::app);

	if(valid == 1){
		outfile<<rentmoviename<<"-"<<address<<"-"<<city<<"-"<<state<<"-"<<zipcode;
		Gtk::MessageDialog dialog(*this, "Application Submission Successful", false, Gtk::MESSAGE_INFO);
		dialog.run();
		dialog.close();
		RentMovie::on_back();
	}
	else{
		Gtk::MessageDialog dialog(*this, "Please fill in all the box", true, Gtk::MESSAGE_ERROR);
		dialog.run();
		dialog.close();
	}
	outfile.close();
}



/*For Movie now*/

displayM::displayM(){

	resize(800,1000);
	set_title("Choose the movie");
	set_border_width(10);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);



	g1.set_row_homogeneous(true);
    g1.set_column_homogeneous(true);
	g2.set_row_homogeneous(true);
    g2.set_column_homogeneous(true);
	g3.set_row_homogeneous(true);
    g3.set_column_homogeneous(true);
	g4.set_row_homogeneous(true);
    g4.set_column_homogeneous(true);
	g5.set_row_homogeneous(true);
    g5.set_column_homogeneous(true);
	g6.set_row_homogeneous(true);
    g6.set_column_homogeneous(true);
	g7.set_row_homogeneous(true);
    g7.set_column_homogeneous(true);

	b3.set_markup("<big><u><i>The Lion King,  Time: 1hr 58m</i></u></big>");
	layout.pack_start(b3);
	a1.add_label("11:00am");
	a1.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click1));
	g1.attach(a1,0,0,1,4);
	layout.pack_start(g1);

	a2.add_label("11:30am");
	a2.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click2));
	g1.attach(a2,1,0,1,4);
	layout.pack_start(g1);

	a3.add_label("12:00am");
	a3.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click3));
	g1.attach(a3,2,0,1,4);
	layout.pack_start(g1);


	b4.set_markup("<big><u><i>Once Upon a Time In Hollywood - Time: 2hr 45m</i></u></big>");
	layout.pack_start(b4);

	a4.add_label("11:00am");
	a4.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click4));

	g2.attach(a4,0,0,1,1);
	layout.pack_start(g2);

	a5.add_label("12:15pm");
	a5.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click5));
	g2.attach(a5,1,0,1,1);
	layout.pack_start(g2);

	a6.add_label("4:15pm");
	a6.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click6));
	g2.attach(a6,2,0,1,1);
	layout.pack_start(g2);


	b5.set_markup("<big><u><i>Spider-Man: Far From Home -Time: 2hr 9m</i></u></big>");
	layout.pack_start(b5);


	e2.add_label("11:45am");
	e2.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click7));
	g3.attach(e2,0,0,1,1);
	layout.pack_start(g3);

	a7.add_label("1:40am");
	a7.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click8));
	g3.attach(a7,1,0,1,1);
	layout.pack_start(g3);

	a8.add_label("4:40pm");
	a8.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click9));
	g3.attach(a8,2,0,1,1);
	layout.pack_start(g3);


	b6.set_markup("<big><u><i>Toy Story 4 -Time: 1hr 40m</i></u></big>");
	layout.pack_start(b6);

	a9.add_label("11:45am");
	a9.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click10));
	g4.attach(a9,0,0,1,1);
	layout.pack_start(g4);

	c1.add_label("2:15am");
	c1.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click11));
	g4.attach(c1,1,0,1,1);
	layout.pack_start(g4);

	c2.add_label("4:45pm");
	c2.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click12));
	g4.attach(c2,2,0,1,1);
	layout.pack_start(g4);

	b9.set_markup("<big><u><i>Aladdin -Time: 2hr 10m</i></u></big>");
	layout.pack_start(b9);

	c8.add_label("11:05am");
	c8.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click13));
	g7.attach(c8,0,0,1,1);
	layout.pack_start(g7);

	c9.add_label("12:45am");
	c9.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click14));
	g7.attach(c9,1,0,1,1);
	layout.pack_start(g7);

	d1.add_label("3:45pm");
	d1.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_click15));
	g7.attach(d1,2,0,1,1);
	layout.pack_start(g7);

	back.add_label("Home");
	back.signal_clicked().connect(sigc::mem_fun(*this, &displayM::on_back));
	layout.pack_start(back);


	layout.show_all();
	add(layout);

}

displayM::~displayM(){}



void displayM::on_click1(){
	whichMov = 1;
	num++;
	if(num == 1){
		
		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){
	
		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click2(){
	
	whichMov = 2;
	num++;
	if(num == 1){
		
		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){
		
		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click3(){
	
	whichMov = 3;
	num++;
	if(num == 1){
		
		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){
		
		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click4(){
	
	whichMov = 4;
	num++;
	if(num == 1){
		
		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){
		
		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click5(){
	
	whichMov = 5;
	num++;
	if(num == 1){
		
		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){
		
		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click6(){

	whichMov = 6;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click7(){

	whichMov = 7;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click8(){

	whichMov = 8;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click9(){

	whichMov = 9;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click10(){

	whichMov = 10;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click11(){

	whichMov = 11;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click12(){
	//Calculate_Price::moviename(12);
	whichMov = 12;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click13(){

	whichMov = 13;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click14(){

	whichMov = 14;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayM::on_click15(){

	whichMov = 15;
	num++;
	if(num == 1){

		displayT m;
		hide();
		Gtk::Main::run(m);
	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}


void displayM::on_back(){
	num = 0;
	display h;
	hide();
	Gtk::Main::run(h);
}

Movie::Movie(string name, string runtime, string showTime1,string showTime2,string showTime3){

	this->moviename = name;
	this->runtime = runtime;
	this->showTime1 = showTime1;
	this->showTime2 = showTime2;
	this->showTime3 = showTime3;

}

string Movie::get_moviename(){
	return moviename;
}

string Movie::get_runtime(){
	return runtime;
}

string Movie::get_showTime1(){
	return showTime1;
}

string Movie::get_showTime2(){
	return showTime2;
}

string Movie::get_showTime3(){
	return showTime3;
}

vector<Movie> MovieFromFile::readformovie(){

	vector<Movie> all;

	string name, runtime, s1,s2,s3;

	fstream infile;
	infile.open("show_runtime_info.txt");

	if(!infile.is_open()){
		cout<<"error to open the file"<<endl;
		exit(1);
	}

	string line;
	while(!infile.eof()){
		vector<string> f;
		getline(cin, line);
		stringstream word(line);
		string token;
		while(getline(word,token, '-')){
			f.push_back(token);
		}

		all.push_back(Movie(f[0],f[1],f[2],f[3],f[4]));
	}

	infile.close();
	return all;
}

displayT::displayT(){


	resize(800,1000);
	set_title("Theater");
	set_border_width(10);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	label.set_markup("<big><big><big><u><b><i>Choose the theather available.</i></b></u></big></big></big>");
	layout.pack_start(label);

	b1.add_label("AMC Irving Mall 14-2433 Irving Mall, Irving,TX-75062");
	b1.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_click1));
	layout.pack_start(b1);

	b2.add_label("AMC CLASSIC Irving 10-4205 W Pioneer Dr, Irving, TX-75061");
	b2.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_click2));
	layout.pack_start(b2);

	b3.add_label("Cinepolis Euless-2601 Brazos Blvd, Euless, TX-76039");
	b3.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_click3));
	layout.pack_start(b3);

	b4.add_label("Movie Tavern Central Park-2204 Airport Fwy Suite 450, Bedford, TX-76022");
	b4.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_click4));
	layout.pack_start(b4);

	b5.add_label("AMC Eastchase 9-8301 Ederville Rd, Fort Worth, TX-76120");
	b5.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_click5));
	layout.pack_start(b5);

	b6.add_label("Alamo Drafthouse Cinema Las Colinas-320 West Las Colinas Boulevard Building A2, Irving, TX-75039");
	b6.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_click6));
	layout.pack_start(b6);

	b7.add_label("Fun Movie Grill Macarthur Market place-8505 Walton Blvd, Irving, TX-75063");
	b7.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_click7));
	layout.pack_start(b7);


	back.add_label("Home");
	back.signal_clicked().connect(sigc::mem_fun(*this, &displayT::on_back));
	layout.pack_start(back);


	layout.show_all();
	add(layout);

}

displayT::~displayT(){}

void displayT::on_click1(){

	price = 18.99;
	theat = 1;
	num++;
	if(num == 1){

		displayM m;
		hide();
		Gtk::Main::run(m);

	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayT::on_click2(){

	price = 25.99;
	theat = 2;
	num++;
	if(num == 1){

		displayM m;
		hide();
		Gtk::Main::run(m);

	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayT::on_click3(){

	price = 22.99;
	theat = 3;
	num++;
	if(num == 1){

		displayM m;
		hide();
		Gtk::Main::run(m);

	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayT::on_click4(){

	price = 21.99;
	theat = 4;
	num++;
	if(num == 1){

		displayM m;
		hide();
		Gtk::Main::run(m);

	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayT::on_click5(){

	price = 22.99;
	theat = 5;
	num++;
	if(num == 1){

		displayM m;
		hide();
		Gtk::Main::run(m);

	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayT::on_click6(){

	price = 27.99;
	theat = 6;
	num++;
	if(num == 1){

		displayM m;
		hide();
		Gtk::Main::run(m);

	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayT::on_click7(){

	price = 31.99;
	theat = 7;
	num++;
	if(num == 1){

		displayM m;
		hide();
		Gtk::Main::run(m);

	}
	else if( num == 2){

		num = 0;
		Coupn s;
		hide();
		Gtk::Main::run(s);
	}
}

void displayT::on_back(){

	num = 0;
	display h;
	hide();
	Gtk::Main::run(h);
}

//Select the coupn

Coupn::Coupn(){
	resize(500,700);
	set_title("Theater");
	set_border_width(10);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	label.set_markup("<big><big><u><b>Choose the Coupon that fits for you.</b></u></big></big>");
	layout.pack_start(label);

	c1.signal_clicked().connect(sigc::mem_fun(*this, &Coupn::on_click1));
	c1.add_label("Entry in a raffle to win the projector.");
	layout.pack_start(c1);

	c2.signal_clicked().connect(sigc::mem_fun(*this, &Coupn::on_click2));
	c2.add_label("$5 off in 1 ticket");
	layout.pack_start(c2);

	c3.signal_clicked().connect(sigc::mem_fun(*this, &Coupn::on_click3));
	c3.add_label("$17 off in purchase of 3 tickets");
	layout.pack_start(c3);

	c4.signal_clicked().connect(sigc::mem_fun(*this, &Coupn::on_click4));
	c4.add_label("$35 free ticket for 5 tickets");
	layout.pack_start(c4);


	layout.show_all();
	add(layout);

}

Coupn::~Coupn(){}

void Coupn::on_click1(){
	Gtk::MessageDialog dialog(*this, "!!! You have successfully entered in the weekly lucky draw !!!", true, Gtk::MESSAGE_INFO);
	dialog.run();
	dialog.close();
	cup = 0;
	Seatwindow s;
	hide();
	Gtk::Main::run(s);
}

void Coupn::on_click2(){

	cup = 5;
	Seatwindow s;
	hide();
	Gtk::Main::run(s);
}

void Coupn::on_click3(){

	cup = 17;
	Seatwindow s;
	hide();
	Gtk::Main::run(s);
}

void Coupn::on_click4(){

	cup = 35;
	Seatwindow s;
	hide();
	Gtk::Main::run(s);
}

//This one is for seat.


Seatwindow::Seatwindow():seat("Select Seats"),
                        bscreen("Front"),
                        detail("Details"),
                        screen("Screen"),
                        top_box(Gtk::ORIENTATION_VERTICAL),
                        available("     O Available "),
                        unavailable("    Unavailable "),
                        selection("  X Selection    "),
                        a("A"),
                        b("B"),
                        c("C"),
                        d("D"),
                        one("1"),
                        two("2"),
                        three("3"),
                        four("4"),
                        five("5")
{
	set_title("Seat Selection");
	this->set_border_width(20);
	resize(500,500);
    //this->set_default_size(500,500);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);



    add(top_box);
    top_box.pack_start(detail);
    //detail.set_border_request(500,50);
    detail.add(space);
    space.set_border_width(5);
    space.pack_start(available);
    space.pack_start(unavailable);
    space.pack_start(selection);
    //top_box.pack_start(space);

    bscreen.add(screen);
    bscreen.set_border_width(15);
    //bscreen.override_color(Gdk::RGBA& get_red_u);
    top_box.pack_start(bscreen);

    //show_all_children();
    seat.add(grid);
    grid.set_row_homogeneous(true);
    grid.set_column_homogeneous(true);

    grid.attach(x,0,0,1,1);
    grid.attach(one,1,0,1,1);
    grid.attach(two,2,0,1,1);
    grid.attach(three,3,0,1,1);
    grid.attach(four,4,0,1,1);
    grid.attach(five,5,0,1,1);
    grid.attach(a,0,1,1,1);
    grid.attach(b,0,2,1,1);
    grid.attach(c,0,3,1,1);
    grid.attach(d,0,4,1,1);



	grid.attach(a1,1,1,1,1);
	grid.attach(a2,2,1,1,1);
	grid.attach(a3,3,1,1,1);
	grid.attach(a4,4,1,1,1);
	grid.attach(a5,5,1,1,1);
	grid.attach(b1,1,2,1,1);
	grid.attach(b2,2,2,1,1);
	grid.attach(b3,3,2,1,1);
	grid.attach(b4,4,2,1,1);
	grid.attach(b5,5,2,1,1);
	grid.attach(c1,1,3,1,1);
	grid.attach(c2,2,3,1,1);
	grid.attach(c3,3,3,1,1);
	grid.attach(c4,4,3,1,1);
	grid.attach(c5,5,3,1,1);
	grid.attach(d1,1,4,1,1);
	grid.attach(d2,2,4,1,1);
	grid.attach(d3,3,4,1,1);
	grid.attach(d4,4,4,1,1);
	grid.attach(d5,5,4,1,1);


	grid.show_all();
	//add(grid);
	top_box.pack_start(seat);

    confirm.add_label("Confirm");	confirm.signal_clicked().connect(sigc::mem_fun(*this,&Seatwindow::on_confirm));


    cancel.add_label("Cancel");
cancel.signal_clicked().connect(sigc::mem_fun(*this,&Seatwindow::close_button));

	
	last.add(confirm);
	last.add(cancel);
  
	top_box.pack_start(last);
	show_all_children();
}
Seatwindow::~Seatwindow()
{}

void Seatwindow::on_confirm()
{
  
	int seat=0;
	if(a1.get_active()==true)
	{
		seat+=1;
	}
	if(a2.get_active()==true)
	{
		seat+=1;
	}
	if(a3.get_active()==true)
	{
		seat+=1;
	}
	if(a4.get_active()==true)
	{
		seat+=1;
	}
	if(a5.get_active()==true)
	{
		seat+=1;
	}
	if(b1.get_active()==true)
	{
		seat+=1;
	}
	if(b2.get_active()==true)
	{
		seat+=1;
	}
	if(b3.get_active()==true)
	{
		seat+=1;
	}
	if(b4.get_active()==true)
	{
		seat+=1;
	}
	if(b5.get_active()==true)
	{
		seat+=1;
	}
	if(c1.get_active()==true)
	{
		seat+=1;
	}
	if(c2.get_active()==true)
	{
		seat+=1;
	}
	if(c3.get_active()==true)
	{
		seat+=1;
	}
	if(c4.get_active()==true)
	{
		seat+=1;
	}
	if(c5.get_active()==true)
	{
		seat+=1;
	}
	if(d1.get_active()==true)
	{
		seat+=1;
	}
	if(d2.get_active()==true)
	{
		seat+=1;
	}
	if(d3.get_active()==true)
	{
		seat+=1;
	}
	if(d4.get_active()==true)
	{
		seat+=1;
	}
	if(d5.get_active()==true)
	{
		seat+=1;
	}

	if(seat == 0){
		Gtk::MessageDialog dialog(*this, "Error", false, Gtk::MESSAGE_ERROR);
		dialog.set_secondary_text("Please, select a seat.");
		dialog.run();
		dialog.close();
	}
	else{
		Confirm w(seat);
		hide();
		Gtk::Main::run(w);
	}
	

}


void Seatwindow::close_button()
{
	display h;
	hide();
	Gtk::Main::run(h);
}
//For Confirmation.

Confirm::Confirm(int seat){

	
	set_title("Confirmation for your ticket");
	set_border_width(20);
	this->seat=seat;
	Confirm::set_allvalue();
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);


	ostringstream line;

	line<<"Your information has been stored as: "<<endl;
	line<<"Name: "<<fir<<endl;
	line<<"email: "<<emai<<endl;
	line<<"The movie you selected is "<<moviename<<endl;
	line<<"The time for movie is "<<time<<endl;
	line<<"The theater you selected is "<<theaterinfo<<endl;
	line<<"Total seats = "<<seat<<endl;
	line<<"Ticket price per seat: $"<<price<<endl;
	line<<"Your total price is $"<<total<<endl;
	string word=line.str();
	label1.set_markup("<big><b><i>"+word+"</i></b></big>");
	layout.pack_start(label1);

	confirm.add_label("Confirm");	confirm.signal_clicked().connect(sigc::mem_fun(*this,&Confirm::on_confirm));
	layout.pack_start(confirm);

    cancel.add_label("Cancel");
cancel.signal_clicked().connect(sigc::mem_fun(*this,&Confirm::on_cancel));
	layout.pack_start(cancel);

	layout.show_all();
	add(layout);

}

Confirm::~Confirm(){}

void Confirm::on_confirm(){

	Billwindow w;
	hide();
	Gtk::Main::run(w);

}

void Confirm::on_cancel(){

	display d;
	hide();
	Gtk::Main::run(d);

}


void Confirm::set_allvalue(){


	vector<string>mov = { "The Lion King,  Time: 1hr 58m","The Lion King,  Time: 1hr 58m","The Lion King,  Time: 1hr 58m","Once Upon a Time In Hollywood - Time: 2hr 45m","Once Upon a Time In Hollywood - Time: 2hr 45m","Once Upon a Time In Hollywood - Time: 2hr 45m","Spider-Man: Far From Home -Time: 2hr 9m","Spider-Man: Far From Home -Time: 2hr 9m","Spider-Man: Far From Home -Time: 2hr 9m","Toy Story 4 -Time: 1hr 40m ","Toy Story 4 -Time: 1hr 40m ","Toy Story 4 -Time: 1hr 40m ","Aladdin -Time: 2hr 10m","Aladdin -Time: 2hr 10m","Aladdin -Time: 2hr 10m"};

	vector<string>fortime = { "11:00am", "11:30am","12:00pm","11:00am","12:15am", "4:15am","11:45am","1:40am","4:40am","11:45am", "2:15pm","4:45pm","11:05am","12:45am","3:45am"};

	vector<string>alltheater = {"AMC Irving Mall 14-2433 Irving Mall, Irving,TX-75062","AMC CLASSIC Irving 10-4205 W Pioneer Dr, Irving, TX-75061", "Cinepolis Euless-2601 Brazos Blvd, Euless, TX-76039","Movie Tavern Central Park-2204 Airport Fwy Suite 450, Bedford, TX-76022", "AMC Eastchase 9-8301 Ederville Rd, Fort Worth, TX-76120","Alamo Drafthouse Cinema Las Colinas-320 West Las Colinas Boulevard Building A2, Irving, TX-75039","Fun Movie Grill Macarthur Market place-8505 Walton Blvd, Irving, TX-75063" };


	val = readFile();
	fir = val[Allindex].get_firstname();
	emai = val[Allindex].get_email();

	moviename = mov[whichMov-1];
	time = fortime[whichMov-1];
	theaterinfo = alltheater[theat -1];

	total = (seat * price)-cup;

}


//For payment

Billwindow::Billwindow():fpayment(""),
                        payment("ENTER PAYMENT INFORMATION"),
                        exit("Close"),
                        cnum("Card Number"),
                        scode("Security Code"),
                        month("Month"),
                        year("Year"),
                        name("Name on Card"),
                        amonth( Gtk::Adjustment::create(1.0, 1.0, 12.0, 1.0, 5.0, 0.0) ),
                        smonth(amonth),
                        ayear( Gtk::Adjustment::create(2019.0, 0.0, 2039.0, 1.0, 100.0, 0.0) ),
                        syear(ayear),
                        submit("Submit")
{
    set_title("Payment");
    mainbox.set_border_width(20);
    resize(300,300);
    add(mainbox);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);

    fpayment.add(payment);
    mainbox.pack_start(fpayment);

    mbox.set_border_width(5);

   
    cnum.set_alignment(Gtk::ALIGN_START);
    bcnum.pack_start(cnum);

    ecnum.set_max_length(16);
    bcnum.pack_start(ecnum);

    mbox.pack_start(bcnum, Gtk::PACK_EXPAND_WIDGET, 5);
    //security code box
    scode.set_alignment(Gtk::ALIGN_START);
    bscode.pack_start(scode);
    escode.set_max_length(4);
    bscode.pack_start(escode);
    mbox.pack_start(bscode, Gtk::PACK_EXPAND_WIDGET, 5);

    //month box
    month.set_alignment(Gtk::ALIGN_START);
    bmonth.pack_start(month);

    smonth.set_wrap();
    smonth.set_size_request(55, -1);
    bmonth.pack_start(smonth);

    mbox.pack_start(bmonth, Gtk::PACK_EXPAND_WIDGET, 5);


    //year box
    year.set_alignment(Gtk::ALIGN_START);
    byear.pack_start(year);

    syear.set_wrap();
    syear.set_size_request(55, -1);
    byear.pack_start(syear);

    mbox.pack_start(byear, Gtk::PACK_EXPAND_WIDGET, 5);

    mainbox.pack_start(mbox);
    
    
    name.set_alignment(Gtk::ALIGN_START);
    bname.pack_start(name);
    ename.set_max_length(50);
    bname.pack_start(ename);
    bname.set_border_width(10);
    mainbox.pack_start(bname);


    submit.signal_clicked().connect(sigc::mem_fun(*this,&Billwindow::on_submit));
    endbox.pack_start(submit);

    exit.signal_clicked().connect(sigc::mem_fun(*this,&Billwindow::on_exit));
    endbox.pack_start(exit);
    mainbox.pack_start(endbox);

    show_all_children();

}


Billwindow::~Billwindow(){}


void Billwindow::on_submit()
{
	if(!(ecnum.get_text().empty() && escode.get_text().empty() && ename.get_text().empty())){
	
	Gtk::MessageDialog dialog(*this, "Payment Successfull", false, Gtk::MESSAGE_INFO);
	dialog.set_secondary_text("Thank you for making the payment");
	dialog.run();
	dialog.close();
	display m;
	hide();
	Gtk::Main::run(m);
    	}
	else{	
	Gtk::MessageDialog dialog(*this, "Error", false, Gtk::MESSAGE_ERROR);
	dialog.set_secondary_text("Please, fill all the boxes");
	dialog.run();
	dialog.close();

	}
}
void Billwindow::on_exit()
{
    	display m;
	hide();
	Gtk::Main::run(m);
}































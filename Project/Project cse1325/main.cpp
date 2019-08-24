#include"movie.h"

#include<gtkmm.h>

int main(int argc, char** argv){

	Gtk::Main app(argc, argv);
	
	Home w;
	Gtk::Main::run(w);
	return 0;

}



CXXFLAGS += -std=c++11
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`

ex: main.o movie.o
	$(CXX) $(CXXFLAGS) -o hw main.o movie.o $(GTKFLAGS)
main.o: main.cpp movie.h
	 $(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)
movie.o: movie.cpp movie.h
	 $(CXX) $(CXXFLAGS) -c movie.cpp $(GTKFLAGS)
clean:
	rm -f *.o
	rm -f hw

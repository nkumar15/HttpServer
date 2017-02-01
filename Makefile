CXX=g++
CXXFLAGS=-std=c++11 -I. -I/usr/local/boost_1_42_0
LDFLAGS=-lboost_system -lboost_thread -lpthread

EXEC=http_server
SOURCES=$(wildcard *.cpp) 
OBJECTS=$(SOURCES:.cpp=.o)

$(EXEC):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(CXXFLAGS) $(LDFLAGS)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f *.o *~ core $(EXEC) $(OBJECTS)

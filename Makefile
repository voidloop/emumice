# Makefile for project "emumice"

CXX = g++
CXXFLAGS = -g
FRMWRKS = -framework Carbon
OBJS = mouse.o main.o emumice.o

.PHONY: all
all: emumice

emumice: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(FRMWRKS) -o emumice

main.o: main.cpp emumice.hpp
	$(CXX) -c main.cpp $(CXXFLAGS)

emumice.o: emumice.cpp emumice.hpp
	$(CXX) -c emumice.cpp $(CXXFLAGS)

mouse.o: mouse.cpp emumice.hpp
	$(CXX) -c mouse.cpp $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f *.o emumice
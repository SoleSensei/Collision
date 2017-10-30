CXX = g++
CXXFLAGS = -g -Wall -std=c++0x

LDFLAGS = -lglfw -lGL -lGLEW -lX11 -lpthread -lXrandr -lXi -ldl

all: test

test:  test.cpp glad.o primitives.o
	$(CXX) $(CXXFLAGS) test.cpp glad.o primitives.o -o test $(LDFLAGS)
primitives.o:
	$(CXX) $(CXXFLAGS) -c primitives.cpp -o primitives.o
glad.o:
	$(CXX) $(CXXFLAGS) -c glad.c -o glad.o

clean:
	rm test glad.o primitives.o
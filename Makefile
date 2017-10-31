CXX = g++
CXXFLAGS = -g -Wall -std=c++0x

LDFLAGS = -lglfw -lGL -lGLEW -lX11 -lpthread -lXrandr -lXi -ldl

all: test

test:  test.cpp glad.o primitives.o scene.o
	$(CXX) $(CXXFLAGS) test.cpp glad.o primitives.o scene.o -o test $(LDFLAGS)
primitives.o: primitives.cpp
	$(CXX) $(CXXFLAGS) -c primitives.cpp -o primitives.o
scene.o: scene.cpp
	$(CXX) $(CXXFLAGS) -c scene.cpp -o scene.o
glad.o: glad.c
	$(CXX) $(CXXFLAGS) -c glad.c -o glad.o

clean:
	rm test glad.o primitives.o
CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

vpath % bin
vpath %.cpp src

ifdef %
% : %.cpp
	g++ -ggdb $(CFLAGS) -o bin/$@ $< $(LIBS)
else
main : main.cpp
	g++ -ggdb $(CFLAGS) -o bin/main src/main.cpp $(LIBS)
endif

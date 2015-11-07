CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

vpath % bin
vpath %.cpp src

% : %.cpp
	g++ -ggdb $(CFLAGS) -o bin/$@ $< $(LIBS)

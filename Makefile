flags = -lglut -lGLU -lGL -Wall

all: 
	g++ main.cpp -o main $(flags)

run: 
	./main
flags = -lglfw -lGL -lGLEW -lm

all: 
	g++ base.cpp Object.cpp Target.cpp mainTest.cpp -o run $(flags)

run: 
	./run
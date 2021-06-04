flags = -lglfw -lGL -lGLEW -lm

all: 
	g++ base.cpp Object.cpp Target.cpp Obstacle.cpp Arrow.cpp main.cpp -o run $(flags)

run: 
	./run
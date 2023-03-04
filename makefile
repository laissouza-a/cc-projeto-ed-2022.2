all: clean create build run

clean:
	rm -rf bin/ obj/

create:
	mkdir bin/ obj/

build: 
	gcc app/main.c -o bin/main -lglut -lGLU -lGL

run: 
	./bin/main
build:
	gcc -Wall -Wextra -std=c99 ./src/*.c -lSDL2 -lm -o ray

run:
	./ray

clean:
	rm ray

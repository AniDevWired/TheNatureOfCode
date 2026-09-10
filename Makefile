randomW: Randomness/examples/random_walker.c 
	gcc -o bin/out.o Randomness/examples/random_walker.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

randomN: Randomness/examples/random_number.c 
	gcc -o bin/out.o Randomness/examples/random_number.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

randomWW: Randomness/exercise/random_walker.c 
	gcc -o bin/out.o Randomness/exercise/random_walker.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

test1: test/test1.c 
	gcc -o bin/test.o test/test1.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run: 
	./bin/out.o

runT: 
	./bin/test.o

clean: 
	rm -rf bin/out.o
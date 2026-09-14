randomW: Randomness/examples/random_walker.c 
	gcc -o bin/out.o Randomness/examples/random_walker.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

randomN: Randomness/examples/random_number.c 
	gcc -o bin/out.o Randomness/examples/random_number.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

randomD: Randomness/examples/normal_distribution.c 
	gcc -o bin/out.o Randomness/examples/normal_distribution.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

randomG: Randomness/examples/normal_gaussian.c 
	gcc -o bin/out.o Randomness/examples/normal_gaussian.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

randomW01: Randomness/exercise/random_walker01.c 
	gcc -o bin/out.o Randomness/exercise/random_walker01.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

randomW02: Randomness/exercise/random_walker02.c 
	gcc -o bin/out.o Randomness/exercise/random_walker02.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

paint: Randomness/exercise/paint_splatter.c 
	gcc -o bin/out.o Randomness/exercise/paint_splatter.c -I lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

test1: test/test1.c 
	gcc -o bin/test.o test/test1.c -I lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run: 
	./bin/out.o

runT: 
	./bin/test.o

clean: 
	rm -rf bin/out.o
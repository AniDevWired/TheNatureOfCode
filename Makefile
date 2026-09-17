CC = gcc
CFLAGS = -I lib/
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
BIN_DIR = bin

$(shell mkdir -p $(BIN_DIR))

# --- Randomness Examples ---
randomW:    _SRC = Randomness/examples/random_walker.c
randomN:    _SRC = Randomness/examples/random_number.c
randomD:    _SRC = Randomness/examples/normal_distribution.c
randomG:    _SRC = Randomness/examples/normal_gaussian.c
AR:         _SRC = Randomness/examples/accept_reject.c
PN:         _SRC = Randomness/examples/perlin_noise.c
PW:         _SRC = Randomness/examples/perlin_walker.c

# --- Randomness Exercises ---
randomW01:  _SRC = Randomness/exercise/random_walker01.c
randomW02:  _SRC = Randomness/exercise/random_walker02.c
paint:      _SRC = Randomness/exercise/paint_splatter.c
Gwalk:      _SRC = Randomness/exercise/gaussian_walk.c
CP:         _SRC = Randomness/exercise/custom_prob.c

randomW randomN randomD randomG AR randomW01 randomW02 paint Gwalk CP PN PW:
	$(CC) -o $(BIN_DIR)/out.o $(_SRC) $(CFLAGS) $(LIBS)

test1: test/test1.c
	$(CC) -o $(BIN_DIR)/test.o test/test1.c $(CFLAGS) $(LIBS)

test2: test/test2.c
	$(CC) -o $(BIN_DIR)/test.o test/test2.c $(CFLAGS) $(LIBS)

run: 
	./$(BIN_DIR)/out.o

runT: 
	./$(BIN_DIR)/test.o

clean: 
	rm -rf $(BIN_DIR)/*

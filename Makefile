CC=gcc
FLAGS=$(CFLAGS) -Wall -I$(INCLUDE_DIR)
INCLUDE_DIR=./include
SRC_DIR=./src
BIN_DIR=./bin
BUILD_DIR=./build

all: build bin ppm clean

ppm: ppm.o util.o ppm-operations.o
	$(CC) $(FLAGS) $(SRC_DIR)/main.c $(BUILD_DIR)/*.o -o $(BIN_DIR)/$@ -lm

ppm.o:
	$(CC) $(FLAGS) -c $(SRC_DIR)/ppm.c -o $(BUILD_DIR)/$@

ppm-operations.o: ppm.o
	$(CC) $(FLAGS) -c $(SRC_DIR)/ppm-operations.c -o $(BUILD_DIR)/$@

util.o:
	$(CC) $(FLAGS) -c $(SRC_DIR)/util.c -o $(BUILD_DIR)/$@

bin:
	mkdir -p $(BIN_DIR)

build:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

test: all
	$(BIN_DIR)/test.sh



FLAGS = -c -Wall -O3
CPP = g++

BUILD_DIR = obj/
SRC_DIR = src/

all : word_test round_test solver add_test

word_test : word
	$(CPP) -Wall -g -o word_test $(SRC_DIR)word_test.cpp $(BUILD_DIR)word.o
	
round_test : word
	$(CPP) -Wall -g -o round_test $(SRC_DIR)round_test.cpp $(BUILD_DIR)word.o
	
add_test : word add
	$(CPP) -Wall -g -o add_test $(SRC_DIR)add_test.cpp $(BUILD_DIR)word.o \
	$(BUILD_DIR)add.o
	
solver : word and or add rotl not operation xor
	$(CPP) -Wall -O3 -o solver $(SRC_DIR)solver.cpp $(BUILD_DIR)word.o \
	$(BUILD_DIR)and.o $(BUILD_DIR)or.o $(BUILD_DIR)add.o $(BUILD_DIR)rotl.o \
	 $(BUILD_DIR)not.o $(BUILD_DIR)operation.o $(BUILD_DIR)xor.o

word : $(SRC_DIR)word.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)word.cpp -o $(BUILD_DIR)word.o

operation : $(SRC_DIR)operation.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)operation.cpp -o $(BUILD_DIR)operation.o

and : $(SRC_DIR)and.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)and.cpp -o $(BUILD_DIR)and.o

or : $(SRC_DIR)or.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)or.cpp -o $(BUILD_DIR)or.o

add : $(SRC_DIR)add.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)add.cpp -o $(BUILD_DIR)add.o

rotl : $(SRC_DIR)rotl.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)rotl.cpp -o $(BUILD_DIR)rotl.o

not : $(SRC_DIR)not.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)not.cpp -o $(BUILD_DIR)not.o

xor : $(SRC_DIR)xor.cpp
	$(CPP) $(FLAGS) $(SRC_DIR)xor.cpp -o $(BUILD_DIR)xor.o

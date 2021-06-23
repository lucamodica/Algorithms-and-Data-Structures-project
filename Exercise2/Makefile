#Flag used to compile both the tests and the main program  
CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
#.h gile dependencies
COMMON_DEPS 	= src/*.h Makefile
#Command to create build and bin folders 
MKDIR_P = mkdir -p
#Parameter to be passed to the main executable
DOC = correctme.txt


#Create the main and tests excutable programs
all: bin/main_corrector bin/tests_corrector

#Compile and run the tests file
tests: bin/tests_corrector
	bin/tests_corrector

#Compile and run the main program
main: bin/main_corrector
	bin/main_corrector $(DOC)

#Compile and create the object files
build/%.o: src/%.c $(COMMON_DEPS)
	$(MKDIR_P) build
	$(MKDIR_P) bin
	$(CC) $(CFLAGS) -c $< -o $@

#Create the main program
bin/main_corrector: build/edit_distance.o build/edit_distancer_utils.o build/word_list_utils.o build/corrector_main.o $(COMMON_DEPS)
	$(CC) -o bin/main_corrector build/edit_distance.o build/edit_distancer_utils.o build/word_list_utils.o build/corrector_main.o -lm

#Create the tests program
bin/tests_corrector: build/corrector_tests.o build/edit_distance.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/tests_corrector build/corrector_tests.o build/edit_distance.o build/unity.o -lm

#Clean all the objects and executable files
clean:
	$(RM) build/*
	$(RM) bin/*

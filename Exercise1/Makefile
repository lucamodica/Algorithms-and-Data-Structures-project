#Flag used to compile both the tests and the main program  
CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
#.h gile dependencies
COMMON_DEPS 	= src/*.h Makefile
#Command to create build and bin folders 
MKDIR_P = mkdir -p
#Parameter to be passed to the main executable
FILE_NAME = records.csv
CRITERIA = 0
ORDER = 0


#Create the main and tests excutable programs
all: bin/main_mbi bin/tests_mbi

#Compile and run the tests file
tests: bin/tests_mbi
	bin/tests_mbi

#Compile and run the main program
main: bin/main_mbi
	bin/main_mbi $(FILE_NAME) $(CRITERIA) $(ORDER)

#Compile and create the object files
build/%.o: src/%.c $(COMMON_DEPS)
	$(MKDIR_P) build
	$(MKDIR_P) bin
	$(CC) $(CFLAGS) -c $< -o $@

#Create the main program
bin/main_mbi: build/array_management.o build/M_BI_Sort_main.o $(COMMON_DEPS)
	$(CC) -o bin/main_mbi build/array_management.o build/M_BI_Sort_main.o -lm

#Create the tests program
bin/tests_mbi: build/M_BI_Sort_tests.o build/array_management.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/tests_mbi build/M_BI_Sort_tests.o build/array_management.o build/unity.o -lm

#Clean all the objects and executable files
clean:
	$(RM) build/*
	$(RM) bin/*

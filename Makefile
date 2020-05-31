##Adapted from http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
DEPS = include/main.h include/run.h include/process.h include/args.h include/process_array.h include/stats.h include/bitmap.h
OBJ = src/main.o src/run.o src/process_array.o src/stats.o src/bitmap.o
EXE = scheduler

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

$(EXE): $(OBJ)
	gcc -Wall -o $@ $^

all: build

build:
	gcc -Wall -o $@ $^
	
test:
	./scripts/test.sh


docker:
	docker build -t scheduler .

##Delete object and executable files
clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(EXE)
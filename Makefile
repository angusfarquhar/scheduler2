##Adapted from http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#DEPS = get_request.h status.h get_links.h url.h
OBJ = main.o
EXE = scheduler

##Create .o files from .c files. Searches for .c files with same .o names given in OBJ
%.o: %.c $(DEPS)
	gcc -c -o $@ $<

##Create executable linked file from object files. 
$(EXE): $(OBJ)
	gcc -Wall -o $@ $^

##Delete object and executable files
clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(EXE)
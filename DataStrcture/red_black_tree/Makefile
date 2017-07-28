cc = gcc
cflags = -Wall -g
program = rbtree 
deps = rbtree.h
objects = rbtree.o rbtree_test.o 

$(program) : $(objects)
	$(cc) $(cflags) -o $(program) $(objects)

%.o : %.c $(deps)
	$(cc) $(cflags) -c $< -o $@

.PHONY : clean
clean :
	rm $(objects) $(program)
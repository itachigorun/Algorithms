cc = gcc
program = rbtree 
deps = rbtree.h
objects = rbtree.o retree_test.o 

$(program) : $(objects)
	$(cc) -o $(program) $(objects)

%.o : %.c $(deps)
	$(cc) -c $< -o $@

.PHONY : clean
clean :
	rm $(objects) $(program)
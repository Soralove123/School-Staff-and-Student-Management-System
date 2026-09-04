CC=gcc
CFLAGS=-c -Wall -g -o
OBJS=main.o administrator.o linkstack.o teacher.o linkstackstudent.o student.o

test:$(OBJS)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) $@ $<

.PHONY:clean
clean:
	rm *.o test -

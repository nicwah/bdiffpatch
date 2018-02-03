PRG= bdiffpatchtest
SRC= main.c bdiffpatch.c
OBJ= main.o bdiffpatch.o

CFLAGS= -g -std=c99

all: $(OBJ)
	gcc $(CFLAGS) -o $(PRG) $(OBJ)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm *.o *~

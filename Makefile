PRG= bdiffpatchtest
SRC= main.c bdiffpatch.c
OBJ= main.o bdiffpatch.o

all: $(OBJ)
	gcc -o $(PRG) $(OBJ)

%.o: %.c
	gcc -c $< -o $@

clean:
	rm *.o *~

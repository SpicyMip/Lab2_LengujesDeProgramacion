all: clean executable execute

executable: main.o certamen.o
	gcc -o exe main.o certamen.o

main.o:
	gcc -c main.c

certamen.o:
	gcc -c certamen.c

execute:
	./exe

clean:
	rm -f *.o exe
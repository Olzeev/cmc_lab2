all: program.exe

program.exe: main.c funcs.o integral.o root.o test.o
	gcc -m32 main.c funcs.o integral.o root.o test.o -o program.exe -lm

funcs.o: funcs.asm
	nasm -f elf32 funcs.asm -o funcs.o 
	
integral.o: integral.c
	gcc -c -m32 integral.c -o integral.o

root.o: root.c
	gcc -c -m32 root.c -o root.o

test.o: test.c
	gcc -c -m32 test.c -o test.o

clean:
	rm funcs.o integral.o root.o test.o

all: main.c funcs.o
	gcc -m32 main.c funcs.o -o program.exe -lm

funcs.o:
	nasm -f elf32 funcs.asm -o funcs.o 
	
clean:
	rm funcs.o

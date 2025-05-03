all: main.c
	gcc main.c -o main.exe -lm

run: build
	./main.exe

clean:
	rm main.exe

all: prog

prog: wordcount.c
	gcc  wordcount.c words.c -o wordcount.o
run: wordcount.o
	./wordcount.o input.txt >> output.txt
clean:
	rm wordcount.o
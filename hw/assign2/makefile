all: prog

prog: prog.c 
	gcc -o prog prog.c pcb.c

clean:
	rm -f prog *.o
cleanAll: test[1-9].txt
	rm -f prog *.o
	rm -f test[1-9].txt
test:
	@make run1 > test1.txt
	@make run2 > test2.txt
	@make run3 > test3.txt
	@make run4 > test4.txt
run1:
	./prog -alg FIFO -input input1.txt
run2:
	./prog -alg SJF -input input1.txt
run3:
	./prog -alg PR -input input1.txt
run4:
	./prog -alg RR --quantum 3  -input input1.txt
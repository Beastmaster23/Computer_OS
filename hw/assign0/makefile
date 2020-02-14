.DEFAULT_GOAL:=compile

test2: driver2.c input_file.txt
	@echo "Testing driver2..."
	@./driver2.out input_file.txt output_file.txt
	@echo "Success?"
	
compile: driver1.c driver2.c
	@echo "Compiling..."
	@gcc myio.c driver1.c -o driver1.out -lm
	@gcc driver2.c myio.c -o driver2.out -lm

clean: driver1.out driver2.out output_file.txt
	@echo "Cleaing..."
	@rm driver1.out
	@rm driver2.out
	@rm output_file.txt
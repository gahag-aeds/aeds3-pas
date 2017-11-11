all:
	@gcc -g -O2 pa.c -o pa.bin && ./pa.bin < input.txt

valgrind:
	@gcc -g -O2 pa.c -o pa.bin && valgrind ./pa.bin < input.txt

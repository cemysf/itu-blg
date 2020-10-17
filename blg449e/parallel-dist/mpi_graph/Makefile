###  BLG449E - MPI Graph Homework
###  Cem Yusuf Aydoğdu
###  150120251
### 
###  Makefile
###  Contains compiling and running parameters
### 

all:
	mpicc -g -Wall -std=c99 -o out main.c -lm
run:
	echo "NOTE: tested with 10 processes"
	echo "Enter number of processes:"; \
	read  process_number; \
	mpiexec -n $$process_number ./out 
clean:
	rm out

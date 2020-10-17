
FILE:=$(shell ls -t | awk 'NR==1{print $0}')	## en son değişen(kaydedilen) dosyayı alır!!!

all:
	mpicc -g -Wall -std=c99 -o out $(FILE)
clean:
	rm out
run:
	echo "process sayısı: "; \
	read  process_number; \
	mpiexec -n $$process_number ./out 

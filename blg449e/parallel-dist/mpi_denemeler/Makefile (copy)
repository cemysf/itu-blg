#process_number=10

all:
	echo "Dosyalar:\n"
	echo "`ls`\n"
	echo "c dosyası adı gir: "; \
	read  f_name; \
	mpicc -g -Wall -std=c99 -o out $$f_name
clean:
	rm out
run:
	echo "process sayısı: "; \
	read  process_number; \
	mpiexec -n $$process_number ./out 

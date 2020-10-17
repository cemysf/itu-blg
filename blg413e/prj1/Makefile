asm_file= kmp
c_file = kmpmain
output_file = kmp

all:
	nasm -f elf32 $(asm_file).asm -o $(asm_file).o
	gcc -c $(c_file).c -o $(c_file).o -g
	gcc $(asm_file).o $(c_file).o -o $(output_file) -g

clean:
	rm $(asm_file).o $(c_file).o $(output_file)

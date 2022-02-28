all: bellman-ford help command1 command2

bellman-ford:
	g++ bellman-ford.cpp -o bellman-ford

help:
	./bellman-ford -h

command1:
	## Exemplo do comando 1
	./bellman-ford -f input -i 1 -l 4

command2:
	## Exemplo do comando 2
	./bellman-ford -f input -i 1

clean:
	rm -f bellman-ford
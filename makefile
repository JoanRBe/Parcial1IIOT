CC=gcc

all: client

help:
	@echo "Objectius possibles:\n"
	@echo "  * help   :Aquesta ajuda"
	@echo "  * all    :Compilar/construir executables"
	@echo "  * clean  :Netejar/borrar projecte"
	@echo "  * doc    :Crear documentacio"
	@echo ""

build/.deixarme:

	mkdir build
	touch build/.deixarme

build: build/.deixarme

client: build build/client

build/client: build src/main_client.c

	${CC} src/main_client.c -o build/client

clean:
	rm -rf build/

make test:

	./build/client --url "parcial1.html" --ip "192.168.11.249"
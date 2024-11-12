CC=gcc

all: client_smtp

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

		./build/client_smtp --servidor "172.20.0.21" --usuari "1457962" --remitent 1457962@campus.euss.org --destinatari 1457962@campus.euss.org --assumpte "Mail de prova" --text /home/pi/Desktop/IIOT/src/client_smtp/textemail.txt

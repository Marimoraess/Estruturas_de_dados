CC = gcc
CFLAGS = -std=c99 -Wall

FONTES = encadeamento_exterior.c cliente.c compartimento_hash.c
HEADERS = encadeamento_exterior.h cliente.h compartimento_hash.h
EXEC = encadeamento_exterior

# Pasta com os casos de teste e pasta onde os testes são executados
CASOS_DIR ?= casos-teste
EXEC_DIR = execucao
CASOS = $(shell ls $(CASOS_DIR) | sort -n)
ARQS = tabHash.dat clientes.dat

.PHONY: all test caso clean

# Compila o programa
all: $(EXEC)

$(EXEC): $(FONTES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXEC) $(FONTES)

# Roda todos os casos de teste: make test
test: $(EXEC)
	@passou=0; total=0; \
	for c in $(CASOS); do \
		total=$$((total + 1)); \
		rm -rf $(EXEC_DIR); mkdir -p $(EXEC_DIR); \
		for a in $(ARQS); do cp $(CASOS_DIR)/$$c/$$a $(EXEC_DIR)/; done; \
		(cd $(EXEC_DIR) && ../$(EXEC) < ../$(CASOS_DIR)/$$c/entrada.txt > saida_obtida.txt); \
		if diff --strip-trailing-cr -q $(EXEC_DIR)/saida_obtida.txt $(CASOS_DIR)/$$c/saida.txt > /dev/null; then \
			echo "Caso $$c: PASSOU"; passou=$$((passou + 1)); \
		else \
			echo "Caso $$c: FALHOU (rode 'make caso N=$$c' para ver as diferenças)"; \
		fi; \
	done; \
	echo "$$passou de $$total casos passaram"; \
	test $$passou -eq $$total

# Roda um caso de teste e mostra as diferenças: make caso N=4
caso: $(EXEC)
	@if [ -z "$(N)" ]; then echo "Informe o número do caso. Exemplo: make caso N=4"; exit 1; fi
	@rm -rf $(EXEC_DIR); mkdir -p $(EXEC_DIR)
	@for a in $(ARQS); do cp $(CASOS_DIR)/$(N)/$$a $(EXEC_DIR)/; done
	@cd $(EXEC_DIR) && ../$(EXEC) < ../$(CASOS_DIR)/$(N)/entrada.txt > saida_obtida.txt || echo "ATENÇÃO: o programa terminou com erro"
	@echo "Saída obtida: $(EXEC_DIR)/saida_obtida.txt"
	@echo "Saída esperada: $(CASOS_DIR)/$(N)/saida.txt"
	@echo "Diferenças (< saída obtida, > saída esperada):"
	@diff --strip-trailing-cr $(EXEC_DIR)/saida_obtida.txt $(CASOS_DIR)/$(N)/saida.txt && echo "Nenhuma: caso $(N) PASSOU"

# Apaga o executável e a pasta de execução
clean:
	rm -rf $(EXEC) $(EXEC).exe $(EXEC_DIR)

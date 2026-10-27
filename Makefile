# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Nome do executável e diretório de saída
TARGET = bin/batalha_jogo

# Busca automaticamente todos os arquivos .c dentro de src/
SRCS = $(wildcard src/*.c)

# Regra principal: compila diretamente do .c para o executável sem gerar .o
all:
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Regra para compilar e já executar o programa
run: all
	./$(TARGET)

# Regra para apagar o executável gerado
clean:
	rm -rf bin/
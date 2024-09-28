# Defina o compilador
CC = gcc

# Defina as flags do compilador
CFLAGS = -Wall -g

# Defina a biblioteca SDL
LIBS = `sdl2-config --cflags --libs` -lm -lsqlite3

# Nome do executável
TARGET = museu

# Arquivos fontes
SRCS = main.c src/pessoa.c src/control.c src/mapa.c src/accoes.c src/bd.c

# Arquivos objetos
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para construir o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Regra para compilar arquivos .c em arquivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

# Regra para limpar arquivos temporários
clean:
	rm -f $(TARGET) $(OBJS)

# Regra para verificar se o compilador e as bibliotecas estão disponíveis
check:
	@sdl2-config --version > /dev/null || (echo "SDL2 não encontrado. Instale a biblioteca SDL2." && exit 1)

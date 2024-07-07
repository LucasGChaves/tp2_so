# Nome do executável
EXECUTABLE = prog

# Compilador C
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Arquivos fonte
SOURCES = main.c linked_list.c stack.c circular_queue.c

# Arquivos objeto (gerados a partir dos arquivos fonte)
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão: compila o executável
all: $(EXECUTABLE)

# Regra para compilar o executável
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Regra para compilar os arquivos objeto 
%.o: %.c data_structs.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
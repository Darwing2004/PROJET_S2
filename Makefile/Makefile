# Nom de l'exécutable
EXEC = main

# Fichiers source et en-tête
SRC = Projet_C_mission1.c
OBJ = $(SRC:.c=.o)
HEADERS = structures.h

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Règle par défaut
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des fichiers .c en .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f *.o $(EXEC)

# Pour tout nettoyer
fclean: clean

# Recompile tout
re: fclean all

.PHONY: all clean fclean re


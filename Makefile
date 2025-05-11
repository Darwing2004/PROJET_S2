# Nom de l'exécutable
EXEC = bin/main

# Dossiers pour les fichiers source, objets et binaires
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Fichiers source et d'en-tête
SRC = $(SRC_DIR)/Projet_C_mission1.c
OBJ = $(OBJ_DIR)/Projet_C_mission1.o
HEADERS = $(INC_DIR)/Projet_C_mission1.h

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I$(INC_DIR)

# Créer le dossier des objets si nécessaire
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Créer le dossier des binaires si nécessaire
$(BIN_DIR):
	mkdir $(BIN_DIR)

# Règle par défaut : compiler et créer l'exécutable
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	@echo "Liaison des fichiers objets pour créer l'exécutable..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Exécutable créé dans $(EXEC)"

# Compilation des fichiers .c en .o
$(OBJ): $(SRC) | $(OBJ_DIR)
	@echo "Compilation de $(SRC) en $(OBJ)..."
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Fichier objet $(OBJ) créé"

# Nettoyage des fichiers générés (compatible Windows)
clean:
	if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	@echo "Fichiers nettoyés"

# Pour tout nettoyer
fclean: clean

# Recompile tout
re: fclean all

.PHONY: all clean fclean re

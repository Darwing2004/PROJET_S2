# Nom de l'exécutable
EXEC = bin/programme

# Répertoires
SRC_DIR = src
OBJ_DIR = build
INC_DIR = include

# Fichiers source
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Objets générés
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Options de compilation
CFLAGS = -Wall -Wextra -g -I$(INC_DIR)

# Librairies à l'édition des liens
LDFLAGS = -lraylib -lwinmm -lgdi32 -lopengl32

# Compilateur
CC = gcc

# Règle par défaut
all: $(EXEC)

# Lien final
$(EXEC): $(OBJS)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@echo "Suppression des fichiers objets..."
	@if exist build\*.o del /Q build\*.o || true
	@if exist build rmdir /S /Q build || true

# Nettoyage complet
mrproper: clean
	@echo "Suppression de l'exécutable..."
	@if exist $(EXEC).exe del /Q $(EXEC).exe || true
	@if exist bin rmdir /S /Q bin || true

.PHONY: all clean mrproper

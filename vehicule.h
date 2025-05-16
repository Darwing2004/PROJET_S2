#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    int capacite;       // pour les capacités des ressources (en kg ou unités)
    char type_urgence[20];  //incendie , évacuation approvissionnement
} Vehicule;


#include <stdio.h>
#include <string.h>
#include "../include/structures.h"



void afficher_sommets_sinistres(Tab_sommets* tab) {
    printf("📍 Sommets sinistrés détectés :\n");
    for (int i = 0; i < tab->n_sommets; i++) {
        Summit_city s = tab->sommets[i];
        if (s.est_sinistre == 1) {
            printf("- ID : %d | Nom : %s | Type : %s | Urgence : %s\n",
                   s.ID, s.nom, s.type, s.type_urgence);
        }
    }
}

int main() 
{
    Tab_sommets tab;

    // Initialisation manuelle pour tester
    Summit_city villes[2] = {
        {0, "ville", "Paris", 1000, NULL, 1, "incendie"},
        {1, "hopital", "Nice", 500, NULL, 0, ""}
    };
    tab.sommets = villes;
    tab.n_sommets = 2;

    afficher_sommets_sinistres(&tab);
    return 0;
}
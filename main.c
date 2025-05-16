#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions.c"  // Inclus les fonctions

int main() {
    Graphe G;
    // Initialiser le graphe et les sommets
    initialiser_graphe_entier(&G);

    // Ajouter des véhicules
    ajouter_vehicule(10, "incendie", 1, 30);
    ajouter_vehicule(5, "évacuation", 2, 45);
    ajouter_vehicule(7, "urgence médicale", 3, 60);

    // Affecter les véhicules aux routes
    affecter_vehicules(&G, 0);  // Exemple avec le sommet de départ 0 (par exemple, ville 1)

    // Afficher les résultats
    afficher_acheminement(&G, 0);

    return 0;
}

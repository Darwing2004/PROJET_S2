#include "Raylib"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SOMMET_MAX 50
#define RAYON_CERCLE 200
#define CENTRE_X 400
#define CENTRE_Y 300

typedef struct Summit_city {
    char type[50];
    Vector2 position;
} Summit_city;

typedef struct Route {
    int distance;
    int etat;      // 0 = OK, 1 = endommagée, 2 = détruite
    int capacite;
} Route;

typedef struct Graphe {
    Summit_city *sommets;
    Route **chemins;
} Graphe;

Graphe *Creation_Graphe() {
    Graphe *graphe = malloc(sizeof(Graphe));
    graphe->sommets = malloc(SOMMET_MAX * sizeof(Summit_city));
    graphe->chemins = malloc(SOMMET_MAX * sizeof(Route*));

    for (int i = 0; i < SOMMET_MAX; i++) {
        graphe->chemins[i] = malloc(SOMMET_MAX * sizeof(Route));
    }

    for (int i = 0; i < SOMMET_MAX; i++) {
        sprintf(graphe->sommets[i].type, "S%d", i);

        float angle = 2 * PI * i / SOMMET_MAX;
        graphe->sommets[i].position = (Vector2){
            CENTRE_X + RAYON_CERCLE * cosf(angle),
            CENTRE_Y + RAYON_CERCLE * sinf(angle)
        };

        for (int j = 0; j < SOMMET_MAX; j++) {
            graphe->chemins[i][j].distance = 0;
            graphe->chemins[i][j].etat = 0;
            graphe->chemins[i][j].capacite = 0;
        }
    }

    // Exemple de routes
    graphe->chemins[0][1].distance = 10;
    graphe->chemins[1][2].distance = 20;
    graphe->chemins[2][3].distance = 15;
    graphe->chemins[3][4].distance = 25;
    graphe->chemins[4][0].distance = 30;
    graphe->chemins[5][6].distance = 10;
    graphe->chemins[5][4].distance = 14;
    

    return graphe;
}

void AfficherGraphe(Graphe *graphe) {
    // Dessiner les arcs (routes)
    for (int i = 0; i < SOMMET_MAX; i++) {
        for (int j = 0; j < SOMMET_MAX; j++) {
            if (graphe->chemins[i][j].distance > 0) {
                Color couleur = BLACK;
                if (graphe->chemins[i][j].etat == 1) couleur = ORANGE;
                else if (graphe->chemins[i][j].etat == 2) couleur = RED;

                DrawLineV(graphe->sommets[i].position, graphe->sommets[j].position, couleur);
            }
        }
    }

    // Dessiner les sommets
    for (int i = 0; i < SOMMET_MAX; i++) {
        Vector2 pos = graphe->sommets[i].position;
        DrawCircleV(pos, 20, SKYBLUE);
        DrawText(graphe->sommets[i].type, pos.x - 10, pos.y - 10, 12, DARKBLUE);
    }
}

void LibererGraphe(Graphe *graphe) {
    for (int i = 0; i < SOMMET_MAX; i++) {
        free(graphe->chemins[i]);
    }
    free(graphe->chemins);
    free(graphe->sommets);
    free(graphe);
}

int main(void) {
    InitWindow(800, 600, "Affichage du Graphe - Raylib");
    SetTargetFPS(60);

    Graphe *graphe = Creation_Graphe();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Graphe des Sommets et Routes", 10, 10, 20, DARKGRAY);
        AfficherGraphe(graphe);

        EndDrawing();
    }

    LibererGraphe(graphe);
    CloseWindow();
    return 0;
}

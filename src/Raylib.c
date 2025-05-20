#include "structures.h"
#include <raylib.h>
#include <math.h>

#define USE_RAYLIB
#define MARGE_MIN 50 // Distance minimale entre sommets
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

void DrawArrow(Vector2 start, Vector2 end, float arrowLength, float arrowWidth, float rayon, Color color)
{
    float angle = atan2f(end.y - start.y, end.x - start.x);

    Vector2 from = {
        start.x + rayon * cosf(angle),
        start.y + rayon * sinf(angle)};

    Vector2 to = {
        end.x - rayon * cosf(angle),
        end.y - rayon * sinf(angle)};

    DrawLineEx(from, to, 2.0f, color);

    Vector2 tip = to;
    Vector2 baseCenter = {
        tip.x - arrowLength * cosf(angle),
        tip.y - arrowLength * sinf(angle)};

    Vector2 left = {
        baseCenter.x + (arrowWidth / 2) * sinf(angle),
        baseCenter.y - (arrowWidth / 2) * cosf(angle)};

    Vector2 right = {
        baseCenter.x - (arrowWidth / 2) * sinf(angle),
        baseCenter.y + (arrowWidth / 2) * cosf(angle)};

    DrawTriangle(tip, left, right, color);
}

float distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void placer_sommets(Graphe *G)
{
    if (!G || !G->sommets_TAB)
        return;

    int n = G->sommets_TAB->n_sommets;
    for (int i = 0; i < n; i++)
    {
        int essais = 0;
        bool position_ok = false;
        int x, y;

        while (!position_ok && essais < 1000)
        {
            x = MARGE_MIN + rand() % (LARGEUR_FENETRE - 2 * MARGE_MIN);
            y = MARGE_MIN + rand() % (HAUTEUR_FENETRE - 2 * MARGE_MIN);
            position_ok = true;

            for (int j = 0; j < i; j++)
            {
                float d = distance(x, y, G->sommets_TAB->sommets[j].x, G->sommets_TAB->sommets[j].y);
                if (d < MARGE_MIN)
                {
                    position_ok = false;
                    break;
                }
            }
            essais++;
        }

        G->sommets_TAB->sommets[i].x = x;
        G->sommets_TAB->sommets[i].y = y;
    }
}

void afficher_graphe_raylib(Graphe *G)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Graphe interactif - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int n = G->sommets_TAB->n_sommets;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j && G->chemins[i][j].distance > 0)
                {
                    Vector2 a = {G->sommets_TAB->sommets[i].x, G->sommets_TAB->sommets[i].y};
                    Vector2 b = {G->sommets_TAB->sommets[j].x, G->sommets_TAB->sommets[j].y};

                    Color arcColor;
                    if (G->chemins[i][j].etat <= 0 || G->chemins[i][j].capacité <= 0)
                        arcColor = RED;
                    else if (G->chemins[i][j].etat < 100)
                        arcColor = ORANGE;
                    else
                        arcColor = DARKGRAY;

                    DrawArrow(a, b, 10.0f, 6.0f, 12.0f, arcColor);
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            Sommet s = G->sommets_TAB->sommets[i];
            Color couleur = (s.ville.etat == 1) ? BLUE : (s.hopitale.etat == 1) ? YELLOW
                                                     : (s.entrepot.etat == 1)   ? PURPLE
                                                                                : RED;

            DrawCircle(s.x, s.y, 12, couleur);
            DrawText(obtenir_nom_sommet(&s), s.x + 16, s.y - 20, 10, BLACK);
        }

        // --- Légende ---
        int legendX = 20;
        int legendY = 20;

        DrawRectangle(legendX - 10, legendY - 10, 160, 140, Fade(LIGHTGRAY, 0.5f));
        DrawRectangleLines(legendX - 10, legendY - 10, 160, 140, DARKGRAY);

        DrawCircle(legendX, legendY, 6, BLUE);
        DrawText("Ville", legendX + 15, legendY - 6, 10, BLACK);

        DrawCircle(legendX, legendY + 20, 6, GREEN);
        DrawText("Hopital", legendX + 15, legendY + 14, 10, BLACK);

        DrawCircle(legendX, legendY + 40, 6, PURPLE);
        DrawText("Entrepot", legendX + 15, legendY + 34, 10, BLACK);

        DrawLine(legendX - 5, legendY + 65, legendX + 10, legendY + 65, DARKGRAY);
        DrawText("Route OK", legendX + 15, legendY + 58, 10, BLACK);

        EndDrawing();
    }

    CloseWindow();
}

void afficher_graphe_raylib_dijkstra(Graphe *G)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Graphe interactif - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int n = G->sommets_TAB->n_sommets;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j && G->chemins[i][j].distance > 0)
                {
                    Vector2 a = {G->sommets_TAB->sommets[i].x, G->sommets_TAB->sommets[i].y};
                    Vector2 b = {G->sommets_TAB->sommets[j].x, G->sommets_TAB->sommets[j].y};

                    Color arcColor;
                    if (G->chemins[i][j].etat <= 0 || G->chemins[i][j].capacité <= 0)
                        arcColor = RED;
                    else if (G->chemins[i][j].etat < 100)
                        arcColor = ORANGE;
                    else
                        arcColor = DARKGRAY;

                    DrawArrow(a, b, 10.0f, 6.0f, 12.0f, arcColor);
                }
            }
        }

        // 2. Mettre en avant le chemin optimal trouvé
        for (int k = 0; k < longueur_chemin - 1; k++)
        {
            int i = chemin_court[k];
            int j = chemin_court[k + 1];

            Vector2 a = {G->sommets_TAB->sommets[i].x, G->sommets_TAB->sommets[i].y};
            Vector2 b = {G->sommets_TAB->sommets[j].x, G->sommets_TAB->sommets[j].y};

            DrawArrow(a, b, 10.0f, 6.0f, 12.0f, GREEN); // surbrillance verte
        }

        for (int i = 0; i < n; i++)
        {
            Sommet s = G->sommets_TAB->sommets[i];
            Color couleur = (s.ville.etat == 1) ? BLUE : (s.hopitale.etat == 1) ? YELLOW
                                                     : (s.entrepot.etat == 1)   ? PURPLE
                                                                                : RED;

            DrawCircle(s.x, s.y, 12, couleur);
            DrawText(obtenir_nom_sommet(&s), s.x + 16, s.y - 20, 10, BLACK);
        }

        // --- Légende ---
        int legendX = 20;
        int legendY = 20;

        DrawRectangle(legendX - 10, legendY - 10, 160, 140, Fade(LIGHTGRAY, 0.5f));
        DrawRectangleLines(legendX - 10, legendY - 10, 160, 140, DARKGRAY);

        DrawCircle(legendX, legendY, 6, BLUE);
        DrawText("Ville", legendX + 15, legendY - 6, 10, BLACK);

        DrawCircle(legendX, legendY + 20, 6, GREEN);
        DrawText("Hopital", legendX + 15, legendY + 14, 10, BLACK);

        DrawCircle(legendX, legendY + 40, 6, PURPLE);
        DrawText("Entrepot", legendX + 15, legendY + 34, 10, BLACK);

        DrawLine(legendX - 5, legendY + 65, legendX + 10, legendY + 65, DARKGRAY);
        DrawText("Route OK", legendX + 15, legendY + 58, 10, BLACK);

        DrawLine(legendX - 5, legendY + 85, legendX + 10, legendY + 85, ORANGE);
        DrawText("Route endommagee", legendX + 15, legendY + 78, 10, BLACK);

        DrawLine(legendX - 5, legendY + 105, legendX + 10, legendY + 105, RED);
        DrawText("Route detruite", legendX + 15, legendY + 98, 10, BLACK);

        DrawLine(legendX - 5, legendY + 125, legendX + 10, legendY + 125, GREEN);
        DrawText("Chemin le plus coourt", legendX + 15, legendY + 118, 10, BLACK);

        EndDrawing();
    }

    CloseWindow();
}

// Tableau de couleurs disponibles pour les groupes
static Color couleurs_groupes[] = {
    BLUE, ORANGE, PURPLE, MAROON, LIME, SKYBLUE, DARKBLUE, GOLD};
#define NB_COULEURS (sizeof(couleurs_groupes) / sizeof(Color))

extern int *identifier_groupes_sommets(Graphe *G, int *nb_groupes);

void afficher_groupes_connexes(Graphe *G)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Groupes connexes - Raylib");
    SetTargetFPS(60);

    int nb_groupes = 0;
    int *groupes = identifier_groupes_sommets(G, &nb_groupes);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Affichage des routes
        for (int i = 0; i < G->sommets_TAB->n_sommets; i++)
        {
            for (int j = i + 1; j < G->sommets_TAB->n_sommets; j++)
            {
                if (G->chemins[i][j].etat > 0 && G->chemins[i][j].distance > 0)
                {
                    Vector2 a = {G->sommets_TAB->sommets[i].x, G->sommets_TAB->sommets[i].y};
                    Vector2 b = {G->sommets_TAB->sommets[j].x, G->sommets_TAB->sommets[j].y};
                    DrawLineV(a, b, GRAY);
                }
            }
        }

        // Affichage des sommets avec la couleur du groupe
        for (int i = 0; i < G->sommets_TAB->n_sommets; i++)
        {
            Vector2 pos = {G->sommets_TAB->sommets[i].x, G->sommets_TAB->sommets[i].y};
            int groupe_id = groupes[i];
            Color c = couleurs_groupes[groupe_id % NB_COULEURS];
            DrawCircleV(pos, 12, c);
            DrawText(obtenir_nom_sommet(&G->sommets_TAB->sommets[i]), pos.x + 14, pos.y - 8, 10, BLACK);
        }

        // Légende (facultatif)
        DrawText("Appuyez sur ECHAP pour quitter", 10, screenHeight - 30, 12, DARKGRAY);

        EndDrawing();
    }

    free(groupes);
    CloseWindow();
}

PROJET S2 - SIMULATION DE GRAPHE INTERACTIF
===========================================

Auteurs : Aipe Darwing DEGNI, Nathanael MBOULE MOUANDJO, Samuel DURANDEAU DIT MEGES
Date    : [Mai 2025]
Filière : Ecole d'ingénieur - ESIEA
Module  : Graphes et applications

------------------------------------------------------------
DESCRIPTION
------------------------------------------------------------

Ce projet implémente une simulation graphique d'un graphe orienté, 
modélisant un réseau de villes, hôpitaux, entrepôts et routes.

Fonctionnalités principales :
- Affichage interactif avec Raylib
- Visualisation des routes détruites ou endommagées
- Détection et affichage des groupes connexes
- Représentation des bâtiments et types de sommets
- Calcul de plus courts chemins (optionnel)

------------------------------------------------------------
STRUCTURE DU DOSSIER
------------------------------------------------------------

MON_PROJET/
├── src/           : Tous les fichiers .c (code source)
├── include/       : Tous les fichiers .h (headers)
├── build/         : Fichiers objets (.o) générés (temporaire)
├── bin/           : Exécutable final (programme.exe)
├── data/          : Fichiers de données éventuels (cartes, graphes)
├── Makefile       : Fichier de compilation
└── README.txt     : Ce fichier d’explication

------------------------------------------------------------
PRÉREQUIS
------------------------------------------------------------

- Compiler avec GCC (MinGW ou MSYS2 recommandé sous Windows)
- Bibliothèque Raylib installée
- Compilation via le Makefile fourni

------------------------------------------------------------
INSTRUCTIONS DE COMPILATION
------------------------------------------------------------

1. Ouvrir un terminal dans le dossier du projet
2. Taper la commande :

   make

3. Le programme sera compilé dans : bin/programme

------------------------------------------------------------
INSTRUCTIONS D’EXÉCUTION
------------------------------------------------------------

Dans le terminal :

   ./bin/programme        (sous Git Bash ou Linux)
   bin\programme.exe      (sous Windows CMD)
   .\bin\programme.exe    (sous PowerShell)

Le programme ouvre une fenêtre graphique avec les graphes simulés.

------------------------------------------------------------
NETTOYAGE
------------------------------------------------------------

Pour supprimer les fichiers objets (.o) :

   make clean

Pour supprimer également l’exécutable :

   make mrproper

------------------------------------------------------------
AUTEURS / CONTRIBUTIONS
------------------------------------------------------------

- [Aipe Darwing DEGNI] : Mission 3 et montage du projet.
- [Nathanael MBOULE MOUANDJO] : Mission 1 et 2.
- [Samuel DURANDEAU DIT MEGES] : Mission 5 et affichage via Raylib

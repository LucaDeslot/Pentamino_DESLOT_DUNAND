# PENTAMINO
## Présentation du jeu
Le programme est une adaptation du jeu de plateau Pentamino en jeu vidéo.
Le joueur doit remplir une grille avec des pièces qui lui sont imposées. Le jeu fonctionne sur la base du Drag&Drop c'est à dire
que le joueur devra glisser les différentes pièces sur le plateau afin de remplir la grille.

## Langages et librairies
Le programme est exclusivement développé en C avec la librairie SDL2 (qu'il convient d'installer).

## Installation et Lancement
Disponible lorsque le jeu sera en phase de test. 

## Equipe
Projet développé par DUNAND Nathan et DESLOT Luca

## Rapport hebdomadaire
#### *Semaine du 19 au 25 octobre*
Commencement du développement avec la mise en place des différents fichiers du projet et configuration du Git. Début du développement avec la fonction qui permet de mettre dans un tablau 3D toutes les pièces d'un fichier txt.
#### *Semaine du 26 octobre au 1er novembre (vacances de la Toussaint)*
Installation de la SDL2 sur le projet, résolution des problèmes de compatibilité entre la SDL2 et CLion (notre IDE). Implémentation de la fonction qui permet d'afficher une pièce sur un écran avec variables globales qui permettront de pouvoir régler dynamiquement la mise en page.
#### *Semaine du 9 au 16 novembre*
Debug d'une partie du code, et allocation dynamique de plusieurs tableaux multidimensionnels. Début de l'implémentation de l'affichage de toutes les pièces sur une même fenêtre avec création de variables (globales ou non) qui permettent de rgler la mise en page dynamiquement.
#### *Semaine 16 au 23 novembre*
Finalisation de l'implémentation de la fonction qui affiche toutes les pièces du fichier txt sur une seule fenêtre. Ajout de variables globales ou non qui permettent de mettre en page dynamiquement l'affichage des pièces. Début de l'implémentation de l'affichage du plateau de jeu.

#### *Semaine du 23 au 30 novembre*
Commencement du drag and drop pour déplacer les pièces (drag fonctionnel) sur la grille, affichage des pièces et du plateau de jeu sur une même fenêtre.

#### *Semaine du 30 au 7 décembre*
Ajout de variables globales pour dynamiser le programme, ajout d'éléments graphiques à l'interface de jeu. Modifications mineures dans le code. Ajout de la fonction de détection de la pièce sur le plateau de jeu. Ajout de la fonction setDisplayPieces() qui permet d'afficher les pièces dans la zone qui leur est réservée : problème avec le drag and drop.

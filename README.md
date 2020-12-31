# PENTAMINO
## Présentation du jeu
Le programme est une adaptation du jeu de plateau Pentamino en jeu vidéo.
Le joueur doit remplir une grille avec des pièces qui lui sont imposées. Le jeu fonctionne sur la base du Drag&Drop c'est à dire
que le joueur devra glisser les différentes pièces sur le plateau afin de remplir la grille.

### Comment jouer ?
Le but du jeu est de compléter entièrement la grille de 6 lignes par 10 colonnes. Pour cela, vous disposez de 12 pièces, non pivotables, que vous devez disposer sur la grille en utilisant votre souris. Un clic sur une pièce, et vous vous en saisissez, un deuxième clic à un emplacemnt valide pour cette pièce et vous la déposez sur la grille. Pour vous saisir d'une autre pièce, cliquez à côté de la grille pour redéposer la pièce en haut de la fenêtre. Trois niveaux sont disponibles, tous sont réalisables, vous disposez de la correction du premier niveau dans les fichiers sources. Pour sélectionner un autre niveau, cliquez sur son numéro. Une fois que vous avez complété un niveau, une fenêtre de victoire s'affiche. Si vous voulez tenter un autre niveau, il faut fermer cette fenêtre et relancer le jeu.

## Langages et librairies
Le programme est exclusivement développé en C avec la librairie SDL2 (qu'il convient d'installer).

## Installation et Lancement
Se positionner dans le dossier de votre choix (le jeu sera installé ici).<br>
```
sudo apt-get install libsdl2-dev
git clone https://github.com/LucaDeslot/Pentamino_DESLOT_DUNAND.git
cd Pentamino_DESLOT_DUNAND/
make
./main
```

## Equipe
Projet développé par DUNAND Nathan et DESLOT Luca.

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

#### *Semaine du 7 au 14 décembre*
Amélioration du drag and drop, ajout du magnétisme, corrections de bugs, on peux reprendre une pièce sur le tableau de jeu, implémentation de SDL_ttf, commencement d'un menu de naviguation entre les niveaux.

#### *Semaine du 14 au 21 décembre*
Drag and drop fonctionnel.

#### *Vacances de Noel*
Ajout de la possibilité de déposer une pièce en dehors de la grille. Implémentation de deux nouveaux niveaux, avec interface cliquable. Possiblité de changer de niveau en cours de jeu. Ajout de la victoire avec message. Réglage des problèmes mémoires avec Valgrind, ajout du makefile, suppression de la SDL_TTF dû à des difficultés. Jeu fonctionnel.

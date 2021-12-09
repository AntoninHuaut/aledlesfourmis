* Global
    * Système de configuration (fichier JSON)
        * Toutes les variables du jeu sont configurables
    * Fichier GNUPlot
    * TPS du jeu configurable
    * 2 threads :
        * Thread graphique
        * Thread de jeu (synchronisé via un mutex)

* Interface graphique
    * Toutes les images (32x32) dans un tileset
    * MinFPS / maxFPS configurable
    * Système de couches visuelles
        * Première couche : cases du plateau statiques
        * Seconde couche : nourritures / colonies
        * Troisième couche : fourmis / nuage (les cases non visitées sont affichées avec un nuage)
    * Gestion dynamique de la résolution d'affichage (affichage de bandes noirs pour garder un aspect/ratio)
    * Impossibilité de sortir de la map (on aperçoit juste les bordures noirs lorsqu'on dézoom)
    * Raccourcies :
        * Espace => Toggle la pause du jeu (+ dump gnuplot)
        * C => Recentre sur la colonie
        * Touches "flèches" : Permet de se déplacer dans la map *via le clavier*
        * Clic de souris + slide : Permet de se déplacement dans la map *via la souris*
        * Shift : Accélère le déplacement lors du déplacement dans la map via les touches "flèches"
        * Molette de la souris : Zoom/Dézoom la map

* Terrain
    * Le terrain mesure 211x201 avec la reine et la colonie en son centre
    * Une case ne peut contenir que 12 fourmis (0 si obstacle, 100 pour la colonie)
    * Les obstacles sont présents sur 30% du terrain
        * 50% sont d'une case
        * 30% de deux cases
        * 10% de trois cases
        * 5% de quatre cases
        * 4% de cinq cases
        * 1% de six cases
    * Il existe 2 gros stock de nourritures sur deux coins de la map, chacun répartie en 5 piles de 20 000 unités de
      nourriture
    * Il existe 0.02% de petit stock de nourritures, chacun de 100 unités de nourriture
    * La colonie s'étend si il n'y a plus de place pour accueillir toutes les fourmis (si total fourmis > 100 \*
      nbCaseColonie)

* Fourmis
    * Elles mangent depuis la colonie à distance (sauf les esclavagistes)
    * Elles peuvent mourir
        * De vieillesse : un an pour les fourmis classiques et 10 ans pour la reine
        * De faim, elles mangent 0.1% de nourriture pour une fourmie et 1% pour la reine
            * Les fourmis esclavagistes peuvent survivre 10j sans manger
    * Ouvrières
        * Elles mangent d'abord leur stock
        * Elles sont mineurs au début puis deviennent majeurs après 14 jours
        * Elles partent chercher la nourriture (dans les cases explorées) pour la ramener à la colonie
        * Elles déposent des phéromones (%) lorsqu'elles ont de la nourriture
        * Elles suivent la phéromone au sol
        * Elles déposent leur nourriture si elles meurent
    * Reine
        * Elle a 2 larves / jour suivant les proba de l'énoncé (et la 1ère = éclaireur)
        * Elle peut se faire attaquer et ne pas en produire
        * Elle vit au centre de la colonie, elle ne bouge pas
    * Eclaireurs
        * Elles sont mineurs au début puis deviennent majeurs après 2 jours
        * Elles explorent les cases non explorées en priorité (et non au hasard)
    * Soldats
        * Elles partent traquer les exclavagistes (dans les cases explorées) pour les tuer
        * Elles partent en direction de la fourmilière au bout de 100 jours
    * Esclavagistes
        * Elles apparaissent dans les coins
        * Elles se dirigent vers la fourmillière puis repartent d'où elles viennent
        * Elles capturent les larves pour les ramener chez elles
        * Elles peuvent manger la nourriture de la fourmillière si elles sont sur une case de la colonie
        * Si elles meurent, les larves capturées seront réintégrées dans la colonie

* Jeu
    * La colonie commence avec 20 unités de nourriture
    * Un tour correspond à une heure de simulation
    * Phéromone
        * Limité à 1000 par case
        * S'évapore à 0.5%
        * Se disperse à 0.02%
        * Une ouvrirère ne peut posséder que 500 phéromones, qui est restauré lors de la visite de la colonie
    * Les esclavagistes apparaissent aléatoirement tous les 5 à 10 jours
    * GNUPlot
        * Le fichier gnuplot.txt est généré lorsque la reine meurt ET / OU lorsque le jeu est mis en pause via le bouton
          ESPACE
        * Le fichier gnuplot.txt est écrasé à chaque lancement de partie
        * Chaque tour de jeu enregistre des paramètres pour le fichier GNUPlot :
          \<tickActuel> \<nbFourmisTotal> \<nbSoldat> \<nbEsclavagiste> \<nbOuvriere> \<nbEclaireur>
          \<nourritureColonie>

* Problèmes rencontrés
    * Optimisation des déplacements des fourmis
    * Synchronisation thread graphique / jeu (UI accède à un élément en cours de suppression dans le jeu)
    * Gestion du tileset / vertices de l'UI
    * Aidés par StackOverflow, OpenClassRoom, doc SFML, doc C++


* Problèmes/Bug connus
    * Les ticks de jeu sont plus lents à partir d'un certain tick (quand y'a beaucoup de fourmis, mais ça reste OK)
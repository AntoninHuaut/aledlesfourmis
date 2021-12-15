# Présentation

Ce projet est une application écrite en C++ avec la bibliothèque graphique SFML. Elle permet de simuler l'évolution
d'une colonie de fourmis, son expansion, sa recherche de nourriture et sa défense fasse à une colonie ennemie dans un
environnement limité. L'objectif est de mettre en évidence l'organisation des fourmis pour trouver des chemins, les plus
courts possibles, qui mènent vers des stocks de nourriture.

Ce projet a été développé dans le cadre d'un projet scolaire à l'ENSICAEN par :

* Quentin Fontaine
* Antonin Huaut

# Installation

## SFML

SFML est nécessaire pour compiler l'application. L'application a été développée avec la version 2.5.1 de SFML.

### Windows

> Cette version de SFML n'est compatible qu'avec la version 7.3.0 de MinGW

Rendez-vous sur la page de téléchargement de SFML [(ici)](https://www.sfml-dev.org/download/sfml/2.5.1/).

Téléchargez la version 7.3.0 de
MinGW ["MinGW Builds 7.3.0 (64-bit)"](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download)
puis
SFML ["GCC 7.3.0 MinGW (SEH) - 64-bit"](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip).

Extrayez ces deux archives dans un dossier. Il faut ajouter à la variable d'environnement PATH de Windows les dossiers
\bin de MinGW et SFML.

Une fois les variables d'environnements définies, lancez un terminal à la racine du dossier et tapez :
> ./compileAndRun.bat

Pour compiler et lancer l'application

### Linux

> Nécessite build-essential, cmake, libsfml-dev

Ne fonctionne pas avec le serveur graphique X.Org : La boucle d'évènement doit être thread-synchro avec la boucle de
rendue.  
Si on fait ça, l'application est trop ralentie.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// Initialisation /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Initialisation de la structure maitre
Program* InitMain(){
	Program* startup = malloc(sizeof(Lib) * 1);
	startup->loadedFileName = NULL;
	startup->f = NULL;
	startup->totalWords = 0;
	return startup;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// Point d'entree /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(){
    //Initialise la structure de base du programme
    Program* startup = InitMain();
    //Appel du "constructeur" pour initialiser les tableaux dictionnaire
    InitLibrary(startup);

    do{
        char choice;
        printf("------- Dictionnaire C -------\n\n");
        printf("Fichier charge : ");
        if (startup->loadedFileName == NULL) {
            printf("Aucun fichier charge\n");
        }else {
            printf("%s\n", startup->loadedFileName);
        }
        printf("Nombre total de mots : %i\n\n", startup->totalWords);
        printf("1. Fichier du dictionnaire\n2. Gestion du dictionnaire\n3. Quitter\nChoix : ");
        scanf("%c", &choice);
        switch(choice){
            case '1':
                FileMenu(startup);
                break;
            case '2':
                DicoMenu(startup);
                break;
            case '3':
                return 0;
                break;
        }
    }while(1);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Menus //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Menu de gestion des fichiers
void FileMenu(Program* startup){
    char choice;
    do{
        system("cls");
        printf("     ------- Dictionnaire C -------\n------- Gestion des dictionnaires -------\n\n");
        printf("1. Charger un dictionnaire\n2. Retour au menu principal\nChoix : ");
        scanf("%c", &choice);
        switch(choice){
            case '1':
                LoadFile(startup);
                break;
            case '2':
                system("cls");
                break;
        }
    }while(choice != '1' && choice != '2');

}

//Menu de correction/proposition
void DicoMenu(Program* startup){
    if(startup->f == NULL){
        system("cls");
        printf("/!\\ : Aucun fichier dictionnaire charge, veuillez charger un fichier dictionnaire !\n\n");
        return;
    }
    char choice;
    do{
        system("cls");
        printf("     ------- Dictionnaire C -------\n------- Manipulation des dictionnaires -------\n\n");
        printf("1. Liste des mots semblables : dictionnaire/fichier\n2. Mots du fichier non-inclus dans le dictionnaire et propositions de mots\n4. Retour au menu principal\nChoix : ");
        scanf("%c", &choice);
        switch(choice){
            case '1':
                WordsNotInDictionary(startup);
                break;
            case '2':

                break;
            case '3':

                break;
            case '4':
                system("cls");
                break;
        }
    }while(choice != '1' && choice != '2' && choice != '3' && choice != '4');
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

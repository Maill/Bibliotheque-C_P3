#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

void LoadFile(Program* startup){
    char* fileName = malloc(sizeof(char) * 100);
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Charger un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", fileName);
    strcat(fileName, ".dico");
    FILE* f = fopen(fileName, "r+");
    if(f == NULL){
        if(startup->f != NULL){
            system("cls");
            printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
            return;
        }
        system("cls");
        printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
        fclose(f);
        return;
    }
    fclose(f);
    startup->loadedFileName = fileName;
    startup->f = fopen(startup->loadedFileName, "a+");
    rewind(startup->f);
    CleanDico(startup);
    FillDicoFromFile(startup);
    system("cls");
}

//Crée un fichier dictionnaire en fonction d'un texte dans un fichier .txt
void BuildALibFromText(Program* startup){
    char* fileName = malloc(sizeof(char) * 100);
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Charger un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", fileName);
    strcat(fileName, ".txt");
    FILE* f = fopen(fileName, "r+");
    if(f == NULL){
        if(startup->f != NULL){
            system("cls");
            printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
            return;
        }
        system("cls");
        printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
        fclose(f);
        return;
    }
    fclose(f);
    startup->loadedFileName = fileName;
    startup->f = fopen(startup->loadedFileName, "a+");
    rewind(startup->f);
    FillDicoFromTextFile(startup);
    system("cls");
}

int IsFileEmpty(FILE *file){
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        rewind(file);
        return 1;
    }
    rewind(file);
    return 0;
}

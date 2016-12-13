#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include <ctype.h>

//Define conçu pour la fonction Levenshtein
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
/*Reminder
    //Écriture simple
    (a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c));
    //Écriture développée
    if (a < b){
        if (a < c){
            a;
        }else{
            b;
        }
    }else{
        if (b < c){
            b;
        }else{
            c;
        }
    }
*/

//Initialisation du tableau de la bibliotheque
void InitLibrary(Program* startup){
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	startup->dictionary = malloc(sizeof(Lib) * 26);
	int i;
	for (i = 0; i < 26; i++) {
		startup->dictionary[i].letter = alphabet[i];
		startup->dictionary[i].capacity = INIT_CAPACITY;
		startup->dictionary[i].size = 0;
		startup->dictionary[i].words = malloc(sizeof(char*) * startup->dictionary[i].capacity);
	}
}

//Fonction de comparaison pour qsort()
static int Compare(const void *a, const void *b){
   //Définie des pointeurs type et initialise avec les paramètres
   const char *pa = *(const char**)a;
   const char *pb = *(const char**)b;

   //Évalue et retourne l'état de l'évaluation (tri croissant)
   return strcmp(pa, pb);
}

//Parcourt et compare les mots entre eux en ne retournant que la première occurence
void ReplaceWordsInDocument(Program* startup){
    system("cls");
    char* fileName = malloc(sizeof(char) * 50);
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Liste des mots semblables : dictionnaire/fichier -------\n\n");
    printf("Nom du fichier texte : ");
    scanf("%s", fileName);
    strcat(fileName, ".txt");
    FILE* textFile = fopen(fileName, "r+");
    FILE* tempFile = fopen("tempFile.txt", "w+");
    if(CheckIfFileExists(startup, textFile) == 0){
        return;
    }
    char ch = 0;
    int line = 1;
    int i = 0;
    int count = 0;
    char* oldWord = malloc(sizeof(char) * 50);
    char* newWord = malloc(sizeof(char) * 50);
    while((ch = fgetc(textFile)) != EOF){
        if(isalpha(ch)){
            oldWord[i] = ch;
            i++;
        }else{
            //printf("\n%c\n",oldWord[i-1]);
            int checkUpper = 0;
            if(oldWord[0] >= 65 && oldWord[0] <= 90){ //Si le mot possède une majuscule au début (premier mot d'une phrase ou nom/prénom)
                checkUpper = 1;
            }
            ToLowerCase(oldWord);
            int indexLib = oldWord[0] - 97;
            if(CheckIfExists(startup, indexLib, oldWord) == 0){ //Si le mot n'existe pas
                printf("%i", count++);
                newWord = CompareWordsToReplace(startup, oldWord, 1);
                if(checkUpper == 1){
                    newWord[0] += 32;
                }
                printf("NewWord : %s\n", newWord);
                fprintf(tempFile, newWord);
                newWord = realloc(newWord, sizeof(char) * 50);
            }else{
                printf("OldWord : %s\n", oldWord);
                fprintf(tempFile, oldWord);
                oldWord = realloc(oldWord, sizeof(char) * 50);
            }
            i = 0;
        }
    }
    free(newWord);
    free(oldWord);
    free(fileName);
    fclose(textFile);
    fclose(tempFile);
}

//Étape 3 de la partie 3 : construire automatiquement un fichier corrigé, en remplaçant les mots erronés par la première suggestion de la liste (seuil une lettre maximum)
char* CompareWordsToReplace(Program* startup, char* word, int toleranceThreshold){ //toleranceThreshold = seuil de tolérance
    char* closeWord = malloc(sizeof(char) * 50);
    int i;
    int j;
    for(i = 0; i < 26; i++){
        for(j = 0; j < startup->dictionary[i].size; j++){
            if(strcmp(word, startup->dictionary[i].words[j]) == 0){ //Si les 2 mots comparés sont identiques, on ignore et on continue
                continue;
            }else if((Levenshtein(word, startup->dictionary[i].words[j]) <= toleranceThreshold) &&
                     (Levenshtein(word, startup->dictionary[i].words[j]) >= 1)){ //Si le résultat de "Levenshtein" retourne un nombre <= au seuil et >= à 1
                closeWord = startup->dictionary[i].words[j];
                return closeWord;
            }
        }
    }
    return closeWord;
}

//Étape 2 de la partie 3 : affiche la liste des mots n'existant pas dans le dictionnaire et proposer une liste de mots proches (seuil deux lettres maximum) pour chacun d'entre eux
void SimilarWordsToWord(Program* startup){
    system("cls");
    char* fileName = malloc(sizeof(char) * 50);
    char* word = malloc(sizeof(char) * 50);
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Liste des mots semblables : dictionnaire/fichier -------\n\n");
    printf("Nom du fichier texte : ");
    scanf("%s", fileName);
    strcat(fileName, ".txt");
    FILE* textFile = fopen(fileName, "r");
    if(CheckIfFileExists(startup, textFile) == 0){ //Si le fichier n'existe pas
        return;
    }
    while(fscanf(textFile, "%50[a-zA-Z-']%*[^a-zA-Z'-]", word) != -1){
        ToLowerCase(word);
        int indexLib = word[0] - 97;
        if(CheckIfExists(startup, indexLib, word) == 0 && strlen(word) > 1){ //Si le mot n'existe pas
            printf("%s\n", word);
            CompareWords(startup, word, 2);
        }
    }
    free(word);
    free(fileName);
    fclose(textFile);
}

//Étape 1 de la partie 3 : affiche la liste des mots du fichier n'existant pas dans le dictionnaire, mais n'affiche pas la ligne des mots (TODO)
void WordsNotInDictionary(Program* startup){
    system("cls");
    char* fileName = malloc(sizeof(char) * 50);
    char* word = malloc(sizeof(char) * 50);
    //int line = 1;
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Liste des mots semblables : dictionnaire/fichier -------\n\n");
    printf("Nom du fichier texte : ");
    scanf("%s", fileName);
    strcat(fileName, ".txt");
    FILE* textFile = fopen(fileName, "r");
    if(CheckIfFileExists(startup, textFile) == 0){
        return;
    }
    while(fscanf(textFile, "%50[a-zA-Z]%*[^a-zA-Z]", word) != -1){ //Si le mot n'existe pas
        ToLowerCase(word);
        int indexLib = word[0] - 97;
        if(CheckIfExists(startup, indexLib, word) == 0){
            printf("%s\n", word); //TODO : Comptage des lignes
        }
    }
    free(word);
    free(fileName);
    fclose(textFile);
}

//Parcourt et compare les mots entre eux
void CompareWords(Program* startup, char* word, int toleranceThreshold){ //toleranceThreshold = seuil de tolérance
    char** closeWords = malloc(sizeof(char*));
    int i;
    int j;
    int k;
    int countCW = -1; //Nombre de mots dans "CloseWords"
    int sizeCW = 0;
    for(i = 0; i < 26; i++){
        for(j = 0; j < startup->dictionary[i].size; j++){
            if(strcmp(word, startup->dictionary[i].words[j]) == 0){ //Si les 2 mots comparés sont identiques, on ignore et on continue
                continue;
            }else if((Levenshtein(word, startup->dictionary[i].words[j]) <= toleranceThreshold) &&
                     (Levenshtein(word, startup->dictionary[i].words[j]) >= 1)){ //Si le résultat de "Levenshtein" retourne un nombre <= au seuil et >= à 1
                countCW++;
                sizeCW++;
                closeWords = realloc(closeWords, sizeof(char*) * (sizeCW * 2));
                closeWords[countCW] = startup->dictionary[i].words[j];
            }
        }
    }
    //Affichage des mots similaires
    for(k = 0; k <= countCW; k++){
        printf("\t - %s\n", closeWords[k]);
    }
    Clean2DArray(closeWords, countCW);
}

//Calcule la "distance" entre 2 mots selon le seuil de tolérance
int Levenshtein(char* str1, char* str2){
     int str1Length;
     int str2Length;
     int x;
     int y;
     int lastChar;
     int oldChar;

     str1Length = strlen(str1);
     str2Length = strlen(str2);

     int column[str1Length+1];

    for(y = 1; y <= str1Length; y++){ //Assigne un nombre à chaque caractère du mot
        column[y] = y;
    }
    for(x = 1; x <= str2Length; x++){
        column[0] = x;
        for(y = 1, lastChar = x - 1; y <= str1Length; y++){
            oldChar = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastChar + (str1[y-1] == str2[x-1] ? 0 : 1)); //Algorithme de Levenshtein : voire documentation technique
            lastChar = oldChar;
        }
    }
    return(column[str1Length]);
}

//Remplace la capacité mémoire du tableau de mots par lettre
void OverrideCapacity(Program* startup, int indexLib){
    startup->dictionary[indexLib].capacity *= 2;
    startup->dictionary[indexLib].words = realloc(startup->dictionary[indexLib].words, sizeof(char*) * startup->dictionary[indexLib].capacity);
}

//Trie le tableau de mots en mémoire par ordre alphabétique croissant
void SortDico(Program* startup, int indexLib){
    qsort(startup->dictionary[indexLib].words, startup->dictionary[indexLib].size, sizeof(char*), Compare);
}

//Remplit le tableau lors de l'initialisation d'un fichier
void FillDicoFromFile(Program* startup){
    if(IsFileEmpty(startup->f) == 1){
        CountTotalWords(startup);
        return;
    }
    printf("%s", "Chargement du fichier en cours...");
    while(!feof(startup->f) && !ferror(startup->f)){
        char* word = malloc(sizeof(char) * 30);
        fscanf(startup->f, "%s", word);
        ToLowerCase(word);
        int indexLib = word[0] - 97;
        int sizeLib = startup->dictionary[indexLib].size;
        if(sizeLib == (startup->dictionary[indexLib].capacity - 3)){
            OverrideCapacity(startup, indexLib);
        }
        if(CheckIfExists(startup, indexLib, word) == 0){
            startup->dictionary[indexLib].words[sizeLib] = word;
            startup->dictionary[indexLib].size++;
        }
    }
    CountTotalWords(startup);
    int i;
    for(i = 0; i < 26; i++){
        SortDico(startup, i);
    }
    WriteOnFile(startup);
    printf("\n-- Le fichier a ete charge. --\n\n");
}

//Remplit le tableau à l'aide d'un texte
void FillDicoFromTextFile(Program* startup){
    char* nameOutExt;
    while(!feof(startup->f) && !ferror(startup->f)){
        char* word = malloc(sizeof(char) * 30);
        fscanf(startup->f, "%30[a-zA-Z-']%*[^a-zA-Z'-]", word);
        ToLowerCase(word);
        int indexLib = word[0] - 97;
        int sizeLib = startup->dictionary[indexLib].size;
        if(sizeLib == (startup->dictionary[indexLib].capacity - 3)){
            OverrideCapacity(startup, indexLib);
        }
        if(CheckIfExists(startup, indexLib, word) == 0){
            startup->dictionary[indexLib].words[sizeLib] = word;
            startup->dictionary[indexLib].size++;
        }
    }
    nameOutExt = strtok(startup->loadedFileName, ".");
    strcat(nameOutExt, ".dico");
    startup->loadedFileName = nameOutExt;
    CountTotalWords(startup);
    int i;
    for(i = 0; i < 26; i++){
        SortDico(startup, i);
    }
    WriteOnFile(startup);
}

//Nettoie les valeurs du dictionnaire en mémoire
void CleanDico(Program* startup){
    int i = 0;
    for(; i < 26; i++){
        int j;
        for(j = 0; j < startup->dictionary[i].size; j++){
            free(startup->dictionary[i].words[j]);
        }
        free(startup->dictionary[i].words);
        startup->dictionary[i].size = 0;
        startup->dictionary[i].capacity = INIT_CAPACITY;
        startup->dictionary[i].words = malloc(sizeof(char*) * startup->dictionary[i].capacity);
    }
    startup->totalWords = 0;
}

//Libération de la mémoire d'un tableau 2D
void Clean2DArray(char** wordsArray, int count){
    int l;
    for (l = 0; l <= count; l++){
        free(wordsArray[l]);
    }
    free(wordsArray);
}

//Transforme les majuscules en minuscules
void ToLowerCase(char* word){
    int i;
    for(i = 0; i < strlen(word); i++){
        if(word[i] >= 65 && word[i] <= 90){
            word[i] += 32;
        }
    }
}

//Comptage du nombre total de mots dans le tableau en mémoire
void CountTotalWords(Program* startup){
    int total = 0;
    int i;
    for(i = 0; i < 26; i++){
        total += startup->dictionary[i].size;
    }
    startup->totalWords = total;
}

//Écriture du tableau de mots dans le fichier
void WriteOnFile(Program* startup){
    fclose(startup->f);
    fopen(startup->loadedFileName, "w+");
    int i;
    int first = 0;
    for(i = 0; i < 26; i++){
        int j;
        for(j = 0; j < startup->dictionary[i].size; j++){
            if(first == 0){
                fprintf(startup->f, "%s", startup->dictionary[i].words[j]);
                first = 1;
                continue;
            }
            fprintf(startup->f, "\n%s", startup->dictionary[i].words[j]);
        }
    }
    fclose(startup->f);
    fopen(startup->loadedFileName, "a+");
    rewind(startup->f);
}

//Vérifie les mots doublons
int CheckIfExists(Program* startup, int indexLib, char* wordToCheck){
    int i;
    for(i = 0; i < startup->dictionary[indexLib].size;i++){
        if(strcmp(startup->dictionary[indexLib].words[i], wordToCheck) == 0){
            return 1;
        }
    }
    return 0;
}

//Vérifie si le fichier existe
int CheckIfFileExists(Program* startup, FILE* textFile){
    if(textFile == NULL){
        if(textFile != NULL){
            system("cls");
            printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
            return 0;
        }
        system("cls");
        printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
        fclose(textFile);
        return 0;
    }
    return 1;
}

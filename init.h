#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#define INIT_CAPACITY 50

struct Library {
	char letter; //Première lettre des mots du tableau
	int capacity;
	int size; //Taille du dictionnaire
	char** words; //Tableau de mots
};

typedef struct Library Lib;


struct Program {
	char* loadedFileName;
	FILE* f;
	Lib* dictionary;
	int totalWords;
};

typedef struct Program Program;

//Prototypes main2.c
void FileMenu(Program*);
void DicoMenu(Program*);

//Prototypes gestrech.c
//  - Load Lib
void InitLibrary(Program*);
void FillDicoFromFile(Program*);
void FillDicoFromTextFile(Program*);
//  - Lib's operations
void WordsNotInDictionary(Program*);
void AdvancedWordSearch(Program*);
void CompareWords(Program*, char*, int);
int Levenshtein(char*, char*);
void CountTotalWords(Program*);
void ToLowerCase(char*);
void SortDico(Program*, int);
int CheckIfExists(Program*, int, char*);
int CheckIfFileExists(Program* startup, FILE* textFile);
void WriteOnFile(Program*);
void OverrideCapacity(Program*, int);
void CleanDico(Program*);
void Clean2DArray(char**, int);
void SearchWord(Program*);

//Prototypes gestfile.c
void LoadFile(Program*);
int IsFileEmpty(FILE*);

#endif // INIT_H_INCLUDED

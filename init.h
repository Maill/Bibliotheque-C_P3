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

//Prototypes main3.c
void FileMenu(Program*);
void DicoMenu(Program*);

//Prototypes gestorth.c
//  - Load Lib
void InitLibrary(Program*);
void FillDicoFromFile(Program*);
void FillDicoFromTextFile(Program*);
//  - Lib's operations
void ReplaceWordsInDocument(Program*);
char* CompareWordsToReplace(Program*, char*, int);
void SimilarWordsToWord(Program*);
void WordsNotInDictionary(Program*);
void CompareWords(Program*, char*, int);
int Levenshtein(char*, char*);
void OverrideCapacity(Program*, int);
void SortDico(Program*, int);
void CleanDico(Program*);
void Clean2DArray(char**, int);
void ToLowerCase(char*);
void CountTotalWords(Program*);
void WriteOnFile(Program*);
int CheckIfExists(Program*, int, char*);
int CheckIfFileExists(Program*, FILE*);

//Prototypes gestfile.c
void BuildALibFromText(Program*);
void LoadFile(Program*);
int IsFileEmpty(FILE*);

#endif // INIT_H_INCLUDED

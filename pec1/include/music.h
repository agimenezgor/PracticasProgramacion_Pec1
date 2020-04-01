#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//                                  constants

#define MAX_MODELS 100
#define MAX_MODELS_ORDER 10
#define MAX_CHAR 100

//                                   types

typedef char string[MAX_CHAR+1];

typedef enum {NONE, LOW, MEDIUM, HIGH} tAvailability;

typedef enum {FALSE, TRUE}tbool;

typedef struct{
	int id;
	string description;
	float price;
	tAvailability availability;
}tInstrument;

typedef struct{
	int idModel;
	int stockModel;
}tInstrumentSet;

typedef struct{
	int day;
	int month;
	int year;
}tDate;

typedef struct{
	int idClient;
	tDate date;
	tInstrument shoppingList[MAX_MODELS_ORDER];
}tOrder;

typedef struct{
	tInstrument *catalogue;
	int numInstruments;
	tInstrumentSet stock[MAX_MODELS];
	int numStock;
	tOrder *orders;
}tMusicStore;

//                                 functions

int counter(tMusicStore ms, int aux);

int find_instrument(tMusicStore ms, int id);

void init_music_store(tMusicStore *ms);

void new_instrument(tMusicStore *ms, int code, string descript, float price);

void add_stock(tMusicStore *ms, int codeModel, int units);

void print_stock(tMusicStore ms);
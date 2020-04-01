#include "music.h"

// auxiliary functions

int find_instrument(tMusicStore ms, int id){
	// search instrument model
	
	tbool found;
	int i;
	
	for(i = 0; i < ms.numInstruments; i++){
		if(ms.catalogue[i].id == id){
			found = 1;
			return found;
		}else{
			found = 0;
		}
	}
	return found;
}

int counter(tMusicStore ms, int aux){
	//lookteh position in which to save data
	
	int i;
	int count = 0;
	
	for(i = 0; i < ms.numInstruments; i++){
		if(aux == ms.catalogue[i].id){
			count = i;
		}
	}
	
	return count;
}
// demanded functions

/************************************************/
void init_music_store(tMusicStore *ms){
	/* Check PRE conditions */
  assert(ms != NULL);

  /* Empty structures */
  
  ms->numInstruments = 0;
  ms->numStock = 0;
  
  int i;
  for(i = 0; i < MAX_MODELS; i++){
	  ms->stock[i].idModel = 0;
	  ms->stock[i].stockModel = 0;
  }
}
/************************************************/
/************************************************/
void new_instrument(tMusicStore *ms, int code, string descript, float price){
	//check pre conditions
	
	assert(ms != NULL);
	assert(code > 0);
	
	// search instrument model
	
	tbool found = 0;
	
	found = find_instrument(*ms, code);
	
  if (found == 1){
	  printf("\n\nERROR: Instrument %d is already in the catalogue.\n\n", code);
  }else {
      /* It does not exist, allocate space */
      if (ms->numInstruments == 0){
		  ms->catalogue = (tInstrument *) malloc(sizeof(tInstrument));
	  }else {
		  ms->catalogue = (tInstrument *) realloc(ms->catalogue, (ms->numInstruments + 1) *sizeof(tInstrument));
	  }

      /* If it is ok, then add the instrument model to the music store */        
      if (ms->catalogue == NULL){
		  printf("ERROR: Memory error.\n");
	  }else {
		  ms->catalogue[ms->numInstruments].id = code;
		  strcpy(ms->catalogue[ms->numInstruments].description, descript);
		  ms->catalogue[ms->numInstruments].price = price;
		  ms->catalogue[ms->numInstruments].availability = 0;
		  ms->numInstruments++;
	  }
  }
}
/************************************************/
/************************************************/
void add_stock(tMusicStore *ms, int codeModel, int units){
	
	tInstrument *inst;
	/* Check PRE conditions */
	 assert(ms != NULL);
	 assert(codeModel > 0);
	 assert(units >= 0);
	 
	 inst = find_instrument(*ms, codeModel);
	 
	 int aux = 0;
	 aux = counter(*ms, codeModel);
	 
	 int i, position;
	 
	 for(i = 0; i < MAX_MODELS; i++){
		 if(ms->stock[i].idModel == 0){
			 position = i;
		 }
	 }
	 //if the code is not in teh catalog, error message

	if(inst == 0){
		printf("ERROR: Instrument %d does not appear in the catalogue.\n\n", codeModel);
	}else{ 
		if(ms->numStock >= MAX_MODELS){
			printf("ERROR: the stock are filled.");
		}else{
			if(ms->stock[position].stockModel != 0){ 
				//if the stock already has a unit, increase units
				ms->stock[position].stockModel += units;
			}else{
				//if there are not units in the stock, add model with units
				ms->stock[position].idModel = codeModel;
				ms->stock[position].stockModel = units;
				
				//choose the availability
				if(ms->stock[position].stockModel == 0){
					ms->catalogue[aux].availability = NONE;
				}
				if(ms->stock[position].stockModel > 0 && ms->stock[position].stockModel < 6){
					ms->catalogue[aux].availability = LOW;
				}else{
					if(ms->stock[position].stockModel > 5 && ms->stock[position].stockModel < 16){
						ms->catalogue[aux].availability = MEDIUM;
					}else{
						ms->catalogue[aux].availability = HIGH;
					}
				}
			}		
		}
	}
}		

/************************************************/
/************************************************/
void print_stock(tMusicStore ms){
	int i;
	string availab;
	
	//show the models that are in the catalog
	for(i = 0; i < ms.numInstruments; i++){
		if(ms.catalogue[i].availability == 0){
			strcpy(availab, "none");
		}else{
			if(ms.catalogue[i].availability == 1){
				strcpy(availab, "low");
			}else{
				if(ms.catalogue[i].availability == 2){
					strcpy(availab, "medium");
				}else{
					strcpy(availab, "high");
				}
			}
		}
		printf("\nInstrument %d\n", i + 1);
		printf("%d %s %.2f %s\n", ms.catalogue[i].id, ms.catalogue[i].description, ms.catalogue[i].price, availab);
	}
	printf("\n");
}
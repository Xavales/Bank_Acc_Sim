/*****************************************************
Arxeio epikefalidas	: TStoixeioyListas.h
Syggrafeas			: D.Mhlios
Skopos				: Ylopoihsh Typou Stoixeioy listas gia TSstoixeioyListas int
*****************************************************/

#ifndef __TSTOIXEIOYLISTAS_H__
#define __TSTOIXEIOYLISTAS_H__

typedef struct 
{   char  *name;
	int init_amount;
}  TStoixeioyListas;

int TSlist_iso(TStoixeioyListas Elem1, TStoixeioyListas Elem2);
int TSlist_mikrotero(TStoixeioyListas Elem1, TStoixeioyListas Elem2);
int TSlist_megalytero(TStoixeioyListas Elem1, TStoixeioyListas Elem2);

void TSlist_setValue (TStoixeioyListas *target, TStoixeioyListas source);
void My_setValue (TStoixeioyListas *target, char* name, int amount);
void Name_setValue (TStoixeioyListas *target, char* name);
void TSlist_clear(TStoixeioyListas *target);
int TSlist_readValue (FILE *from, TStoixeioyListas * Elem);
int TSlist_writeValue (FILE *to, TStoixeioyListas Elem);
#endif

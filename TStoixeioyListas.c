/*****************************************************
Arxeio ylopoihshs	: TStoixeioyListas.c
Syggrafeas			: D.Mhlios
Skopos				: Ylopoihsh Typou Stoixeioy listas gia TSstoixeioyListas struct
*****************************************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "TStoixeioyListas.h"

int TSlist_iso (TStoixeioyListas Elem1, TStoixeioyListas Elem2)
{   if(strcmp(Elem1.name,Elem2.name)==0)
      return 1;
   else
      return 0; 
}

int TSlist_mikrotero(TStoixeioyListas Elem1, TStoixeioyListas Elem2)
{
    if((strcmp(Elem1.name,Elem2.name)<0))
       return 1;
    else
       return 0;
}

int TSlist_megalytero(TStoixeioyListas Elem1, TStoixeioyListas Elem2)
{
    if((strcmp(Elem1.name,Elem2.name)>0))
       return 1;
    else
       return 0;
}

void TSlist_setValue (TStoixeioyListas *target, TStoixeioyListas source)
{    target->init_amount=source.init_amount;
	 target->name=source.name;
}

void My_setValue (TStoixeioyListas *target, char* name, int amount)
{    target->init_amount=amount;
	target->name=malloc(strlen(name)+1);
	strcpy(target->name,name);
}

void Name_setValue (TStoixeioyListas *target, char* name)
{  
	target->name=malloc(strlen(name)+1);
	strcpy(target->name,name);
}

void TSlist_clear(TStoixeioyListas *target)
{	if((target->name)!= NULL)
		free(target->name);
}

int TSlist_readValue (FILE *from, TStoixeioyListas * Elem)
{    int fd;
     fd=fscanf(from,"%d %s",&(Elem->init_amount),Elem->name);    
     if(fd==2)
      return 1;
     else
      return 0;  
}

int TSlist_writeValue (FILE *to, TStoixeioyListas Elem)
{   int fd;
	fd=fprintf(to, "%d %s-- ", Elem.init_amount,Elem.name);
	return fd;
}


/***************************************************************************************
Arxeio Ylopoihshs	: SimpleL_pointer.c -to sigkekrimeno apotelei to arxeio protipo 
Syggrafeas			: G. Kotrwnhs
Skopos				: Ylopoihsh me deiktes, ATD Syndedemenh Lista
Ana8ewrhsh			: D.Mhlios
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Pointer_List.h"
#include "TStoixeioyListas.h"


typedef struct info_node
{   int      size;	
	typos_deikti     arxi; 	/*deikths sto proto komvo tis listas*/
} info_node;   /* o komvos plhroforias ths listas */ 


typedef struct typos_komvou
{   TStoixeioyListas dedomena;	
	typos_deikti    epomenos; 
	TransactionList_deikti transactions;	
} typos_komvou;	  /*o typos toy kombou ths listas*/ 

typedef struct TransactionList

{   int      size;	
	TransactionListNode_deikti     arxi; 	/*deikths sto proto komvo tis listas*/
} TransactionList;   /* o komvos plhroforias ths listas */ 



typedef struct TransactionListNode

{   TStoixeioyListas dedomena;	
	TransactionListNode_deikti    epomenos; 	
} TransactionListNode;	  /*o typos toy kombou ths listas*/ 

void eisagogi_arxi(info_deikti * const,TStoixeioyListas , int *);
void eisagogi_meta(info_deikti *  const,TStoixeioyListas,typos_deikti , int *);


info_deikti LIST_dimiourgia( )
{/*	Pro: 		kamia
  *	Meta: 		Dhmioyrgia kenhs syndedemenhs listas meso tis desmeusis kai arxikopoiisis tou  komvou
                linfo pou leitourgei os komvos pliroforias kai tha sindethei me ton proto komvo pou tha 
                eisaxthei */	
    info_deikti linfo;
    linfo = malloc(sizeof(info_node));
   	linfo->size = 0;
	linfo->arxi = NULL; 
    return linfo;	
}

TransactionList_deikti TransactionList_dimiourgia( ) //similar to LIST_dimiourgia( );
{	
    TransactionList_deikti linfo;

    linfo = malloc(sizeof(TransactionList));
   	linfo->size = 0;
	linfo->arxi = NULL; 
    return linfo;	
}

TransactionList_deikti* TransactionList_return(typos_deikti p) //return function 
{
	return &(p->transactions);
}


void LIST_katastrofi(info_deikti * linfo)
{/*	Pro: 	  Dhmioyrgia listas
  *	Meta: 	  Katastrofi ths listas kai apodesmeusi sto telos kai tou komvou linfo */ 
     
	typos_deikti todel,todel2;
	todel= (*linfo)->arxi;
	while(todel!=NULL)
	{   todel2=todel;
		todel=(todel)->epomenos;
		TransactionList_katastrofi(&(todel2->transactions));
		free(todel2);
	}
	(*linfo)->arxi = NULL;
    free(*linfo);
    (*linfo)=NULL;
}

void TransactionList_katastrofi(TransactionList_deikti * linfo) //similar LIST_katastrofi(info_deikti * linfo);
{
     
	TransactionListNode_deikti todel,todel2;
	todel= (*linfo)->arxi;
	while(todel!=NULL)
	{   todel2=todel;

		todel=(todel)->epomenos;
		free(todel2);

	}
	(*linfo)->arxi = NULL;
    free(*linfo);
    (*linfo)=NULL;
}

int List_find_Amount(typos_deikti p){ //find amount function

	return p->dedomena.init_amount;
}

TStoixeioyListas * Dedomena_return(typos_deikti p){ //return function

	return &(p->dedomena);
}


int LIST_keni(const info_deikti  linfo)
{/*	Pro: 		Dhmioyrgia Listas
  *	Meta:		Epistrefei 1 an h lista einai kenh, diaforetika 0  */
	return ( linfo->arxi == NULL );
}

void LIST_periexomeno(info_deikti  const linfo, const typos_deikti p, TStoixeioyListas *val,int * const error)
{/*	Pro: 		O deikths p deixnei ena kombo sth lista
  *	Meta:		Epistrefei ta dedomena ston komvo pou deixnei o p */
   *error=0;
    if(p!=NULL)
	  TSlist_setValue(val, p->dedomena);
	else
	   *error=1;	   
}

void LIST_allagi(info_deikti * const linfo,typos_deikti * const p, TStoixeioyListas stoixeio,int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Allazei ta dedomena ston komvo pou deixnei o p */     
    *error=0;
	if((*p)!=NULL)
	  TSlist_setValue(&(*p)->dedomena, stoixeio);
	else
      *error=1;	
}

void LIST_diadromi(const info_deikti  linfo, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Grafei stin eksodo ola ta stoixeia tis listas */       
      
	typos_deikti temp;
	temp=(linfo)->arxi;
	*error=0;
	
	if(LIST_keni(linfo))
	{	*error=1;
		return;
	}
	
	while(temp!=NULL)
	{   TSlist_writeValue(stdout,temp->dedomena);
		temp=temp->epomenos;
	}
}

void LIST_eisagogi(info_deikti * const linfo, TStoixeioyListas stoixeio,
					typos_deikti  prodeiktis, int *error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta: 		Eisagetai to "stoixeio" meta ton "prodeikti",an einai null autos to stoixeio mpainei
                stin arxi tis listas allios mpainei meta apo ton komvo pou deixnei autos  */      
      
	*error=0;
	if(prodeiktis==NULL)
		eisagogi_arxi(linfo, stoixeio, error);
	else
		eisagogi_meta(linfo,stoixeio,prodeiktis, error);		 
}

void eisagogi_arxi(info_deikti *  const linfo,TStoixeioyListas stoixeio, int *error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta: 		O kombos me ta dedomena stoixeio exei eisax8ei sthn arxh ths listas */
  
	typos_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(typos_komvou));
	if ( prosorinos == NULL )
	{	*error=1;
		return;
	}
	TSlist_setValue(&prosorinos->dedomena, stoixeio);
    prosorinos->epomenos = (*linfo)->arxi;
    (*linfo)->arxi = prosorinos;
    (*linfo)->size ++;
     
}

void eisagogi_meta(info_deikti *  const linfo,TStoixeioyListas stoixeio, typos_deikti  prodeiktis, int *error)
{/*	Pro: 		O prodeiktis deixnei ena kombo sth lista
  *	Meta: 		O komboe me ta dedomena exei eisax8ei meta ton kombo pou
 				deixnei o prodeiktis */
 				
	typos_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(typos_komvou));
	if (prosorinos == NULL)
	{	*error=1;
		return;
	}
	TSlist_setValue(&prosorinos->dedomena, stoixeio);
	prosorinos->epomenos = prodeiktis->epomenos;
	prodeiktis->epomenos = prosorinos;
    (*linfo)->size ++;
}

void eisagogi_arxi2(info_deikti *  const linfo,TStoixeioyListas stoixeio) //modified version of eisagogi arxi
{
	typos_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(typos_komvou));
	if (prosorinos == NULL)
		return;
	TSlist_setValue(&prosorinos->dedomena, stoixeio);
	prosorinos->transactions=TransactionList_dimiourgia();
	prosorinos->epomenos = (*linfo)->arxi;
    (*linfo)->arxi = prosorinos;
    (*linfo)->size ++;
}

void TransactionList_eisagogi_arxi2(TransactionList_deikti *  const linfo,TStoixeioyListas stoixeio)
{	
	TransactionListNode_deikti ListNodeptr;

	ListNodeptr=TransactionList_anazitisi(*linfo, stoixeio);
	if(ListNodeptr==NULL){
		
		TransactionListNode_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

		prosorinos = malloc(sizeof(TransactionListNode));
		if (prosorinos == NULL)
			return;
		TSlist_setValue(&prosorinos->dedomena, stoixeio);
		prosorinos->epomenos = (*linfo)->arxi;
		(*linfo)->arxi = prosorinos;
		(*linfo)->size ++;

	} 
	else {
		(ListNodeptr->dedomena.init_amount)+=stoixeio.init_amount;  //if the amount exists add the new one to the old one
	}

}
void LIST_diagrafi(info_deikti * const linfo, typos_deikti *deiktis, int * const error)
{/*	Pro: 		Dhmiourgia Listas
  *	Meta: 		Diagrafetai to stoixeio ths listas pou deixnei o "deiktis" */     
     
	typos_deikti prosorinos,previous; //prosorinos gia ton kombo pou tha diagrafei 
                                      //kai previous gia ton proigoumeno tou
	*error=0;

	if(LIST_keni(*linfo)|| (*deiktis==NULL)) 
	{   *error=1;
		return;
	}
	if((*linfo)->arxi==(*deiktis)) //an einai o protos kombos
	{    prosorinos=*deiktis;
        *deiktis=prosorinos->epomenos;
		(*linfo)->arxi =prosorinos->epomenos;
	}
	else
	{      prosorinos=*deiktis;
           previous=prosorinos;
           *deiktis=prosorinos->epomenos;
	       LIST_proigoymenos(*linfo, &previous, error);
           if(((*error)==1) || ((*error)==2))
			 	return; 
	       previous->epomenos=prosorinos->epomenos;
     }
     free(prosorinos);
     prosorinos=NULL;
     (*linfo)->size--;	
}

void LIST_epomenos(const info_deikti  linfo, typos_deikti * const p, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton epomeno komvo tou "p" kai sto error 0,an o p einai null tote epistrefei 
                sto error 2 allios an den iparxei epomenos epistrefei sto error 1 */  
   
	*error = 0;
	if((*p)!=NULL)
	 { if((*p)->epomenos!=NULL) 
		 *p=(*p)->epomenos;
       else
         *error=1;                  
      }  
	else
	  *error=2; 
}

void LIST_proigoymenos (const info_deikti linfo, typos_deikti * const p, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton prohgoumeno komvo tou "p" kai sto error 0,an o p einai null tote epistrefei 
                sto error 2 allios an o p einai o protos komvos tis listas epistrefei sto error 1 */  
     
//	typos_deikti prosorinos=linfo->arxi;
	*error = 0;
	if((*p)!=NULL)             /*  lista oxi adeia  */
	{
		if((*p)==linfo->arxi)           /* an deixnei ston proto kombo tis listas */
			*error=1;                 
		else                       
		{   typos_deikti prosorinos=linfo->arxi;
			while(prosorinos->epomenos != *p)
				prosorinos=prosorinos->epomenos;
			*p=prosorinos;
		}
	}
	else
	 	*error=2;   
}

void LIST_first (info_deikti  const linfo, typos_deikti * const first, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton  proto komvo ths listas diaforetika epistrefei 1 sto error */    
	*error=0;
	*first=linfo->arxi;
	if (LIST_keni(linfo))
		*error=1;
}

void LIST_last (info_deikti  const linfo, typos_deikti * const last, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton  teleutaio komvo ths listas diaforetika 1 sto error an einai kenh auti */
     
//	typos_deikti prosorinos=linfo->arxi;
	*error = 0;
	*last=NULL;
	if (LIST_keni(linfo))           
		*error=1;                 
	else                       
	{   typos_deikti prosorinos=linfo->arxi;
		while (prosorinos->epomenos != NULL)
			prosorinos=prosorinos->epomenos;
		*last=prosorinos;
	} 
}


void LIST_anazitisi(info_deikti  const linfo, TStoixeioyListas stoixeio,
					typos_deikti *prodeiktis, int *vrethike)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Anazhta an yparxei sthn lista to stoixeio,an yparxei to vrethike ginetai 1 */      
      
	TStoixeioyListas temp;
	typos_deikti trexon;
	int  error=0;

	trexon = linfo->arxi;
	*prodeiktis = NULL;
	*vrethike = 0;
	while ( (!(*vrethike)) && (trexon!=NULL))
	{   LIST_periexomeno(linfo,trexon,&temp,&error);
		if (TSlist_iso(temp, stoixeio)) //ana vrethei to stoixeio
	    	*vrethike =1; 
		else             
		{   *prodeiktis = trexon;
			LIST_epomenos(linfo, &trexon,&error);
			if(error)   //an den iparxei epomenos
                trexon=NULL;   
		}
	 }
}


typos_deikti LIST_anazitisi2(info_deikti  const linfo, TStoixeioyListas stoixeio) //similar to LIST_anazitisi but returns struct 
{     																				//pointer 
      
	TStoixeioyListas temp;
	typos_deikti trexon;
	int  vrethike=0;

	trexon = linfo->arxi;
	
	while ( (!(vrethike)) && (trexon!=NULL))
	{   TSlist_setValue(&temp,trexon->dedomena);
		if (TSlist_iso(temp, stoixeio)){ //ana vrethei to stoixeio
	    	vrethike =1; 
			return trexon;
		}
		else             
		{   
			trexon=trexon->epomenos;  
		}
		//TSlist_clear(&temp);
	 }
	
	return NULL;
}

TransactionListNode_deikti TransactionList_anazitisi(TransactionList_deikti  const linfo, TStoixeioyListas stoixeio)
{     
      
	TStoixeioyListas temp;
	TransactionListNode_deikti trexon;
	int  vrethike=0;

	trexon = linfo->arxi;
	
	while ( (!(vrethike)) && (trexon!=NULL))
	{   TSlist_setValue(&temp,trexon->dedomena);
		if (TSlist_iso(temp, stoixeio)){ //ana vrethei to stoixeio
	    	vrethike =1; 
			return trexon;
		}
		else             
		{   
			trexon=trexon->epomenos;  
		}
		//TSlist_clear(&temp);
	 }
	
	return NULL;
}

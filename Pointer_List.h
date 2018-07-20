/***************************************************************************************
Arxeio Epikefalidas	: Pointer_List.h -to sigkekrimeno apotelei to arxeio protipo 
Syggrafeas			: Y.Kotrwnis
Skopos			    : Ylopoihsh me deiktes, ATD Syndedemenh Lista
Ana8ewrhsh			: D.Mhlios
                  Ena arxeio diepafhs gia oles tis ylopoihseis listas
****************************************************************************************/
#ifndef __POINTER__LIST_ 
#define __POINTER__LIST_

#include "TStoixeioyListas.h"

/*dhlwseis typwn*/

typedef struct info_node  * info_deikti;

typedef struct typos_komvou * typos_deikti;

typedef struct TransactionList  * TransactionList_deikti; //transaction lists definitions

typedef struct TransactionListNode * TransactionListNode_deikti;

/*dhlwseis synarthsewn*/

/*dhmioyrgia listas/kastastrofi*/
info_deikti LIST_dimiourgia( );
TransactionList_deikti TransactionList_dimiourgia( ); 
void LIST_katastrofi(info_deikti * linfo);
void TransactionList_katastrofi(TransactionList_deikti * linfo); 

/*prakseis elegxoy*/
int	LIST_keni(const info_deikti  linfo);

/*prakseis prosbashs*/
void LIST_periexomeno(info_deikti  const linfo, const typos_deikti p, TStoixeioyListas *val,int * const error);
void LIST_allagi(info_deikti * const linfo, typos_deikti * const p, TStoixeioyListas stoixeio,int * const error);
void LIST_diadromi(const info_deikti  linfo, int * const error);

/*prakseis eisagwgh-diagrafh*/
void LIST_eisagogi(info_deikti * const linfo, TStoixeioyListas stoixeio,typos_deikti prodeiktis, int *error);
void LIST_diagrafi(info_deikti * const linfo, typos_deikti *deiktis, int * const error);
void eisagogi_arxi2(info_deikti *  const linfo,TStoixeioyListas stoixeio);
void TransactionList_eisagogi_arxi2(TransactionList_deikti *  const linfo,TStoixeioyListas stoixeio);
typos_deikti LIST_anazitisi2(info_deikti  const linfo, TStoixeioyListas stoixeio);
TransactionListNode_deikti TransactionList_anazitisi(TransactionList_deikti  const linfo, TStoixeioyListas stoixeio);

/* Epilogh Kombou */

void LIST_epomenos(info_deikti  const linfo, typos_deikti * const p, int * const error);
void LIST_proigoymenos(const info_deikti linfo, typos_deikti * const p, int * const error);
void LIST_first(const info_deikti  linfo, typos_deikti * const first, int * const error);
void LIST_last(const info_deikti  linfo, typos_deikti * const last, int * const error);
int List_find_Amount(typos_deikti p);
TransactionList_deikti* TransactionList_return(typos_deikti p);
TStoixeioyListas * Dedomena_return(typos_deikti p);

/*prakseis anazhthshs*/

void LIST_anazitisi(const info_deikti  linfo, TStoixeioyListas stoixeio,
					typos_deikti *prodeiktis, int *vrethike);

#endif /*#ifndef __POINTER__LIST_ */

/* i n e t _ s t r _ s e r v e r . c : Internet stream sockets server */
#include <stdio.h>
#include <sys/wait.h> /* sockets */
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* internet sockets */
#include <netdb.h> /* g e t h o s t b y a d d r */
#include <unistd.h>
#include <stdlib.h> /* exit */
#include <string.h>
#include <pthread.h>
#include "Pointer_List.h"
#include "TStoixeioyListas.h"
#include <signal.h>

#define  Hash_Size 100
#define Queue_Size 20
#define Worker_threads 100
#define perror2(s,e) fprintf(stderr,"%s : %s \n",s,strerror(e))

typedef struct { //pro-cond.c
    int * data;
    int start;
    int end;
    int count;
} pool_t;

pool_t pool;

int poolsize;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //init mutexes and condition variables
static pthread_cond_t cond_nonempty = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_nonfull = PTHREAD_COND_INITIALIZER;

void perror_exit(char * message);
void del_new_line(char *str);
void * worker(void *arg); //worker threads

void place(pool_t * pool, int data, int pool_size); //place and obtain from pool functions
int obtain(pool_t * pool, int pool_size);

int Hash_function(char* name);

int connections = -1;
info_deikti Hashtable[Hash_Size];
pthread_mutex_t Mutextable[Hash_Size];

int sock = 0;

void freememory_and_exit(int s) {
    if (sock > 0) {
        close(sock);
    }
    exit(0);
}


int cmpfunc (const void * a, const void * b) ;

int main(int argc, char * argv []) {

    int port, threadpoolsize, queuesize, newsock, err;

    pthread_t * workers = NULL;

    struct sockaddr_in server, client;
    socklen_t clientlen;
    struct sockaddr *serverptr = (struct sockaddr*) &server;
    struct sockaddr *clientptr = (struct sockaddr*) &client;

    //choose your arguments (./bankserver -p <port> -s <threadpoolsize> -q <queuesize> order doesnt matter)
    if (argc != 7) {
        printf("Wrong parameters given...\norder matters not\ninput parameters: -p <port> -s <threadpoolsize> -q <queuesize>\n");
        exit(1);
    } else {
        int j;
        for (j = 1; j < argc; j += 2) {

            if (strcmp(argv[j], "-p") == 0) {
                port = atoi(argv[j + 1]);
                if (port <= 0) {
                    printf("Invalid port number \n");
                    exit(1);
                }
                continue;
            } else if (strcmp(argv[j], "-s") == 0) {
                threadpoolsize = atoi(argv[j + 1]);
                if ((threadpoolsize <= 0) || (threadpoolsize > Worker_threads)) {
                    printf("You can use 1 up to 100 worker threads \n");
                    exit(1);
                }
                continue;
            } else if (strcmp(argv[j], "-q") == 0) {
                queuesize = atoi(argv[j + 1]);
                if ((queuesize <= 0) || (queuesize > Queue_Size)) {
                    printf("You can queue 1 up to 20 requests at a time \n");
                    exit(1);
                }
                continue;
            } else {
                printf("Invalid parameters\n");
                exit(1);
            }
        }
    }

    signal(SIGINT, freememory_and_exit); //if signal ^C happens call freememory exit to break the loop and free resources

    workers = malloc(sizeof (pthread_t) * threadpoolsize);

    pool.data = malloc(sizeof (int)*queuesize);   //initialiaze thread_pool values
    pool.count = 0;
    pool.start = 0;
    pool.end = -1;

    poolsize = queuesize;

    /* Create socket */

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror_exit("socket");
    server.sin_family = AF_INET;

    /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    /* The given port */

  
    /* Bind socket to address */
    if (bind(sock, serverptr, sizeof (server)) < 0)
        perror_exit("bind");

    /* Listen for connections */
    if (listen(sock, 5) < 0)
        perror_exit("listen");


    printf("Listening for connections to port % d \n", port);


    int i;

    for (i = 0; i < Hash_Size; i++) {
        Hashtable[i] = LIST_dimiourgia();
        pthread_mutex_init(&Mutextable[i], NULL);
    }

    for (i = 0; i < threadpoolsize; i++) { /* thread pool */
        if ((err = pthread_create(&workers[i], NULL, worker, (void *) &connections)) < 0) { 
            perror2("pthread_create", err);
            exit(1);
        }
    }


    clientlen = sizeof (*clientptr);
    while (1) {

        /* accept connection */
        if ((newsock = accept(sock, clientptr, &clientlen)) < 0)
            perror_exit("accept");

        printf("Accepted connection \n");

        //printf("testme1");

        place(&pool, newsock, poolsize);

        //printf("testme2");

    }

    for (i = 0; i < threadpoolsize; i++) {
        if ((err = pthread_join(workers[i], NULL)) < 0) {
            /* Wait for thread termination */
            perror2("pthread_join ", err);
            exit(1);
        }
    }

    for (i = 0; i < Hash_Size; i++)
        LIST_katastrofi(&Hashtable[i]);

    free(workers);
    free(pool.data);
}

void * worker(void *arg) {

    char *string, *name, *src_name, *dest_name, *saveptr, *init_command, buf[512], bufp [512], bufpp[100];
    int init_amount, delay = 0, my_connect, time = 0; //, ms = 0;

    //printf("executing");
    while (1) {
        my_connect = obtain(&pool, poolsize);
        if (my_connect < 0) {
            break;
        }
        connections = -1;

        //printf("executing2");	

        while (read(my_connect, buf, 512) > 0) {

            init_command = malloc(sizeof (buf));
            strncpy(init_command, buf, sizeof (buf));
            string = strtok_r(buf, " ", &saveptr);
            //printf("%s\n",init_command);


            if (strcmp(string, "add_account") == 0) { //add account 
                string = strtok_r(NULL, " ", &saveptr);
                if (string != NULL) {
                    init_amount = atoi(string);
                    string = strtok_r(NULL, " ", &saveptr);
                    if (string != NULL) {
                        name = malloc(strlen(string) + 1);
                        if (name == NULL)
                            perror_exit("malloc add_account");
                        strncpy(name, string, strlen(string) + 1);
                        //printf("test --->>%s",name);
                        del_new_line(name);
                        //printf("test --->>%s",name);
                        string = strtok_r(NULL, "\n", &saveptr);
                        if (string != NULL) {
                            delay = atoi(string);
                            time = 1000 * delay;
                            //ms = time / 1000;                            
                            //printf("sleeping for %dms\n",ms);
                        }
                        //sanity checks
                        if (init_amount < 0) {                            
                            sprintf(buf, "Error. Account creation failed (%s:%d)\n", name, init_amount);
                        } else {
                            // *********************************************** LOCK
                            int hashvalue = Hash_function(name);
                            pthread_mutex_lock(&Mutextable[hashvalue]);
							// *********************************************** LOCK
                            usleep(time);
                            TStoixeioyListas stoixeio;
                            My_setValue(&stoixeio, name, init_amount);
                            typos_deikti saltas = LIST_anazitisi2(Hashtable[Hash_function(name)], stoixeio);
                            if (saltas != NULL)
                                sprintf(buf, "Error. Account creation failed (%s:%d)\n", name, init_amount);
                            else {
                                eisagogi_arxi2(&Hashtable[Hash_function(name)], stoixeio);
                                sprintf(buf, "Success. Account creation  (%s:%d)\n", name, init_amount);
                            }
							// *********************************************** UNLOCK
                            pthread_mutex_unlock(&Mutextable[hashvalue]);
                            // *********************************************** UNLOCK
                        }
                    }
                    free(name);
                }
                delay = 0;
                time = 0;

            } else if (strcmp(string, "add_transfer") == 0) { // add transfer
                string = strtok_r(NULL, " ", &saveptr);
                if (string != NULL) {
                    init_amount = atoi(string);
                    string = strtok_r(NULL, " ", &saveptr);
                    if (string != NULL) {
                        src_name = malloc(strlen(string) + 1);
                        if (src_name == NULL)
                            perror_exit("malloc add_transfer");
                        strncpy(src_name, string, strlen(string) + 1);
                        string = strtok_r(NULL, " ", &saveptr);
                        if (string != NULL) {
                            dest_name = malloc(strlen(string) + 1);
                            if (dest_name == NULL)
                                perror_exit("malloc add_transfer");
                            strncpy(dest_name, string, strlen(string) + 1);
                            del_new_line(dest_name);
                            string = strtok_r(NULL, "\n", &saveptr);
                            if (string != NULL) {
                                delay = atoi(string);
                                time = 1000 * delay;
                                //ms = time / 1000;                                
                                //printf("sleeping for %dms\n",ms);
                            }
                            //sanity checks
                            if (init_amount < 0)
                                sprintf(buf, "Error. Transfer addition failed (%s:%s:%d[:%d])\n", src_name, dest_name, init_amount, delay);
                            else {
                                // *********************************************** LOCK
                                int src_hashvalue = Hash_function(src_name);
                                int dest_hashvalue = Hash_function(dest_name);
                                
                                if (src_hashvalue < dest_hashvalue) {
                                    pthread_mutex_lock(&Mutextable[src_hashvalue]);
                                    pthread_mutex_lock(&Mutextable[dest_hashvalue]);
                                } else {    
                                    if (src_hashvalue > dest_hashvalue) {
                                        pthread_mutex_lock(&Mutextable[dest_hashvalue]);
                                        pthread_mutex_lock(&Mutextable[src_hashvalue]);
                                    } else {
                                        pthread_mutex_lock(&Mutextable[src_hashvalue]);
                                    }
                                }
								// *********************************************** LOCK
                                usleep(time);
                            
                                TStoixeioyListas stoixeio;
                                My_setValue(&stoixeio, src_name, init_amount);
                                typos_deikti saltas = LIST_anazitisi2(Hashtable[Hash_function(src_name)], stoixeio);
                                if (saltas != NULL) {
                                    TStoixeioyListas stoixeio2;
                                    My_setValue(&stoixeio2, dest_name, init_amount);
                                    typos_deikti saltas2 = LIST_anazitisi2(Hashtable[Hash_function(dest_name)], stoixeio2);
                                    if (saltas2 != NULL) {
                                        if ((List_find_Amount(saltas)) >= (init_amount)) {
                                            TransactionList_eisagogi_arxi2((TransactionList_return(saltas2)), stoixeio2);
                                            (Dedomena_return(saltas)->init_amount) -= init_amount;
                                            (Dedomena_return(saltas2)->init_amount) += init_amount;
                                            sprintf(buf, "Success. Transfer addition (%s:%s:%d[:%d])\n", src_name, dest_name, init_amount, delay);
                                        } else {
                                            sprintf(buf, "Error. Transfer addition failed(%s:%s:%d[:%d])\n", src_name, dest_name, init_amount, delay);
                                        }
                                    } else {
                                        sprintf(buf, "Error. Transfer addition failed(%s:%s:%d[:%d])\n", src_name, dest_name, init_amount, delay);
                                    }
                                } else {
                                    sprintf(buf, "Error. Transfer addition failed(%s:%s:%d[:%d])\n", src_name, dest_name, init_amount, delay);
                                }				
                                // *********************************************** UNLOCK
                                if (src_hashvalue < dest_hashvalue) {
                                    pthread_mutex_unlock(&Mutextable[src_hashvalue]);
                                    pthread_mutex_unlock(&Mutextable[dest_hashvalue]);
                                } else {    
                                    if (src_hashvalue > dest_hashvalue) {
                                        pthread_mutex_unlock(&Mutextable[dest_hashvalue]);
                                        pthread_mutex_unlock(&Mutextable[src_hashvalue]);
                                    } else {
                                        pthread_mutex_unlock(&Mutextable[src_hashvalue]);
                                    }
                                }
                                // *********************************************** UNLOCK
                            }
                        }
                    }
                }
                delay = 0;
                time = 0;
                //ms = 0;
                free(src_name);
                free(dest_name);
			 } 

			else if (strcmp(string, "add_multi_transfer") == 0) {
                int total_strings = 0, i;

                //printf("inside add_multi_transfer!!\n");
                string = strtok_r(NULL, " ", &saveptr);
                while ((string != NULL)) {
                    //printf("string=%s\n", string);
                    string = strtok_r(NULL, " ", &saveptr);
                    total_strings++;
                }
                char **strings_given;
                int * hashes_needed;
                int hashes_count;
                strings_given = malloc(total_strings * sizeof (char*));                

                strncpy(buf, init_command, strlen(init_command) + 1);
                string = strtok_r(buf, " ", &saveptr);
                //printf("bufbuf=%s stringstring=%s\n***** total_strings=%d\n", buf, string, total_strings);
                string = strtok_r(NULL, " ", &saveptr);
                for (i = 0; i < total_strings; i++) {
                    //printf("3ddddddddddd %s\n", string);
                    strings_given[i] = malloc((strlen(string) + 1));
                    strncpy(strings_given[i], string, strlen(string) + 1);
                    string = strtok_r(NULL, " ", &saveptr);
                }
               // printf("Printing INNNN STRING !!!!!!!!%s\n", strings_given[total_strings - 1]);

                if (atoi(strings_given[total_strings - 1]) > 0 || strcmp(strings_given[total_strings - 1], "0")==0) {
                    delay = atoi(strings_given[total_strings - 1]);
                    time = 1000 * delay;
                    //   ms = time / 1000;
                    //printf("sleeping for %dms\n",ms);
                    //printf("delay%d\n",delay);
                    total_strings -= 1;                    
                }
                //printf("Printing LAST STRING !!!!!!!!%s\n", strings_given[total_strings - 1]);
               
                // *********************************************** LOCK
                hashes_needed = malloc((total_strings-1) * sizeof (int));
                hashes_count = total_strings-1;
                for (i = 0; i < hashes_count; i++) {
                    hashes_needed[i] = Hash_function(strings_given[i+1]);
                }
                
                //for (i = 0; i <  hashes_count; i++) {
                    //printf("%d  ", hashes_needed[i]);
                //}
                //printf("\n");
                qsort(hashes_needed,hashes_count, sizeof(int), cmpfunc ); //sort the locks
                //for (i = 0; i < hashes_count; i++) {
                   // printf("%d  ", hashes_needed[i]);
               // }
               // printf("\n");
                
                for (i = 0; i < hashes_count; i++) {
                    if (i == hashes_count-1 || hashes_needed[i] != hashes_needed[i+1]) {
                        pthread_mutex_lock(&Mutextable[i]);
                    }
                }
                // *********************************************** LOCK
                
                usleep(time);

                //printf("Printing string !!!!!!!!\n");
                TStoixeioyListas stoixeio;
                typos_deikti first_saltas, *saltas_board;
                saltas_board = malloc((total_strings) * sizeof (typos_deikti*));
                int power_flag = 0, flag = 0, total_amount;
                for (i = 1; i < total_strings; i++)
                    saltas_board[i] = malloc(sizeof (typos_deikti));
                (stoixeio.init_amount) = atoi(strings_given[0]);
                init_amount = (stoixeio.init_amount);
                for (i = 1; i < total_strings; i++) {
                    del_new_line(strings_given[i]);
                    Name_setValue(&stoixeio, strings_given[i]);
                    //if(i==total_strings-1)
                    //del_new_line(strings_given[i]);
                    saltas_board[i] = LIST_anazitisi2(Hashtable[Hash_function(strings_given[i])], stoixeio);
                    if (i == 1) {
                        first_saltas = saltas_board[i];
                        total_amount = List_find_Amount(first_saltas);
                       // printf("total_amount--->%d\n", total_amount);
                    }
                    //printf("in_condition_total_strings--->%dNULL----->%d\n", total_strings, saltas_board[i] == NULL);
                    if (saltas_board[i] == NULL) {
                        sprintf(buf, "Error.Multi Transfer addition failed(%s:%d[:%d])\n", strings_given[1], init_amount, delay);
                        power_flag = 1;
                        break;
                    }
                    //printf("after_condition_strings--->%s\n", strings_given[i]);
                }
				if (power_flag == 0) {
                    for (i = 2; i < total_strings; i++) {
                        if ((total_amount >= (init_amount * (total_strings - 2)))) {
                            TransactionList_eisagogi_arxi2((TransactionList_return(saltas_board[i])), stoixeio);
                            (Dedomena_return(first_saltas)->init_amount) -= init_amount;
                            (Dedomena_return(saltas_board[i])->init_amount) += init_amount;
                            flag = 1;
                            //printf("in_condition_strings--->%s\nflag---->%d", strings_given[i], flag);
                        }
                    }
                }
                
                // *********************************************** UNLOCK
                for (i = 0; i < hashes_count; i++) {
                    if (i == hashes_count-1 || hashes_needed[i] != hashes_needed[i+1]) {
                        pthread_mutex_unlock(&Mutextable[i]);
                    }
                }
                // *********************************************** UNLOCK
                
                if (flag == 1)
                    sprintf(buf, "Success. Multi Transfer addition(%s:%d[:%d])\n", strings_given[1], init_amount, delay);
                else
                    sprintf(buf, "Error. Multi Transfer addition failed(%s:%d[:%d])\n", strings_given[1], init_amount, delay);
                delay = 0;  
                time = 0;
                //                ms = 0;
                for (i = 0; i < total_strings; i++)
                    free(strings_given[i]);
                for (i = 1; i < total_strings; i++)
                    (saltas_board[i]) = NULL;
                free(strings_given);
                saltas_board = NULL;
                total_strings = 0;
                total_amount = 0;
            } 

			else if (strcmp(string, "print_multi_balance") == 0) { //print_multi_balance
                int total_strings = 0, i;

                //printf("inside print_multi_balance!!\n");
                string = strtok_r(NULL, " ", &saveptr);
                while ((string != NULL)) {
                    //printf("string=%s\n", string);
                    string = strtok_r(NULL, " ", &saveptr);
                    total_strings++;
                }
                char **strings_given;
                int * hashes_needed;
                int hashes_count;
                strings_given = malloc(total_strings * sizeof (char*));                

                strncpy(buf, init_command, strlen(init_command) + 1);
                string = strtok_r(buf, " ", &saveptr);
                //printf("bufbuf=%s stringstring=%s\n***** total_strings=%d\n", buf, string, total_strings);
                string = strtok_r(NULL, " ", &saveptr);
                for (i = 0; i < total_strings; i++) {
                    //printf("3ddddddddddd %s\n", string);
                    strings_given[i] = malloc((strlen(string) + 1));
                    strncpy(strings_given[i], string, strlen(string) + 1);
                    string = strtok_r(NULL, " ", &saveptr);
                }
               
                // *********************************************** LOCK
                hashes_needed = malloc((total_strings-1) * sizeof (int));
                hashes_count = total_strings-1;
                for (i = 0; i < hashes_count; i++) {
                    hashes_needed[i] = Hash_function(strings_given[i+1]);
                }                
                //for (i = 0; i <  hashes_count; i++) {
                    //printf("%d  ", hashes_needed[i]);
               // }
                //printf("\n");
                qsort(hashes_needed,hashes_count, sizeof(int), cmpfunc ); //sort locks
                //for (i = 0; i < hashes_count; i++) {
                    //printf("%d  ", hashes_needed[i]);
                //}
               // printf("\n");               
                for (i = 0; i < hashes_count; i++) {
                    if (i == hashes_count-1 || hashes_needed[i] != hashes_needed[i+1]) {
                        pthread_mutex_lock(&Mutextable[i]);
                    }
                }
                // *********************************************** LOCK
                
                string = strtok_r(NULL, " ", &saveptr);
                int w = 0, f = 0;
                
                for (i = 0; i < total_strings; i++) {
                    TStoixeioyListas stoixeio;
                    
                    del_new_line(strings_given[i]);
                    Name_setValue(&stoixeio, strings_given[i]);
                    
                    typos_deikti saltas = LIST_anazitisi2(Hashtable[Hash_function(strings_given[i])], stoixeio);
                    if (saltas != NULL) {
                        if (w == 0) {
                            sprintf(bufp, "Success. Balance (%s:%d)", strings_given[i], (Dedomena_return(saltas)->init_amount));
                            w++;
                        } else {
                            sprintf(bufpp, "/(%s:%d)", strings_given[i], (Dedomena_return(saltas)->init_amount));
                            w++;
                            strcat(bufp, bufpp);
                        }
                    } else {
                        if (f == 0) {
                            sprintf(bufp, "Error. Balance  (%s)", strings_given[i]);
                            f++;
                        } else {
                            sprintf(bufpp, "/(%s)", strings_given[i]);
                            f++;
                            strcat(bufp, bufpp);
                        }
                    }
                }
                strcat(bufp, "\n");
                strncpy(buf, bufp, sizeof (bufp));
                w = 0;
                f = 0;
                
                // *********************************************** UNLOCK
                for (i = 0; i < hashes_count; i++) {
                    if (i == hashes_count-1 || hashes_needed[i] != hashes_needed[i+1]) {
                        pthread_mutex_unlock(&Mutextable[i]);
                    }
                }
                // *********************************************** UNLOCK
            } 

			else if (strcmp(string, "print_balance") == 0) {  //print balance
                string = strtok_r(NULL, "\n", &saveptr);
                if (string != NULL) {
                    name = malloc(strlen(string) + 1);
                    if (name == NULL)
                        perror_exit("malloc print_balance");
                    strncpy(name, string, strlen(string) + 1);
                    // *********************************************** LOCK
                    int hashvalue = Hash_function(name);
                    pthread_mutex_lock(&Mutextable[hashvalue]);
					// *********************************************** LOCK
                    TStoixeioyListas stoixeio;
                    Name_setValue(&stoixeio, name);
                    typos_deikti saltas = LIST_anazitisi2(Hashtable[Hash_function(name)], stoixeio);
                    if (saltas != NULL)
                        sprintf(buf, "Success. Balance (%s:%d)\n", name, (Dedomena_return(saltas)->init_amount));
                    else {
                        sprintf(buf, "Error. Balance  (%s)\n", name);
                    }
					// *********************************************** UNLOCK
                    pthread_mutex_unlock(&Mutextable[hashvalue]);
                    // *********************************************** UNLOCK
                }
                free(name);
            } else {
                string = "Unknown command\n";
                strncpy(buf, "Unknown command\n", strlen(string) + 1);
            }



            if (write(my_connect, buf, 512) < 0)
                perror_exit(" write ");

            memset(buf, '\0', sizeof (buf));
            memset(bufp, '\0', sizeof (bufp));
            memset(bufpp, '\0', sizeof (bufpp));

            free(init_command);
        }

        printf("Closed connection \n");

        close(my_connect);
    } // while (1)



    return 0;
}

void perror_exit(char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int Hash_function(char* name) { //convert every name into an id based on its length

    int i, id = 0;
    for (i = 0; i < strlen(name); i++) {
        id += name[i];
    }
    return id % Hash_Size;
}

void del_new_line(char *str) { //replace newline character with \0 
    int i;
    for (i = 0; i < strlen(str); i++) {
        //printf("%d:%c",i,str[i]);
        if (str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}

// -------------------prod-cons.c---------------------------------------------------

void place(pool_t * pool, int data, int pool_size) {
    pthread_mutex_lock(&mtx);
    while (pool->count == pool_size) {
        pthread_cond_wait(&cond_nonfull, &mtx);
    }
    pool->end = (pool->end + 1) % pool_size;
    pool->data[pool->end] = data;
    pool->count++;
    pthread_cond_broadcast(&cond_nonempty);
    pthread_mutex_unlock(&mtx);
}

int obtain(pool_t * pool, int pool_size) {
    int data = 0;
    pthread_mutex_lock(&mtx);
    while (pool->count == 0) {
        pthread_cond_wait(&cond_nonempty, &mtx);
    }
    data = pool->data[pool->start];
    pool->start = (pool->start + 1) % pool_size;
    pool->count--;
    pthread_cond_broadcast(&cond_nonfull);
    pthread_mutex_unlock(&mtx);
    return data;
}

// -------------------prod-cons.c---------------------------------------------------


// http://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

// http://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm


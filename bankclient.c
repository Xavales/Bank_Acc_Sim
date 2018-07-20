#include <stdio.h>
#include <sys/types.h>/* sockets */
#include <sys/socket.h>/* sockets */
#include <netinet/in.h>/* internet sockets */
#include <unistd.h>/* read , write , close */
#include <netdb.h>/* gethostbyaddr */
#include <stdlib.h>/* exit */
#include <string.h>/* strlen */


void perror_exit(char * message);

int main(int argc, char * argv []) {

    int serverport, sock;
    char buf [512];
    char *command_file = NULL;
    char *serverhost = NULL;
    FILE *file;

    struct sockaddr_in server;
    struct sockaddr * serverptr = (struct sockaddr *) &server;
    struct hostent * rem;


    //choose your arguments (./bankclient -h <serverhost> -p <serverport> -i <commandfile> order doesnt matter)
    if (argc != 7) {
        printf("Wrong parameters given...\n");
        printf("order matters not\ninput parameters: -h <serverhost> -p <serverport> -i <commandfile>\n");
        exit(1);
    } else {
        int i;
        for (i = 1; i < argc; i += 2) {

            if (strcmp(argv[i], "-p") == 0) {
                serverport = atoi(argv[i + 1]);
                continue;
            }
            else if (strcmp(argv[i], "-h") == 0) {
                serverhost = argv[i + 1];
                /* Find server address */
                if ((rem = gethostbyname(serverhost)) == NULL) {
                    herror("gethostbyname ");
                    exit(1);
                }
                continue;
            } else if (strcmp(argv[i], "-i") == 0) {
                command_file = argv[i + 1];
                continue;
            } else {
                printf("Invalid parameters\n");
                exit(1);
            }
        }
    }



    /* Create socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        perror_exit(" socket ");


    server.sin_family = AF_INET;

    /* Internet domain */
    memcpy(&server.sin_addr, rem -> h_addr, rem -> h_length);
    server.sin_port = htons(serverport);

    /* Server port */
    /* Initiate connection */

    if (connect(sock, serverptr, sizeof (server)) < 0)
        perror_exit("connect");

    printf("Connecting to %s port %d\n", serverhost, serverport);

    if (command_file != NULL) {

        file = fopen(command_file, "r");
    }

    char *string, buf2[256], *end_of_file;
    int time, ms;

    while (1) {

        if (file != NULL)
            end_of_file = fgets(buf, sizeof ( buf), file); /* Read from file*/


        if ((end_of_file == NULL) || (file == NULL)) {
            printf("Enter your command :");
            fgets(buf, sizeof ( buf), stdin); /* Read from stdin */
        }

        strcpy(buf2, buf);
        string = strtok(buf2, " ");

        if (strcmp(string, "exit\n") == 0) {
            printf("....client is about to exit...\n");
            break;
        }

        if (strcmp(string, "sleep") == 0) {
            string = strtok(NULL, "\n");
            if (string != NULL) {
                time = 1000 * atoi(string);
                ms = time / 1000;
                printf("sleeping for %dms\n", ms);
                usleep(time);
            }
        }

        else {

            if (write(sock, buf, 512) < 0)
                perror_exit("write");

            if (read(sock, buf, 512) < 0)
                perror_exit("read");

            printf("Responding : %s ", buf);
        }
    }

    if (file != NULL)
        fclose(file);
    close(sock);
    /* Close socket and exit */

    return 0;
}

void perror_exit(char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}



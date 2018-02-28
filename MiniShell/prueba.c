#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 4096

int main(void) {
    char    buf[MAXLINE];
    pid_t   pid;
    int     status, i=0;
    char    *token;
    char    **Args;
    const char delim[2] = " ";                        /*Delimiter that will be used in strtok()*/

    token = (char *)malloc(sizeof(char*));
    Args = (char **)malloc(5*sizeof(char*));        /* Allocate memory for an array of strings(parameters)*/

    printf("> ");                                     /* print prompt */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        i=0;
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';              /* replace newline with null */

        token = strtok(buf,delim);                    /* Tokenize whats in the buffer */
        Args[i++] = token;
        //token = strtok(NULL,delim);
        //arArgs[i++] = token;

        
        while(token != NULL && i<5){                  /* While there's more to read or the maximum */
            token = strtok(NULL,delim);               /* has been reached */
            Args[i++] = token;
        }
        if(i<5){
            for (i;i<5;i++) Args[i] = NULL;         /* Complete the rest of the array with NULL*/
        }
        else Args[5] = 0;

        if ((pid = fork()) < 0) {
            printf("fork error");
            exit(1);
        } else if (pid == 0) {                       /* child process */
            //execlp(buf, buf, arArgs[1], (char *)0);
            //execlp(arArgs[0], arArgs[0], arArgs[1],arArgs[2],arArgs[3],arArgs[4], (char *)0);
            execvp(Args[0],Args);
            printf("couldn’t execute: %s\n", buf);
            exit(127);
        }
        /* parent process*/
        if ((pid = waitpid(pid, &status, 0)) < 0){
            printf("waitpid error");
            exit(1);
        }
		printf ("Child status %d\n", WEXITSTATUS(status));
        printf("> ");
    }
    exit(0);
}

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 4096


int  main(void) {

char buf[MAXLINE];
pid_t pid,child;
int status,i;
char **Args;
char *token;
const char delim[2]= " ";
char *Help="help";
char *Exit="exit";


token=(char *)malloc(sizeof(char*));
Args=(char **)malloc(sizeof(char*));



printf("Enter help for information \n" );
printf("Enter exit to finish the Minishell \n" );
printf("> ");
while (fgets(buf,MAXLINE,stdin)!= NULL) {
i=0;
if (buf[strlen(buf) -1] == '\n')
    buf[strlen(buf) -1] = '\0';

token=strtok(buf,delim);
Args[i++]=token;

while(token != NULL && i<5){
    token = strtok(NULL,delim);
    Args[i++] = token;
}
if(i<5){
    for (i;i<5;i++) Args[i] = NULL;
}
else Args[5] = 0;



int h=strcmp(buf,Help);
int q=strcmp(buf,Exit);




if((pid=fork())< 0)
{
  printf("fork error");
exit(127);
}
else if (pid == 0) {
  /*
  Este es el proceso hijo
  */

  if(h==0)
  {
    printf("Lista de todos los comandos del Mini Shell\n" );
    printf("cal    --Saca el calendario\n" );



}else if (q==0) {
  static char *argv[ ]={"kill","0"};
  execv("/bin/kill",argv);
  exit(127);    // Only if execv() fails
}else
  {
    execvp(Args[0],Args);
    printf("No se pudo ejecutar el comando: %s\n",buf );
    exit(127);
  }


}
/*
Este es el padre
*/
if (waitpid(pid,NULL,0)) {
  /* code */
printf ("Child status %d\n", WEXITSTATUS(status));

}

printf("> ");

}
/*
Libera la memoria
*/
free(token);
free(Args);
  exit(0);
}

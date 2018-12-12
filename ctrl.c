#include "imports.h"

void process(char *arg){
  int semd,key = ftok("story.txt",999);
  if(strcmp(arg,"-c")){
    semd = semget(key,1,IPC_CREAT|IPC_EXCL|0644);
    struct sembuf * alt;
    alt.sem_op = 1;
    alt.sem_num = 0;
    alt.sem_flag
    semop(semd,alt,1);
    open("story.txt",);
  }
  if(strcmp(arg,"-r")){
    semd = semget(key,1,0644);
    semctl(semd,0,IPC_RMID);
  }
  if(strcmp(arg,"-v"))
}

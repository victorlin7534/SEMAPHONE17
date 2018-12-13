#include "imports.h"

void process(char *arg,key_t key){
  if(strcmp(arg,"-c")) create(key);
  else if(strcmp(arg,"-r")) delete(key);
  else if(strcmp(arg,"-v")) view(key);
}

void create(key_t  key){
  int semd = semget(key,1,IPC_CREAT|IPC_EXCL|0644);
  int shmid = shmget(key,10000,0644|IPC_CREAT);
  int file = open("story.txt",O_TRUNC|O_CREAT|0644);
  struct sembuf * alt;
  alt->sem_op = 1;
  alt->sem_num = 0;
  alt->sem_flg = SEM_UNDO;
  semop(semd,alt,1);
}

void delete(key_t  key){
  int semd = semget(key,1,0644);
  int shmid = shmget(key,10000,0644);
  int file = open("story.txt",O_RDONLY);

  char story[10000];
  read(file,story,10000);
  printf("%s\n",story);

  semctl(semd,0,IPC_RMID);
  shmctl(shmid,IPC_RMID,NULL);
  close(file);
  remove("story.txt");
}

void view(key_t key){
  int file = open("story.txt",O_RDONLY);
  char story[10000];
  read(file,story,10000);
  printf("%s\n",story);
  close(file);
}

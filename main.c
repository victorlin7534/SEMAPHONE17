#include "imports.h"

int main(int argc, char * argv[]){
  key_t key = ftok("story.txt",999);
  process(argv[1],key);
  int shmid = shmget(key,10000,0644);
  int file = open("story.txt",O_WRONLY);
  int semd = semget(key,1,0644);

  struct sembuf * alt;
  alt->sem_op = -1;
  alt->sem_num = 0;
  alt->sem_flg = SEM_UNDO;
  semop(semd,alt,1);

  char * data = shmat(shmid,0,0);
  printf("%s\n",data);
  printf("type in the next line of the story: ");
  char input[10000];
  fgets(input,10000,stdin);
  write(file,input,10000);
  data = input;

  alt->sem_op = 1;
  semop(semd,alt,1);
  return 0;
}

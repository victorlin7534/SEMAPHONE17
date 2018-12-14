#include "imports.h"

void create(key_t  key){
  int semd = semget(key,1,IPC_CREAT|IPC_EXCL|0644);
  if(semd==-1) printf("%s\n",strerror(errno));
  else{
  	union semun data;
  	data.val = 1;
  	semctl(semd,0,SETVAL,data);
  } 

  int shmid = shmget(key,10000,0644|IPC_CREAT);
  if(shmid==-1) printf("%s\n",strerror(errno));

  int file = open("story.txt",O_TRUNC|O_CREAT,0644);
  if(file==-1) printf("%s\n",strerror(errno));
}

void delete(key_t  key){
  	int semd = semget(key,1,0644);
  	if(semd==-1) printf("%s\n",strerror(errno));
  	else{
  		while(semctl(semd,0,GETVAL)==0) printf("checking resource availability\n");

		int shmid = shmget(key,10000,0644);
		if(shmid==-1) printf("%s\n",strerror(errno));
		else shmctl(shmid,IPC_RMID,NULL);

		int file = open("story.txt",O_RDONLY);
		if(file==-1) printf("%s\n",strerror(errno));
		else{
			char story[10000];
			read(file,story,10000);
			printf("%s\n",story);
			close(file);
			remove("story.txt");
		}

		semctl(semd,0,IPC_RMID);
	}
}

void view(key_t key){
  int file = open("story.txt",O_RDONLY);
  if(file==-1) printf("%s\n",strerror(errno));
  else{
  	  char story[10000];
	  read(file,story,10000);
	  printf("%s\n",story);
	  close(file);
  }
}


void edit(key_t key){
  	int semd = semget(key,1,0644);
  	if(semd==-1) printf("%s\n",strerror(errno));
  	else{
  		while(semctl(semd,0,GETVAL)==0) printf("checking resource availability\n");

  		struct sembuf * alt;
		alt->sem_op = -1;
		alt->sem_num = 0;
		alt->sem_flg = SEM_UNDO;
		semop(semd,alt,1);

		int shmid = shmget(key,10000,0644);
		if(shmid==-1) printf("%s\n",strerror(errno));
		else{
			int file = open("story.txt",O_RDONLY);
			if(file==-1) printf("%s\n",strerror(errno));
			else{
				char * data = shmat(shmid,0,0);
				printf("previously written data: %s\n",data);
				printf("type in the next line of the story: ");
				char input[10000];
				fgets(input,10000,stdin);
				write(file,input,10000);
				strcpy(data,input);
			}
		}

		alt->sem_op = 1;
  		semop(semd,alt,1);
	}
}

void process(char *arg,key_t key){
  if(strcmp(arg,"-c")) create(key);
  else if(strcmp(arg,"-r")) delete(key);
  else if(strcmp(arg,"-v")) view(key);
  edit(key);
}
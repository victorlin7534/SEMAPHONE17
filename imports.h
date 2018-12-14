#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

union semun{
  int val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};

void process(char *arg,key_t key);
void create(key_t key);
void delete(key_t key);
void view(key_t key);
void edit(key_t key);

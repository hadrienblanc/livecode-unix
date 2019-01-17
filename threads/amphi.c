#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>


int main(int argc, char const *argv[]) {
  /* code */
  key_t key = ftok("./a.out", 123);

  int shm_id =  shmget(key, 64, SHM_READ | SHM_WRITE);

  char * p = shmat(shm_id, NULL, SHM_READ | SHM_WRITE);

  return 0;
}

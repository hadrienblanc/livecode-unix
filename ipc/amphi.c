#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(int argc, char const *argv[]) {
  /* code */
  key_t key = ftok("./a.out", 456);

  int shm_id =  shmget(key, 128,  SHM_R | SHM_W );

  if (shm_id == -1)
  {
      printf("shm_id == -1\n");
      shm_id =  shmget(key, 128,  SHM_R | SHM_W | IPC_CREAT);
  }

  char * p = shmat(shm_id, NULL, SHM_R | SHM_W);

  if (argv[1][0] == '1')
  {
    memset(p, '.', 64);
    int n = 0;
    while (1) {
      printf("%d %s\n",n, p);
      sleep(3);
      n++;
    }
  }
  else
  {
      int j = 0;
      while (j < 64) {
        p[j] = argv[1][0];
        sleep(3);
        j++;
      }
  }


  return 0;
}

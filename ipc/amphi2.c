#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <stdio.h>


int main(int argc, char const *argv[]) {
  /* code */
  key_t key = ftok(argv[0], 888);

  int shmid = shmget(key, 64, SHM_R | SHM_W);

  if (shmid == -1)
  {
    shmid = shmget(key, 64, SHM_R | SHM_W | IPC_CREAT);
    printf("On crée la mémoire partagée :) !\n");
  }
  printf("shmid = %d\n", shmid);

  char * ptr = shmat(shmid, NULL, SHM_R | SHM_W);

  if (argv[1][0] == '1') {

      memset(ptr, '.', 64);
      int n = 0;
      while (1) {
        printf("%d %s\n", n, ptr);
        n++;
        sleep(2);
      }
  } else
  {
    int i = 0;
    while (i < 64) {
      ptr[i] = argv[1][0];
      sleep(2);
      i++;
    }
  }

  return 0;
}

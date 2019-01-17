#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  int key = ftok(argv[0], 55);

  int idshm = shmget(key, 64, SHM_W | SHM_R);

  if (idshm == -1) {
    printf("creation\n");
    idshm = shmget(key, 64, SHM_W | SHM_R | IPC_CREAT);
  }

  char *ptr = shmat(idshm, 0, SHM_W | SHM_R );

  if (argv[1][0] == '1')
  {
    memset(ptr, '.', 64);
    int n = 0;
    while (1) {
      printf("%d %s\n", n, ptr);
      n++;
      sleep(4);
    }

  } else
  {
    int j = 0;

    while (j < 64) {
      ptr[j] = argv[1][0];
      printf("updated\n");
      sleep(4);
      j++;

      /* code */
    }
  }

  return 0;
}

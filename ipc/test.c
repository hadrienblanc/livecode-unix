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
  int pid = ftok(*argv, 142);
  printf("[+] pid : %i\n", pid);

  int shm_id = shmget(pid, 64, IPC_CREAT | SHM_R | SHM_W);

  printf("%d\n", shm_id);
  char *adr = shmat(shm_id, NULL, SHM_R | SHM_W);

int n = 0;
if (argv[1][0] == '1')
 {
   memset(adr, '.', 64);

  while (1) {
    printf("%d %s\n", n, adr);
    sleep(4);
    n++;
  }

}
else
{
  int j = 0;
  while (j < 64) {
    adr[j] = argv[1][0];
    sleep(4);
    j++;
  }

}

  return 0;
}

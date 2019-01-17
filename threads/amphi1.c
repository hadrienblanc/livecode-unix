#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *godownload(void *website)
{
  char *s = website;
  pthread_mutex_trylock(&mutex);
  count++;
  sleep(2);
  pthread_mutex_unlock(&mutex);
  printf("%s\n", s);
  pthread_exit(0);
}
void *godownloadAll(void *website)
{
  char *s = website;
  pthread_mutex_trylock(&mutex);
  count++;
  sleep(3);
  pthread_mutex_unlock(&mutex);
  printf("%s\n", s);

  pthread_exit(0);
}

int main(int argc, char const *argv[])
{
  char *w1 = "www.google.fr";
  char *w2 = "www.facebook.fr";

  pthread_t t1;
  pthread_t t2;


//  godownload(w1);
//  godownloadAll(w2);

  pthread_create(&t1, NULL, godownload, w1);
  pthread_create(&t2, NULL, godownloadAll, w2);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
//  godownload(w1);
//  godownload(w2);
  /* code */
  return 0;
}

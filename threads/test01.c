/*
**
*/
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void  *fun1(void *arg)
{
  char * s;

  if (pthread_mutex_lock(&lock) == 0)
  {
    s = ((char *)arg);
    printf("download : %s\n", s);
    sleep(2);

    pthread_mutex_unlock(&lock);
  }


  pthread_exit(0);

}

void  *fun2(void *arg)
{
  char * s;

  if (pthread_mutex_lock(&lock) == 0)
  {

  s = ((char *)arg);
  printf("download : %s\n", s);
  sleep(4);

    pthread_mutex_unlock(&lock);
  }
  pthread_exit(0);
}

int         main(int ac, char *argv)
{
  pthread_t th1;
  pthread_t th2;

  char * s1 = "www.google.fr";
  char * s2 = "www.facebook.com";

//  pthread_mutex_init();

  pthread_create(&th1, NULL, fun1, s1);
  pthread_create(&th2, NULL, fun2, s2);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  // without threads
  //fun1(s1);
  //fun2(s2);

  return (0);
}

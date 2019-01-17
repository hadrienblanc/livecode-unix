#include <sys/socket.h>
#include <stdlib.h> // exit
#include <stdio.h> // printf

int   main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(PF_INET, SOCK_STREAM, 0);

  if (socket_id < 0) {
    printf("[error] socket\n");
    exit(EXIT_FAILURE);
  }


  /* code */
  return 0;
}

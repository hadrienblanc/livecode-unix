#include <sys/socket.h>
#include <stdlib.h> // exit
#include <stdio.h> // printf

#include <netinet/in.h> // bind - types

#include <sys/select.h> // select

int   main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(PF_INET, SOCK_STREAM, 0);

  if (socket_id < 0) {
    printf("[error] socket\n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in name;

  name.sin_family = AF_INET;
  name.sin_port = htons (5558);
  name.sin_addr.s_addr = htonl (INADDR_ANY);

  int ret = bind(socket_id, (struct sockaddr *) &name, sizeof(struct sockaddr_in));
  if (ret < 0 ) {
    printf("[error] bind\n");
    exit(EXIT_FAILURE);
  }

  ret = listen(socket_id, 4);

  if (ret < 0) {
    printf("[error] listen\n");
    exit(EXIT_FAILURE);
  }

  fd_set my_active_set;

  FD_ZERO(&my_active_set);
  FD_SET(socket_id, &my_active_set);

  int fd_max = socket_id;
  while (1)
  {

    select(fd_max + 1, &my_active_set, NULL, NULL, NULL);

    printf("[+] out of select\n");

    for (int i = 0; i <= fd_max ; i++)
    {
      if (FD_ISSET(i, &my_active_set))
      {
        if (i == socket_id)
        {
          printf("[+] new connection\n");

        }
        else
        {
          printf("[+] hangle client\n");
        }
      }

    }


  }


  /* code */
  return 0;
}

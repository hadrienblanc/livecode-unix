#include <sys/socket.h>
#include <stdlib.h> // exit
#include <stdio.h> // printf

#include <netinet/in.h> // bind - types

#include <sys/select.h> // select

#include <sys/types.h> // read
 #include <sys/uio.h> // read
 #include <unistd.h> //read

int handle_client(int fd)
{
  char buffer[100];

  read(fd, buffer,100);
  printf("[+] client sent = '%s'\n", buffer);

  if (buffer[0] == 'q')
    return 1;
  return 0;
}

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
  fd_set my_set;

  FD_ZERO(&my_set);
  FD_SET(socket_id, &my_set);

  int fd_max = socket_id;
  while (1)
  {
    my_active_set = my_set;
    printf("select in\n");
    select(fd_max + 1, &my_active_set, NULL, NULL, NULL);

    printf("[+] out of select\n");

    for (int i = 0; i <= fd_max ; i++)
    {
      if (FD_ISSET(i, &my_active_set))
      {
        if (i == socket_id)
        {
          printf("[+] New connection\n");

          int new_socket;
          struct sockaddr_in clientname;
          int size = sizeof (struct sockaddr);

          new_socket = accept(socket_id,
          (struct sockaddr *)&clientname, &size);

          FD_SET(new_socket, &my_set);
          if (new_socket > fd_max)
            fd_max = new_socket;
        }
        else
        {
          printf("[+] hangle client\n");
          int goQuit = handle_client(i);

          if (goQuit == 1)
          {
            close(i);
            FD_CLR(i, &my_set);
          }
        }
      }

    }


  }


  /* code */
  return 0;
}

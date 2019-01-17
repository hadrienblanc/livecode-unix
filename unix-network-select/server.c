#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int handle_client(int fd)
{
  char buffer[100];

  int ret = read(fd, buffer, 100);

    if (ret < 0 ) {
      printf("[error] read()\n");
    }

  printf("Client sent them message : '%s'\n", buffer);

  if (buffer[0] == 'q')
    return 1;
  else
    return 0;
}

int main(int argc, char const *argv[]) {
  /* code */

  int socket_id;
  fd_set my_set;
  fd_set my_active_set;

  struct sockaddr_in clientname;

  struct sockaddr_in name;

  socket_id = socket(PF_INET, SOCK_STREAM, 0);

  if (socket_id < 0 ) {
    printf("[error] socket\n");
    exit(EXIT_FAILURE);
  }

  name.sin_family = AF_INET;
  name.sin_port = htons (5558);
  name.sin_addr.s_addr = htonl (INADDR_ANY);

  int ret = bind(socket_id, (struct sockaddr *) &name, sizeof(struct sockaddr_in));
  if (ret < 0 ) {
    printf("[error] bind\n");
    exit(EXIT_FAILURE);
  }

  ret = listen(socket_id, 4);
  if (ret < 0 ) {
    printf("[error] listen()\n");
    exit(EXIT_FAILURE);
  }

  FD_ZERO (&my_active_set);
  FD_SET(socket_id, &my_active_set);
  int fd_max = socket_id;

  while(1)
  {
    my_set = my_active_set;
    ret = select(fd_max + 1, &my_set, NULL, NULL, NULL);

printf("out of select %i\n", ret);
    if (ret < 0 ) {
      printf("[error] select()\n");
      exit(EXIT_FAILURE);
    }


    for (int i = 0; i <= fd_max ; i++)
    {
      if (FD_ISSET(i, &my_set))
      {
        if (i == socket_id)
        {
          int new_socket;

          printf("accept...\n");
          int size = sizeof(struct sockaddr_in);
          new_socket = accept(socket_id,
          (struct sockaddr *) & clientname, &size);
          if (new_socket > fd_max)
            fd_max = new_socket;
          printf("[+]New connection [%d]\n", new_socket);
          FD_SET(new_socket, &my_active_set);
          printf("[ok]\n");
        }
        else
        {
          printf("[handle client %d]\n", i);
          int goQuit = handle_client(i);

          if (goQuit == 1)
          {
            close(i);
            FD_CLR(i, &my_active_set);
          }
        }
      }
    }

  }

  return 0;
}

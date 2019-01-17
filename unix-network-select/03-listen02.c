#include <sys/socket.h>
#include <stdlib.h> // exit
#include <stdio.h> // printf

#include <netinet/in.h> // bind - types
       #include <unistd.h>

int hadrien_handle_client(int fd)
{
  char buffer[200];

  int ret = read(fd, buffer, 200);

  if (ret < 0) {
    printf("Read ERRoR\n");
    exit(EXIT_FAILURE);
  }

  printf("[+] The client sent '%s'\n", buffer);

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

  fd_set current_set;
  fd_set my_set;

  FD_ZERO(&my_set);
  FD_SET(socket_id, &my_set);

  int fd_max = socket_id;
  while (1)
  {
    current_set = my_set;
    printf("--select in --\n");
    select(fd_max + 1, &current_set, NULL, NULL, NULL);
    printf("--select out --\n");

    for (int i = 0 ; i <= fd_max ; i++)
    {
      if (FD_ISSET(i, &current_set))
        {
          if (i == socket_id) {

            struct sockaddr_in client;
            int size = sizeof(struct sockaddr_in);
            int new_socket = accept(socket_id, (struct sockaddr *)&client, &size);

            if (new_socket < 0) {
              printf("Error accept\n");
            }

            FD_SET(new_socket, &my_set);
            printf("[+] New client connected (%d)\n", new_socket);
            if (fd_max < new_socket)
              fd_max = new_socket;
          }
          else {
            int goQuit = hadrien_handle_client(i);

            if (goQuit) {
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

#include <sys/socket.h>
#include <stdlib.h> // exit
#include <stdio.h> // printf
       #include <unistd.h>

#include <netinet/in.h> // bind - types

#include <sys/select.h> // select


int handle_client(int fd) {
  char buffer[100];

  int ret = read(fd, buffer, 100);

  if (ret < 0) {
    printf("[-] read error\n");
    exit(EXIT_FAILURE);
  }

  printf("[+] client sent '%s'\n", buffer);


  if (buffer[0] == 'q' || ret == 0)
    return 1;
  return 0;
}

int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);


  struct sockaddr_in name;

  name.sin_family = AF_INET;
  name.sin_port = htons (5556);
  name.sin_addr.s_addr = htonl (INADDR_ANY);

  int ret = bind(socket_id, (struct sockaddr *)&name, sizeof(struct sockaddr_in));

  if (ret < 0) {
    printf("[+] error bind()\n");
    exit(EXIT_FAILURE);
  }

  ret = listen(socket_id, 5);
  if (ret < 0) {
    printf("[+] error listen()\n");
    exit(EXIT_FAILURE);
  }

  fd_set my_set;
  fd_set current_set;

  FD_ZERO(&my_set);
  FD_SET(socket_id, &my_set);

  int fd_max = socket_id;
  while (1) {
    current_set = my_set;
    printf("[+] Select in\n");
    select(fd_max + 1, &current_set, NULL, NULL, NULL);
    printf("[+] Select out\n");

    for (int i = 0 ; i <= fd_max ; i++)
    {
      if (FD_ISSET(i, &current_set)) {

        if (i == socket_id) {

          struct sockaddr_in clientname;

          int len = sizeof(struct sockaddr_in);

          int new_socket = accept(socket_id, (struct sockaddr *)&clientname, &len);
          if (new_socket < 0)
            printf("error accept\n");
          FD_SET(new_socket, &my_set);

          if (new_socket > fd_max)
          fd_max = new_socket;

        } else {

          int isQuit = handle_client(i);
          if (isQuit)
          {
            close(i);
            FD_CLR(i, &my_set);
          }
        }

      }
    }

    /* code */
  }

  return 0;
}

/*
struct sockaddr_in name;

name.sin_family = AF_INET;
name.sin_port = htons (5558);
name.sin_addr.s_addr = htonl (INADDR_ANY);

*/

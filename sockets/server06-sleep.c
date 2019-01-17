#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in

#include <stdio.h> // printf
#include <unistd.h>// close // fork
#include <stdlib.h> // exit
#include <string.h> // memset

int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(4242);

  bind(socket_id, (struct sockaddr *)&server_address, sizeof(server_address));

  if (listen(socket_id, 5) == 0) {
    printf("[+] listen(socket_id, 5) OK\n");
  } else {
    printf("[-] listen(socket_id, 5) ERROR\n");
  }

  int client_socket = 0;
  struct sockaddr_in client_address;
  int client_len = 0;

  char buffer[100];
  while(1)
  {
    printf("[+] waiting client\n");
    client_socket = accept(socket_id,(struct sockaddr *)&client_address, &client_len);

    if (client_socket != -1)
    {
      printf("[+] Client connected\n");
    } else {
      printf("[-] accept error\n");
    }

    if(fork() == 0)
    {
      memset(buffer, 0, 100);
      read(client_socket, &buffer, 100);
      printf("[+] client sent : %s\n", buffer);
      sleep(3);
      write(client_socket, "OUI", 4);
      printf("[+] server sent : OUI\n");
      close(client_socket);
      exit(0);
    }
    else {
      close(client_socket);
    }
  }

  return 0;
}

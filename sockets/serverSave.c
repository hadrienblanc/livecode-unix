#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h> // sockaddr_in
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_id != -1)
  {
    printf("[+] Socket created\n");
  } else {
    printf("ERROR socket\n");
    exit(0);
  }

  struct sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(4242);

  int ret = bind(socket_id,
    (struct sockaddr *)&server_address,
    sizeof(struct sockaddr_in));

  if (ret != -1)
  {
    printf("[+] Bind OK\n");
  } else {
    printf("ERROR bind()\n");
    exit(0);
  }

  ret = listen(socket_id, 5);

  if (ret != -1)
  {
    printf("[+] Listen OK\n");
  } else {
    printf("ERROR listen()\n");
    exit(0);
  }

     // ACCEPT DES CONNEXION !!!
     struct sockaddr_in client_address;

    int len;

    while (1)
    {

    int socket_client = accept(socket_id,
    (struct sockaddr *)&client_address,
    &len);

    int pid = fork();

    if (pid == 0)
    {
      close(socket_id);

    if (socket_client != -1)
    {
      printf("[+] New client OK !\n");
    } else {
      printf("ERROR accept()\n");
      exit(0);
    }

    char buffer[100];
    buffer[0] = 0;
    while (buffer[0] != 'q')
    {
      memset(buffer, 0, 100);

      read(socket_client, buffer, 100);
      printf("[+] the client sent : '%s'\n", buffer);
    }
    close(socket_client);
  }
  else
  {
    close(socket_client);

  }

}
  return 0;
}





/*
struct sockaddr_in server_address;

server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = htonl(INADDR_ANY);
server_address.sin_port = htons(4242);
*/

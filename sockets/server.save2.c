#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <arpa/inet.h> // sockaddr_in
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  int socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_id == -1) {
      printf("[-] Error socket\n");
    }
    else {
      printf("[+] socket OK\n");
    }

 // bind
 struct sockaddr_in server_address;

 server_address.sin_family = AF_INET;
 server_address.sin_addr.s_addr = htonl(INADDR_ANY);
 server_address.sin_port = htons(4242);

int ret =
  bind(socket_id,
    (struct sockaddr *)&server_address,
    sizeof(struct sockaddr_in));

    if (ret == -1) {
      printf("[-] Error bind()\n");
      exit(0);
    }
    else {
      printf("[+] bind OK\n");
    }

    ret = listen(socket_id, 6);

    if (ret == -1) {
      printf("[-] Error listen()\n");
      exit(0);
    }
    else {
      printf("[+] listen OK\n");
    }

    struct sockaddr_in client_address;

    int len;

    while (1)
    {

      int socket_client =
      accept(socket_id,
        (struct sockaddr *)&client_address,
        &len);

        if (socket_client == -1) {
          printf("[-] Error accept()\n");
          exit(0);
        }
        else {
          printf("[+] New client connected !\n");
        }

        int pid = fork();

        if (pid == 0)
        {
          close(socket_id);
          char buffer[100];

          while (buffer[0] != 'q') {
            memset(buffer,0, 100);
            read(socket_client, buffer, 100);
            printf("[+] The client sent '%s'\n", buffer);
          }
          printf("[client quit]\n");
          close(socket_client);
          exit(0);
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

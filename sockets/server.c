#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {


int socket_id = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in server_address;

server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = htonl(INADDR_ANY);
server_address.sin_port = htons(4242);


int ret = bind(socket_id,
  (struct sockaddr *)&server_address,
  sizeof(struct sockaddr));


  if (ret == -1) {
    printf("[-] Error bind\n");
    return(0);
  } else {
    printf("[+] bind ok\n");
  }


  ret = listen(socket_id, 8);

  if (ret == -1) {
    printf("[-] Error listen\n");
    return(0);
  } else {
    printf("[+] listen ok\n");
  }

  int socket_client;

  struct sockaddr_in sockaddr_client;
  int len;

  while (1)
  {
    socket_client = accept(socket_id,
      (struct sockaddr *)&sockaddr_client,
      &len);

      int pid = fork();


      if (pid == -1) {
          printf("Error fork (I dont think so)\n");
        return 0;
      }

      if (pid == 0)
      {
        close(socket_id);

        if (socket_client == -1) {
          printf("[-] Error accept\n");
          return(0);
        } else {
          printf("[+] New client connected\n");
        }

        char buffer[100];

        buffer[0] = 0;
        while (buffer[0] != 'q') {
          memset(buffer, 0, 100);
          read(socket_client, buffer, 100);
          printf("[+] the client sent '%s'\n", buffer);
        }

        close(socket_client);
        return 0;
      }
      else // parent
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

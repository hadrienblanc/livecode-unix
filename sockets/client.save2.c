#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <arpa/inet.h> // sockaddr_in
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  int socket_id = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_id == -1) {
    printf("[-] Error socket\n");
  }
  else {
    printf("[+] socket OK\n");
  }

  struct sockaddr_in sai;

  sai.sin_family      = AF_INET;
  sai.sin_addr.s_addr = inet_addr("127.0.0.1");
  sai.sin_port        = htons(4242);


  int ret = connect(socket_id,
    (struct sockaddr *)&sai,
    sizeof(struct sockaddr));

  if (ret == -1) {
    printf("[-] Error connect\n");
  }
  else {
    printf("[+] connect OK\n");
  }

  char buffer[100];
  buffer[0] = 0;

  while (buffer[0] != 'q')
  {
      printf("Bonjour que voulez vous envoyer ?\n");
      scanf("%s", buffer);
      write(socket_id, buffer, strlen(buffer));
  }

  close(socket_id);

  return 0;
}


/*
struct sockaddr_in sai;

sai.sin_family      = AF_INET;
sai.sin_addr.s_addr = inet_addr("127.0.0.1");
sai.sin_port        = htons(4242);
*/

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[]) {
  /* code */
  int socket_id;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in sai;

sai.sin_family      = AF_INET;
sai.sin_addr.s_addr = inet_addr("127.0.0.1");
sai.sin_port        = htons(4242);

  int ret = connect(socket_id,
    (struct sockaddr *)&sai,
    sizeof(struct sockaddr_in));

if (ret == -1) {
  printf("[-] Error connect\n");
  return(0);
} else {
  printf("[+] connection server ok\n");
}

  char buffer[100];
  buffer[0] = 0;
  while (buffer[0] != 'q')
  {
    memset(buffer, 0, 100);

    printf(">Que voulez vous envoyer au serveur ?\n");
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

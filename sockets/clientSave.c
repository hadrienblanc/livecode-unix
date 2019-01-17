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
  printf("Socket created\n");
} else {
  printf("ERROR socket\n");
  exit(0);
}

struct sockaddr_in sai;

sai.sin_family      = AF_INET;
sai.sin_addr.s_addr = inet_addr("127.0.0.1");
sai.sin_port        = htons(4242);

int ret = connect(socket_id,  (struct sockaddr *)&sai, sizeof(struct sockaddr_in));

if (ret != -1)
{
  printf("Connected localhost:4242 OK\n");
} else {
  printf("ERROR connect()\n");
  exit(0);
}

char buffer[100];

while (1)
{
printf("Que voulez vous envoyer au serveur ?\n");
scanf("%s", buffer);

ret = write(socket_id, buffer, strlen(buffer));

if (ret != -1)
{
  printf("[+] write '%s' OK\n", buffer);
} else {
  printf("ERROR write()\n");
  exit(0);
}

  if (buffer[0] == 'q')
  {
    close(socket_id);
    return 0;
  }
}

close(socket_id);
  /* code */
  return 0;
}

/*
struct sockaddr_in sai;

sai.sin_family      = AF_INET;
sai.sin_addr.s_addr = inet_addr("127.0.0.1");
sai.sin_port        = htons(4242);
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> // sockaddr_in

#include <stdio.h> // printf

#include <unistd.h> // close
#include <string.h> // memset

int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);


  struct sockaddr_in sai;

  sai.sin_family      = AF_INET;
  sai.sin_addr.s_addr = inet_addr("127.0.0.1");
  sai.sin_port        = htons(4242);

  int ret = connect(socket_id,(struct sockaddr *)&sai, sizeof(sai));

  if (ret != -1) {
    printf("[+] Connected\n");
  }

  char buffer[100];
  memset(buffer,0,100);

  printf(">Enter your string:");
  scanf("%s",buffer);

  close(socket_id);


  return 0;
}

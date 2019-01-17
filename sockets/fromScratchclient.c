#include <sys/socket.h>
#include <sys/types.h>


int main(int argc, char const *argv[]) {
  int socket_id;

  socket_id = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sai;

  sai.sin_family      = AF_INET;
  sai.sin_addr.s_addr = inet_addr("127.0.0.1");
  sai.sin_port        = htons(4242);

  connect(socket_id, (struct sockaddr *)sai, sizeof(sai));

  char str = "haha";

  write(socket_id, str, strlen(str));

  char buffer[100];
  memset(buffer, 0, 100);

  read(socket_id, buffer, 100);

  close(socket_id);

  return 0;
}

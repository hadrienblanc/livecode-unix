#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in

int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(4242);

  bind(socket_id, (struct sockaddr *)&server_address, sizeof(server_address));


  return 0;
}

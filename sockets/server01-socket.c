#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  return 0;
}

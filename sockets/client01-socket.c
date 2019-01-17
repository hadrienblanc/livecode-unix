#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket( ... );
  /* code */
  return 0;
}

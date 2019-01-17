


int main(int argc, char const *argv[]) {

  int socket_id;

  socket_id = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port   = htons(4242);

  bind(socket_id, &server_address, sizeof(server_address));

  listen(socket_id, 5);

  struct sockaddr_in client_address;

  int new_socket;
  new_socket = accept(socket_id, &client_address, sizeof(client_address));

  return 0;
}

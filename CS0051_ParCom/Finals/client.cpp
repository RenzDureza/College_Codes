#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int client_socket;

void *receive_messages(void *arg) {
  char buffer[BUFFER_SIZE];
  while (true) {
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
      cout << "Disconnected from server." << endl;
      exit(0);
    }
    cout << buffer << flush;

    string msg(buffer);
    if (msg.find("Enter your answer") != string::npos) {
      string answer;
      cout << "Your answer (A/B/C/D): ";
      getline(cin, answer);
      send(client_socket, answer.c_str(), answer.length(), 0);
    }
  }
  return nullptr;
}

int main() {
  struct sockaddr_in server_addr;
  pthread_t recv_thread;

  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    cerr << "Socket creation failed." << endl;
    return 1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

  if (connect(client_socket, (struct sockaddr *)&server_addr,
              sizeof(server_addr)) == -1) {
    cerr << "Connection failed." << endl;
    return 1;
  }

  cout << "Connected to server! Enter your name: ";
  string name;
  getline(cin, name);
  send(client_socket, name.c_str(), name.length(), 0);

  pthread_create(&recv_thread, nullptr, receive_messages, nullptr);
  pthread_join(recv_thread, nullptr);

  close(client_socket);
  return 0;
}

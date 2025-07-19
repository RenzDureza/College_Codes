#include <algorithm>
#include <arpa/inet.h>
#include <array>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 3
#define MAX_QUESTIONS 5

struct ClientInfo {
  int socket;
  string name;
  int score = 0;
};

vector<ClientInfo> clients;

struct Question {
  string text;
  array<string, 4> options;
  char correctAnswer;
};

vector<Question> getQuestions() {
  return {
      {"What is the biggest island of the Philippines?",
       {"A) Luzon", "B) Visayas", "C) Mindanao", "D) Palawan"},
       'A'},
      {"The Philippines consist of how many islands?",
       {"A) 100", "B) 7641", "C) 70 641", "D) 767"},
       'B'},
      {"What is the Philippines national flower?",
       {"A) Sampaguita", "B) Gumamela", "C) Rosas", "D) Kamelya"},
       'A'},
      {"Who is a Philippine national hero?",
       {"A) Kris Aquino", "B) jose Risal", "C) Juan Luna", "D) Sarah Duterte"},
       'C'},
      {"Which among the following is the Philippine national animal?",
       {"A) Askal", "B) Carabao", "C) Philippine Eagle", "D) Tiger"},
       'B'}};
}

void send_to_client(int client_socket, const string &msg) {
  send(client_socket, msg.c_str(), msg.size(), 0);
}

void broadcast(const string &msg) {
  for (auto &client : clients) {
    send_to_client(client.socket, msg);
  }
}

void start_game() {
  cout << "\n--- Trivia Game Started ---\n";
  vector<Question> questions = getQuestions();

  for (int i = 0; i < MAX_QUESTIONS; ++i) {
    const Question &q = questions[i];
    stringstream ss;
    ss << "\n--- Round " << (i + 1) << " ---\n";
    ss << q.text << "\n";
    for (const auto &opt : q.options)
      ss << opt << "\n";
    ss << "Enter your answer (A/B/C/D): ";

    string question_msg = ss.str();
    broadcast(question_msg);

    vector<char> answers(clients.size());
    for (size_t j = 0; j < clients.size(); ++j) {
      char buffer[BUFFER_SIZE] = {};
      recv(clients[j].socket, buffer, BUFFER_SIZE, 0);
      answers[j] = toupper(buffer[0]);
    }

    stringstream result;
    result << "\nCorrect Answer: " << q.correctAnswer << "\n";

    for (size_t j = 0; j < clients.size(); ++j) {
      if (answers[j] == q.correctAnswer) {
        clients[j].score += 10;
        result << clients[j].name << " is Correct! +10 points.\n";
      } else {
        result << clients[j].name << " is Incorrect.\n";
      }
    }

    broadcast(result.str());
    sleep(2);
  }

  cout << "\n--- Final Scores (Server View) ---\n";
  broadcast("\n=== Final Scores ===\n");
  int highest = 0;
  for (auto &c : clients) {
    cout << "[SCORE] " << c.name << ": " << c.score << " points" << endl;
    broadcast(c.name + ": " + to_string(c.score) + " points\n");
    highest = max(highest, c.score);
  }

  cout << "\n--- Winner(s) (Server View) ---\n";
  broadcast("\n=== Winner(s) ===\n");
  for (auto &c : clients) {
    if (c.score == highest) {
      cout << "[WINNER] " << c.name << endl;
      broadcast(c.name + "\n");
    }
  }
}

int main() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("socket");
    return 1;
  }

  int opt = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind");
    return 1;
  }

  if (listen(server_socket, MAX_CLIENTS) < 0) {
    perror("listen");
    return 1;
  }

  cout << "Waiting for " << MAX_CLIENTS << " players to connect...\n";

  while ((int)clients.size() < MAX_CLIENTS) {
    sockaddr_in client_addr{};
    socklen_t len = sizeof(client_addr);
    int client_socket = accept(server_socket, (sockaddr *)&client_addr, &len);
    if (client_socket >= 0) {
      char buffer[BUFFER_SIZE] = {};
      recv(client_socket, buffer, BUFFER_SIZE, 0);
      string name(buffer);

      clients.push_back({client_socket, name});
      cout << name << " has joined.\n";

      string msg = name + " has joined the game.\n";
      broadcast(msg);
    }
  }

  cout << "All players connected! Starting game...\n";
  broadcast("All players connected! Starting the trivia game...\n");
  sleep(1);

  start_game();
  close(server_socket);
  return 0;
}

#include <barrier>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

mutex print_mtx;

string player_names[] = {"Dureza", "How", "Reyes"};
const int player_num = sizeof(player_names)/sizeof(player_names[0]);
const int rounds = 3;

void get_ready(int id);
void start_game(int id);

barrier ready(player_num, [](){
  cout << "\n\n==============================================" << endl;
  cout << "                  GAME START!" << endl;
  cout << "==============================================" << endl;
});

vector<string> moves(player_num);

int main() {
  srand(time(0));
  vector<thread> players;
  for (int i = 0; i < player_num; ++i) {
    players.emplace_back(get_ready, i);
  }

  for (auto& p : players) {
    p.join();
  }

  players.clear();

  int taya = rand() % player_num;

  for (int i = 0; i < rounds; ++i) {
    cout << "\n\n==============================================" << endl;
    {
      lock_guard<mutex> lock(print_mtx);
      cout << "ROUND: " << i + 1 << endl;
      cout << "It: " << player_names[taya] << endl;
      cout << "==============================================" << endl;
    }

    moves = vector<string>(player_num);

    for (int i = 0; i < player_num; ++i) {
      if (i == taya) continue;
      players.emplace_back(start_game, i);
    }

    for (auto& i : players) {
      i.join();
    }

    players.clear();

    int tatayain;
    do {
      tatayain = rand() % player_num;
    } while (tatayain == taya);

    cout << "==============================================" << endl;
    int original_it = taya;
    bool someone_tagged = false;

    for (int i = 0; i < player_num; ++i) {
      if (i == original_it) continue;

      if (!someone_tagged && moves[i] == "running") {
        {
          lock_guard<mutex> lock(print_mtx);
          cout << ">>> " << player_names[i] << " got tagged. He's the new 'It'." << endl;
          this_thread::sleep_for(chrono::milliseconds(300));
        }
        taya = i;
        someone_tagged = true;
      } else {
        {
          lock_guard<mutex> lock(print_mtx);
          cout << ">>> " << player_names[i] << " is safe!" << endl;
          this_thread::sleep_for(chrono::milliseconds(300));
        }
      }
    }
    cout << "----------------------------------------------" << endl;
  }

  cout << "\n==============================================" << endl;
  cout << "         " << player_names[taya] << " is the last 'It'. LOSER!" << endl;
  cout << "==============================================" << endl;

  return 0;
}

void get_ready(int id) {
  {
    lock_guard<mutex> lock(print_mtx);
    cout << "Player: " << player_names[id] << " is getting ready for the game..." << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
  }
  ready.arrive_and_wait();
}

void start_game(int id) {
  string action = rand() % 2 == 0 ? "hidding" : "running";
  {
    lock_guard<mutex> lock(print_mtx);
    moves[id] = action;
    cout << "Player: " << player_names[id] << " is " << action << "." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
  }
}

#include <atomic>
#include <barrier>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <latch>
#include <vector>

using namespace std;

mutex print_mtx;
atomic<int> logged_in_count(0);
int player_num = 0;

struct Question {
  string question;
  string choices[4];
  char answer;
};

char goc[] = {'A', 'B', 'C', 'D'};

vector<Question> questions = {
{"What is the capital of France?", {"A. Paris", "B. London", "C. Rome", "D. Berlin"}, 'A'},
{"What is the largest planet in our solar system?", {"A. Earth", "B. Jupiter", "C. Saturn", "D. Mars"}, 'B'},
{"Which language is primarily used for Android development?", {"A. Kotlin", "B. Swift", "C. C++", "D. JavaScript"}, 'A'}
};

void log_in(int id, latch& my_latch);
bool all_players_logged_in();
void give_question(int id);
void submit_answer(char ans);

int main() {
  cout << "Enter number of players: ";
  cin >> player_num;

  latch my_latch(player_num);
  vector<thread> players;

  for (int i = 0; i < player_num; ++i) {
    players.emplace_back(log_in, i+1, ref(my_latch));
  }

  for (auto& p : players) {
    p.join();
  }

  if (all_players_logged_in()) {
    // start game
    cout << "START GAME" << endl;
  }
  return 0;
}

void log_in(int id, latch& my_latch) {
  {
    lock_guard<mutex> lock(print_mtx);
    cout << "player number: " << id << " is logging in..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  my_latch.arrive_and_wait();
  ++logged_in_count;
  {
    lock_guard<mutex> lock(print_mtx);
    this_thread::sleep_for(chrono::milliseconds(100 * (id % 3 + 1)));
    cout << "Player number: " << id << " is logged in" << endl;

  }
}

bool all_players_logged_in() {
  return logged_in_count == player_num;
}

void submit_answer(char ans) {
  auto submitted = [] () {
    cout << "Done" << endl;
  };

  barrier my_barrier(player_num, submitted);
}



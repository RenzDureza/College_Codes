#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <latch>
#include <barrier>
#include <array>
#include <random>
#include <cctype>

using namespace std;

struct Player {
	string name;
	int score = 0;
	bool isHuman = false;
};

struct Question {
	string text;
	array<string, 4> options;
	char correctAnswer;
};

mutex console_mutex;

vector<Question> getQuestions() {
	return {
		{
			"What is the biggest island of the Philippines?",
			{ "A) Luzon", "B) Visayas", "C) Mindanao", "D) Palawan" },
			'A'
		},
		{
			"The Philippines consist of how many islands?",
			{ "A) 100", "B) 7641", "C) 70 641", "D) 767" },
			'B'
		},
		{
			"What is the Philippines national flower?",
			{ "A) Sampaguita", "B) Gumamela", "C) Rosas", "D) Kamelya" },
			'A'
		},
		{
			"Who is a Philippine national hero?",
			{ "A) Kris Aquino", "B) jose Risal", "C) Juan Luna", "D) Sarah Duterte" },
			'C'
		},
		{
			"Which among the following is the Philippine national animal?",
			{ "A) Askal", "B) Carabao", "C) Philippine Eagle", "D) Tiger" },
			'B'
		}
	};
}

char getRandomAnswer() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 3);
	return "ABCD"[dist(gen)];
}

void enemyThread(Player& enemy, latch& login_latch, barrier<>& round_barrier, const vector<Question>& questions, vector<char>& answers) {
	{
		lock_guard<mutex> lock(console_mutex);
		cout << enemy.name << " is logging in...\n";
	}
	this_thread::sleep_for(chrono::milliseconds(300));

	{
		lock_guard<mutex> lock(console_mutex);
		cout << enemy.name << " is ready!\n";
	}

	login_latch.count_down();
	login_latch.wait();

	for (size_t i = 0; i < questions.size(); ++i) {
		char answer = getRandomAnswer();
		answers[i] = answer;

		{
			lock_guard<mutex> lock(console_mutex);
			cout << enemy.name << " answered: " << answer << "\n";
		}

		round_barrier.arrive_and_wait(); 
	}
}

int main() {
	int numEnemies = 2;

	vector<Player> players(numEnemies + 1);

	cout << "Enter your name: ";
	cin >> players[0].name;
	players[0].isHuman = true;

	for (int i = 0; i < numEnemies; ++i) {
		players[i + 1].name = "Enemy_" + to_string(i + 1);
		players[i + 1].isHuman = false;
	}

	vector<Question> questions = getQuestions();

	latch login_latch(numEnemies + 1);
	barrier round_barrier(numEnemies + 1);

	vector<vector<char>> enemyAnswers(numEnemies, vector<char>(questions.size()));

	vector<thread> threads;
	for (int i = 0; i < numEnemies; ++i) {
		threads.emplace_back(enemyThread, ref(players[i + 1]), ref(login_latch), ref(round_barrier), cref(questions), ref(enemyAnswers[i]));
	}
	
	{
		lock_guard<mutex> lock(console_mutex);
		cout << players[0].name << " is logging in...\n";
	}
	this_thread::sleep_for(chrono::milliseconds(300));

	{
		lock_guard<mutex> lock(console_mutex);
		cout << players[0].name << " is ready!\n";
	}

	login_latch.count_down();
	login_latch.wait();

	vector<char> humanAnswers(questions.size());

	for (int i = 0; i < (int)questions.size(); ++i) {
		const Question& q = questions[i];

		{
			lock_guard<mutex> lock(console_mutex);
			cout << "\n--- Round " << (i + 1) << " ---\n";
			cout << q.text << "\n";
			for (int j = 0; j < 4; ++j) {
				cout << q.options[j] << "\n";
			}
		}

		char answer;
		while (true) {
			lock_guard<mutex> lock(console_mutex);
			cout << "Your answer (A/B/C/D): ";
			cin >> answer;
			answer = toupper(answer);
			if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') break;
			cout << "Invalid input. Please enter A, B, C, or D: " << endl;
		}
		humanAnswers[i] = answer;

		round_barrier.arrive_and_wait();

		{
			lock_guard<mutex> lock(console_mutex);
			if (humanAnswers[i] == q.correctAnswer) {
				players[0].score += 10;
				cout << players[0].name << " is Correct! +10 points.\n";
			} else {
				cout << players[0].name << " is Incorrect.\n";
			}

			for (int j = 0; j < numEnemies; ++j) {
				char eAnswer = enemyAnswers[j][i];
				if (eAnswer == q.correctAnswer) {
					players[j + 1].score += 10;
					cout << players[j + 1].name << " is Correct! +10 points.\n";
				} else {
					cout << players[j + 1].name << " is Incorrect.\n";
				}
			}
		}
		
	}

	for (int i = 0; i < numEnemies; ++i) {
		threads[i].join();
	}

	cout << "\n--- Final Scores ---\n";
	int highest = 0;
	for (int i = 0; i < (int)players.size(); ++i) {
		cout << players[i].name << ": " << players[i].score << " points\n";
		if (players[i].score > highest) highest = players[i].score;
	}

	cout << "\n--- Winner(s) ---\n";
	for (int i = 0; i < (int)players.size(); ++i) {
		if (players[i].score == highest) {
			cout << players[i].name << "\n";
		}
	}

	return 0;
}
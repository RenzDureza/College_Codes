#include <cstdlib>
#include <iostream>
#include <ostream>
#include <thread>
#include <barrier>
#include <string>
#include <chrono>
#include <vector>
#include <latch>
#include <semaphore>

#define STUDENTS 3

using namespace std;
constexpr int NUM_TABLES = 4;
counting_semaphore tableSemaphore(NUM_TABLES);
binary_semaphore nSGreen(1);
binary_semaphore eWGreen(0);

int get_mode();
void prob1(int mode);
void connectStudent(const string& name, const int& id, latch& examLatch);
void tryExamStart(latch& examLatch);
void automated();
void manual();
void prob3(int mode);
void groupMember(int groupId, int memberId, barrier<> &groupBarrier);
void seatGroup(int groupId, int groupSize);
void manualMode();
void automatedMode();
bool invalidInput();

int main() {
  int choice;
  bool run = true;

  do {
    cout << "===== MP3 =====" << endl;
    cout << "[1] Traffic Light System at Intersection" << endl;
    cout << "[2] Online Exam Start" << endl;
    cout << "[3] Synchronized Swimmers Routine" << endl;
    cout << "[4] Restaurant Table Reservation System" << endl;
    cout << "[5] Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (invalidInput()) {
      system("cls");
      continue;
    }
    
    switch (choice) {
      case 1:
        system("cls");
        prob1(get_mode());
        system("pause");
        system("cls");
        break;

      case 2:
        system("cls");
        int mode;
        mode = get_mode();
        if (mode == 1) {
          manual();
        } else if (mode == 2) {
          automated();
        } else {
          cout << "Invalid input" << endl;
        }
        system("pause");
        system("cls");
        break;

      case 3:
        system("cls");
        prob3(get_mode());
        system("pause");
        system("cls");
        break;

      case 4:
        system("cls");
        int c4_mode;
        c4_mode = get_mode();
        if (c4_mode == 1) {
          manualMode();
        } else if (c4_mode == 2) {
          automatedMode();
        } else {
          cout << "Invalid input" << endl;
        }
        system("pause");
        system("cls");
        break;

      case 5:
        system("cls");
        cout << "===== Exit =====" << endl;
        run = false;
        cout << "Thank you for using our program.\nBye!" << endl;
        system("pause");
        system("cls");
        break;

      default:
        system("cls");
        cout << "Invalid input" << endl;
        system("pause");
        system("cls");
        break;
    }
  } while(run);

  return 0;
}

void prob1(int mode) {
  cout << "===== Traffic Light System at Intersection =====" << endl;
  int cycles;

  if (mode == 1) {
    cout << "Enter number of cycles to simulate: ";
    cin >> cycles;
  } else {
    cycles = 3;
  }

  auto northSouth = [&]() {
    for (int i = 0; i < cycles; ++i) {

      nSGreen.acquire();
      cout << "\nNorth-South traffic is moving..." << endl;
      this_thread::sleep_for(chrono::seconds(2));
      cout << "North-South traffic stops..." << endl;
      eWGreen.release();
    }
  };

  auto eastWest = [&]() {
    for (int i = 0; i < cycles; ++i) {
      eWGreen.acquire();
      cout << "East-West traffic is moving..." << endl;
      this_thread::sleep_for(chrono::seconds(2));
      cout << "East-West traffic stops...\n" << endl;
      nSGreen.release();
    }
  };

  thread t1(northSouth);
  thread t2(eastWest);

  t1.join();
  t2.join();
}

void connectStudent(const string& name, const int& id, latch& examLatch) {
	cout << "[Thread " << id << "] " << name << " connecting to online exam...\n";
	this_thread::sleep_for(chrono::seconds(2));
	cout << "[Thread " << id << "] " << name << " successfully connected.\n";
	examLatch.count_down();

}

void tryExamStart(latch& examLatch) {
	cout << "[Exam Starter] Checking if all students are ready to take the exam...\n";
	if(examLatch.try_wait()) {
		cout << "[Exam Starter] All students are connected. Starting exam...\n";
	} else {
		cout << "[Exam Starter] Not all students are connected yet. Waiting for all students before starting.\n";
		examLatch.wait();
		
	}
}

void automated() {
	latch examLatch(STUDENTS);
	cout << "[Main] Students are now starting to connect..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	thread student1(connectStudent, "Hannah", 1, ref(examLatch));
	thread student2(connectStudent, "Carl", 2, ref(examLatch));
	thread student3(connectStudent, "Gabriel", 3, ref(examLatch));
	thread exam_starter(tryExamStart, ref(examLatch));
	student1.join();
	student2.join();
	student3.join();
	exam_starter.join();

	cout << "[Main] Exam Started! You may answer now. Good luck and may the odds be in your favor!" << endl << endl;

}

void manual() {
	string count_string;
	int count;
	string name;

	while(true) {
		cout << "[Main] Enter how many students are going to take the exam: ";
		cin >> count_string;
		break;
	}

	count = stoi(count_string);
	string students[count];
	for (int i = 0; i < count; i++) {
		cout << "[Main] Enter Student#" << i+1 << " Name: ";
		getline(cin>>ws, name);
		students[i] = name;
	}

	cout << "[Main] Students are now starting to connect..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	latch examLatch(count);
	thread student[count];

	for (int i = 0; i < count; i++) {

		student[i] = thread(connectStudent, students[i], (i+1), ref(examLatch));

	}

	for (int i = 0; i < count; i++) {
		student[i].join();
	}

	thread exam_starter(tryExamStart, ref(examLatch));
	exam_starter.join();

	cout << "[Main] Exam Started! You may answer now. Good luck and may the odds be in your favor!" << endl << endl;

}

void prob3(int mode) {
  cout << "===== Synchronized Swimmers Routine =====" << endl;
  int num;

  if (mode == 1) {
    cout << "Enter number of swimmers: ";
    cin >> num;
  } else {
    num = 3;
  }

  auto done = [] () {
    cout << "\nAll swiallowsmmers ready! \nMUSIC START!" << endl;
  };

  barrier bar(num, done);

  auto worker= [&] (int id) {
    cout << "Swimmer number: " << id << " is getting ready..." << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "Swimmer number: " << id << " is ready!" << endl;
    bar.arrive_and_wait();
  };

  vector<thread> swimmers;
  for (int i = 0; i < num; ++i) {
    swimmers.emplace_back(worker, i + 1);
  }

  for (auto& s : swimmers) {
    s.join();
  }
}

void groupMember(int groupId, int memberId, barrier<> &groupBarrier) {
	cout << "Group " << groupId << ", Member " << memberId << " arrived.\n";
	groupBarrier.arrive_and_wait();
	cout << "Group " << groupId << " is placing order.\n";
}

void seatGroup(int groupId, int groupSize) {
	cout << "Group " << groupId << " is requesting a table...\n";
	tableSemaphore.acquire();
	cout << "Group " << groupId << " is seated.\n";

	barrier groupBarrier(groupSize);

	vector<thread> threads;
	for (int i = 1; i <= groupSize; ++i) {
		threads.emplace_back(groupMember, groupId, i, ref(groupBarrier));
	}

	for (auto &t : threads) t.join();

	cout << "Group " << groupId << " is done eating. Table is free.\n";
	tableSemaphore.release();
}

void manualMode() {
  cout << "===== Restaurant Table Reservation System =====" << endl;
	int numGroups;
	cout << "Enter number of groups: ";
	cin >> numGroups;
	cin.ignore();

	vector<pair<int, int>> groupInfo;
	for (int i = 1; i <= numGroups; ++i) {
		int size;
		cout << "Enter number of members in Group " << i << ": ";
		cin >> size;
		cin.ignore();
		groupInfo.emplace_back(i, size);
	}

	vector<thread> groupThreads;
	for (auto&[id, size] : groupInfo) {
		groupThreads.emplace_back(seatGroup, id, size);
	}

	for (auto &t : groupThreads) t.join();
}

void automatedMode() {
  cout << "===== Restaurant Table Reservation System =====" << endl;
	const int numGroups = 4;
	const int minSize = 2;
	const int maxSize = 5;

	srand(time(nullptr));

	vector<thread> groupThreads;

	for (int i = 1; i <= numGroups; ++i) {
		int groupSize = minSize + rand() % (maxSize - minSize + 1);
		cout << "[Auto] Group " << i << " with " << groupSize << " members is arriving...\n";

		groupThreads.emplace_back(seatGroup, i, groupSize);
		this_thread::sleep_for(chrono::milliseconds(300)); // simulate delay }

		for (auto &t : groupThreads) t.join();
  }
}

int get_mode() {
  int mode;

  cout << "===== Modes =====" << endl;
  cout << "[1] Manual" << endl;
  cout << "[2] Automated" << endl;
  cout << "Enter your choice: ";
  cin >> mode;

  return mode;
}

bool invalidInput(){
  if (cin.fail()){
    cin.clear();
    char c;
    while (cin.get(c) && c != '\n');
    cout << "Invalid input. Please try again." << endl;
    return true;
  }
  return false;
}

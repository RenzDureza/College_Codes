#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

// Functions
void makeSandwich();
void prepareCoffeeAndToast();
void washDishes();
void foldClothes();
void prepareFood();
void decorate();
void setupPlaylist();
void packBox(const string &who, int boxCount);
void sequentialPacking();
void parallelPacking();
void gatherMaterials();
void makeSlides();
void printHandouts();
void parallelTask();
void organizeParty();
void handsOn();

int main() {
  int choice;

  do {
    cout << "============================================\n\t\tExercise "
            "#1\n============================================\n";
    cout << "[1] Section 1\n[2] Section 2\n[3] Section 3\n[4] Section 4\n[5] "
            "Section 5\n[6] Hands-on\n[7] EXIT\n";
    cout << "Enter section no#: ";
    cin >> choice;

    switch (choice) {
      case 1:
        makeSandwich();
        system("pause");
        system("cls");
        break;
      case 2:
        prepareCoffeeAndToast();
        system("pause");
        system("cls");
        break;
      case 3:
        parallelTask();
        system("pause");
        system("cls");
        break;
      case 4:
        organizeParty();
        system("pause");
        system("cls");
        break;
      case 5:
        sequentialPacking();
        parallelPacking();
        system("pause");
        system("cls");
        break;
      case 6:
        handsOn(); 
        system("pause");
        system("cls");
        break;
      case 7:
        cout << "Thank you for using our program!\n";
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << "Goodbye!\n";
        system("pause");
        system("cls");
        break;
      default:
        cout << "Invalid Choice";
    }
  } while (choice != 7);
  return 0;
}

// Section 1
void makeSandwich() {
  cout << "Making a Sandwich\n";

  cout << "1.Get bread\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "2.Spread butter\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "3.Add mayo\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "4.Add tomato\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "5.Add lettuce\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "6.Add cheese\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "7.Add ham\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "8.Put the other half of the bread\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "9.put in a small oven for 2 mins\n";
  this_thread::sleep_for(chrono::milliseconds(200));

  cout << "Sandwich is ready to be devoured!\n";
}

// Section 2
void prepareCoffeeAndToast() {
  string coffeeSteps[] = {
    "Coffee #1: Boil Water",
    "Coffee #2: Put instant coffee, sugar and creamer in the mug",
    "Coffee #3: Pour hot water on the mug", "Coffee #4: Stir",
    "Coffee #5: Enjoy your coffee!"
    };

  string toastSteps[] = {
    "Toast #1: Cut a piece of bread",
    "Toast #2: Spread some butter on the sliced bread",
    "Toast #3: Heat the pan",
    "Toast #4: Toast the bread for 3 to 5 mins",
    "Toast #5: Enjoy your toast!"
    };

  cout << "Start cookin! \n";

  int toast = 0, coffee = 0;
  while (toast <= 4 || coffee <= 4) {
    if (toast <= 4) {
      cout << toastSteps[toast] << endl;
      toast += 1;
      this_thread::sleep_for(chrono::milliseconds(200));
    }
    if (coffee <= 4) {
      cout << coffeeSteps[coffee] << endl;
      coffee += 1;
      this_thread::sleep_for(chrono::milliseconds(200));
    }
  }
}

// Section 3
void washDishes() {
  for (int i = 1; i <= 7; i++) {
    cout << "Washing dish " << i << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
  }
}

void foldClothes() {
  for (int i = 1; i <= 7; i++) {
    cout << "Folding cloth " << i << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
  }
}

void parallelTask() {
  thread t1(washDishes);
  thread t2(foldClothes);
  t1.join();
  t2.join();
}

// Section 4
void prepareFood() {
  string steps[] = {
    "Food #1: Gather ingredients", 
    "Food #2: Chop vegetables",
    "Food #3: Cook the food", 
    "Food #4: Plate the food",
    "Food #5: Food is ready!"
  };

  for (int i = 0; i < 5; ++i) {
    cout << steps[i] << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
  }
}

void decorate() {
  string steps[] = {
    "Decor #1: Bring out decorations",
    "Decor #2: Hang up streamers", 
    "Decor #3: Inflate balloons",
    "Decor #4: Arrange tables and chairs",
    "Decor #5: Decorations complete!"
  };

  for (int i = 0; i < 5; ++i) {
    cout << steps[i] << endl;
    this_thread::sleep_for(chrono::milliseconds(600));
  }
}

void organizeParty() {
  thread t3(prepareFood);
  thread t4(decorate);
  thread t5(setupPlaylist);
  t3.join();
  t4.join();
  t5.join();
}

// Section 4 "Try it Yourself"
void setupPlaylist() {
  string steps[] = {
    "Playlist #1: Pick songs", 
    "Playlist #2: Create a playlist",
    "Playlist #3: Test the speaker",
    "Playlist #4: Set up music queue",
    "Playlist #5: Music is ready!"
  };

  for (int i = 0; i < 5; ++i) {
    cout << steps[i] << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
  }
}

// Section 5
void packBox(const string &who, int boxCount) {
  for (int i = 1; i <= boxCount; i++) {
    cout << who << "  packing box " << i << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
  }
}

void sequentialPacking() {
  cout << "\nSequential Packing\n";
  packBox("You're", 5);
  cout << "All boxes packed (Sequential)!\n";
}

void parallelPacking() {
  cout << "\nParallel Packing\n";

  thread you(packBox, "You're", 5);
  thread friend1(packBox, "With help", 5);

  you.join();
  friend1.join();
  cout << "All boxes packed (Parallel)!\n";
}

// Hands-on Challenge
void gatherMaterials() {
  cout << "[You] Looking up the materials needed\n";
  this_thread::sleep_for(chrono::milliseconds(600));

  cout << "[You] Searching for information online\n";
  this_thread::sleep_for(chrono::milliseconds(700));

  cout << "[You] Grabbing the needed materials for the project\n";
  this_thread::sleep_for(chrono::milliseconds(600));

  cout << "[You] Done gathering all the materials.\n";
}

void makeSlides() {
  cout << "[Friend 1] Opening Canva\n";
  this_thread::sleep_for(chrono::milliseconds(500));

  cout << "[Friend 1] Choosing a template\n";
  this_thread::sleep_for(chrono::milliseconds(600));

  cout << "[Friend 1] Adding information and images\n";
  this_thread::sleep_for(chrono::milliseconds(700));

  cout << "[Friend 1] Finalizing then it is done\n";
}

void printHandouts() {
  cout << "[Friend 2] preparing the file\n";
  this_thread::sleep_for(chrono::milliseconds(500));

  cout << "[Friend 2] Connecting to the printer...\n";
  this_thread::sleep_for(chrono::milliseconds(600));

  cout << "[Friend 2] Printing pages one by one\n";
  this_thread::sleep_for(chrono::milliseconds(800));

  cout << "[Friend 2] Stapling everything together.\n";
}

void handsOn() {
  cout << "Getting the School Project Ready\n\n";
  thread t6(gatherMaterials);
  thread t7(makeSlides);
  thread t8(printHandouts);
  t6.join();
  t7.join();
  t8.join();
  cout << "\nProject preparation complete!\n";
}
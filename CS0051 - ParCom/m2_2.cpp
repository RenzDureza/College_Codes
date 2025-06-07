#include <iostream>
#include <thread>

using namespace std;

void studentTask(string name);

int main() {
    cout << "Teacher (main thread) start the class " << endl;
    thread s1(studentTask, "Hadji");
    thread s2(studentTask, "John"); 
    cout << "Theacher  prepares for the next lesson " << endl;
    s1.join();
    s2.join();
    cout << "Class dismissed" << endl;

    return 0;
}

void studentTask(string name) {
    cout << name << " is doing their homework" << endl;
}
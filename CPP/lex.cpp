#include <iostream>
#include <string>
using namespace std;
string keywords[] = {"int", "char", "String", "float", "Boolean", "print"};
string identifier[] = {};
int integer[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
string operation[] = {"+", "-", "*", "/", "%", "<", ">", "<<", ">>"};
string punctuation[] = {";", ":", "{", "}", "(", ")", "#", ","};
void lex(string code) {
  for (int i = 0; i < code.length(); i++) {
    if
  }
}

int main() {
  string code;
  cout << "Lexical Analyzer" << endl;
  cin >> code;
  lex(code);
}

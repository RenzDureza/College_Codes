#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

int main() {
  vector<pair<regex, string>> patterns = {
      {regex(R"(^\b(abstract|assert|boolean|break|byte|case|catch|char|class|const|continue|default|do|double|else|enum|extends|final|finally|float|for|goto|if|implements|import|instanceof|int|interface|long|native|new|package|private|protected|public|return|short|static|strictfp|super|switch|synchronized|this|throw|throws|transient|try|void|volatile|while)\b)"), "Keyword"},
      {regex(R"(^0|^[1-9][0-9]*)"), "Integer"},
      {regex(R"(^-?\d*\.\d+)"), "Decimal"},
      {regex(R"(^[_a-zA-Z][_a-zA-Z0-9]*)"), "Identifier"},
      {regex(R"(^\"([^\"\\]|\\.)*\")"), "String"},
      {regex(R"(^//[^\n]*)"), "Comment"},
      {regex(R"(^/\*[\s\S]*?\*/)"), "Comment"},
      {regex(R"(^[{}\[\]();,.:])"), "Punctuation"},
      {regex(R"(^[-+*/=<>!&|%^~]+)"), "Operator"},
      {regex(R"(^\s+)"), "Whitespace"}
  };

  ifstream codeFile("test.java");
  stringstream buffer;
  buffer << codeFile.rdbuf();
  string myCode = buffer.str();

  cout << "CS0023_TN28_MIDTERMPROJECT_DUREZA\nLexical Analyzer of Java:\n";

  size_t pos = 0;
  while (pos < myCode.size()) {
    bool matched = false;
    for (auto &token : patterns) {
      smatch match;
      string remaining = myCode.substr(pos);
      if (regex_search(remaining, match, token.first)) {
        if (match.position() == 0) {
          if (token.second != "Whitespace") {
            cout << match.str() << " - " << token.second << endl;
          }
          pos += match.length();
          matched = true;
          break;
        }
      }
    }
    if (!matched) {
      cerr << "Unknown token starting at: " << myCode.substr(pos, 10) << endl;
      break;
    }
  }
  return 0;
}

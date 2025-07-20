#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
using namespace std;

bool isPrintable(char c) {
 return c >= 32 && c <= 126;
}

vector<string> extractStrings(string filePath, size_t minLen = 4) {
 vector<string> found;
 ifstream file(filePath, ios::binary);
 if (!file.is_open()) {
  cerr << "[error] can't open " << filePath << endl;
  return found;
 }

 string buffer;
 char ch;
 while (file.get(ch)) {
  if (isPrintable(ch)) {
   buffer += ch;
  } else {
   if (buffer.length() >= minLen) found.push_back(buffer);
   buffer.clear();
  }
 }
 if (buffer.length() >= minLen) found.push_back(buffer);
 return found;
}

// convert hex like "68656c6c6f" -> "hello"
string hex2ascii(string hex) {
 stringstream ss;
 for (size_t i = 0; i < hex.length(); i += 2) {
  string byte = hex.substr(i, 2);
  char chr = (char)(strtol(byte.c_str(), nullptr, 16));
  ss << chr;
 }
 return ss.str();
}

void dumpAnalysis(vector<string> strList) {
 regex b64("([A-Za-z0-9+/]{8,}={0,2})");
 regex hex("([0-9a-fA-F]{8,})");

 for (auto s : strList) {
  if (regex_match(s, b64)) {
   cout << "[b64]  " << s << endl;
  }
  else if (regex_match(s, hex)) {
   cout << "[hex]  " << s << " -> " << hex2ascii(s.substr(0, 16)) << endl;
  }
  else {
   cout << "[str]  " << s << endl;
  }
 }
}

int main(int argc, char* argv[]) {
 if (argc != 2) {
  cout << "Usage: ./stringreaper <filename>" << endl;
  return 0;
 }

 string file = argv[1];
 cout << "[*] scanning " << file << "...\n";
 auto strings = extractStrings(file);
 cout << "[*] found " << strings.size() << " strings\n\n";
 dumpAnalysis(strings);
 return 0;
}

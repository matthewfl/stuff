#include <iostream>
#include <map>
#include <string>

using namespace std;

std::map<string, string> m_;

namespace {
  struct something {
    something () {
      m_.insert(pair<string, string>("what", "hello"));
    }
  } random;
}

int main () {
  cout << m_["what"] << endl;
}

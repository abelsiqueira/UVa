#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main () {
  char text[256];
  while (cin.getline (text, 256)) {
    for (size_t i = 0; i < 256; i++) {
      if (text[i] == 0)
        break;
      text[i] -= 7;
    }
    cout << text << endl;
  }
  return 0;
}

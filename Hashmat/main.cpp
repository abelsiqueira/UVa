#include <iostream>

using namespace std;

int main () {
  int x, y;
  while (!cin.eof()) {
    cin >> x >> y;
    if (cin.eof())
      break;
    cout << y - x << endl;
  }
  return 0;
}

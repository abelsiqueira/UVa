#include <iostream>
#include <cmath>

using namespace std;

int main () {
  int x, y;
  while (!cin.eof()) {
    cin >> x >> y;
    if (cin.eof())
      break;
    cout << fabs(y - x) << endl;
  }
  return 0;
}

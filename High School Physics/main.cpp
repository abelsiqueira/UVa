#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main () {
  int v, t;
  while (!cin.eof()) {
    cin >> v >> t;
    if (cin.eof())
      break;
    cout << setiosflags(ios::fixed) <<
      setprecision(0) << 2*v*t << endl;
  }
  return 0;
}

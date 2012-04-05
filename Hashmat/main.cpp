#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main () {
  long int x, y;
  while (!cin.eof()) {
    cin >> x >> y;
    if (cin.eof())
      break;
    cout << setiosflags(ios::fixed) <<
      setprecision(0) << fabs(y - x) << endl;
  }
  return 0;
}

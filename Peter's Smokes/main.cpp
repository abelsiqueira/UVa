#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main () {
  unsigned long int n, k, d, r, cigars;
  while (!cin.eof()) {
    cin >> n >> k;
    if (cin.eof())
      break;
    cigars = n;
    d = n/k;
    r = n - d*k;
    n = d;
    while (n > 0) {
      cigars += n;
      d = (n + r)/k;
      r = n + r - d*k;
      n = d;
    }
    cout << cigars << endl;
  }
  return 0;
}

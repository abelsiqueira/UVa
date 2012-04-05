#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main () {
  int n = 0, f = 0;
  int A = 0, N = 0, E = 0;
  cin >> n;
  while (n > 0) {
    n--;
    cin >> f;
    int budget = 0.0;
    while (f > 0) {
      f--;
      cin >> A >> N >> E;
      budget += A*E;
    }
    cout << setprecision(0) << setiosflags(ios::fixed) << budget << endl;
  }
  return 0;
}
